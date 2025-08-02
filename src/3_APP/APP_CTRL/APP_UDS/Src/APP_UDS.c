/**
 * @file        LibRamp.c
 * @brief       Framework Memory Access Control module.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        15/09/2024
 * @version     1.0
 */
// ********************************************************************
// *                      Includes
// ********************************************************************

#include "./APP_UDS.h"
#ifdef APPSYS_MODULE_APP_UDS_ENABLE
#include "APP_CTRL/APP_SDM/Src/APP_SDM.h"
#include "APP_LGC/Src/APP_LGC.h"
#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"


#include "Library/SafeMem/SafeMem.h"
#include "APP_CFG/ConfigApp/SoftwareVersion.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
/**
 * @brief Max Data Len
 */
#define APPUDS_MAX_DATA_LEN ((t_uint32)64)
/**
 * @brief When user send command it's exatly 8 bytes
 */
#define APPUDS_CLIENT_INFO_MAX_LEN ((t_uint8)8)
/**
 * @brief Max Data Len
 */
#define APPUDS_MAX_TIME_WAIT_ACK ((t_uint32)20001)
/**
 * @brief Define for Message Id
 */
#define APPUDS_ID_AKNOWLEDGMENT_OK          ((t_uint8)0xFF)
#define APPUDS_ID_AKNOWLEDGMENT_NOT_OK      ((t_uint8)0x0F)
#define APPUDS_ID_SERVER_SEND_INFO          ((t_uint8)0x31)
#define APPUDS_ID_CLIENT_INFO_OK            ((t_uint8)0x32)
#define APPUDS_ID_CLIENT_SEND_RQST          ((t_uint8)0x41)
#define APPUDS_ID_CLIENT_SERVER_RQST_RESP   ((t_uint8)0x42)
#define APPUDS_ID_ERROR_STATUS              ((t_uint8)0x51)
#define APPUDS_ID_SERVER_SEND_ACT           ((t_uint8)0x61)
#define APPUDS_ID_SERVER_SEND_SNS           ((t_uint8)0x62)
#define APPUDS_ID_SERVER_SEND_SRV           ((t_uint8)0x63)
#define APPUDS_ID_SERVER_SEND_DAIG          ((t_uint8)0x64)

#define APPUDS_ID_FIRST_FRAME_DATA_0        ((t_uint8)0x1A)
#define APPUDS_ID_FIRST_FRAME_DATA_1        ((t_uint8)0x1B)
#define APPUDS_ID_FIRST_FRAME_DATA_2        ((t_uint8)0x1C)
#define APPUDS_ID_FIRST_FRAME_DATA_3        ((t_uint8)0x1D)
#define APPUDS_ID_FIRST_FRAME_DATA_4        ((t_uint8)0x1E)
#define APPUDS_ID_FIRST_FRAME_DATA_5        ((t_uint8)0x1F)
#define APPUDS_ID_FIRST_FRAME_DATA_6        ((t_uint8)0x2A)

// ********************************************************************
// *                      Types
// ********************************************************************
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */

//-----------------------------ENUM TYPES-----------------------------//
/**
 * @brief FSM for Operational State 
 */
typedef enum 
{
    APPUDS_FSM_OPE_IDLE = 0x00,             /**< No client send request to be connected */
    APPUDS_FSM_OPE_AUTHENTIFICATION,        /**< A client try to connect, verification & authentification state */
    APPUDS_FSM_CLIENT_CONNECTED,                  /**< A client is connected and wants to do stuff */
} t_eAPPUDS_FsmOpeState;

/**
 * @brief FSM for Client Processing state
 */
typedef enum 
{
    APPUDS_FSM_CLIENTCO_WAIT_REQUEST = 0x00,      /**< Waiting a client request  */
    APPUDS_FSM_CLIENTCO_PROCESS_REQUEST,          /**< A request has been submitted and server is processing */
} t_eAPPUDS_FsmClientCoState;

/**
 * @brief FSM for Client Authentification
 */
typedef enum 
{
    APPUDS_FSM_AUTH_CHECK_CLIENT = 0x00,        /**< Check the data msg to know it it's the one expected */
    APPUDS_FSM_AUTH_SEND_INFO,                  /**< Send Information about software version/ hardware version / Ecu ID*/ 
    APPUDS_FSM_AUTH_WAIT_ACK,                        /**< Wait Acknolegment from application*/ 
} t_eAPPUDS_FsmAuthState;
/**
 * @brief Enum of all Request available
 */
