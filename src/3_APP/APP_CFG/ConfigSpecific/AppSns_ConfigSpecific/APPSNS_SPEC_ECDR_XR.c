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
#include "./APPSNS_SPEC_ECDR_XR.h"
/* CAUTION : Automatic generated code section for Include: End */
#include "FMK_HAL/FMK_IO/Src/FMK_IO.h"
#include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
#include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
#include "APP_CTRL/APP_SDM/Src/APP_SDM.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
#define APPSNS_SPEC_ECDR_ID (FMKIO_INPUT_ENCODER_1)
#define APPSNS_SPEC_ECDR_MULTIPLE_TOUR ((t_uint8)1)
#define APPSNS_SPEC_ECDR_PULSE_PER_REV ((t_uint16)3600)
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
static t_uint8 g_OptSysCfg_u8 = 0xFF;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/* CAUTION : Automatic generated code section for Specific Function Implementation: Start */


/******************************************
* APPSNS_SPEC_ECDR_XR_SetCfg
******************************************/
t_eReturnCode APPSNS_SPEC_ECDR_XR_SetCfg(t_uint8 f_snsDvcOpt_u8, t_eAPPSNS_SnsDriverList *f_drvUsed_pe)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for ECDR_XR_SetSnsCfg here
    if(f_drvUsed_pe == NULL)
    {
        ASSERT((t_uint16)0);
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else 
    {
        switch (f_snsDvcOpt_u8)
        {
            case APPSYS_OPT_SNS_ECDR_XR_UNUSED:
                *f_drvUsed_pe = APPSNS_DRV_NB;
                Ret_e = RC_WARNING_NO_OPERATION;
                break;

            case APPSYS_OPT_SNS_ECDR_XR_NEMA17:
            {
                t_sFMKIO_SigEcdrCfg sigEcdr_s = {
                    .hwCfg_s = {
                        .HwMode_e = FMKTIM_ECDR_MODE_TI12,
                        .IC1_s.Polarity_e = FMKTIM_ECDR_IN_POLARITY_RISING,
                        .IC1_s.Selection_e = FMKTIM_ICSELECT_DIRECT_TI,
                        .IC2_s.Polarity_e = FMKTIM_ECDR_IN_POLARITY_RISING,
                        .IC2_s.Selection_e = FMKTIM_ICSELECT_DIRECT_TI,
                    },
                    .MultipleTourPerRev_u8 = APPSNS_SPEC_ECDR_MULTIPLE_TOUR,
                    .PulsePerRev_u16 = APPSNS_SPEC_ECDR_PULSE_PER_REV,
                    .pullMode_e = FMKIO_PULL_MODE_UP,
                    .speedMode_e = FMKIO_SPD_MODE_HIGH
                };
                Ret_e = FMKIO_Set_InEncoderSigCfg(  APPSNS_SPEC_ECDR_ID,
                                                    sigEcdr_s,
                                                    FMKIO_ENCODER_START_BOTH);
                break;
            }
            case APPSYS_OPT_SNS_ECDR_XR_APPSIG:
                *f_drvUsed_pe = APPSNS_DRV_NB;
                Ret_e = RC_OK;
            break;
            case APPSYS_OPT_SNS_ECDR_XR_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                ASSERT((t_uint16)f_snsDvcOpt_u8);
                break;
        }

        if (Ret_e == RC_OK)
        {
            g_OptSysCfg_u8 = f_snsDvcOpt_u8;
        }
    }

    return Ret_e;
}



