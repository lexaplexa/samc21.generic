/*****************************************************************************
 * can.h
 *
 * Created: 9.12.2015 11:31:14
 * Revised: 22.7.2019
 * Author: uidm2956
 * BOARD: 
 * ABOUT:
 *
 *****************************************************************************/


#ifndef CAN_H_
#define CAN_H_

#include <sam.h>
#include <conf/conf_board.h>

/*===== STANDARD DEFINES ================================================
 *======================================================================*/
#define can_init_state()                                        m_pCan->CCCR.bit.INIT = true; while(!m_pCan->CCCR.bit.INIT); m_pCan->CCCR.bit.CCE = true
#define can_normal_state()                                      m_pCan->CCCR.bit.INIT = false

namespace Core
{
    namespace Drivers
    {
        /*===== DATA FIELD SIZE ================================================
         * CAN has standardized data field size. It must be defined exactly one
         * of these 8 possibilities.
         * Data field size = 8 (Classic CAN/CAN FD)
         * Data field size > 8 (CAN FD)
         *======================================================================*/
        #ifndef CAN_DATA_FIELD_SIZE
           #define CAN_DATA_FIELD_SIZE             64
        #endif

        #if CAN_DATA_FIELD_SIZE <= 8
           #define CAN_DATA_FIELD_SIZE             8
           #define CAN_DATA_FIELD_Val              CAN_TXESC_TBDS_DATA8_Val
        #elif CAN_DATA_FIELD_SIZE <= 12
           #define CAN_DATA_FIELD_SIZE             12
           #define CAN_DATA_FIELD_Val              CAN_TXESC_TBDS_DATA12_Val
        #elif CAN_DATA_FIELD_SIZE <= 16
           #define CAN_DATA_FIELD_SIZE             16
           #define CAN_DATA_FIELD_Val              CAN_TXESC_TBDS_DATA16_Val
        #elif CAN_DATA_FIELD_SIZE <= 20
           #define CAN_DATA_FIELD_SIZE             20
           #define CAN_DATA_FIELD_Val              CAN_TXESC_TBDS_DATA20_Val
        #elif CAN_DATA_FIELD_SIZE <= 24
           #define CAN_DATA_FIELD_SIZE             24
           #define CAN_DATA_FIELD_Val              CAN_TXESC_TBDS_DATA24_Val
        #elif CAN_DATA_FIELD_SIZE <= 32
           #define CAN_DATA_FIELD_SIZE             32
           #define CAN_DATA_FIELD_Val              CAN_TXESC_TBDS_DATA32_Val
        #elif CAN_DATA_FIELD_SIZE <= 48
           #define CAN_DATA_FIELD_SIZE             48
           #define CAN_DATA_FIELD_Val              CAN_TXESC_TBDS_DATA48_Val
        #else
           #define CAN_DATA_FIELD_SIZE             64
           #define CAN_DATA_FIELD_Val              CAN_TXESC_TBDS_DATA64_Val
        #endif

        /************************************************************************/
        /* ENUMS                                                                */
        /************************************************************************/
        enum CAN_DATA_LENGTH_CODE_enum {
            CAN_DATA_LENGTH_CODE_0,
            CAN_DATA_LENGTH_CODE_1,
            CAN_DATA_LENGTH_CODE_2,
            CAN_DATA_LENGTH_CODE_3,
            CAN_DATA_LENGTH_CODE_4,
            CAN_DATA_LENGTH_CODE_5,
            CAN_DATA_LENGTH_CODE_6,
            CAN_DATA_LENGTH_CODE_7,
            CAN_DATA_LENGTH_CODE_8,
            CAN_DATA_LENGTH_CODE_12,
            CAN_DATA_LENGTH_CODE_16,
            CAN_DATA_LENGTH_CODE_20,
            CAN_DATA_LENGTH_CODE_24,
            CAN_DATA_LENGTH_CODE_32,
            CAN_DATA_LENGTH_CODE_48,
            CAN_DATA_LENGTH_CODE_64,
        };

        enum CAN_RET_CODE_enum {
            CAN_RET_CODE_OK,
            CAN_RET_CODE_BUFFER_FULL,
            CAN_RET_CODE_BUFFER_EMPTY,
            CAN_RET_CODE_BUFFER_MSG_LOST,
            CAN_RET_CODE_BUFFER_FILLED,
            CAN_RET_CODE_OUT_OF_RANGE,
            CAN_RET_CODE_FIFO_UNDEFINED,
        };

