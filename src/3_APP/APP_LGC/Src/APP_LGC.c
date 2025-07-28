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

#include "Library/SafeMem/SafeMem.h"

// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
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
/**
* @brief Container for Sensors Values
*/
//static t_float32 g_snsValues_af32[APPSNS_SENSOR_NB];
static t_float32 g_snsValues_af32[2];

/**
* @brief Flag to Reset Service State
*/
static t_bool  g_resetSrvState_b = (t_bool)False; 

t_sSafeMem_BlockInfo g_SecBlockSnsValue_as[2];
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
*	@brief      Get Sensors Values.\n
*
*/

static t_eReturnCode s_APPLGC_GetSnsValues(void);
/**
*
*	@brief      Set Actuators Values Depending on g_srvFuncInfo_as
*/
static t_eReturnCode s_APPLGC_SetActValues(void);
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
*/
static t_eReturnCode s_APPLGC_SetActValues(void);
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

    /* CAUTION : Automatic generated code section for Actuators Containers/Service: Start */
    /* CAUTION : Automatic generated code section for Actuators Containers/Service: End */

    //----- Set Service Init -----//
    for(idxSrv_u8 = (t_uint8)0 ; idxSrv_u8 < APPLGC_SRV_NB ; idxSrv_u8++)
    {

        g_srvFuncInfo_as[idxSrv_u8].health_e = APPLGC_SRV_HEALTH_OK;
        g_srvFuncInfo_as[idxSrv_u8].state_e = APPLGC_SRV_STATE_NB;
        
    }

    //---- Set Agent Init -----//
    for(idxAgent_u8 = (t_uint8)0 ; (idxAgent_u8 < APPLGC_AGENT_NB) && (Ret_e == RC_OK) ; idxAgent_u8++)
    {
        Ret_e = c_AppLGc_AgentFunc_apf[idxAgent_u8].init_pcb();
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
 * APPLGC_GetServiceInfo
 *********************************/
t_eReturnCode APPLGC_GetActValue(t_eAPPACT_Actuators f_actuators_e, t_sint32 * f_actValue_ps32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxSrv_u8;
    t_uint8 idxActSrv_u8;
    t_eAPPACT_Actuators actLabel_e;
    t_bool findActVal_b = False;

    if(f_actuators_e >= APPACT_ACTUATOR_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)f_actuators_e);
    }
    if(f_actValue_ps32 == (t_sint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
        ASSERT((t_uint16)0);
    }
    if(Ret_e == RC_OK)
    {
        for(idxSrv_u8 = (t_uint8)0 ; (idxSrv_u8 < APPLGC_SRV_NB) && (Ret_e == RC_OK) ; idxSrv_u8++)
        {
            //----- Loop on every Actuators For this Service -----//
            for(idxActSrv_u8 = (t_uint8)0 ; idxActSrv_u8 < c_AppLGc_SrvActuatorsMax_ua8[idxSrv_u8] ; idxActSrv_u8++)
            {
                actLabel_e = c_AppLGc_SrvDepedencies_pae[idxSrv_u8][idxActSrv_u8];

                if(actLabel_e == f_actuators_e)
                {
                    *f_actValue_ps32 = (t_sint32)g_srvFuncInfo_as[idxSrv_u8].actVal_pau[idxActSrv_u8].setPoint_s32;
                    findActVal_b = True;
                    break;
                }
            }
            if(findActVal_b == (t_bool)True)
            {
                break;
            }
        }
    }

    return Ret_e;
}

/*********************************
 * APPLGC_GetSnsValue
 *********************************/
t_eReturnCode APPLGC_GetSnsValue(t_eAPPSNS_Sensors f_sensors_e, t_sint32 * f_snsValue_ps32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_sensors_e >= APPSNS_SENSOR_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)f_sensors_e);
    }
    if(f_snsValue_ps32 == (t_sint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
        ASSERT((t_uint16)0);
    }
    if(Ret_e == RC_OK)
    {
        *f_snsValue_ps32 = (t_sint32)g_snsValues_af32[f_sensors_e];
    }

    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
static void s_APPLGC_AppEvntCallback(   t_uint8 * f_rxData_pu8, 
                                        t_uint16 f_dataSize_u16, 
                                        t_eFMKSRL_RxCallbackInfo f_InfoCb_e);

static void s_APPLGC_AppEvntCallback(   t_uint8 * f_rxData_pu8, 
                    t_uint16 f_dataSize_u16, 
                    t_eFMKSRL_RxCallbackInfo f_InfoCb_e)
{
    return;
}
/*********************************
 * s_APPLGC_ConfigurationState
 *********************************/
static t_eReturnCode s_APPLGC_ConfigurationState(void)
{

    t_eReturnCode Ret_e;
    
    Ret_e = FMKIO_Set_InAnaSigCfg(  FMKIO_INPUT_SIGANA_1,
                                    NULL_FUNCTION);
    Ret_e = FMKIO_Set_InAnaSigCfg(  FMKIO_INPUT_SIGANA_2,
                                    NULL_FUNCTION);


    

    return Ret_e;
}

/*********************************
 * s_APPLGC_ConfigurationState
 *********************************/
static t_eReturnCode s_APPLGC_PreOperational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    return Ret_e;
}
/*********************************
 * s_APPLGC_Operational
 *********************************/
