/*********************************************************************
 * @file        APP_LGC.c
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */






// ********************************************************************
// *                      Includes
// ********************************************************************
#include "stdio.h"
#include "string.h"

#include "./APP_LGC.h"
#include "./APP_CTRL/APP_SYS/Src/APP_SYS.h"
#include "APP_CFG/ConfigFiles/APPLGC_ConfigPrivate.h"
#include "3_APP/APP_CTRL/APP_SPM/Src/APP_SPM.h"
#include "FMK_HAL/FMK_IO/Src/FMK_IO.h"
#include "FMK_HAL/FMK_HRT/Src/FMK_HRT.h"
#include "FMK_HAL/FMK_CAN/Src/FMK_FDCAN.h"
#include "APP_CTRL/APP_SIG/Src/APP_SIG.h"

#include "Library/SafeMem/SafeMem.h"
#include "CL42T/Src/CL42T.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************

/// @brief structure to get actuators value
typedef struct 
{
    t_float32 value_f32;
    t_bool isValueOK_b;
} t_sAPPLGC_ActIfInfo;

/// @brief Agent Ordonnancer Information
typedef struct 
{
    t_uint32 prdTskMs_u32;          //---- Periodicity ask by the agent ----//
    t_uint32 lastExecMs_u32;        //---- Last time the agent was executed -----//
    t_bool isActive_b;
    t_sAPPLGC_AgentFunc * AgCfg_ps;
} t_sAPPLGC_AgentInfo;
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------ENUM TYPES-----------------------------//


/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//

/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************
/**
* @brief App Logic Module State
*/
static t_eCyclicModState g_AppLgc_ModState_e = STATE_CYCLIC_CFG;
/**
* @brief Structure for Service Information 
*/
static t_sAPPLGC_ServiceInfo g_srvFuncInfo_as[APPLGC_SRV_NB]; 

///@brief sensors info
static t_sAPPSNS_SnsValueInfo g_snsValues_as[APPSNS_SNSITF_NB];
///@brief actuators info
static t_sAPPLGC_ActIfInfo g_actValues_as[APPACT_ACTITF_NB];
/**
* @brief Flag to Reset Service State
*/
static t_bool  g_resetSrvState_b = (t_bool)FALSE; 

/* CAUTION : Automatic generated code section for Variable: Start */
/* CAUTION : Automatic generated code section for Variable: End */
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
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
static t_eReturnCode s_APPLGC_PreOperational(void);
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
static t_eReturnCode s_APPLGC_Operational(void);
/**
*
*	@brief
*	@note
*	 
*
*
*/
static t_eReturnCode s_APPLGC_ConfigurationState(void);
/**
*	@brief      Get Sensors Values.\n
*/
static t_eReturnCode s_APPLGC_UpdateActValues(void);
/**
*
*	@brief      Get Sensors Values.\n
*
*/

static t_eReturnCode s_APPLGC_UpdateSnsValues(void);
/**
*
*	@brief
*	@note   
*
*
*/
static t_eReturnCode s_APPLGC_ResetSrvState(void);
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
static void s_APPLGC_DiagnosticEvent(   t_eAPPSDM_DiagnosticItem f_item_e,
                                        t_eAPPSDM_DiagnosticReport f_reportState_e,
                                        t_uint16 f_debugInfo1_u16,
                                        t_uint16 f_debugInfo2_u16);

static void s_APPLGC_FastTask(void);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************

/*********************************
 * APPLGC_Init
 *********************************/
t_eReturnCode APPLGC_Init(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxAgent_u8 = (t_uint8)0; 
    t_uint8 idxSrv_u8 = (t_uint8)0;

    //----- Set Service Init -----//
    for(idxSrv_u8 = (t_uint8)0 ; idxSrv_u8 < APPLGC_SRV_NB ; idxSrv_u8++)
    {
        g_srvFuncInfo_as[idxSrv_u8].health_e = APPLGC_SRV_HEALTH_OK;
        g_srvFuncInfo_as[idxSrv_u8].state_e = APPLGC_SRV_STATE_NB;        
    }

    Ret_e = APPSDM_AddCallbackEvnt(s_APPLGC_DiagnosticEvent);

    return Ret_e;
}

/*********************************
 * APPLGC_Cyclic
 *********************************/
