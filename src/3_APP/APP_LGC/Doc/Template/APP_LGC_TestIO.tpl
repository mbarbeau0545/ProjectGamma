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
#include "APP_CFG/ConfigFiles/APPLGC_ConfigPrivate.h"
#include "FMK_HAL/FMK_IO/Src/FMK_IO.h"
#include "FMK_HAL/FMK_HRT/Src/FMK_HRT.h"

#include "Library/SafeMem/SafeMem.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
#define SIGNAL_IN_TEST FMKIO_OUTPUT_SIGPWM_6
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
typedef enum 
{
    TYPETEST_PWM_FREQ_CHANGE = 0x00,
    TYPETEST_PWM_DC_CHANGE,
    TYPETEST_PWM_DC_FREQ_CHANGE,
    TYPERTEST_PWM_PULSE_GEN,
    TYPERTEST_PWM_RAMP_DC,
    TYPERTEST_PWM_RAMP_FREQ,

} t_eAPPLGC_TypeTest;
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
static t_float32 g_snsValues_af32[APPSNS_SNSITF_NB];
/**
* @brief Flag to Reset Service State
*/
static t_bool  g_resetSrvState_b = (t_bool)False; 

static t_eAPPLGC_TypeTest g_TypeTest_e = TYPERTEST_PWM_PULSE_GEN;
static t_bool g_fastTaskON = (t_bool)False;
static t_bool g_pulseFinish_b = (t_bool)True;
static t_uint32 f_finishpulse_u32;
static t_uint32 f_finishpulse1_u32;
static t_uint32 f_finishpulse2_u32;
static t_uint32 f_finishpulse3_u32;
static t_uint32 f_finishpulse4_u32;
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

static void s_APPLGC_Callback(t_eFMKIO_OutPwmSig f_signal_e);
/*static void s_APPLGC_Callback_1(t_eFMKIO_OutPwmSig f_signal_e);
static void s_APPLGC_Callback_2(t_eFMKIO_OutPwmSig f_signal_e);
static void s_APPLGC_Callback_3(t_eFMKIO_OutPwmSig f_signal_e);
static void s_APPLGC_Callback_4(t_eFMKIO_OutPwmSig f_signal_e);*/
static void s_APPLGC_FastTask(t_eFMKTIM_InterruptLineType f_InterruptType_e, t_uint8 f_InterruptLine_u8);


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
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************

/*********************************
 * s_APPLGC_ConfigurationState
 *********************************/
static t_eReturnCode s_APPLGC_ConfigurationState(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sLIBRamp_RampCfg rampcfg_s = {
        .rampMode_e = LIBRAMP_MODE_SIGMOIDALE,
        .rampInfo_u.sigmoidaleCfg_s.kFactor_f32 = 0.2,
        .rampInfo_u.sigmoidaleCfg_s.slopSpeed_f32 = 5.0 * 1000.0,
        .startValue_f32 = 0,
        .totalSteps_u32 = 200
    };
    t_sFMKIO_PwmWaveformCfg waveform_s = {
        .deadTime_u32 = 0,
        .frequency_f32 = 1000,
        .polarity_e = FMKIO_SIGPWM_POLARITY_HIGH,
        .pullMode_e = FMKIO_PULL_MODE_DISABLE,
        .spdMode_e = FMKIO_SPD_MODE_HIGH
    };

    t_sFMKIO_PwmControlPrm controlPwm_s = {
        .ctrlType_e = FMKIO_PWM_CTRL_TYPE_UNUSED,
        .enablePulseSyncOpe_b = TRUE,
        .rampCfg_ps = &rampcfg_s
    };

   
    Ret_e = FMKIO_Set_OutPwmSigCfg  (   SIGNAL_IN_TEST,
                                        waveform_s,
                                        controlPwm_s,
                                        s_APPLGC_Callback,
                                        NULL_FUNCTION);

    Ret_e = FMKIO_Set_OutPwmSigCfg  (   FMKIO_OUTPUT_SIGPWM_7,
                                        waveform_s,
                                        controlPwm_s,
                                        s_APPLGC_Callback,
                                        NULL_FUNCTION);

    // Ret_e = FMKTIM_Set_EvntTimerCfg(FMKTIM_INTERRUPT_LINE_EVNT_1, 
    //                         (t_uint32)5,
    //                         s_APPLGC_FastTask);
    return Ret_e;
}

