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
#include "./APPACT_SPEC_MTR_Y.h"
/* CAUTION : Automatic generated code section for Include: End */
#include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
#include "APPACT_ConfigSpecific.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
///@brief ENable motor XL Dead Time
#define APPACT_SPEC_MOTOR_XL_ENABLE_DEADTIME TRUE

///@brief Positive direction for Y
#define APPACT_SPEC_MOTOR_Y_DIR_POS ((t_sint32)1)
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

/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************
const static t_eCL42T_MotorId c_MtrXL_CL42T_Id = CL42T_MOTOR_3;

static t_eAPPSYS_OptActMtrXl g_MtrXL_OptCfg_e = APPSYS_OPT_ACT_MTR_Y_NB;

static t_sAPPACT_SPEC_CL42T_ShadowCmd g_cl42tShadowCmd_s;
static t_sint32 g_droppPulses_s32;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
 * @brief Set CL42T Motor Configuration 
 */
static t_eReturnCode s_APPACT_SPEC_CL42T_Cfg(void);
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
* APPACT_SPEC_MTR_Y_SetCfg
******************************************/
t_eReturnCode APPACT_SPEC_MTR_Y_SetCfg(t_uint8 f_actDvcOpt_u8, t_eAPPACT_ActDriverList *f_drvUsed_pe)
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
            case APPSYS_OPT_ACT_MTR_Y_CL42T:
                Ret_e = s_APPACT_SPEC_CL42T_Cfg();
                if(Ret_e == RC_OK)
                {
                    *f_drvUsed_pe = APPACT_DRV_CL42T;
                    g_cl42tShadowCmd_s.isPulsesRcv_b = FALSE;
                    g_cl42tShadowCmd_s.isFreqRcv_b = FALSE;
                    g_cl42tShadowCmd_s.isTrigTimerRcv_b = FALSE;
                    g_cl42tShadowCmd_s.lastCmdSet_u32 = 0;
                    g_droppPulses_s32 = (t_sint32)0;
                }
            break;
            case APPSYS_OPT_ACT_MTR_Y_UNUSED:
                Ret_e = RC_WARNING_NO_OPERATION;
            break;
            case APPSYS_OPT_ACT_MTR_Y_NB:
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
* APPACT_SPEC_MTR_Y_PLS_GetValue
******************************************/
t_eReturnCode APPACT_SPEC_MTR_Y_PLS_GetValue(t_float32 *f_rawSigValue_pf32)
{
    t_eReturnCode Ret_e;
    //    Your code for MTR_XL_GetIfValue here
    switch(g_MtrXL_OptCfg_e)
        {
            case APPSYS_OPT_ACT_MTR_Y_CL42T:
                //---- We give the pulses that has been dropped ----//
                *f_rawSigValue_pf32 = (t_float32)g_droppPulses_s32;
                g_droppPulses_s32 = 0;
                Ret_e = RC_OK;
            break;
            case APPSYS_OPT_ACT_MTR_Y_UNUSED:
                *f_rawSigValue_pf32 = 0.0f;
                Ret_e = RC_WARNING_NO_OPERATION;
            break;
            case APPSYS_OPT_ACT_MTR_Y_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
            break;
        }


    return Ret_e;
}



/******************************************
* APPACT_SPEC_MTR_Y_PLS_SetValue
******************************************/
t_eReturnCode APPACT_SPEC_MTR_Y_PLS_SetValue(t_float32 f_SigValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    
    //    Your code for MTR_XL_SetIfValue here

    switch(g_MtrXL_OptCfg_e)
    {
        case APPSYS_OPT_ACT_MTR_Y_CL42T:
            Ret_e = APPACT_SPEC_CL42T_PLS_SetValue(   f_SigValue_pf32, 
                                                        c_MtrXL_CL42T_Id,
                                                        APPACT_SPEC_MOTOR_Y_DIR_POS,
                                                        &g_cl42tShadowCmd_s);
        break;
        case APPSYS_OPT_ACT_MTR_Y_UNUSED:
            Ret_e = RC_WARNING_NO_OPERATION;
        break;
        case APPSYS_OPT_ACT_MTR_Y_NB:
        default:
            Ret_e = RC_ERROR_PARAM_INVALID;
        break;
    }

    return Ret_e;
}



