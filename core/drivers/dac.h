/*************************************************************************
 * dac.h
 *
 * Created: 19.2.2018 9:38:45
 * Revised: 4.4.2019
 * Author: uidm2956
 * BOARD:
 *
 * ABOUT:
 *
 *************************************************************************/


#ifndef DAC_H_
#define DAC_H_

#include <sam.h>

#define dac_enable()                    DAC->CTRLA.bit.ENABLE = true
#define dac_disable()                   DAC->CTRLA.bit.ENABLE = false
#define dac_set_genclock(gennum)        GCLK->PCHCTRL[DAC_GCLK_ID].reg = gennum|GCLK_PCHCTRL_CHEN; MCLK->APBCMASK.bit.DAC_ = true
#define dac_set_reference(ref_num)      DAC->CTRLB.bit.REFSEL = ref_num
#define dac_output_enable()             DAC->CTRLB.bit.EOEN = true
#define dac_output_disable()            DAC->CTRLB.bit.EOEN = false
#define dac_output(data)                DAC->DATA.reg = data

namespace Core
{
    namespace Drivers
    {
        class DACONV
        {
            protected:
                ::Dac* m_pDac;
                float m_fRefVoltage;
                
            public:
                /**
                * \brief   Digital to analog converter constructor
                *
                * \param pDac
                * \param unGeneratorNum
                *
                * \return
                */
                DACONV(::Dac* pDac, uint8_t unGeneratorNum);
                    
                void Init(uint8_t unRefSel, float fRefVoltage);
                    
                void Enable() {m_pDac->CTRLA.bit.ENABLE = true; while(m_pDac->SYNCBUSY.bit.ENABLE);}
                    
                void Disable() {m_pDac->CTRLA.bit.ENABLE = false; while(m_pDac->SYNCBUSY.bit.ENABLE);}
                    
                void OutputEnable() {m_pDac->CTRLB.bit.EOEN = true;}
                    
                void OutputDisable() {m_pDac->CTRLB.bit.EOEN = false;}
                    
                void SetOutput(uint16_t unDacNum) {m_pDac->DATA.reg = unDacNum;}
            };
    }
}

#endif /* DAC_H_ */