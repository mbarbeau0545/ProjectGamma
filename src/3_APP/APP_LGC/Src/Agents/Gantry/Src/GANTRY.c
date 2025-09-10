/*********************************************************************
 * @file        GANTRY.c
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
#include "./GANTRY.h"

#include "APP_CFG/ConfigFiles/GANTRY_ConfigPrivate.h"
#include "Library/QUEUE/Src/LIBQueue.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
#define GTRTY_SIZEOF_ELEM_POSCMD_QUEUE          (t_uint16)(sizeof(t_float32) * GTRY_PHYS_AXE_NB)
#define GTRTY_SIZEOF_ELEM_ITERCMD_QUEUE          (t_uint16)(sizeof(t_sGTRY_MtrCmdIterPayload))
// ********************************************************************
// *                      Types
// ********************************************************************
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------ENUM TYPES-----------------------------//
///@brief Finite State Machine for Periodic Task
typedef enum 
{
    GTRY_FSM_PRD_TSK_CFG = 0,           //---- Fsm for configuration ----//
    GTRY_FSM_PRD_TSK_CALIB_AXE,         //---- Fsm for calibration ----//
    GTRY_FSM_PRD_TSK_OPS,               //---- Fsm for operational ----//
    GTRY_FSM_PRD_TSK_SAFETY,            //---- Fsm for safety ----//
    GTRY_FSM_PRD_TSK_ERROR,             //---- Fsm for error ----//
} t_eGTRY_FsmPeriodicTask;

///@brief Finite State Machine for Periodic Task Sub State Calibration
typedef enum 
{
    GTRY_FSM_PRDTSK_CALIB_INIT = 0,     //--- Fsm for Calibration initialization -----//
    GTRY_FSM_PRDTSK_CALIB_AXE_X,        //--- Fsm for Calibration axe X -----//
    GTRY_FSM_PRDTSK_CALIB_AXE_Y,        //--- Fsm for Calibration axe Y -----//
    GTRY_FSM_PRDTSK_CALIB_AXE_Z,        //--- Fsm for Calibration axe Z -----//
    GTRY_FSM_PRDTSK_CALIB_AXE_ALL,      //--- Fsm for Calibration all axes in sync -----//
} t_eGTRY_FsmPrdTsk_Calib;

///@brief Finite State Machine for Periodic Task Sub State Calibration Ope
typedef enum 
{
    GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE = 0,     //----Fsm for calibration, sub state axe xxx -> stop axe ----//
    GTRY_FSM_PRDTSK_CALIB_OPE_MOVE_AXE,         //----Fsm for calibration, sub state axe xxx -> move axe ----//
    GTRY_FSM_PRDTSK_CALIB_OPE_WAIT_AXE,         //----Fsm for calibration, sub state axe xxx -> wait axe ----//
    GTRY_FSM_PRDTSK_CALIB_OPE_OFFSET_AXE,       //----Fsm for calibration, sub state axe xxx -> wait axe ----//
} t_eGTRY_FsmPrdTsk_CalibOpe;

///@brief Finite State Machine for Periodic Task Sub State Operational
typedef enum 
{
    GTRY_FSM_PRDTSK_OPE_IDLE =  0,      //---- Fsm for Operational state, subState Idle ----//
    GTRY_FSM_PRDTSK_OPE_CMD_CHECK,      //---- Fsm for Operational state, subState check command ----//
    GTRY_FSM_PRDTSK_OPE_CMD_PROCESS,    //---- Fsm for Operational state, subState process command ----//
} t_eGTRY_FsmPrdTsk_Ope;

///@brief Finite State Machine for Periodic Task Sub State Operatinal Process
typedef enum 
{
    GTRY_FSM_PRDTSK_OPE_CMDPRCSS_CMPTE_ITER = 0,        //---- Fsm for Operation state, subState process cmd, substaet compute iteration -----//
    GTRY_FSM_PRDTSK_OPE_CMDPRCSS_SEND_ITERS,            //---- Fsm for Operation state, subState process cmd, substaet send iterations -----//
} t_eGTRY_FsmPrdTsk_OpeCmdPrcss;

/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
///@brief calib waiting information 
typedef struct 
{
    t_uint32 startWait_u32;         //---- store the Tick where we start to wait the axes to go to the setpoint ----//
    t_uint32 maxTimeWait_u32;       //---- Store the amount of time this is suspicious that the axe has not reach the set point yet ----//
} t_sGTRY_CalibWaitInfo;
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************
///@brief the current position of the gantry
static t_float32 g_axeCurrPos_af32[GTRY_PHYS_AXE_NB];
/// @brief The Gantry Position that we calculated with pulse 
static t_float32 g_AxeComputePos_af32[GTRY_PHYS_AXE_NB];
/// @brief What encoder says the position is
static t_float32 g_AxesFeedbackPos_af32[GTRY_PHYS_AXE_NB];
/// @brief Position We suppose to ended up after a new iteration computations 
static t_float32 g_AxesPositionExpected_af32[GTRY_PHYS_AXE_NB];
/// @brief the difference between what encoder says and currPos
static t_float32 g_DeltaPos_af32[GTRY_PHYS_AXE_NB];
/// @brief Pulses which are missed by the motor axes
static t_float32 g_axeMissPulses_af32[GTRY_PHYS_AXE_NB];

///@brief Signal reception Managment 
t_sGTRY_cmdSigInfo g_CmdSigInfo_as[GTRY_CMD_SIG_NB];

///@brief Finite State Machine Variables
static t_eGTRY_FsmPeriodicTask g_Fsm_PrdcTskSts_e;
static t_eGTRY_FsmPrdTsk_Calib g_Fsm_PrdTsk_CalibSts_e;
static t_eGTRY_FsmPrdTsk_CalibOpe g_Fsm_PrdTsk_CalibOpeSts_ae[GTRY_PHYS_AXE_NB];
static  t_eGTRY_FsmPrdTsk_Ope g_Fsm_PrdTsk_OpeSts_e;
static t_eGTRY_FsmPrdTsk_OpeCmdPrcss g_Fsm_PrdTsk_OpeCmdPrcssSts_e;

///@brief Command Queue Variables
static t_sLIBQUEUE_QueueCore g_QueueCmdPosRcvMngmt_s;
static t_sLIBQUEUE_QueueCore g_QueueCmdIterMngmt_as[GTRY_PHYS_AXE_NB];
static t_float32 g_BufferCmdPosRcv_af32[GTRY_CMD_POS_RCV_BUFFER_LEN];
static t_sGTRY_MtrCmdIterPayload g_BufferCmdMtrIter_as[GTRY_PHYS_AXE_NB][GTRY_CMD_ITER_BUFFER_LEN];

///@brief At least one Rcv Command is on the Queue
static t_bool g_FlagRcvPosCmd_b = FALSE;
///@brief At least one Iter Command is on the Queue
static t_bool g_FlagIterCmdReady_b = FALSE;
///@brief One Position cmd cannot be pushed inside PosQueue
static t_bool g_FlagPosCmdPending_b = FALSE;
static t_eGTRY_CmdTypeId g_cmdTypePending_e = GTRY_CMD_TYPE_ID_NB;

///@brief Time Max to wait for the axe to go to the calibration point 
static t_sGTRY_CalibWaitInfo g_CalibWaitTimeMax_ua32[GTRY_PHYS_AXE_NB];

///@brief store the parameter in case we want to change it in runtime 
static t_sGTRYSPEC_AlgoParameter g_algoParam_s;
static t_eGTRY_AlgoComputeType g_AlgoCpteType_e;
///@brief Algo Computation Time 
static t_uint32 g_algoComputeTime_u32 = 0u;

/// @brief To know where we start to send a iteration plan, for absolute timing planner 
static t_uint32 g_startSendIter_u32 = 0u;
/* CAUTION : Automatic generated code section for Variable: Start */
/* CAUTION : Automatic generated code section for Variable: End */
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
 * @brief State Machine of the Agent.
 * @brief This function check if motors are in a logic state
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_StateMachine(void);
/**
 * @brief Function called every cyclic to check motor.
 * @details This function check if motors are in a logic state
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_SafetyUpdate(void);
/**
 * @brief Update the current position of each axes
 * @details This function checck if encoder option are one,
 *          if there is for each axes, this function read the ecdr position
 *          compare it to the position compute 
 * 
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_UpdatePosition(void);
/**
 * @brief This function handle the configuration state of State Machine
 * @details Not much happen for now in this function
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTsk_Configuration(void);
/**
 * @brief This function handle the calibration state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTsk_Calibration(void);
/**
 * @brief This function handle the calibration Operationnal state 
 *          of State Machine
 * ----------------------------------------------------------------------------
 * @param[in] f_calibId_e : calibration axe Id
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_Ops(t_eGTRY_CalibAxeId f_calibId_e);
/**
 * @brief This function handle the calibration Operationnal Movement 
 *          state of State Machine
 * ----------------------------------------------------------------------------
 * @param[in] f_calibId_e : calibration axe Id
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_OpsMove(t_eGTRY_PhysicalAxe f_PhysAxe_e);
/**
 * @brief This function handle the calibration Operationnal Movement 
 *          state of State Machine
 * ----------------------------------------------------------------------------
 * @param[in] f_calibId_e : calibration axe Id
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_OpsStop(t_eGTRY_PhysicalAxe f_PhysAxe_e);
/**
 * @brief This function handle the calibration Operationnal Movement 
 *          state of State Machine
 * ----------------------------------------------------------------------------
 * @param[in] f_calibId_e : calibration axe Id
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_OpsWait(t_eGTRY_PhysicalAxe f_PhysAxe_e);

/**
 * @brief This function handle the calibration Operationnal Movement 
 *          state of State Machine
 * ----------------------------------------------------------------------------
 * @param[in] f_calibId_e : calibration axe Id
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_OpsOffset(t_eGTRY_PhysicalAxe f_PhysAxe_e);
/**
 * @brief This function handle the Operation state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTsk_Operational(void);
/**
 * @brief This function handle the Operation Idle
 *          of state  Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTskOpe_Idle(void);
/**
 * @brief This function handle the Operation Cmd Check
 *          of state  Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTskOpe_CmdCheck(void);
/**
 * @brief This function handle the Operation Cmd Process
 *          of state  Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTskOpe_CmdProcess(void);
/**
 * @brief This function handle the Operation Cmd Process subState Compute Iteration
 *          of state  Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTskOpeCmdPrcss_ComputeIter(void);
/**
 * @brief This function handle the Operation Cmd Process subState Send Iteration
 *          of state  Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTskOpeCmdPrcss_SendIter(void);
/**
 * @brief This function handle the Safety state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTsk_Safety(void);
/**
 * @brief This function handle the Error state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTsk_Error(void);
/**
 * @brief This function handle the Send of iterations to all motor
 * ----------------------------------------------------------------------------
 * @param[in] f_physAxeID_e : which motor send iteration
 * @param[in] f_MtrCmdIter_ps : pointor to the container that conains iterations to send
 * ----------------------------------------------------------------------------
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_SendMtrIteration(t_eGTRY_PhysicalAxe f_physAxeID_e, t_sGTRY_MtrCmdIterPayload * f_MtrCmdIter_ps);
/**
 * @brief This function handle the reception of signals from APPSIG
 * ----------------------------------------------------------------------------
 * @param[in] f_signal_e : signal ID
 * @param[in] f_sigVal_f32 :signl; value
 * ----------------------------------------------------------------------------
 * @return 
 */
