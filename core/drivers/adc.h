/*************************************************************************
 * adc.h
 *
 * Created: 3.2.2019 15:51:28
 * Revised: 4.4.2019
 * Author: uidm2956
 * BOARD:
 *
 * ABOUT:
 *
 *************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include <sam.h>

namespace Core
{
    namespace Drivers
    {
        enum ADC_REFERENCE_enum
        {
            ADC_REFERENCE_INTREF,
            ADC_REFERENCE_INTVCC0,
            ADC_REFERENCE_INTVCC1,
            ADC_REFERENCE_VREFA,
            ADC_REFERENCE_DAC,
            ADC_REFERENCE_INTVCC2,
        };

        enum ADC_PRESCALER_enum
        {
            ADC_PRESCALER_DIV2,
            ADC_PRESCALER_DIV4,
            ADC_PRESCALER_DIV8,
            ADC_PRESCALER_DIV16,
            ADC_PRESCALER_DIV32,
            ADC_PRESCALER_DIV64,
            ADC_PRESCALER_DIV128,
            ADC_PRESCALER_DIV256,
        };

        enum ADC_RESOLUTION_enum
        {
            ADC_RESOLUTION_12BIT,
            ADC_RESOLUTION_16BIT,
            ADC_RESOLUTION_10BIT,
            ADC_RESOLUTION_8BIT,
        };

        enum ADC_MUXPOS_enum
        {
            ADC_MUXPOS_AIN0,
            ADC_MUXPOS_AIN1,
            ADC_MUXPOS_AIN2,
            ADC_MUXPOS_AIN3,
            ADC_MUXPOS_AIN4,
            ADC_MUXPOS_AIN5,
            ADC_MUXPOS_AIN6,
            ADC_MUXPOS_AIN7,
            ADC_MUXPOS_AIN8,
            ADC_MUXPOS_AIN9,
            ADC_MUXPOS_AIN10,
            ADC_MUXPOS_AIN11,
            ADC_MUXPOS_BANDGAP = 0x19,
            ADC_MUXPOS_SCALEDCOREVCC,
            ADC_MUXPOS_SCALEDIOVCC,
            ADC_MUXPOS_DAC,
        };

        enum ADC_MUXNEG_enum
        {
            ADC_MUXNEG_AIN0,
            ADC_MUXNEG_AIN1,
            ADC_MUXNEG_AIN2,
            ADC_MUXNEG_AIN3,
            ADC_MUXNEG_AIN4,
            ADC_MUXNEG_AIN5,
            ADC_MUXNEG_GND = 0x18,
        };

        class ADC
        {
            protected:
                ::Adc* m_pAdc;
                float m_fRefVoltage;
                    
            public:
                /**
                    * \brief   Analog to digital converter constructor
                    * 
                    * \param pAdc
                    * \param unGeneratorNum
                    * 
                    * \return 
                    */
                ADC(::Adc* pAdc, uint8_t unGeneratorNum);
                    
                /**
                    * \brief   Initialize ADC
                    * 
                    * \param ePrescale     - prescaler
                    * \param eResolution   - ADC resolution
                    * \param eReference    - reference type
                    * \param fRefVoltage   - reference voltage
                    * 
                    * \return void
                    */
                virtual void Init(ADC_PRESCALER_enum ePrescale, ADC_RESOLUTION_enum eResolution, ADC_REFERENCE_enum eReference, float fRefVoltage);
                    
                /**
                    * \brief   Convert voltage in positive pin
                    * 
                    * \param ePos          - Positive position
                    * 
                    * \return uint16_t     - result
                    */
                virtual uint16_t Convert(ADC_MUXPOS_enum ePos);
        };
    }
}
#endif /* ADC_H_ */