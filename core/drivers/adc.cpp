/*************************************************************************
 * adc.cpp
 *
 * Created: 04.02.2019 16:19:42
 * Revised: 4.4.2019
 * Author: uidm2956
 * BOARD:
 *
 * ABOUT:
 *
 *************************************************************************/

#include "adc.h"

namespace Core::Drivers
{
    ADC::ADC(::Adc* pAdc, uint8_t unGeneratorNum)
    {
        m_pAdc = pAdc;
        
        if (m_pAdc == ADC0)
        {
            GCLK->PCHCTRL[ADC0_GCLK_ID].reg = unGeneratorNum|GCLK_PCHCTRL_CHEN;
            MCLK->APBCMASK.bit.ADC0_ = true;			
        }
        else if (m_pAdc == ADC1)
        {
            GCLK->PCHCTRL[ADC1_GCLK_ID].reg = unGeneratorNum|GCLK_PCHCTRL_CHEN;
            MCLK->APBCMASK.bit.ADC1_ = true;
        }
    }

    void ADC::Init(ADC_PRESCALER_enum ePrescale, ADC_RESOLUTION_enum eResolution, ADC_REFERENCE_enum eReference, float fRefVoltage)
    {
        m_fRefVoltage = fRefVoltage;

        m_pAdc->CTRLA.bit.SWRST = true;
        while(m_pAdc->SYNCBUSY.bit.SWRST);
        
        m_pAdc->CTRLB.bit.PRESCALER = ePrescale;
        m_pAdc->REFCTRL.bit.REFSEL = eReference;
        m_pAdc->CTRLC.bit.RESSEL = eResolution;

        m_pAdc->CTRLA.bit.ENABLE = true;
        while(m_pAdc->SYNCBUSY.bit.ENABLE);
    }

    uint16_t ADC::Convert(ADC_MUXPOS_enum ePos)
    {
        m_pAdc->INTFLAG.bit.RESRDY = 1;     /* Clear Flag before conversion */
        m_pAdc->INPUTCTRL.bit.MUXPOS = ePos;
        m_pAdc->SWTRIG.bit.START = true;
        while(m_pAdc->INTFLAG.bit.RESRDY);
    }
}