/******************************************
* APPACT_SPEC_MTR_Y_SPD_GetValue
******************************************/
t_eReturnCode APPACT_SPEC_MTR_Y_SPD_GetValue(t_float32 *f_rawSigValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for MTR_XL_GetIfValue here
    switch(g_MtrXL_OptCfg_e)
    {
        case APPSYS_OPT_ACT_MTR_Y_CL42T:
            Ret_e = APPACT_SPEC_CL42T_SPD_GetValue(   f_rawSigValue_pf32,
                                                        c_MtrXL_CL42T_Id);
        break;
        case APPSYS_OPT_ACT_MTR_Y_UNUSED:
            Ret_e = RC_WARNING_NO_OPERATION;
        break;
        case APPSYS_OPT_ACT_MTR_Y_NB:
        default:
            Ret_e = RC_ERROR_PARAM_INVALID;
        break;
    }

    return Ret_e;
}



/******************************************
* APPACT_SPEC_MTR_Y_SPD_SetValue
******************************************/
t_eReturnCode APPACT_SPEC_MTR_Y_SPD_SetValue(t_float32 f_SigValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for MTR_XL_SetIfValue here
    switch(g_MtrXL_OptCfg_e)
        {
            case APPSYS_OPT_ACT_MTR_Y_CL42T:
                Ret_e = APPACT_SPEC_CL42T_SPD_SetValue(   f_SigValue_pf32,
                                                            c_MtrXL_CL42T_Id,
                                                            APPACT_SPEC_MOTOR_Y_DIR_POS,
                                                            &g_cl42tShadowCmd_s);
            break;
            case APPSYS_OPT_ACT_MTR_Y_UNUSED:
                Ret_e = RC_WARNING_NO_OPERATION;
            break;
            case APPSYS_OPT_ACT_MTR_Y_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
            break;
        }


    return Ret_e;
}

/******************************************
* APPACT_SPEC_MTR_Y_TRG_GetValue
******************************************/
t_eReturnCode APPACT_SPEC_MTR_Y_TRG_GetValue(t_float32 *f_rawSigValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for MTR_XL_GetIfValue here
    switch(g_MtrXL_OptCfg_e)
        {
            case APPSYS_OPT_ACT_MTR_XL_CL42T:
                *f_rawSigValue_pf32 = 0.0f;
                Ret_e = RC_OK;
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
* APPACT_SPEC_MTR_Y_TRG_SetValue
******************************************/
t_eReturnCode APPACT_SPEC_MTR_Y_TRG_SetValue(t_float32 f_SigValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for MTR_XL_SetIfValue here
    switch(g_MtrXL_OptCfg_e)
        {
            case APPSYS_OPT_ACT_MTR_XL_CL42T:
                Ret_e = APPACT_SPEC_CL42T_TRG_SetValue(f_SigValue_pf32,
                                                            c_MtrXL_CL42T_Id,
                                                            APPACT_SPEC_MOTOR_Y_DIR_POS,
                                                            &g_cl42tShadowCmd_s);                
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
        .DirSignal_e = FMKIO_OUTPUT_SIGDIG_7,
        .StateSignal_e = FMKIO_OUTPUT_SIGDIG_4,
        .EndStopSigCW_s = {
            .EndStopSignal_e = FMKIO_INPUT_SIGEVNT_5,
            .PullMode_e = FMKIO_PULL_MODE_UP,
            .triggerEvnt_e = FMKIO_STC_RISING_EDGE
        },
        .EndStopSigCCW_s = {
            .EndStopSignal_e = FMKIO_INPUT_SIGEVNT_6,
            .PullMode_e = FMKIO_PULL_MODE_UP,
            .triggerEvnt_e = FMKIO_STC_RISING_EDGE
        },
        .PulseSigCfg_s = {
            .PulseSignal_e = FMKIO_OUTPUT_SIGPWM_5,
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
                .enablePulseSyncOpe_b = FALSE,
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
 * s_APPACT_SPEC_CL42T_HealthCallback
 *********************************/
static void s_APPACT_SPEC_CL42T_HealthCallback(t_eCL42T_MotorId f_MotorID_e, t_eCL42T_DiagError f_defaultInfo_e)
{
    
    if(f_MotorID_e != c_MtrXL_CL42T_Id)
    {
        ASSERT((t_uint16)f_MotorID_e);
    }
    else 
    {
        APPACT_SPEC_CL42T_Diagnostic(   f_defaultInfo_e,
                                        c_MtrXL_CL42T_Id,
                                        APPSDM_DIAG_ITEM_LGC_GTRY_Y_OPE_ERROR);
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
            g_droppPulses_s32 -= f_pulseDropped_u16;
        }
        else 
        {
            g_droppPulses_s32 += (f_pulseDropped_u16);
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
