/*****************************************************************************
 * pwm.h
 *
 * Created: 30.12.2015 21:40:48
 * Revised: 4.4.2012
 * Author: uidm2956
 * BOARD: 
 * ABOUT:
 *
 *****************************************************************************/


#ifndef PWM_H_
#define PWM_H_

#include <sam.h>

#define pwm_sstart(tc)              tc->COUNT16.CTRLBSET.reg = TC_CTRLBSET_CMD_RETRIGGER
#define pwm_sstop(tc)               tc->COUNT16.CTRLBSET.reg = TC_CTRLBSET_CMD_STOP
#define pwm_ssetfreq(tc,fgen,fpwm)  tc->COUNT16.CC[0].reg = fgen/fpwm; tc->COUNT16.CTRLBSET.reg = TC_CTRLBSET_CMD_UPDATE
#define pwm_ssetwidth(tc,percent)   tc->COUNT16.CCBUF[1].reg = tc->COUNT16.CC[0].reg*percent/100; tc->COUNT16.CTRLBSET.reg = TC_CTRLBSET_CMD_UPDATE


namespace Core
{
    namespace Drivers
    {
        /************************************************************************/
        /* CLASS                                                                */
        /************************************************************************/
        class PWM
        {
            private:
                Tc* m_pTc;
                int8_t m_nPercent;
                
            public:
                /**
                 * \brief   PWM constructor
                 * 
                 * \param pTimerCounter     - pointer to Timer/Counter module
                 * \param unGeneratorNum    - number of generator clock
                 * \param unPwmFreq         - PWM frequency (1bit = 1Hz)
                 * \param unFgen            - Generator frequency (1bit = 1Hz)
                 * \param bInvert           - output signal inverted
                 * 
                 * \return 
                 */
                PWM(Tc *pTimerCounter, uint8_t unGeneratorNum, uint32_t unPwmFreq, uint32_t unFgen, bool bInvert);
                
                /**
                 * \brief   Start PWM module
                 *
                 * \return void
                 */
                void Start() {m_pTc->COUNT16.CTRLBSET.reg = TC_CTRLBSET_CMD_RETRIGGER;}
                
                /**
                 * \brief   Stop PWM module
                 *
                 * \return void
                 */
                void Stop() {m_pTc->COUNT16.CTRLBSET.reg = TC_CTRLBSET_CMD_STOP;}
                
                /**
                 * \brief Set PWM ratio 
                 * 
                 * \param nPercent          - PWM ratio 1bit = 1% (0-100%)
                 * 
                 * \return void
                 */
                void SetWidth(int8_t nPercent);
                
                /**
                 * \brief Get actual PWM ratio
                 * 
                 * 
                 * \return int8_t           - PWM ratio 1bit = 1% (0-100%)
                 */
                int8_t GetWidth() {return m_nPercent;}
                
                /**
                 * \brief Set PWM frequency
                 * 
                 * \param unPwmFreq         - frequency of PWM signal (1bit = 1Hz)
                 * \param unFgen            - generator frequency (1bit = 1Hz)
                 * 
                 * \return void
                 */
                void SetFreq(uint32_t unPwmFreq, uint32_t unFgen);
        };
    }
}

#endif /* PWM_H_ */