enum 
{
    APPUDS_BIT_REQUEST_CYCLIC_TIME = 0x00,
    APPUDS_BIT_REQUEST_READ_ACTUATOR,
    APPUDS_BIT_REQUEST_READ_SENSORS,
    APPUDS_BIT_REQUEST_READ_SERVICE_HEALTH,
    APPUDS_BIT_REQUEST_READ_DIAGNOSTIC,
    APPUDS_BIT_REQUEST_READ_PARAM,
    APPUDS_BIT_REQUEST_WRITE_PARAM,
    APPUDS_BIT_REQUEST_READ_ALL_PARAM,
    APPUDS_BIT_REQUEST_WRITE_ALL_PARAM,
    APPUDS_BIT_REQUEST_FLASH_ECU,
    APPUDS_BIT_REQUEST_CONTROL_ACTUATORS,

    APPUDS_BIT_REQUEST_NB
};

/**
 * @brief Enum of Info about Reception
 */
enum 
{
    APPUDS_BIT_RX_INFO_RECEPTION_LOCKED = 0x00,
    APPUDS_BIT_RX_INFO_NEW_DATA,
};

/**
 * @brief Enum to inform client an error occured 
 */
typedef enum 
{
    APPUDS_SERVER_ERROR_CRC = 0x01,
    APPUDS_SERVER_ERROR_FIRST_FRAME,
    APPUDS_SERVER_ERROR_TIMEOUT,
    APPUDS_SERVER_FRAME_RQST_ERROR,
    APPUDS_SERVER_ERROR_NB,
} t_eAPPUDS_ServerError;
/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//


//-----------------------------TYPEDEF TYPES---------------------------//

// ********************************************************************
// *                      Variables
// ********************************************************************

/**
 * @brief Container for module stazte
 */
static t_eCyclicModState g_AppUds_ModState_e = STATE_CYCLIC_CFG;
/**
 * 
 * @brief Container to know when a client is trying to connect to the UDS Server
 */
static t_bool g_reqClientCo_b = (t_bool)False;
/**
 * 
 * @brief Container to get information about the state of the reception
 */
static t_uint8 g_flagReception_u8 = (t_uint8)0;
/**
 * @brief Container for Receiving/ Transmitting Data from Client 
 */
static t_uint8 g_RxBuffer_ua8[APPUDS_MAX_DATA_LEN];
//static t_uint8 g_TxBuffer_ua8[APPUDS_MAX_DATA_LEN];

static t_uint8 g_8bitsCrcMcuId_u8 = (t_uint8)(0x00);

static t_uint32 g_32bitsCrcMcuId_u32 = (t_uint32)(0x00);
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
*
*	@brief      Configure the Wire Serial Line.
*	@note   	 
*
*
*/
static t_eReturnCode s_APPUDS_ConfigurationState(void);
/**
*
*	@brief      Configure the Wire Serial Line.
*	@note   
*
*
*/
static t_eReturnCode s_APPUDS_OperationalState(void);
/**
*
*	@brief      Authentification Process Management
*	@note   
*
*
*/
static t_eReturnCode s_APPUDS_AuthentificationMngmt(void);
/**
*
*	@brief      Authentification Process Management
*	@note   
*
*
*/
static t_eReturnCode s_APPUDS_ClientConnectedMngmt(void);
/**
*
*	@brief      Authentification Process Management
*	@note   
*
*
*/
static t_eReturnCode s_APPUDS_ProcessClientRequest(t_uint32 f_maskOpe_u32);
/**
*
*	@brief      Send Error Message to Client
*	@note   
*
*
*/
static t_eReturnCode s_APPUDS_SendErrorMngmt(t_eAPPUDS_ServerError f_errorId_e);
/**
*
*	@brief      Send Error Message to Client
*	@note   
*
*
*/
static t_eReturnCode s_APPUDS_SendMcuInfo(void);
/**
*
*	@brief      Authentification Process Management
*	@note   
*
*
*/
static t_eReturnCode s_APPUDS_ClientReqReadIODiagSrv(t_uint8 f_clientReqId_u8);
/**
*
*	@brief      Send Ecu Response for a client request
*
*
*/
static t_eReturnCode s_APPUDS_SendEcuRqstResponse(t_bool f_isReqstAccept_b);
/**
*
*	@brief      Serial Receive Callback
*	@note   
*
*
*/
static void s_APPUDS_ClientRcvCallback( t_uint8 * f_rxData_pu8, 
                                        t_uint16 f_dataSize_u16, 
                                        t_eFMKSRL_RxCallbackInfo f_InfoCb_e);