static void s_GTRY_SigReceptionCallback(t_eAPPSIG_Signal f_signal_e, t_float32 f_sigVal_f32);
/**
 * @brief Check if all signal are beeing received to build a comladn
 * ----------------------------------------------------------------------------
 * @param[in] f_currentTime_u32 : Current Time
 * ----------------------------------------------------------------------------
 * @return 
 */
static void S_GTRY_CheckAndBuilCommand(t_eGTRY_CmdTypeId f_cmdTypeID_e, t_uint32 f_currentTime_u32);
/**
 * @brief Iteration Algorithm Core, Prepare And Call algorithm 
 * ----------------------------------------------------------------------------
 * @param[in] f_currentTime_u32 : Current Time
 * ----------------------------------------------------------------------------
 * @return 
 */
static t_eReturnCode s_GTRY_AlgoMngmt(  t_eGTRY_AlgoComputeType f_computeType_e,
                                        t_float32 f_posValues_af32[GTRY_PHYS_AXE_NB]);
/**
 * @brief Update the current position of each axes
 * @details This function checck if encoder option are one,
 *          if there is for each axes, this function read the ecdr position
 *          compare it to the position compute 
 *          It also get the missing pulse for each axe
 * 
 * ----------------------------------------------------------------------------
 * @param[in] f_idxAxe_e : axe to get informatio on
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_UpdateAxePosition(t_eGTRY_PhysicalAxe f_idxAxe_e);
/**
 * @brief Hard Stop for all Axes Motor
 * @details This function Set an hard stop, means pin enable se to 1
 *             to release torque on each axes, this function also check if action 
 *              has to be made before hard stop motor
 * 
 * ----------------------------------------------------------------------------
 * @param[in] f_idxAxe_e : axe to get informatio on
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_HardAxeStop(t_eGTRY_PhysicalAxe f_idxAxe_e);
/**
 * @brief Enable the motor axes
 * 
 * ----------------------------------------------------------------------------
 * @param[in] f_idxAxe_e : axe to get informatio on
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_EnableAxe(t_eGTRY_PhysicalAxe f_idxAxe_e);
/**
 * @brief Get/ Update the parameter used for gantry algorithm
 * 
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_UpdateAlgoParameters();

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * GTRY_Init
 *********************************/
t_eReturnCode GANTRY_Init(void)
{
    t_eReturnCode Ret_e;
    t_eGTRY_PhysicalAxe idxAxe_e;
    t_eGTRY_CmdSignals idxGtrySig_e;
    t_sLIBQUEUE_QueueCfg CmdPosFifoCfg_s;
    t_sLIBQUEUE_QueueCfg CmdIterFifoCfg_s;

    Ret_e = RC_OK;
    //---- init all relative stuff to axes ----//
    for(idxAxe_e = GTRY_PHYS_AXE_HEAD ; (idxAxe_e < GTRY_PHYS_AXE_NB) && (Ret_e == RC_OK) ; idxAxe_e++)
    {
        CmdIterFifoCfg_s.bufferHead_pv = &g_BufferCmdMtrIter_as[idxAxe_e];
        CmdIterFifoCfg_s.bufferSize_u8 = GTRY_CMD_ITER_BUFFER_LEN;
        CmdIterFifoCfg_s.elementSize_u8 = sizeof(t_sGTRY_MtrCmdIterPayload);
        CmdIterFifoCfg_s.enableOverwrite_b = FALSE;
        Ret_e = LIBQUEUE_Create(&g_QueueCmdIterMngmt_as[idxAxe_e], CmdIterFifoCfg_s);

        if(Ret_e == RC_OK)
        {
            g_AxeComputePos_af32[idxAxe_e] = 0.0f;
            g_axeCurrPos_af32[idxAxe_e] = 0.0f;
            g_AxesFeedbackPos_af32[idxAxe_e] = 0.0f;
            g_DeltaPos_af32[idxAxe_e] = 0.0f;
            g_AxesPositionExpected_af32[idxAxe_e] = 0.0f;
            g_axeMissPulses_af32[idxAxe_e] = 0.0f;
            g_CalibWaitTimeMax_ua32[idxAxe_e].maxTimeWait_u32 = 0;
            g_CalibWaitTimeMax_ua32[idxAxe_e].startWait_u32 = 0;
        }
    }
    //---- init gantry signals information ---//
    if(Ret_e == RC_OK)
    {
        for(idxGtrySig_e = GTRY_CMD_SIG_HEAD ; (idxGtrySig_e < GTRY_CMD_SIG_NB) && (Ret_e == RC_OK) ; idxGtrySig_e++)
        {
            g_CmdSigInfo_as[idxGtrySig_e].isRcv_b = FALSE;
            g_CmdSigInfo_as[idxGtrySig_e].value_f32 = 0.0f;
            g_CmdSigInfo_as[idxGtrySig_e].timeStamp_u32 = 0;

            Ret_e = APPSIG_AddRcvMsgCallback(c_GTRY_AppSIgSignalsList_ae[idxGtrySig_e], s_GTRY_SigReceptionCallback);
        }
    }
    if(Ret_e == RC_OK)
    {
        CmdPosFifoCfg_s.bufferHead_pv = &g_BufferCmdPosRcv_af32[0];
        CmdPosFifoCfg_s.bufferSize_u8 = GTRY_CMD_POS_RCV_BUFFER_LEN;
        CmdPosFifoCfg_s.elementSize_u8 = GTRTY_SIZEOF_ELEM_POSCMD_QUEUE;
        CmdPosFifoCfg_s.enableOverwrite_b = FALSE;
        Ret_e = LIBQUEUE_Create(&g_QueueCmdPosRcvMngmt_s, CmdPosFifoCfg_s);
    }

    g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_CFG;
    g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_INIT;
    g_Fsm_PrdTsk_OpeSts_e = GTRY_FSM_PRDTSK_OPE_IDLE;
    g_Fsm_PrdTsk_OpeCmdPrcssSts_e = GTRY_FSM_PRDTSK_OPE_CMDPRCSS_CMPTE_ITER;
    g_Fsm_PrdTsk_CalibOpeSts_ae[GTRY_PHYS_AXE_X] = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
    g_Fsm_PrdTsk_CalibOpeSts_ae[GTRY_PHYS_AXE_Y] = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
    g_Fsm_PrdTsk_CalibOpeSts_ae[GTRY_PHYS_AXE_Z] = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;

    return Ret_e;
}

/*********************************
 * GTRY_Init
 *********************************/
t_eReturnCode GANTRY_PeriodicTask(void)
{
    t_eReturnCode Ret_e;
    
    //---- 1- Call Safety Update ----//
    Ret_e = s_GTRY_SafetyUpdate();

    //---- 2- Update Current position ----//
    Ret_e = s_GTRY_UpdatePosition();

    //---- 2- Call State Machine ----//
    if(Ret_e == RC_OK)
    {
        Ret_e = s_GTRY_StateMachine();
    }
    return Ret_e;
}

/*********************************
 * GTRY_GetPosition
 *********************************/
t_eReturnCode  GTRY_GetPosition(t_float32 f_currPos_af32[GTRY_PHYS_AXE_NB])
{
    t_eReturnCode Ret_e;
    t_uint8 ecdrXRCfg_u8;
    t_uint8 ecdrXLCfg_u8;
    t_uint8 ecdrYCfg_u8;
    t_uint8 ecdrZCfg_u8;

    if(f_currPos_af32 == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
        ASSERT((t_uint16)0);
    }
    else if((g_Fsm_PrdcTskSts_e != GTRY_FSM_PRD_TSK_CALIB_AXE)
    ||      (g_Fsm_PrdcTskSts_e != GTRY_FSM_PRD_TSK_OPS))
    {
        Ret_e = RC_WARNING_BUSY;
    }
    else
    {
        Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SNS_ECDR_XL, &ecdrXLCfg_u8);
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SNS_ECDR_XR, &ecdrXRCfg_u8);   
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SNS_ECDR_Y, &ecdrYCfg_u8);   
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SNS_ECDR_Z, &ecdrZCfg_u8);   
        }
        if(Ret_e == RC_OK)
        {
            if((ecdrXLCfg_u8 > APPSYS_OPT_SNS_ECDR_XL_UNUSED)
            || (ecdrXRCfg_u8 > APPSYS_OPT_SNS_ECDR_XR_UNUSED))
            {
                f_currPos_af32[GTRY_PHYS_AXE_X] = g_axeCurrPos_af32[GTRY_PHYS_AXE_X];
            }
            else 
            {
                f_currPos_af32[GTRY_PHYS_AXE_X] = g_AxesPositionExpected_af32[GTRY_PHYS_AXE_X];
            }
            if(ecdrYCfg_u8 > APPSYS_OPT_SNS_ECDR_Y_UNUSED)
            {
                f_currPos_af32[GTRY_PHYS_AXE_Y] = g_axeCurrPos_af32[GTRY_PHYS_AXE_Y];
            }
            else 
            {
                f_currPos_af32[GTRY_PHYS_AXE_Y] = g_AxesPositionExpected_af32[GTRY_PHYS_AXE_Y];
            }
            if(ecdrZCfg_u8 > APPSYS_OPT_SNS_ECDR_Z_UNUSED)
            {
                f_currPos_af32[GTRY_PHYS_AXE_Z] = g_axeCurrPos_af32[GTRY_PHYS_AXE_Z];
            }
            else 
            {
                f_currPos_af32[GTRY_PHYS_AXE_Z] = g_AxesPositionExpected_af32[GTRY_PHYS_AXE_Z];
            }
        }

    }

    return Ret_e;
}
// ********************************************************************
// *                      Local Functions - Implementation
// ********************************************************************
/*********************************
 * s_GTRY_SafetyUpdate
 *********************************/
static t_eReturnCode s_GTRY_SafetyUpdate(void)
{
    return RC_OK;
}

/*********************************
 * s_GTRY_UpdatePosition
 *********************************/
