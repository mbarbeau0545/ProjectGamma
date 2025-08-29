/*********************************************************************
 * @file        GANTRY_ConfigSPecific.c
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
#include "./GANTRY_ConfigSpecific.h"
#include "APP_LGC/Src/Agents/Gantry/Src/GANTRY/GANTRY.h"
#include "APP_CFG/ConfigFiles/APPACT_ConfigPublic.h"
#include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
#include "Constant.h"
#include "arm_math.h"
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
/**< enum for module list */

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
///@brief parameter algorithm for the runtime 
t_sGTRYSPEC_AlgoParameter g_param_s;

///@brief Pulse remaining when pass to uint32 to float32 etc
t_float32 g_axePulseRemain_af32[GTRY_PHYS_AXE_NB];
//****************************************************************************
//                      Local functions - Prototypes
//****************************************************************************
/**
 * @brief This function handle the Safety state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static void GTRY_SPEC_Algo_ComputeSteps(   t_float32 f_targetPos_af32[GTRY_PHYS_AXE_NB],
                                                    t_float32 f_currPos_af32[GTRY_PHYS_AXE_NB],
                                                    t_float32 f_missPulses_af32[GTRY_PHYS_AXE_NB],
                                                    t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                    t_sint32 f_pulseSigns_as32[GTRY_PHYS_AXE_NB],
                                                    t_eGTRY_PhysicalAxe * f_domAxis_pe,
                                                    t_uint32 * f_domAxePulses_pu32);
/**
 * @brief This function handle the Safety state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static void GTRY_SPEC_Algo_ComputeChunkCount(   t_eGTRY_PhysicalAxe f_domAxe_e, 
                                                t_uint32 f_domTotalStep_u32,
                                                t_uint16 * f_NbIterMax_pu16);
/**
 * @brief This function handle the Safety state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static void GTRY_SPEC_Algo_DistribInitialPulse( t_uint32 f_PulsesToMake_au32[GTRY_PHYS_AXE_NB], 
                                                t_eGTRY_PhysicalAxe f_domAxe_e,
                                                t_uint16  f_NbIterMax_u16);
//****************************************************************************
//                      Public functions - Implementation
//****************************************************************************
/*********************************
 * GANTRY_SPEC_BuildCartesianCmd
 *********************************/
t_eReturnCode GANTRY_SPEC_BuildCartesianCmd(t_float32 f_value_af32[GTRY_CMD_SIG_NB], 
                                            t_sLIBQUEUE_QueueCore * f_QueuePosCmd_ps)
{
    t_eReturnCode Ret_e;
    t_float32 bufferCmdPos_af32[GTRY_PHYS_AXE_NB];

    if((f_value_af32 == NULL)
    || (f_QueuePosCmd_ps == NULL))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else 
    {
        //--- here nothing to do 'cause already in cmd position ---//
        bufferCmdPos_af32[GTRY_PHYS_AXE_X] = f_value_af32[GTRY_CMD_SIG_POS_X];
        bufferCmdPos_af32[GTRY_PHYS_AXE_Y] = f_value_af32[GTRY_CMD_SIG_POS_Y];
        bufferCmdPos_af32[GTRY_PHYS_AXE_Z] = f_value_af32[GTRY_CMD_SIG_POS_Z];

        Ret_e = LIBQUEUE_WriteElement(  f_QueuePosCmd_ps,
                                        bufferCmdPos_af32,
                                        sizeof(t_float32) * GTRY_PHYS_AXE_NB);
    }

    return Ret_e;
}

/*********************************
 * GANTRY_SPEC_BuildSphericCmd
 *********************************/