/******************************************
* APPSNS_SPEC_ECDR_XR_POS_GetSigValue
******************************************/
t_eReturnCode APPSNS_SPEC_ECDR_XR_POS_GetSigValue(t_float32 *f_rawSigValue_pf32, t_bool * f_isValue_OK)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 position_f32;
    //    Your code for ECDR_XR_GetSigValue here
    if(f_rawSigValue_pf32 == NULL)
    {
        ASSERT((t_uint16)0);
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else 
    {
        switch (g_OptSysCfg_u8)
        {
            case APPSYS_OPT_SNS_ECDR_XR_UNUSED:
                Ret_e = RC_WARNING_NO_OPERATION;
                break;

            case APPSYS_OPT_SNS_ECDR_XR_NEMA17:
                Ret_e = FMKIO_Get_InEcdrPositionValue(  APPSNS_SPEC_ECDR_ID,
                                                        FMKIO_ECDR_VAL_FORMAT_MRADIAN,
                                                        &position_f32);
                if(Ret_e == RC_OK)
                {
                    *f_rawSigValue_pf32 = position_f32 / 1000.0f; // value is in radian
                    *f_isValue_OK = TRUE;
                }
                else 
                {
                    *f_rawSigValue_pf32 = 0.0F;
                    *f_isValue_OK = FALSE;
                }
                break;

            case APPSYS_OPT_SNS_ECDR_XR_APPSIG:
                Ret_e = APPSIG_GetSignalValue(  APPSIG_SIGNAL_SNS_ECDR_XR_POS,
                                                &position_f32);
                if(Ret_e == RC_OK)
                {
                    *f_rawSigValue_pf32 = position_f32;
                    *f_isValue_OK = TRUE;
                }
                else 
                {
                    *f_rawSigValue_pf32 = 0.0F;
                    *f_isValue_OK = FALSE;
                }
                break;
            case APPSYS_OPT_SNS_ECDR_XR_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                ASSERT((t_uint16)g_OptSysCfg_u8);
                break;
        }
    }

    return Ret_e;
}



/******************************************
* APPSNS_SPEC_ECDR_XR_POS_FormatValue
******************************************/
t_eReturnCode APPSNS_SPEC_ECDR_XR_POS_FormatValue(t_float32  rawValue_f32, t_float32 *SnsValue_f32)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for ECDR_XR_FormatValSI here
    if(SnsValue_f32 == NULL)
    {
        ASSERT((t_uint16)0);
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else 
    {
        *SnsValue_f32 = rawValue_f32;
    }

    return Ret_e;
}



/******************************************
* APPSNS_SPEC_ECDR_XR_SPD_GetSigValue
******************************************/
t_eReturnCode APPSNS_SPEC_ECDR_XR_SPD_GetSigValue(t_float32 *f_rawSigValue_pf32, t_bool * f_isValue_OK)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for ECDR_XR_GetSigValue here
    t_float32 speed_f32;

    if(f_rawSigValue_pf32 == NULL)
    {
        ASSERT((t_uint16)0);
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else 
    {
        switch (g_OptSysCfg_u8)
        {
            case APPSYS_OPT_SNS_ECDR_XR_UNUSED:
                Ret_e = RC_WARNING_NO_OPERATION;
                break;

            case APPSYS_OPT_SNS_ECDR_XR_NEMA17:
                Ret_e = FMKIO_Get_InEcdrSpeed(  APPSNS_SPEC_ECDR_ID,
                                                FMKIO_ECDR_VAL_FORMAT_MRADIAN,
                                                &speed_f32);
                if(Ret_e == RC_OK)
                {
                    *f_rawSigValue_pf32 = speed_f32 / 1000.0F; // in milliradian
                    *f_isValue_OK = TRUE;
                }
                else 
                {
                    *f_rawSigValue_pf32 = 0.0F;
                    *f_isValue_OK = FALSE;
                }
                break;

            case APPSYS_OPT_SNS_ECDR_XR_APPSIG:
                Ret_e = APPSIG_GetSignalValue(  APPSIG_SIGNAL_SNS_ECDR_XR_SPD,
                                                &speed_f32);
                if(Ret_e == RC_OK)
                {
                    *f_rawSigValue_pf32 = speed_f32; // already in rad/s
                    *f_isValue_OK = TRUE;
                }
                else 
                {
                    *f_rawSigValue_pf32 = 0.0F;
                    *f_isValue_OK = FALSE;
                }
                break;
            case APPSYS_OPT_SNS_ECDR_XR_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                ASSERT((t_uint16)g_OptSysCfg_u8);
                break;
        }
    }

    return Ret_e;
}



/******************************************
* APPSNS_SPEC_ECDR_XR_SPD_FormatValue
******************************************/
t_eReturnCode APPSNS_SPEC_ECDR_XR_SPD_FormatValue(t_float32  rawValue_f32, t_float32 *SnsValue_f32)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for ECDR_XR_FormatValSI here

    if(SnsValue_f32 == NULL)
    {
        ASSERT((t_uint16)0);
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else 
    {
        *SnsValue_f32 = rawValue_f32;
    }

    return Ret_e;
}

/* CAUTION : Automatic generated code section for Specific Function Implementation: End */
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
           
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
