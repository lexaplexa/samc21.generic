/*****************************************************************************
 * realtime.h
 *
 * Created: 07.02.2019 15:17:33
 * Revised: 
 * Author: uidm2956
 * BOARD:
 * ABOUT:
 *
 *****************************************************************************/


#ifndef RTC_H_
#define RTC_H_

namespace Core
{
    namespace Drivers
    {
        enum RTC_SOURCE_enum {
            RTC_SOURCE_ULP1K,
            RTC_SOURCE_ULP32K,
            RTC_SOURCE_OSC1K,
            RTC_SOURCE_OSC32K,
            RTC_SOURCE_XOSC1K,
            RTC_SOURCE_XOSC32K,
        };

        enum RTC_MODE_enum {
            RTC_MODE_Count32Bit,
            RTC_MODE_Count16Bit,
            RTC_MODE_Calendar,
        };

        enum RTC_PRESCALER_enum {
            RTC_PRESCALER_OFF,
            RTC_PRESCALER_DIV1,
            RTC_PRESCALER_DIV2,
            RTC_PRESCALER_DIV4,
            RTC_PRESCALER_DIV8,
            RTC_PRESCALER_DIV16,
            RTC_PRESCALER_DIV32,
            RTC_PRESCALER_DIV64,
            RTC_PRESCALER_DIV128,
            RTC_PRESCALER_DIV256,
            RTC_PRESCALER_DIV512,
            RTC_PRESCALER_DIV1024,
        };
        
        /************************************************************************/
        /* RTC                                                                  */
        /************************************************************************/
        class REALTIME
        {
            protected:
            
            public:
                /**
                 * \brief   Real time constructor
                 * 
                 * 
                 * \return 
                 */
                REALTIME();

                virtual void Init(RTC_PRESCALER_enum ePrescaler, RTC_SOURCE_enum eRtcSource) = 0;
        };

        /************************************************************************/
        /* RTC Counter 32bit                                                    */
        /************************************************************************/
        class RTCMODE32BIT: public REALTIME
        {
            private:
            
            public:
                /**
                 * \brief   RTC mode 32bit counter constructor
                 * 
                 * 
                 * \return 
                 */
                RTCMODE32BIT(): REALTIME() {};

                void Init(RTC_PRESCALER_enum ePrescaler, RTC_SOURCE_enum eRtcSource);

        };

        /************************************************************************/
        /* RTC Counter 16bit                                                    */
        /************************************************************************/
        class RTCMODE16BIT: public REALTIME
        {
            private:

            public:
                /**
                 * \brief   RTC mode 16bit counter constructor
                 * 
                 * 
                 * \return 
                 */
                RTCMODE16BIT(): REALTIME() {};

                void Init(RTC_PRESCALER_enum ePrescaler, RTC_SOURCE_enum eRtcSource);
        };

        /************************************************************************/
        /* RTC Calendar                                                         */
        /************************************************************************/
        class RTCMODECALENDAR: public REALTIME
        {
            private:
                
            public:
                /**
                 * \brief   RTC mode calendar constructor
                 * 
                 * 
                 * \return 
                 */
                RTCMODECALENDAR(): REALTIME() {};

                void Init(RTC_PRESCALER_enum ePrescaler, RTC_SOURCE_enum eRtcSource);
        };
    }
}



#endif /* RTC_H_ */