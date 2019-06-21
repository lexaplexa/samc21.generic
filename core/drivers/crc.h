/*************************************************************************
 * crc.h
 *
 * Created: 18.06.2019 14:05:14
 * Revised: 
 * Author: uidm2956
 * BOARD:
 *
 * ABOUT:
 *
 *************************************************************************/


#ifndef CRC_H_
#define CRC_H_

#include <sam.h>

namespace Core
{
    namespace Drivers
    {
        class CRC
        {
            public:
                /**
                 * \brief   CRC16
                 *          CCITT (polynom 0x1021)
                 *          Init value 0xFFFF
                 * 
                 * \param pData         - pointer to data
                 * \param unLength      - data length
                 * 
                 * \return uint16_t     - CRC16 value
                 */
                static uint16_t unCRC16(uint8_t* pData, uint16_t unLength);

                /**
                 * \brief   CRC16
                 *          CCITT (polynom 0x1021)
                 *          Init value 0xFFFF
                 * 
                 * \param pData         - pointer to data
                 * \param unLength      - data length
                 * 
                 * \return uint16_t     - CRC16 value
                 */
                static uint16_t unCRC16(uint16_t* pData, uint16_t unLength);

                /**
                 * \brief   CRC16
                 *          CCITT (polynom 0x1021)
                 *          Init value 0xFFFF
                 * 
                 * \param pData         - pointer to data
                 * \param unLength      - data length
                 * 
                 * \return uint16_t     - CRC16 value
                 */
                static uint16_t unCRC16(uint32_t* pData, uint16_t unLength);

                /**
                 * \brief   CRC32
                 *          IEEE 802.3 (polynom 0x04C11DB7)
                 *          Init value 0xFFFFFFFF
                 * 
                 * \param pData         - pointer to data
                 * \param unLength      - data length
                 * 
                 * \return uint16_t     - CRC32 value
                 */
                static uint32_t unCRC32(uint8_t* pData, uint16_t unLength);

                /**
                 * \brief   CRC32
                 *          IEEE 802.3 (polynom 0x04C11DB7)
                 *          Init value 0xFFFFFFFF
                 * 
                 * \param pData         - pointer to data
                 * \param unLength      - data length
                 * 
                 * \return uint16_t     - CRC32 value
                 */
                static uint32_t unCRC32(uint16_t* pData, uint16_t unLength);

                /**
                 * \brief   CRC32
                 *          IEEE 802.3 (polynom 0x04C11DB7)
                 *          Init value 0xFFFFFFFF
                 * 
                 * \param pData         - pointer to data
                 * \param unLength      - data length
                 * 
                 * \return uint16_t     - CRC32 value
                 */
                static uint32_t unCRC32(uint32_t* pData, uint16_t unLength);
        };
    }
}

#endif /* CRC_H_ */