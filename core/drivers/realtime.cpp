/*****************************************************************************
 * realtime.cpp
 *
 * Created: 07.02.2019 15:55:18
 * Revised: 4.4.2019
 * Author: uidm2956
 * BOARD:
 * ABOUT:
 *
 *****************************************************************************/

#include "realtime.h"
#include <sam.h>

namespace Core::Drivers
{
    REALTIME::REALTIME()
    {
        /* Enable 32kHz oscillator */
        REG_OSC32KCTRL_OSC32K = OSC32KCTRL_XOSC32K_XTALEN|OSC32KCTRL_XOSC32K_EN32K|OSC32KCTRL_XOSC32K_ENABLE;
        while (!OSC32KCTRL->STATUS.bit.XOSC32KRDY);

        MCLK->APBAMASK.bit.RTC_ = true;
    }

    void RTCMODE32BIT::Init(RTC_PRESCALER_enum ePrescaler, RTC_SOURCE_enum eRtcSource)
    {
        OSC32KCTRL->RTCCTRL.bit.RTCSEL = eRtcSource;

        RTC->MODE0.CTRLA.bit.SWRST = true;
        while(RTC->MODE0.SYNCBUSY.reg);

        RTC->MODE0.CTRLA.bit.PRESCALER = ePrescaler;
        RTC->MODE0.CTRLA.bit.MODE = RTC_MODE_Count32Bit;
        RTC->MODE0.CTRLA.bit.COUNTSYNC = true;

        RTC->MODE0.CTRLA.bit.ENABLE = true;
        while(RTC->MODE0.SYNCBUSY.reg);
    }

    void RTCMODE16BIT::Init(RTC_PRESCALER_enum ePrescaler, RTC_SOURCE_enum eRtcSource)
    {
        OSC32KCTRL->RTCCTRL.bit.RTCSEL = eRtcSource;

        RTC->MODE1.CTRLA.bit.SWRST = true;
        while(RTC->MODE1.SYNCBUSY.reg);

        RTC->MODE1.CTRLA.bit.PRESCALER = ePrescaler;
        RTC->MODE1.CTRLA.bit.MODE = RTC_MODE_Count16Bit;
        RTC->MODE1.CTRLA.bit.COUNTSYNC = true;

        RTC->MODE1.CTRLA.bit.ENABLE = true;
        while(RTC->MODE1.SYNCBUSY.reg);
    }

    void RTCMODECALENDAR::Init(RTC_PRESCALER_enum ePrescaler, RTC_SOURCE_enum eRtcSource)
    {
        OSC32KCTRL->RTCCTRL.bit.RTCSEL = eRtcSource;

        RTC->MODE2.CTRLA.bit.SWRST = true;
        while(RTC->MODE2.SYNCBUSY.reg);

        RTC->MODE2.CTRLA.bit.PRESCALER = ePrescaler;
        RTC->MODE2.CTRLA.bit.MODE = RTC_MODE_Calendar;

        RTC->MODE2.CTRLA.bit.ENABLE = true;
        while(RTC->MODE2.SYNCBUSY.reg);
    }
}