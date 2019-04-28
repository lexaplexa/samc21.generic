/*****************************************************************************
 * pwm.cpp
 *
 * Created: 30.12.2015 21:50:22
 * Revised: 4.4.2019
 * Author: uidm2956
 * BOARD:
 * ABOUT:
 *
 *****************************************************************************/

#include "pwm.h"

namespace Core::Drivers
{
    PWM::PWM(Tc *pTimerCounter, uint8_t unGeneratorNum, uint32_t unPwmFreq, uint32_t unFgen, bool bInvert)
    {
        m_pTc = pTimerCounter;
        
        if (m_pTc == TC0)
        {
            GCLK->PCHCTRL[TC0_GCLK_ID].reg = unGeneratorNum|GCLK_PCHCTRL_CHEN;
            MCLK->APBCMASK.bit.TC0_ = true;
        }
        else if (m_pTc == TC1)
        {
            GCLK->PCHCTRL[TC1_GCLK_ID].reg = unGeneratorNum|GCLK_PCHCTRL_CHEN;
            MCLK->APBCMASK.bit.TC1_ = true;
        }
        else if (m_pTc == TC2)
        {
            GCLK->PCHCTRL[TC2_GCLK_ID].reg = unGeneratorNum|GCLK_PCHCTRL_CHEN;
            MCLK->APBCMASK.bit.TC2_ = true;
        }
        else if (m_pTc == TC3)
        {
            GCLK->PCHCTRL[TC3_GCLK_ID].reg = unGeneratorNum|GCLK_PCHCTRL_CHEN;
            MCLK->APBCMASK.bit.TC3_ = true;
        }
        else if (m_pTc == TC4)
        {
            GCLK->PCHCTRL[TC4_GCLK_ID].reg = unGeneratorNum|GCLK_PCHCTRL_CHEN;
            MCLK->APBCMASK.bit.TC4_ = true;
        }
        
        /* SW reset */
        m_pTc->COUNT16.CTRLA.bit.SWRST = 1;
        while(pTimerCounter->COUNT16.SYNCBUSY.reg);
        
        /* Set registers */
        m_pTc->COUNT16.CC[0].reg = unFgen/unPwmFreq;        /* Top value (period in PWM mode) */
        m_pTc->COUNT16.CC[1].reg = 0;                       /* Match value (in PWM mode) */
        m_pTc->COUNT16.DRVCTRL.reg = bInvert<<TC_DRVCTRL_INVEN1_Pos;
        m_pTc->COUNT16.WAVE.reg = TC_WAVE_WAVEGEN_MPWM;
        m_pTc->COUNT16.CTRLA.reg = TC_CTRLA_MODE_COUNT16|TC_CTRLA_ENABLE;
        while(m_pTc->COUNT16.SYNCBUSY.reg);
    }
    
    void PWM::SetWidth(int8_t nPercent)
    {
        m_nPercent = nPercent;
        if (m_nPercent >= 100) 
        {
            m_nPercent = 100;
            m_pTc->COUNT16.CCBUF[1].reg = m_pTc->COUNT16.CC[0].reg+1;
        }
        else 
        {
            m_pTc->COUNT16.CCBUF[1].reg = m_pTc->COUNT16.CC[0].reg*m_nPercent/100;
        }
        m_pTc->COUNT16.CTRLBSET.reg = TC_CTRLBSET_CMD_UPDATE;
    }
    
    void PWM::SetFreq(uint32_t unPwmFreq, uint32_t unFgen)
    {
        m_pTc->COUNT16.CC[0].reg = unFgen/unPwmFreq;
        m_pTc->COUNT16.CTRLBSET.reg = TC_CTRLBSET_CMD_UPDATE;
    }
}
