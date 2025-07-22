/**
 * @file        LIBRamp.h
 * @brief       Ramp signal Managment 
 * @note        Perform Linear/ Exponential/ S-Curve Ramps
 *
 * @author      mba
 * @date        29/03/25
 * @version     1.0
 */
// ********************************************************************
// *                      Includes
// ********************************************************************
#include "./LibRamp.h"
#include "math.h"
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
typedef struct 
{
    t_eLIBRamp_Mode Mode_e;
    t_float32 startValue_f32;
    t_float32 currentValue_f32;
    t_uLIBRamp_RampCfg InfoRmp_u;
    t_bool isConfigured_b;
    t_float32 previousTargetValue_f32;  /**< Last target value used to detect a change in the request.*/
    t_uint32 currentStep_u32;
    t_uint32 totalSteps_u32;
} t_sLIBRamp_RampInfo;
//-----------------------------TYPEDEF TYPES---------------------------//
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
typedef t_eReturnCode (t_cbLIBRamp_ComputeMode)(t_sLIBRamp_RampInfo *f_rampInfo_ps, 
                                                t_float32 f_rqstValue_f32,
                                                t_float32 * f_computeValue_pf32);

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
static t_eReturnCode s_LIBRamp_SetInitRegistration(t_sLIBRamp_RampCfg * f_rampCfg_ps, t_uint8 f_rampID_u8);
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
static t_eReturnCode s_LIBRamp_ComputeValue(t_uint8 f_rampID_u8, 
                                            t_float32 f_valueRqst_f32,
                                            t_float32 * f_computeValue_pf32);
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
static t_eReturnCode s_LIBRamp_ComputeLinearRamp(   t_sLIBRamp_RampInfo * f_rampInfo_ps,
                                                    t_float32 f_valueRqst_f32,
                                                    t_float32 *f_ComputeValue_pf32);
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
static t_eReturnCode s_LIBRamp_ComputeExponentialRamp(  t_sLIBRamp_RampInfo * f_rampInfo_ps,
                                                        t_float32 f_valueRqst_f32,
                                                        t_float32 * f_ComputeValue_pf32);
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
static t_eReturnCode s_LIBRamp_ComputeSigmoidalRamp(t_sLIBRamp_RampInfo * f_rampInfo_ps,
                                                    t_float32 f_valueRqst_f32,
                                                    t_float32 * f_ComputeValu_epf32);
// ********************************************************************
// *                      Variables
// ********************************************************************
static t_cbLIBRamp_ComputeMode * c_ComputeMode_apf[LIBRAMP_MODE_NB] = 
{
    s_LIBRamp_ComputeLinearRamp,
    s_LIBRamp_ComputeExponentialRamp,
    s_LIBRamp_ComputeSigmoidalRamp,
};

static t_sLIBRamp_RampInfo g_RampInfo_as[LIBRAMP_MAX_REGISTRATION];
static t_uint8 g_CntRegistration_u8 = (t_uint8)0;

//********************************************************************************
//                      Public functions - Implementation
//********************************************************************************
//**********************
// LIBRamp_Init
//**********************
t_eReturnCode LIBRamp_Init(t_sLIBRamp_RampCfg f_rampCfg_s, t_uint8 *f_rampID_pu8)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_rampID_pu8 == (t_uint8 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_CntRegistration_u8 >= LIBRAMP_MAX_REGISTRATION)
    {
        Ret_e = RC_ERROR_LIMIT_REACHED;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_LIBRamp_SetInitRegistration(&f_rampCfg_s, g_CntRegistration_u8);

        if(Ret_e == RC_OK)
        {
            *f_rampID_pu8 = (t_uint8)g_CntRegistration_u8;
            g_CntRegistration_u8 += (t_uint8)1;
        }
    }

    return Ret_e;
}

