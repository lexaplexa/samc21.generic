/*****************************************************************************
 * eic.cpp
 *
 * Created: 19.7.2017 12:48:38
 * Revised: 4.4.2019
 * Author: uidm2956
 * BOARD: 
 * ABOUT: External Interrupt Controller
 *
 *****************************************************************************/

#include "eic.h"

namespace Core::Drivers
{
    
    void EXTINT::Enable()
    {
        MCLK->APBAMASK.bit.EIC_ = true;
        EIC->CTRLA.bit.ENABLE = true;
        while(EIC->SYNCBUSY.bit.ENABLE);
    }

    void EXTINT::Enable(uint8_t unGenNum)
    {
        GCLK->PCHCTRL[EIC_GCLK_ID].bit.GEN = unGenNum;
        GCLK->PCHCTRL[EIC_GCLK_ID].bit.CHEN = true;
        MCLK->APBAMASK.bit.EIC_ = true;
        EIC->CTRLA.bit.ENABLE = true;
        while(EIC->SYNCBUSY.bit.ENABLE);
    }

    void EXTINT::Disable()
    {
        EIC->CTRLA.bit.ENABLE = false;
        while(EIC->SYNCBUSY.bit.ENABLE);
        MCLK->APBAMASK.bit.EIC_ = false;
    }

    void EXTINT::SetExtInt(uint8_t unIntNum, EIC_SENSE_enum eSense)
    {
        EIC->CTRLA.bit.ENABLE = false;
        while(EIC->SYNCBUSY.bit.ENABLE);
        EIC->INTENSET.reg = 1<<unIntNum;
        EIC->CONFIG[unIntNum/8].reg &= ~(EIC_CONFIG_SENSE0_Msk<<(unIntNum%8*4));
        EIC->CONFIG[unIntNum/8].reg |= eSense<<(unIntNum%8*4);
        EIC->CTRLA.bit.ENABLE = true;
        while(EIC->SYNCBUSY.bit.ENABLE);
    }

    void EXTINT::ClearExtInt(uint8_t unIntNum)
    {
        EIC->CTRLA.bit.ENABLE = false;
        while(EIC->SYNCBUSY.bit.ENABLE);
        EIC->INTENCLR.reg = 1<<unIntNum;
        EIC->CONFIG[unIntNum/8].reg &= ~(EIC_CONFIG_SENSE0_Msk<<(unIntNum%8*4));
        EIC->CTRLA.bit.ENABLE = true;
        while(EIC->SYNCBUSY.bit.ENABLE);
    }
}