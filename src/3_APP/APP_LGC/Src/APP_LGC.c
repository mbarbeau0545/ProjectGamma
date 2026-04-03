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

///@brief Ecu Position 
static t_eAPPSYS_EcuPos g_EcuPos_e;
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
static void s_APPLGC_AppSigMsgRcvCallback(  t_uint16 f_msgID_u16,
                                            t_uint8 f_nbSignal_u8,
                                            t_eAPPSIG_Signal *f_signal_ae, 
                                            t_float32 *f_sigValue_af32);
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
            g_AppLgc_ModState_e = STATE_CYCLIC_PREOPE;
        }
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

    Ret_e = APPSYS_GetEcuPosition(&g_EcuPos_e);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSYS_AddFastTask(APPSYS_MODULE_APP_LGC, s_APPLGC_FastTask);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_AddRcvMsgCallback(   APPSIG_CAN_MSG_APPLICATIONDIAGNOSTIC4,
                                            APPSIG_MSG_ORIGIN_CAN,
                                            s_APPLGC_AppSigMsgRcvCallback);
    }

    switch(g_EcuPos_e)
    {
        case APPSYS_ECU_POS_GTRY:
            Ret_e = c_AppLgc_AgentInfo_as[APPLGC_AGENT_GANTRY].init_pcb();
        break;
        case APPSYS_ECU_POS_GTRY_HEAD:
            Ret_e = c_AppLgc_AgentInfo_as[APPLGC_AGENT_HEAD_CUTTER].init_pcb();
        break;
        case APPSYS_ECU_POS_MOTION:
            Ret_e = c_AppLgc_AgentInfo_as[APPLGC_AGENT_MOTION].init_pcb();
        break;
    }
    if(Ret_e < RC_OK)
    {
        ASSERT((t_uint16)Ret_e);
    }

    return Ret_e;
}

/*********************************
 * s_APPLGC_ConfigurationState
 *********************************/
static t_eReturnCode s_APPLGC_PreOperational(void)
{
    t_eReturnCode Ret_e;
    t_eCyclicModState actSts_e;
    t_eCyclicModState snsSts_e;

    //---- waiting sns & act module to be in ope state -----//
    Ret_e = APPACT_GetState(&actSts_e);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSNS_GetState(&snsSts_e);
    }
    if(Ret_e == RC_OK)
    {
        if((actSts_e != STATE_CYCLIC_OPE)
        || (snsSts_e != STATE_CYCLIC_OPE))
        {
            Ret_e = RC_WARNING_PENDING;
        }
        else 
        {
            Ret_e = RC_OK;
        }
    }
    
    return Ret_e;
}
/*********************************
 * s_APPLGC_Operational
 *********************************/
static t_eReturnCode s_APPLGC_Operational(void)
{

    t_eReturnCode Ret_e;
    //static t_bool isSent_b = FALSE;

    Ret_e = s_APPLGC_UpdateSnsValues();

    if(Ret_e == RC_OK)
    {
        Ret_e = s_APPLGC_UpdateActValues();
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSYS_GetEcuPosition(&g_EcuPos_e);
    }
    if(Ret_e == RC_OK)
    {
        switch(g_EcuPos_e)
        {
            case APPSYS_ECU_POS_GTRY:
                Ret_e = c_AppLgc_AgentInfo_as[APPLGC_AGENT_GANTRY].PeriodTask_pcb();
            break;
            case APPSYS_ECU_POS_GTRY_HEAD:
                Ret_e = c_AppLgc_AgentInfo_as[APPLGC_AGENT_HEAD_CUTTER].PeriodTask_pcb();
            break;
            case APPSYS_ECU_POS_MOTION:
                Ret_e = c_AppLgc_AgentInfo_as[APPLGC_AGENT_MOTION].PeriodTask_pcb();
            break;
        }
        if(Ret_e < RC_OK)
        {
            ASSERT((t_uint16)Ret_e);
        }
    }
   
    return Ret_e;
}

/*********************************
 * s_APPLGC_UpdateSnsValues
 *********************************/