//**********************
// LIBRamp_Compute
//**********************
t_eReturnCode LIBRamp_Compute(  t_uint8 f_rampID_u8, 
                                t_float32 f_valueRqst_f32,
                                t_float32 * f_computeValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 computeValue_f32 = (t_float32)0;

    if(f_computeValue_pf32 == (t_float32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(f_rampID_u8 > LIBRAMP_MAX_REGISTRATION)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_LIBRamp_ComputeValue( f_rampID_u8,
                                        f_valueRqst_f32,
                                        &computeValue_f32);

        if(Ret_e == RC_OK)
        {
            *f_computeValue_pf32 = (t_float32)computeValue_f32;
        }

    }

    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
//********************************
// s_LIBRamp_SetInitRegistration
//********************************
static t_eReturnCode s_LIBRamp_SetInitRegistration(t_sLIBRamp_RampCfg * f_rampCfg_ps, t_uint8 f_rampID_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sLIBRamp_RampInfo * rampInfo_ps; 

    if(f_rampCfg_ps == (t_sLIBRamp_RampCfg *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL; 
    }   
    if(Ret_e == RC_OK)
    {
        //------ Reach Ramp Information -----//
        rampInfo_ps = (t_sLIBRamp_RampInfo *)(&g_RampInfo_as[f_rampID_u8]);

        rampInfo_ps->totalSteps_u32 = f_rampCfg_ps->totalSteps_u32;
        rampInfo_ps->startValue_f32 = f_rampCfg_ps->startValue_f32;
        rampInfo_ps->Mode_e = f_rampCfg_ps->rampMode_e;
        rampInfo_ps->currentStep_u32 = (t_uint32)0;
        rampInfo_ps->currentValue_f32 = (t_float32)rampInfo_ps->startValue_f32;
        rampInfo_ps->isConfigured_b = (t_bool)True;
        switch(rampInfo_ps->Mode_e)
        {
            case LIBRAMP_MODE_LINEAR:
            {
                rampInfo_ps->InfoRmp_u.linearCfg_s.accelerationMax_f32 = f_rampCfg_ps->rampInfo_u.linearCfg_s.accelerationMax_f32;
                rampInfo_ps->InfoRmp_u.linearCfg_s.decelerationMax_f32 = f_rampCfg_ps->rampInfo_u.linearCfg_s.decelerationMax_f32;
                break;
            }
            case LIBRAMP_MODE_EXPONENTIAL:
            {
                rampInfo_ps->InfoRmp_u.expCfg_s.expFactor_f32 = f_rampCfg_ps->rampInfo_u.expCfg_s.expFactor_f32;
                rampInfo_ps->InfoRmp_u.expCfg_s.smoothingFactor_f32 = f_rampCfg_ps->rampInfo_u.expCfg_s.smoothingFactor_f32;
                break;
            }
            case LIBRAMP_MODE_SIGMOIDALE:
            {
                rampInfo_ps->InfoRmp_u.sigmoidaleCfg_s.kFactor_f32 = f_rampCfg_ps->rampInfo_u.sigmoidaleCfg_s.kFactor_f32;
                rampInfo_ps->InfoRmp_u.sigmoidaleCfg_s.slopSpeed_f32 = f_rampCfg_ps->rampInfo_u.sigmoidaleCfg_s.slopSpeed_f32;
                break;
            }
            case LIBRAMP_MODE_NB:
            default:
            {
                Ret_e = RC_ERROR_NOT_ALLOWED;
                break;
            }
        }        
    }

    return Ret_e;
}

//********************************
// s_LIBRamp_ComputeValue
//********************************
static t_eReturnCode s_LIBRamp_ComputeValue(t_uint8 f_rampID_u8, 
                                            t_float32 f_valueRqst_f32,
                                            t_float32 * f_computeValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sLIBRamp_RampInfo * rampInfo_ps = (t_sLIBRamp_RampInfo *)(&g_RampInfo_as[f_rampID_u8]);

    if(f_computeValue_pf32 == (t_float32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(rampInfo_ps->isConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {
        //------ Compute Ramp Calculation -----//
        Ret_e = c_ComputeMode_apf[rampInfo_ps->Mode_e]( rampInfo_ps, 
                                                        f_valueRqst_f32, 
                                                        f_computeValue_pf32);
    }

    return Ret_e;
} 

//********************************
// s_LIBRamp_ComputeLinearRamp
//********************************
t_eReturnCode s_LIBRamp_ComputeLinearRamp(t_sLIBRamp_RampInfo *f_rampInfo_ps,
                                          t_float32 f_valueRqst_f32,
                                          t_float32 *f_ComputeValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 totalDelta_f32;
    t_float32 normalizedTime_f32;
    t_float32 desiredValue_f32;
    t_float32 inc_f32;
    t_sLIBRamp_LinearCfg *linCfg_ps;

    // Check for null pointers
    if ((f_rampInfo_ps == (t_sLIBRamp_RampInfo *)NULL) 
    ||  (f_ComputeValue_pf32 == (t_float32 *)NULL)) 
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        // Get the pointer to the linear ramp configuration from the union
        linCfg_ps = &f_rampInfo_ps->InfoRmp_u.linearCfg_s;

        // If the target has changed, reset the ramp progression
        if (f_valueRqst_f32 != f_rampInfo_ps->previousTargetValue_f32) 
        {
            f_rampInfo_ps->previousTargetValue_f32 = f_valueRqst_f32;
            f_rampInfo_ps->startValue_f32 = f_rampInfo_ps->currentValue_f32;
            f_rampInfo_ps->currentStep_u32 = 1;
        }

        // Compute the total delta from the starting value to the target value
        totalDelta_f32 = f_valueRqst_f32 - f_rampInfo_ps->startValue_f32;

        // Ensure totalSteps_u32 is valid (at least 1)
        if (f_rampInfo_ps->totalSteps_u32 == 0) 
        {
            f_rampInfo_ps->totalSteps_u32 = 1;
        }

        // Normalize the current step: value between 0 and 1
        normalizedTime_f32 = (t_float32)f_rampInfo_ps->currentStep_u32 / (t_float32)(f_rampInfo_ps->totalSteps_u32 - 1);

        // Compute the desired value using linear interpolation between start and target
        desiredValue_f32 = f_rampInfo_ps->startValue_f32 + totalDelta_f32 * normalizedTime_f32;

        // Compute the increment needed
        inc_f32 = desiredValue_f32 - f_rampInfo_ps->currentValue_f32;

        // Limit the increment according to the acceleration/deceleration limits
        if (inc_f32 > 0.0f) 
        {
            if (inc_f32 > linCfg_ps->accelerationMax_f32) 
            {
                inc_f32 = linCfg_ps->accelerationMax_f32;
            }
        } 
        else 
        {
            if (inc_f32 < -linCfg_ps->decelerationMax_f32) 
            {
                inc_f32 = -linCfg_ps->decelerationMax_f32;
            }
        }

        // Update the current value
        f_rampInfo_ps->currentValue_f32 += inc_f32;

        // If the difference to the target is very small, snap to the target
        if (fabs(f_valueRqst_f32 - f_rampInfo_ps->currentValue_f32) <= fabs(inc_f32)) 
        {
            f_rampInfo_ps->currentValue_f32 = f_valueRqst_f32;
        }

        // Output the computed value
        *f_ComputeValue_pf32 = f_rampInfo_ps->currentValue_f32;

        // Increment the step if the ramp is not yet complete
        if (f_rampInfo_ps->currentStep_u32 < f_rampInfo_ps->totalSteps_u32) 
        {
            f_rampInfo_ps->currentStep_u32++;
        } 
        else 
        {
            // End of ramp: force the final value to exactly match the target
            f_rampInfo_ps->currentValue_f32 = f_valueRqst_f32;
            *f_ComputeValue_pf32 = f_valueRqst_f32;
        }
    }

    return Ret_e;
}

//**********************************
// s_LIBRamp_ComputeExponentialRamp
//**********************************
t_eReturnCode s_LIBRamp_ComputeExponentialRamp(t_sLIBRamp_RampInfo *f_rampInfo_ps,
                                                 t_float32 f_targetValue_f32,
                                                 t_float32 *f_ComputeValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 normalizedTime_f32;
    t_float32 progress_f32;
    t_sLIBRamp_ExpCfg *expCfg_ps;

    // Check for null pointers
    if ((f_rampInfo_ps == (t_sLIBRamp_RampInfo *)NULL) 
    ||  (f_ComputeValue_pf32 == (t_float32 *)NULL)) 
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        // Retrieve pointer to the exponential configuration in the union
        expCfg_ps = (t_sLIBRamp_ExpCfg *)(&f_rampInfo_ps->InfoRmp_u.expCfg_s);

        // If the target has changed, reset the ramp progression
        if (f_targetValue_f32 != f_rampInfo_ps->previousTargetValue_f32)
        {
            f_rampInfo_ps->previousTargetValue_f32 = f_targetValue_f32;
            f_rampInfo_ps->startValue_f32 = f_rampInfo_ps->currentValue_f32;
            f_rampInfo_ps->currentStep_u32 = 1;
        }

        // Ensure totalSteps_u32 is at least 2 to avoid division by zero
        if (f_rampInfo_ps->totalSteps_u32 < 2)
        {
            f_rampInfo_ps->totalSteps_u32 = 2;
        }

        // Normalize time: currentStep_u32 ranges from 0 to (totalSteps_u32 - 1), normalized to [0,1]
        normalizedTime_f32 = (t_float32)f_rampInfo_ps->currentStep_u32 / (t_float32)(f_rampInfo_ps->totalSteps_u32 - 1);

        // If the difference between target and current value is very small, snap directly to target
        if (fabs(f_targetValue_f32 - f_rampInfo_ps->currentValue_f32) <= expCfg_ps->smoothingFactor_f32)
        {
            f_rampInfo_ps->currentValue_f32 = f_targetValue_f32;
            *f_ComputeValue_pf32 = f_targetValue_f32;
            
        }
        else 
        {
            // Compute exponential progress using the formula:
            // progress = (exp(k * normalizedTime_f32) - 1) / (exp(k) - 1)
            // where k is the expFactor_f32 parameter.
            if (expCfg_ps->expFactor_f32 == 0.0f)
            {
                progress_f32 = normalizedTime_f32;  // fallback to linear interpolation if k==0
            }
            else
            {
                progress_f32 = (exp(expCfg_ps->expFactor_f32 * normalizedTime_f32) - 1.0f) /
                            (exp(expCfg_ps->expFactor_f32) - 1.0f);
            }

            // Compute the new ramp value using the exponential progression
            f_rampInfo_ps->currentValue_f32 = f_rampInfo_ps->startValue_f32 +
                (f_targetValue_f32 - f_rampInfo_ps->startValue_f32) * progress_f32;

            // Store the computed value in the output pointer
            *f_ComputeValue_pf32 = f_rampInfo_ps->currentValue_f32;

            // Increment the step counter if the ramp is not complete
            if (f_rampInfo_ps->currentStep_u32 < f_rampInfo_ps->totalSteps_u32)
            {
                f_rampInfo_ps->currentStep_u32++;
            }
            else
            {
                // End of ramp: force the final value to match the target exactly
                f_rampInfo_ps->currentValue_f32 = f_targetValue_f32;
                *f_ComputeValue_pf32 = f_targetValue_f32;
            }
        }
    }

    return Ret_e;
}



//**********************************
// s_LIBRamp_ComputeSigmoidalRamp
//**********************************
t_eReturnCode s_LIBRamp_ComputeSigmoidalRamp(   t_sLIBRamp_RampInfo *f_rampInfo_ps, 
                                                t_float32 f_targetValue_f32,
                                                t_float32 *f_ComputeValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 normalizedTime_f32;
    t_float32 sigmoidalValue_f32;
    t_sLIBRamp_SigmoidaleCfg *sigCfg_ps;

    // Check for null pointers
    if ((f_rampInfo_ps == (t_sLIBRamp_RampInfo *)NULL) 
    ||  (f_ComputeValue_pf32 == (t_float32 *)NULL)) 
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        // Retrieve pointer to the sigmoidal configuration in the union
        sigCfg_ps = (t_sLIBRamp_SigmoidaleCfg *)(&f_rampInfo_ps->InfoRmp_u.sigmoidaleCfg_s);

        // If the target has changed, reset the ramp progression
        if (f_targetValue_f32 != f_rampInfo_ps->previousTargetValue_f32) 
        {
            f_rampInfo_ps->previousTargetValue_f32 = f_targetValue_f32;
            // Store the current value as the starting point for the new ramp
            f_rampInfo_ps->startValue_f32 = f_rampInfo_ps->currentValue_f32;
            // Reset the step counter
            f_rampInfo_ps->currentStep_u32 = (t_uint32)1;
            // Calculate kFactor based on the slope speed and the absolute difference
            if (fabs(f_targetValue_f32 - f_rampInfo_ps->currentValue_f32) > 1e-6f) 
            {
                sigCfg_ps->kFactor_f32 = (t_float32)((double)sigCfg_ps->slopSpeed_f32 / 
                                                        fabs(f_targetValue_f32 - f_rampInfo_ps->currentValue_f32));
            } 
            else 
            {
                sigCfg_ps->kFactor_f32 = 1.0f;
            }
        }

        // Ensure totalSteps_u32 is valid (at least 2 to avoid division by zero)
        if (f_rampInfo_ps->totalSteps_u32 < 2) 
        {
            f_rampInfo_ps->totalSteps_u32 = 2;
        }
        
        // Normalize the current step to a value between 0 and 1
        normalizedTime_f32 = (t_float32)f_rampInfo_ps->currentStep_u32 / (t_float32)(f_rampInfo_ps->totalSteps_u32 - 1);

        // Compute the sigmoidal value at the current normalized time.
        // The sigmoid is centered at 0.5 and its steepness is adjusted by kFactor_f32.
        sigmoidalValue_f32 = 1.0f / (1.0f + exp(-sigCfg_ps->kFactor_f32 * (normalizedTime_f32 - 0.5f)));

        // Calculate the new ramp value using a sigmoidal progression
        f_rampInfo_ps->currentValue_f32 = f_rampInfo_ps->startValue_f32 +
                                        (f_targetValue_f32 - f_rampInfo_ps->startValue_f32) * sigmoidalValue_f32;

        // Store the computed value in the output pointer
        *f_ComputeValue_pf32 = f_rampInfo_ps->currentValue_f32;

        // Increment the current step if the ramp is not yet complete
        if (f_rampInfo_ps->currentStep_u32 < f_rampInfo_ps->totalSteps_u32) 
        {
            f_rampInfo_ps->currentStep_u32++;
        } 
        else 
        {
            // End of ramp: force the final value to equal the target exactly
            f_rampInfo_ps->currentValue_f32 = f_targetValue_f32;
            *f_ComputeValue_pf32 = f_targetValue_f32;
        }
    }

    return Ret_e;
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