        enum CAN_EVENT_enum {
            CAN_EVENT_RxFifo0Received,
            CAN_EVENT_RxFifo1Received,
            CAN_EVENT_TxFifoEmpty,
            CAN_EVENT_sum,                  /* Sum of all events. DO NOT DELETE!! */
        };

        /*===== RAM MESSAGE DESCRIPTORS ========================================
         * According data sheet chapter 34.9
         *======================================================================*/
        struct CAN_TX_FIFO_ELEMENT_struct {
            /* T0 register */
            union {
                struct {
                    uint32_t ID:29;             /* Identifier */
                    uint32_t RTR:1;             /* Remote transmission Request */
                    uint32_t XTD:1;             /* Extended Identifier */
                    uint32_t ESI:1;             /* Error State indicator */
                };
                uint32_t T0_reg;
            };  
            /* T1 register */
            union {
                struct {
                    uint32_t :16;               
                    uint32_t DLC:4;             /* Data Length Code */ 
                    uint32_t BRS:1;             /* Bit Rate Search */
                    uint32_t FDF:1;             /* FD Format */
                    uint32_t :1;
                    uint32_t EFC:1;             /* Event FIFO control */
                    uint32_t MM:8;              /* Message Marker (Written by CPU) */
                };
                uint32_t T1_reg;
            };
            /* Data registers */
            uint8_t aunData[CAN_DATA_FIELD_SIZE];   /* CAN Data bytes */
        };

        struct CAN_RX_FIFO_ELEMENT_struct {
            /* R0 register */
            union {
                struct {
                    uint32_t ID:29;             /* Identifier */
                    uint32_t RTR:1;             /* Remote transmission Request */
                    uint32_t XTD:1;             /* Extended Identifier */
                    uint32_t ESI:1;             /* Error State indicator */
                };
                uint32_t R0_reg;
            };
            /* R1 register */
            union {
                struct {
                    uint32_t RXTS:16;           /* Time Stamp */
                    uint32_t DLC:4;             /* Data Length Code */
                    uint32_t BRS:1;             /* Bit Rate Search */
                    uint32_t FDF:1;             /* FD Format */
                    uint32_t :2;
                    uint32_t FIDX:7;            /* Filter Index */
                    uint32_t ANMF:1;            /* Accepted Non-matching Frame */
                };
                uint32_t R1_reg;
            };
            /* Data registers */
            uint8_t aunData[CAN_DATA_FIELD_SIZE];   /* CAN Data bytes */
        };

        struct CAN_TX_EVENT_ELEMENT_struct {
            /* E0 register */
            union {
                struct {
                    uint32_t ID:29;             /* Identifier */
                    uint32_t RTR:1;             /* Remote transmission Request */
                    uint32_t XTD:1;             /* Extended Identifier */
                    uint32_t ESI:1;             /* Error State indicator */
                };
                uint32_t E0_reg;
            };
            /* E1 register */
            union {
                struct {
                    uint32_t TXTS:16;           /* TX Time Stamp */
                    uint32_t DLC:4;             /* Data Length Code */
                    uint32_t BRS:1;             /* Bit Rate Search */
                    uint32_t FDF:1;             /* FD Format */
                    uint32_t ET:2;              /* Event Type */
                    uint32_t MM:8;              /* Message Marker (Written by CPU) */
                };
                uint32_t E1_reg;
            };
        };

        struct CAN_RX_STD_ID_FILTER_ELEMENT_struct {
            /* S0 Register */
            union {
                struct {
                    uint32_t SFID2:11;          /* Standard filter ID 2 */
                    uint32_t :5;
                    uint32_t SFID1:11;          /* Standard filter ID 1 */
                    uint32_t SFEC:3;            /* Standard filter element configuration */
                    uint32_t SFT:2;             /* Standard filter type */  
                    };
                uint32_t S0_reg;    
            };  
        };

        struct CAN_RX_EXT_ID_FILTER_ELEMENT_struct {
            /* F0 Register */
            union {
                struct {
                    uint32_t EFID1:28;          /* Extended filter ID 1 */
                    uint32_t EFEC:3;            /* Extended filter element configuration */
                };
                uint32_t F0_reg;
            };
            /* F1 Register */
            union {
                struct {
                    uint32_t EFID2:28;          /* Extended filter ID 2 */
                    uint32_t :1;
                    uint32_t EFT:2;             /* Extended filter type */  
                };
                uint32_t F1_reg;
            };
        };