/*********************************
 * s_APPLGC_ConfigurationState
 *********************************/
static t_eReturnCode s_APPLGC_PreOperational(void)
{
    t_eReturnCode Ret_e = RC_OK;

    if(g_TypeTest_e == TYPETEST_PWM_FREQ_CHANGE || g_TypeTest_e == TYPERTEST_PWM_RAMP_FREQ)
    {
        Ret_e = FMKIO_Set_OutPwmSigDutyCycle(SIGNAL_IN_TEST,
                                    500);
    }
    if(g_fastTaskON == True)
    {
        Ret_e = FMKTIM_Set_EvntLineState(   FMKTIM_INTERRUPT_LINE_EVNT_1,
                                            FMKTIM_EVNT_OPE_START_TIMER);
    }
    
    
    return Ret_e;
}

/*********************************
 * s_APPLGC_Operational
 *********************************/
static void s_APPLGC_FastTask(t_eFMKTIM_InterruptLineType f_InterruptType_e, t_uint8 f_InterruptLine_u8)
{
    static t_uint32 frequency_u32  = 1000;
    static t_uint16 pulses_u16 = 0;
    static t_uint16 dutycycle_u16 = 100;
    static t_uint32 saveTime_u32 = 0;
    t_uint32 currentTime_u32; 

    FMKCPU_GetTick(&currentTime_u32);
    switch(g_TypeTest_e)
    {
        case  TYPETEST_PWM_FREQ_CHANGE:
        {
            if((currentTime_u32 - saveTime_u32) > 1000)
            {
                saveTime_u32 = currentTime_u32;

                if(frequency_u32 > 60000)
                {
                    frequency_u32 = 60000;
                }
                else 
                {
                    frequency_u32 += 5000;
                }
                FMKIO_Set_OutPwmSigFrequency(SIGNAL_IN_TEST,
                                            frequency_u32);
            }
            
            break;
        }
        case  TYPETEST_PWM_DC_CHANGE:
        {
            if((currentTime_u32 - saveTime_u32) > 2000)
            {
                saveTime_u32 = currentTime_u32;

                //saveTime_u32 = currentTime_u32;
                dutycycle_u16 += 100;
                if(dutycycle_u16 > 1000)
                {
                    dutycycle_u16 = 0;
                }
                FMKIO_Set_OutPwmSigDutyCycle(SIGNAL_IN_TEST,
                                        dutycycle_u16);
            }
                
            break;
        }
        case TYPETEST_PWM_DC_FREQ_CHANGE:
        {  
            if((currentTime_u32 - saveTime_u32) > 2000)
            {
                saveTime_u32 = currentTime_u32;

                frequency_u32 += 100;
                FMKIO_Set_OutPwmSigFrequency(SIGNAL_IN_TEST,
                                            frequency_u32);
                dutycycle_u16 += 10;
                if(dutycycle_u16 > 1000)
                {
                    dutycycle_u16 = 1000;
                }
                FMKIO_Set_OutPwmSigDutyCycle(SIGNAL_IN_TEST,
                                        dutycycle_u16);
            }
            break;
        }
        case TYPERTEST_PWM_PULSE_GEN:
        {
            if(g_pulseFinish_b == (t_bool)True)
            {
                if((currentTime_u32 - saveTime_u32) > 1000)
                {
                    saveTime_u32 = currentTime_u32;
                    FMKIO_Set_OutPwmSigPulses(SIGNAL_IN_TEST,
                                                500,
                                                500,
                                                10000);
                }
            }
            break;
        }

        
    }
    return;
}
/*********************************
 * s_APPLGC_Operational
 *********************************/