//********************************************************************************
//                      Public functions - Implementation
//********************************************************************************
//********************************
// APPUDS_Init
//********************************
t_eReturnCode APPUDS_Init(void)
{
    t_eReturnCode Ret_e = RC_OK;
    // get the Unique id 
    t_uint32 WordMcuId_ua32[MCU_UID_LEN] = {
        MCU_UID_WORD_1,
        MCU_UID_WORD_2,
        MCU_UID_WORD_3
    };

    //---- Compute 32BitsCRC from 96 bits MCUID & 8BitsCRC from 32bits CRC ----//
    Ret_e = LIBCRC_ComputeCrc32Bits((const t_uint8 *)(&WordMcuId_ua32),
                                    (t_uint16)(sizeof(t_uint32) * MCU_UID_LEN),
                                    APPUDS_CRC32B_POLYNOME_USED,
                                    (t_uint32)APPUDS_CRC32B_STARTVALUE,
                                    &g_32bitsCrcMcuId_u32);
    if(Ret_e == RC_OK)
    {
        Ret_e = LIBCRC_ComputeCrc8Bits( (const t_uint8 *)(&g_32bitsCrcMcuId_u32),
                                        (t_uint8)(sizeof(t_uint8) * 4), // 32 bits 
                                        APPUDS_CRC8B_POLYNOME_USED,
                                        (t_uint8)APPUDS_CRC8B_STARTVALUE,
                                        &g_8bitsCrcMcuId_u8);
    }
    return Ret_e;
}

//********************************
// APPUDS_Cyclic
//********************************
t_eReturnCode APPUDS_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;

    switch(g_AppUds_ModState_e)
    {
        case STATE_CYCLIC_CFG:
        {
            Ret_e = s_APPUDS_ConfigurationState();

            if(Ret_e == RC_OK)
            {
                g_AppUds_ModState_e = STATE_CYCLIC_WAITING;
            }
            break;
        }
        case STATE_CYCLIC_WAITING:
        {
            break;
        }
        case STATE_CYCLIC_PREOPE:
        {
            g_AppUds_ModState_e = STATE_CYCLIC_OPE;
            break;
        }
        case STATE_CYCLIC_OPE:
        {
            Ret_e = s_APPUDS_OperationalState();
            if(Ret_e < RC_OK)
            {
                ASSERT((t_uint16)0);
                g_AppUds_ModState_e = STATE_CYCLIC_ERROR;
            }
        }
        case STATE_CYCLIC_BUSY:
        case STATE_CYCLIC_ERROR:
        default:
        {
            break;
        }
    }

    return Ret_e;
}

/*********************************
 * APPLGC_GetState
 *********************************/
t_eReturnCode APPUDS_GetState(t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_AppUds_ModState_e;
    }

    return Ret_e;
}

/*********************************
 * APPLGC_SetState
 *********************************/
t_eReturnCode APPUDS_SetState(t_eCyclicModState f_State_e)
{

    g_AppUds_ModState_e = f_State_e;

    return RC_OK;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************

//********************************
// s_APPUDS_ConfigurationState
//********************************
static t_eReturnCode s_APPUDS_ConfigurationState(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sFMKSRL_DrvSerialCfg SrlCfg_s;
    SrlCfg_s.runMode_e = FMKSRL_LINE_RUNMODE_DMA;
    SrlCfg_s.hwProtType_e = FMKSRL_HW_PROTOCOL_UART;

    SrlCfg_s.hwCfg_s.Baudrate_e = FMKSRL_LINE_BAUDRATE_115200,
    SrlCfg_s.hwCfg_s.Mode_e = FMKSRL_LINE_MODE_RX_TX;
    SrlCfg_s.hwCfg_s.Parity_e = FMKSRL_LINE_PARITY_NONE,
    SrlCfg_s.hwCfg_s.Stopbit_e = FMKSRL_LINE_STOPBIT_1,
    SrlCfg_s.hwCfg_s.wordLenght_e = FMKSRL_LINE_WORDLEN_8BITS,

    SrlCfg_s.CfgSpec_u.uartCfg_s.hwFlowCtrl_e = FMKSRL_UART_HW_FLOW_CTRL_NONE;
    SrlCfg_s.CfgSpec_u.uartCfg_s.Type_e = FMKSRL_UART_TYPECFG_UART;

    /*Ret_e = FMKSRL_InitDrv( APPUDS_SERIAL_LINE,
                            SrlCfg_s,
                            s_APPUDS_ClientRcvCallback,
                            (t_cbFMKSRL_TransmitMsgEvent *)NULL_FUNCTION);
    if(Ret_e == RC_OK)
    {
        Ret_e = FMKSRL_ConfigureReception(  APPUDS_SERIAL_LINE,
                                            FMKSRL_OPE_RX_CYCLIC_SIZE,
                                            APPUDS_CLIENT_INFO_MAX_LEN);
    }*/
        
    return Ret_e;
}

//********************************
// s_APPUDS_OperationalState
//********************************
static t_eReturnCode s_APPUDS_OperationalState(void)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_eAPPUDS_FsmOpeState s_FsmOperationalState_e = APPUDS_FSM_OPE_IDLE;
    
    switch(s_FsmOperationalState_e)
    {
        case APPUDS_FSM_OPE_IDLE:
        {
            if(g_reqClientCo_b == (t_bool)True)
            {
                SETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_RECEPTION_LOCKED);
                s_FsmOperationalState_e = APPUDS_FSM_OPE_AUTHENTIFICATION;
            }
            break;
        }
        case APPUDS_FSM_OPE_AUTHENTIFICATION:
        {
            Ret_e = s_APPUDS_AuthentificationMngmt();

            if(Ret_e == RC_OK)
            {
                s_FsmOperationalState_e = APPUDS_FSM_CLIENT_CONNECTED;
            }

            //---- Too many seconds has passed and connection is aborted ----//
            if((Ret_e == RC_WARNING_LIMIT_REACHED)
            || (Ret_e == RC_WARNING_WRONG_RESULT))
            {
                s_FsmOperationalState_e = APPUDS_FSM_OPE_IDLE;
                RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_RECEPTION_LOCKED);
                RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA);
                Ret_e = RC_OK;
            }
            else if(Ret_e < RC_OK)
            {
                ASSERT((t_uint16)Ret_e);
                s_FsmOperationalState_e = APPUDS_FSM_OPE_IDLE;

            }
            break;
        }
        case APPUDS_FSM_CLIENT_CONNECTED:
        {
            Ret_e = s_APPUDS_ClientConnectedMngmt();

            if(Ret_e == RC_WARNING_WRONG_RESULT)
            {
                s_FsmOperationalState_e = APPUDS_FSM_OPE_IDLE;
            }
            if(Ret_e != RC_OK)
            {
                s_FsmOperationalState_e = APPUDS_FSM_OPE_IDLE;
                RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_RECEPTION_LOCKED);
                RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA);
                Ret_e = RC_OK;
            }
            break;
        }
    }

    return Ret_e;
}

