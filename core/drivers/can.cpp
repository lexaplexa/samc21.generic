/*****************************************************************************
 * can.cpp
 *
 * Created: 4.1.2018 10:05:10
 * Revised: 4.4.2019
 * Author: uidm2956
 * BOARD: 
 * ABOUT:
 *
 *****************************************************************************/

#include "can.h"
#include <string.h>

namespace Core::Drivers
{
    CAN::CAN(::Can *pCan, uint8_t unGeneratorNum)
    {
        m_pCan = pCan;
        
        /* Enable peripheral clock */
        if (m_pCan == CAN0)         {GCLK->PCHCTRL[CAN0_GCLK_ID].reg = unGeneratorNum|GCLK_PCHCTRL_CHEN; MCLK->AHBMASK.bit.CAN0_ = true;}
        else if (m_pCan == CAN1)    {GCLK->PCHCTRL[CAN1_GCLK_ID].reg = unGeneratorNum|GCLK_PCHCTRL_CHEN; MCLK->AHBMASK.bit.CAN1_ = true;}
    }
    
    void CAN::Init(uint8_t unTxFifoSize, uint8_t unRxFifo0Size, uint8_t unRxFifo1Size, uint8_t unRxStdFilterSize, uint8_t unRxExtFilterSize, CAN_DATA_FIELD_SIZE_enum eDataFieldSize)
    {
        /* Initialization */
        can_init_state();
        
        /* TX FIFO initialization */
        if (m_psTxFifo != nullptr) {delete m_psTxFifo;}
        m_psTxFifo = nullptr;
        m_pCan->TXBC.reg = 0;
        if (unTxFifoSize > 0 && unTxFifoSize <= TX_FIFO_MAX_SIZE)
        {
            m_psTxFifo = new CAN_TX_FIFO_ELEMENT_struct[unTxFifoSize];
            can_tx_buffer_config(m_psTxFifo, unTxFifoSize);
            for (uint16_t i=0; i<sizeof(CAN_TX_FIFO_ELEMENT_struct)*unTxFifoSize; i++) {*((uint8_t*)m_psTxFifo+i) = 0x00;}
        }
        
        /* RX FIFO0 initialization */
        if (m_psRxFifo0 != nullptr) {delete m_psRxFifo0;}
        m_psRxFifo0 = nullptr;
        m_pCan->RXF0C.reg = 0;
        if (unRxFifo0Size > 0 && unRxFifo0Size <= RX_FIFO0_MAX_SIZE)
        {
            m_psRxFifo0 = new CAN_RX_FIFO_ELEMENT_struct[unRxFifo0Size];
            can_rx_fifo0_config(m_psRxFifo0, unRxFifo0Size);
            for (uint16_t i=0; i<sizeof(CAN_RX_FIFO_ELEMENT_struct)*unRxFifo0Size; i++) {*((uint8_t*)m_psRxFifo0+i) = 0x00;}
        }
        
        /* RX FIFO1 initialization */
        if (m_psRxFifo1 != nullptr) {delete m_psRxFifo1;}
        m_psRxFifo1 = nullptr;
        m_pCan->RXF1C.reg = 0;
        if (unRxFifo1Size > 0 && unRxFifo1Size <= RX_FIFO1_MAX_SIZE)
        {
            m_psRxFifo1 = new CAN_RX_FIFO_ELEMENT_struct[unRxFifo1Size];
            can_rx_fifo1_config(m_psRxFifo1, unRxFifo1Size);
            for (uint16_t i=0; i<sizeof(CAN_RX_FIFO_ELEMENT_struct)*unRxFifo1Size; i++) {*((uint8_t*)m_psRxFifo1+i) = 0x00;}
        }
        
        /* RX standard ID filter */
        if (m_psRxStdFilter != nullptr) {delete m_psRxStdFilter;}
        m_psRxStdFilter = nullptr;
        m_pCan->SIDFC.reg = 0;
        if (unRxStdFilterSize > 0 && unRxStdFilterSize <= RX_STD_ID_FILTER_MAX_SIZE)
        {
            m_psRxStdFilter = new CAN_RX_STD_ID_FILTER_ELEMENT_struct[unRxStdFilterSize];
            can_rx_filter_std_config(m_psRxStdFilter, unRxStdFilterSize);
            for (uint16_t i=0; i<sizeof(CAN_RX_STD_ID_FILTER_ELEMENT_struct)*unRxStdFilterSize; i++) {*((uint8_t*)m_psRxStdFilter+i) = 0x00;}
        }
        
        /* RX extended ID filter */
        if (m_psRxExtFilter != nullptr) {delete m_psRxExtFilter;}
        m_psRxExtFilter = nullptr;
        m_pCan->XIDFC.reg = 0;
        if (unRxExtFilterSize > 0 && unRxExtFilterSize <= RX_STD_ID_FILTER_MAX_SIZE)
        {
            m_psRxExtFilter = new CAN_RX_EXT_ID_FILTER_ELEMENT_struct[unRxExtFilterSize];
            can_rx_filter_ext_config(m_psRxExtFilter, unRxExtFilterSize);
            for (uint16_t i=0; i<sizeof(CAN_RX_STD_ID_FILTER_ELEMENT_struct)*unRxExtFilterSize; i++) {*((uint8_t*)m_psRxExtFilter+i) = 0x00;}
        }
        
        /* Data field size (CAN FD not implemented yet) */
        m_pCan->TXESC.bit.TBDS = CAN_DATA_FIELD_SIZE_8;
        m_pCan->RXESC.bit.F0DS = CAN_DATA_FIELD_SIZE_8;
        m_pCan->RXESC.bit.F1DS = CAN_DATA_FIELD_SIZE_8;
        
        /* Normal state */
        can_normal_state();
    }
    