static t_eReturnCode s_APPLGC_UpdateSnsValues(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxSns_u8 = (t_uint8)0;
    t_sAPPSNS_SnsValueInfo snsValInfo_s;

    for(idxSns_u8 = (t_uint8)0 ; (idxSns_u8 < APPSNS_SNSITF_NB) && (Ret_e == RC_OK) ; idxSns_u8++)
    {
        //----- Reset Container values -----//
        snsValInfo_s.rqstedUnity_u8 = c_APPLGC_SnsIfCompType_au8[idxSns_u8];
        snsValInfo_s.isValueOK_b = FALSE;
        snsValInfo_s.rawValue_f32 = (t_float32)0.0;
        snsValInfo_s.SnsValue_f32 = (t_float32)0.0;

        Ret_e = APPSNS_Get_SnsValue((t_eAPPSNS_SnsInterface)idxSns_u8, &snsValInfo_s);

        if(Ret_e == RC_OK)
        {
            Ret_e = SafeMem_memcpy(&g_snsValues_as[idxSns_u8], &snsValInfo_s, sizeof(t_sAPPSNS_SnsValueInfo));
        }
        else
        {
            //---- meaning not config on this software ----//
            if((Ret_e == RC_WARNING_MISSING_CONFIG)
            || (Ret_e == RC_WARNING_NO_OPERATION))
            {
                Ret_e = RC_OK;
            }
            g_snsValues_as[idxSns_u8].isValueOK_b = FALSE;
            g_snsValues_as[idxSns_u8].rawValue_f32 = 0.0F;
            g_snsValues_as[idxSns_u8].SnsValue_f32 = 0.0F;
        }

        if(Ret_e < RC_OK)
        {
            ASSERT((t_uint16)idxSns_u8);
        }
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

    for(idxAct_u8 = (t_uint8)0 ; (idxAct_u8 < APPACT_ACTITF_NB) && (Ret_e == RC_OK) ; idxAct_u8++)
    {
        //----- Reset Container values -----//
        actValue_f32 = 0.0f;

        Ret_e = APPACT_GetActValue((t_eAPPACT_ActInterface)idxAct_u8, &actValue_f32);
        if(Ret_e == RC_OK)
        {
            g_actValues_as[idxAct_u8].value_f32 = actValue_f32;
            g_actValues_as[idxAct_u8].isValueOK_b = TRUE;
        }
        else if((Ret_e == RC_WARNING_MISSING_CONFIG)
            || (Ret_e == RC_WARNING_NO_OPERATION))
        {
            //---- meaning not config on this software ----//
            Ret_e = RC_OK;
            g_actValues_as[idxAct_u8].value_f32 = 0.0F;
            g_actValues_as[idxAct_u8].isValueOK_b = FALSE;
        }
        else
        {
            if(Ret_e < RC_OK)
            {
                ASSERT((t_uint16)Ret_e);
            }
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
    

    //---- send error to can ----//
    (void)APPSIG_SetSignalValue(APPSIG_SIGNAL_SDM_DIAG_ITEM, (t_float32)f_item_e);
    (void)APPSIG_SetSignalValue(APPSIG_SIGNAL_SDM_DIAG_REPORT_STATUS, (t_float32)f_reportState_e);
    (void)APPSIG_SetSignalValue(APPSIG_SIGNAL_SDM_DIAG_DEBUG_INFO_1, (t_float32)f_debugInfo1_u16);
    (void)APPSIG_SetSignalValue(APPSIG_SIGNAL_SDM_DIAG_DEBUG_INFO_2, (t_float32)f_debugInfo2_u16);

    //---- send error to serial ----//
    #warning special debug
    if(f_item_e == APPSDM_DIAG_ITEM_APPSIG_MSG_TIMEOUT)
    {
        return;
    }
    FMKSRL_LOG("Diag Item %d, status : %d, debug1 : %d, debug2 : %d\r\n",
                f_item_e,
                f_reportState_e,
                f_debugInfo1_u16,
                f_debugInfo2_u16);
    return;
}

/*********************************
 * s_APPLGC_AppSigMsgRcvCallback
 *********************************/
static void s_APPLGC_AppSigMsgRcvCallback(  t_uint16 f_msgID_u16,
                                            t_uint8 f_nbSignal_u8,
                                            t_eAPPSIG_Signal *f_signal_ae, 
                                            t_float32 *f_sigValue_af32)
{
    t_uint8 idxSrv_u8;
    t_uint8 idxActItf_u8;
    t_eReturnCode Ret_e;
    t_uint32 report_item_u32;
    t_eAPPSDM_DiagnosticReport reprtEcuSafety_e;

    if((f_msgID_u16 >= (t_uint16)APPSIG_CAN_MSG_NB)
    || (f_msgID_u16 != (t_uint16)APPSIG_CAN_MSG_APPLICATIONDIAGNOSTIC4))
    {
        ASSERT((t_uint16)f_msgID_u16);
    }
    else if((f_signal_ae == (t_eAPPSIG_Signal *)NULL)
    || (f_sigValue_af32 == (t_float32 *)NULL))
    {
        ASSERT((t_uint16)0);
    }
    else if(g_AppLgc_ModState_e != STATE_CYCLIC_OPE)
    {
        return;
    }
    else 
    {
        if((f_nbSignal_u8 != (t_uint8)4)
        || (f_signal_ae[0] != APPSIG_SIGNAL_SDM_DIAG_ECU_SAFETY_ITEM)
        || (f_signal_ae[1] != APPSIG_SIGNAL_SDM_DIAG_ECU_SAFETY_RPRT_STS)
        || (f_signal_ae[2] != APPSIG_SIGNAL_SDM_DIAG_ECU_SAFETY_DEBUG_INFO_1)
        || (f_signal_ae[3] != APPSIG_SIGNAL_SDM_DIAG_ECU_SAFETY_DEBUG_INFO_2))
        {
            ASSERT((t_uint16)f_nbSignal_u8);
        }
        else 
        {
            //---- if safety ecu is in error we set all service to default ----//
            report_item_u32 = (t_uint32)f_sigValue_af32[0];
            reprtEcuSafety_e = (t_eAPPSDM_DiagnosticReport)f_sigValue_af32[1];
            if((report_item_u32 < CST_MAX_UINT_16BIT)
            && (reprtEcuSafety_e == APPSDM_DIAG_ITEM_REPORT_FAIL))
            {
                FMKSRL_LOG( "[LGC] : Receive diagnostic from EcuSafety, ITEM ->%d, REPORT ->%d\r\n", 
                            (t_sint32)report_item_u32,
                            (t_sint32)reprtEcuSafety_e);
                for(idxSrv_u8 = (t_uint8)0 ; idxSrv_u8 < (t_uint8)APPLGC_SRV_NB ; idxSrv_u8++)
                {
                    (void)APPLGC_SetServiceHealth((t_eAPPLGC_SrvList)idxSrv_u8, APPLGC_SRV_HEALTH_ERROR);
                }

                for(idxActItf_u8 = (t_uint8)0 ; idxActItf_u8 < APPACT_ACTITF_NB ; idxActItf_u8++)
                {
                    Ret_e = APPACT_SetActValue((t_eAPPACT_ActInterface)idxActItf_u8, 0.0F);

                    if(Ret_e != RC_OK)
                    {
                        ASSERT((t_uint16)Ret_e);
                    }
                }
            }
        }
    }

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