//********************************
// s_APPUDS_AuthentificationMngmt
//********************************
static t_eReturnCode s_APPUDS_AuthentificationMngmt(void)
{
    t_eReturnCode Ret_e = RC_WARNING_PENDING;
    t_eReturnCode subRet_e = RC_OK;
    t_uint8 CrcCompute_u8;
    static t_eAPPUDS_FsmAuthState s_FsmAuthState_e = APPUDS_FSM_AUTH_CHECK_CLIENT;
    static t_uint32 s_saveTime_u32 = (t_uint32)0;
    t_uint32 currentTime_u32 = (t_uint32)0;

    switch(s_FsmAuthState_e)
    {
        case APPUDS_FSM_AUTH_CHECK_CLIENT:
        {
            //---- Check if the data receiving are exactly the one expected ----//
            if((g_RxBuffer_ua8[0] == APPUDS_ID_FIRST_FRAME_DATA_0)
            && (g_RxBuffer_ua8[1] == APPUDS_ID_FIRST_FRAME_DATA_1)
            && (g_RxBuffer_ua8[2] == APPUDS_ID_FIRST_FRAME_DATA_2)
            && (g_RxBuffer_ua8[3] == APPUDS_ID_FIRST_FRAME_DATA_3)
            && (g_RxBuffer_ua8[4] == APPUDS_ID_FIRST_FRAME_DATA_4)
            && (g_RxBuffer_ua8[5] == APPUDS_ID_FIRST_FRAME_DATA_5)
            && (g_RxBuffer_ua8[6] == APPUDS_ID_FIRST_FRAME_DATA_6))
            {
                //---- compute Crc from client ----//
                subRet_e = LIBCRC_ComputeCrc8Bits( (const t_uint8 *)(g_RxBuffer_ua8),
                                                (t_uint8)(sizeof(t_uint8) * (APPUDS_CLIENT_INFO_MAX_LEN - 1)), // 32 bits 
                                                APPUDS_CRC8B_POLYNOME_USED,
                                                (t_uint8)APPUDS_CRC8B_STARTVALUE,
                                                &CrcCompute_u8);
                if((subRet_e == RC_OK)
                && (CrcCompute_u8 == g_RxBuffer_ua8[7]))
                {                    
                    s_FsmAuthState_e = APPUDS_FSM_AUTH_SEND_INFO;
                }
                else 
                {
                    subRet_e = s_APPUDS_SendErrorMngmt(APPUDS_SERVER_ERROR_CRC);
                    if(subRet_e == RC_OK)
                    {
                        Ret_e = RC_WARNING_WRONG_RESULT;
                        g_reqClientCo_b = (t_bool)False;
                    }
                }
            }
            else 
            {
                subRet_e = s_APPUDS_SendErrorMngmt(APPUDS_SERVER_ERROR_FIRST_FRAME);
                if(subRet_e == RC_OK)
                {
                    Ret_e = RC_WARNING_WRONG_RESULT;
                    g_reqClientCo_b = (t_bool)False;
                }
            }
            
            RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_RECEPTION_LOCKED);
            RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA);
            break;
        }
        case APPUDS_FSM_AUTH_SEND_INFO:
        {
            //----- send the different information ----//
            subRet_e = s_APPUDS_SendMcuInfo();

            if(subRet_e == RC_OK)
            {
                s_FsmAuthState_e = APPUDS_FSM_AUTH_WAIT_ACK;
                FMKCPU_GetTick(&s_saveTime_u32);
            }
            break;
        }
        case APPUDS_FSM_AUTH_WAIT_ACK:
        {
            if(GETBIT(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA))
            {
                if((g_RxBuffer_ua8[0] == g_8bitsCrcMcuId_u8)
                && (g_RxBuffer_ua8[1] == APPUDS_ID_CLIENT_INFO_OK)
                && (g_RxBuffer_ua8[2] == APPUDS_ID_AKNOWLEDGMENT_OK))
                {
                    #warning('verify checksum of msg after showing Pajdak')
                    s_FsmAuthState_e = APPUDS_FSM_AUTH_CHECK_CLIENT; // Fsm return default :OK
                    Ret_e = RC_OK; // client connect state for FSM above
                }
                RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA);
            }
            
            //---- Timeout Managment ----//
            FMKCPU_GetTick(&currentTime_u32);
            if((currentTime_u32 - s_saveTime_u32) > APPUDS_MAX_TIME_WAIT_ACK)
            {
                subRet_e = s_APPUDS_SendErrorMngmt(APPUDS_SERVER_ERROR_TIMEOUT);
                if(subRet_e != RC_OK)
                {
                    Ret_e = RC_WARNING_PENDING; 
                }
                else 
                {
                    s_FsmAuthState_e = APPUDS_FSM_AUTH_CHECK_CLIENT;
                    g_reqClientCo_b = (t_bool)False;
                    Ret_e = RC_WARNING_LIMIT_REACHED;
                }
            }
            break;
        }
    }

    return Ret_e;
}

