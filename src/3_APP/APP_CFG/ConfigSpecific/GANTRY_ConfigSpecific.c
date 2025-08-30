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
static t_sGTRYSPEC_AlgoParameter g_param_s;

///@brief Pulse remaining when pass to uint32 to float32 etc
static t_float32 g_axePulseRemain_af32[GTRY_PHYS_AXE_NB];

///@brief Pulse calculation buffer
static t_uint16 g_IterCmd_au16[GTRY_PHYS_AXE_NB][GTRY_MAX_ITERATION];
//****************************************************************************
//                      Local functions - Prototypes
//****************************************************************************
/**
 * @brief This function handle the Safety state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return void
 */
static void GTRY_SPEC_Algo_ComputeSteps(t_float32 f_targetPos_af32[GTRY_PHYS_AXE_NB],
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
 * @return void
 */
static void GTRY_SPEC_Algo_ComputeChunkCount(   t_eGTRY_PhysicalAxe f_domAxe_e, 
                                                t_uint32 f_domTotalStep_u32,
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
static void GTRY_SPEC_Algo_DistribInitialPulse( t_eGTRY_AlgoComputeType f_computeType_e, 
                                                t_uint32 f_PulsesToMake_au32[GTRY_PHYS_AXE_NB],
                                                 
                                                t_eGTRY_PhysicalAxe f_domAxe_e,
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
static void s_GTRY_SPEC_DistribInitPulse_Balanced(  const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                    t_eGTRY_PhysicalAxe f_domninantAxe_e,
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
static void GTRY_SPEC_DistribInitPulse_BurstFirst(  const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                    t_eGTRY_PhysicalAxe f_domninantAxe_e,
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
static void GTRY_SPEC_DistribInitPulse_Priority(const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                t_eGTRY_PhysicalAxe f_domninantAxe_e,
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
static void GTRY_SPEC_Algo_SplitSingleIter( const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
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
static void s_GTRY_SPEC_Algo_AdjustLastIter(const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
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
static t_eReturnCode s_GTRY_SPEC_Algo_BuidlIterations(  t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                        t_sint32 f_pulseSigns_as32[GTRY_PHYS_AXE_NB],
                                                        t_uint16 f_nbIterMax_u16,
                                                        t_eGTRY_PhysicalAxe f_domAxe_e,
                                                        t_uint16 f_DominantPulses_u16,
                                                        t_sLIBQUEUE_QueueCore f_QueueAxeMngmt_as[GTRY_PHYS_AXE_NB]);
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
static void GTRY_SPEC_DistribLastPulse( t_eGTRY_PhysicalAxe f_axe_e,
                                        t_sint32 f_factor_s32,
                                        t_uint32 f_nbPulses_u32,
                                        t_uint16 f_nbIter_u16);
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
    g_param_s.chunkSize_u16 = f_Parameter_s.chunkSize_u16;

    t_eGTRY_PhysicalAxe idxAxe_e;

    for(idxAxe_e = GTRY_PHYS_AXE_HEAD ; idxAxe_e < GTRY_PHYS_AXE_NB ; idxAxe_e++)
    {
        g_param_s.MaxFreq_af32[idxAxe_e] = f_Parameter_s.MaxFreq_af32[idxAxe_e];
        g_param_s.MinFreq_af32[idxAxe_e] = f_Parameter_s.MinFreq_af32[idxAxe_e];
        g_param_s.pulsePerMm_af32[idxAxe_e] = f_Parameter_s.pulsePerMm_af32[idxAxe_e];
        g_param_s.cptPrio_SafeHeight_af32[idxAxe_e] = f_Parameter_s.cptPrio_SafeHeight_af32[idxAxe_e];
        g_axePulseRemain_af32[idxAxe_e] = 0.0f;
    }

    return RC_OK;
}

/*********************************
 * GANTRY_SPEC_AlgorithmCompute
 *********************************/
t_eReturnCode GANTRY_SPEC_AlgorithmCompute( t_eGTRY_AlgoComputeType f_computeType_e,
                                            t_float32 f_targetPos_af32[GTRY_PHYS_AXE_NB],
                                            t_float32 f_currPos_af32[GTRY_PHYS_AXE_NB],
                                            t_float32 f_droppPulses_s32[GTRY_PHYS_AXE_NB],
                                            t_float32 f_missPulses_af32[GTRY_PHYS_AXE_NB],
                                            t_sLIBQUEUE_QueueCore * f_QueueIterCmd_ps[GTRY_PHYS_AXE_NB])
{
    t_eReturnCode Ret_e;
    t_uint32 pulseTomake_au32[GTRY_PHYS_AXE_NB] = {0,0,0};
    t_sint32 pulseSigns_as32[GTRY_PHYS_AXE_NB] = {1,1,1};
    t_float32 factorPulses_af32[GTRY_PHYS_AXE_NB] = {1.0f, 1.0f, 1.0f};
    t_eGTRY_PhysicalAxe dominantAxe_e = GTRY_PHYS_AXE_NB;
    t_uint32 totalPulseDominant_u32 = 0;
    t_uint16 nbIterMax_u16 = 0;
    t_uint8 QueueXLeft_u8, QueueYLeft_u8, QueueZLeft_u8;

    if((f_currPos_af32 == NULL) || (f_droppPulses_s32 == NULL) || 
       (f_targetPos_af32 == NULL) || (f_missPulses_af32 == NULL) || 
       (f_QueueIterCmd_ps == NULL))
    {
        ASSERT((t_uint16)0);
        return RC_ERROR_PTR_NULL;
    }

    Ret_e = RC_OK;

    //---- 1- Compute steps and dominant axis ----//
    GTRY_SPEC_Algo_ComputeSteps(f_targetPos_af32, 
                                f_currPos_af32,
                                f_missPulses_af32,
                                pulseTomake_au32,
                                pulseSigns_as32,
                                &dominantAxe_e,
                                &totalPulseDominant_u32);

    //---- 2- Compute number of iterations ----//
    GTRY_SPEC_Algo_ComputeChunkCount(dominantAxe_e, totalPulseDominant_u32, &nbIterMax_u16);

    //---- 3- Check queues ----//
    LIBQUEUE_GetSizeLeft(f_QueueIterCmd_ps[GTRY_PHYS_AXE_X], &QueueXLeft_u8);
    LIBQUEUE_GetSizeLeft(f_QueueIterCmd_ps[GTRY_PHYS_AXE_Y], &QueueYLeft_u8);
    LIBQUEUE_GetSizeLeft(f_QueueIterCmd_ps[GTRY_PHYS_AXE_Z], &QueueZLeft_u8);

    if((QueueXLeft_u8 < nbIterMax_u16) || (QueueYLeft_u8 < nbIterMax_u16) || (QueueZLeft_u8 < nbIterMax_u16))
        return RC_WARNING_LIMIT_REACHED;

    if(nbIterMax_u16 > GTRY_MAX_ITERATION)
        return RC_ERROR_LIMIT_REACHED;

    //---- 4- Distribute pulses ----//
    GTRY_SPEC_Algo_DistribInitialPulse(f_computeType_e, pulseTomake_au32, dominantAxe_e, nbIterMax_u16);

    //---- 5- Handle single iteration ----//
    if(nbIterMax_u16 == 1)
    {
        nbIterMax_u16 = 2;
        GTRY_SPEC_Algo_SplitSingleIter(pulseTomake_au32, nbIterMax_u16);
    }

    //---- 6- Adjust last iteration ----//
    s_GTRY_SPEC_Algo_AdjustLastIter(pulseTomake_au32, nbIterMax_u16);

    //---- 7- Build iterations ----//
    Ret_e = s_GTRY_SPEC_Algo_BuidlIterations(pulseTomake_au32,
                                             pulseSigns_as32,
                                             nbIterMax_u16,
                                             dominantAxe_e,
                                             (t_uint16)totalPulseDominant_u32,
                                             f_QueueIterCmd_ps);

    return Ret_e;
}

/*********************************
 * GTRY_SPEC_Algo_ComputeSteps
 *********************************/
static void GTRY_SPEC_Algo_ComputeSteps(t_float32 f_targetPos_af32[GTRY_PHYS_AXE_NB],
                                        t_float32 f_currPos_af32[GTRY_PHYS_AXE_NB],
                                        t_float32 f_missPulses_af32[GTRY_PHYS_AXE_NB],
                                        t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                        t_sint32 f_pulseSigns_as32[GTRY_PHYS_AXE_NB],
                                        t_eGTRY_PhysicalAxe * f_domAxis_pe,
                                        t_uint32 * f_domAxePulses_pu32)
{
    t_eGTRY_PhysicalAxe idxAxe_e;
    t_float32 exactStepToMake_f32;
    t_sint32 realStepToMake_s32;
    t_eGTRY_PhysicalAxe axeDominant_e = GTRY_PHYS_AXE_HEAD;
    t_uint32 axeDomPulses_u32 = 0;

    for(idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
    {
        exactStepToMake_f32 = (f_targetPos_af32[idxAxe_e] - f_currPos_af32[idxAxe_e]) *
                               g_param_s.pulsePerMm_af32[idxAxe_e] +
                               g_axePulseRemain_af32[idxAxe_e] +
                               f_missPulses_af32[idxAxe_e];

        realStepToMake_s32 = (t_sint32)exactStepToMake_f32;

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
            axeDominant_e = idxAxe_e;
        }

        g_axePulseRemain_af32[idxAxe_e] = exactStepToMake_f32 - (t_float32)realStepToMake_s32;
    }

    *f_domAxis_pe = axeDominant_e;
    *f_domAxePulses_pu32 = axeDomPulses_u32;

    return;
}

/*********************************
 * GTRY_SPEC_Algo_ComputeChunkCount
 *********************************/
static void GTRY_SPEC_Algo_ComputeChunkCount(t_eGTRY_PhysicalAxe f_domAxe_e,
                                             t_uint32 f_domTotalStep_u32,
                                             t_uint16 * f_NbIterMax_pu16)
{
    UNUSED(f_domAxe_e);
    t_uint32 chunkSize_u32 = (t_uint32)g_param_s.chunkSize_u16;
    *f_NbIterMax_pu16 = (t_uint16)((f_domTotalStep_u32 + chunkSize_u32 - 1) / chunkSize_u32);
}

/*********************************
 * GTRY_SPEC_Algo_DistribInitialPulse
 *********************************/
static void GTRY_SPEC_Algo_DistribInitialPulse(t_eGTRY_AlgoComputeType f_computeType_e,
                                               t_uint32 f_PulsesToMake_au32[GTRY_PHYS_AXE_NB],
                                               t_eGTRY_PhysicalAxe f_domAxe_e,
                                               t_uint16 f_NbIterMax_u16)
{
    switch(f_computeType_e)
    {
        case GTRY_ALGO_COMPUTE_TYPE_BALANCED:
            s_GTRY_SPEC_DistribInitPulse_Balanced(f_PulsesToMake_au32, f_domAxe_e, f_NbIterMax_u16);
            break;
        case GTRY_ALGO_COMPUTE_TYPE_X_BURSTFIRST:
            GTRY_SPEC_DistribInitPulse_BurstFirst(f_PulsesToMake_au32, f_domAxe_e, f_NbIterMax_u16, GTRY_PHYS_AXE_X);
            break;
        case GTRY_ALGO_COMPUTE_TYPE_Y_BURSTFIRST:
            GTRY_SPEC_DistribInitPulse_BurstFirst(f_PulsesToMake_au32, f_domAxe_e, f_NbIterMax_u16, GTRY_PHYS_AXE_Y);
            break;
        case GTRY_ALGO_COMPUTE_TYPE_Z_BURSTFIRST:
            GTRY_SPEC_DistribInitPulse_BurstFirst(f_PulsesToMake_au32, f_domAxe_e, f_NbIterMax_u16, GTRY_PHYS_AXE_Z);
            break;
        case GTRY_ALGO_COMPUTE_TYPE_X_PRIORITY:
            GTRY_SPEC_DistribInitPulse_Priority(f_PulsesToMake_au32, f_domAxe_e, f_NbIterMax_u16, GTRY_PHYS_AXE_X);
            break;
        case GTRY_ALGO_COMPUTE_TYPE_Y_PRIORITY:
            GTRY_SPEC_DistribInitPulse_Priority(f_PulsesToMake_au32, f_domAxe_e, f_NbIterMax_u16, GTRY_PHYS_AXE_Y);
            break;
        case GTRY_ALGO_COMPUTE_TYPE_Z_PRIORITY:
            GTRY_SPEC_DistribInitPulse_Priority(f_PulsesToMake_au32, f_domAxe_e, f_NbIterMax_u16, GTRY_PHYS_AXE_Z);
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
                                                  t_eGTRY_PhysicalAxe f_domninantAxe_e,
                                                  t_uint16 f_nbIterMax_u16)
{
    t_eGTRY_PhysicalAxe idxAxe_e;
    t_sint32 idxIter_s32;
    t_uint32 chunkSize_u32 = (t_uint32)g_param_s.chunkSize_u16;

    for(idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
    {
        t_uint32 sumPulseGive_u32 = 0;
        for(idxIter_s32 = 0; idxIter_s32 < (t_sint32)f_nbIterMax_u16; idxIter_s32++)
        {
            g_IterCmd_au16[idxAxe_e][idxIter_s32] = (t_uint16)(f_pulseToMake_au32[idxAxe_e] / f_nbIterMax_u16);
            sumPulseGive_u32 += g_IterCmd_au16[idxAxe_e][idxIter_s32];
        }

        t_sint32 correction_s32 = (t_sint32)f_pulseToMake_au32[idxAxe_e] - (t_sint32)sumPulseGive_u32;
        if(correction_s32 != 0)
        {
            t_sint32 factorCorrection_s32 = (correction_s32 > 0) ? 1 : -1;
            if(factorCorrection_s32 < 0) correction_s32 = -correction_s32;

            GTRY_SPEC_DistribLastPulse(idxAxe_e, factorCorrection_s32, (t_uint32)correction_s32, f_nbIterMax_u16);
        }
    }

    return;
}

/*********************************
 * GTRY_SPEC_DistribInitPulse_BurstFirst
 *********************************/
static void GTRY_SPEC_DistribInitPulse_BurstFirst(const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                  t_eGTRY_PhysicalAxe f_domninantAxe_e,
                                                  t_uint16 f_nbIterMax_u16,
                                                  t_eGTRY_PhysicalAxe f_AxeBurstFirst_e)
{
    t_eGTRY_PhysicalAxe idxAxe_e;
    t_uint32 PulseDone_au32[GTRY_PHYS_AXE_NB] = {0,0,0};

    for(idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
    {
        for(t_sint32 idxIter_s32 = 0; idxIter_s32 < (t_sint32)f_nbIterMax_u16; idxIter_s32++)
        {
            t_uint16 pulseCmpte_u16 = 0;
            if(idxAxe_e == f_AxeBurstFirst_e)
            {
                if(PulseDone_au32[f_AxeBurstFirst_e] < f_pulseToMake_au32[f_AxeBurstFirst_e])
                {
                    pulseCmpte_u16 = (f_pulseToMake_au32[f_AxeBurstFirst_e] - PulseDone_au32[f_AxeBurstFirst_e]);
                    if(pulseCmpte_u16 > 0xFFFF) 
                    {
                        pulseCmpte_u16 = 0xFFFF;
                    }
                    g_IterCmd_au16[f_AxeBurstFirst_e][idxIter_s32] = pulseCmpte_u16;
                    PulseDone_au32[f_AxeBurstFirst_e] += pulseCmpte_u16;
                }
                else g_IterCmd_au16[f_AxeBurstFirst_e][idxIter_s32] = 0;
            }
            else
            {
                pulseCmpte_u16 = (t_uint16)((f_pulseToMake_au32[idxAxe_e] * (t_uint32)g_param_s.chunkSize_u16) / f_nbIterMax_u16);
                g_IterCmd_au16[idxAxe_e][idxIter_s32] = pulseCmpte_u16;
                PulseDone_au32[idxAxe_e] += pulseCmpte_u16;
            }
        }
    }

    return;
}

/*********************************
 * GTRY_SPEC_DistribInitPulse_Priority
 *********************************/
static void GTRY_SPEC_DistribInitPulse_Priority(const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                t_eGTRY_PhysicalAxe f_domninantAxe_e,
                                                t_uint16 f_nbIterMax_u16,
                                                t_eGTRY_PhysicalAxe f_AxePriority_e)
{
    t_eGTRY_PhysicalAxe idxAxe_e;
    t_uint32 PulseDone_au32[GTRY_PHYS_AXE_NB] = {0,0,0};
    t_uint32 heightTarget_u32 = g_param_s.cptPrio_SafeHeight_af32[f_AxePriority_e];
    t_uint32 stepToReachTarget_u32 = (t_uint32)((t_float32)heightTarget_u32 / g_param_s.pulsePerMm_af32[f_AxePriority_e]);

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
                pulseAxeCmpte_u16 = g_param_s.chunkSize_u16;
            }

            PulseDone_au32[f_AxePriority_e] += pulseAxeCmpte_u16;

            for(idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
            {
                g_IterCmd_au16[idxAxe_e][idxIter_s32] = (idxAxe_e == f_AxePriority_e) ? pulseAxeCmpte_u16 : 0;
            }
        }
        else
        {
            for(idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
            {
                t_uint32 remainPulse_u32 = f_pulseToMake_au32[idxAxe_e] - PulseDone_au32[idxAxe_e];
                pulseAxeCmpte_u16 = (remainPulse_u32 > g_param_s.chunkSize_u16) ? g_param_s.chunkSize_u16 : (t_uint16)remainPulse_u32;
                g_IterCmd_au16[idxAxe_e][idxIter_s32] = pulseAxeCmpte_u16;
                PulseDone_au32[idxAxe_e] += pulseAxeCmpte_u16;
            }
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
            GTRY_SPEC_DistribLastPulse(idxAxe_e, factorCorrect_s32, (t_uint32)correction_s32, f_nbIterMax_u16);
        }
    }

    return;
}

/*********************************
 * GTRY_SPEC_Algo_SplitSingleIter
 *********************************/
static void GTRY_SPEC_Algo_SplitSingleIter(const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                           t_uint16 f_nbIterMax_u16)
{
    if(f_nbIterMax_u16 != 2) ASSERT((t_uint16)f_nbIterMax_u16);

    for(t_eGTRY_PhysicalAxe idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
    {
        t_float32 meanPulses_f32 = (t_float32)g_IterCmd_au16[idxAxe_e][0] / 2.0f;
        t_sint32 leftPulses_s32 = g_IterCmd_au16[idxAxe_e][0] - (t_uint16)meanPulses_f32;
        g_IterCmd_au16[idxAxe_e][0] = (t_uint16)meanPulses_f32 + leftPulses_s32;
        g_IterCmd_au16[idxAxe_e][1] = (t_uint16)meanPulses_f32;
    }

    return;
}

/*********************************
 * s_GTRY_SPEC_Algo_AdjustLastIter
 *********************************/
static void s_GTRY_SPEC_Algo_AdjustLastIter(const t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                            t_uint16 f_nbIterMax_u16)
{
    t_sint32 smallerPulse_s32 = 0x7FFFFFFF;
    t_eGTRY_PhysicalAxe axeSmallerPulse_e = GTRY_PHYS_AXE_HEAD;

    // Find smallest pulse on last iteration
    for(t_eGTRY_PhysicalAxe idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
    {
        t_sint32 pulseLastIter_s32 = g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1];
        if(pulseLastIter_s32 < smallerPulse_s32)
        {
            smallerPulse_s32 = pulseLastIter_s32;
            axeSmallerPulse_e = idxAxe_e;
        }
    }

    // Distribute remaining
    for(t_eGTRY_PhysicalAxe idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
    {
        if(idxAxe_e != axeSmallerPulse_e)
        {
            t_uint32 diffPulses_u32 = g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] - smallerPulse_s32;
            g_IterCmd_au16[idxAxe_e][f_nbIterMax_u16 - 1] = smallerPulse_s32;
            GTRY_SPEC_DistribLastPulse(idxAxe_e, 1, diffPulses_u32, f_nbIterMax_u16);
        }
    }

    return;
}

/*********************************
 * s_GTRY_SPEC_Algo_BuidlIterations
 *********************************/
static t_eReturnCode s_GTRY_SPEC_Algo_BuidlIterations(t_uint32 f_pulseToMake_au32[GTRY_PHYS_AXE_NB],
                                                      t_sint32 f_pulseSigns_as32[GTRY_PHYS_AXE_NB],
                                                      t_uint16 f_nbIterMax_u16,
                                                      t_eGTRY_PhysicalAxe f_domAxe_e,
                                                      t_uint16 f_DominantPulses_u16,
                                                      t_sLIBQUEUE_QueueCore *f_QueueAxeMngmt_as[GTRY_PHYS_AXE_NB])
{
    t_eReturnCode Ret_e = RC_OK;
    t_sGTRY_MtrCmdIterPayload mtrAxeCmd_s;
    t_float32 totalTime_f32 = (g_param_s.MaxFreq_af32[f_domAxe_e] > 0.0f) ? 
                               ((t_float32)f_DominantPulses_u16 / g_param_s.MaxFreq_af32[f_domAxe_e]) : 0.0f;

    for(t_sint32 idxIter_s32 = 0; idxIter_s32 < (t_sint32)f_nbIterMax_u16 && Ret_e == RC_OK; idxIter_s32++)
    {
        for(t_eGTRY_PhysicalAxe idxAxe_e = GTRY_PHYS_AXE_HEAD; idxAxe_e < GTRY_PHYS_AXE_NB; idxAxe_e++)
        {
            t_float32 frequencyCmd_f32 = (idxIter_s32 < (t_sint32)(f_nbIterMax_u16 - 1) && totalTime_f32 > 0.0f) ?
                                         f_pulseToMake_au32[idxAxe_e] / totalTime_f32 : g_param_s.MinFreq_af32[idxAxe_e];

            if(frequencyCmd_f32 > g_param_s.MaxFreq_af32[idxAxe_e])
            {
                frequencyCmd_f32 = g_param_s.MaxFreq_af32[idxAxe_e];
            }
            else if(frequencyCmd_f32 < g_param_s.MinFreq_af32[idxAxe_e])
            {   
                frequencyCmd_f32 = g_param_s.MinFreq_af32[idxAxe_e];
            }

            mtrAxeCmd_s.pulses_s32 = g_IterCmd_au16[idxAxe_e][idxIter_s32] * f_pulseSigns_as32[idxAxe_e];
            mtrAxeCmd_s.frequency_f32 = frequencyCmd_f32;

            Ret_e = LIBQUEUE_WriteElement(f_QueueAxeMngmt_as[idxAxe_e], &mtrAxeCmd_s, sizeof(t_sGTRY_MtrCmdIterPayload));
        }
    }
    return Ret_e;
}

/*********************************
 * GTRY_SPEC_DistribLastPulse
 *********************************/
static void GTRY_SPEC_DistribLastPulse(t_eGTRY_PhysicalAxe f_axe_e,
                                       t_sint32 f_factor_s32,
                                       t_uint32 f_nbPulses_u32,
                                       t_uint16 f_nbIter_u16)
{
    t_uint32 meanDistribPulse_u32 = f_nbPulses_u32 / f_nbIter_u16;
    t_uint32 leftDistribPulse_u32 = f_nbPulses_u32 - meanDistribPulse_u32 * f_nbIter_u16;
    t_sint16 incrementVal_s16;

    for(t_sint32 loopIter_s32 = 0; loopIter_s32 < f_nbIter_u16; loopIter_s32++)
    {
        incrementVal_s16 = (t_sint16)(f_factor_s32 * meanDistribPulse_u32);
        if(incrementVal_s16 > 0)
        {
            g_IterCmd_au16[f_axe_e][loopIter_s32] += (t_uint16)incrementVal_s16;
        }
        else 
        {
            incrementVal_s16 *= -1;
            g_IterCmd_au16[f_axe_e][loopIter_s32] -= (t_uint16)incrementVal_s16;
        }
    }
    for(t_sint32 loopLeftPulse_s32 = 0; loopLeftPulse_s32 < leftDistribPulse_u32; loopLeftPulse_s32++)
    {
        incrementVal_s16 = (t_sint16)f_factor_s32;
        if(f_factor_s32 > 0)
        {
            g_IterCmd_au16[f_axe_e][loopLeftPulse_s32] += (t_uint16)incrementVal_s16;
        }
        else 
        {
            incrementVal_s16 *= -1;
            g_IterCmd_au16[f_axe_e][loopLeftPulse_s32] -= (t_uint16)incrementVal_s16;
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
 *	@params[in] 
 *	@params[out]
 *	 
 *
 *
 */
