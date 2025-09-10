/*********************************************************************
 * @file        TemplateName.c
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
/* CAUTION : Automatic generated code section for Include: Start */
#include "./APPACT_SPEC_MTR_XR.h"
/* CAUTION : Automatic generated code section for Include: End */
#include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
#include "APP_CFG/ConfigFiles/APPACT_ConfigPublic.h"
#include "CL42T/Src/CL42T.h"
#include "APP_CTRL/APP_SDM/Src/APP_SDM.h"

// ********************************************************************
// *                      Defines
// ********************************************************************
///@brief ENable motor XL Dead Time
#define APPACT_SPEC_MOTOR_XL_ENABLE_DEADTIME TRUE

///@brief To go in opposite direction than XL
#define APPACT_SPEC_MOTOR_XR_DIR ((t_sint32)-1)
/* CAUTION : Automatic generated code section for Include: Start */

/* CAUTION : Automatic generated code section for Include: End */
// ********************************************************************
// *                      Types
// ********************************************************************
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------ENUM TYPES-----------------------------//


/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
///@brief structure to send the iteration for CL42T (required)
typedef struct 
{
    t_sint32 nbPulses_s32;
    t_uint32 frequency_f32;
    t_uint32 trigTimer_u32;
    t_bool isPulsesRcv_b;
    t_bool isFreqRcv_b;
    t_bool isTrigTimerRcv_b;
} t_sAPPACT_SPEC_CL42T_ShadowCmd;
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************
const static t_eCL42T_MotorId c_MtrXL_CL42T_Id = CL42T_MOTOR_2;

static t_eAPPSYS_OptActMtrXl g_MtrXL_OptCfg_e = APPSYS_OPT_ACT_MTR_XR_NB;

static t_sAPPACT_SPEC_CL42T_ShadowCmd g_cl42tShadowCmd_s;
static t_sint32 g_doppPulses_s32;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
 * @brief Set CL42T Motor Configuration 
 */
static t_eReturnCode s_APPACT_SPEC_CL42T_Cfg(void);
/**
 * @brief Set CL42T Motor Configuration 
 */
static t_eReturnCode s_APPACT_SPEC_CL42T_GetMtrInfo(t_float32 * f_mtrValue_pf32);
/**
 * @brief Set CL42T Healh 
 */
static void s_APPACT_SPEC_CL42T_HealthCallback(t_eCL42T_MotorId f_MotorID_e, t_eCL42T_DiagError f_defaultInfo_e);
/**
 * @brief Set Pulse Dropped Callback
 */
static void s_APPACT_SPEC_CL42T_PulseDroppedCallback(t_eCL42T_MotorId f_MotorID_e, 
                                                     t_uint16 f_pulseDropped_u16, 
                                                     t_eCL42T_MotorDirection f_direction_e);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/* CAUTION : Automatic generated code section for Specific Function Implementation: Start */