//********************************
// s_APPUDS_ClientConnectedMngmt
//********************************
static t_eReturnCode s_APPUDS_ClientConnectedMngmt(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eReturnCode subRet_e = RC_OK;
    t_uint8 computeCrc_u8;
    static t_uint32 s_maskClientOpe_u32 = (t_uint32)0;
    static t_eAPPUDS_FsmClientCoState s_FsmClientCoState_e = APPUDS_FSM_CLIENTCO_WAIT_REQUEST;

    switch(s_FsmClientCoState_e)
    {
        case APPUDS_FSM_CLIENTCO_WAIT_REQUEST:
        {
            if(GETBIT(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA) == BIT_IS_SET_8B)
            {
                //---- extract requests from Client ----//
                if((g_RxBuffer_ua8[0] == g_8bitsCrcMcuId_u8)
                && (g_RxBuffer_ua8[1]) == APPUDS_ID_CLIENT_SEND_RQST)
                {
                    s_maskClientOpe_u32 = Mu32BuildFromByte(    g_RxBuffer_ua8[5],
                                                                g_RxBuffer_ua8[4],
                                                                g_RxBuffer_ua8[3],
                                                                g_RxBuffer_ua8[2]);

                    //---- Compute Crc ----//
                    subRet_e= LIBCRC_ComputeCrc8Bits(   g_RxBuffer_ua8,
                                                        (t_uint16)(APPUDS_CLIENT_INFO_MAX_LEN - 1),
                                                        APPUDS_CRC8B_POLYNOME_USED,
                                                        APPUDS_CRC8B_STARTVALUE,
                                                        &computeCrc_u8);
                    if((subRet_e == RC_OK)
                    && (computeCrc_u8 == g_RxBuffer_ua8[7]))
                    {
                        //---- see if there is any reason we do not accept ----//
                        subRet_e = s_APPUDS_SendEcuRqstResponse(True);
                        if(subRet_e == RC_OK)
                        {
                            s_FsmClientCoState_e = APPUDS_FSM_CLIENTCO_PROCESS_REQUEST;
                        }
                    }
                    else 
                    {
                        subRet_e = s_APPUDS_SendErrorMngmt(APPUDS_SERVER_FRAME_RQST_ERROR);
                        if(subRet_e == RC_OK)
                        {
                            Ret_e = RC_WARNING_WRONG_RESULT;
                            g_reqClientCo_b = False;
                        }
                    }
                    RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA);
                    RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_RECEPTION_LOCKED);
                }
                else 
                {
                    subRet_e = s_APPUDS_SendErrorMngmt(APPUDS_SERVER_FRAME_RQST_ERROR);
                    if(subRet_e == RC_OK)
                    {
                        Ret_e = RC_WARNING_WRONG_RESULT;
                        g_reqClientCo_b = False;
                    }
                }
            }
            else if(GETBIT(g_flagReception_u8, APPUDS_BIT_RX_INFO_RECEPTION_LOCKED) == BIT_IS_SET_8B)
            {
                RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_RECEPTION_LOCKED);
            }
            break;
        }
        case APPUDS_FSM_CLIENTCO_PROCESS_REQUEST:
        {
            //---- check transition ----//
            if((GETBIT(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA) == BIT_IS_SET_8B)
            && ((g_RxBuffer_ua8[1]) == APPUDS_ID_CLIENT_SEND_RQST))
            {
                SETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_RECEPTION_LOCKED);
                s_FsmClientCoState_e = APPUDS_FSM_CLIENTCO_WAIT_REQUEST;
            }
            else 
            {
                subRet_e = s_APPUDS_ProcessClientRequest((t_uint32)s_maskClientOpe_u32);
            }
            break;
        }
        default:
        break;
    }
    if((subRet_e != RC_OK)
    && (Ret_e == RC_OK))
    {
        Ret_e = subRet_e;
        ASSERT((t_uint16)Ret_e);
    }

    return Ret_e;
}

