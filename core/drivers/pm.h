/*****************************************************************************
 * pm.h
 *
 * Created: 22.7.2019 15:20:18
 * Revised: 
 * Author: uidm2956
 * BOARD:
 * ABOUT:
 *
 *****************************************************************************/


#ifndef PM_H_
#define PM_H_

namespace Core
{
    namespace Drivers
    {
        class POWER
        {
            private:

            public:
                static inline void Sleep() {REG_PM_SLEEPCFG = PM_SLEEPCFG_SLEEPMODE_IDLE2; __WFI();}
                static inline void DeepSleep() {REG_PM_SLEEPCFG = PM_SLEEPCFG_SLEEPMODE_STANDBY; __WFI();};
        };
    }
}



#endif /* PM_H_ */
