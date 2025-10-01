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
#include "./APPACT_ConfigSpecific.h"
#include "APP_CFG/ConfigFiles/APPACT_ConfigPublic.h"
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
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/* CAUTION : Automatic generated code section for Specific Function Implementation: Start */


/******************************************
* APPACT_SPEC_CL42T_Speed_SetValue
******************************************/
t_eReturnCode APPACT_SPEC_CL42T_Speed_SetValue( t_float32 f_SigValue_pf32, 
                                                t_eCL42T_MotorId f_MotorId_e,
                                                t_sint32 f_dirPositive_s32,
                                                t_sAPPACT_SPEC_CL42T_ShadowCmd * f_shadowCmd_ps)
{
    t_eReturnCode Ret_e;
    t_sCL42T_SetMotorValue cl42T_MtrVal_s;

    if(f_shadowCmd_ps == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        if(f_SigValue_pf32 == APPACT_SOFT_STOP)
        {
            Ret_e = CL42T_SetMotorState(f_MotorId_e, CL42T_MOTOR_STATE_OFF, FALSE);
        }
        else if(f_SigValue_pf32 == APPACT_HARD_STOP)
        {
            Ret_e = CL42T_SetMotorState(f_MotorId_e, CL42T_MOTOR_STATE_OFF, TRUE);
        }
        else if(f_SigValue_pf32 == APPACT_ENABLE_MOTOR)
        {
            Ret_e = CL42T_SetMotorState(f_MotorId_e, CL42T_MOTOR_STATE_ON, FALSE);
        }
        else
        {       
            f_shadowCmd_ps->frequency_f32 = f_SigValue_pf32;
            f_shadowCmd_ps->isFreqRcv_b = TRUE;

            if((f_shadowCmd_ps->isPulsesRcv_b == TRUE)
            && f_shadowCmd_ps->isTrigTimerRcv_b == TRUE)
            {
                cl42T_MtrVal_s.triggerTimer_u32 = f_shadowCmd_ps->trigTimer_u32;
                cl42T_MtrVal_s.frequency_f32 = f_shadowCmd_ps->frequency_f32;
                cl42T_MtrVal_s.nbPulses_s32 = f_shadowCmd_ps->nbPulses_s32 * f_dirPositive_s32;

                Ret_e = CL42T_SetMotorSigValue( f_MotorId_e,
                                                cl42T_MtrVal_s);
                //---- even if ret_e != RC_OK, we reset the flag ----//
                f_shadowCmd_ps->isFreqRcv_b = FALSE;
                f_shadowCmd_ps->isPulsesRcv_b = FALSE;
                f_shadowCmd_ps->isTrigTimerRcv_b = FALSE;
            }
            else 
            {
                Ret_e = RC_OK;
            }
        }
    }

    return Ret_e;
}

/******************************************
* APPACT_SPEC_CL42T_TrigTime_SetValue
******************************************/
t_eReturnCode APPACT_SPEC_CL42T_TrigTime_SetValue(  t_float32 f_SigValue_pf32, 
                                                    t_eCL42T_MotorId f_MotorId_e,
                                                    t_sint32 f_dirPositive_s32,
                                                    t_sAPPACT_SPEC_CL42T_ShadowCmd * f_shadowCmd_ps)
{
    t_eReturnCode Ret_e;
    t_sCL42T_SetMotorValue cl42T_MtrVal_s;

    if(f_shadowCmd_ps == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        f_shadowCmd_ps->trigTimer_u32 = (t_uint32)f_SigValue_pf32;   
        if((f_shadowCmd_ps->isPulsesRcv_b == TRUE)
        && (f_shadowCmd_ps->isFreqRcv_b == TRUE))
        {
            cl42T_MtrVal_s.triggerTimer_u32 = f_shadowCmd_ps->trigTimer_u32;
            cl42T_MtrVal_s.frequency_f32 = f_shadowCmd_ps->frequency_f32;
            cl42T_MtrVal_s.nbPulses_s32 = f_shadowCmd_ps->nbPulses_s32 * f_dirPositive_s32;

            Ret_e = CL42T_SetMotorSigValue( f_MotorId_e,
                                            cl42T_MtrVal_s);
            //---- even if ret_e != RC_OK, we reset the flag ----//
            f_shadowCmd_ps->isFreqRcv_b = FALSE;
            f_shadowCmd_ps->isPulsesRcv_b = FALSE;
            f_shadowCmd_ps->isTrigTimerRcv_b = FALSE;
        }
        else 
        {
            Ret_e = RC_OK;
        }
    }

    return Ret_e;
}