//********************************
// s_APPUDS_ProcessClientRequest
//********************************
static t_eReturnCode s_APPUDS_ProcessClientRequest(t_uint32 f_maskOpe_u32)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- first deal with unitary request and then deal with cyclic request ----//
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_CONTROL_ACTUATORS) == BIT_IS_SET_8B)
    {
        //Ret_e = s_APPUDS_ClientReqActControlMngmt();
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_FLASH_ECU) == BIT_IS_SET_8B)
    {
        //Ret_e = s_APPUDS_ClientReqFlashEcu()
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_READ_ALL_PARAM) == BIT_IS_SET_8B)
    {
        //Ret_e = s_APPUDS_ClientReqParamMngmt(APPUDS_BIT_REQUEST_READ_ALL_PARAM);
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_WRITE_ALL_PARAM) == BIT_IS_SET_8B)
    {
        //Ret_e = s_APPUDS_ClientReqParamMngmt(APPUDS_BIT_REQUEST_WRITE_ALL_PARAM);
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_READ_PARAM) == BIT_IS_SET_8B)
    {
        //Ret_e = s_APPUDS_ClientReqParamMngmt(APPUDS_BIT_REQUEST_READ_ALL_PARAM);
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_WRITE_PARAM) == BIT_IS_SET_8B)
    {
        //Ret_e = s_APPUDS_ClientReqParamMngmt(APPUDS_BIT_REQUEST_WRITE_ALL_PARAM);
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_READ_ACTUATOR) == BIT_IS_SET_8B)
    {
        Ret_e = s_APPUDS_ClientReqReadIODiagSrv(APPUDS_BIT_REQUEST_READ_ACTUATOR);
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_READ_SENSORS) == BIT_IS_SET_8B)
    {
        Ret_e = s_APPUDS_ClientReqReadIODiagSrv(APPUDS_BIT_REQUEST_READ_SENSORS);
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_READ_DIAGNOSTIC) == BIT_IS_SET_8B)
    {
        Ret_e = s_APPUDS_ClientReqReadIODiagSrv(APPUDS_BIT_REQUEST_READ_DIAGNOSTIC);
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_READ_SERVICE_HEALTH) == BIT_IS_SET_8B)
    {
        Ret_e = s_APPUDS_ClientReqReadIODiagSrv(APPUDS_BIT_REQUEST_READ_SERVICE_HEALTH);
    }
    
    return Ret_e;
}

