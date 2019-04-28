/*****************************************************************************
 * dma.h
 *
 * Created: 9.1.2018 9:17:44
 * Revised: 4.4.2019
 * Author: uidm2956
 * BOARD:
 * ABOUT:
 *
 *****************************************************************************/


#ifndef DMA_H_
#define DMA_H_

#include <sam.h>

namespace Core
{
	namespace Drivers
    {
        /************************************************************************/
        /* CHANNEL DESCRIPTOR                                                   */
        /************************************************************************/
        struct DMA_CH_DESCRIPTOR_struct 
        {
            union 
            {
                struct 
                {
                    uint16_t VALID:1;
                    uint16_t EVOSEL:2;
                    uint16_t BLOCKACT:2;
                    uint16_t :3;
                    uint16_t BEATSIZE:2;
                    uint16_t SRCINC:1;
                    uint16_t DSTINC:1;
                    uint16_t STEPSEL:1;
                    uint16_t STEPSIZE:3;            
                };
                uint16_t reg;
            } BTCTRL;
            uint16_t BTCNT;
            uint32_t SRCADDR;
            uint64_t DSTADDR:32;
            uint64_t DESCADDR:32;
        };
        
        /************************************************************************/
        /* ENUMS                                                                */
        /************************************************************************/
        enum DMA_TRIGSRC_enum {
            DMA_TRIGSRC_DIS,
            DMA_TRIGSRC_TSENS,
            DMA_TRIGSRC_SERCOM0_RX,
            DMA_TRIGSRC_SERCOM0_TX,
            DMA_TRIGSRC_SERCOM1_RX,
            DMA_TRIGSRC_SERCOM1_TX,
            DMA_TRIGSRC_SERCOM2_RX,
            DMA_TRIGSRC_SERCOM2_TX,
            DMA_TRIGSRC_SERCOM3_RX,
            DMA_TRIGSRC_SERCOM3_TX,
            DMA_TRIGSRC_SERCOM4_RX,
            DMA_TRIGSRC_SERCOM4_TX,
            DMA_TRIGSRC_SERCOM5_RX,
            DMA_TRIGSRC_SERCOM5_TX,
            DMA_TRIGSRC_CAN0_DEBUG,
            DMA_TRIGSRC_CAN1_DEBUG,
            DMA_TRIGSRC_TCC0_OVF,
            DMA_TRIGSRC_TCC0_MC0,
            DMA_TRIGSRC_TCC0_MC1,
            DMA_TRIGSRC_TCC0_MC2,
            DMA_TRIGSRC_TCC0_MC3,
            DMA_TRIGSRC_TCC1_OVF,
            DMA_TRIGSRC_TCC1_MC0,
            DMA_TRIGSRC_TCC1_MC1,
            DMA_TRIGSRC_TCC2_OVF,
            DMA_TRIGSRC_TCC2_MC0,
            DMA_TRIGSRC_TCC2_MC1,
            DMA_TRIGSRC_TC0_OVF,
            DMA_TRIGSRC_TC0_MC0,
            DMA_TRIGSRC_TC0_MC1,
            DMA_TRIGSRC_TC1_OVF,
            DMA_TRIGSRC_TC1_MC0,
            DMA_TRIGSRC_TC1_MC1,
            DMA_TRIGSRC_TC2_OVF,
            DMA_TRIGSRC_TC2_MC0,
            DMA_TRIGSRC_TC2_MC1,
            DMA_TRIGSRC_TC3_OVF,
            DMA_TRIGSRC_TC3_MC0,
            DMA_TRIGSRC_TC3_MC1,
            DMA_TRIGSRC_TC4_OVF,
            DMA_TRIGSRC_TC4_MC0,
            DMA_TRIGSRC_TC4_MC1,
            DMA_TRIGSRC_ADC0_RESRDY,
            DMA_TRIGSRC_ADC1_RESRDY,
            DMA_TRIGSRC_SDADC_RESRDY,
            DMA_TRIGSRC_DAC_EMPTY,
            DMA_TRIGSRC_PTC_EOC,
            DMA_TRIGSRC_PTC_WCOMP,
            DMA_TRIGSRC_PTC_SEQ,
            DMA_TRIGSRC_SERCOM6_RX,
            DMA_TRIGSRC_SERCOM6_TX,
            DMA_TRIGSRC_SERCOM7_RX,
            DMA_TRIGSRC_SERCOM7_TX,
            DMA_TRIGSRC_TC5_OVF,
            DMA_TRIGSRC_TC5_MC0,
            DMA_TRIGSRC_TC5_MC1,
            DMA_TRIGSRC_TC6_OVF,
            DMA_TRIGSRC_TC6_MC0,
            DMA_TRIGSRC_TC6_MC1,
            DMA_TRIGSRC_TC7_OVF,
            DMA_TRIGSRC_TC7_MC0,
            DMA_TRIGSRC_TC7_MC1,
        };
        
