/*************************************************************************
 * dac.cpp
 *
 * Created: 3.2.2019 16:26:44
 * Revised: 4.4.2019
 * Author: uidm2956
 * BOARD:
 *
 * ABOUT:
 *
 *************************************************************************/

#include "dac.h"

namespace Core::Drivers
{
    DACONV::DACONV(::Dac* pDac, uint8_t unGeneratorNum)
    {
        m_pDac = pDac;
        GCLK->PCHCTRL[DAC_GCLK_ID].reg = unGeneratorNum|GCLK_PCHCTRL_CHEN;
        MCLK->APBCMASK.bit.DAC_ = true;        
    }

    void DACONV::Init(uint8_t unRefSel, float fRefVoltage)
    {
        m_fRefVoltage = fRefVoltage;
        
        m_pDac->CTRLA.bit.SWRST = true;
        while(m_pDac->SYNCBUSY.bit.SWRST);        
        m_pDac->CTRLB.bit.REFSEL = unRefSel;
        OutputEnable();
        Enable();
    }
}