//********************************
// s_APPUDS_ClientReqReadIODiagSrv
//********************************
static t_eReturnCode s_APPUDS_ClientReqReadIODiagSrv(t_uint8 f_clientReqId_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LLI_U8;
    t_uint8 TxData_ua8[64];
    t_uint8 s_dataIdx_u8 = 0;
    if(f_clientReqId_u8 > APPUDS_BIT_REQUEST_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)f_clientReqId_u8);
    }
    if(Ret_e == RC_OK)
    {
        TxData_ua8[0] = g_8bitsCrcMcuId_u8;
        TxData_ua8[1] = APPUDS_ID_SERVER_SEND_ACT;
        for(LLI_U8 = (t_uint8)2 ; LLI_U8 < 64 ; LLI_U8++)
        {
            TxData_ua8[LLI_U8] = s_dataIdx_u8;
            s_dataIdx_u8++;
        }
        Ret_e = FMKSRL_Transmit(APPUDS_SERIAL_LINE,
                                FMKSRL_TX_ONESHOT,
                                TxData_ua8,
                                64,
                                (t_uint16)0,
                                False);
        /*if(f_clientReqId_u8 == APPUDS_BIT_REQUEST_READ_ACTUATOR)
        {

        }
        else if(f_clientReqId_u8 == APPUDS_BIT_REQUEST_READ_SENSORS)
        {

        }
        else if (f_clientReqId_u8 ==  APPUDS_BIT_REQUEST_READ_DIAGNOSTIC)
        {

        }
        else if (f_clientReqId_u8 ==  APPUDS_BIT_REQUEST_READ_SERVICE_HEALTH)
        {

        }
        else 
        {
            Ret_e = RC_WARNING_NO_OPERATION;
        }*/
    }

    return Ret_e;
}

//********************************
// s_APPUDS_ClientRcvCallback
//********************************
static void s_APPUDS_ClientRcvCallback( t_uint8 * f_rxData_pu8, 
                                        t_uint16 f_dataSize_u16, 
                                        t_eFMKSRL_RxCallbackInfo f_InfoCb_e)
{
    static t_uint8 s_idxWrite_u8 = (t_uint8)0;
    t_bool receptionComplete_b = False;
    t_eReturnCode Ret_e = RC_OK;

    if(f_dataSize_u16 > APPUDS_MAX_DATA_LEN)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)(f_dataSize_u16));
    }
    if(s_idxWrite_u8 >= APPUDS_MAX_DATA_LEN)
    {
        Ret_e = RC_ERROR_LIMIT_REACHED;
        ASSERT((t_uint16)(s_idxWrite_u8));
    }
    if(GETBIT(g_flagReception_u8, APPUDS_BIT_RX_INFO_RECEPTION_LOCKED) != BIT_IS_RESET_8B)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_InfoCb_e)
        {
            case FMKSRL_CB_INFO_RECEIVE_PENDING:
            {
                Ret_e = SafeMem_memcpy( (&g_RxBuffer_ua8[s_idxWrite_u8]),
                                        f_rxData_pu8,
                                        f_dataSize_u16);
                break;
            }
            case FMKSRL_CB_INFO_RECEIVE_ENDING:
            {
                Ret_e = SafeMem_memcpy( (&g_RxBuffer_ua8[s_idxWrite_u8]),
                                        f_rxData_pu8,
                                        f_dataSize_u16);
                if(Ret_e == RC_OK)
                {
                    s_idxWrite_u8 = (t_uint8)0;
                    receptionComplete_b = (t_bool)True;
                }
                break;
            }
            case FMKSRL_CB_INFO_RECEIVE_ERR:
            case FMKSRL_CB_INFO_RECEIVE_OVERFLOW:
            {
                //----- Report Diagnostic Evnt -----//
                APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_UDS_COM_ERROR,
                                        APPSDM_DIAG_ITEM_REPORT_FAIL,
                                        (t_uint16)f_InfoCb_e,
                                        (t_uint16)0);
                break;
            }
        }
        if(receptionComplete_b == (t_bool)True)
        {
            //---- check first byte to know if the key work is corresponding 
            //          to a client trying to connect to the server ----//
            //---- we don't check all 'caus eit's in the interruption, go fast ----//
            if((g_RxBuffer_ua8[0] == (t_uint8)(APPUDS_ID_FIRST_FRAME_DATA_0))
            && (g_reqClientCo_b == (t_bool)False))
            {
                g_reqClientCo_b = (t_bool)True;
            }
            SETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA);
        }
    }

    return;
}

//********************************
// s_APPUDS_SendErrorMngmt
//********************************
static t_eReturnCode s_APPUDS_SendErrorMngmt(t_eAPPUDS_ServerError f_errorId_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 txData_ua8[APPUDS_CLIENT_INFO_MAX_LEN];
    t_uint8 crcCompute_u8;

    if(f_errorId_e >= APPUDS_SERVER_ERROR_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)f_errorId_e);
    }
    if(Ret_e == RC_OK)
    {
        //----- Set data to default value ----//
        (void)SafeMem_memclear(txData_ua8, APPUDS_CLIENT_INFO_MAX_LEN);

        txData_ua8[0] = g_8bitsCrcMcuId_u8; // ecuId
        txData_ua8[1] = APPUDS_ID_ERROR_STATUS;
        txData_ua8[2] = (t_uint8)(f_errorId_e);

        Ret_e = LIBCRC_ComputeCrc8Bits( txData_ua8,
                                        (t_uint16)(APPUDS_CLIENT_INFO_MAX_LEN - 1),
                                        APPUDS_CRC8B_POLYNOME_USED,
                                        APPUDS_CRC8B_STARTVALUE,
                                        &crcCompute_u8);
        if(Ret_e == RC_OK)
        {
            txData_ua8[7] = crcCompute_u8;

            Ret_e = FMKSRL_Transmit(APPUDS_SERIAL_LINE,
                                    FMKSRL_TX_ONESHOT,
                                    txData_ua8,
                                    APPUDS_CLIENT_INFO_MAX_LEN,
                                    (t_uint16)0,
                                    False);
        }

        if(Ret_e != RC_OK)
        {
            ASSERT((t_uint16)Ret_e);
        }
    }

    return Ret_e;
}