t_eReturnCode GANTRY_SPEC_BuildSphericCmd(  t_float32 f_value_af32[GTRY_CMD_SIG_NB], 
                                            t_sLIBQUEUE_QueueCore * f_QueuePosCmd_ps)
{
    t_eReturnCode Ret_e;
    t_float32 bufferCmdPos_af32[GTRY_PHYS_AXE_NB];
    t_float32 rayon_f32;
    t_float32 theta_f32;
    t_float32 phi_f32;

    if((f_value_af32 == NULL)
    || (f_QueuePosCmd_ps == NULL))
    {
        ASSERT((t_uint16)0);
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else 
    {
        rayon_f32     = f_value_af32[GTRY_CMD_SIG_POS_RAYON];
        theta_f32 = f_value_af32[GTRY_CMD_SIG_POS_THETHA];
        phi_f32   = f_value_af32[GTRY_CMD_SIG_POS_PHI];

        //---- degrees to radian ----//
        theta_f32 *= (M_PI / 180.0f);
        phi_f32   *= (M_PI / 180.0f);

        bufferCmdPos_af32[GTRY_PHYS_AXE_X] = rayon_f32 * arm_cos_f32(phi_f32) * arm_cos_f32(theta_f32);
        bufferCmdPos_af32[GTRY_PHYS_AXE_Y] = rayon_f32 * arm_cos_f32(phi_f32) * arm_sin_f32(theta_f32);
        bufferCmdPos_af32[GTRY_PHYS_AXE_Z] = rayon_f32 * arm_sin_f32(phi_f32);

        Ret_e = LIBQUEUE_WriteElement(  f_QueuePosCmd_ps,
                                        bufferCmdPos_af32,
                                        sizeof(t_float32) * GTRY_PHYS_AXE_NB);     
    }

    return Ret_e;
}

/*********************************
 * GANTRY_SPEC_BuildStepCmd
 *********************************/
t_eReturnCode GANTRY_SPEC_BuildStepCmd( t_float32 f_value_af32[GTRY_CMD_SIG_NB], 
                                        t_sLIBQUEUE_QueueCore * f_QueuePosCmd_ps)
{
    t_eReturnCode Ret_e;
    t_float32 bufferCmdPos_af32[GTRY_PHYS_AXE_NB];
    t_sGTRY_AxePosition axePos_s;
    t_uint16 pulseperMmAxeXID_u16;
    t_uint16 pulseperMmAxeYID_u16;
    t_uint16 pulseperMmAxeZID_u16;
    t_float32 factorAxeX_f32;
    t_float32 factorAxeY_f32;
    t_float32 factorAxeZ_f32;

    if((f_value_af32 == NULL)
    || (f_QueuePosCmd_ps == NULL))
    {
        ASSERT((t_uint16)0);
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else 
    {
        //---- 1- get current position ---// 
        Ret_e = GTRY_GetPosition(&axePos_s);

        //---- 2- getpulse per mm parameter for each axe ---//
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_AXE_X_PULSE_PER_MM, 
                                    &pulseperMmAxeXID_u16);
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_AXE_Y_PULSE_PER_MM, 
                                        &pulseperMmAxeYID_u16);
            }
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_AXE_Z_PULSE_PER_MM, 
                                        &pulseperMmAxeZID_u16);
            }
        }
        //--- 3- Compute factor depending on direction ----//
        if(f_value_af32[GTRY_CMD_SIG_DIR_X] == APPACT_DIRECTION_CW)
        {
            factorAxeX_f32 = 1.0f;
        }
        else 
        {
            factorAxeX_f32 = -1.0f;
        }
        if(f_value_af32[GTRY_CMD_SIG_DIR_Y] == APPACT_DIRECTION_CW)
        {
            factorAxeY_f32 = 1.0f;
        }
        else 
        {
            factorAxeY_f32 = -1.0f;
        }
        if(f_value_af32[GTRY_CMD_SIG_DIR_Z] == APPACT_DIRECTION_CW)
        {
            factorAxeZ_f32 = 1.0f;
        }
        else 
        {
            factorAxeZ_f32 = -1.0f;
        }
        //--- 4- Compute new position target ----//
        bufferCmdPos_af32[GTRY_PHYS_AXE_X] = (f_value_af32[GTRY_CMD_SIG_STEP_X] 
                                            * (t_float32)pulseperMmAxeXID_u16 
                                            * factorAxeX_f32);
        bufferCmdPos_af32[GTRY_PHYS_AXE_Y] = (f_value_af32[GTRY_CMD_SIG_STEP_Y] 
                                            * (t_float32)pulseperMmAxeXID_u16 
                                            * factorAxeX_f32);
        bufferCmdPos_af32[GTRY_PHYS_AXE_Z] = (f_value_af32[GTRY_CMD_SIG_STEP_Z] 
                                            * (t_float32)pulseperMmAxeXID_u16 
                                            * factorAxeX_f32);   
        Ret_e = LIBQUEUE_WriteElement(  f_QueuePosCmd_ps,
                                        bufferCmdPos_af32,
                                        sizeof(t_float32) * GTRY_PHYS_AXE_NB);
    }

    return Ret_e;
}