/******************************************
* APPACT_SPEC_CL42T_Pulse_SetValue
******************************************/
t_eReturnCode APPACT_SPEC_CL42T_Pulse_SetValue( t_float32 f_SigValue_pf32, 
                                                t_eCL42T_MotorId f_MotorId_e,
                                                t_sint32 f_dirPositive_s32,
                                                t_sAPPACT_SPEC_CL42T_ShadowCmd * f_shadowCmd_ps)
{
    t_eReturnCode Ret_e;
    t_sCL42T_SetMotorValue cl42T_MtrVal_s;

    if(f_shadowCmd_ps == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        f_shadowCmd_ps->nbPulses_s32 = (t_sint32)(f_SigValue_pf32 + 0.5f);
        f_shadowCmd_ps->isPulsesRcv_b = TRUE;

        if((f_shadowCmd_ps->isFreqRcv_b == TRUE)
        && (f_shadowCmd_ps->isTrigTimerRcv_b == TRUE))
        {
            cl42T_MtrVal_s.triggerTimer_u32 = f_shadowCmd_ps->trigTimer_u32;
            cl42T_MtrVal_s.frequency_f32 = f_shadowCmd_ps->frequency_f32;
            cl42T_MtrVal_s.nbPulses_s32 = f_shadowCmd_ps->nbPulses_s32 * f_dirPositive_s32;

            Ret_e = CL42T_SetMotorSigValue( f_MotorId_e,
                                            cl42T_MtrVal_s);
            //---- even if ret_e != RC_OK, we reset the flag ----//
            f_shadowCmd_ps->isFreqRcv_b = FALSE;
            f_shadowCmd_ps->isPulsesRcv_b = FALSE;
            f_shadowCmd_ps->isTrigTimerRcv_b = FALSE;
        }
        else 
        {
            Ret_e = RC_OK;
        }
    }

    return Ret_e;
}

/******************************************
* APPACT_SPEC_CL42T_Speed_GetValue
******************************************/
t_eReturnCode APPACT_SPEC_CL42T_Speed_GetValue( t_float32 * f_SigValue_pf32,
                                                t_eCL42T_MotorId f_MotorId_e)
{
    t_eReturnCode Ret_e;
    t_uint16 mtrValue_u16;

    if(f_SigValue_pf32 == (t_float32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else 
    {
        Ret_e = CL42T_GetMotorInfo(f_MotorId_e, &mtrValue_u16);
        if(Ret_e == RC_OK)
        {
            if(GETBIT(mtrValue_u16, CL42T_BITFIELD_MOTOR_ON) == BIT_IS_SET_16B)
            {
                *f_SigValue_pf32 = APPACT_MOTOR_STS_ON;
            }
            else if(GETBIT(mtrValue_u16, CL42T_BITFIELD_TRIG_ENDSTOP_CW) == BIT_IS_SET_16B)
            {
                *f_SigValue_pf32 = APPACT_MOTOR_STS_ENDSTOP_CW;
            }
            else if(GETBIT(mtrValue_u16, CL42T_BITFIELD_TRIG_ENDSTOP_CCW) == BIT_IS_SET_16B)
            {
                *f_SigValue_pf32 = APPACT_MOTOR_STS_ENDSTOP_CCW;
            }
            else
            {
                *f_SigValue_pf32 = APPACT_MOTOR_STS_OFF;
            }
        }
    }

    return Ret_e;

}

/******************************************
* APPACT_SPEC_CL42T_Diagnostic
******************************************/
void APPACT_SPEC_CL42T_Diagnostic(  t_eCL42T_DiagError f_defaultInfo_e,
                                    t_eCL42T_MotorId f_MotorId_e,
                                    t_eAPPSDM_DiagnosticItem f_DiagITem_e)
{
    t_bool emitDiag_b = FALSE;

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
        APPSDM_ReportDiagEvnt(  f_DiagITem_e,
                                APPSDM_DIAG_ITEM_REPORT_FAIL,
                                f_defaultInfo_e,
                                (t_uint16)0);
    }
    else 
    {
        APPSDM_ReportDiagEvnt(  f_DiagITem_e,
                                APPSDM_DIAG_ITEM_REPORT_PASS,
                                f_defaultInfo_e,
                                (t_uint16)0);
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
