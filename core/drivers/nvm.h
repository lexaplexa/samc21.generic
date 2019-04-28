/*****************************************************************************
 * nvm.h
 *
 * Created: 20.02.2019 14:23:34
 * Revised: 4.4.2019
 * Author: uidm2956
 * BOARD:
 * ABOUT:
 *
 *****************************************************************************/


#ifndef NVM_H_
#define NVM_H_

#include <sam.h>

namespace Core
{
    namespace Drivers
    {
        /************************************************************************/
        /* ENUMS                                                                */
        /************************************************************************/
        enum NVM_CMD_enum {
            NVM_CMD_EraseRow = 2,
            NVM_CMD_WritePage = 4,
            NVM_CMD_EraseAuxiliaryRow = 5,
            NVM_CMD_WriteAuxiliaryPage = 6,
            NVM_CMD_RWWEEEraseRow = 26,
            NVM_CMD_RWWEEWritePage = 28,
            NVM_CMD_LockRegion = 64,
            NVM_CMD_UnlockRegion = 65,
            NVM_CMD_SetPowerReductionMode = 66,
            NVM_CMD_ClearPowerReductionMode = 67,
            NVM_CMD_PageBufferClear = 68,
            NVM_CMD_SetSecurityBit = 69,
            NVM_CMD_InvalidateCacheLines = 70,
            NVM_CMD_LockDataRegion = 71,
            NVM_CMD_UnlockDataRegion = 72,
        };

        class NVM
        {
            private:
                /**
                 * \brief   Execute command
                 * 
                 * \param eCmd          - command
                 * 
                 * \return void
                 */
                void ExecCommand(NVM_CMD_enum eCmd)
                {
                    NVMCTRL->ADDR.reg = 0;
                    NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMDEX_KEY|eCmd;
                    while (!NVMCTRL->INTFLAG.bit.READY);
                };

                /**
                 * \brief   Execute command
                 * 
                 * \param eCmd          - command
                 * \param unAddress     - address
                 * 
                 * \return void
                 */
                void ExecCommand(NVM_CMD_enum eCmd, uint32_t unAddress)
                {
                    NVMCTRL->ADDR.reg = unAddress/2;
                    NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMDEX_KEY|eCmd;
                    while (!NVMCTRL->INTFLAG.bit.READY);
                };

            public:

                /**
                 * \brief   Write flash page
                 * 
                 * \param unAddress     - address inside page
                 * \param pBuffer       - pointer to data buffer (same size like FLASH_PAGE_SIZE)
                 * \param unLength      - data length
                 * 
                 * \return void
                 */
                void WritePage(uint32_t unAddress, uint8_t *pBuffer);

                /**
                 * \brief   Read flash page (also RWWEE section)
                 * 
                 * \param unAddress     - address inside page
                 * \param pBuffer       - pointer to data buffer (same size like FLASH_PAGE_SIZE)
                 * 
                 * \return void
                 */
                void ReadPage(uint32_t unAddress, uint8_t *pBuffer);

                /**
                 * \brief   Erase row (4 pages)
                 * 
                 * \param unAddress     - address inside row
                 * 
                 * \return void
                 */
                void EraseRow(uint32_t unAddress);

                /**
                 * \brief   Write Flash EEPROM page
                 * 
                 * \param unAddress     - address inside RWWEE section
                 * \param pBuffer       - pointer to data buffer (same size like FLASH_PAGE_SIZE)
                 * 
                 * \return void
                 */
                void WritePageFEE(uint32_t unAddress, uint8_t *pBuffer);

                /**
                 * \brief   Erase row (4 pages) in RWWEE section
                 * 
                 * \param unAddress     - address inside row
                 * 
                 * \return void
                 */
                void EraseRowFEE(uint32_t unAddress);
        };
    }
}




#endif /* NVM_H_ */