    void CAN::SetBaud(uint8_t unBaudPrescaler, uint8_t unTimeSegment1, uint8_t unTimeSegment2)
    {
        can_init_state();
        can_bit_timing(unBaudPrescaler, unTimeSegment1, unTimeSegment2);
        can_normal_state();
    }
    
    CAN_RET_CODE_enum CAN::eAddStdFilter(uint16_t unCanID)
    {
        if (m_psRxStdFilter == nullptr) {return CAN_RET_CODE_FIFO_UNDEFINED;}
        if (unCanID >= 0x800)           {return CAN_RET_CODE_OUT_OF_RANGE;}
        uint8_t unRxStdFilterSize = m_pCan->SIDFC.bit.LSS;
        for (uint8_t i=0; i<unRxStdFilterSize; i++)
        {
            if (m_psRxStdFilter[i].SFEC == 0)          /* Filter element is disabled */
            {
                m_psRxStdFilter[i].SFT = 1;            /* DUAL */
                m_psRxStdFilter[i].SFEC = 2;           /* Store to FIFO1 if match */
                m_psRxStdFilter[i].SFID1 = unCanID;
                m_psRxStdFilter[i].SFID2 = unCanID;
                return CAN_RET_CODE_OK;
            }
        }
        return CAN_RET_CODE_BUFFER_FULL;
    }
    
    CAN_RET_CODE_enum CAN::eAddExtFilter(uint32_t unCanID)
    {
        if (m_psRxExtFilter == nullptr) {return CAN_RET_CODE_FIFO_UNDEFINED;}
        if (unCanID < 0x800)            {return CAN_RET_CODE_OUT_OF_RANGE;}
        uint8_t unRxExtFilterSize = m_pCan->XIDFC.bit.LSE;
        for (uint8_t i=0; i<unRxExtFilterSize; i++)
        {
            if (m_psRxExtFilter[i].EFEC == 0)          /* Filter element is disabled */
            {
                m_psRxExtFilter[i].EFT = 1;            /* DUAL */
                m_psRxExtFilter[i].EFEC = 2;           /* Store to FIFO1 if match */
                m_psRxExtFilter[i].EFID1 = unCanID;
                m_psRxExtFilter[i].EFID2 = unCanID;
                return CAN_RET_CODE_OK;
            }
        }
        return CAN_RET_CODE_BUFFER_FULL;
    }
    
    void CAN::DisableStdFilters()
    {
        if (m_psRxStdFilter == nullptr) {return;}
        uint8_t unRxStdFilterSize = m_pCan->SIDFC.bit.LSS;
        for (uint8_t i=0; i<unRxStdFilterSize; i++) {m_psRxStdFilter[i].SFEC = 0;}
    }
    
    void CAN::DisableExtFilters()
    {
        if (m_psRxExtFilter == nullptr) {return;}
        uint8_t unRxExtFilterSize = m_pCan->XIDFC.bit.LSE;
        for (uint8_t i=0; i<unRxExtFilterSize; i++) {m_psRxExtFilter[i].EFEC = 0;}
    }
    
