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
#include "APP_LGC/Src/Agents/Gantry/Src/GANTRY.h"
#include "APP_CFG/ConfigFiles/APPACT_ConfigPublic.h"
#include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
#include "Constant.h"
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
static t_sGTRYSPEC_AlgoParameter g_param_s;

///@brief Pulse remaining when pass to uint32 to float32 etc
static t_float32 g_axePulseRemain_af32[GTRY_PHYS_AXE_NB];

///@brief Pulse calculation buffer
static t_uint16 g_IterCmd_au16[GTRY_PHYS_AXE_NB][GTRY_MAX_ITERATION];
///@brief global variable to know when to start ditrib left pulse, use on several 
///         function which has no common proper way to get this parameter 
static t_uint16 g_startDistribIdxITerCmd_u16 = (t_sint32)0;
static t_uint16 g_endIdxPulsePrio_u16 = (t_sint32)0;
///@brief know if param received 
static t_bool g_AlgoPrmInit_b = False;
//****************************************************************************
//                      Local functions - Prototypes
//****************************************************************************
/**
 * @brief This function handle the Safety state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return void
 */
static void s_GTRY_SPEC_Algo_ComputeSteps(  t_float32 f_targetPos_af32[GTRY_PHYS_AXE_NB],
                                            t_float32 f_currPos_af32[GTRY_PHYS_AXE_NB],
                                            t_float32 f_missPulses_af32[GTRY_PHYS_AXE_NB],
                                            t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                            t_sint32 f_pulseSigns_as32[GTRY_PHYS_AXE_NB]);
/**
 * @brief This function handle the Safety state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return void
 */
static void s_GTRY_SPEC_Algo_ComputeChunkCount(   t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                t_eGTRY_AlgoComputeType f_algoCpteType_e,
                                                t_uint16 * f_NbIterMax_pu16);
/**
 * @brief This function handle the Safety state of State Machine
  * ----------------------------------------------------------------------------
 * @param[in] f_pulseToMake_au32 : pulse to make for each axe
 * @param[in] f_domninantAxe_e : Dominnant axe
 * @param[in] f_pulseToMake_au32 : Number of iterations to make
 * ----------------------------------------------------------------------------d
 * @return void
 */
static void s_GTRY_SPEC_Algo_DistribInitialPulse( t_eGTRY_AlgoComputeType f_computeType_e, 
                                                t_uint32 f_PulsesToMake_au32[GTRY_PHYS_AXE_NB],
                                                t_uint16  f_NbIterMax_u16);
/**
 * @brief Iteration are distribute using average method 
 * ----------------------------------------------------------------------------
 * @param[in] f_pulseToMake_au32 : pulse to make for each axe
 * @param[in] f_domninantAxe_e : Dominnant axe
 * @param[in] f_pulseToMake_au32 : Number of iterations to make
 * ----------------------------------------------------------------------------
 * @return void
 */
static void s_GTRY_SPEC_DistribInitPulse_Balanced(const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                  t_uint16 f_nbIterMax_u16);
/**
 * @brief  Iteration are distribute in burst first 
 * ----------------------------------------------------------------------------
 * @param[in] f_pulseToMake_au32 : pulse to make for each axe
 * @param[in] f_domninantAxe_e : Dominnant axe
 * @param[in] f_pulseToMake_au32 : Number of iterations to make
 * @param[in] f_AxeBurstFirst_e : which axe to make burst first
 * ----------------------------------------------------------------------------
 * @return void
 */
static void s_GTRY_SPEC_DistribInitPulse_BurstFirst(  const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                    t_uint16 f_nbIterMax_u16,
                                                    t_eGTRY_PhysicalAxe f_AxeBurstFirst_e);
/**
 * @brief This function handle the Safety state of State Machine
 * ----------------------------------------------------------------------------
 * @param[in] f_pulseToMake_au32 : pulse to make for each axe
 * @param[in] f_iterCmd_pas : Iterations cmd pointor
 * @param[in] f_pulseToMake_au32 : Number of iterations to make
 * @param[in] f_AxeBurstFirst_e : which axe to be prioritized
 * ----------------------------------------------------------------------------
 * @return void
 */
static void s_GTRY_SPEC_DistribInitPulse_Priority(const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                t_uint16 f_nbIterMax_u16,
                                                t_eGTRY_PhysicalAxe f_AxePriority_e);
/**
 * @brief This function handle the Safety state of State Machine
 * ----------------------------------------------------------------------------
 * @param[in] f_pulseToMake_au32 : pulse to make for each axe
 * @param[in] f_factor_s32 : factor pulse
 * @param[in] f_nbPulses_u32 : Number of pulse 
 * @param[in] f_nbIter_u16 : Number of iterations to make
 * ----------------------------------------------------------------------------
 * @return void 
 */
static void s_GTRY_SPEC_Algo_SplitSingleIter(t_uint16 f_nbIterMax_u16);
/**
 * @brief This function handle the Safety state of State Machine
 * ----------------------------------------------------------------------------
 * @param[in] f_pulseToMake_au32 : pulse to make for each axe
 * @param[in] f_factor_s32 : factor pulse
 * @param[in] f_nbPulses_u32 : Number of pulse 
 * @param[in] f_nbIter_u16 : Number of iterations to make
 * ----------------------------------------------------------------------------
 * @return void 
 */
static void s_GTRY_SPEC_Algo_AdjustLastIter(t_eGTRY_AlgoComputeType f_computeType_e,
                                            t_uint16 f_nbIterMax_u16);
/**
 * @brief This function handle the Safety state of State Machine
 * ----------------------------------------------------------------------------
 * @param[in] f_pulseToMake_au32 : pulse to make for each axe
 * @param[in] f_factor_s32 : factor pulse
 * @param[in] f_nbPulses_u32 : Number of pulse 
 * @param[in] f_nbIter_u16 : Number of iterations to make
 * ----------------------------------------------------------------------------
 * @return void 
 */
static t_eReturnCode s_GTRY_SPEC_Algo_BuildIterations(  t_eGTRY_AlgoComputeType f_computeType_e,
                                                        t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                        t_sint32 f_pulseSigns_as32[GTRY_PHYS_AXE_NB],
                                                        t_sLIBQUEUE_QueueCore f_QueueAxeMngmt_as[GTRY_PHYS_AXE_NB],
                                                        t_uint16 f_nbIterMax_u16);
/**
 * @brief This function handle the Safety state of State Machine
 * ----------------------------------------------------------------------------
 * @param[in] f_axe_e : axe to distribute last pulse
 * @param[in] f_factor_s32 : factor pulse
 * @param[in] f_nbPulses_u32 : Number of pulse 
 * @param[in] f_nbIter_u16 : Number of iterations to make
 * @param[in] f_startIterIdx_u16 : start distribIdx
 * ----------------------------------------------------------------------------
 * @return void
 */
static void s_GTRY_SPEC_DistribLastPulse( t_eGTRY_PhysicalAxe f_axe_e,
                                        t_sint32 f_factor_s32,
                                        t_uint32 f_nbPulses_u32,
                                        t_uint16 f_nbIter_u16,
                                        t_uint16 f_startIterIdx_u16);
/**
 * @brief This function handle the Safety state of State Machine
 * ----------------------------------------------------------------------------
 * @param[in] f_axe_e : axe to distribute last pulse
 * @param[in] f_factor_s32 : factor pulse
 * @param[in] f_nbPulses_u32 : Number of pulse 
 * @param[in] f_nbIter_u16 : Number of iterations to make
 * ----------------------------------------------------------------------------
 * @return void
 */