t_eReturnCode APPLGC_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;
    // code to run every x milliseconds, config in APPSYS_ConfigPrivate.h

    switch (g_AppLgc_ModState_e)
    {
    case STATE_CYCLIC_CFG:
    {
        Ret_e = s_APPLGC_ConfigurationState();
        if(Ret_e == RC_OK)
        {
            g_AppLgc_ModState_e = STATE_CYCLIC_WAITING;
        }
        break;
    }

    case STATE_CYCLIC_WAITING:
    {
        // nothing to do, just wait all module are Ope
        break;
    }
    case STATE_CYCLIC_PREOPE:
    {
        Ret_e = s_APPLGC_PreOperational();

        if(Ret_e == RC_OK)
        {
            g_AppLgc_ModState_e = STATE_CYCLIC_OPE;
        }
    
        break;
    }
    case STATE_CYCLIC_OPE:
    {
        Ret_e = s_APPLGC_Operational();
        break;
    }
    case STATE_CYCLIC_ERROR:
    {
        break;
    }
    case STATE_CYCLIC_BUSY:
    default:
        Ret_e = RC_OK;
        break;
    }
    return Ret_e;
}

/*********************************
 * APPLGC_GetState
 *********************************/
t_eReturnCode APPLGC_GetState(t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_AppLgc_ModState_e;
    }

    return Ret_e;
}

/*********************************
 * APPLGC_SetState
 *********************************/
t_eReturnCode APPLGC_SetState(t_eCyclicModState f_State_e)
{

    g_AppLgc_ModState_e = f_State_e;

    return RC_OK;
}

/*********************************
 * APPLGC_SetServiceHealth
 *********************************/
t_eReturnCode APPLGC_SetServiceHealth(t_eAPPLGC_SrvList f_service_e, t_eAPPLGC_SrvHealth f_srvHealth_e)
{
    t_eReturnCode Ret_e = RC_OK;

    if((f_service_e >= APPLGC_SRV_NB)
    || (f_srvHealth_e >= APPLGC_SRV_HEALTH_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        //----- set Health state -----//
        g_srvFuncInfo_as[f_service_e].health_e = f_srvHealth_e; 
    }

    return Ret_e;
}

/*********************************
 * APPLGC_SetServiceHealth
 *********************************/
t_eReturnCode APPLGC_GetServiceHealth(t_eAPPLGC_SrvList f_service_e, t_eAPPLGC_SrvHealth * f_srvHealth_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_service_e >= APPLGC_SRV_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_srvHealth_pe == (t_eAPPLGC_SrvHealth *)NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        *f_srvHealth_pe = g_srvFuncInfo_as[f_service_e].health_e;
    }

    return Ret_e;
}

/*********************************
 * APPLGC_GetSnsValue
 *********************************/
t_eReturnCode APPLGC_GetSnsValue(t_eAPPSNS_SnsInterface f_snsIfID_e, t_float32 * f_snsValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_snsIfID_e >= APPSNS_SNSITF_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)f_snsIfID_e);
    }
    if(f_snsValue_pf32 == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
        ASSERT((t_uint16)0);
    }
    if(Ret_e == RC_OK)
    {
        if(g_snsValues_as[f_snsIfID_e].isValueOK_b == TRUE)
        {
            *f_snsValue_pf32 = g_snsValues_as[f_snsIfID_e].SnsValue_f32;
        }
        else
        {
            *f_snsValue_pf32 = 0.0f;
            Ret_e = RC_WARNING_WRONG_RESULT;
        }
    }

    return Ret_e;
}

/*********************************
 * APPLGC_GetActValue
 *********************************/
t_eReturnCode APPLGC_GetActValue(t_eAPPACT_ActInterface f_actIfID_e, t_float32 * f_actValue_pf32)
{
    {
    t_eReturnCode Ret_e = RC_OK;

    if(f_actIfID_e >= APPACT_ACTITF_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)f_actIfID_e);
    }
    if(f_actValue_pf32 == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
        ASSERT((t_uint16)0);
    }
    if(Ret_e == RC_OK)
    {
        if(g_actValues_as[f_actIfID_e].isValueOK_b == TRUE)
        {
            *f_actValue_pf32 = g_actValues_as[f_actIfID_e].value_f32;
        }
        else
        {
            *f_actValue_pf32 = 0.0f;
            Ret_e = RC_WARNING_WRONG_RESULT;
        }
    }

    return Ret_e;
}
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_APPLGC_ConfigurationState
 *********************************/
static t_eReturnCode s_APPLGC_ConfigurationState(void)
{

    t_eReturnCode Ret_e;

    //Ret_e = APPSYS_AddFastTask(APPSYS_MODULE_APP_LGC, s_APPLGC_FastTask);
    
    return Ret_e;
}

/*********************************
 * s_APPLGC_ConfigurationState
 *********************************/
static t_eReturnCode s_APPLGC_PreOperational(void)
{
    t_eReturnCode Ret_e = RC_OK;

    // if(Ret_e == RC_OK)
    // {
    //     Ret_e = APPSYS_SetFastTaskState(APPSYS_MODULE_APP_LGC, APPSYS_FAST_TASK_ENABLE);
    // }

    return Ret_e;
}
/*********************************
 * s_APPLGC_Operational
 *********************************/
