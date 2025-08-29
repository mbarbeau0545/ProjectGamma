/*********************************************************************
 * @file        GANTRY_ConfigSpecific.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef GANTRY_CONFIGSPECIFIC_H_INCLUDED
#define GANTRY_CONFIGSPECIFIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "APP_CFG/ConfigFiles/GANTRY_ConfigPublic.h"
    #include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
    #include "Library/QUEUE/Src/LIBQueue.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************
    ///@brief mapping between signals from appsig and cmd signal
    typedef enum 
    {
        GTRY_CMD_SIG_POS_X = 0,
        GTRY_CMD_SIG_POS_Y,
        GTRY_CMD_SIG_POS_Z,

        GTRY_CMD_SIG_POS_RAYON,
        GTRY_CMD_SIG_POS_THETHA,
        GTRY_CMD_SIG_POS_PHI,

        GTRY_CMD_SIG_STEP_X,
        GTRY_CMD_SIG_STEP_Y,
        GTRY_CMD_SIG_STEP_Z,
        GTRY_CMD_SIG_DIR_X,
        GTRY_CMD_SIG_DIR_Y,
        GTRY_CMD_SIG_DIR_Z,

        GTRY_CMD_SIG_NB
    } t_eGTRY_CmdSignals;

    ///@brief Algorithm Computation type 
    typedef enum 
    {
        GTRY_ALGO_COMPUTE_TYPE_BALANCED = 0,        //---- Algorithm Compuution 
                                                    //      will be repart the same amount of pulse for each axes ----//
        GTRY_ALGO_COMPUTE_TYPE_X_PRIORITY,          //---- Algorithm Computation will be based on X axe priority, which means X axes has to reach a certain position 
                                                    //          before allowed others to move ----//
        GTRY_ALGO_COMPUTE_TYPE_Y_PRIORITY,          //---- Algorithm Computation will be based on Y axe priority, which means Y axes has to reach a certain position 
                                                    //          before allowed others to move ----//
        GTRY_ALGO_COMPUTE_TYPE_Z_PRIORITY,          //---- Algorithm Computation will be based on Z axe priority, which means Z axes has to reach a certain position 
                                                    //          before allowed others to move ----//
        GTRY_ALGO_COMPUTE_TYPE_X_BURSTFIRST,        //---- Algorithm Computation will be based on X axe getting all the pulses in the first iteraions (or the firsts if > 0xFFFF)
                                                    //          before others axes get pulses -----//
        GTRY_ALGO_COMPUTE_TYPE_Y_BURSTFIRST,        //---- Algorithm Computation will be based on X axe getting all the pulses in the first iteraions (or the firsts if > 0xFFFF)
                                                    //          before others axes get pulses -----//
        GTRY_ALGO_COMPUTE_TYPE_Z_BURSTFIRST,        //---- Algorithm Computation will be based on X axe getting all the pulses in the first iteraions (or the firsts if > 0xFFFF)
                                                    //          before others axes get pulses -----//
        GTRY_ALGO_COMPUTE_TYPE_NB
    } t_eGTRY_AlgoComputeType;
	/* CAUTION : Automatic generated code section for Enum: Start */

	/* CAUTION : Automatic generated code section for Enum: End */
	//-----------------------------ENUM TYPES-----------------------------//
    /**< enum for module list */

	/* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
	//-----------------------------STRUCT TYPES---------------------------//
    ///@brief Strucutre for information needed for iteration algorithm
    typedef struct 
    {
        t_uint16 minPulses_u16;                         //---- Minimum of pulses per iteraitons ----//
        t_eGTRY_AlgoComputeType computeType_e;          //---- Computaion type algorithm ----//
        t_float32 MinFreq_af32[GTRY_PHYS_AXE_NB];       //---- Minimum Frequency for Axe X ----//
        t_float32 MaxFreq_af32[GTRY_PHYS_AXE_NB];       //---- Maximum Frequency for Axe X ----//
        t_float32 pulsePerMm_af32[GTRY_PHYS_AXE_NB];     //---- Pulse per Millimeter for Axe Z ----//
    } t_sGTRYSPEC_AlgoParameter;
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
	//-----------------------------TYPEDEF TYPES---------------------------//

    
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************

    //********************************************************************************
    //                      Public functions - Prototyupe
    //********************************************************************************
    /**
     * @brief This function handle the Safety state of State Machine
     * ----------------------------------------------------------------------------
     * @return RC_OK : The state finish, pass to new state from fsm
     * @return RC_WARNNING_PENDING : The State is on going 
     * @return ohters : @ref t_eReturnCode
     */
    t_eReturnCode GANTRY_SPEC_BuildCartesianCmd(t_float32 f_value_af32[GTRY_CMD_SIG_NB], 
                                                t_sLIBQUEUE_QueueCore * f_QueuePosCmd_ps);
    /**
     * @brief This function handle the Safety state of State Machine
     * ----------------------------------------------------------------------------
     * @return RC_OK : The state finish, pass to new state from fsm
     * @return RC_WARNNING_PENDING : The State is on going 
     * @return ohters : @ref t_eReturnCode
     */
    t_eReturnCode GANTRY_SPEC_BuildSphericCmd(  t_float32 f_value_af32[GTRY_CMD_SIG_NB], 
                                                t_sLIBQUEUE_QueueCore * f_QueuePosCmd_ps);
    /**
     * @brief This function handle the Safety state of State Machine
     * ----------------------------------------------------------------------------
     * @return RC_OK : The state finish, pass to new state from fsm
     * @return RC_WARNNING_PENDING : The State is on going 
     * @return ohters : @ref t_eReturnCode
     */
    t_eReturnCode GANTRY_SPEC_BuildStepCmd( t_float32 f_value_af32[GTRY_CMD_SIG_NB], 
                                            t_sLIBQUEUE_QueueCore * f_QueuePosCmd_ps);
    /**
     * @brief This function handle the Safety state of State Machine
     * ----------------------------------------------------------------------------
     * @return RC_OK : The state finish, pass to new state from fsm
     * @return RC_WARNNING_PENDING : The State is on going 
     * @return ohters : @ref t_eReturnCode
     */
    t_eReturnCode GANTRY_SPEC_AlgorithmInit(t_sGTRYSPEC_AlgoParameter f_Parameter_s);
    /**
     * @brief This function handle the Safety state of State Machine
     * ----------------------------------------------------------------------------
     * @return RC_OK : The state finish, pass to new state from fsm
     * @return RC_WARNNING_PENDING : The State is on going 
     * @return ohters : @ref t_eReturnCode
     */
    t_eReturnCode GANTRY_SPEC_AlgorithmCompute( t_float32 f_targetPos_af32[GTRY_PHYS_AXE_NB],
                                                t_float32 f_currPos_af32[GTRY_PHYS_AXE_NB],
                                                t_float32 f_droppPulses_s32[GTRY_PHYS_AXE_NB],
                                                t_float32 f_missPulses_af32[GTRY_PHYS_AXE_NB],
                                                t_sLIBQUEUE_QueueCore * f_QueueIterCmdX_ps,
                                                t_sLIBQUEUE_QueueCore * f_QueueIterCmdY_ps,
                                                t_sLIBQUEUE_QueueCore * f_QueueIterCmdZ_ps);
#endif // APPSDM_CONFIGSPECIFIC_H_INCLUDED           
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