static void s_GTRY_SPEC_GetDominantAxeInfo(  const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                            t_eGTRY_PhysicalAxe * f_domAxe_pe,
                                            t_uint32 * f_totalPulse_pu32);
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

        bufferCmdPos_af32[GTRY_PHYS_AXE_X] = rayon_f32 * cosf(phi_f32) * cosf(theta_f32);
        bufferCmdPos_af32[GTRY_PHYS_AXE_Y] = rayon_f32 * cosf(phi_f32) * sinf(theta_f32);
        bufferCmdPos_af32[GTRY_PHYS_AXE_Z] = rayon_f32 * sinf(phi_f32);

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
    t_float32 axePos_af32[GTRY_PHYS_AXE_NB];
    t_uAPPSPM_PrmValType pulseperMmAxeXID_u = {.prmVal_u16 = 0};
    t_uAPPSPM_PrmValType pulseperMmAxeYID_u = {.prmVal_u16 = 0};
    t_uAPPSPM_PrmValType pulseperMmAxeZID_u = {.prmVal_u16 = 0};
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
        Ret_e = GTRY_GetPosition(axePos_af32);

        //---- 2- getpulse per mm parameter for each axe ---//
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_AXE_X_PULSE_PER_MM, 
                                    &pulseperMmAxeXID_u);
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_AXE_Y_PULSE_PER_MM, 
                                        &pulseperMmAxeYID_u);
            }
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_AXE_Z_PULSE_PER_MM, 
                                        &pulseperMmAxeZID_u);
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
        //----4- start initializong buffer cmdd pos with current pos ----//
        bufferCmdPos_af32[GTRY_PHYS_AXE_X] = axePos_af32[GTRY_PHYS_AXE_X];
        bufferCmdPos_af32[GTRY_PHYS_AXE_Y] = axePos_af32[GTRY_PHYS_AXE_Y];
        bufferCmdPos_af32[GTRY_PHYS_AXE_Z] = axePos_af32[GTRY_PHYS_AXE_Z];
        //--- 5- Compute new position target ----//
        bufferCmdPos_af32[GTRY_PHYS_AXE_X] += (f_value_af32[GTRY_CMD_SIG_STEP_X] 
                                            * (t_float32)pulseperMmAxeXID_u.prmVal_u16 
                                            * factorAxeX_f32);
        bufferCmdPos_af32[GTRY_PHYS_AXE_Y] += (f_value_af32[GTRY_CMD_SIG_STEP_Y] 
                                            * (t_float32)pulseperMmAxeXID_u.prmVal_u16 
                                            * factorAxeY_f32);
        bufferCmdPos_af32[GTRY_PHYS_AXE_Z] += (f_value_af32[GTRY_CMD_SIG_STEP_Z] 
                                            * (t_float32)pulseperMmAxeXID_u.prmVal_u16
                                            * factorAxeZ_f32);
        //---- 6- inster in pos Queue Cmd ----//
        Ret_e = LIBQUEUE_WriteElement(  f_QueuePosCmd_ps,
                                        bufferCmdPos_af32,
                                        sizeof(t_float32) * GTRY_PHYS_AXE_NB);
    }

    return Ret_e;
}

/*********************************
 * GANTRY_SPEC_AlgorithmSetParam
 *********************************/
t_eReturnCode GANTRY_SPEC_AlgorithmSetParam(t_sGTRYSPEC_AlgoParameter f_Parameter_s)
{
    t_eGTRY_PhysicalAxe idxAxe_e;
    g_param_s.chunkSize_u16 = f_Parameter_s.chunkSize_u16;

    for(idxAxe_e = GTRY_PHYS_AXE_HEAD ; idxAxe_e < GTRY_PHYS_AXE_NB ; idxAxe_e++)
    {
        g_param_s.MaxFreq_af32[idxAxe_e] = f_Parameter_s.MaxFreq_af32[idxAxe_e];
        g_param_s.MinFreq_af32[idxAxe_e] = f_Parameter_s.MinFreq_af32[idxAxe_e];
        g_param_s.pulsePerMm_af32[idxAxe_e] = f_Parameter_s.pulsePerMm_af32[idxAxe_e];
        g_param_s.cptPrio_SafeHeight_af32[idxAxe_e] = f_Parameter_s.cptPrio_SafeHeight_af32[idxAxe_e];
        g_axePulseRemain_af32[idxAxe_e] = 0.0f;
    }

    g_AlgoPrmInit_b = True;

    return RC_OK;
}

/*********************************
 * GANTRY_SPEC_AlgorithmCompute
 *********************************/
t_eReturnCode GANTRY_SPEC_AlgorithmCompute( t_eGTRY_AlgoComputeType f_computeType_e,
                                            t_float32 f_targetPos_af32[GTRY_PHYS_AXE_NB],
                                            t_float32 f_currPos_af32[GTRY_PHYS_AXE_NB],
                                            t_float32 f_missPulses_af32[GTRY_PHYS_AXE_NB],
                                            t_sLIBQUEUE_QueueCore f_QueueIterCmd_as[GTRY_PHYS_AXE_NB])
{
    t_eReturnCode Ret_e;
    t_uint32 pulseTomake_au32[GTRY_PHYS_AXE_NB] = {0,0,0};
    t_sint32 pulseSigns_as32[GTRY_PHYS_AXE_NB] = {1,1,1};
    t_uint16 nbIterMax_u16 = 0;
    t_uint8 QueueXLeft_u8, QueueYLeft_u8, QueueZLeft_u8;

    if((f_currPos_af32 == NULL) || 
       (f_targetPos_af32 == NULL) || (f_missPulses_af32 == NULL) || 
       (f_QueueIterCmd_as == NULL))
    {
        ASSERT((t_uint16)0);
        return RC_ERROR_PTR_NULL;
    }
    else if(g_AlgoPrmInit_b == false)
    {
        return RC_ERROR_MODULE_NOT_INITIALIZED;
    }

    Ret_e = RC_OK;
    g_startDistribIdxITerCmd_u16 = (t_sint32)0;
    g_endIdxPulsePrio_u16 = (t_sint32)0;
    //---- 1- Compute steps and dominant axis ----//
    s_GTRY_SPEC_Algo_ComputeSteps(f_targetPos_af32, 
                                f_currPos_af32,
                                f_missPulses_af32,
                                pulseTomake_au32,
                                pulseSigns_as32);

    //---- 2- Compute number of iterations ----//
    s_GTRY_SPEC_Algo_ComputeChunkCount(pulseTomake_au32, f_computeType_e, &nbIterMax_u16);

    //---- 3- Check queues ----//
    LIBQUEUE_GetSizeLeft(&f_QueueIterCmd_as[GTRY_PHYS_AXE_X], &QueueXLeft_u8);
    LIBQUEUE_GetSizeLeft(&f_QueueIterCmd_as[GTRY_PHYS_AXE_Y], &QueueYLeft_u8);
    LIBQUEUE_GetSizeLeft(&f_QueueIterCmd_as[GTRY_PHYS_AXE_Z], &QueueZLeft_u8);

    if((QueueXLeft_u8 < nbIterMax_u16) 
    || (QueueYLeft_u8 < nbIterMax_u16) 
    || (QueueZLeft_u8 < nbIterMax_u16))
    {
        return RC_WARNING_LIMIT_REACHED;
    }

    if(nbIterMax_u16 > GTRY_MAX_ITERATION)
    {
        return RC_ERROR_LIMIT_REACHED;
    }

    //---- 4- Distribute pulses ----//
    s_GTRY_SPEC_Algo_DistribInitialPulse(f_computeType_e, pulseTomake_au32, nbIterMax_u16);

    //---- 5- Handle single iteration ----//
    if(nbIterMax_u16 == 1)
    {
        nbIterMax_u16 = 2;
        s_GTRY_SPEC_Algo_SplitSingleIter(nbIterMax_u16);
    }

    //---- 6- Adjust last iteration ----//
    s_GTRY_SPEC_Algo_AdjustLastIter(f_computeType_e, nbIterMax_u16);

    //---- 7- Build iterations ----//
    Ret_e = s_GTRY_SPEC_Algo_BuildIterations(   f_computeType_e,
                                                pulseTomake_au32,
                                                pulseSigns_as32,
                                                f_QueueIterCmd_as,
                                                nbIterMax_u16);

    return Ret_e;
}

/*********************************
 * s_GTRY_SPEC_Algo_ComputeSteps
 *********************************/