    CAN_RET_CODE_enum CAN::eSendMsg(CAN_MSG_struct *psCanMsg)
    {
        if (m_psTxFifo == nullptr)  {return CAN_RET_CODE_FIFO_UNDEFINED;}
        if (can_tx_fifo_full())     {return CAN_RET_CODE_BUFFER_MSG_LOST;}
        
        uint8_t unLength;
        if (psCanMsg->unDLC <= 8)       {unLength = psCanMsg->unDLC;}
        else if (psCanMsg->unDLC == 9)  {unLength = 12;}
        else if (psCanMsg->unDLC == 10) {unLength = 16;}
        else if (psCanMsg->unDLC == 11) {unLength = 20;}
        else if (psCanMsg->unDLC == 12) {unLength = 24;}
        else if (psCanMsg->unDLC == 13) {unLength = 32;}
        else if (psCanMsg->unDLC == 14) {unLength = 48;}
        else if (psCanMsg->unDLC == 15) {unLength = 64;}
        
        if (psCanMsg->unID >= 0x800)
        {
            /* Extended ID */
            m_psTxFifo[m_pCan->TXFQS.bit.TFQPI].ID = psCanMsg->unID;
            m_psTxFifo[m_pCan->TXFQS.bit.TFQPI].XTD = true;
        }
        else
        {
            /* Standard ID */
            m_psTxFifo[m_pCan->TXFQS.bit.TFQPI].ID = psCanMsg->unID<<18;
            m_psTxFifo[m_pCan->TXFQS.bit.TFQPI].XTD = false;
        }
        m_psTxFifo[m_pCan->TXFQS.bit.TFQPI].DLC = psCanMsg->unDLC;
        
        for (uint8_t i=0; i<unLength; i++) {m_psTxFifo[m_pCan->TXFQS.bit.TFQPI].aunData[i] = psCanMsg->aunData[i];}
        can_tx_add_request(m_pCan->TXFQS.bit.TFQPI);
        if (can_tx_fifo_full())     {return CAN_RET_CODE_BUFFER_FULL;}
        return CAN_RET_CODE_OK;
    }
    
    CAN_RET_CODE_enum CAN::eAddTxElm(CAN_TX_FIFO_ELEMENT_struct* psTxMsg)
    {
        if (m_psTxFifo == nullptr)  {return CAN_RET_CODE_FIFO_UNDEFINED;}
        if (can_tx_fifo_full())     {return CAN_RET_CODE_BUFFER_MSG_LOST;}
        memcpy(&m_psTxFifo[m_pCan->TXFQS.bit.TFQPI].T0_reg, psTxMsg, sizeof(CAN_TX_FIFO_ELEMENT_struct));
        can_tx_add_request(m_pCan->TXFQS.bit.TFQPI);
        if (can_tx_fifo_full())     {return CAN_RET_CODE_BUFFER_FULL;}
        return CAN_RET_CODE_OK;
    }
    
    CAN_RET_CODE_enum CAN::eRxFifo0Status()
    {
        if (m_psRxFifo0 == nullptr)         {return CAN_RET_CODE_FIFO_UNDEFINED;}
        if (can_rx_fifo0_msg_lost())        {return CAN_RET_CODE_BUFFER_MSG_LOST;}
        if (can_rx_fifo0_full())            {return CAN_RET_CODE_BUFFER_FULL;}
        if (can_rx_fifo0_fill_size() == 0)  {return CAN_RET_CODE_BUFFER_EMPTY;}
        return CAN_RET_CODE_BUFFER_FILLED;
    }
    
    CAN_RET_CODE_enum CAN::eRxFifo1Status()
    {
        if (m_psRxFifo1 == nullptr)         {return CAN_RET_CODE_FIFO_UNDEFINED;}
        if (can_rx_fifo1_msg_lost())        {return CAN_RET_CODE_BUFFER_MSG_LOST;}
        if (can_rx_fifo1_full())            {return CAN_RET_CODE_BUFFER_FULL;}
        if (can_rx_fifo1_fill_size() == 0)  {return CAN_RET_CODE_BUFFER_EMPTY;}
        return CAN_RET_CODE_BUFFER_FILLED;
    }
    
    CAN_RET_CODE_enum CAN::eRxFifo0LastMsg(CAN_RX_FIFO_ELEMENT_struct* psRxMsg)
    {
        if (m_psRxFifo0 == nullptr)         {return CAN_RET_CODE_FIFO_UNDEFINED;}
        if (can_rx_fifo0_fill_size() == 0)  {return CAN_RET_CODE_BUFFER_EMPTY;}
        memcpy(psRxMsg, &m_psRxFifo0[can_rx_fifo0_last_index()].R0_reg, sizeof(CAN_RX_FIFO_ELEMENT_struct));
        can_rx_fifo0_flush_last();
        can_int_clear_flag(CAN_IR_RF0L);
        return CAN_RET_CODE_OK;
    }
    
    CAN_RET_CODE_enum CAN::eRxFifo1LastMsg(CAN_RX_FIFO_ELEMENT_struct* psRxMsg)
    {
        if (m_psRxFifo1 == nullptr)         {return CAN_RET_CODE_FIFO_UNDEFINED;}
        if (can_rx_fifo1_fill_size() == 0)  {return CAN_RET_CODE_BUFFER_EMPTY;}
        memcpy(psRxMsg, &m_psRxFifo1[can_rx_fifo1_last_index()].R0_reg, sizeof(CAN_RX_FIFO_ELEMENT_struct));
        can_rx_fifo1_flush_last();
        can_int_clear_flag(CAN_IR_RF1L);
        return CAN_RET_CODE_OK;
    }
}