static t_eReturnCode s_GTRY_UpdatePosition(void)
{
    t_eReturnCode Ret_e = RC_OK;
    
    for(t_eGTRY_PhysicalAxe idxAxe_e = GTRY_PHYS_AXE_HEAD ;
        (idxAxe_e < GTRY_PHYS_AXE_NB) && (Ret_e >= RC_OK) ; 
        idxAxe_e++)
    {
        Ret_e = s_GTRY_UpdateAxePosition(idxAxe_e);
    }

    return Ret_e;
}
/*********************************
 * s_GTRY_StateMachine
 *********************************/
static t_eReturnCode s_GTRY_StateMachine(void)
{
    t_eReturnCode Ret_e;

    switch(g_Fsm_PrdcTskSts_e)
    {
        case GTRY_FSM_PRD_TSK_CFG:
            Ret_e = s_GTRY_Fsm_PrdTsk_Configuration();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_OPS;
                g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_INIT;
            }
            else if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_ERROR;
            }
        break;
        case GTRY_FSM_PRD_TSK_CALIB_AXE:
            Ret_e = s_GTRY_Fsm_PrdTsk_Calibration();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_OPS;
                g_Fsm_PrdTsk_OpeSts_e = GTRY_FSM_PRDTSK_OPE_IDLE;
            }
            else if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_SAFETY;
            }
        break;
        case GTRY_FSM_PRD_TSK_OPS:
            Ret_e = s_GTRY_Fsm_PrdTsk_Operational();
             if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_SAFETY;
            }
        break;
        case GTRY_FSM_PRD_TSK_SAFETY:
            Ret_e = s_GTRY_Fsm_PrdTsk_Safety();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_CFG;
            }
            else if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_ERROR;
            }
        break;
        case GTRY_FSM_PRD_TSK_ERROR:
            Ret_e = s_GTRY_Fsm_PrdTsk_Error();
            //--- no way out ----//
        default:
            Ret_e = RC_ERROR_WRONG_STATE;
        break;
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_Fsm_PrdTsk_Configuration
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTsk_Configuration(void)
{
    t_eReturnCode Ret_e;
    
    //---- init the finit state machine ----//
    g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_CFG;
    g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_INIT;
    g_Fsm_PrdTsk_OpeSts_e = GTRY_FSM_PRDTSK_OPE_IDLE;
    g_Fsm_PrdTsk_OpeCmdPrcssSts_e = GTRY_FSM_PRDTSK_OPE_CMDPRCSS_CMPTE_ITER;
    g_Fsm_PrdTsk_CalibOpeSts_ae[GTRY_PHYS_AXE_X] = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
    g_Fsm_PrdTsk_CalibOpeSts_ae[GTRY_PHYS_AXE_Y] = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
    g_Fsm_PrdTsk_CalibOpeSts_ae[GTRY_PHYS_AXE_Z] = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;

    //----1- Enable axes Motor ----//
    Ret_e = s_GTRY_EnableAxe(GTRY_PHYS_AXE_X);
    Ret_e |= s_GTRY_EnableAxe(GTRY_PHYS_AXE_Y);
    Ret_e |= s_GTRY_EnableAxe(GTRY_PHYS_AXE_Z);

    
    //---- 2- Init the algo parameter ----//
    Ret_e = s_GTRY_UpdateAlgoParameters();
    //---- 3- send the algo parameter ----//
    if(Ret_e == RC_OK)
    {
        Ret_e = GANTRY_SPEC_AlgorithmSetParam(g_algoParam_s);
    }
    
    // t_float32 bufferCmdPos_af32[GTRY_PHYS_AXE_NB];
    // bufferCmdPos_af32[GTRY_PHYS_AXE_X] = 450.F;
    // bufferCmdPos_af32[GTRY_PHYS_AXE_Y] = 450.F;
    // bufferCmdPos_af32[GTRY_PHYS_AXE_Z] = 450.F;
    // g_FlagRcvPosCmd_b = TRUE;
    // Ret_e = LIBQUEUE_WriteElement(  &g_QueueCmdPosRcvMngmt_s,
    //                                 bufferCmdPos_af32,
    //                                 sizeof(t_float32) * GTRY_PHYS_AXE_NB);
    return Ret_e;
}