static void s_GTRY_SPEC_Algo_ComputeSteps(t_float32 f_targetPos_af32[GTRY_PHYS_AXE_NB],
                                        t_float32 f_currPos_af32[GTRY_PHYS_AXE_NB],
                                        t_float32 f_missPulses_af32[GTRY_PHYS_AXE_NB],
                                        t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                        t_sint32 f_pulseSigns_as32[GTRY_PHYS_AXE_NB])
{
    t_eGTRY_PhysicalAxe idxAxe_e;
    t_float32 exactStepToMake_f32;
    t_sint32 realStepToMake_s32;
    t_uint32 axeDomPulses_u32 = 0;

    for(idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
    {
        exactStepToMake_f32 = (f_targetPos_af32[idxAxe_e] - f_currPos_af32[idxAxe_e]) *
                               g_param_s.pulsePerMm_af32[idxAxe_e] +
                               g_axePulseRemain_af32[idxAxe_e] +
                               f_missPulses_af32[idxAxe_e];

        realStepToMake_s32 = (t_sint32)roundf(exactStepToMake_f32);

        if(realStepToMake_s32 >= 0)
        {
            f_pulseSigns_as32[idxAxe_e] = 1;
            f_pulseToMake_au32[idxAxe_e] = (t_uint32)realStepToMake_s32;
        }
        else
        {
            f_pulseSigns_as32[idxAxe_e] = -1;
            f_pulseToMake_au32[idxAxe_e] = (t_uint32)(-realStepToMake_s32);
        }

        if(f_pulseToMake_au32[idxAxe_e] > axeDomPulses_u32)
        {
            axeDomPulses_u32 = f_pulseToMake_au32[idxAxe_e];
        }

        g_axePulseRemain_af32[idxAxe_e] = exactStepToMake_f32 - (t_float32)realStepToMake_s32;
    }

    return;
}

/*********************************
 * s_GTRY_SPEC_Algo_ComputeChunkCount
 *********************************/
static void s_GTRY_SPEC_Algo_ComputeChunkCount(   t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                t_eGTRY_AlgoComputeType f_algoCpteType_e,
                                                t_uint16 * f_NbIterMax_pu16)
{
    t_uint32 totalPulse_u32;
    t_uint32 prioAxetotalPulse_u32;
    t_uint32 prioStep_u32;
    t_eGTRY_PhysicalAxe axeDom_e = GTRY_PHYS_AXE_NB;
    t_uint32 CpteTypepulseToMake_au32[GTRY_PHYS_AXE_NB] = {f_pulseToMake_au32[GTRY_PHYS_AXE_X], f_pulseToMake_au32[GTRY_PHYS_AXE_Y], f_pulseToMake_au32[GTRY_PHYS_AXE_Z]};
    s_GTRY_SPEC_GetDominantAxeInfo(f_pulseToMake_au32, &axeDom_e, &totalPulse_u32);
    t_uint32 chunkSize_u32 = (t_uint32)g_param_s.chunkSize_u16;

    switch(f_algoCpteType_e)
    {
        case GTRY_ALGO_COMPUTE_TYPE_BALANCED:
            *f_NbIterMax_pu16 = (t_uint16)((totalPulse_u32 + chunkSize_u32 - 1) / chunkSize_u32);
        break;
        case GTRY_ALGO_COMPUTE_TYPE_X_BURSTFIRST:
            //---- in this compute type, X will not be the 
            //      dominant axes because every pulses 
            //  will be made in 1 or 2 iterations ----//
            if(axeDom_e == GTRY_PHYS_AXE_X)
            {
                CpteTypepulseToMake_au32[GTRY_PHYS_AXE_X] = 0;
                s_GTRY_SPEC_GetDominantAxeInfo(CpteTypepulseToMake_au32, &axeDom_e, &totalPulse_u32);
                
            }

            *f_NbIterMax_pu16 = (t_uint16)((totalPulse_u32 + chunkSize_u32 - 1) / chunkSize_u32);
        break;
        case GTRY_ALGO_COMPUTE_TYPE_Y_BURSTFIRST:
            //---- in this compute type, X will not be the 
            //      dominant axes because every pulses 
            //  will be made in 1 or 2 iterations ----//
            if(axeDom_e == GTRY_PHYS_AXE_Y)
            {
                CpteTypepulseToMake_au32[GTRY_PHYS_AXE_Y] = 0;
                s_GTRY_SPEC_GetDominantAxeInfo(CpteTypepulseToMake_au32, &axeDom_e, &totalPulse_u32);
                
            }
            
            *f_NbIterMax_pu16 = (t_uint16)((totalPulse_u32 + chunkSize_u32 - 1) / chunkSize_u32);
        break;
        case GTRY_ALGO_COMPUTE_TYPE_Z_BURSTFIRST:
            //---- in this compute type, X will not be the 
            //      dominant axes because every pulses 
            //  will be made in 1 or 2 iterations ----//
            if(axeDom_e == GTRY_PHYS_AXE_Z)
            {
                CpteTypepulseToMake_au32[GTRY_PHYS_AXE_Z] = 0;
                s_GTRY_SPEC_GetDominantAxeInfo(CpteTypepulseToMake_au32, &axeDom_e, &totalPulse_u32);
                
            }

            *f_NbIterMax_pu16 = (t_uint16)((totalPulse_u32 + chunkSize_u32 - 1) / chunkSize_u32);
        break;
        case GTRY_ALGO_COMPUTE_TYPE_X_PRIORITY:
            prioStep_u32 = (t_uint32)(g_param_s.cptPrio_SafeHeight_af32[GTRY_PHYS_AXE_X] 
                                        * g_param_s.pulsePerMm_af32[GTRY_PHYS_AXE_X]);
            prioAxetotalPulse_u32 = totalPulse_u32;
            //---- get the pulse to make after prio alone passed ----//
            CpteTypepulseToMake_au32[GTRY_PHYS_AXE_X] = 0;
            s_GTRY_SPEC_GetDominantAxeInfo(CpteTypepulseToMake_au32, &axeDom_e, &totalPulse_u32);          
                
            if(totalPulse_u32 > (prioAxetotalPulse_u32 - prioStep_u32))
            {
                totalPulse_u32 = prioStep_u32 + totalPulse_u32; 
            }
            else 
            {
                totalPulse_u32 = prioAxetotalPulse_u32;
            }            
     
            *f_NbIterMax_pu16 = (t_uint16)((totalPulse_u32 + chunkSize_u32 - 1) / chunkSize_u32);
        break;
        case GTRY_ALGO_COMPUTE_TYPE_Y_PRIORITY:
            prioStep_u32 = (t_uint32)(g_param_s.cptPrio_SafeHeight_af32[GTRY_PHYS_AXE_Y] 
                                        * g_param_s.pulsePerMm_af32[GTRY_PHYS_AXE_Y]);
            prioAxetotalPulse_u32 = totalPulse_u32;
            //---- get the pulse to make after prio alone passed ----//
            CpteTypepulseToMake_au32[GTRY_PHYS_AXE_Y] = 0;
            s_GTRY_SPEC_GetDominantAxeInfo(CpteTypepulseToMake_au32, &axeDom_e, &totalPulse_u32);          
                
            if(totalPulse_u32 > (prioAxetotalPulse_u32 - prioStep_u32))
            {
                totalPulse_u32 = prioStep_u32 + totalPulse_u32; 
            }
            else 
            {
                totalPulse_u32 = prioAxetotalPulse_u32;
            }            
     
            *f_NbIterMax_pu16 = (t_uint16)((totalPulse_u32 + chunkSize_u32 - 1) / chunkSize_u32);
        break;
        case GTRY_ALGO_COMPUTE_TYPE_Z_PRIORITY:
            prioStep_u32 = (t_uint32)(g_param_s.cptPrio_SafeHeight_af32[GTRY_PHYS_AXE_Z] 
                                        * g_param_s.pulsePerMm_af32[GTRY_PHYS_AXE_Z]);
            prioAxetotalPulse_u32 = totalPulse_u32;
            //---- get the pulse to make after prio alone passed ----//
            CpteTypepulseToMake_au32[GTRY_PHYS_AXE_Z] = 0;
            s_GTRY_SPEC_GetDominantAxeInfo(CpteTypepulseToMake_au32, &axeDom_e, &totalPulse_u32);          
                
            if(totalPulse_u32 > (prioAxetotalPulse_u32 - prioStep_u32))
            {
                totalPulse_u32 = prioStep_u32 + totalPulse_u32; 
            }
            else 
            {
                totalPulse_u32 = prioAxetotalPulse_u32;
            }            
     
            *f_NbIterMax_pu16 = (t_uint16)((totalPulse_u32 + chunkSize_u32 - 1) / chunkSize_u32);
        break;
        case GTRY_ALGO_COMPUTE_TYPE_NB:
        default:
            ASSERT((t_uint16)0);
    }

    
}

/*********************************
 * s_GTRY_SPEC_Algo_DistribInitialPulse
 *********************************/
static void s_GTRY_SPEC_Algo_DistribInitialPulse(t_eGTRY_AlgoComputeType f_computeType_e,
                                               t_uint32 f_PulsesToMake_au32[GTRY_PHYS_AXE_NB],
                                               t_uint16 f_NbIterMax_u16)
{
    switch(f_computeType_e)
    {
        case GTRY_ALGO_COMPUTE_TYPE_BALANCED:
            s_GTRY_SPEC_DistribInitPulse_Balanced(f_PulsesToMake_au32, f_NbIterMax_u16);
            break;
        case GTRY_ALGO_COMPUTE_TYPE_X_BURSTFIRST:
            s_GTRY_SPEC_DistribInitPulse_BurstFirst(f_PulsesToMake_au32, f_NbIterMax_u16, GTRY_PHYS_AXE_X);
            break;
        case GTRY_ALGO_COMPUTE_TYPE_Y_BURSTFIRST:
            s_GTRY_SPEC_DistribInitPulse_BurstFirst(f_PulsesToMake_au32, f_NbIterMax_u16, GTRY_PHYS_AXE_Y);
            break;
        case GTRY_ALGO_COMPUTE_TYPE_Z_BURSTFIRST:
            s_GTRY_SPEC_DistribInitPulse_BurstFirst(f_PulsesToMake_au32, f_NbIterMax_u16, GTRY_PHYS_AXE_Z);
            break;
        case GTRY_ALGO_COMPUTE_TYPE_X_PRIORITY:
            s_GTRY_SPEC_DistribInitPulse_Priority(f_PulsesToMake_au32, f_NbIterMax_u16, GTRY_PHYS_AXE_X);
            break;
        case GTRY_ALGO_COMPUTE_TYPE_Y_PRIORITY:
            s_GTRY_SPEC_DistribInitPulse_Priority(f_PulsesToMake_au32, f_NbIterMax_u16, GTRY_PHYS_AXE_Y);
            break;
        case GTRY_ALGO_COMPUTE_TYPE_Z_PRIORITY:
            s_GTRY_SPEC_DistribInitPulse_Priority(f_PulsesToMake_au32, f_NbIterMax_u16, GTRY_PHYS_AXE_Z);
            break;
        default:
            ASSERT((t_uint16)f_computeType_e);
            break;
    }

    return;
}

/*********************************
 * s_GTRY_SPEC_DistribInitPulse_Balanced
 *********************************/
static void s_GTRY_SPEC_DistribInitPulse_Balanced(const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                  t_uint16 f_nbIterMax_u16)
{
    t_eGTRY_PhysicalAxe idxAxe_e;
    t_sint32 idxIter_s32;
    t_uint32 chunkSize_u32 = (t_uint32)g_param_s.chunkSize_u16;
    t_uint32 dominantTotalPulse_u32 = 0;
    s_GTRY_SPEC_GetDominantAxeInfo(f_pulseToMake_au32, NULL, &dominantTotalPulse_u32);

    for(idxAxe_e = GTRY_PHYS_AXE_HEAD ; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
    {
        t_uint32 sumPulseGive_u32 = 0;
        for(idxIter_s32 = 0; idxIter_s32 < (t_sint32)f_nbIterMax_u16; idxIter_s32++)
        {
            g_IterCmd_au16[idxAxe_e][idxIter_s32] = (t_uint16)(
                (f_pulseToMake_au32[idxAxe_e] * chunkSize_u32) 
                / dominantTotalPulse_u32);
            sumPulseGive_u32 += g_IterCmd_au16[idxAxe_e][idxIter_s32];
        }

        t_sint32 correction_s32 = (t_sint32)f_pulseToMake_au32[idxAxe_e] - (t_sint32)sumPulseGive_u32;
        if(correction_s32 != 0)
        {
            t_sint32 factorCorrection_s32 = (correction_s32 > 0) ? 1 : -1;
            if(factorCorrection_s32 < 0)
            {
                correction_s32 = -correction_s32;
            }

            s_GTRY_SPEC_DistribLastPulse(idxAxe_e, factorCorrection_s32, (t_uint32)correction_s32, f_nbIterMax_u16, 0u);
        }
    }

    return;
}

/*********************************
 * s_GTRY_SPEC_DistribInitPulse_BurstFirst
 *********************************/
static void s_GTRY_SPEC_DistribInitPulse_BurstFirst(  const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                    t_uint16 f_nbIterMax_u16,
                                                    t_eGTRY_PhysicalAxe f_AxeBurstFirst_e)
{
    t_eGTRY_PhysicalAxe idxAxe_e;
    t_uint32 PulseDone_au32[GTRY_PHYS_AXE_NB] = {0,0,0};
    t_uint32 domAxeTotalPulse_u32;
    t_bool isStartDistribChange_b = False;
    t_uint32 newPulseToMake_ua32[GTRY_PHYS_AXE_NB] = {f_pulseToMake_au32[GTRY_PHYS_AXE_X], f_pulseToMake_au32[GTRY_PHYS_AXE_Y], f_pulseToMake_au32[GTRY_PHYS_AXE_Z]};
    newPulseToMake_ua32[f_AxeBurstFirst_e] = 0;

    s_GTRY_SPEC_GetDominantAxeInfo(newPulseToMake_ua32, NULL, &domAxeTotalPulse_u32);

    for(idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
    {
        for(t_sint32 idxIter_s32 = 0; idxIter_s32 < (t_sint32)f_nbIterMax_u16; idxIter_s32++)
        {
            t_uint32 pulseCmpte_u32 = 0;
            if(idxAxe_e == f_AxeBurstFirst_e)
            {
                if(PulseDone_au32[f_AxeBurstFirst_e] < f_pulseToMake_au32[f_AxeBurstFirst_e])
                {
                    pulseCmpte_u32 = (f_pulseToMake_au32[f_AxeBurstFirst_e] - PulseDone_au32[f_AxeBurstFirst_e]);
                    if(pulseCmpte_u32 > 0xEA60) // 60000, leave a range in case we have to add some pulse
                    {
                        pulseCmpte_u32 = 0xEA60 ;
                    }
                    //---- make sure we're always have 2 iterations, one to put at maximum and the others
                    //      at minimum for a short amount of pulse
                    //      if the number of iteration is 1, the SplitIteration will deal with it 
                    //      but if > 1 the function is not called ----//
                    if((pulseCmpte_u32 == f_pulseToMake_au32[f_AxeBurstFirst_e])
                    && (f_nbIterMax_u16 > 1))
                    {
                        pulseCmpte_u32 = pulseCmpte_u32 * 0.9f;
                    }
                    g_IterCmd_au16[f_AxeBurstFirst_e][idxIter_s32] = (t_uint16)pulseCmpte_u32;
                    PulseDone_au32[f_AxeBurstFirst_e] += pulseCmpte_u32;
                }
                else
                {
                    if(isStartDistribChange_b == False)
                    {
                        isStartDistribChange_b = True;
                        g_startDistribIdxITerCmd_u16 = (t_uint16)idxIter_s32;
                        g_endIdxPulsePrio_u16 = (t_uint16)idxIter_s32;
                    }
                    g_IterCmd_au16[f_AxeBurstFirst_e][idxIter_s32] = 0;
                }
            }
            else
            {
                pulseCmpte_u32 = ((f_pulseToMake_au32[idxAxe_e] * (t_uint32)g_param_s.chunkSize_u16) / domAxeTotalPulse_u32);
                if(PulseDone_au32[idxAxe_e] + pulseCmpte_u32 > f_pulseToMake_au32[idxAxe_e])
                {
                    pulseCmpte_u32 = f_pulseToMake_au32[idxAxe_e] - PulseDone_au32[idxAxe_e];
                }
                g_IterCmd_au16[idxAxe_e][idxIter_s32] = (t_uint16)pulseCmpte_u32;
                PulseDone_au32[idxAxe_e] += pulseCmpte_u32;
            }
        }
    }
    //--- it means we only have one iteration, but we're about to get both 
    //      'cause we splitting itteration ----//
    if((g_endIdxPulsePrio_u16 == (t_uint16)0)
    && (isStartDistribChange_b == FALSE))
    {
        g_endIdxPulsePrio_u16 = 2;
    }
    // Correction
    for(idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
    {
        t_sint32 correction_s32 = (t_sint32)f_pulseToMake_au32[idxAxe_e] - (t_sint32)PulseDone_au32[idxAxe_e];
        if(correction_s32 != 0)
        {
            t_sint32 factorCorrect_s32 = (correction_s32 > 0) ? 1 : -1;
            if(factorCorrect_s32 < 0) correction_s32 = -correction_s32;
            s_GTRY_SPEC_DistribLastPulse(idxAxe_e, factorCorrect_s32, (t_uint32)correction_s32, f_nbIterMax_u16, 0u);
        }
    }

    return;
}

/*********************************
 * s_GTRY_SPEC_DistribInitPulse_Priority
 *********************************/
static void s_GTRY_SPEC_DistribInitPulse_Priority(const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                t_uint16 f_nbIterMax_u16,
                                                t_eGTRY_PhysicalAxe f_AxePriority_e)
{
    t_eGTRY_PhysicalAxe idxAxe_e;
    t_uint32 PulseDone_au32[GTRY_PHYS_AXE_NB] = {0,0,0};
    t_uint32 pulseToMakeAfterPrioDone_u32[GTRY_PHYS_AXE_NB] = {0,0,0};
    t_uint32 domAxeTotalPulse_u32;
    t_bool isStartDistribChange_b = False;
    t_bool updateChunk_b = FALSE;
    t_uint32 heightTarget_u32 = (t_uint32)g_param_s.cptPrio_SafeHeight_af32[f_AxePriority_e];
    t_uint32 stepToReachTarget_u32 = (t_uint32)((t_float32)heightTarget_u32 * g_param_s.pulsePerMm_af32[f_AxePriority_e]);

    if(stepToReachTarget_u32 > f_pulseToMake_au32[f_AxePriority_e]) 
    {
        stepToReachTarget_u32 = f_pulseToMake_au32[f_AxePriority_e];
    }

    for(t_sint32 idxIter_s32 = 0; idxIter_s32 < (t_sint32)f_nbIterMax_u16; idxIter_s32++)
    {
        t_uint16 pulseAxeCmpte_u16;
        if(PulseDone_au32[f_AxePriority_e] < stepToReachTarget_u32)
        {
            pulseAxeCmpte_u16 = (t_uint16)(f_pulseToMake_au32[f_AxePriority_e] - PulseDone_au32[f_AxePriority_e]);
            if(pulseAxeCmpte_u16 > g_param_s.chunkSize_u16)
            {
                //---- only for idx prio, else 0 ----//
                pulseAxeCmpte_u16 = g_param_s.chunkSize_u16;
            }
            else if(pulseAxeCmpte_u16 > stepToReachTarget_u32)
            {
                pulseAxeCmpte_u16 = (t_uint16)stepToReachTarget_u32;
            }

            PulseDone_au32[f_AxePriority_e] += pulseAxeCmpte_u16;

            for(idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
            {
                g_IterCmd_au16[idxAxe_e][idxIter_s32] = (idxAxe_e == f_AxePriority_e) ? pulseAxeCmpte_u16 : 0;
            }
        }
        else
        {
            //---- upsate distrib start idx ----//
            if(isStartDistribChange_b == False)
            {
                t_uint16 lastPulse_u16;
                
                //---- create a last iteration for ramp signal for the priority axes, that is not too long  ----//
                if(idxIter_s32 != (t_uint32)(f_nbIterMax_u16 - 1))
                {
                    
                    if((PulseDone_au32[f_AxePriority_e] == f_pulseToMake_au32[f_AxePriority_e]))
                    {
                        lastPulse_u16 = (t_uint16)(0.15f * g_param_s.MinFreq_af32[f_AxePriority_e]);
                        if(g_IterCmd_au16[f_AxePriority_e][(idxIter_s32 - 1)] > lastPulse_u16)
                        {
                            isStartDistribChange_b = True;
                            //--- else less that way ----//
                            if(idxIter_s32 > (t_sint32)2)
                            {
                                s_GTRY_SPEC_DistribLastPulse(f_AxePriority_e,     
                                    (t_sint32)1, 
                                    (t_uint32)(g_IterCmd_au16[f_AxePriority_e][(idxIter_s32 - 1)] - lastPulse_u16),
                                    (t_uint16)(idxIter_s32 - 2),
                                    (t_uint16)0);
                                    
                            }
                            else
                            {
                                g_IterCmd_au16[f_AxePriority_e][0] += (g_IterCmd_au16[f_AxePriority_e][(idxIter_s32 - 1)] - lastPulse_u16);
                            }

                            g_IterCmd_au16[f_AxePriority_e][(idxIter_s32 - 1)] = lastPulse_u16;
                        }

                        g_endIdxPulsePrio_u16 = (t_uint16)idxIter_s32;
                    }
                }
                if(updateChunk_b == FALSE)
                {
                    g_startDistribIdxITerCmd_u16 = (t_sint32)idxIter_s32;
                    updateChunk_b = TRUE;
                    //--- update the domainant axis now that we finish the prio axe ----//
                    for(idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
                    {
                        pulseToMakeAfterPrioDone_u32[idxAxe_e] = f_pulseToMake_au32[idxAxe_e] - PulseDone_au32[idxAxe_e];

                    }
                    s_GTRY_SPEC_GetDominantAxeInfo(pulseToMakeAfterPrioDone_u32,
                                                    NULL,
                                                    &domAxeTotalPulse_u32);
                }
                
            }
            for(idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
            {
                if(idxAxe_e != f_AxePriority_e)
                {
                    pulseAxeCmpte_u16 = f_pulseToMake_au32[idxAxe_e] * (t_uint32)g_param_s.chunkSize_u16 
                                            / domAxeTotalPulse_u32;
                }
                else 
                {
                    pulseAxeCmpte_u16 = (t_uint16)(f_pulseToMake_au32[f_AxePriority_e] - PulseDone_au32[f_AxePriority_e]);
                    if(pulseAxeCmpte_u16 > g_param_s.chunkSize_u16)
                    {
                        pulseAxeCmpte_u16 = g_param_s.chunkSize_u16;
                    }
                }
                if((PulseDone_au32[idxAxe_e] + (t_uint32)pulseAxeCmpte_u16) > f_pulseToMake_au32[idxAxe_e])
                {
                    pulseAxeCmpte_u16 = (t_uint16)(f_pulseToMake_au32[idxAxe_e] - PulseDone_au32[idxAxe_e]);
                }
                g_IterCmd_au16[idxAxe_e][idxIter_s32] = pulseAxeCmpte_u16;
                PulseDone_au32[idxAxe_e] += pulseAxeCmpte_u16;                
            }
        }
    }
    if((g_endIdxPulsePrio_u16 == (t_sint32)0)
    && (isStartDistribChange_b == FALSE))
    {
        if(f_nbIterMax_u16 > 1)
        {
            g_endIdxPulsePrio_u16 = f_nbIterMax_u16;
        }
        //--- function split will wplit in two iteration
        else 
        {
            g_endIdxPulsePrio_u16 = 2;
        }
    }
    // Correction
    for(idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
    {
        t_sint32 correction_s32 = (t_sint32)f_pulseToMake_au32[idxAxe_e] - (t_sint32)PulseDone_au32[idxAxe_e];
        if(correction_s32 != 0)
        {
            t_sint32 factorCorrect_s32 = (correction_s32 > 0) ? 1 : -1;
            if(factorCorrect_s32 < 0) correction_s32 = -correction_s32;
            s_GTRY_SPEC_DistribLastPulse(idxAxe_e, factorCorrect_s32, (t_uint32)correction_s32, f_nbIterMax_u16, g_startDistribIdxITerCmd_u16);
        }
    }

    return;
}

/*********************************
 * s_GTRY_SPEC_Algo_SplitSingleIter
 *********************************/
static void s_GTRY_SPEC_Algo_SplitSingleIter(t_uint16 f_nbIterMax_u16)
{
    if(f_nbIterMax_u16 != 2)
    {
        ASSERT((t_uint16)f_nbIterMax_u16);
    }

    for(t_eGTRY_PhysicalAxe idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
    {
        t_float32 meanPulses_f32 = (t_float32)g_IterCmd_au16[idxAxe_e][0] / 2.0f;
        t_uint16 leftPulses_u16 = g_IterCmd_au16[idxAxe_e][0] % (t_uint16)2;
        g_IterCmd_au16[idxAxe_e][0] = (t_uint16)meanPulses_f32 + leftPulses_u16;
        g_IterCmd_au16[idxAxe_e][1] = (t_uint16)meanPulses_f32;
    }

    return;
}

/*********************************
 * s_GTRY_SPEC_Algo_AdjustLastIter
 *********************************/
static void s_GTRY_SPEC_Algo_AdjustLastIter(t_eGTRY_AlgoComputeType f_computeType_e,
                                            t_uint16 f_nbIterMax_u16)
{
    t_uint16 smallerPulse_u16 = 0xFFFF;
    t_uint16 pulseLastIter_u16 = 0;

    // Find smallest pulse on last iteration
    for(t_eGTRY_PhysicalAxe idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
    {
        switch(f_computeType_e)
        {
            case GTRY_ALGO_COMPUTE_TYPE_BALANCED:
                pulseLastIter_u16 = g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1];
            break;
            case GTRY_ALGO_COMPUTE_TYPE_X_BURSTFIRST:
                if(idxAxe_e == GTRY_PHYS_AXE_X)
                {
                    pulseLastIter_u16 = g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1];
                }
                else 
                {
                    pulseLastIter_u16 = g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1];
                }
            break;
            case GTRY_ALGO_COMPUTE_TYPE_Y_BURSTFIRST:
                if(idxAxe_e == GTRY_PHYS_AXE_Y)
                {
                    pulseLastIter_u16 = g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1];
                }
                else 
                {
                    pulseLastIter_u16 = g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1];
                }
            break;
            case GTRY_ALGO_COMPUTE_TYPE_Z_BURSTFIRST:
                if(idxAxe_e == GTRY_PHYS_AXE_Z)
                {
                    pulseLastIter_u16 = g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1];
                }
                else 
                {
                    pulseLastIter_u16 = g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1];
                }
            break;
            case GTRY_ALGO_COMPUTE_TYPE_X_PRIORITY:
                if(idxAxe_e == GTRY_PHYS_AXE_X)
                {
                    pulseLastIter_u16 = g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1];
                }
                else 
                {
                    pulseLastIter_u16 = g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1];
                }
            break;
            case GTRY_ALGO_COMPUTE_TYPE_Y_PRIORITY:
                if(idxAxe_e == GTRY_PHYS_AXE_Y)
                {
                    pulseLastIter_u16 = g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1];
                }
                else 
                {
                    pulseLastIter_u16 = g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1];
                }
            break;
            case GTRY_ALGO_COMPUTE_TYPE_Z_PRIORITY:
                if(idxAxe_e == GTRY_PHYS_AXE_Z)
                {
                    pulseLastIter_u16 = g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1];
                }
                else 
                {
                    pulseLastIter_u16 = g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1];
                }
            break;
            case GTRY_ALGO_COMPUTE_TYPE_NB:
            default:
                ASSERT((t_uint16)0);
            break;
        }
        if((pulseLastIter_u16 < smallerPulse_u16)
        && (smallerPulse_u16 > (t_uint16)0))
        {
            smallerPulse_u16 = pulseLastIter_u16;
        }

        if(smallerPulse_u16 == 0xFFFF)
        {
            ASSERT((t_uint16)0);
            smallerPulse_u16 = 1;
        }
        
        
    }

    // Distribute remaining
    for(t_eGTRY_PhysicalAxe idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
    { 
        switch(f_computeType_e)
        {
            case GTRY_ALGO_COMPUTE_TYPE_BALANCED:
                if(g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] != smallerPulse_u16)
                {
                    t_uint32 diffPulses_u32 = (t_uint32)g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] - smallerPulse_u16;
                    g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] = smallerPulse_u16;
                    s_GTRY_SPEC_DistribLastPulse(idxAxe_e, 1, diffPulses_u32, (f_nbIterMax_u16 - (t_uint16)1), 0u);
                }
            break;
            case GTRY_ALGO_COMPUTE_TYPE_X_BURSTFIRST:
                if(idxAxe_e == GTRY_PHYS_AXE_X)
                {
                    if(g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] != smallerPulse_u16)
                    {
                        t_uint32 diffPulses_u32 = (t_uint32)g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] - smallerPulse_u16;
                        g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] = smallerPulse_u16;
                        s_GTRY_SPEC_DistribLastPulse(idxAxe_e, 1, diffPulses_u32, (g_endIdxPulsePrio_u16 - 1), 0u);
                    }
                }
                else 
                {
                    if(g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] != smallerPulse_u16)
                    {
                        t_uint32 diffPulses_u32 = (t_uint32)g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] - smallerPulse_u16;
                        g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] = smallerPulse_u16;
                        s_GTRY_SPEC_DistribLastPulse(idxAxe_e, 1, diffPulses_u32, (f_nbIterMax_u16 - (t_uint16)1), 0);
                    }
                }
            break;
            case GTRY_ALGO_COMPUTE_TYPE_Y_BURSTFIRST:
                if(idxAxe_e == GTRY_PHYS_AXE_Y)
                {
                    if(g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] != smallerPulse_u16)
                    {
                        t_uint32 diffPulses_u32 = (t_uint32)g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] - smallerPulse_u16;
                        g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] = smallerPulse_u16;
                        s_GTRY_SPEC_DistribLastPulse(idxAxe_e, 1, diffPulses_u32, g_endIdxPulsePrio_u16, 0u);
                    }
                }
                else 
                {
                    if(g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] != smallerPulse_u16)
                    {
                        t_uint32 diffPulses_u32 = (t_uint32)g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] - smallerPulse_u16;
                        g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] = smallerPulse_u16;
                        s_GTRY_SPEC_DistribLastPulse(idxAxe_e, 1, diffPulses_u32, (f_nbIterMax_u16 - (t_uint16)1), 0);
                    }
                }
            break;
            case GTRY_ALGO_COMPUTE_TYPE_Z_BURSTFIRST:
                if(idxAxe_e == GTRY_PHYS_AXE_Z)
                {
                    if(g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] != smallerPulse_u16)
                    {
                        t_uint32 diffPulses_u32 = (t_uint32)g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] - smallerPulse_u16;
                        g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] = smallerPulse_u16;
                        s_GTRY_SPEC_DistribLastPulse(idxAxe_e, 1, diffPulses_u32, g_endIdxPulsePrio_u16, 0u);
                    }
                }
                else 
                {
                    if(g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] != smallerPulse_u16)
                    {
                        t_uint32 diffPulses_u32 = (t_uint32)g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] - smallerPulse_u16;
                        g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] = smallerPulse_u16;
                        s_GTRY_SPEC_DistribLastPulse(idxAxe_e, 1, diffPulses_u32, (f_nbIterMax_u16 - (t_uint16)1), 0u);
                    }
                }
            break;
            case GTRY_ALGO_COMPUTE_TYPE_X_PRIORITY:
                if(idxAxe_e == GTRY_PHYS_AXE_X)
                {
                    if(g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] != smallerPulse_u16)
                    {
                        t_uint32 diffPulses_u32 = (t_uint32)g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] - smallerPulse_u16;
                        g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] = smallerPulse_u16;
                        s_GTRY_SPEC_DistribLastPulse(idxAxe_e, 1, diffPulses_u32, (f_nbIterMax_u16 - (t_uint16)1), 0u);
                    }
                }
                else 
                {
                    if(g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] != smallerPulse_u16)
                    {
                        t_uint32 diffPulses_u32 = (t_uint32)g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] - smallerPulse_u16;
                        g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] = smallerPulse_u16;
                        s_GTRY_SPEC_DistribLastPulse(idxAxe_e, 1, diffPulses_u32, (f_nbIterMax_u16 - (t_uint16)1), g_startDistribIdxITerCmd_u16);
                    }
                }
            break;
            case GTRY_ALGO_COMPUTE_TYPE_Y_PRIORITY:
                if(idxAxe_e == GTRY_PHYS_AXE_Y)
                {
                    if(g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] != smallerPulse_u16)
                    {
                        t_uint32 diffPulses_u32 = (t_uint32)g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] - smallerPulse_u16;
                        g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] = smallerPulse_u16;
                        s_GTRY_SPEC_DistribLastPulse(idxAxe_e, 1, diffPulses_u32, (f_nbIterMax_u16 - (t_uint16)1), 0u);
                    }
                }
                else 
                {
                    if(g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] != smallerPulse_u16)
                    {
                        t_uint32 diffPulses_u32 = (t_uint32)g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] - smallerPulse_u16;
                        g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] = smallerPulse_u16;
                        s_GTRY_SPEC_DistribLastPulse(idxAxe_e, 1, diffPulses_u32, (f_nbIterMax_u16 - (t_uint16)1), g_startDistribIdxITerCmd_u16);
                    }
                }
            break;
            case GTRY_ALGO_COMPUTE_TYPE_Z_PRIORITY:
                if(idxAxe_e == GTRY_PHYS_AXE_Z)
                {
                   if(g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] != smallerPulse_u16)
                    {
                        t_uint32 diffPulses_u32 = (t_uint32)g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] - smallerPulse_u16;
                        g_IterCmd_au16[idxAxe_e][g_endIdxPulsePrio_u16 - 1] = smallerPulse_u16;
                        s_GTRY_SPEC_DistribLastPulse(idxAxe_e, 1, diffPulses_u32, (f_nbIterMax_u16 - (t_uint16)1), 0);
                    }
                }
                else 
                {
                    if(g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] != smallerPulse_u16)
                    {
                        t_uint32 diffPulses_u32 = (t_uint32)g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] - smallerPulse_u16;
                        g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] = smallerPulse_u16;
                        s_GTRY_SPEC_DistribLastPulse(idxAxe_e, 1, diffPulses_u32, (f_nbIterMax_u16 - (t_uint16)1), g_startDistribIdxITerCmd_u16);
                    }
                }
            break;
            case GTRY_ALGO_COMPUTE_TYPE_NB:
            default:
                ASSERT((t_uint16)0);
            break;
        }        
    }

    return;
}

