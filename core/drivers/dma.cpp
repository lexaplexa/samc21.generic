/*****************************************************************************
 * dma.cpp
 *
 * Created: 16.1.2018 10:29:15
 * Revised: 4.4.2019
 * Author: uidm2956
 * BOARD:
 * ABOUT:
 *
 *****************************************************************************/

#include "dma.h"

namespace Core::Drivers
{
    uint8_t DMA::m_unChSum = 0;
    DMA_CH_DESCRIPTOR_struct DMA::m_asChDescriptor[DMAC_CH_NUM] = {0};
    DMA_CH_DESCRIPTOR_struct DMA::m_asWBDescriptor[DMAC_CH_NUM] = {0};

    DMA::DMA(uint8_t unGenNum)
    {
        /* Only if no channel have been created */
        if (!m_unChSum)
        {
            GCLK->PCHCTRL[DMAC_CLK_AHB_ID].reg = unGenNum|GCLK_PCHCTRL_CHEN;
            MCLK->AHBMASK.bit.DMAC_ = true;
        
            DMAC->CTRL.bit.DMAENABLE = false;
            DMAC->CTRL.bit.SWRST = true;
        
            DMAC->BASEADDR.reg = (uint32_t)&m_asChDescriptor;
            DMAC->WRBADDR.reg = (uint32_t)&m_asWBDescriptor;
        
            DMAC->CTRL.bit.LVLEN0 = true;
            DMAC->CTRL.bit.LVLEN1 = true;
            DMAC->CTRL.bit.LVLEN2 = true;
            DMAC->CTRL.bit.LVLEN3 = true;
        
            DMAC->CTRL.bit.DMAENABLE = true;
        }
        /* No other channel is available */
        else if (m_unChSum >= DMAC_CH_NUM) {m_unChID = 0xFF; return;}
        m_unChID = m_unChSum++;
    }

    void DMA::MemCopy(uint8_t* punSrc, uint8_t* punDest, uint16_t unLen)
    {
        ChDisable();
        SetAddress(punSrc,punDest,unLen,true,true);
        SetChTransfer(DMA_BEATSIZE_BYTE, DMA_STEPSIZE_X1);
        ChEnable(DMA_TRIGACT_BEAT, DMA_TRIGSRC_DIS);
        SetSwTrigger();
    }

    void DMA::MemCopy(uint16_t* punSrc, uint16_t* punDest, uint16_t unLen)
    {
        ChDisable();
        SetAddress(punSrc,punDest,unLen,true,true);
        SetChTransfer(DMA_BEATSIZE_HWORD, DMA_STEPSIZE_X1);
        ChEnable(DMA_TRIGACT_BEAT, DMA_TRIGSRC_DIS);
        SetSwTrigger();
    }

    void DMA::MemCopy(uint32_t* punSrc, uint32_t* punDest, uint16_t unLen)
    {
        ChDisable();
        SetAddress(punSrc,punDest,unLen,true,true);
        SetChTransfer(DMA_BEATSIZE_WORD, DMA_STEPSIZE_X1);
        ChEnable(DMA_TRIGACT_BEAT, DMA_TRIGSRC_DIS);
        SetSwTrigger();
    }
}