        /*===== CAN MESSAGE ====================================================
         * Structure for using in application
         *======================================================================*/
        struct CAN_MSG_struct {
            uint32_t unID;
            CAN_DATA_LENGTH_CODE_enum eDLC;
            uint8_t* pData;
        };

        /*===== CAN BUFFER/FIFO SIZE ===========================================
         *======================================================================*/
        #ifndef CAN_TX_FIFO_SIZE
            #define CAN_TX_FIFO_SIZE                2
        #endif

        #ifndef CAN_RX_FIFO0_SIZE
            #define CAN_RX_FIFO0_SIZE               2
        #endif

        #ifndef CAN_RX_FIFO1_SIZE
            #define CAN_RX_FIFO1_SIZE               2
        #endif

        #ifndef CAN_RX_FILTER_STD_SIZE
            #define CAN_RX_FILTER_STD_SIZE          2
        #endif

        #ifndef CAN_RX_FILTER_EXT_SIZE
            #define CAN_RX_FILTER_EXT_SIZE          2
        #endif

        /*===== NOMINAL BIT TIMING =============================================
         * Fcan = Fclock/(NBRP + 1)
         * 1 Time segment = 1/Fcan
         * 1 Nominal bit = NTSEG1 + NTSEG2 + 3
         *======================================================================*/
        #ifndef CAN_NBIT_TIMING_NBRP
            #define CAN_NBIT_TIMING_NBRP            2       /* Nominal baud rate prescaler */
        #endif
        #ifndef CAN_NBIT_TIMING_NTSEG1
            #define CAN_NBIT_TIMING_NTSEG1          9       /* Nominal time segment 1 (before sample point) */ 
        #endif
        #ifndef CAN_NBIT_TIMING_NTSEG2
            #define CAN_NBIT_TIMING_NTSEG2          4       /* Nominal time segment 2 (after sample point) */ 
        #endif

        /************************************************************************/
        /* MAX Elements size                                                    */
        /************************************************************************/
        #define CAN_TX_FIFO_MAX_SIZE                32
        #define CAN_RX_FIFO0_MAX_SIZE               64
        #define CAN_RX_FIFO1_MAX_SIZE               64
        #define CAN_RX_STD_ID_FILTER_MAX_SIZE       128
        #define CAN_RX_EXT_ID_FILTER_MAX_SIZE       64


        /************************************************************************/
        /* CLASS                                                                */
        /************************************************************************/
        class CAN
        {
            private:
                Can *m_pCan;
                CAN_TX_FIFO_ELEMENT_struct* m_psTxFifo = nullptr;
                CAN_RX_FIFO_ELEMENT_struct* m_psRxFifo0 = nullptr;
                CAN_RX_FIFO_ELEMENT_struct* m_psRxFifo1 = nullptr;
                CAN_RX_STD_ID_FILTER_ELEMENT_struct* m_psRxStdFilter = nullptr;
                CAN_RX_EXT_ID_FILTER_ELEMENT_struct* m_psRxExtFilter = nullptr;
                void* m_peventFunc[CAN_EVENT_sum];              /* Pointers to event functions */
                    
            public:

                /**
                 * \brief   CAN constructor
                 * 
                 * \param pCan      - pointer to CAN peripheral module
                 * \param unGenNum  - clock generator number
                 * 
                 * \return 
                 */
                CAN(::Can *pCan, uint8_t unGeneratorNum);
                
                /**
                 * \brief   Initialize CAN
                 * 
                 * \param unTxFifoSize      - Tx FIFO size
                 * \param unRxFifo0Size     - Rx FIFO0 size
                 * \param unRxFifo1Size     - Rx FIFO0 size
                 * \param unRxStdFilterSize - Rx Standard filter buffer size
                 * \param unRxExtFilterSize - Rx Extended filter buffer size
                 * 
                 * \return void
                 */
                void Init(uint8_t unTxFifoSize, uint8_t unRxFifo0Size, uint8_t unRxFifo1Size, uint8_t unRxStdFilterSize, uint8_t unRxExtFilterSize);

                /**
                 * \brief   Set nominal baud rate
                 *          1 Nominal bit = 3 + unTimeSegment1 + unTimeSegment2
                 * 
                 * \param unBaudPrescaler   - CAN clock prescaler (Fcan = Fclock/(unBaudPrescaler + 1))
                 * \param unTimeSegment1    - Nominal time segment 1 (before sample point)
                 * \param unTimeSegment2    - Nominal time segment 2 (after sample point)
                 * 
                 * \return void
                 */
                void SetBaud(uint8_t unBaudPrescaler, uint8_t unTimeSegment1, uint8_t unTimeSegment2);