/*********************************
 * s_GTRY_Fsm_PrdTsk_Calibration
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTsk_Calibration(void)
{   
    t_eReturnCode Ret_e;

    switch(g_Fsm_PrdTsk_CalibSts_e)
    {
        case GTRY_FSM_PRDTSK_CALIB_INIT:
        {
            t_uAPPSPM_PrmValType calibType_u = {.prmVal_u16 = 0};
            //---- Get the parameter that define the type of calibration ----//
            Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_CALIB_TYPE, &calibType_u);
            //---- If not accessible take default one ----//
            if((Ret_e != RC_OK)
            || calibType_u.prmVal_u16 >= GTRY_CALIB_TYPE_NB)
            {
                ASSERT((t_uint16)calibType_u.prmVal_u16);
                calibType_u.prmVal_u16 = GTRY_CALIB_TYPE_ASYNC;
            }
            //---- Reset Fsm State ----//
            g_Fsm_PrdTsk_CalibOpeSts_ae[GTRY_PHYS_AXE_X] = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
            g_Fsm_PrdTsk_CalibOpeSts_ae[GTRY_PHYS_AXE_Y] = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
            g_Fsm_PrdTsk_CalibOpeSts_ae[GTRY_PHYS_AXE_Z] = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
            //--- redirect to the right state of state machine ----//
            if(calibType_u.prmVal_u16 == (t_uint16)GTRY_CALIB_TYPE_ASYNC)
            {
                g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_AXE_X;
            }
            else if(calibType_u.prmVal_u16 == GTRY_CALIB_TYPE_SYNC)
            {
                g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_AXE_ALL;
            }
            else 
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }
            if(Ret_e == RC_OK)
            {
                Ret_e = RC_WARNING_PENDING;
            }       
        }
        break;
        case GTRY_FSM_PRDTSK_CALIB_AXE_X:
        {
            Ret_e = s_GTRY_Fsm_PrdTskCalib_Ops(GTRY_CALIB_ID_AXE_X);
            if(Ret_e == RC_OK)
            {
                Ret_e = RC_WARNING_PENDING;
                g_AxeComputePos_af32[GTRY_PHYS_AXE_X] = 0.0f;
                g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_AXE_Y;
            }
            //---- problem occur in calibration, take too much time ----//
            else if(Ret_e == RC_WARNING_LIMIT_REACHED)
            {
                g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_SAFETY;
            }
        }
        break;
        case GTRY_FSM_PRDTSK_CALIB_AXE_Y:
        {
            Ret_e = s_GTRY_Fsm_PrdTskCalib_Ops(GTRY_CALIB_ID_AXE_Y);
            if(Ret_e == RC_OK)
            {
                Ret_e = RC_WARNING_PENDING;
                g_AxeComputePos_af32[GTRY_PHYS_AXE_Y] = 0.0f;
                g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_AXE_Z;
            }
            //---- problem occur in calibration, take too much time ----//
            else if(Ret_e == RC_WARNING_LIMIT_REACHED)
            {
                g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_SAFETY;
            }
        }
        break;
        case GTRY_FSM_PRDTSK_CALIB_AXE_Z:
        {
            Ret_e = s_GTRY_Fsm_PrdTskCalib_Ops(GTRY_CALIB_ID_AXE_Z);
            if(Ret_e == RC_OK)
            {
                //--- out of state calibration ----//
                g_AxeComputePos_af32[GTRY_PHYS_AXE_Z] = 0.0f;
                g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_INIT;
            }
            //---- problem occur in calibration, take too much time ----//
            else if(Ret_e == RC_WARNING_LIMIT_REACHED)
            {
                g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_SAFETY;
            }
            break;
        }
        case GTRY_FSM_PRDTSK_CALIB_AXE_ALL:
        {
            Ret_e = s_GTRY_Fsm_PrdTskCalib_Ops(GTRY_CALIB_ID_AXE_ALL);
            if(Ret_e == RC_OK)
            {
                g_AxeComputePos_af32[GTRY_PHYS_AXE_X] = 0.0f;
                g_AxeComputePos_af32[GTRY_PHYS_AXE_Y] = 0.0f;
                g_AxeComputePos_af32[GTRY_PHYS_AXE_Z] = 0.0f;
            }
            //---- problem occur in calibration, take too much time ----//
            else if(Ret_e == RC_WARNING_LIMIT_REACHED)
            {
                g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_SAFETY;
            }
        }
        break;
        default:
            Ret_e = RC_ERROR_WRONG_STATE;
        break;
    }

    return  Ret_e;
}

/*********************************
 * s_GTRY_Fsm_PrdTskCalib_Ops
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_Ops(t_eGTRY_CalibAxeId f_calibId_e)
{
    t_eReturnCode Ret_e;
    t_eGTRY_CalibAxeId currAxeId_e;
    t_eGTRY_CalibAxeId startAxeId_e;
    t_eGTRY_CalibAxeId endAxeId_e;

    if(f_calibId_e >= GTRY_CALIB_ID_AXE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)0);
    }
    else 
    {   
       
        //---- 1- determine the start axe and end axe ----//
        if(f_calibId_e == GTRY_CALIB_ID_AXE_ALL)
        {
            startAxeId_e = GTRY_CALIB_ID_AXE_X;
            endAxeId_e = (GTRY_CALIB_ID_AXE_Z + 1);
        }
        else 
        {
            startAxeId_e = f_calibId_e;
            endAxeId_e = (startAxeId_e + 1);
        }
        //---- 2- state machine calib Ope 
        //      we loop on one axe or all, if return Code OK, we pass
        //      to the other axe, if not OK, we get out and retry with this
        //      axe on next cyclic ----//
        Ret_e = RC_OK;
        for(currAxeId_e = startAxeId_e ; 
            (currAxeId_e < endAxeId_e) && (Ret_e == RC_OK) ; 
            currAxeId_e++)
        {
            switch(g_Fsm_PrdTsk_CalibOpeSts_ae[currAxeId_e])
            {
                case GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE:
                    Ret_e = s_GTRY_Fsm_PrdTskCalib_OpsStop(currAxeId_e);
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = RC_WARNING_PENDING;
                        g_Fsm_PrdTsk_CalibOpeSts_ae[currAxeId_e] = GTRY_FSM_PRDTSK_CALIB_OPE_MOVE_AXE;
                    }
                break;
                case GTRY_FSM_PRDTSK_CALIB_OPE_MOVE_AXE:
                    Ret_e = s_GTRY_Fsm_PrdTskCalib_OpsMove(currAxeId_e);
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = RC_WARNING_PENDING;
                        g_Fsm_PrdTsk_CalibOpeSts_ae[currAxeId_e] = GTRY_FSM_PRDTSK_CALIB_OPE_WAIT_AXE;
                    }
                break;
                case GTRY_FSM_PRDTSK_CALIB_OPE_WAIT_AXE:
                    Ret_e = s_GTRY_Fsm_PrdTskCalib_OpsWait(currAxeId_e);
                    if(Ret_e == RC_OK)
                    {
                        g_Fsm_PrdTsk_CalibOpeSts_ae[currAxeId_e] = GTRY_FSM_PRDTSK_CALIB_OPE_OFFSET_AXE;
                        Ret_e = RC_WARNING_PENDING;
                    }
                break;
                case GTRY_FSM_PRDTSK_CALIB_OPE_OFFSET_AXE:
                    Ret_e = s_GTRY_Fsm_PrdTskCalib_OpsOffset(currAxeId_e);
                    if(Ret_e == RC_OK)
                    {
                        g_Fsm_PrdTsk_CalibOpeSts_ae[currAxeId_e] = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
                    }
                break;
                default:
                    Ret_e = RC_ERROR_WRONG_STATE;
                break;
            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_Fsm_PrdTskCalib_OpsStop
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_OpsStop(t_eGTRY_PhysicalAxe f_PhysAxe_e)
{
    t_eReturnCode Ret_e;
    const t_sGTRY_AxeAppCfg * axeCfg_ps;

    if(f_PhysAxe_e >= GTRY_PHYS_AXE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)0);
    }
    else 
    {
        switch(f_PhysAxe_e)
        {
            case GTRY_PHYS_AXE_X:
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XL];
                Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, APPACT_SOFT_STOP);
                if(Ret_e == RC_OK)
                {
                    axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XR];
                    Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, APPACT_SOFT_STOP);
                }
            break;
            case GTRY_PHYS_AXE_Y:
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Y];
                Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, APPACT_SOFT_STOP);
            break;
            case GTRY_PHYS_AXE_Z:
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Z];
                Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, APPACT_SOFT_STOP);
            break;
            case GTRY_PHYS_AXE_NB:
            default:
                Ret_e = RC_ERROR_WRONG_STATE;
            break;
        }
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_Fsm_PrdTskCalib_OpsMove
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_OpsMove(t_eGTRY_PhysicalAxe f_PhysAxe_e)
{
    t_eReturnCode Ret_e;
    const t_sGTRY_AxeAppCfg * axeCfg_ps;
    t_uAPPSPM_PrmValType pulsePerMm_u = {.prmVal_f32 = 0.0f};
    t_uAPPSPM_PrmValType minMtrFreq_u = {.prmVal_u16 = 0};
    t_uAPPSPM_PrmValType axeLenghtMm_u = {.prmVal_f32 = 0.0f};
    t_sint32 pulseToSend_s32 = 0;
    t_sint32 pulseFactor_s32;
    t_eAPPSPM_ItemPrm pulseperMmID_e;
    t_eAPPSPM_ItemPrm minSpeedID_e;
    t_eAPPSPM_ItemPrm axeLenghtID_e;

    if(f_PhysAxe_e >= GTRY_PHYS_AXE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)0);
    }
    else 
    {
        Ret_e = RC_OK;
        //---- 1- reach the right accessors axe ----//
        switch(f_PhysAxe_e)
        {
            case GTRY_PHYS_AXE_X:
                pulseFactor_s32 = GTRY_CALIB_DIR_AXE_X;
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XL];
                pulseperMmID_e = APPSPM_PRM_LGC_GTRY_AXE_X_PULSE_PER_MM;
                minSpeedID_e = APPSPM_PRM_LGC_GTRY_X_SPEED_MIN;
                axeLenghtID_e = APPSPM_PRM_LGC_GTRY_AXE_X_LEN;
            break;
            case GTRY_PHYS_AXE_Y:
                pulseFactor_s32 = GTRY_CALIB_DIR_AXE_Y;
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Y];
                pulseperMmID_e = APPSPM_PRM_LGC_GTRY_AXE_Y_PULSE_PER_MM;
                minSpeedID_e = APPSPM_PRM_LGC_GTRY_Y_SPEED_MIN;
                axeLenghtID_e = APPSPM_PRM_LGC_GTRY_AXE_Y_LEN;
            break;
            case GTRY_PHYS_AXE_Z:
                pulseFactor_s32 = GTRY_CALIB_DIR_AXE_Z;
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Z];
                pulseperMmID_e = APPSPM_PRM_LGC_GTRY_AXE_Z_PULSE_PER_MM;
                minSpeedID_e = APPSPM_PRM_LGC_GTRY_Z_SPEED_MIN;
                axeLenghtID_e = APPSPM_PRM_LGC_GTRY_AXE_Z_LEN;
            break;
            case GTRY_PHYS_AXE_NB:
            default:
                Ret_e = RC_ERROR_WRONG_STATE;
            break;
        }
        //---- 2- Parameter ----//
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSPM_GetParam(pulseperMmID_e, &pulsePerMm_u);
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSPM_GetParam(axeLenghtID_e, &axeLenghtMm_u);
            }
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSPM_GetParam(minSpeedID_e, &minMtrFreq_u);
            }
        }
        //---- 3- Compute and send the motor pulse to get to the reference point ----//
        if(Ret_e == RC_OK)
        {
            pulseToSend_s32 = (t_sint32)(pulsePerMm_u.prmVal_f32 * axeLenghtMm_u.prmVal_f32);
            pulseToSend_s32 *= pulseFactor_s32;

            Ret_e = APPACT_SetActValue(axeCfg_ps->actIfMtrPulse_e, pulseToSend_s32);
            if(Ret_e == RC_OK)
            {
                Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, (t_float32)minMtrFreq_u.prmVal_u16);
            }
            if(Ret_e == RC_OK)
            {
                Ret_e = APPACT_SetActValue(axeCfg_ps->actIfTimTrig_e, 0.0f);
            }

            //---- for axe X get the XR also ----//
            if((f_PhysAxe_e == GTRY_PHYS_AXE_X)
            && (Ret_e == RC_OK))
            {
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XR];
                Ret_e = APPACT_SetActValue(axeCfg_ps->actIfMtrPulse_e, pulseToSend_s32);
                if(Ret_e == RC_OK)
                {
                    Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, (t_float32)minMtrFreq_u.prmVal_u16);
                }
                if(Ret_e == RC_OK)
                {
                    Ret_e = APPACT_SetActValue(axeCfg_ps->actIfTimTrig_e, 0.0f);
                }
            }
        }
        //---- 4- set the maxe time to wait ----//
        if(Ret_e == RC_OK)
        {
            if(pulseToSend_s32 < (t_sint32)0)
            {
                pulseToSend_s32 = -pulseFactor_s32;
            }
            g_CalibWaitTimeMax_ua32[f_PhysAxe_e].maxTimeWait_u32 = pulseToSend_s32 
                                                                    / (t_sint32)minMtrFreq_u.prmVal_u16 
                                                                    * (t_sint32)1000; // ms
            g_CalibWaitTimeMax_ua32[f_PhysAxe_e].maxTimeWait_u32 += 50; // add on additional time of 50 ms
            FMKCPU_GetTick(&g_CalibWaitTimeMax_ua32[f_PhysAxe_e].startWait_u32);
        }
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_Fsm_PrdTskCalib_OpsWait
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_OpsWait(t_eGTRY_PhysicalAxe f_PhysAxe_e)
{
    t_eReturnCode Ret_e;
    const t_sGTRY_AxeAppCfg * axeCfg_ps;
    t_float32 actMtrStsVal_f32 = 0.0f;
    t_float32 actMtrXRStsVal_f32 = 0.0f;
    t_uint32 currentTime_u32;

    if(f_PhysAxe_e >= GTRY_PHYS_AXE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)0);
    }
    else 
    {
        FMKCPU_GetTick(&currentTime_u32);
        Ret_e = RC_OK;
        //---- 1- reach the right accessors axe ----//
        switch(f_PhysAxe_e)
        {
            case GTRY_PHYS_AXE_X:
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XL];
            break;
            case GTRY_PHYS_AXE_Y:
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Y];
            break;
            case GTRY_PHYS_AXE_Z:
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Z];
            break;
            case GTRY_PHYS_AXE_NB:
            default:
                Ret_e = RC_ERROR_WRONG_STATE;
            break;
        }
        //---- 2- Get Motor State ----//
        if(Ret_e == RC_OK)
        {
            Ret_e = APPACT_GetActValue(axeCfg_ps->actIfSpeed_e, &actMtrStsVal_f32);
            if(Ret_e == RC_OK)
            {
                if(f_PhysAxe_e == GTRY_PHYS_AXE_X)
                {
                    axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XR];
                    Ret_e = APPACT_GetActValue(axeCfg_ps->actIfSpeed_e, &actMtrXRStsVal_f32);
                    if(Ret_e == RC_OK)
                    {
                        //---- equality works here 'cause define are affect 
                        // to the variable and not compute ----//s
                        if(((actMtrStsVal_f32 != APPACT_MOTOR_STS_ENDSTOP_CW)
                        && (actMtrStsVal_f32 != APPACT_MOTOR_STS_ENDSTOP_CCW))
                        || ((actMtrXRStsVal_f32 != APPACT_MOTOR_STS_ENDSTOP_CW)
                        && (actMtrXRStsVal_f32 != APPACT_MOTOR_STS_ENDSTOP_CCW)))
                        {
                            Ret_e = RC_WARNING_PENDING;
                        }
                        // else Ret_e alredy RC_OK
                    }
                }
                else 
                {
                    if(actMtrStsVal_f32 != APPACT_MOTOR_STS_ENDSTOP_CW
                    ||(actMtrStsVal_f32 != APPACT_MOTOR_STS_ENDSTOP_CCW))
                    {
                        Ret_e = RC_WARNING_PENDING;
                    }
                    // else Ret_e alredy RC_OK
                }
                if(Ret_e == RC_WARNING_PENDING) // means we waiting the motor to get to the calibration point
                {
                    if((currentTime_u32 - g_CalibWaitTimeMax_ua32[f_PhysAxe_e].startWait_u32)
                        > g_CalibWaitTimeMax_ua32[f_PhysAxe_e].maxTimeWait_u32)
                    {
                        Ret_e = RC_WARNING_LIMIT_REACHED;
                    }
                }
            }
        }        
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_Fsm_PrdTsk_Operational
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_OpsOffset(t_eGTRY_PhysicalAxe f_PhysAxe_e)
{
    t_eReturnCode Ret_e;
    const t_sGTRY_AxeAppCfg * axeCfg_ps;
    t_eAPPSPM_ItemPrm calibPrm_e;
    t_eAPPSPM_ItemPrm  pulsePerMmPrm_e;
    t_eAPPSPM_ItemPrm  minFreq_e;
    t_uAPPSPM_PrmValType offsetCalibVal_u = {.prmVal_f32 = 0.0f};
    t_uAPPSPM_PrmValType pulsePerMmVal_u = {.prmVal_f32 = 0.0f};
    t_uAPPSPM_PrmValType minFreqVal_u = {.prmVal_u16 = 0.0f};
    t_sint32 pulseValue_s32;
    t_sint32 gtryCalibDirOpposite_s32;

    if(f_PhysAxe_e >= GTRY_PHYS_AXE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)0);
    }
    else 
    {
        Ret_e = RC_OK;
        //---- 1- reach the right accessors axe ----//
        switch(f_PhysAxe_e)
        {
            case GTRY_PHYS_AXE_X:
                gtryCalibDirOpposite_s32 = -GTRY_CALIB_DIR_AXE_X;
                minFreq_e = APPSPM_PRM_LGC_GTRY_X_SPEED_MIN;
                calibPrm_e = APPSPM_PRM_LGC_GTRY_X_CALIB_OFFSET;
                pulsePerMmPrm_e = APPSPM_PRM_LGC_GTRY_AXE_X_PULSE_PER_MM;
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XL];
            break;
            case GTRY_PHYS_AXE_Y:
                gtryCalibDirOpposite_s32 = -GTRY_CALIB_DIR_AXE_Y;
                minFreq_e = APPSPM_PRM_LGC_GTRY_Y_SPEED_MIN;
                calibPrm_e = APPSPM_PRM_LGC_GTRY_Y_CALIB_OFFSET;
                pulsePerMmPrm_e = APPSPM_PRM_LGC_GTRY_AXE_Y_PULSE_PER_MM;
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Y];
            break;
            case GTRY_PHYS_AXE_Z:
                gtryCalibDirOpposite_s32 = -GTRY_CALIB_DIR_AXE_Z;
                minFreq_e = APPSPM_PRM_LGC_GTRY_Z_SPEED_MIN;
                calibPrm_e = APPSPM_PRM_LGC_GTRY_Z_CALIB_OFFSET;
                pulsePerMmPrm_e = APPSPM_PRM_LGC_GTRY_AXE_Z_PULSE_PER_MM;
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Z];
            break;
            case GTRY_PHYS_AXE_NB:
            default:
                Ret_e = RC_ERROR_WRONG_STATE;
            break;
        }
        //---- 2- Get Motor State ----//
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSPM_GetParam(calibPrm_e, &offsetCalibVal_u);
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSPM_GetParam(pulsePerMmPrm_e, &pulsePerMmVal_u);
            }
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSPM_GetParam(minFreq_e, &minFreqVal_u);
            }
            if(Ret_e == RC_OK)
            {
                pulseValue_s32 = offsetCalibVal_u.prmVal_f32 * pulsePerMmVal_u.prmVal_f32 * gtryCalibDirOpposite_s32;
                Ret_e = APPACT_SetActValue(axeCfg_ps->actIfMtrPulse_e, (t_float32)pulseValue_s32);
                if(Ret_e == RC_OK)
                {
                    Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, (t_float32)minFreqVal_u.prmVal_u16);
                }
                if(Ret_e == RC_OK)
                {
                    Ret_e = APPACT_SetActValue(axeCfg_ps->actIfTimTrig_e, 0.0f);
                }
                if(f_PhysAxe_e == GTRY_PHYS_AXE_X)
                {
                    axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XR];
                    Ret_e = APPACT_SetActValue(axeCfg_ps->actIfMtrPulse_e, (t_float32)pulseValue_s32);
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, (t_float32)minFreqVal_u.prmVal_u16);
                    }
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actIfTimTrig_e, 0.0f);
                    }
                }
            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_Fsm_PrdTsk_Operational
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTsk_Operational(void)
{
    t_eReturnCode Ret_e;

    switch(g_Fsm_PrdTsk_OpeSts_e)
    {
        case GTRY_FSM_PRDTSK_OPE_IDLE:
            Ret_e = s_GTRY_Fsm_PrdTskOpe_Idle();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdTsk_OpeSts_e = GTRY_FSM_PRDTSK_OPE_CMD_CHECK;
            }
        break;
        case GTRY_FSM_PRDTSK_OPE_CMD_CHECK:
            Ret_e = s_GTRY_Fsm_PrdTskOpe_CmdCheck();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdTsk_OpeSts_e = GTRY_FSM_PRDTSK_OPE_CMD_PROCESS;
                g_Fsm_PrdTsk_OpeCmdPrcssSts_e = GTRY_FSM_PRDTSK_OPE_CMDPRCSS_CMPTE_ITER;
            }
            else if(Ret_e == RC_WARNING_NO_OPERATION)
            {
                g_Fsm_PrdTsk_OpeSts_e = GTRY_FSM_PRDTSK_OPE_IDLE;
                Ret_e = RC_OK;
            }
        break;
        case GTRY_FSM_PRDTSK_OPE_CMD_PROCESS:
            Ret_e = s_GTRY_Fsm_PrdTskOpe_CmdProcess();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdTsk_OpeSts_e = GTRY_FSM_PRDTSK_OPE_CMD_PROCESS;
            }
            else if(Ret_e == RC_WARNING_NO_OPERATION)
            {
                g_FlagIterCmdReady_b = FALSE;
                g_Fsm_PrdTsk_OpeSts_e = GTRY_FSM_PRDTSK_OPE_CMD_CHECK;
                Ret_e = RC_OK;
            }
        break;
        default:
            Ret_e = RC_ERROR_WRONG_STATE;
        break;
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_Fsm_PrdTskOpe_Idle
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTskOpe_Idle(void)
{
    t_eReturnCode Ret_e;

    if(g_FlagRcvPosCmd_b == TRUE)
    {
        Ret_e = RC_OK;
    }
    else 
    {
        Ret_e = RC_WARNING_NO_OPERATION;
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_Fsm_PrdTskOpe_CmdCheck
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTskOpe_CmdCheck(void)
{
    t_eReturnCode Ret_e;
    t_float32 posCmdBuffer_af32[GTRY_PHYS_AXE_NB] = {0.0f, 0.0f, 0.0f};
    t_bool isCmdValid_b = TRUE;
    t_uAPPSPM_PrmValType axeXLenght_u = {.prmVal_f32 = 0.0f};
    t_uAPPSPM_PrmValType axeYLenght_u = {.prmVal_f32 = 0.0f};
    t_uAPPSPM_PrmValType axeZLenght_u = {.prmVal_f32 = 0.0f};

    //---- Get the parameter to know if the cmd is not out of range ----//
    Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_AXE_X_LEN,
                            &axeXLenght_u);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_AXE_Y_LEN,
                                &axeYLenght_u);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_AXE_Z_LEN,
                                &axeZLenght_u);
    }
    if(Ret_e == RC_OK)
    {
        //---- Get a fifo cmd pos ----//
        Ret_e = LIBQUEUE_PopElement(&g_QueueCmdPosRcvMngmt_s,
                                    posCmdBuffer_af32,
                                    GTRTY_SIZEOF_ELEM_POSCMD_QUEUE);
        if(Ret_e == RC_OK)
        {
            if(posCmdBuffer_af32[GTRY_PHYS_AXE_X] > axeXLenght_u.prmVal_f32)
            {
                ASSERT((t_uint16)posCmdBuffer_af32[GTRY_PHYS_AXE_X]);
                isCmdValid_b = FALSE;
            }
            else if(posCmdBuffer_af32[GTRY_PHYS_AXE_Y] > axeYLenght_u.prmVal_f32)
            {
                ASSERT((t_uint16)posCmdBuffer_af32[GTRY_PHYS_AXE_Y]);
                isCmdValid_b = FALSE;
            }
            else if(posCmdBuffer_af32[GTRY_PHYS_AXE_Z] > axeZLenght_u.prmVal_f32)
            {
                ASSERT((t_uint16)posCmdBuffer_af32[GTRY_PHYS_AXE_Z]);
                isCmdValid_b = FALSE;
            }
            if(isCmdValid_b == FALSE)   
            {
                //--- Delete element ----//
                Ret_e = RC_WARNING_LIMIT_REACHED;
                (void)LIBQUEUE_ReadElement( &g_QueueCmdPosRcvMngmt_s,
                                            NULL,
                                            GTRTY_SIZEOF_ELEM_POSCMD_QUEUE);
            }
            else 
            {
                Ret_e = RC_OK;
            }
        }
        else if(Ret_e == RC_WARNING_NO_OPERATION)
        {
            g_FlagRcvPosCmd_b = FALSE;
        }
    }

    return Ret_e;
}


/*********************************
 * s_GTRY_Fsm_PrdTskOpe_CmdProcess
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTskOpe_CmdProcess(void)
{
    t_eReturnCode Ret_e;

    switch(g_Fsm_PrdTsk_OpeCmdPrcssSts_e)
    {
        case GTRY_FSM_PRDTSK_OPE_CMDPRCSS_CMPTE_ITER:
            Ret_e = s_GTRY_Fsm_PrdTskOpeCmdPrcss_ComputeIter();
            if(Ret_e == RC_OK)
            {
                FMKCPU_GetTick(&g_startSendIter_u32);
                g_Fsm_PrdTsk_OpeCmdPrcssSts_e = GTRY_FSM_PRDTSK_OPE_CMDPRCSS_SEND_ITERS;
            }
        break;
        case GTRY_FSM_PRDTSK_OPE_CMDPRCSS_SEND_ITERS:
            Ret_e = s_GTRY_Fsm_PrdTskOpeCmdPrcss_SendIter();
            if(Ret_e == RC_OK)
            {
                g_startSendIter_u32 = 0u;
                g_Fsm_PrdTsk_OpeCmdPrcssSts_e = GTRY_FSM_PRDTSK_OPE_CMDPRCSS_CMPTE_ITER;
            }
        break;
        default:
            Ret_e = RC_ERROR_WRONG_STATE;
        break;
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_Fsm_PrdTskOpeCmdPrcss_ComputeIter
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTskOpeCmdPrcss_ComputeIter(void)
{
    t_eReturnCode Ret_e;
    t_float32 posCmdBuffer_af32[GTRY_PHYS_AXE_NB] = {0.0f, 0.0f, 0.0f};
    t_uint32 currenTime_u32;

    if(g_FlagPosCmdPending_b == TRUE)
    {
        FMKCPU_GetTick(&currenTime_u32);
        S_GTRY_CheckAndBuilCommand(g_cmdTypePending_e, currenTime_u32); 
        g_FlagPosCmdPending_b = FALSE;
    }

    Ret_e = LIBQUEUE_PopElement(&g_QueueCmdPosRcvMngmt_s,
                                posCmdBuffer_af32,
                                GTRTY_SIZEOF_ELEM_POSCMD_QUEUE);
    if(Ret_e == RC_OK)
    {
        if(Ret_e == RC_OK)
        {
            Ret_e = s_GTRY_UpdateAlgoParameters();
            if(Ret_e == RC_OK)
            {
                Ret_e = GANTRY_SPEC_AlgorithmSetParam(g_algoParam_s);
            }
        }
        Ret_e = s_GTRY_AlgoMngmt(g_AlgoCpteType_e, posCmdBuffer_af32);

        if(Ret_e == RC_OK)
        {
            
            if(g_FlagIterCmdReady_b == FALSE)
            {
                g_FlagIterCmdReady_b = TRUE;
            } 
            //--- update position expectect ----//
            g_AxesPositionExpected_af32[GTRY_PHYS_AXE_X] = posCmdBuffer_af32[GTRY_PHYS_AXE_X];
            g_AxesPositionExpected_af32[GTRY_PHYS_AXE_Y] = posCmdBuffer_af32[GTRY_PHYS_AXE_Y];
            g_AxesPositionExpected_af32[GTRY_PHYS_AXE_Z] = posCmdBuffer_af32[GTRY_PHYS_AXE_Z];
            //--- delete the element ----//
            (void)LIBQUEUE_ReadElement( &g_QueueCmdPosRcvMngmt_s,
                                        NULL,
                                        GTRTY_SIZEOF_ELEM_POSCMD_QUEUE);
        }
        else 
        {
            ASSERT((t_uint16)Ret_e);
        }
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_Fsm_PrdTskOpeCmdPrcss_SendIter
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTskOpeCmdPrcss_SendIter(void)
{
    t_eReturnCode Ret_e;
    static t_eGTRY_PhysicalAxe currPhysAxe_e = GTRY_PHYS_AXE_NB;
    t_sGTRY_MtrCmdIterPayload cmdIter_s = {
        .frequency_f32 = 0.0f,
        .pulses_s32 = 0
    };
    t_uint8 idxSendCmd_u8;
    t_uAPPSPM_PrmValType sendItertType_u = {.prmVal_u16 = 0};
    t_uint8 mskAxeNoCmdLeft_u8 = (t_uint8)0;

    Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_SENDITER_TYPE, &sendItertType_u);
    if((Ret_e != RC_OK)
    || (sendItertType_u.prmVal_u16 > (t_uint16)GTRY_SEN_ITER_NB))
    {
        ASSERT((t_uint16)Ret_e);
        sendItertType_u.prmVal_u16 = GTRY_SEND_ITER_ASYNC;
    }

    for(idxSendCmd_u8 = 0; 
        (idxSendCmd_u8 < GTRY_MTR_MAX_SEND_ITER) && (Ret_e == RC_OK) ; 
        idxSendCmd_u8++)
    {
        if(currPhysAxe_e == GTRY_PHYS_AXE_NB)
        {
            currPhysAxe_e = GTRY_PHYS_AXE_HEAD; // _X
        }
        for( /* currPhysAxe_e */ ; 
            (currPhysAxe_e < GTRY_PHYS_AXE_NB) && (Ret_e == RC_OK) ; 
            currPhysAxe_e++)
        {
            Ret_e = LIBQUEUE_PopElement(&g_QueueCmdIterMngmt_as[currPhysAxe_e],
                                        &cmdIter_s,
                                        GTRTY_SIZEOF_ELEM_ITERCMD_QUEUE);
            if(Ret_e == RC_OK)
            {
                if(cmdIter_s.pulses_s32 != (t_sint32)0)
                {
                    //---- set the absolute timing ----//
                    cmdIter_s.triggerTimer_f32 = (t_uint32)cmdIter_s.triggerTimer_f32 + g_startSendIter_u32;
                    Ret_e = s_GTRY_SendMtrIteration(currPhysAxe_e, &cmdIter_s);
                }
                if(Ret_e == RC_OK)
                {
                    //---- delete the element ----//
                    Ret_e = LIBQUEUE_ReadElement(&g_QueueCmdIterMngmt_as[currPhysAxe_e],
                                                NULL,
                                                GTRTY_SIZEOF_ELEM_ITERCMD_QUEUE);
                }
                //---- Motor does not accept cmd right now pass to another axe ---//
                else if(Ret_e == RC_WARNING_BUSY)
                {
                    if(sendItertType_u.prmVal_u16 == GTRY_SEND_ITER_BLOCKING)
                    {
                        //--- stop sending pulse for this cyclic retry later 
                        //      with that one ----//
                        Ret_e = RC_WARNING_PENDING;
                    }
                    else
                    {
                        //---- send iteration for others axes and retry this item one 
                        //          on each loop ----//
                        Ret_e = RC_OK;
                    }
                }
            }
            else if(Ret_e == RC_WARNING_NO_OPERATION)
            {
                SETBIT_8B(mskAxeNoCmdLeft_u8, currPhysAxe_e);
                //---- check if no more iteration to send on each motors 
                // if different from all, ket the loop turn ----//
                if(mskAxeNoCmdLeft_u8 != ((1 << GTRY_PHYS_AXE_X) 
                                        | (1 << GTRY_PHYS_AXE_Y)
                                        | 1 << GTRY_PHYS_AXE_Z))
                {
                    Ret_e = RC_OK;
                }
                // else NO_OPE will kill all loop and we'll et out from "send command"
                //  substate of Ope
            }
        }
        //---- out of this states ----//
        // else if(Ret_e == RC_WARNING_NO_OPERATION
    }
    //--- get out of that state ----//
    if(Ret_e == RC_WARNING_NO_OPERATION)
    {
        Ret_e = RC_OK;
    }
    else if(Ret_e >= RC_OK)
    {
        Ret_e = RC_WARNING_PENDING;
    }
    
    return Ret_e; 
}

