/*****************************************************************************
 * sercom.cpp
 *
 * Created: 23.9.2015 17:18:53
 * Revised: 4.4.2019
 * Author: uidm2956
 * BOARD: 
 * ABOUT:
 *
 *****************************************************************************/

#include "sercom.h"

namespace Core::Drivers
{
    /************************************************************************/
    /* SERCOM                                                               */
    /************************************************************************/
    SERCOM::SERCOM(::Sercom* pSercom, uint8_t unGeneratorNum)
    {
        m_pSercom = pSercom;
        
        if (m_pSercom == SERCOM0)
        {
            GCLK->PCHCTRL[SERCOM0_GCLK_ID_CORE].reg = unGeneratorNum|GCLK_PCHCTRL_CHEN;
            MCLK->APBCMASK.bit.SERCOM0_ = true;
        }
        else if (m_pSercom == SERCOM1)
        {
            GCLK->PCHCTRL[SERCOM1_GCLK_ID_CORE].reg = unGeneratorNum|GCLK_PCHCTRL_CHEN;
            MCLK->APBCMASK.bit.SERCOM1_ = true;
        }
        else if (m_pSercom == SERCOM2)
        {
            GCLK->PCHCTRL[SERCOM2_GCLK_ID_CORE].reg = unGeneratorNum|GCLK_PCHCTRL_CHEN;
            MCLK->APBCMASK.bit.SERCOM2_ = true;
        }
        else if (m_pSercom == SERCOM3)
        {
            GCLK->PCHCTRL[SERCOM3_GCLK_ID_CORE].reg = unGeneratorNum|GCLK_PCHCTRL_CHEN;
            MCLK->APBCMASK.bit.SERCOM3_ = true;
        }
        else if (m_pSercom == SERCOM4)
        {
            GCLK->PCHCTRL[SERCOM4_GCLK_ID_CORE].reg = unGeneratorNum|GCLK_PCHCTRL_CHEN;
            MCLK->APBCMASK.bit.SERCOM4_ = true;
        }
        else if (m_pSercom == SERCOM5)
        {
            GCLK->PCHCTRL[SERCOM5_GCLK_ID_CORE].reg = unGeneratorNum|GCLK_PCHCTRL_CHEN;
            MCLK->APBCMASK.bit.SERCOM5_ = true;
        }
    }
    
    /************************************************************************/
    /* USART                                                                */
    /************************************************************************/
    void USART::Init(uint8_t unPadIn, uint8_t unPadOut, uint32_t unFgen, uint32_t unBaud)
    {
        m_pSercom->USART.CTRLA.bit.SWRST = true;
        while (m_pSercom->USART.SYNCBUSY.bit.SWRST);
        
        m_pSercom->USART.CTRLA.bit.MODE = 1;
        m_pSercom->USART.CTRLA.bit.FORM = 0;
        m_pSercom->USART.CTRLA.bit.DORD = 1;
        m_pSercom->USART.CTRLA.bit.RXPO = unPadIn;
        m_pSercom->USART.CTRLA.bit.TXPO = unPadOut;
        m_pSercom->USART.BAUD.reg = 65536 - (65536*16*(unBaud/1000)/(unFgen/1000));
        m_pSercom->USART.CTRLB.bit.RXEN = true;
        m_pSercom->USART.CTRLB.bit.TXEN = true;
        m_pSercom->USART.INTENSET.reg = SERCOM_USART_INTFLAG_RXC;
        
        m_pSercom->USART.CTRLA.bit.ENABLE = true;
        while (m_pSercom->USART.SYNCBUSY.bit.ENABLE);
    }

    void USART::Send(char* pString)
    {
        for (pString; *pString != '\0'; pString++)
        {
            m_pSercom->USART.DATA.reg = *pString;
            while (m_pSercom->USART.INTFLAG.bit.TXC);
            m_pSercom->USART.INTFLAG.bit.TXC = 1;       /* Clear flag */
        }
    }

    void USART::Send(uint8_t* pData, uint16_t unLength)
    {
        for (uint16_t i=0; i<unLength; i++)
        {
            m_pSercom->USART.DATA.reg = *pData++;
            while (m_pSercom->USART.INTFLAG.bit.TXC);
            m_pSercom->USART.INTFLAG.bit.TXC = 1;       /* Clear flag */
        }
    }
    
    /************************************************************************/
    /* SPI                                                                  */
    /************************************************************************/
    void SPI::Init(uint8_t unPadIn, uint8_t unPadOut)
    {
        m_pSercom->SPI.CTRLA.bit.SWRST = true;
        while (m_pSercom->SPI.SYNCBUSY.bit.SWRST);
        
        m_pSercom->SPI.CTRLA.bit.MODE = 2;
        m_pSercom->SPI.CTRLA.bit.DOPO = unPadOut;
        m_pSercom->SPI.CTRLA.bit.DIPO = unPadIn;
        m_pSercom->SPI.INTENSET.reg = SERCOM_SPI_INTENSET_SSL|SERCOM_SPI_INTENSET_RXC|SERCOM_SPI_INTENSET_TXC;
        m_pSercom->SPI.CTRLB.bit.RXEN = true;
        m_pSercom->SPI.CTRLB.bit.SSDE = true;
        m_pSercom->SPI.INTFLAG.reg = 0xFF;
        m_pSercom->SPI.CTRLB.bit.PLOADEN = true;
        
        m_pSercom->SPI.CTRLA.bit.ENABLE = true;
        while (m_pSercom->SPI.SYNCBUSY.bit.ENABLE);
    }

    void SPI::Init(uint8_t unPadIn, uint8_t unPadOut, uint32_t unFgen, uint32_t unBaud)
    {
        m_pSercom->SPI.CTRLA.bit.SWRST = true;
        while (m_pSercom->SPI.SYNCBUSY.bit.SWRST);
        
        m_pSercom->SPI.CTRLA.bit.MODE = 3;
        m_pSercom->SPI.CTRLA.bit.DOPO = unPadOut;
        m_pSercom->SPI.CTRLA.bit.DIPO = unPadIn;
        m_pSercom->SPI.CTRLB.bit.RXEN = true;
        m_pSercom->SPI.BAUD.reg = (unFgen/2/unBaud)-1;
        m_pSercom->SPI.INTFLAG.reg = 0xFF;
        
        m_pSercom->SPI.CTRLA.bit.ENABLE = true;
        while (m_pSercom->SPI.SYNCBUSY.bit.ENABLE);
    }

    void SPI::Read(uint8_t* pData, uint16_t unLength)
    {
        for (uint16_t i=0; i<unLength; i++) {*pData++ = Read();}
    }

    void SPI::Send(uint8_t* pData, uint16_t unLength)
    {
        for (uint16_t i=0; i<unLength; i++) {Send(*pData++);}
    }
}