                /**
                 * \brief   Set baud rate for data
                 *          
                 * 
                 * \param unBaudPrescaler   - CAN clock prescaler (Fcan = Fclock/(unBaudPrescaler + 1))
                 * \param unTimeSegment1    - Nominal time segment 1 (before sample point)
                 * \param unTimeSegment2    - Nominal time segment 2 (after sample point)
                 * 
                 * \return void
                 */
                void SetBaudFd(uint8_t unBaudPrescaler, uint8_t unTimeSegment1, uint8_t unTimeSegment2);

                /**
                 * \brief   Add CAN ID to filter element. Filtered messages are stored to FIFO1
                 * 
                 * \param unCanID       - CAN ID (11 bit or 29bit)
                 * 
                 * \return RET_CODE_enum
                 */
                CAN_RET_CODE_enum eAddFilter(uint32_t unCanID);

                /**
                 * \brief   Disable all filter elements
                 * 
                 * 
                 * \return void
                 */
                void DisableFilters();

                /**
                 * \brief   Send CAN message
                 * 
                 * \param psCanMsg  - pointer to CAN message structure
                 * 
                 * \return RET_CODE_enum
                 */
                CAN_RET_CODE_enum eSendMsg(CAN_MSG_struct *psCanMsg);

                /**
                 * \brief   Add TX FIFO element
                 * 
                 * \param psTxMsg   - pointer to transmit buffer element
                 * 
                 * \return RET_CODE_enum
                 */
                CAN_RET_CODE_enum eAddTxElm(CAN_TX_FIFO_ELEMENT_struct* psTxMsg);

                /**
                 * \brief   Returns Rx FIFO0 status
                 * 
                 * 
                 * \return RET_CODE_enum
                 */
                CAN_RET_CODE_enum eRxFifo0Status();

                /**
                 * \brief   Returns Rx FIFO1 status
                 * 
                 * 
                 * \return RET_CODE_enum
                 */
                CAN_RET_CODE_enum eRxFifo1Status();

                /**
                 * \brief   Returns buffer FIFO0 fill size
                 * 
                 * 
                 * \return uint8_t  - buffer fill size
                 */
                uint8_t unRxFifo0FillSize() {return m_pCan->RXF0S.bit.F0FL;}

                /**
                 * \brief   Returns buffer FIFO1 fill size
                 * 
                 * 
                 * \return uint8_t  - buffer fill size
                 */
                uint8_t unRxFifo1FillSize() {return m_pCan->RXF1S.bit.F1FL;}

                /**
                 * \brief   Save oldest received message from Rx FIFO0 to pointer sRxMsg. 
                 *          Element is flushed from Rx FIFO0
                 * 
                 * \param psRxMsg   - pointer to Rx buffer element
                 * 
                 * \return RET_CODE_enum
                 */
                CAN_RET_CODE_enum eRxFifo0LastMsg(CAN_RX_FIFO_ELEMENT_struct* psRxMsg);

                /**
                 * \brief   Save oldest received message from Rx FIFO1 to pointer sRxMsg. 
                 *          Element is flushed from Rx FIFO1
                 * 
                 * \param psRxMsg   - pointer to Rx buffer element
                 * 
                 * \return RET_CODE_enum
                 */
                CAN_RET_CODE_enum eRxFifo1LastMsg(CAN_RX_FIFO_ELEMENT_struct* psRxMsg);

                /**
                 * \brief   Assign function to a event type
                 *
                 * \param eEventType    - type of event
                 * \param peventFunc    - pointer to event function
                 *
                 * \return void
                 */
                void SetEvent(CAN_EVENT_enum eEventType, void* peventFunc)
                {
                    m_peventFunc[eEventType] = peventFunc;
                }

                /**
                 * \brief   Get pointer to event function
                 * 
                 * \param eEventType    - type of event
                 * 
                 * \return void*        - pointer to event function
                 */
                void* GetEvent(CAN_EVENT_enum eEventType)
                {
                    return m_peventFunc[eEventType];
                }

                /**
                 * \brief   Interrupt handler
                 *
                 *
                 * \return void
                 */
                inline void InterruptHandler()
                {

                }
        };
    }
}

#endif /* CAN_H_ */
