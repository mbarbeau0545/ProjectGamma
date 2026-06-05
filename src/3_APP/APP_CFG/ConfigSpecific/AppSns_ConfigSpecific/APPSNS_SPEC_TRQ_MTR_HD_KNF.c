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
#include "./APPSNS_SPEC_TRQ_MTR_HD_KNF.h"
/* CAUTION : Automatic generated code section for Include: End */
#include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
#include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
#include "APP_CTRL/APP_SDM/Src/APP_SDM.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
#define APPSNS_SPEC_SIG_TRQ (APPSIG_SIGNAL_SNS_TRQ_MTR_HD_KNF_TRQ)
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
* APPSNS_SPEC_TRQ_MTR_HD_KNF_SetCfg
******************************************/
t_eReturnCode APPSNS_SPEC_TRQ_MTR_HD_KNF_SetCfg(t_uint8 f_snsDvcOpt_u8, t_eAPPSNS_SnsDriverList *f_drvUsed_pe)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for TRQ_MTR_HD_KNF_SetSnsCfg here
    if(f_drvUsed_pe == NULL)
    {
        ASSERT((t_uint16)0);
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else 
    {
        switch (f_snsDvcOpt_u8)
        {
            break;
            case APPSYS_OPT_SNS_TRQ_MTR_HD_KNF_APPSIG:
                *f_drvUsed_pe = APPSNS_DRV_NB;
                Ret_e = RC_OK;
            break;
            case APPSYS_OPT_SNS_TRQ_MTR_HD_KNF_UNUSED:
                Ret_e = RC_WARNING_NO_OPERATION;
                *f_drvUsed_pe = APPSNS_DRV_NB;
            break;
            case APPSYS_OPT_SNS_TRQ_MTR_HD_KNF_ACS716:
            case APPSYS_OPT_SNS_TRQ_MTR_HD_KNF_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                ASSERT((t_uint16)f_snsDvcOpt_u8);
            break;
        }
    }

    if (Ret_e == RC_OK)
    {
        g_OptSysCfg_u8 = f_snsDvcOpt_u8;
    }

    return Ret_e;
}



/******************************************
* APPSNS_SPEC_TRQ_MTR_HD_KNF_TRQ_GetSigValue
******************************************/
t_eReturnCode APPSNS_SPEC_TRQ_MTR_HD_KNF_TRQ_GetSigValue(t_float32 *f_rawSigValue_pf32, t_bool * f_isValue_OK)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 sigVal_f32 = 0.0F;
    //    Your code for TRQ_MTR_HD_KNF_GetSigValue here

    if((f_rawSigValue_pf32 == NULL)
    || (f_isValue_OK == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
        ASSERT((t_uint16)0);
    }
    else 
    {
        switch (g_OptSysCfg_u8)
        {
            break;
            case APPSYS_OPT_SNS_TRQ_MTR_HD_KNF_APPSIG:
                Ret_e = APPSIG_GetSignalValue(  APPSNS_SPEC_SIG_TRQ,
                                                &sigVal_f32);
                if(Ret_e == RC_OK)
                {
                    *f_rawSigValue_pf32 = sigVal_f32;
                    *f_isValue_OK = TRUE;
                }
                else 
                {
                    *f_rawSigValue_pf32 = 0.0F;
                    *f_isValue_OK = FALSE;
                }
            break;
            case APPSYS_OPT_SNS_TRQ_MTR_HD_KNF_UNUSED:
                *f_rawSigValue_pf32 = 0.0F;
                *f_isValue_OK = FALSE;
                Ret_e = RC_WARNING_NO_OPERATION;
            break;
            case APPSYS_OPT_SNS_TRQ_MTR_HD_KNF_ACS716:
            case APPSYS_OPT_SNS_TRQ_MTR_HD_KNF_NB:
            default:
                *f_rawSigValue_pf32 = 0.0F;
                *f_isValue_OK = FALSE;
                Ret_e = RC_ERROR_PARAM_INVALID;
                ASSERT((t_uint16)g_OptSysCfg_u8);
            break;
        }
    }
    return Ret_e;
}



/******************************************
* APPSNS_SPEC_TRQ_MTR_HD_KNF_TRQ_FormatValue
******************************************/
t_eReturnCode APPSNS_SPEC_TRQ_MTR_HD_KNF_TRQ_FormatValue(t_float32  rawValue_f32, t_float32 *SnsValue_f32)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for TRQ_MTR_HD_KNF_FormatValSI here
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
