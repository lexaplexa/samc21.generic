/*****************************************************************************
 * genclock.h
 *
 * Created: 22.9.2015 11:21:04
 * Revised: 4.4.2019
 * Author: uidm2956
 * BOARD: 
 * ABOUT:
 *
 *****************************************************************************/


#ifndef GENCLOCK_H_
#define GENCLOCK_H_

#include "sam.h"

#define genclk_init(num,source,div)     REG_GCLK_GENCTRL##num = source|GCLK_GENCTRL_DIV(div)|GCLK_GENCTRL_GENEN
#define genclk_waitsync()               while (REG_GCLK_SYNCBUSY)


/************************************************************************/
/* CLASS                                                                */
/************************************************************************/
namespace Core
{
	namespace Drivers
    {
        class GENCLOCK
        {
            private:
                uint32_t m_unFrequency;
                uint8_t m_unGenNum;
                    
            public:            
                /**
                 * \brief   Set generator clock using DPLL
                 * 
                 * \param unGenNum          - generator number (0-8)
                 * \param unGenFreq         - generator frequency
                 * \param unDiv             - divide generator frequency
                 * \param unRefClk          - DPLL reference clock (0 - XOSC32K, 1 - XOSC, 2 - GCLK)
                 * \param unMultiplication  - multiplication factor
                 * 
                 * \return 
                 */
                GENCLOCK(uint8_t unGenNum, uint32_t unGenFreq, uint8_t unDiv, uint8_t unRefClk, uint16_t unMultiplication)
                {
                    if (unGenNum > 8 || unRefClk > 2) {return;}
                    
                    m_unFrequency = unGenFreq;	
                    m_unGenNum = unGenNum;
                        
                    REG_NVMCTRL_CTRLB |= NVMCTRL_CTRLB_RWS(2);		/* Read wait state must be >1 for frequencies >24MHz */
                        
                    /* Enable RTC oscillator */
                    if (unRefClk == 0)
                    {
                        REG_OSC32KCTRL_XOSC32K = OSC32KCTRL_XOSC32K_XTALEN|OSC32KCTRL_XOSC32K_EN32K|OSC32KCTRL_XOSC32K_ENABLE;
                        while (!OSC32KCTRL->STATUS.bit.XOSC32KRDY);
                    }
                    /* Enable external oscillator */
                    else if (unRefClk == 1)
                    {
                        if      (unGenFreq <= 2000000)  {REG_OSCCTRL_XOSCCTRL = OSCCTRL_XOSCCTRL_GAIN(0)|OSCCTRL_XOSCCTRL_XTALEN|OSCCTRL_XOSCCTRL_ENABLE;}
                        else if (unGenFreq <= 4000000)  {REG_OSCCTRL_XOSCCTRL = OSCCTRL_XOSCCTRL_GAIN(1)|OSCCTRL_XOSCCTRL_XTALEN|OSCCTRL_XOSCCTRL_ENABLE;}
                        else if (unGenFreq <= 8000000)  {REG_OSCCTRL_XOSCCTRL = OSCCTRL_XOSCCTRL_GAIN(2)|OSCCTRL_XOSCCTRL_XTALEN|OSCCTRL_XOSCCTRL_ENABLE;}
                        else if (unGenFreq <= 16000000) {REG_OSCCTRL_XOSCCTRL = OSCCTRL_XOSCCTRL_GAIN(3)|OSCCTRL_XOSCCTRL_XTALEN|OSCCTRL_XOSCCTRL_ENABLE;}
                        else                            {REG_OSCCTRL_XOSCCTRL = OSCCTRL_XOSCCTRL_GAIN(4)|OSCCTRL_XOSCCTRL_XTALEN|OSCCTRL_XOSCCTRL_ENABLE;}
                        while(!OSCCTRL->STATUS.bit.XOSCRDY);
                        unMultiplication *= 2;      /* Multiplication must be 2x higher because XOSC is divided by 2 (DPLLCTRLB.DIV = 0) */
                    }
                        
                    /* Enable DPLL */
                    REG_OSCCTRL_DPLLCTRLB = OSCCTRL_DPLLCTRLB_REFCLK(unRefClk);
                    REG_OSCCTRL_DPLLRATIO = OSCCTRL_DPLLRATIO_LDR(unMultiplication-1);
                    REG_OSCCTRL_DPLLPRESC = 0;
                    REG_OSCCTRL_DPLLCTRLA = OSCCTRL_DPLLCTRLA_ENABLE;
                    while (OSCCTRL->DPLLSYNCBUSY.bit.ENABLE);
                        
                    /* Set Genclock */
                    GCLK->GENCTRL[m_unGenNum].reg = GCLK_GENCTRL_SRC_DPLL96M|GCLK_GENCTRL_DIV(unDiv)|GCLK_GENCTRL_GENEN;
                    genclk_waitsync();	
                }
                    
                    
                /**
                 * \brief   Set generator clock
                 * 
                 * \param unGenNum          - generator number (0-8)
                 * \param unGenFreq         - generator frequency
                 * \param unDiv             - divide generator frequency
                 * \param unSourceClk       - generator source clock (0->XOSC, 1->GCLKIN, 2->GCLKGEN1, 3->OSCULP32K, 4->OSC32K, 5->XOSC32K, 6->OSC48M, 7->DPPL96M)
                 * 
                 * \return 
                 */
                GENCLOCK(uint8_t unGenNum, uint32_t unGenFreq, uint8_t unDiv, uint8_t unSourceClk)
                {
                    if (unGenNum > 8 || unSourceClk > 7) {return;}
                        
                    m_unFrequency = unGenFreq;
                    m_unGenNum = unGenNum;
                        
                    REG_NVMCTRL_CTRLB |= NVMCTRL_CTRLB_RWS(2);		/* Read wait state must be >1 for frequencies >24MHz */
                        
                    if (unSourceClk == GCLK_GENCTRL_SRC_XOSC)
                    {
                        if      (unGenFreq <= 2000000)  {REG_OSCCTRL_XOSCCTRL = OSCCTRL_XOSCCTRL_GAIN(0)|OSCCTRL_XOSCCTRL_XTALEN|OSCCTRL_XOSCCTRL_ENABLE;}
                        else if (unGenFreq <= 4000000)  {REG_OSCCTRL_XOSCCTRL = OSCCTRL_XOSCCTRL_GAIN(1)|OSCCTRL_XOSCCTRL_XTALEN|OSCCTRL_XOSCCTRL_ENABLE;}
                        else if (unGenFreq <= 8000000)  {REG_OSCCTRL_XOSCCTRL = OSCCTRL_XOSCCTRL_GAIN(2)|OSCCTRL_XOSCCTRL_XTALEN|OSCCTRL_XOSCCTRL_ENABLE;}
                        else if (unGenFreq <= 16000000) {REG_OSCCTRL_XOSCCTRL = OSCCTRL_XOSCCTRL_GAIN(3)|OSCCTRL_XOSCCTRL_XTALEN|OSCCTRL_XOSCCTRL_ENABLE;}
                        else                            {REG_OSCCTRL_XOSCCTRL = OSCCTRL_XOSCCTRL_GAIN(4)|OSCCTRL_XOSCCTRL_XTALEN|OSCCTRL_XOSCCTRL_ENABLE;}
                        while(!OSCCTRL->STATUS.bit.XOSCRDY);
                    }
                    else if (unSourceClk == GCLK_GENCTRL_SRC_XOSC32K)
                    {
                        REG_OSC32KCTRL_XOSC32K = OSC32KCTRL_XOSC32K_XTALEN|OSC32KCTRL_XOSC32K_EN32K|OSC32KCTRL_XOSC32K_ENABLE;
                        while (!OSC32KCTRL->STATUS.bit.XOSC32KRDY);
                    }
                    else if (unSourceClk == GCLK_GENCTRL_SRC_OSC48M)
                    {
                        /* to be done */
                    }
                        
                    /* Set Genclock */
                    GCLK->GENCTRL[m_unGenNum].reg = GCLK_GENCTRL_SRC(unSourceClk)|GCLK_GENCTRL_DIV(unDiv)|GCLK_GENCTRL_GENEN;
                    genclk_waitsync();
                }
                    
                    
                /**
                 * \brief   Get generator number
                 * 
                 * 
                 * \return uint8_t
                 */
                uint8_t GenNum()
                {
                    return m_unGenNum;
                }
                    
                    
                /**
                 * \brief   Get actual frequency
                 * 
                 * 
                 * \return uint32_t
                 */
                uint32_t GenFreq()
                {
                    return (m_unFrequency/GCLK->GENCTRL[m_unGenNum].bit.DIV);
                }
        };
    }
}


#endif /* GENCLOCK_H_ */