/*********************************
 * GANTRY_SPEC_AlgorithmInit
 *********************************/
t_eReturnCode GANTRY_SPEC_AlgorithmInit(t_sGTRYSPEC_AlgoParameter f_Parameter_s)
{
    t_eGTRY_PhysicalAxe idxAxe_e;
    g_param_s.minPulses_u16 = f_Parameter_s.minPulses_u16;
    g_param_s.computeType_e = f_Parameter_s.computeType_e;

    t_eGTRY_PhysicalAxe idxAxe_e;

    for(idxAxe_e = GTRY_PHYS_AXE_HEAD ; idxAxe_e < GTRY_PHYS_AXE_NB ; idxAxe_e++)
    {
        g_param_s.MaxFreq_af32[idxAxe_e] = f_Parameter_s.MaxFreq_af32[idxAxe_e];
        g_param_s.MinFreq_af32[idxAxe_e] = f_Parameter_s.MinFreq_af32[idxAxe_e];
        g_param_s.pulsePerMm_af32[idxAxe_e] = f_Parameter_s.pulsePerMm_af32[idxAxe_e];
        g_axePulseRemain_af32[idxAxe_e] = 0.0f;
    }

    return RC_OK;
}

/*********************************
 * GANTRY_SPEC_AlgorithmCompute
 *********************************/