//********************************
// s_APPUDS_SendErrorMngmt
//********************************
static t_eReturnCode s_APPUDS_SendEcuRqstResponse(t_bool f_isReqstAccept_b)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 txData_ua8[APPUDS_CLIENT_INFO_MAX_LEN];
    t_uint8 crcCompute_u8;


    //----- Set data to default value ----//
    (void)SafeMem_memclear(txData_ua8, APPUDS_CLIENT_INFO_MAX_LEN);

    txData_ua8[0] = g_8bitsCrcMcuId_u8; // ecuId
    txData_ua8[1] = APPUDS_ID_CLIENT_SERVER_RQST_RESP;
    if(f_isReqstAccept_b == (t_bool)True)
    {
        txData_ua8[2] = (t_uint8)(APPUDS_ID_AKNOWLEDGMENT_OK);
    }
    else 
    {
        txData_ua8[2] = (t_uint8)(APPUDS_ID_AKNOWLEDGMENT_NOT_OK);
    }

    Ret_e = LIBCRC_ComputeCrc8Bits( txData_ua8,
                                    (t_uint16)(APPUDS_CLIENT_INFO_MAX_LEN - 1),
                                    APPUDS_CRC8B_POLYNOME_USED,
                                    APPUDS_CRC8B_STARTVALUE,
                                    &crcCompute_u8);
    if(Ret_e == RC_OK)
    {
        txData_ua8[7] = crcCompute_u8;

        Ret_e = FMKSRL_Transmit(APPUDS_SERIAL_LINE,
                                FMKSRL_TX_ONESHOT,
                                txData_ua8,
                                APPUDS_CLIENT_INFO_MAX_LEN,
                                (t_uint16)0,
                                False);
    }

    if(Ret_e != RC_OK)
    {
        ASSERT((t_uint16)Ret_e);
    }
    

    return Ret_e;
}

//********************************
// s_APPUDS_SendMcuInfo
//********************************
static t_eReturnCode s_APPUDS_SendMcuInfo(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 txData_ua8[APPUDS_CLIENT_INFO_MAX_LEN];
    t_uint8 crcCompute_u8;

    //----- Set data to default value ----//
    (void)SafeMem_memclear(txData_ua8, APPUDS_CLIENT_INFO_MAX_LEN);

    txData_ua8[0] = APPUDS_ID_SERVER_SEND_INFO;
    txData_ua8[1] = (t_uint8)(g_32bitsCrcMcuId_u32 >> 24);
    txData_ua8[2] = (t_uint8)(g_32bitsCrcMcuId_u32 >> 16);
    txData_ua8[3] = (t_uint8)(g_32bitsCrcMcuId_u32 >> 8);
    txData_ua8[4] = (t_uint8)(g_32bitsCrcMcuId_u32);
    txData_ua8[5] = (t_uint8)(SOFTWARE_VERSION >> 8);
    txData_ua8[6] = (t_uint8)(SOFTWARE_VERSION);

    Ret_e = LIBCRC_ComputeCrc8Bits( txData_ua8,
                                    (t_uint16)(APPUDS_CLIENT_INFO_MAX_LEN - 1),
                                    APPUDS_CRC8B_POLYNOME_USED,
                                    APPUDS_CRC8B_STARTVALUE,
                                    &crcCompute_u8);
    if(Ret_e == RC_OK)
    {
        txData_ua8[7] = (t_uint8)(crcCompute_u8);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = FMKSRL_Transmit(APPUDS_SERIAL_LINE,
                                FMKSRL_TX_ONESHOT,
                                txData_ua8,
                                APPUDS_CLIENT_INFO_MAX_LEN,
                                (t_uint16)0,
                                False);
    }

    if(Ret_e != RC_OK)
    {
        ASSERT((t_uint16)Ret_e);
    }

    return Ret_e;
}

#endif // APPSYS_MODULE_APP_UDS_ENABLE
//************************************************************************************
// End of File
//************************************************************************************

/**
 *
 *	@brief
 *	@note   
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