/*********************************
 * s_GTRY_Fsm_PrdTsk_Safety
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTsk_Safety(void)
{
    t_eReturnCode Ret_e;
    Ret_e = s_GTRY_HardAxeStop(GTRY_PHYS_AXE_X);
    if(Ret_e >= RC_OK)
    {
        Ret_e = s_GTRY_HardAxeStop(GTRY_PHYS_AXE_Y);
    }
    if(Ret_e >= RC_OK)
    {
        Ret_e = s_GTRY_HardAxeStop(GTRY_PHYS_AXE_Z);
    }
    return Ret_e;
}

/*********************************
 * s_GTRY_Fsm_PrdTsk_Error
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTsk_Error(void)
{
    return RC_OK;
}
/*********************************
 * s_GTRY_SendMtrIterations
 *********************************/
static t_eReturnCode s_GTRY_SendMtrIteration(t_eGTRY_PhysicalAxe f_physAxeID_e, t_sGTRY_MtrCmdIterPayload * f_MtrCmdIter_ps)
{
    t_eReturnCode Ret_e;
    const t_sGTRY_AxeAppCfg * axeCfg_ps;
    t_eAPPLGC_SrvHealth axeHealth_e;
    t_uAPPSPM_PrmValType pulsePerMm_u = {.prmVal_f32 = 0.0f};

    if(f_MtrCmdIter_ps == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
        ASSERT((t_uint16)0);
    }
    else if(f_physAxeID_e >= GTRY_PHYS_AXE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)0);
    }
    else if(f_MtrCmdIter_ps->pulses_s32 == (t_sint32)0)
    {
        //---- we don't send no pulse iterations 
        //      even if the algorithm compute so,
        //      cause for drivers it means shutdown the motor ----// 
        Ret_e = RC_OK;
    }
    else
    {
        pulsePerMm_u.prmVal_f32 = 0.0f;
        switch(f_physAxeID_e)
        {
            case GTRY_PHYS_AXE_X:
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XL];

                Ret_e = APPLGC_GetServiceHealth(axeCfg_ps->lgcSrvID_e, &axeHealth_e);
                if(Ret_e != RC_OK)
                {
                    axeHealth_e = APPLGC_SRV_HEALTH_ERROR;
                }
                if(axeHealth_e == APPLGC_SRV_HEALTH_OK)
                {
                    Ret_e = APPACT_SetActValue(axeCfg_ps->actIfMtrPulse_e, f_MtrCmdIter_ps->pulses_s32);
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, f_MtrCmdIter_ps->frequency_f32);
                    }
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actIfTimTrig_e, f_MtrCmdIter_ps->triggerTimer_f32);
                    }
                    if(Ret_e == RC_OK)
                    {
                        axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XR];
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actIfMtrPulse_e, f_MtrCmdIter_ps->pulses_s32);
                        if(Ret_e == RC_OK)
                        {
                            Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, f_MtrCmdIter_ps->frequency_f32);
                        }
                        if(Ret_e == RC_OK)
                        {
                            Ret_e = APPACT_SetActValue(axeCfg_ps->actIfTimTrig_e, f_MtrCmdIter_ps->triggerTimer_f32);
                        }
                    }
                    //--- update compute position ----//
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_AXE_X_PULSE_PER_MM, &pulsePerMm_u);
                        if(Ret_e == RC_OK)
                        {
                            g_AxeComputePos_af32[GTRY_PHYS_AXE_X] += (t_float32)f_MtrCmdIter_ps->pulses_s32 / pulsePerMm_u.prmVal_f32;
                        }
                    }
                }
                else 
                {
                    Ret_e = RC_WARNING_BUSY;
                }
            break;
            case GTRY_PHYS_AXE_Y:
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Y];

                Ret_e = APPLGC_GetServiceHealth(axeCfg_ps->lgcSrvID_e, &axeHealth_e);
                if(Ret_e != RC_OK)
                {
                    axeHealth_e = APPLGC_SRV_HEALTH_ERROR;
                }
                if(axeHealth_e == APPLGC_SRV_HEALTH_OK)
                {
                    Ret_e = APPACT_SetActValue(axeCfg_ps->actIfMtrPulse_e, f_MtrCmdIter_ps->pulses_s32);
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, f_MtrCmdIter_ps->frequency_f32);
                    }
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actIfTimTrig_e, f_MtrCmdIter_ps->triggerTimer_f32);
                    }
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_AXE_Y_PULSE_PER_MM, &pulsePerMm_u);
                        if(Ret_e == RC_OK)
                        {
                            g_AxeComputePos_af32[GTRY_PHYS_AXE_Y] += (t_float32)f_MtrCmdIter_ps->pulses_s32 / pulsePerMm_u.prmVal_f32;
                        }
                    }
                }
                else 
                {
                    Ret_e = RC_WARNING_BUSY;
                }
            break;
            case GTRY_PHYS_AXE_Z:
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Z];

                Ret_e = APPLGC_GetServiceHealth(axeCfg_ps->lgcSrvID_e, &axeHealth_e);
                if(Ret_e != RC_OK)
                {
                    axeHealth_e = APPLGC_SRV_HEALTH_ERROR;
                }
                if(axeHealth_e == APPLGC_SRV_HEALTH_OK)
                {
                    Ret_e = APPACT_SetActValue(axeCfg_ps->actIfMtrPulse_e, f_MtrCmdIter_ps->pulses_s32);
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, f_MtrCmdIter_ps->frequency_f32);
                    }
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actIfTimTrig_e, f_MtrCmdIter_ps->triggerTimer_f32);
                    }
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_AXE_Z_PULSE_PER_MM, &pulsePerMm_u);
                        if(Ret_e == RC_OK)
                        {
                            g_AxeComputePos_af32[GTRY_PHYS_AXE_Z] += (t_float32)f_MtrCmdIter_ps->pulses_s32 / pulsePerMm_u.prmVal_f32;
                        }
                    }
                }
                else 
                {
                    Ret_e = RC_WARNING_BUSY;
                }
            break;
            case GTRY_PHYS_AXE_NB:
            default:
                Ret_e = RC_ERROR_WRONG_STATE;
            break;
        }
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_SigReceptionCallback
 *********************************/
