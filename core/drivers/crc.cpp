/*************************************************************************
 * crc.cpp
 *
 * Created: 18.06.2019 14:26:25
 * Revised:
 * Author: uidm2956
 * BOARD:
 *
 * ABOUT:
 *
 *************************************************************************/

#include "crc.h"

uint16_t Core::Drivers::CRC::unCRC16(uint8_t* pData, uint16_t unLength)
{
    REG_DMAC_CRCCHKSUM = 0xFFFF;
    REG_DMAC_CRCCTRL = DMAC_CRCCTRL_CRCSRC_IO|DMAC_CRCCTRL_CRCPOLY_CRC16|DMAC_CRCCTRL_CRCBEATSIZE_BYTE;
    DMAC->CTRL.bit.CRCENABLE = 1;
    for (uint16_t i=0; i<unLength; i++) {REG_DMAC_CRCDATAIN = pData[i];}
    DMAC->CRCSTATUS.bit.CRCBUSY = 1;
    DMAC->CTRL.bit.CRCENABLE = 0;
    return REG_DMAC_CRCCHKSUM;
}

uint16_t Core::Drivers::CRC::unCRC16(uint16_t* pData, uint16_t unLength)
{
    REG_DMAC_CRCCHKSUM = 0xFFFF;
    REG_DMAC_CRCCTRL = DMAC_CRCCTRL_CRCSRC_IO|DMAC_CRCCTRL_CRCPOLY_CRC16|DMAC_CRCCTRL_CRCBEATSIZE_HWORD;
    DMAC->CTRL.bit.CRCENABLE = 1;
    for (uint16_t i=0; i<unLength; i++) {REG_DMAC_CRCDATAIN = pData[i];}
    DMAC->CRCSTATUS.bit.CRCBUSY = 1;
    DMAC->CTRL.bit.CRCENABLE = 0;
    return REG_DMAC_CRCCHKSUM;
}

uint16_t Core::Drivers::CRC::unCRC16(uint32_t* pData, uint16_t unLength)
{
    REG_DMAC_CRCCHKSUM = 0xFFFF;
    REG_DMAC_CRCCTRL = DMAC_CRCCTRL_CRCSRC_IO|DMAC_CRCCTRL_CRCPOLY_CRC16|DMAC_CRCCTRL_CRCBEATSIZE_WORD;
    DMAC->CTRL.bit.CRCENABLE = 1;
    for (uint16_t i=0; i<unLength; i++) {REG_DMAC_CRCDATAIN = pData[i];}
    DMAC->CRCSTATUS.bit.CRCBUSY = 1;
    DMAC->CTRL.bit.CRCENABLE = 0;
    return REG_DMAC_CRCCHKSUM;
}

uint32_t Core::Drivers::CRC::unCRC32(uint8_t* pData, uint16_t unLength)
{
    REG_DMAC_CRCCHKSUM = 0xFFFFFFFF;
    REG_DMAC_CRCCTRL = DMAC_CRCCTRL_CRCSRC_IO|DMAC_CRCCTRL_CRCPOLY_CRC32|DMAC_CRCCTRL_CRCBEATSIZE_BYTE;
    DMAC->CTRL.bit.CRCENABLE = 1;
    for (uint16_t i=0; i<unLength; i++) {REG_DMAC_CRCDATAIN = pData[i];}
    DMAC->CRCSTATUS.bit.CRCBUSY = 1;
    DMAC->CTRL.bit.CRCENABLE = 0;
    return REG_DMAC_CRCCHKSUM;
}

uint32_t Core::Drivers::CRC::unCRC32(uint16_t* pData, uint16_t unLength)
{
    REG_DMAC_CRCCHKSUM = 0xFFFFFFFF;
    REG_DMAC_CRCCTRL = DMAC_CRCCTRL_CRCSRC_IO|DMAC_CRCCTRL_CRCPOLY_CRC32|DMAC_CRCCTRL_CRCBEATSIZE_HWORD;
    DMAC->CTRL.bit.CRCENABLE = 1;
    for (uint16_t i=0; i<unLength; i++) {REG_DMAC_CRCDATAIN = pData[i];}
    DMAC->CRCSTATUS.bit.CRCBUSY = 1;
    DMAC->CTRL.bit.CRCENABLE = 0;
    return REG_DMAC_CRCCHKSUM;
}

uint32_t Core::Drivers::CRC::unCRC32(uint32_t* pData, uint16_t unLength)
{
    REG_DMAC_CRCCHKSUM = 0xFFFFFFFF;
    REG_DMAC_CRCCTRL = DMAC_CRCCTRL_CRCSRC_IO|DMAC_CRCCTRL_CRCPOLY_CRC32|DMAC_CRCCTRL_CRCBEATSIZE_WORD;
    DMAC->CTRL.bit.CRCENABLE = 1;
    for (uint16_t i=0; i<unLength; i++) {REG_DMAC_CRCDATAIN = pData[i];}
    DMAC->CRCSTATUS.bit.CRCBUSY = 1;
    DMAC->CTRL.bit.CRCENABLE = 0;
    return REG_DMAC_CRCCHKSUM;
}
