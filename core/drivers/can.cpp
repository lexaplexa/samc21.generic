/*****************************************************************************
 * can.cpp
 *
 * Created: 4.1.2018 10:05:10
 * Revised: 22.7.2019
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
    
    void CAN::Init(uint8_t unTxFifoSize, uint8_t unRxFifo0Size, uint8_t unRxFifo1Size, uint8_t unRxStdFilterSize, uint8_t unRxExtFilterSize)
    {
        /* Delete old pointers */
        if (m_psTxFifo != nullptr)      {delete m_psTxFifo; m_psTxFifo = nullptr;}
        if (m_psRxFifo0 != nullptr)     {delete m_psRxFifo0; m_psRxFifo0 = nullptr;}
        if (m_psRxFifo1 != nullptr)     {delete m_psRxFifo1; m_psRxFifo1 = nullptr;}
        if (m_psRxStdFilter != nullptr) {delete m_psRxStdFilter; m_psRxStdFilter = nullptr;}
        if (m_psRxExtFilter != nullptr) {delete m_psRxExtFilter; m_psRxExtFilter = nullptr;}
        
        /* Initialization */
        can_init_state();

        /* TX FIFO initialization */
        m_pCan->TXBC.reg = 0;
        if (unTxFifoSize > 0 && unTxFifoSize <= CAN_TX_FIFO_MAX_SIZE)
        {
            m_psTxFifo = new CAN_TX_FIFO_ELEMENT_struct[unTxFifoSize];
            m_pCan->TXBC.reg = CAN_TXBC_TBSA((uint32_t)m_psTxFifo)|CAN_TXBC_TFQS(unTxFifoSize);
            for (uint16_t i=0; i<(sizeof(CAN_TX_FIFO_ELEMENT_struct)*unTxFifoSize/4); i++) {*((uint32_t*)m_psTxFifo+i) = 0x00000000;}
        }
        
        /* RX FIFO0 initialization */
        m_pCan->RXF0C.reg = 0;
        if (unRxFifo0Size > 0 && unRxFifo0Size <= CAN_RX_FIFO0_MAX_SIZE)
        {
            m_psRxFifo0 = new CAN_RX_FIFO_ELEMENT_struct[unRxFifo0Size];
            m_pCan->RXF0C.reg = CAN_RXF0C_F0SA((uint32_t)m_psRxFifo0)|CAN_RXF0C_F0S(unRxFifo0Size);
            for (uint16_t i=0; i<(sizeof(CAN_RX_FIFO_ELEMENT_struct)*unRxFifo0Size/4); i++) {*((uint32_t*)m_psRxFifo0+i) = 0x00000000;}
        }
        
        /* RX FIFO1 initialization */
        m_pCan->RXF1C.reg = 0;
        if (unRxFifo1Size > 0 && unRxFifo1Size <= CAN_RX_FIFO1_MAX_SIZE)
        {
            m_psRxFifo1 = new CAN_RX_FIFO_ELEMENT_struct[unRxFifo1Size];
            m_pCan->RXF1C.reg = CAN_RXF1C_F1SA((uint32_t)m_psRxFifo1)|CAN_RXF1C_F1S(unRxFifo1Size);
            for (uint16_t i=0; i<(sizeof(CAN_RX_FIFO_ELEMENT_struct)*unRxFifo1Size/4); i++) {*((uint32_t*)m_psRxFifo1+i) = 0x00000000;}
        }
        
        /* RX standard ID filter */
        m_pCan->SIDFC.reg = 0;
        if (unRxStdFilterSize > 0 && unRxStdFilterSize <= CAN_RX_STD_ID_FILTER_MAX_SIZE)
        {
            m_psRxStdFilter = new CAN_RX_STD_ID_FILTER_ELEMENT_struct[unRxStdFilterSize];
            m_pCan->SIDFC.reg = CAN_SIDFC_FLSSA((uint32_t)m_psRxStdFilter)|CAN_SIDFC_LSS(unRxStdFilterSize);
            for (uint16_t i=0; i<sizeof(CAN_RX_STD_ID_FILTER_ELEMENT_struct)*unRxStdFilterSize; i++) {*((uint8_t*)m_psRxStdFilter+i) = 0x00;}
        }
        
        /* RX extended ID filter */
        m_pCan->XIDFC.reg = 0;
        if (unRxExtFilterSize > 0 && unRxExtFilterSize <= CAN_RX_STD_ID_FILTER_MAX_SIZE)
        {
            m_psRxExtFilter = new CAN_RX_EXT_ID_FILTER_ELEMENT_struct[unRxExtFilterSize];
            m_pCan->XIDFC.reg = CAN_XIDFC_FLESA((uint32_t)m_psRxExtFilter)|CAN_XIDFC_LSE(unRxExtFilterSize);
            for (uint16_t i=0; i<sizeof(CAN_RX_STD_ID_FILTER_ELEMENT_struct)*unRxExtFilterSize; i++) {*((uint8_t*)m_psRxExtFilter+i) = 0x00;}
        }
        
        /* Set Data field size for FIFO's */
        m_pCan->TXESC.bit.TBDS = CAN_DATA_FIELD_Val;
        m_pCan->RXESC.bit.F0DS = CAN_DATA_FIELD_Val;
        m_pCan->RXESC.bit.F1DS = CAN_DATA_FIELD_Val;

        /* CAN FD enable */
        m_pCan->CCCR.bit.FDOE = true;

        /* Disable bit rate switch. Can be enabled in function SetBaudFd() */
        m_pCan->CCCR.bit.BRSE = false;

        /* Clear flags */
        m_pCan->IR.reg = 0xFF;

        /* Normal state */
        can_normal_state();
    }
    
    void CAN::SetBaud(uint8_t unBaudPrescaler, uint8_t unTimeSegment1, uint8_t unTimeSegment2)
    {
        can_init_state();
        m_pCan->NBTP.reg = CAN_NBTP_NBRP(unBaudPrescaler)|CAN_NBTP_NTSEG1(unTimeSegment1)|CAN_NBTP_NTSEG2(unTimeSegment2)|CAN_NBTP_NSJW(3);
        m_pCan->CCCR.bit.BRSE = false;
        can_normal_state();
    }

    void CAN::SetBaudFd(uint8_t unBaudPrescaler, uint8_t unTimeSegment1, uint8_t unTimeSegment2)
    {
        can_init_state();
        m_pCan->DBTP.reg = CAN_DBTP_DBRP(unBaudPrescaler)|CAN_DBTP_DTSEG1(unTimeSegment1)|CAN_DBTP_DTSEG2(unTimeSegment2)|CAN_DBTP_DSJW(3);
        m_pCan->CCCR.bit.BRSE = true;
        can_normal_state();
    }
    
    Core::Drivers::CAN_RET_CODE_enum CAN::eAddFilter(uint32_t unCanID)
    {
        /* Extended ID */
        if (unCanID >= 0x800)
        {
            if (m_psRxExtFilter == nullptr) {return CAN_RET_CODE_FIFO_UNDEFINED;}
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
        /* Standard ID */
        else
        {
            if (m_psRxStdFilter == nullptr) {return CAN_RET_CODE_FIFO_UNDEFINED;}
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
    }

    void CAN::DisableFilters()
    {
        /* Standard filters */
        if (m_psRxStdFilter != nullptr)
        {
            uint8_t unRxStdFilterSize = m_pCan->SIDFC.bit.LSS;
            for (uint8_t i=0; i<unRxStdFilterSize; i++) {m_psRxStdFilter[i].SFEC = 0;}
        }        
        /* Extended filters */
        if (m_psRxExtFilter != nullptr)
        {
            uint8_t unRxExtFilterSize = m_pCan->XIDFC.bit.LSE;
            for (uint8_t i=0; i<unRxExtFilterSize; i++) {m_psRxExtFilter[i].EFEC = 0;}
        }
    }

    CAN_RET_CODE_enum CAN::eSendMsg(CAN_MSG_struct *psCanMsg)
    {
        uint8_t unLength;
        CAN_TX_FIFO_ELEMENT_struct* psTxFifoElm = &m_psTxFifo[m_pCan->TXFQS.bit.TFQPI];

        if (m_psTxFifo == nullptr)  {return CAN_RET_CODE_FIFO_UNDEFINED;}
        if (m_pCan->TXFQS.bit.TFQF) {return CAN_RET_CODE_BUFFER_MSG_LOST;}
        
        if      (psCanMsg->eDLC <= CAN_DATA_LENGTH_CODE_8)  {unLength = psCanMsg->eDLC; psTxFifoElm->FDF = 0;}
        else if (psCanMsg->eDLC == CAN_DATA_LENGTH_CODE_12) {unLength = 12; psTxFifoElm->FDF = 1;}
        else if (psCanMsg->eDLC == CAN_DATA_LENGTH_CODE_16) {unLength = 16; psTxFifoElm->FDF = 1;}
        else if (psCanMsg->eDLC == CAN_DATA_LENGTH_CODE_20) {unLength = 20; psTxFifoElm->FDF = 1;}
        else if (psCanMsg->eDLC == CAN_DATA_LENGTH_CODE_24) {unLength = 24; psTxFifoElm->FDF = 1;}
        else if (psCanMsg->eDLC == CAN_DATA_LENGTH_CODE_32) {unLength = 32; psTxFifoElm->FDF = 1;}
        else if (psCanMsg->eDLC == CAN_DATA_LENGTH_CODE_48) {unLength = 48; psTxFifoElm->FDF = 1;}
        else if (psCanMsg->eDLC == CAN_DATA_LENGTH_CODE_64) {unLength = 64; psTxFifoElm->FDF = 1;}

        /* Set bit rate switch */
        if (m_pCan->CCCR.bit.BRSE) {psTxFifoElm->BRS = true;}
        else {psTxFifoElm->BRS = false;}
        /* Extended ID */
        if (psCanMsg->unID >= 0x800) {psTxFifoElm->ID = psCanMsg->unID; psTxFifoElm->XTD = true;}
        /* Standard ID */
        else {psTxFifoElm->ID = psCanMsg->unID<<18; psTxFifoElm->XTD = false;}
        /* Copy Data length code */
        psTxFifoElm->DLC = psCanMsg->eDLC;
        /* Copy CAN data to FIFO element */
        for (uint8_t i=0; i<unLength; i++) {psTxFifoElm->aunData[i] = psCanMsg->pData[i];}
        /* Add transmit request */
        m_pCan->TXBAR.reg = 1<<m_pCan->TXFQS.bit.TFQPI;

        if (m_pCan->TXFQS.bit.TFQF) {return CAN_RET_CODE_BUFFER_FULL;}
        return CAN_RET_CODE_OK;
    }
    
    CAN_RET_CODE_enum CAN::eAddTxElm(CAN_TX_FIFO_ELEMENT_struct* psTxMsg)
    {
        CAN_TX_FIFO_ELEMENT_struct* psTxFifoElm = &m_psTxFifo[m_pCan->TXFQS.bit.TFQPI];

        if (m_psTxFifo == nullptr)  {return CAN_RET_CODE_FIFO_UNDEFINED;}
        if (m_pCan->TXFQS.bit.TFQF) {return CAN_RET_CODE_BUFFER_MSG_LOST;}
        memcpy(psTxFifoElm, psTxMsg, sizeof(CAN_TX_FIFO_ELEMENT_struct));
        /* Add transmit request */
        m_pCan->TXBAR.reg = 1<<m_pCan->TXFQS.bit.TFQPI;
        if (m_pCan->TXFQS.bit.TFQF) {return CAN_RET_CODE_BUFFER_FULL;}
        return CAN_RET_CODE_OK;
    }
    
    CAN_RET_CODE_enum CAN::eRxFifo0Status()
    {
        if (m_psRxFifo0 == nullptr)         {return CAN_RET_CODE_FIFO_UNDEFINED;}
        if (m_pCan->RXF0S.bit.RF0L)         {return CAN_RET_CODE_BUFFER_MSG_LOST;}
        if (m_pCan->RXF0S.bit.F0F)          {return CAN_RET_CODE_BUFFER_FULL;}
        if (!m_pCan->RXF0S.bit.F0FL)        {return CAN_RET_CODE_BUFFER_EMPTY;}
        return CAN_RET_CODE_BUFFER_FILLED;
    }
    
    CAN_RET_CODE_enum CAN::eRxFifo1Status()
    {
        if (m_psRxFifo1 == nullptr)         {return CAN_RET_CODE_FIFO_UNDEFINED;}
        if (m_pCan->RXF1S.bit.RF1L)         {return CAN_RET_CODE_BUFFER_MSG_LOST;}
        if (m_pCan->RXF1S.bit.F1F)          {return CAN_RET_CODE_BUFFER_FULL;}
        if (!m_pCan->RXF1S.bit.F1FL)        {return CAN_RET_CODE_BUFFER_EMPTY;}
        return CAN_RET_CODE_BUFFER_FILLED;
    }
    
    CAN_RET_CODE_enum CAN::eRxFifo0LastMsg(CAN_RX_FIFO_ELEMENT_struct* psRxMsg)
    {
        CAN_RX_FIFO_ELEMENT_struct* psRxFifoElm = &m_psRxFifo0[m_pCan->RXF0S.bit.F0GI];

        if (m_psRxFifo0 == nullptr)         {return CAN_RET_CODE_FIFO_UNDEFINED;}
        if (!m_pCan->RXF0S.bit.F0FL)        {return CAN_RET_CODE_BUFFER_EMPTY;}
        memcpy(psRxMsg, psRxFifoElm, sizeof(CAN_RX_FIFO_ELEMENT_struct));
        /* Flush last received message */
        m_pCan->RXF0A.bit.F0AI = m_pCan->RXF0S.bit.F0GI;
        /* Clear message lost flag */
        m_pCan->IR.bit.RF0L = 1;
        return CAN_RET_CODE_OK;
    }
    
    CAN_RET_CODE_enum CAN::eRxFifo1LastMsg(CAN_RX_FIFO_ELEMENT_struct* psRxMsg)
    {
        CAN_RX_FIFO_ELEMENT_struct* psRxFifoElm = &m_psRxFifo1[m_pCan->RXF1S.bit.F1GI];

        if (m_psRxFifo1 == nullptr)         {return CAN_RET_CODE_FIFO_UNDEFINED;}
        if (!m_pCan->RXF1S.bit.F1FL)        {return CAN_RET_CODE_BUFFER_EMPTY;}
        memcpy(psRxMsg, psRxFifoElm, sizeof(CAN_RX_FIFO_ELEMENT_struct));
        /* Flush last received message */
        m_pCan->RXF1A.bit.F1AI = m_pCan->RXF1S.bit.F1GI;
        /* Clear message lost flag */
        m_pCan->IR.bit.RF1L = 1;
        return CAN_RET_CODE_OK;
    }
}