t_eReturnCode GANTRY_SPEC_AlgorithmCompute( t_float32 f_targetPos_af32[GTRY_PHYS_AXE_NB],
                                            t_float32 f_currPos_af32[GTRY_PHYS_AXE_NB],
                                            t_float32 f_missPulses_af32[GTRY_PHYS_AXE_NB],
                                            t_float32 f_droppPulses_s32[GTRY_PHYS_AXE_NB],
                                            t_sLIBQUEUE_QueueCore * f_QueueIterCmdX_ps,
                                            t_sLIBQUEUE_QueueCore * f_QueueIterCmdY_ps,
                                            t_sLIBQUEUE_QueueCore * f_QueueIterCmdZ_ps)
{
    t_eReturnCode Ret_e;
    t_uint32 pulseTomake_au32[GTRY_PHYS_AXE_NB] = {0,0,0};
    t_float32 factorPulses_af32[GTRY_PHYS_AXE_NB] = {1.0f, 1.0f, 1.0f};
    t_eGTRY_PhysicalAxe dominantAxe_e = GTRY_PHYS_AXE_NB;
    t_uint32 totalPulseDominant_u32;
    t_uint16 nbIterMax_u16;


    if((f_currPos_af32 == NULL)
    || (f_droppPulses_s32 == NULL)
    || (f_targetPos_af32 == NULL)
    || (f_missPulses_af32 == NULL)
    || (f_QueueIterCmdX_ps == NULL)
    || (f_QueueIterCmdY_ps == NULL)
    || (f_QueueIterCmdZ_ps == NULL))
    {
        ASSERT((t_uint16)0);
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else 
    {
        Ret_e == RC_OK;
        GTRY_SPEC_Algo_ComputeSteps(f_targetPos_af32, 
                                    f_currPos_af32,
                                    f_missPulses_af32,
                                    pulseTomake_au32,
                                    factorPulses_af32,
                                    &dominantAxe_e,
                                    &totalPulseDominant_u32);

        GTRY_SPEC_Algo_ComputeChunkCount(   dominantAxe_e,
                                            totalPulseDominant_u32,
                                            nbIterMax_u16);

        GTRY_SPEC_Algo_DistribInitialPulse( pulseTomake_au32,
                                            dominantAxe_e,
                                            nbIterMax_u16);

        GTRY_SPEC_Algo_SplitSingleIter( pulseTomake_au32,
                                        &nbIterMax_u16);

        GTRY_SPEC_Algo_AdjustLastIter(  pulseTomake_au32,
                                        nbIterMax_u16);

        GTRY_SPEC_Algo_BuidlIterations( pulseTomake_au32,
                                        factorPulses_af32,
                                        nbIterMax_u16,
                                        totalPulseDominant_u32);
        
    }

    return Ret_e;
}

//************************************************************************************
//                      Local Function - Implementation
//************************************************************************************
/*********************************
 * GANTRY_SPEC_AlgorithmCompute
 *********************************/
static void GTRY_SPEC_Algo_ComputeSteps(   t_float32 f_targetPos_af32[GTRY_PHYS_AXE_NB],
                                                    t_float32 f_currPos_af32[GTRY_PHYS_AXE_NB],
                                                    t_float32 f_missPulses_af32[GTRY_PHYS_AXE_NB],
                                                    t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                    t_sint32 f_pulseSigns_as32[GTRY_PHYS_AXE_NB],
                                                    t_eGTRY_PhysicalAxe * f_domAxis_pe,
                                                    t_uint32 * f_domAxePulses_pu32)
{
    t_eReturnCode Ret_e;
    t_eGTRY_PhysicalAxe idxAxe_e;
    t_float32 exactStepToMake_f32;
    t_sint32 realStepToMake_s32;
    t_eGTRY_PhysicalAxe axeDominant_e;
    t_uint32 axeDomPulses_u32 = (t_uint32)0;

    //--- 1- compute unsigned pulse to make ----//
    for(idxAxe_e = GTRY_PHYS_AXE_HEAD ; idxAxe_e < GTRY_PHYS_AXE_NB ; idxAxe_e++)
    {
        exactStepToMake_f32 = (t_float32)(  (f_targetPos_af32[idxAxe_e]
                                            - f_currPos_af32[idxAxe_e])
                                            * g_param_s.pulsePerMm_af32[idxAxe_e]
                                            + g_axePulseRemain_af32[idxAxe_e]
                                            + f_missPulses_af32[idxAxe_e]);

        realStepToMake_s32 = (t_sint32)(exactStepToMake_f32);        
        //--- 2- get the global signed for each axes ----//
        if(realStepToMake_s32 > (t_sint32)0)
        {
            f_pulseSigns_as32[idxAxe_e] = (t_sint32)1;
            f_pulseToMake_au32[idxAxe_e] = (t_uint32)(realStepToMake_s32);
        }
        else 
        {
            f_pulseSigns_as32[idxAxe_e] = (t_sint32)-1;
            f_pulseToMake_au32[idxAxe_e] = (t_uint32)(realStepToMake_s32 * -1);
        }
        //--- 3- Update the dominant axis ----//
        if(f_pulseToMake_au32[idxAxe_e] > axeDomPulses_u32)
        {
            axeDomPulses_u32 = f_pulseToMake_au32[idxAxe_e];
            axeDominant_e = idxAxe_e;
        }

        g_axePulseRemain_af32[idxAxe_e] = (exactStepToMake_f32 - (t_float32)realStepToMake_s32);
    }
    *f_domAxePulses_pu32 = axeDomPulses_u32;
    *f_domAxis_pe = axeDominant_e;

    return Ret_e;
}   

/*********************************
 * GTRY_SPEC_Algo_ComputeChunkCount
 *********************************/
static void GTRY_SPEC_Algo_ComputeChunkCount(   t_eGTRY_PhysicalAxe f_domAxe_e, 
                                                t_uint32 f_domTotalStep_u32,
                                                t_uint16 * f_NbIterMax_pu16)
{
    UNUSED(f_domAxe_e);

    t_uint32 chunckSize_u32 = (t_uint32)g_param_s.minPulses_u16;
    *f_NbIterMax_pu16 = (t_uint16)(f_domTotalStep_u32 + chunckSize_u32 - 1) / chunckSize_u32;

    return ;
}

/*********************************
 * GTRY_SPEC_Algo_DistribInitialPulse
 *********************************/
static void GTRY_SPEC_Algo_DistribInitialPulse( t_uint32 f_PulsesToMake_au32[GTRY_PHYS_AXE_NB], 
                                                t_eGTRY_PhysicalAxe f_domAxe_e,
                                                t_uint16  f_NbIterMax_u16)
{
    switch(g_param_s.computeType_e)
    {
        case GTRY_ALGO_COMPUTE_TYPE_BALANCED:
            GTRY_SPEC_DistribInitPulse_Balanced(f_PulsesToMake_au32[GTRY_PHYS_AXE_NB], 
                                                f_domAxe_e,
                                                f_NbIterMax_u16);
        break;
        case GTRY_ALGO_COMPUTE_TYPE_X_BURSTFIRST:
            GTRY_SPEC_DistribInitPulse_BurstFirst(  f_PulsesToMake_au32[GTRY_PHYS_AXE_NB], 
                                                    f_domAxe_e,
                                                    f_NbIterMax_u16,
                                                    GTRY_PHYS_AXE_X);
        break;
        case GTRY_ALGO_COMPUTE_TYPE_Y_BURSTFIRST:
            GTRY_SPEC_DistribInitPulse_BurstFirst(  f_PulsesToMake_au32[GTRY_PHYS_AXE_NB], 
                                                f_domAxe_e,
                                                f_NbIterMax_u16,
                                                GTRY_PHYS_AXE_Y);
        break;
        case GTRY_ALGO_COMPUTE_TYPE_Z_BURSTFIRST:
            GTRY_SPEC_DistribInitPulse_BurstFirst(  f_PulsesToMake_au32[GTRY_PHYS_AXE_NB], 
                                                    f_domAxe_e,
                                                    f_NbIterMax_u16,
                                                    GTRY_PHYS_AXE_Z);
        break;
        case GTRY_ALGO_COMPUTE_TYPE_X_PRIORITY:
            GTRY_SPEC_DistribInitPulse_Priority( f_PulsesToMake_au32[GTRY_PHYS_AXE_NB], 
                                                f_domAxe_e,
                                                f_NbIterMax_u16,
                                                GTRY_PHYS_AXE_X);
        break;
        case GTRY_ALGO_COMPUTE_TYPE_Y_PRIORITY:
            GTRY_SPEC_DistribInitPulse_Priority(f_PulsesToMake_au32[GTRY_PHYS_AXE_NB], 
                                                f_domAxe_e,
                                                f_NbIterMax_u16,
                                                GTRY_PHYS_AXE_Y);
        break;
        case GTRY_ALGO_COMPUTE_TYPE_Z_PRIORITY:
            GTRY_SPEC_DistribInitPulse_Priority(f_PulsesToMake_au32[GTRY_PHYS_AXE_NB], 
                                                f_domAxe_e,
                                                f_NbIterMax_u16,
                                                GTRY_PHYS_AXE_Z);
        break;
        default:
                ASSERT((t_uint16)g_param_s.computeType_e);
        break;
        
    }
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