/******************************************
* APPACT_SPEC_MTR_XR_SetCfg
******************************************/
t_eReturnCode APPACT_SPEC_MTR_XR_SetCfg(t_uint8 f_actDvcOpt_u8, t_eAPPACT_ActDriverList *f_drvUsed_pe)
{
    t_eReturnCode Ret_e;

    if(f_drvUsed_pe == (t_eAPPACT_ActDriverList *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else 
    {
        //    Your code for MTR_XL_SetActCfg here
        switch(f_actDvcOpt_u8)
        {
            case APPSYS_OPT_ACT_MTR_XR_CL42T:
                Ret_e = s_APPACT_SPEC_CL42T_Cfg();
                if(Ret_e == RC_OK)
                {
                    *f_drvUsed_pe = APPACT_DRV_CL42T;
                    g_cl42tShadowCmd_s.isPulsesRcv_b = FALSE;
                    g_cl42tShadowCmd_s.isFreqRcv_b = FALSE;
                    g_cl42tShadowCmd_s.isTrigTimerRcv_b = FALSE;
                    g_doppPulses_s32 = (t_sint32)0;
                }
            break;
            case APPSYS_OPT_ACT_MTR_XR_UNUSED:
                Ret_e = RC_WARNING_NO_OPERATION;
            break;
            case APPSYS_OPT_ACT_MTR_XR_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
            break;
        }
        if(Ret_e == RC_OK)
        {
            g_MtrXL_OptCfg_e = f_actDvcOpt_u8;
        }
    }

    return Ret_e;
}



/******************************************
* APPACT_SPEC_MTR_XR_PULSE_GetValue
******************************************/
t_eReturnCode APPACT_SPEC_MTR_XR_PULSE_GetValue(t_float32 *f_rawSigValue_pf32)
{
    t_eReturnCode Ret_e;
    //    Your code for MTR_XL_GetIfValue here
    switch(g_MtrXL_OptCfg_e)
        {
            case APPSYS_OPT_ACT_MTR_XR_CL42T:
                //---- We give the pulses that has been dropped ----//
                *f_rawSigValue_pf32 = (t_float32)g_doppPulses_s32;
                Ret_e = RC_OK;
            break;
            case APPSYS_OPT_ACT_MTR_XR_UNUSED:
                *f_rawSigValue_pf32 = 0.0f;
                Ret_e = RC_WARNING_NO_OPERATION;
            break;
            case APPSYS_OPT_ACT_MTR_XR_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
            break;
        }


    return Ret_e;
}



/******************************************
* APPACT_SPEC_MTR_XR_PULSE_SetValue
******************************************/
t_eReturnCode APPACT_SPEC_MTR_XR_PULSE_SetValue(t_float32 f_SigValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_SetMotorValue cl42T_MtrVal_s;
    //    Your code for MTR_XL_SetIfValue here

    switch(g_MtrXL_OptCfg_e)
        {
            case APPSYS_OPT_ACT_MTR_XR_CL42T:
                g_cl42tShadowCmd_s.nbPulses_s32 = (t_sint32)(f_SigValue_pf32 + 0.5f);
                g_cl42tShadowCmd_s.isPulsesRcv_b = TRUE;
                if((g_cl42tShadowCmd_s.isFreqRcv_b == TRUE)
                && (g_cl42tShadowCmd_s.isTrigTimerRcv_b == TRUE))
                {
                    cl42T_MtrVal_s.triggerTimer_u32 = g_cl42tShadowCmd_s.trigTimer_u32;
                    cl42T_MtrVal_s.frequency_f32 = g_cl42tShadowCmd_s.frequency_f32;
                    cl42T_MtrVal_s.nbPulses_s32 = g_cl42tShadowCmd_s.nbPulses_s32 * APPACT_SPEC_MOTOR_XR_DIR;

                    Ret_e = CL42T_SetMotorSigValue( c_MtrXL_CL42T_Id,
                                                    cl42T_MtrVal_s);
                    //---- even if ret_e != RC_OK, we reset the flag ----//
                    g_cl42tShadowCmd_s.isFreqRcv_b = FALSE;
                    g_cl42tShadowCmd_s.isPulsesRcv_b = FALSE;
                    g_cl42tShadowCmd_s.isTrigTimerRcv_b = FALSE;
                }
            break;
            case APPSYS_OPT_ACT_MTR_XR_UNUSED:
                Ret_e = RC_WARNING_NO_OPERATION;
            break;
            case APPSYS_OPT_ACT_MTR_XR_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
            break;
        }

    return Ret_e;
}



/******************************************
* APPACT_SPEC_MTR_XR_SPEED_GetValue
******************************************/
t_eReturnCode APPACT_SPEC_MTR_XR_SPEED_GetValue(t_float32 *f_rawSigValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for MTR_XL_GetIfValue here
    switch(g_MtrXL_OptCfg_e)
        {
            case APPSYS_OPT_ACT_MTR_XR_CL42T:
                Ret_e = s_APPACT_SPEC_CL42T_GetMtrInfo(f_rawSigValue_pf32);
            break;
            case APPSYS_OPT_ACT_MTR_XR_UNUSED:
                Ret_e = RC_WARNING_NO_OPERATION;
            break;
            case APPSYS_OPT_ACT_MTR_XR_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
            break;
        }


    return Ret_e;
}



/******************************************
* APPACT_SPEC_MTR_XR_SPEED_SetValue
******************************************/
t_eReturnCode APPACT_SPEC_MTR_XR_SPEED_SetValue(t_float32 f_SigValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_SetMotorValue cl42T_MtrVal_s;
    //    Your code for MTR_XL_SetIfValue here
    switch(g_MtrXL_OptCfg_e)
        {
            case APPSYS_OPT_ACT_MTR_XR_CL42T:
                if(f_SigValue_pf32 == APPACT_SOFT_STOP)
                {
                    Ret_e = CL42T_SetMotorState(c_MtrXL_CL42T_Id, CL42T_MOTOR_STATE_OFF, FALSE);
                }
                else if(f_SigValue_pf32 == APPACT_HARD_STOP)
                {
                    Ret_e = CL42T_SetMotorState(c_MtrXL_CL42T_Id, CL42T_MOTOR_STATE_OFF, TRUE);
                }
                else if(f_SigValue_pf32 == APPACT_ENABLE_MOTOR)
                {
                    Ret_e = CL42T_SetMotorState(c_MtrXL_CL42T_Id, CL42T_MOTOR_STATE_ON, FALSE);
                } 
                else
                {       
                     g_cl42tShadowCmd_s.frequency_f32 = f_SigValue_pf32;
                    g_cl42tShadowCmd_s.isFreqRcv_b = TRUE;
                    if((g_cl42tShadowCmd_s.isPulsesRcv_b == TRUE)
                    && g_cl42tShadowCmd_s.isTrigTimerRcv_b == TRUE)
                    {
                        cl42T_MtrVal_s.triggerTimer_u32 = g_cl42tShadowCmd_s.trigTimer_u32;
                        cl42T_MtrVal_s.frequency_f32 = g_cl42tShadowCmd_s.frequency_f32;
                        cl42T_MtrVal_s.nbPulses_s32 = g_cl42tShadowCmd_s.nbPulses_s32 * APPACT_SPEC_MOTOR_XR_DIR;

                        Ret_e = CL42T_SetMotorSigValue( c_MtrXL_CL42T_Id,
                                                        cl42T_MtrVal_s);
                        //---- even if ret_e != RC_OK, we reset the flag ----//
                        g_cl42tShadowCmd_s.isFreqRcv_b = FALSE;
                        g_cl42tShadowCmd_s.isPulsesRcv_b = FALSE;
                        g_cl42tShadowCmd_s.isTrigTimerRcv_b = FALSE;
                    }
                }
            break;
            case APPSYS_OPT_ACT_MTR_XR_UNUSED:
                Ret_e = RC_WARNING_NO_OPERATION;
            break;
            case APPSYS_OPT_ACT_MTR_XR_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
            break;
        }


    return Ret_e;
}

/******************************************
* APPACT_SPEC_MTR_XR_TRIGTIME_GetValue
******************************************/
t_eReturnCode APPACT_SPEC_MTR_XR_TRIGTIME_GetValue(t_float32 *f_rawSigValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for MTR_XL_GetIfValue here
    switch(g_MtrXL_OptCfg_e)
        {
            case APPSYS_OPT_ACT_MTR_XL_CL42T:
                *f_rawSigValue_pf32 = 0.0f;
                Ret_e = RC_WARNING_NO_OPERATION;
            break;
            case APPSYS_OPT_ACT_MTR_XL_UNUSED:
                *f_rawSigValue_pf32 = 0.0f;
                Ret_e = RC_WARNING_NO_OPERATION;
            break;
            case APPSYS_OPT_ACT_MTR_XL_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
            break;
        }


    return Ret_e;
}

/******************************************
* APPACT_SPEC_MTR_XR_TRIGTIME_SetValue
******************************************/
t_eReturnCode APPACT_SPEC_MTR_XR_TRIGTIME_SetValue(t_float32 f_SigValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_SetMotorValue cl42T_MtrVal_s;
    //    Your code for MTR_XL_SetIfValue here
    switch(g_MtrXL_OptCfg_e)
        {
            case APPSYS_OPT_ACT_MTR_XL_CL42T:
                g_cl42tShadowCmd_s.trigTimer_u32 = (t_uint32)f_SigValue_pf32;   
                if((g_cl42tShadowCmd_s.isPulsesRcv_b == TRUE)
                && g_cl42tShadowCmd_s.isFreqRcv_b == TRUE)
                {
                    cl42T_MtrVal_s.triggerTimer_u32 = g_cl42tShadowCmd_s.trigTimer_u32;
                    cl42T_MtrVal_s.frequency_f32 = g_cl42tShadowCmd_s.frequency_f32;
                    cl42T_MtrVal_s.nbPulses_s32 = g_cl42tShadowCmd_s.nbPulses_s32 * APPACT_SPEC_MOTOR_XR_DIR;

                    Ret_e = CL42T_SetMotorSigValue( c_MtrXL_CL42T_Id,
                                                    cl42T_MtrVal_s);
                    //---- even if ret_e != RC_OK, we reset the flag ----//
                    g_cl42tShadowCmd_s.isFreqRcv_b = FALSE;
                    g_cl42tShadowCmd_s.isPulsesRcv_b = FALSE;
                    g_cl42tShadowCmd_s.isTrigTimerRcv_b = FALSE;
                }
                
            break;
            case APPSYS_OPT_ACT_MTR_XL_UNUSED:
                Ret_e = RC_WARNING_NO_OPERATION;
            break;
            case APPSYS_OPT_ACT_MTR_XL_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
            break;
        }


    return Ret_e;
}

/* CAUTION : Automatic generated code section for Specific Function Implementation: End */
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_APPACT_SPEC_CL42T_Cfg
 *********************************/
static t_eReturnCode s_APPACT_SPEC_CL42T_Cfg(void)
{
    t_eReturnCode Ret_e;

    t_sCL42T_MotorSigCfg motorConfig = {
        .DiagSignal_e = FMKIO_INPUT_SIGFREQ_1,
        .DirSignal_e = FMKIO_OUTPUT_SIGDIG_1,
        .StateSignal_e = FMKIO_OUTPUT_SIGDIG_7,
        .EndStopSigCW_s = {
            .EndStopSignal_e = FMKIO_INPUT_SIGEVNT_1,
            .PullMode_e = FMKIO_PULL_MODE_UP,
            .triggerEvnt_e = FMKIO_STC_RISING_EDGE
        },
        .EndStopSigCCW_s = {
            .EndStopSignal_e = FMKIO_INPUT_SIGEVNT_2,
            .PullMode_e = FMKIO_PULL_MODE_UP,
            .triggerEvnt_e = FMKIO_STC_RISING_EDGE
        },
        .PulseSigCfg_s = {
            .PulseSignal_e = FMKIO_OUTPUT_SIGPWM_6,
            .pwmWaveForm_s = {
                .deadTime_u32 = 0,
                .frequency_f32 = 1000,
                .polarity_e = FMKIO_SIGPWM_POLARITY_LOW,
                .pullMode_e = FMKIO_PULL_MODE_DISABLE,
                .spdMode_e = FMKIO_SPD_MODE_HIGH,
            },
            .pwmCtrlPrm_s = {
                .ctrlType_e = FMKIO_PWM_CTRL_TYPE_UNUSED,
                .rampCfg_ps = NULL,
                .enablePulseSyncOpe_b = TRUE
            }
        }
    };

    Ret_e  = CL42T_AddMotorConfiguration(   c_MtrXL_CL42T_Id,
                                            motorConfig, 
                                            APPACT_SPEC_MOTOR_XL_ENABLE_DEADTIME,
                                            s_APPACT_SPEC_CL42T_HealthCallback,
                                            s_APPACT_SPEC_CL42T_PulseDroppedCallback);
    return Ret_e;
}

/*********************************
 * s_APPACT_SPEC_CL42T_GetMtrInfo
 *********************************/
static t_eReturnCode s_APPACT_SPEC_CL42T_GetMtrInfo(t_float32 * f_mtrValue_pf32)
{
    t_eReturnCode Ret_e;
    t_uint16 mtrValue_u16;

    if(f_mtrValue_pf32 == (t_float32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else 
    {
        Ret_e = CL42T_GetMotorInfo(c_MtrXL_CL42T_Id, &mtrValue_u16);
        if(Ret_e == RC_OK)
        {
            if(GETBIT(mtrValue_u16, CL42T_BITFIELD_MOTOR_ON) == BIT_IS_SET_16B)
            {
                *f_mtrValue_pf32 = APPACT_MOTOR_STS_ON;
            }
            else if(GETBIT(mtrValue_u16, CL42T_BITFIELD_TRIG_ENDSTOP_CW) == BIT_IS_SET_16B)
            {
                *f_mtrValue_pf32 = APPACT_MOTOR_STS_ENDSTOP_CW;
            }
            else if(GETBIT(mtrValue_u16, CL42T_BITFIELD_TRIG_ENDSTOP_CCW) == BIT_IS_SET_16B)
            {
                *f_mtrValue_pf32 = APPACT_MOTOR_STS_ENDSTOP_CCW;
            }
            else
            {
                *f_mtrValue_pf32 = APPACT_MOTOR_STS_OFF;
            }
        }
    }

    return Ret_e;
}
/*********************************
 * s_APPACT_SPEC_CL42T_HealthCallback
 *********************************/
static void s_APPACT_SPEC_CL42T_HealthCallback(t_eCL42T_MotorId f_MotorID_e, t_eCL42T_DiagError f_defaultInfo_e)
{
    t_bool emitDiag_b = FALSE;
    if(f_MotorID_e != c_MtrXL_CL42T_Id)
    {
        ASSERT((t_uint16)f_MotorID_e);
    }
    else 
    {
        switch(f_defaultInfo_e)
        {           
            case CL42T_DIAGNOSTIC_PRESENTS:
            case CL42T_DIAGNOSTIC_OVER_CURRENT:
            case CL42T_DIAGNOSTIC_OVER_VOLTAGE:
            case CL42T_DIAGNOSTIC_CHIP_ERROR:
            case CL42T_DIAGNOSTIC_LOCK_MOTOR_SHAFT:
            case CL42T_DIAGNOSTIC_AUTO_TUNNING:
            case CL42T_DIAGNOSTIC_EEPROM:
            case CL42T_DIAGNOSTIC_POSITION:
            case CL42T_DIAGNOSTIC_PCB_BOARD:
            case CL42T_DIAGNOSTIC_PULSE_INFINITE:
                emitDiag_b = TRUE;
            break;
            case CL42T_DIAGNOSTIC_SIGNAL_PULSE:
            case CL42T_DIAGNOSTIC_OK:
            case CL42T_DIAGNOSTIC_SIGNAL_FREQ:
            default:
            break;
        }
        if(emitDiag_b == TRUE)
        {
            APPSDM_ReportDiagEvnt(  APPSDM_DIAG_STRAT_GANTRY_AXE_X_OFF,
                                    APPSDM_DIAG_ITEM_REPORT_FAIL,
                                    f_defaultInfo_e,
                                    (t_uint16)0);
        }
        else 
        {
            APPSDM_ReportDiagEvnt(  APPSDM_DIAG_STRAT_GANTRY_AXE_X_OFF,
                                    APPSDM_DIAG_ITEM_REPORT_PASS,
                                    f_defaultInfo_e,
                                    (t_uint16)0);
        }
    }

    return;
}

/*********************************
 * s_APPACT_SPEC_CL42T_PulseDroppedCallback
 *********************************/
static void s_APPACT_SPEC_CL42T_PulseDroppedCallback(t_eCL42T_MotorId f_MotorID_e, 
                                                     t_uint16 f_pulseDropped_u16, 
                                                     t_eCL42T_MotorDirection f_direction_e)
{
    if(f_MotorID_e != c_MtrXL_CL42T_Id)
    {
        ASSERT((t_uint16)f_MotorID_e);
    }
    else if(f_direction_e >= CL42T_MOTOR_DIRECTION_NB)
    {
        ASSERT((t_uint16)f_direction_e);
    }
    else 
    {
        if(f_direction_e == CL42T_MOTOR_DIRECTION_CCW)
        {
            g_doppPulses_s32 -= f_pulseDropped_u16;
        }
        else 
        {
            g_doppPulses_s32 += (f_pulseDropped_u16);
        }
    }

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
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