static t_eReturnCode s_APPLGC_Operational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    
        
        /*t_uint8 idxAgent_u8;
        
        if(g_resetSrvState_b == (t_bool)True)
        {
            Ret_e = s_APPLGC_ResetSrvState();
            if(Ret_e == RC_OK)
        {
            g_resetSrvState_b = (t_bool)False;
        }
    }
    if(Ret_e == RC_OK)
    {
        //------ Get Sensors Values for this cyclic -----//
        Ret_e = s_APPLGC_GetSnsValues();
    }

    //----- Call Agent Periodic Task Depending on Coordinator -----//
    if(Ret_e == RC_OK)
    {   
        for(idxAgent_u8 = (t_uint8)0 ; (idxAgent_u8 < APPLGC_AGENT_NB) &&  (Ret_e >= RC_OK) ; idxAgent_u8++)
        {
            Ret_e = c_AppLGc_AgentFunc_apf[idxAgent_u8].PeriodTask_pcb( (t_float32 *)g_snsValues_af32,
                                                                        (t_sAPPLGC_ServiceInfo *)g_srvFuncInfo_as);
        }
    }

    if(Ret_e >= RC_OK)
    { 
        Ret_e = s_APPLGC_SetActValues();
    }*/
    return Ret_e;
}
/*********************************
 * s_APPLGC_GetSnsValues
 *********************************/
static t_eReturnCode s_APPLGC_GetSnsValues(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sAPPSNS_SnsValueInfo snsInfo_s;
    t_uint8 idxSns_u8 = (t_uint8)0;

    for(idxSns_u8 = (t_uint8)0 ; (idxSns_u8 < APPSNS_SENSOR_NB) && (Ret_e == RC_OK) ; idxSns_u8++)
    {
        //----- Reset Container values -----//
        snsInfo_s.isValueOK_b = (t_bool)False;
        snsInfo_s.rawValue_f32 = (t_float32)0.0;
        snsInfo_s.SnsValue_f32 = (t_float32)0.0;

        Ret_e = APPSNS_Get_SnsValue((t_eAPPSNS_Sensors)idxSns_u8, &snsInfo_s);

        if((Ret_e == RC_OK)
        && (snsInfo_s.isValueOK_b == (t_bool)true))
        {
            g_snsValues_af32[idxSns_u8] = snsInfo_s.SnsValue_f32;
        }
    }
    
    return Ret_e;
}


/*********************************
 * s_APPLGC_SetActValues
 *********************************/
static t_eReturnCode s_APPLGC_SetActValues(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxSrv_u8 = (t_uint8)0;
    t_uint8 idxAct_u8 = (t_uint8)0;
    t_eAPPACT_Actuators actuatorLabel_e;

    //----- Loop on every Service -----//
    for(idxSrv_u8 = (t_uint8)0 ; (idxSrv_u8 < APPLGC_SRV_NB) && (Ret_e == RC_OK) ; idxSrv_u8++)
    {
        //----- Loop on every Actuators For this Service -----//
        for(idxAct_u8 = (t_uint8)0 ; idxAct_u8 < c_AppLGc_SrvActuatorsMax_ua8[idxSrv_u8] ; idxAct_u8++)
        {
            actuatorLabel_e = c_AppLGc_SrvDepedencies_pae[idxSrv_u8][idxAct_u8];

            Ret_e = APPACT_Set_ActValue(actuatorLabel_e, (t_uAPPACT_SetValue)g_srvFuncInfo_as[idxSrv_u8].actVal_pau[idxAct_u8]);

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
    t_eReturnCode Ret_e = RC_OK;

    // choose a way to communicate error

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