        enum DMA_TRIGACT_enum {
            DMA_TRIGACT_BLOCK = DMAC_CHCTRLB_TRIGACT_BLOCK_Val,
            DMA_TRIGACT_BEAT = DMAC_CHCTRLB_TRIGACT_BEAT_Val,    
            DMA_TRIGACT_TRANSACTION = DMAC_CHCTRLB_TRIGACT_TRANSACTION_Val
        };
        
        enum DMA_STEPSIZE_enum {
            DMA_STEPSIZE_X1,       /* Next ADDR = ADDR + (Beat size in byte) * 1 */
            DMA_STEPSIZE_X2,       /* Next ADDR = ADDR + (Beat size in byte) * 2 */
            DMA_STEPSIZE_X4,       /* Next ADDR = ADDR + (Beat size in byte) * 4 */
            DMA_STEPSIZE_X8,       /* Next ADDR = ADDR + (Beat size in byte) * 8 */
            DMA_STEPSIZE_X16,      /* Next ADDR = ADDR + (Beat size in byte) * 16 */
            DMA_STEPSIZE_X32,      /* Next ADDR = ADDR + (Beat size in byte) * 32 */
            DMA_STEPSIZE_X64,      /* Next ADDR = ADDR + (Beat size in byte) * 64 */
            DMA_STEPSIZE_X128,     /* Next ADDR = ADDR + (Beat size in byte) * 128 */
        };
        
        enum DMA_BEATSIZE_enum {
            DMA_BEATSIZE_BYTE,     /* 8-bit */
            DMA_BEATSIZE_HWORD,    /* 16-bit */
            DMA_BEATSIZE_WORD,     /* 32-bit */
        };    
        
        /************************************************************************/
        /* CLASS                                                                */
        /************************************************************************/
        class DMA
        {
            private:
                static DMA_CH_DESCRIPTOR_struct m_asChDescriptor[DMAC_CH_NUM];
                static DMA_CH_DESCRIPTOR_struct m_asWBDescriptor[DMAC_CH_NUM];
                static uint8_t m_unChSum;
                uint8_t m_unChID;
            
            public:
                /**
                 * \brief   DMA initialization
                 * 
                 * \param unGenNum      - clock generation number
                 * 
                 * \return 
                 */
                DMA(uint8_t unGenNum);
                
                /**
                 * \brief   Get DMA channel number
                 * 
                 * 
                 * \return uint8_t
                 */
                uint8_t GetChID() {return m_unChID;}
                
                /**
                 * \brief   Set data transfer
                 * 
                 * \param eBeatSize     - Beat size (Byte - 8bit, HalfWord - 16bit, Word - 32bit)
                 * \param eStepSize     - Address step size
                 * 
                 * \return void
                 */
                void SetChTransfer(DMA_BEATSIZE_enum eBeatSize, DMA_STEPSIZE_enum eStepSize)
                {
                    m_asChDescriptor[m_unChID].BTCTRL.BEATSIZE = eBeatSize;
                    m_asChDescriptor[m_unChID].BTCTRL.STEPSIZE = eStepSize;
                }
                
                /**
                 * \brief   Set address of source and destination (Beat 8bit)
                 * 
                 * \param punSrc        - pointer to source
                 * \param punDest       - pointer to destination
                 * \param unLen         - number of data
                 * \param bSrcInc       - source increment
                 * \param bDstInc       - destination increment
                 * 
                 * \return void
                 */
                void SetAddress(uint8_t* punSrc, uint8_t* punDest, uint16_t unLen, bool bSrcInc, bool bDstInc)
                {
                    m_asChDescriptor[m_unChID].BTCTRL.SRCINC = bSrcInc;
                    m_asChDescriptor[m_unChID].BTCTRL.DSTINC = bDstInc;
                    m_asChDescriptor[m_unChID].BTCNT = unLen;
                    m_asChDescriptor[m_unChID].SRCADDR = (uint32_t)punSrc;
                    m_asChDescriptor[m_unChID].DSTADDR = (uint32_t)punDest;
                    if (m_asChDescriptor[m_unChID].BTCTRL.SRCINC) {m_asChDescriptor[m_unChID].SRCADDR += unLen;}
                    if (m_asChDescriptor[m_unChID].BTCTRL.DSTINC) {m_asChDescriptor[m_unChID].DSTADDR += unLen;}
                }
                