static void s_GTRY_SigReceptionCallback(t_eAPPSIG_Signal f_signal_e, t_float32 f_sigVal_f32)
{
    t_eReturnCode Ret_e;
    t_uint32 currentTime_u32;
    t_eGTRY_CmdSignals currCmdSig_e;
    t_eGTRY_CmdTypeId cmdIdType_e;

    if(f_signal_e >= APPSIG_SIGNAL_NB)
    {
        ASSERT((t_uint16)f_signal_e);
        Ret_e = RC_OK;
    }
    else 
    {
        FMKCPU_GetTick(&currentTime_u32);
        Ret_e = RC_OK;
        if(g_Fsm_PrdcTskSts_e == GTRY_FSM_PRD_TSK_OPS)
        {
            switch(f_signal_e)
            {
                case APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_X:
                    currCmdSig_e = GTRY_CMD_SIG_POS_X;
                    cmdIdType_e = GTRY_CMD_TYPE_ID_CARTESIAN;
                break;
                case APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_Y:
                    currCmdSig_e = GTRY_CMD_SIG_POS_Y;
                    cmdIdType_e = GTRY_CMD_TYPE_ID_CARTESIAN;
                break;
                case APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_Z:  
                    currCmdSig_e = GTRY_CMD_SIG_POS_Z;
                    cmdIdType_e = GTRY_CMD_TYPE_ID_CARTESIAN;
                break;
                case APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_RAYON:  
                    currCmdSig_e = GTRY_CMD_SIG_POS_RAYON;
                    cmdIdType_e = GTRY_CMD_TYPE_ID_SPHERIC;
                break;
                case APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_THETHA:
                    currCmdSig_e = GTRY_CMD_SIG_POS_THETHA;
                    cmdIdType_e = GTRY_CMD_TYPE_ID_SPHERIC;
                break;
                case APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_PHI:
                    currCmdSig_e = GTRY_CMD_SIG_POS_PHI;
                    cmdIdType_e = GTRY_CMD_TYPE_ID_SPHERIC;
                break;
                case APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_X:
                    currCmdSig_e = GTRY_CMD_SIG_STEP_X;
                    cmdIdType_e = GTRY_CMD_TYPE_ID_STEPS;
                break;
                case APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_Y:
                    currCmdSig_e = GTRY_CMD_SIG_STEP_Y;
                    cmdIdType_e = GTRY_CMD_TYPE_ID_STEPS;
                break;
                case APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_Z:
                    currCmdSig_e = GTRY_CMD_SIG_STEP_Z;
                    cmdIdType_e = GTRY_CMD_TYPE_ID_STEPS;
                break;
                case APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_X:
                    currCmdSig_e = GTRY_CMD_SIG_DIR_X;
                    cmdIdType_e = GTRY_CMD_TYPE_ID_STEPS;
                break;
                case APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_Y:
                    currCmdSig_e = GTRY_CMD_SIG_DIR_Y;
                    cmdIdType_e = GTRY_CMD_TYPE_ID_STEPS;
                break;
                case APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_Z:
                    currCmdSig_e = GTRY_CMD_SIG_DIR_Z;
                    cmdIdType_e = GTRY_CMD_TYPE_ID_STEPS;
                break;
                default:
                    currCmdSig_e = GTRY_CMD_SIG_NB;
                    cmdIdType_e = GTRY_CMD_TYPE_ID_NB;
                    Ret_e = RC_WARNING_NO_OPERATION;
                    ASSERT((t_uint16)f_signal_e);
            }
            if(Ret_e == RC_OK)
            {
                g_CmdSigInfo_as[currCmdSig_e].value_f32 = f_sigVal_f32;
                g_CmdSigInfo_as[currCmdSig_e].isRcv_b = TRUE;
                g_CmdSigInfo_as[currCmdSig_e].timeStamp_u32 = currentTime_u32;
                S_GTRY_CheckAndBuilCommand(cmdIdType_e, currentTime_u32);
            }
        }
    }

    return;
}