static t_eReturnCode s_APPLGC_Operational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_uint32 frequency_u32  = 1000;
    static t_uint16 pulses_u16 = 0;
    static t_uint16 dutycycle_u16 = 100;
    static t_uint32 saveTime_u32 = 0;
    t_uint32 currentTime_u32; 

    FMKCPU_GetTick(&currentTime_u32);
    switch(g_TypeTest_e)
    {
        case  TYPETEST_PWM_FREQ_CHANGE:
        {
            if( frequency_u32 >= 30000)
            {
                frequency_u32 = 1000;
        
            }
        
            if((currentTime_u32 - saveTime_u32) > 1000)
            {
                saveTime_u32 = currentTime_u32;
                frequency_u32 += 500;
                FMKIO_Set_OutPwmSigFrequency(SIGNAL_IN_TEST,
                                            frequency_u32);
            }
            break;
        }
        case  TYPETEST_PWM_DC_CHANGE:
        {
            if( dutycycle_u16 >= 1000)
            {
                dutycycle_u16 = 100;
        
            }
        
            if((currentTime_u32 - saveTime_u32) > 1000)
            {
                saveTime_u32 = currentTime_u32;
                dutycycle_u16 += 100;
                FMKIO_Set_OutPwmSigDutyCycle(SIGNAL_IN_TEST,
                                            dutycycle_u16);
            }
            break;
        }
        case TYPETEST_PWM_DC_FREQ_CHANGE:
        {
            if( frequency_u32 >= 30000)
            {
                frequency_u32 = 1000;
        
            }
            if( dutycycle_u16 >= 1000)
            {
                dutycycle_u16 = 100;
        
            }
            if((currentTime_u32 - saveTime_u32) > 1000)
            {
                //saveTime_u32 = currentTime_u32;
                frequency_u32 += 500;
                FMKIO_Set_OutPwmSigFrequency(SIGNAL_IN_TEST,
                                            frequency_u32);
                dutycycle_u16 += 100;
                FMKIO_Set_OutPwmSigDutyCycle(SIGNAL_IN_TEST,
                                        dutycycle_u16);
            }
            
            break;
        }
        case  TYPERTEST_PWM_PULSE_GEN:
        {
            if(g_pulseFinish_b == (t_bool)True)
            {
                if((currentTime_u32 - f_finishpulse_u32) > 3000)
                {
                    saveTime_u32 = currentTime_u32;
                    g_pulseFinish_b = False;
                    FMKIO_Set_OutPwmSigPulses(SIGNAL_IN_TEST,
                                                100,
                                                500,
                                                1000);
                }
            }
            /*if(((currentTime_u32 - saveTime_u32) > 1000)
            && (g_pulseFinish_b == False))
            {
                FMKIO_Set_OutPwmSigPulses(SIGNAL_IN_TEST,
                    500,
                    0);
            }*/
            break;
        }

        case TYPERTEST_PWM_RAMP_DC:
            if((currentTime_u32 - saveTime_u32) > 2000)
            {
                saveTime_u32 = currentTime_u32;
                if(dutycycle_u16 > 500)
                {
                    dutycycle_u16 = 0;
                }
                else 
                {
                    dutycycle_u16 = 950;
                }
                FMKIO_Set_OutPwmSigDutyCycle(SIGNAL_IN_TEST,
                                                dutycycle_u16);
            }
        break;
        case TYPERTEST_PWM_RAMP_FREQ:
            if((currentTime_u32 - saveTime_u32) > 2000)
            {
                saveTime_u32 = currentTime_u32;
                if(frequency_u32 > 30000)
                {
                    frequency_u32 = 3000;
                }
                else 
                {
                    frequency_u32 = 50000;
                }
                FMKIO_Set_OutPwmSigFrequency(SIGNAL_IN_TEST,
                                            frequency_u32);
            }
        break;
    }
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

/*********************************
 * s_APPLGC_Callback
 *********************************/
static void s_APPLGC_Callback(t_eFMKIO_OutPwmSig f_signal_e)
{
    g_pulseFinish_b = True;
    FMKCPU_GetTick(&f_finishpulse_u32);
    return;
}

/*static void s_APPLGC_Callback_1(t_eFMKIO_OutPwmSig f_signal_e)
{

    FMKCPU_GetTick(&f_finishpulse1_u32);
    return;
}

static void s_APPLGC_Callback_2(t_eFMKIO_OutPwmSig f_signal_e)
{
    
    FMKCPU_GetTick(&f_finishpulse2_u32);
    return;
}
static void s_APPLGC_Callback_3(t_eFMKIO_OutPwmSig f_signal_e)
{
    FMKCPU_GetTick(&f_finishpulse3_u32);
    return;
}
static void s_APPLGC_Callback_4(t_eFMKIO_OutPwmSig f_signal_e)
{
    FMKCPU_GetTick(&f_finishpulse4_u32);
    return;
}*/
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

