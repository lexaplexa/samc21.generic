/*****************************************************************************
 * nvm.cpp
 *
 * Created: 20.02.2019 15:09:43
 * Revised: 4.4.2019
 * Author: uidm2956
 * BOARD:
 * ABOUT:
 *
 *****************************************************************************/

#include "nvm.h"

namespace Core::Drivers
{
    void NVM::WritePage(uint32_t unAddress, uint8_t *pBuffer)
    {
        uint32_t* pFlashAddress = (uint32_t*)(unAddress & 0xFFFFFFC0);

        ExecCommand(NVM_CMD_PageBufferClear);
    
        /* Load data to page buffer */
        for(uint8_t i=0; i<FLASH_PAGE_SIZE; i+=4)
        {
            *(pFlashAddress++) = pBuffer[i]|pBuffer[i+1]<<8|pBuffer[i+2]<<16|pBuffer[i+3]<<24;
        }
    
        ExecCommand(NVM_CMD_WritePage, unAddress);
    }

    void NVM::ReadPage(uint32_t unAddress, uint8_t *pBuffer)
    {
        unAddress &= 0xFFFFFFC0;
        for (uint8_t i=0; i<FLASH_PAGE_SIZE; i++)
        {
            *(pBuffer+i) = *(uint8_t*)(unAddress+i);
        }
    }

    void NVM::EraseRow(uint32_t unAddress)
    {
        ExecCommand(NVM_CMD_EraseRow, unAddress);
    }

    void NVM::WritePageFEE(uint32_t unAddress, uint8_t *pBuffer)
    {
        uint32_t* pFEEAddress = (uint32_t*)(unAddress & 0xFFFFFFC0);

        ExecCommand(NVM_CMD_PageBufferClear);
    
        /* Load data to page buffer */
        for(uint8_t i=0; i<FLASH_PAGE_SIZE; i+=4)
        {
            *(pFEEAddress++) = pBuffer[i]|pBuffer[i+1]<<8|pBuffer[i+2]<<16|pBuffer[i+3]<<24;
        }
    
        ExecCommand(NVM_CMD_RWWEEWritePage, unAddress);
    }

    void NVM::EraseRowFEE(uint32_t unAddress)
    {
        ExecCommand(NVM_CMD_RWWEEEraseRow, unAddress);
    }
}