/*********************************
 * s_GTRY_SPEC_Algo_BuildIterations
 *********************************/
static t_eReturnCode s_GTRY_SPEC_Algo_BuildIterations(  t_eGTRY_AlgoComputeType f_computeType_e,
                                                        t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                        t_sint32 f_pulseSigns_as32[GTRY_PHYS_AXE_NB],
                                                        t_sLIBQUEUE_QueueCore f_QueueAxeMngmt_as[GTRY_PHYS_AXE_NB],
                                                        t_uint16 f_nbIterMax_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eGTRY_PhysicalAxe domAxe_e;
    t_uint32 dominantPulses_u32;
    t_float32 pulseSafeHeight_f32 = 0.0f;
    t_bool distribFirstPulseForOtherAxes_b[GTRY_PHYS_AXE_NB] = {FALSE, FALSE, FALSE};
    t_uint32 PulseDone_au32[GTRY_PHYS_AXE_NB] = {0,0,0};
    t_bool iterCmdFinish_ab[GTRY_PHYS_AXE_NB] = {FALSE, FALSE, FALSE};
    t_float32 PulseDuration_af32[GTRY_PHYS_AXE_NB] = {0.0f, 0.0f, 0.0f};
    s_GTRY_SPEC_GetDominantAxeInfo(f_pulseToMake_au32, &domAxe_e, &dominantPulses_u32);
    t_sGTRY_MtrCmdIterPayload mtrAxeCmd_s;
    t_uint8 mskPulseActivity_u8 = 0;
    t_sint32 idxIter_s32;
    t_float32 totalTime_f32 = (g_param_s.MaxFreq_af32[domAxe_e] > 0.0f) ? 
                               ((t_float32)dominantPulses_u32 / g_param_s.MaxFreq_af32[domAxe_e]) : 0.0f;

    for(idxIter_s32 = 0; idxIter_s32 < (t_sint32)f_nbIterMax_u16 && Ret_e == RC_OK; idxIter_s32++)
    {
        if(mskPulseActivity_u8 == ((1 << GTRY_PHYS_AXE_X) | (1 << GTRY_PHYS_AXE_Y) | (1 << GTRY_PHYS_AXE_Z)))
        {
            break;
        }
        for(t_eGTRY_PhysicalAxe idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
        {
            mtrAxeCmd_s.frequency_f32 = 0.0f;
            mtrAxeCmd_s.pulses_s32 = 0;
            mtrAxeCmd_s.triggerTimer_f32 = 0.0f;
            PulseDone_au32[idxAxe_e] += g_IterCmd_au16[idxAxe_e][idxIter_s32];
            if(iterCmdFinish_ab[idxAxe_e] == True)
            {
                mtrAxeCmd_s.pulses_s32 = (t_sint32)0;
                mtrAxeCmd_s.frequency_f32 = g_param_s.MinFreq_af32[idxAxe_e]; 
                mtrAxeCmd_s.triggerTimer_f32 = 0.0f;
            }
            else 
            {
                if(PulseDone_au32[idxAxe_e] == f_pulseToMake_au32[idxAxe_e])
                {
                    iterCmdFinish_ab[idxAxe_e] = True;
                    mskPulseActivity_u8 |= idxAxe_e;
                    mtrAxeCmd_s.pulses_s32 = (t_sint32)g_IterCmd_au16[idxAxe_e][idxIter_s32] * f_pulseSigns_as32[idxAxe_e];
                    mtrAxeCmd_s.frequency_f32 = g_param_s.MinFreq_af32[idxAxe_e]; 
                    mtrAxeCmd_s.triggerTimer_f32 = 0.0f;
                }
                else if((idxIter_s32 < (t_sint32)(f_nbIterMax_u16 - 1))
                && (totalTime_f32 > 0.0f))
                {
                    switch(f_computeType_e)
                    {
                        case GTRY_ALGO_COMPUTE_TYPE_BALANCED:
                            mtrAxeCmd_s.pulses_s32 = (t_sint32)g_IterCmd_au16[idxAxe_e][idxIter_s32] * f_pulseSigns_as32[idxAxe_e];
                            mtrAxeCmd_s.frequency_f32 = (t_float32)f_pulseToMake_au32[idxAxe_e] / totalTime_f32;
                            mtrAxeCmd_s.triggerTimer_f32 = 0.0f; // send all ASAP
                        break;
                        case GTRY_ALGO_COMPUTE_TYPE_X_PRIORITY:
                            mtrAxeCmd_s.pulses_s32 = (t_sint32)g_IterCmd_au16[idxAxe_e][idxIter_s32] * f_pulseSigns_as32[idxAxe_e];
                            mtrAxeCmd_s.frequency_f32 = (t_float32)f_pulseToMake_au32[idxAxe_e] / totalTime_f32;

                            pulseSafeHeight_f32 = g_param_s.cptPrio_SafeHeight_af32[GTRY_PHYS_AXE_X] * g_param_s.pulsePerMm_af32[GTRY_PHYS_AXE_X];
                            if((t_float32)PulseDone_au32[GTRY_PHYS_AXE_X] < pulseSafeHeight_f32)
                            {
                                //--- if idxAxe = X send ASAP, if others there are no pulses so we don't case ----//
                                mtrAxeCmd_s.triggerTimer_f32 = 0.0f; // send all ASAP
                            }
                            else 
                            {
                                //---- still sand ASAP for X -----//
                                if(idxAxe_e == GTRY_PHYS_AXE_X)
                                {
                                    mtrAxeCmd_s.triggerTimer_f32 = 0.0f; // send all ASAP
                                }
                                else 
                                {
                                    //---- first iteration non null for other axes has to start now ---//
                                    if((distribFirstPulseForOtherAxes_b[idxAxe_e] == FALSE)
                                    && (mtrAxeCmd_s.pulses_s32 != (t_sint32)0))
                                    {
                                        distribFirstPulseForOtherAxes_b[idxAxe_e] = TRUE;
                                        mtrAxeCmd_s.triggerTimer_f32 = PulseDuration_af32[GTRY_PHYS_AXE_X];
                                    }
                                    else 
                                    {
                                        //---- ASAP now ----//
                                        mtrAxeCmd_s.triggerTimer_f32 = 0.0f;
                                    }
                                        
                                }
                            }
                        break;
                        case GTRY_ALGO_COMPUTE_TYPE_Y_PRIORITY:
                            mtrAxeCmd_s.pulses_s32 = (t_sint32)g_IterCmd_au16[idxAxe_e][idxIter_s32] * f_pulseSigns_as32[idxAxe_e];
                            mtrAxeCmd_s.frequency_f32 = (t_float32)f_pulseToMake_au32[idxAxe_e] / totalTime_f32;

                            pulseSafeHeight_f32 = g_param_s.cptPrio_SafeHeight_af32[GTRY_PHYS_AXE_X] * g_param_s.pulsePerMm_af32[GTRY_PHYS_AXE_X];
                            if((t_float32)PulseDone_au32[GTRY_PHYS_AXE_Y] < pulseSafeHeight_f32)
                            {
                                //--- if idxAxe = X send ASAP, if others there are no pulses so we don't case ----//
                                mtrAxeCmd_s.triggerTimer_f32 = 0.0f; // send all ASAP
                            }
                            else 
                            {
                                //---- still sand ASAP for Y -----//
                                if(idxAxe_e == GTRY_PHYS_AXE_Y)
                                {
                                    mtrAxeCmd_s.triggerTimer_f32 = 0.0f; // send all ASAP
                                }
                                else 
                                {
                                    //---- first iteration non null for other axes has to start now ---//
                                    if((distribFirstPulseForOtherAxes_b[idxAxe_e] == FALSE)
                                    && (mtrAxeCmd_s.pulses_s32 != (t_sint32)0))
                                    {
                                        distribFirstPulseForOtherAxes_b[idxAxe_e] = TRUE;
                                        mtrAxeCmd_s.triggerTimer_f32 = PulseDuration_af32[GTRY_PHYS_AXE_X];
                                    }
                                    else 
                                    {
                                        //---- ASAP now ----//
                                        mtrAxeCmd_s.triggerTimer_f32 = 0.0f;
                                    }
                                        
                                }
                            }
                        break;
                        case GTRY_ALGO_COMPUTE_TYPE_Z_PRIORITY:
                            mtrAxeCmd_s.pulses_s32 = (t_sint32)g_IterCmd_au16[idxAxe_e][idxIter_s32] * f_pulseSigns_as32[idxAxe_e];
                            mtrAxeCmd_s.frequency_f32 = (t_float32)f_pulseToMake_au32[idxAxe_e] / totalTime_f32;

                            pulseSafeHeight_f32 = g_param_s.cptPrio_SafeHeight_af32[GTRY_PHYS_AXE_Z] * g_param_s.pulsePerMm_af32[GTRY_PHYS_AXE_Z];
                            if((t_float32)PulseDone_au32[GTRY_PHYS_AXE_Z] < pulseSafeHeight_f32)
                            {
                                //--- if idxAxe = X send ASAP, if others there are no pulses so we don't case ----//
                                mtrAxeCmd_s.triggerTimer_f32 = 0.0f; // send all ASAP
                            }
                            else 
                            {
                                //---- still sand ASAP for X -----//
                                if(idxAxe_e == GTRY_PHYS_AXE_Z)
                                {
                                    mtrAxeCmd_s.triggerTimer_f32 = 0.0f; // send all ASAP
                                }
                                else 
                                {
                                    //---- first iteration non null for other axes has to start now ---//
                                    if((distribFirstPulseForOtherAxes_b[idxAxe_e] == FALSE)
                                    && (mtrAxeCmd_s.pulses_s32 != (t_sint32)0))
                                    {
                                        distribFirstPulseForOtherAxes_b[idxAxe_e] = TRUE;
                                        mtrAxeCmd_s.triggerTimer_f32 = PulseDuration_af32[GTRY_PHYS_AXE_Z];
                                    }
                                    else 
                                    {
                                        //---- ASAP now ----//
                                        mtrAxeCmd_s.triggerTimer_f32 = 0.0f;
                                    }
                                        
                                }
                            }
                        break;
                        //--- all iteration macimum and the last one for min freqc is deal in previously  ----//
                        case GTRY_ALGO_COMPUTE_TYPE_X_BURSTFIRST:
                            if(idxAxe_e == GTRY_PHYS_AXE_X)
                            {
                                mtrAxeCmd_s.pulses_s32 = (t_sint32)g_IterCmd_au16[idxAxe_e][idxIter_s32] * f_pulseSigns_as32[idxAxe_e];
                                //---- all pulses at max speed ----//
                                mtrAxeCmd_s.frequency_f32 = (t_float32)g_param_s.MaxFreq_af32[idxAxe_e];
                            }
                            else 
                            {
                                mtrAxeCmd_s.pulses_s32 = (t_sint32)g_IterCmd_au16[idxAxe_e][idxIter_s32] * f_pulseSigns_as32[idxAxe_e];
                                mtrAxeCmd_s.frequency_f32 = (t_float32)f_pulseToMake_au32[idxAxe_e] / totalTime_f32;
                            }
                        break;
                        case GTRY_ALGO_COMPUTE_TYPE_Y_BURSTFIRST:
                            if(idxAxe_e == GTRY_PHYS_AXE_Y)
                            {
                                mtrAxeCmd_s.pulses_s32 = (t_sint32)g_IterCmd_au16[idxAxe_e][idxIter_s32] * f_pulseSigns_as32[idxAxe_e];
                                mtrAxeCmd_s.frequency_f32 = (t_float32)g_param_s.MaxFreq_af32[idxAxe_e];
                            }
                            else 
                            {
                                mtrAxeCmd_s.pulses_s32 = (t_sint32)g_IterCmd_au16[idxAxe_e][idxIter_s32] * f_pulseSigns_as32[idxAxe_e];
                                mtrAxeCmd_s.frequency_f32 = (t_float32)f_pulseToMake_au32[idxAxe_e] / totalTime_f32;
                            }
                        break;
                        case GTRY_ALGO_COMPUTE_TYPE_Z_BURSTFIRST:
                            if(idxAxe_e == GTRY_PHYS_AXE_Z)
                            {
                                mtrAxeCmd_s.pulses_s32 = (t_sint32)g_IterCmd_au16[idxAxe_e][idxIter_s32] * f_pulseSigns_as32[idxAxe_e];
                                mtrAxeCmd_s.frequency_f32 = (t_float32)g_param_s.MaxFreq_af32[idxAxe_e];
                            }
                            else 
                            {
                                mtrAxeCmd_s.pulses_s32 = (t_sint32)g_IterCmd_au16[idxAxe_e][idxIter_s32] * f_pulseSigns_as32[idxAxe_e];
                                mtrAxeCmd_s.frequency_f32 = (t_float32)f_pulseToMake_au32[idxAxe_e] / totalTime_f32;
                            }
                        case GTRY_ALGO_COMPUTE_TYPE_NB:
                        default:
                            Ret_e = RC_ERROR_WRONG_STATE;
                        break;                            
                    }                    
                }            
                else 
                {
                    mtrAxeCmd_s.pulses_s32 = (t_sint32)g_IterCmd_au16[idxAxe_e][idxIter_s32] * f_pulseSigns_as32[idxAxe_e];
                    mtrAxeCmd_s.frequency_f32 = g_param_s.MinFreq_af32[idxAxe_e];                
                }
            }

            if(mtrAxeCmd_s.frequency_f32 > g_param_s.MaxFreq_af32[idxAxe_e])
            {
                mtrAxeCmd_s.frequency_f32 = g_param_s.MaxFreq_af32[idxAxe_e];
            }
            else if(mtrAxeCmd_s.frequency_f32 < g_param_s.MinFreq_af32[idxAxe_e])
            {
                mtrAxeCmd_s.frequency_f32 = g_param_s.MinFreq_af32[idxAxe_e];
            }

            Ret_e = LIBQUEUE_WriteElement(&f_QueueAxeMngmt_as[idxAxe_e], &mtrAxeCmd_s, sizeof(t_sGTRY_MtrCmdIterPayload));
            PulseDuration_af32[idxAxe_e] += (t_float32)mtrAxeCmd_s.pulses_s32 / mtrAxeCmd_s.frequency_f32 * 1000.0f; // ms
            //g_IterCmd_au16[idxAxe_e][idxIter_s32] = (t_uint16)0;
        }
    }
    for(t_eGTRY_PhysicalAxe idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
    {
        if(PulseDone_au32[idxAxe_e] != f_pulseToMake_au32[idxAxe_e])
        {
            ASSERT((t_uint16)idxAxe_e);
        }
    }
    return Ret_e;
}

/*********************************
 * s_GTRY_SPEC_DistribLastPulse
 *********************************/
static void s_GTRY_SPEC_DistribLastPulse( t_eGTRY_PhysicalAxe f_axe_e,
                                        t_sint32 f_factor_s32,
                                        t_uint32 f_nbPulses_u32,
                                        t_uint16 f_nbIter_u16,
                                        t_uint16 f_startIterIdx_u16)
{
    t_float32 meanDistribPulse_f32 = (f_nbIter_u16 - f_startIterIdx_u16) > 0 ? 
                                                                        (t_float32)f_nbPulses_u32 / (t_float32)(f_nbIter_u16 - (t_uint16)f_startIterIdx_u16)  
                                                                        : f_nbPulses_u32;
    t_uint32 leftDistribPulse_u32 = (f_nbIter_u16 - f_startIterIdx_u16) > 0 ? 
                                                                        f_nbPulses_u32 - (t_uint32)meanDistribPulse_f32 * (t_uint32)(f_nbIter_u16 - (t_uint16)f_startIterIdx_u16)
                                                                        : (t_uint32)0;
    t_sint16 incrementVal_s16;
    t_sint32 idxIterCmd_s32;

    for(t_sint32 loopIter_s32 = f_startIterIdx_u16; loopIter_s32 < (t_sint32)f_nbIter_u16; loopIter_s32++)
    {
        incrementVal_s16 = (t_sint16)(f_factor_s32 * meanDistribPulse_f32);
        idxIterCmd_s32 = loopIter_s32 % (t_sint32)f_nbIter_u16;
        if(incrementVal_s16 > 0)
        {
            g_IterCmd_au16[f_axe_e][idxIterCmd_s32] += (t_uint16)incrementVal_s16;
        }
        else 
        {
            incrementVal_s16 *= (t_sint16)(-1);
            g_IterCmd_au16[f_axe_e][idxIterCmd_s32] -= (t_uint16)incrementVal_s16;
        }
    }
    for(t_uint32 loopLeftPulse_u32 = 0; loopLeftPulse_u32 < leftDistribPulse_u32; loopLeftPulse_u32++)
    {
        idxIterCmd_s32 = loopLeftPulse_u32 % ((t_sint32)f_nbIter_u16 - f_startIterIdx_u16) + f_startIterIdx_u16;
        incrementVal_s16 = (t_sint16)f_factor_s32;
        if(incrementVal_s16 > (t_sint16)0)
        {
            
            g_IterCmd_au16[f_axe_e][idxIterCmd_s32] += incrementVal_s16;
        }
        else 
        {
            incrementVal_s16 =  -incrementVal_s16; 
            g_IterCmd_au16[f_axe_e][idxIterCmd_s32] -= incrementVal_s16;
        }
    }

    return;
}

/*********************************
 * s_GTRY_SPEC_GetDominantAxeInfo
 *********************************/
static void s_GTRY_SPEC_GetDominantAxeInfo( const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                            t_eGTRY_PhysicalAxe * f_domAxe_pe,
                                            t_uint32 * f_totalPulse_pu32)
{
    t_eGTRY_PhysicalAxe dominantAxe_e = GTRY_PHYS_AXE_NB;
    t_uint32 totalPulse_u32 = 0;

    for(t_eGTRY_PhysicalAxe idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
    {
        if(f_pulseToMake_au32[idxAxe_e] > totalPulse_u32)
        {
            dominantAxe_e = idxAxe_e;
            totalPulse_u32 = f_pulseToMake_au32[idxAxe_e];
        }
    }

    if(f_domAxe_pe != NULL)
    {
        *f_domAxe_pe = dominantAxe_e;
    }
    if(f_totalPulse_pu32 != NULL)
    {
        *f_totalPulse_pu32 = totalPulse_u32;
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
 *	@params[in] 
 *	@params[out]
 *	 
 *
 *
 */