                /**
                 * \brief   Set address of source and destination (Beat 16bit)
                 * 
                 * \param punSrc        - pointer to source
                 * \param punDest       - pointer to destination
                 * \param unLen         - number of data
                 * \param bSrcInc       - source increment
                 * \param bDstInc       - destination increment
                 * 
                 * \return void
                 */
                void SetAddress(uint16_t* punSrc, uint16_t* punDest, uint16_t unLen, bool bSrcInc, bool bDstInc)
                {
                    m_asChDescriptor[m_unChID].BTCTRL.SRCINC = bSrcInc;
                    m_asChDescriptor[m_unChID].BTCTRL.DSTINC = bDstInc;
                    m_asChDescriptor[m_unChID].BTCNT = unLen;
                    m_asChDescriptor[m_unChID].SRCADDR = (uint32_t)punSrc;
                    m_asChDescriptor[m_unChID].DSTADDR = (uint32_t)punDest;
                    if (m_asChDescriptor[m_unChID].BTCTRL.SRCINC) {m_asChDescriptor[m_unChID].SRCADDR += unLen;}
                    if (m_asChDescriptor[m_unChID].BTCTRL.DSTINC) {m_asChDescriptor[m_unChID].DSTADDR += unLen;}
                }
                
                /**
                 * \brief   Set address of source and destination (Beat 32bit)
                 * 
                 * \param punSrc        - pointer to source
                 * \param punDest       - pointer to destination
                 * \param unLen         - number of data
                 * \param bSrcInc       - source increment
                 * \param bDstInc       - destination increment
                 * 
                 * \return void
                 */
                void SetAddress(uint32_t* punSrc, uint32_t* punDest, uint16_t unLen, bool bSrcInc, bool bDstInc)
                {
                    m_asChDescriptor[m_unChID].BTCTRL.SRCINC = bSrcInc;
                    m_asChDescriptor[m_unChID].BTCTRL.DSTINC = bDstInc;
                    m_asChDescriptor[m_unChID].BTCNT = unLen;
                    m_asChDescriptor[m_unChID].SRCADDR = (uint32_t)punSrc;
                    m_asChDescriptor[m_unChID].DSTADDR = (uint32_t)punDest;
                    if (m_asChDescriptor[m_unChID].BTCTRL.SRCINC) {m_asChDescriptor[m_unChID].SRCADDR += unLen;}
                    if (m_asChDescriptor[m_unChID].BTCTRL.DSTINC) {m_asChDescriptor[m_unChID].DSTADDR += unLen;}
                }
                
                /**
                 * \brief   Set Software trigger
                 * 
                 * 
                 * \return void
                 */
                void SetSwTrigger()
                {
                    DMAC->SWTRIGCTRL.reg = 1<<m_unChID;
                }
                
                /**
                 * \brief   Enable DMA channel
                 * 
                 * \param eTriggerAction    - trigger action
                 * \param eTriggerSource    - trigger source
                 * 
                 * \return void
                 */
                void ChEnable(DMA_TRIGACT_enum eTriggerAction, DMA_TRIGSRC_enum eTriggerSource)
                {
                    DMAC->CHID.bit.ID = m_unChID;
                    DMAC->CHCTRLB.bit.TRIGSRC = eTriggerSource;
                    DMAC->CHCTRLB.bit.TRIGACT = eTriggerAction;
                    m_asChDescriptor[m_unChID].BTCTRL.VALID = true;
                    DMAC->CHCTRLA.bit.ENABLE = true;
                }
                
                /**
                 * \brief   Disable DMA channel
                 * 
                 * 
                 * \return void
                 */
                void ChDisable()
                {
                    DMAC->CHID.bit.ID = m_unChID;
                    DMAC->CHCTRLA.bit.ENABLE = false;
                    DMAC->CHCTRLA.bit.SWRST = true;
                    m_asChDescriptor[m_unChID].BTCTRL.VALID = false;
                }
                
                /**
                 * \brief   Copy data from memory to memory (Beat 8bit)
                 * 
                 * \param punSrc        - pointer to source
                 * \param punDest       - pointer to destination
                 * \param unLen         - number of data
                 * 
                 * \return void
                 */
                void MemCopy(uint8_t* punSrc, uint8_t* punDest, uint16_t unLen);
                
                /**
                 * \brief   Copy data from memory to memory (Beat 16bit)
                 * 
                 * \param punSrc        - pointer to source
                 * \param punDest       - pointer to destination
                 * \param unLen         - number of data
                 * 
                 * \return void
                 */
                void MemCopy(uint16_t* punSrc, uint16_t* punDest, uint16_t unLen);
                
                /**
                 * \brief   Copy data from memory to memory (Beat 32bit)
                 * 
                 * \param punSrc        - pointer to source
                 * \param punDest       - pointer to destination
                 * \param unLen         - number of data
                 * 
                 * \return void
                 */
                void MemCopy(uint32_t* punSrc, uint32_t* punDest, uint16_t unLen);
        };
    }
}

#endif /* DMA_H_ */