/*********************************
 * S_GTRY_CheckAndBuilCommand
 *********************************/
static void S_GTRY_CheckAndBuilCommand(t_eGTRY_CmdTypeId f_cmdTypeID_e, t_uint32 f_currentTime_u32)
{
    t_eReturnCode Ret_e;
    t_bool allReceived_b = TRUE;
    t_float32 sigGrpValues_af32[GTRY_CMD_SIG_NB];
    t_bool expired_b = FALSE;
    t_uint32 lastTime_u32 = f_currentTime_u32;
    t_uint8 idxGrpSig_u8;
    const t_sGTRY_SigGroupInfo * grpInfo_ps;
    t_sGTRY_cmdSigInfo * cmdSigInfo_ps;
    t_eAPPSIG_Signal sigGrpList_e;

    if(f_cmdTypeID_e >= GTRY_CMD_TYPE_ID_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)0);
    }
    else 
    {
        grpInfo_ps = &c_GTRY_SigGroupInfo_as[f_cmdTypeID_e];
        for(idxGrpSig_u8 = 0 ; idxGrpSig_u8 < grpInfo_ps->nbsignals_u8 ; idxGrpSig_u8++)
        {
            sigGrpList_e = grpInfo_ps->signal_pe[idxGrpSig_u8];
            cmdSigInfo_ps = &g_CmdSigInfo_as[sigGrpList_e]; 
            if(cmdSigInfo_ps->isRcv_b == FALSE)
            {
                allReceived_b = FALSE;
                break;
            }
            else 
            {
                if((f_currentTime_u32 - cmdSigInfo_ps->timeStamp_u32) > grpInfo_ps->timeoutMs_u32)
                {
                    expired_b = TRUE;
                    break;
                }
                if(cmdSigInfo_ps->timeStamp_u32 < lastTime_u32)
                {
                    lastTime_u32 = cmdSigInfo_ps->timeStamp_u32;
                }
            }
            
        }
        //--- 1- All is received ans we can now process to build the command ----//
        if((allReceived_b == TRUE)
        && (expired_b == FALSE))
        {
            (void)memset(sigGrpValues_af32, 0, (sizeof(t_float32) * GTRY_CMD_SIG_NB));   
            for(idxGrpSig_u8 = 0 ; idxGrpSig_u8 < grpInfo_ps->nbsignals_u8 ; idxGrpSig_u8++)
            {
                sigGrpValues_af32[grpInfo_ps->signal_pe[idxGrpSig_u8]] = 
                    g_CmdSigInfo_as[grpInfo_ps->signal_pe[idxGrpSig_u8]].value_f32;
                g_CmdSigInfo_as[grpInfo_ps->signal_pe[idxGrpSig_u8]].isRcv_b = FALSE;
            }

            if(grpInfo_ps->buildFunc_pf != NULL_FUNCTION)
            {
                Ret_e = grpInfo_ps->buildFunc_pf(sigGrpValues_af32, &g_QueueCmdPosRcvMngmt_s);
                if(Ret_e == RC_WARNING_LIMIT_REACHED)
                {
                    //---- set flag that cmd is pending ----//
                    g_FlagPosCmdPending_b = TRUE;
                    g_cmdTypePending_e = f_cmdTypeID_e;

                }
                else if(Ret_e == RC_OK)
                {
                    g_FlagPosCmdPending_b = FALSE;
                    g_cmdTypePending_e = GTRY_CMD_TYPE_ID_NB;
                    if(g_FlagRcvPosCmd_b == FALSE)
                    {
                        g_FlagRcvPosCmd_b = TRUE;
                    }
                }
                else 
                {
                    ASSERT((t_uint16)Ret_e);
                }
            }
        }
        //--- 2- Timeout happened, we reset -----//
        if(expired_b == TRUE)
        {
            ASSERT((t_uint16)0);
            for(idxGrpSig_u8 = 0 ; idxGrpSig_u8 < grpInfo_ps->nbsignals_u8 ; idxGrpSig_u8++)
            {
                g_CmdSigInfo_as[grpInfo_ps->signal_pe[idxGrpSig_u8]].isRcv_b = FALSE;
            }
        }
    }
    
    return;
}

/*********************************
 * s_GTRY_AlgoMngmt
 *********************************/
static t_eReturnCode s_GTRY_AlgoMngmt(  t_eGTRY_AlgoComputeType f_computeType_e,
                                        t_float32 f_posValues_af32[GTRY_PHYS_AXE_NB])
{
    t_eReturnCode Ret_e;
    t_uint32 startTime_u32;
    t_uint32 endTime_u32;

    FMKCPU_GetTick(&startTime_u32);
    Ret_e = GANTRY_SPEC_AlgorithmCompute(   f_computeType_e,
                                            f_posValues_af32,
                                            g_axeCurrPos_af32,
                                            g_axeMissPulses_af32,
                                            g_QueueCmdIterMngmt_as);
    FMKCPU_GetTick(&endTime_u32);
    g_algoComputeTime_u32 = (endTime_u32 - startTime_u32);
    return Ret_e;
}

/*********************************
 * s_GTRY_UpdateAxePosition
 *********************************/