static t_eReturnCode s_APPLGC_Operational(void)
{

    t_eReturnCode Ret_e;
    t_uint8 data_u8[8] = {0,1,2,3,4,5,6,7};
    t_sFMKFDCAN_TxItem txItem_s = {
        .BitRate_e = FMKFDCAN_BITRATE_SWITCH_OFF,
        .frameFormat_e = FMKFDCAN_FRAME_FORMAT_CLASSIC,
        .ItemId_s.FramePurpose_e = FMKFDCAN_FRAME_PURPOSE_DATA,
        .ItemId_s.Identifier_u32 = 0x18FF999,
        .ItemId_s.IdType_e = FMKFDCAN_IDTYPE_EXTENDED,
        .CanMsg_s.Direction_e = FMKFDCAN_NODE_DIRECTION_TX,
        .CanMsg_s.Dlc_e = FMKFDCAN_DLC_8,
        .CanMsg_s.data_pu8 = data_u8

    };

    Ret_e = FMKFDCAN_SendTxItem(FMKFDCAN_NODE_1, txItem_s);
    return Ret_e;
}

/*********************************
 * s_APPLGC_UpdateSnsValues
 *********************************/
static t_eReturnCode s_APPLGC_UpdateSnsValues(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxSns_u8 = (t_uint8)0;

    for(idxSns_u8 = (t_uint8)0 ; (idxSns_u8 < APPSNS_SNSITF_NB) && (Ret_e >= RC_OK) ; idxSns_u8++)
    {
        //----- Reset Container values -----//
        g_snsValues_as[idxSns_u8].rqstedUnity_u8 = c_APPLGC_SnsIfCompType_au8[idxSns_u8];
        g_snsValues_as[idxSns_u8].isValueOK_b = FALSE;
        g_snsValues_as[idxSns_u8].rawValue_f32 = (t_float32)0.0;
        g_snsValues_as[idxSns_u8].SnsValue_f32 = (t_float32)0.0;

        Ret_e = APPSNS_Get_SnsValue((t_eAPPSNS_SnsInterface)idxSns_u8, &g_snsValues_as[idxSns_u8]);
    }
    
    return Ret_e;
}

/*********************************
 * s_APPLGC_UpdateSnsValues
 *********************************/
static t_eReturnCode s_APPLGC_UpdateActValues(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxAct_u8 = (t_uint8)0;
    t_float32 actValue_f32;

    for(idxAct_u8 = (t_uint8)0 ; (idxAct_u8 < APPSNS_SNSITF_NB) && (Ret_e >= RC_OK) ; idxAct_u8++)
    {
        //----- Reset Container values -----//
        actValue_f32 = 0.0f;

        Ret_e = APPACT_GetActValue((t_eAPPACT_ActInterface)idxAct_u8, &actValue_f32);
        if(Ret_e == RC_OK)
        {
            g_actValues_as[idxAct_u8].value_f32 = actValue_f32;
            g_actValues_as[idxAct_u8].isValueOK_b = TRUE;
        }
        else
        {
            g_actValues_as[idxAct_u8].value_f32 = 0.0f;
            g_actValues_as[idxAct_u8].isValueOK_b = FALSE;
        }
    }
    
    return Ret_e;
}

/*********************************
 * s_APPLGC_ResetSrvState
 *********************************/
static t_eReturnCode s_APPLGC_ResetSrvState(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxSrv_u8;

    Ret_e = APPSDM_ResetDiagEvnt();

    if(Ret_e == RC_OK)
    {
        for(idxSrv_u8 = (t_uint8)0 ; 
            (idxSrv_u8 < APPLGC_SRV_NB)
        &&  (Ret_e == RC_OK) ; 
        idxSrv_u8++)
        {
            Ret_e = APPLGC_SetServiceHealth((t_eAPPLGC_SrvList)idxSrv_u8, 
                                            APPLGC_SRV_HEALTH_OK);
        }
    }

    return Ret_e;
}

/*********************************
 * s_APPLGC_DiagnosticEvent
 *********************************/
static void s_APPLGC_DiagnosticEvent(   t_eAPPSDM_DiagnosticItem f_item_e,
                                        t_eAPPSDM_DiagnosticReport f_reportState_e,
                                        t_uint16 f_debugInfo1_u16,
                                        t_uint16 f_debugInfo2_u16)
{
    FMKSRL_LOG("Diag Item %d, status : %d, debug1 : %d, debug2 : %d\r\n",
                f_item_e,
                f_reportState_e,
                f_debugInfo1_u16,
                f_debugInfo2_u16);

    return;
}

/*********************************
 * s_APPLGC_FastTask
 *********************************/
static void s_APPLGC_FastTask(void)
{
    return;
}
//************************************************************************************
// End of File
//************************************************************************************

/**
 *
 *	@brief
 *	@note   
 *
 *
 *	@params[in] 
 *	@params[out]
 *	 
 *
 *
 */