static t_eReturnCode s_GTRY_UpdateAxePosition(t_eGTRY_PhysicalAxe f_idxAxe_e)
{
    t_eReturnCode Ret_e;

    switch(f_idxAxe_e)
    {
        case GTRY_PHYS_AXE_X:
        {
            t_uint8 ecdrXRCfg_u8 = 0;
            t_uint8 ecdrXLCfg_u8 = 0;
            t_float32 ecdrXLPos_f32 = 0.0f;
            t_float32 ecdrXRPos_f32 = 0.0f;
            t_float32 actMissXLPulse_f32 = 0.0f;
            t_float32 actMissXRPulse_f32 = 0.0f;
            
            //---- 1- Get sys option information ---//
            Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SNS_ECDR_XL, &ecdrXLCfg_u8);
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SNS_ECDR_XR, &ecdrXRCfg_u8);   
            }
            //---- 2- Get missing information ---//
            if(Ret_e == RC_OK)
            {
                APPLGC_GetActValue(APPACT_ACTITF_MTR_XL_PULSE, &actMissXLPulse_f32);
                if(Ret_e == RC_OK)
                {
                    APPLGC_GetActValue(APPACT_ACTITF_MTR_XR_PULSE, &actMissXRPulse_f32);
                }
                if(Ret_e == RC_OK)
                {
                    g_axeMissPulses_af32[GTRY_PHYS_AXE_X] = (actMissXLPulse_f32 + actMissXRPulse_f32) / 2.0f;
                }
            }
            //---- 3- Get sns encodor information ---//
            if(Ret_e == RC_OK)
            {
                if((ecdrXLCfg_u8 > APPSYS_OPT_SNS_ECDR_XL_UNUSED)
                && (ecdrXRCfg_u8 > APPSYS_OPT_SNS_ECDR_XR_UNUSED))
                {
                    Ret_e = APPLGC_GetSnsValue(APPSNS_SNSITF_ECDR_XL_POS, &ecdrXLPos_f32);
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPLGC_GetSnsValue(APPSNS_SNSITF_ECDR_XR_POS, &ecdrXLPos_f32);
                    }
                    if(Ret_e == RC_OK)
                    {
                        g_AxesFeedbackPos_af32[GTRY_PHYS_AXE_X] = (ecdrXLPos_f32 + ecdrXRPos_f32) / 2.0;
                        g_axeCurrPos_af32[GTRY_PHYS_AXE_X] = g_AxesFeedbackPos_af32[GTRY_PHYS_AXE_X];
                    }
                }
                else if(ecdrXLCfg_u8 > APPSYS_OPT_SNS_ECDR_XL_UNUSED)
                {
                    Ret_e = APPLGC_GetSnsValue(APPSNS_SNSITF_ECDR_XL_POS, &ecdrXLPos_f32);
                    if(Ret_e == RC_OK)
                    {
                        g_AxesFeedbackPos_af32[GTRY_PHYS_AXE_X] = ecdrXLPos_f32;
                        g_axeCurrPos_af32[GTRY_PHYS_AXE_X] = g_AxesFeedbackPos_af32[GTRY_PHYS_AXE_X];
                    }
                }
                else if(ecdrXRCfg_u8 > APPSYS_OPT_SNS_ECDR_XR_UNUSED)
                {
                    Ret_e = APPLGC_GetSnsValue(APPSNS_SNSITF_ECDR_XR_POS, &ecdrXRPos_f32);
                    if(Ret_e == RC_OK)
                    {
                        g_AxesFeedbackPos_af32[GTRY_PHYS_AXE_X] = ecdrXRPos_f32;
                        g_axeCurrPos_af32[GTRY_PHYS_AXE_X] = g_AxesFeedbackPos_af32[GTRY_PHYS_AXE_X];
                    }
                }
                else 
                {
                    g_AxesFeedbackPos_af32[GTRY_PHYS_AXE_X] = 0.0f;
                    g_axeCurrPos_af32[GTRY_PHYS_AXE_X] = g_AxeComputePos_af32[GTRY_PHYS_AXE_X];
                }
            }
        }
        break;
        case GTRY_PHYS_AXE_Y:
        case GTRY_PHYS_AXE_Z:
        {
            t_uint8 ecdrCfg_u8 = 0;
            t_float32 ecdrPosValue_f32;
            t_float32 actMissPulse_f32 = 0.0f;
            t_eGTRY_AxeHandleList axeHandle_e;
            if(f_idxAxe_e == GTRY_PHYS_AXE_Y)
            {
                axeHandle_e = GTRY_AXE_HANDLE_Y;
            }
            else 
            {
                axeHandle_e = GTRY_AXE_HANDLE_Z;
            }
            const t_sGTRY_AxeAppCfg * appxeCfg_ps = &c_GTRY_AppAxesCfg_as[axeHandle_e];
            
            //---- 1- Get sys option information ---//
            Ret_e = APPSYS_GetSysOption(appxeCfg_ps->sysOptEcdr_e, &ecdrCfg_u8);
            //---- 2- Get missing information ---//
            if(Ret_e == RC_OK)
            {
                APPLGC_GetActValue(appxeCfg_ps->actIfMtrPulse_e, &actMissPulse_f32);
                if(Ret_e == RC_OK)
                {
                    g_axeMissPulses_af32[f_idxAxe_e] = actMissPulse_f32;
                }
            }
            if(Ret_e == RC_OK)
            {
                if(ecdrCfg_u8 > APPSYS_OPT_SNS_ECDR_Y_UNUSED)
                {
                    Ret_e = APPLGC_GetSnsValue(appxeCfg_ps->snsIfEcdrPos_e, &ecdrPosValue_f32);
                    if(Ret_e == RC_OK)
                    {
                        g_AxesFeedbackPos_af32[f_idxAxe_e] = ecdrPosValue_f32;
                        g_axeCurrPos_af32[f_idxAxe_e] = ecdrPosValue_f32;
                    }
                    else 
                    {
                        g_AxesFeedbackPos_af32[f_idxAxe_e] = 0.0f;
                        g_axeCurrPos_af32[f_idxAxe_e] = g_AxeComputePos_af32[f_idxAxe_e];
                    }
                }
                else 
                {
                    g_AxesFeedbackPos_af32[f_idxAxe_e] = 0.0f;
                    g_axeCurrPos_af32[f_idxAxe_e] = g_AxeComputePos_af32[f_idxAxe_e];
                }
            }
        }
        break;
        case GTRY_PHYS_AXE_NB:
        default:
            Ret_e = RC_ERROR_PARAM_INVALID;
        break;
    }

    //---- update delta ----//
    g_DeltaPos_af32[f_idxAxe_e] = g_AxeComputePos_af32[f_idxAxe_e] - g_axeCurrPos_af32[f_idxAxe_e];

    return Ret_e;
}

/*********************************
 * s_GTRY_HardAxeStop static t_eReturnCode s_GTRY_EnableAxe(t_eGTRY_PhysicalAxe f_idxAxe_e)
 *********************************/
static t_eReturnCode s_GTRY_HardAxeStop(t_eGTRY_PhysicalAxe f_idxAxe_e)
{
    t_eReturnCode Ret_e;
    const t_sGTRY_AxeAppCfg * appAxeCfg_ps;

    if(f_idxAxe_e > GTRY_PHYS_AXE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)0);
    }
    else 
    {
        switch(f_idxAxe_e)
        {
            case GTRY_PHYS_AXE_X:
                appAxeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XL];
                Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, APPACT_HARD_STOP);
                appAxeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XR];
                Ret_e |= APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, APPACT_HARD_STOP);
            break;
            case GTRY_PHYS_AXE_Y:
                appAxeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Y];
                Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, APPACT_HARD_STOP);
            break;
            case GTRY_PHYS_AXE_Z:
            appAxeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Z];
            Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, APPACT_HARD_STOP);
            break;
            case GTRY_PHYS_AXE_NB:
            default:
                Ret_e = RC_ERROR_WRONG_STATE;
            break;
        }
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_EnableAxe 
 *********************************/
static t_eReturnCode s_GTRY_EnableAxe(t_eGTRY_PhysicalAxe f_idxAxe_e)
{
    t_eReturnCode Ret_e;
    const t_sGTRY_AxeAppCfg * appAxeCfg_ps;

    if(f_idxAxe_e > GTRY_PHYS_AXE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)0);
    }
    else 
    {
        switch(f_idxAxe_e)
        {
            case GTRY_PHYS_AXE_X:
                appAxeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XL];
                Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, APPACT_ENABLE_MOTOR);
                appAxeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XR];
                Ret_e |= APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, APPACT_ENABLE_MOTOR);
            break;
            case GTRY_PHYS_AXE_Y:
                appAxeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Y];
                Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, APPACT_ENABLE_MOTOR);
            break;
            case GTRY_PHYS_AXE_Z:
            appAxeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Z];
            Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, APPACT_ENABLE_MOTOR);
            break;
            case GTRY_PHYS_AXE_NB:
            default:
                Ret_e = RC_ERROR_WRONG_STATE;
            break;
        }
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_UpdateAlgoParameters 
 *********************************/
static t_eReturnCode s_GTRY_UpdateAlgoParameters(void)
{
    t_eReturnCode Ret_e;
    t_eGTRY_PhysicalAxe idxAxe_e;
    t_uAPPSPM_PrmValType prmValue_u;

    //----1- init the algo parameter ----//
    Ret_e = RC_OK;
    for(idxAxe_e = GTRY_PHYS_AXE_HEAD ; (idxAxe_e < GTRY_PHYS_AXE_NB) && (Ret_e == RC_OK) ; idxAxe_e++)
    {
        prmValue_u.prmVal_u16 = 0u;
        Ret_e = APPSPM_GetParam(c_GTRY_AlgoItemPrm_s.MinFreq_ae[idxAxe_e], &prmValue_u);
        if(Ret_e == RC_OK)
        {
            g_algoParam_s.MinFreq_af32[idxAxe_e] = (t_float32)prmValue_u.prmVal_u16;
        }
        if(Ret_e == RC_OK)
        {
            prmValue_u.prmVal_u16 = 0u;
            Ret_e = APPSPM_GetParam(c_GTRY_AlgoItemPrm_s.MaxFreq_ae[idxAxe_e], &prmValue_u);
            if(Ret_e == RC_OK)
            {
                g_algoParam_s.MaxFreq_af32[idxAxe_e] = (t_float32)prmValue_u.prmVal_u16;
            }
        }
        if(Ret_e == RC_OK)
        {
            prmValue_u.prmVal_f32 = 0.0f;
            Ret_e = APPSPM_GetParam(c_GTRY_AlgoItemPrm_s.pulsePerMm_ae[idxAxe_e], &prmValue_u);
            if(Ret_e == RC_OK)
            {
                g_algoParam_s.pulsePerMm_af32[idxAxe_e] = prmValue_u.prmVal_f32;
            }
        }
        if(Ret_e == RC_OK)
        {
            prmValue_u.prmVal_f32 = 0.0f;
            Ret_e = APPSPM_GetParam(c_GTRY_AlgoItemPrm_s.cptPrio_SafeHeight_ae[idxAxe_e], &prmValue_u);
            if(Ret_e == RC_OK)
            {
                g_algoParam_s.cptPrio_SafeHeight_af32[idxAxe_e] = prmValue_u.prmVal_f32;
            }
        }
    }
    if(Ret_e == RC_OK)
    {
        prmValue_u.prmVal_u16 = 0;
        Ret_e = APPSPM_GetParam(c_GTRY_AlgoItemPrm_s.chunkSize_e, &prmValue_u);
        if(Ret_e == RC_OK)
        {
            g_algoParam_s.chunkSize_u16 = prmValue_u.prmVal_u16;

            prmValue_u.prmVal_u16 = 0;
            Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_ALGO_CPTE_TYPE, &prmValue_u);
            if(Ret_e == RC_OK)
            {
                g_AlgoCpteType_e = prmValue_u.prmVal_u16;
            }
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
 *	@params[in] 
 *	@params[out]
 *	 
 *
 *
 */

