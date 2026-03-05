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
    GTRY_FSM_PRD_TSK_PREOPS,               //---- Fsm for operational ----//
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
    GTRY_FSM_PRDTSK_CALIB_OPE_REGISTER,         //----Fsm for calibration, sub state axe xxx -> register calib value ----//
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

///@brief calibration command information (CAN)
typedef struct
{
    t_eGTRY_PhysicalAxe axe_e;
    t_eAPPLGC_CalibStatus reqSts_e;
    t_eAPPLGC_CalibStatus currSts_e;
    t_bool isNewCmdReceiv_b;
} t_sGTRY_CalibCmdInfo;

///@brief Rearmament info
typedef struct
{
    t_eAPPLGC_RearmType rearmType_e;
    t_bool reqRearm_b;
} t_sGTRY_RearmInfo;
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
///@brief flag to know when the parameter has been set once correctly
static t_bool g_FlagPrmSet_b = FALSE;

static t_eGTRY_CmdTypeId g_cmdTypePending_e = GTRY_CMD_TYPE_ID_NB;

///@brief Time Max to wait for the axe to go to the calibration point 
static t_sGTRY_CalibWaitInfo g_CalibWaitTimeMax_ua32[GTRY_PHYS_AXE_NB];
///@brief calibration command state from CAN
static t_sGTRY_CalibCmdInfo g_calibCmdInfo_s;
///@brief rearm command state from CAN
static t_sGTRY_RearmInfo g_RearmInfo_s;

///@brief store the parameter in case we want to change it in runtime 
static t_sGTRYSPEC_AlgoParameter g_algoParam_s;
static t_eGTRY_AlgoComputeType g_AlgoCpteType_e;
///@brief Algo Computation Time 
static t_uint32 g_algoComputeTime_u32 = 0u;

/// @brief To know where we start to send a iteration plan, for absolute timing planner 
static t_uint32 g_startSendIter_u32 = 0u;

///@brief Flag Motor Enable 
static t_bool g_FlagMotorEnable_b = FALSE;

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
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_OpsRegister(t_eGTRY_PhysicalAxe f_PhysAxe_e);
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
static t_eReturnCode s_GTRY_Fsm_PrdTsk_PreOperational(void);

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
static t_eReturnCode s_GTRY_ApplyRearmRequest(void);
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
 * @return void
 */
static void s_GTRY_MsgReceptionCallback( t_uint16 f_msgID_u16,
                                         t_uint8 f_nbSignal_u8,
                                         t_eAPPSIG_Signal *f_signal_ae,
                                         t_float32 *f_sigValue_af32);
/**
 * @brief This function handle the reception of signals from APPSIG
 * ----------------------------------------------------------------------------
 * @param[in] f_signal_e : signal ID
 * @param[in] f_sigVal_f32 :signl; value
 * ----------------------------------------------------------------------------
 * @return void
 */
static t_eReturnCode s_GTRY_GetPhysAxeFromSnsItf(t_eAPPSNS_SnsInterface f_snsItf_e,
                                                 t_eGTRY_PhysicalAxe * f_pAxe_e);
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
static t_eReturnCode s_GTRY_AxeStop(t_eGTRY_PhysicalAxe f_idxAxe_e, t_bool f_isHardStop_b);
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
 * @brief Enable the motor axes
 * 
 * ----------------------------------------------------------------------------
 * @param[in] f_idxAxe_e : axe to set new position
 * @param[in] f_setPoint_s32 : set point to reach (pulses)
 * @param[in] f_speed_f32 : speed of the setpoint (frequency)
 * @param[in] f_trigTiming_u32 : motor get the capabilities to store the command and set it in f_trigTiming_u32 ms
 * ----------------------------------------------------------------------------
 * @return RC_OK  : command set
 * @return RC_WARNING_BUSY  : Health of the axe is not correct 
 * @return others : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_SetAxeSetPoint( t_eGTRY_PhysicalAxe f_idxAxe_e, 
                                            t_sint32 f_setPoint_s32,
                                            t_float32 f_speed_f32, 
                                            t_float32 f_trigTiming_u32);
/**
 * @brief Get/ Update the parameter used for gantry algorithm
 * 
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_UpdateAlgoParameters();
/**
 * @brief Update Signal for debugging process
 * 
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static void s_GTRYDebugRoutine();

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
    t_eGTRY_CmdMsg idxMsg_e;
    t_sLIBQUEUE_QueueCfg CmdPosFifoCfg_s;
    t_sLIBQUEUE_QueueCfg CmdIterFifoCfg_s;

    Ret_e = RC_OK;
    //---- init all relative stuff to axes ----//
    for(idxAxe_e = GTRY_PHYS_AXE_HEAD ; (idxAxe_e < GTRY_PHYS_AXE_NB) && (Ret_e == RC_OK) ; idxAxe_e++)
    {
        CmdIterFifoCfg_s.bufferHead_pv = &g_BufferCmdMtrIter_as[idxAxe_e];
        CmdIterFifoCfg_s.actualSize_u16 = GTRY_CMD_ITER_BUFFER_LEN;
        CmdIterFifoCfg_s.elementSize_u16 = sizeof(t_sGTRY_MtrCmdIterPayload);
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

    //---- register CAN message callback ----//
    if(Ret_e == RC_OK)
    {
        for(idxMsg_e = GTRY_CMD_MSGSIG_HEAD ; (idxMsg_e < GTRY_CMD_MSGSIG_NB) && (Ret_e == RC_OK) ; idxMsg_e++)
        {
            Ret_e = APPSIG_AddRcvMsgCallback(   c_GTRY_SubMsgSig_ae[idxMsg_e],
                                                APPSIG_MSG_ORIGIN_CAN,
                                                s_GTRY_MsgReceptionCallback);
        }
    }
    if(Ret_e == RC_OK)
    {
        CmdPosFifoCfg_s.bufferHead_pv = &g_BufferCmdPosRcv_af32[0];
        CmdPosFifoCfg_s.actualSize_u16 = GTRY_CMD_POS_RCV_BUFFER_LEN;
        CmdPosFifoCfg_s.elementSize_u16 = GTRTY_SIZEOF_ELEM_POSCMD_QUEUE;
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
    g_calibCmdInfo_s.axe_e = GTRY_PHYS_AXE_NB;
    g_calibCmdInfo_s.reqSts_e = APPLGC_CALIB_REQSTS_IDLE;
    g_calibCmdInfo_s.currSts_e = APPLGC_CALIB_REQSTS_IDLE;
    g_calibCmdInfo_s.isNewCmdReceiv_b = FALSE;
    g_RearmInfo_s.rearmType_e = LGC_REARM_TYPE_NB;
    g_RearmInfo_s.reqRearm_b = FALSE;

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
    if((Ret_e == RC_OK)
    && (g_FlagPrmSet_b == TRUE))
    {
        Ret_e = s_GTRY_UpdatePosition();
    }
    //---- 3- Call State Machine ----//
    if(Ret_e == RC_OK)
    {
        Ret_e = s_GTRY_StateMachine();
    }

    //---- 4- Debug Routine ----//
    s_GTRYDebugRoutine();
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
    &&      (g_Fsm_PrdcTskSts_e != GTRY_FSM_PRD_TSK_OPS))
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
                g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_PREOPS;
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
                g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_PREOPS;
            }
            else if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_SAFETY;
            }
        break;
        case GTRY_FSM_PRD_TSK_PREOPS:
            Ret_e = s_GTRY_Fsm_PrdTsk_PreOperational();
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
        break;
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

    
    
    //---- 2- Init the algo parameter ----//
    Ret_e = s_GTRY_UpdateAlgoParameters();

    //---- 3- Update flag ----//
    if(g_FlagPrmSet_b == FALSE)
    {
        g_FlagPrmSet_b = TRUE;
    }
    
    //---- 4- send the algo parameter ----//
    if(Ret_e == RC_OK)
    {
        Ret_e = GANTRY_SPEC_AlgorithmSetParam(g_algoParam_s);
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_Fsm_PrdTsk_Calibration
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTsk_Calibration(void)
{   
    t_eReturnCode Ret_e = RC_OK;
    t_eAPPLGC_CalibFeedbackSts feedbackSts_e = APPLGC_CALIB_FBSTS_UNDEFINED_ERROR;

    if(g_FlagMotorEnable_b == FALSE)
    {
        feedbackSts_e = APPLGC_CALIB_FBSTS_MTR_DISABLE;
        FMKSRL_LOG("[GTRY][CALIB] : Motor Disable, could not proceed calibration\r\n");
    }
    else if(g_calibCmdInfo_s.reqSts_e == APPLGC_CALIB_REQSTS_IDLE)
    {
        feedbackSts_e = APPLGC_CALIB_FBSTS_REGIST_VAL_FAILED;
        FMKSRL_LOG("[GTRY][CALIB] : No active calibration request\r\n");
    }
    else
    {
        switch(g_Fsm_PrdTsk_CalibSts_e)
        {
            case GTRY_FSM_PRDTSK_CALIB_INIT:
                g_Fsm_PrdTsk_CalibOpeSts_ae[GTRY_PHYS_AXE_X] = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
                g_Fsm_PrdTsk_CalibOpeSts_ae[GTRY_PHYS_AXE_Y] = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
                g_Fsm_PrdTsk_CalibOpeSts_ae[GTRY_PHYS_AXE_Z] = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
                if(g_calibCmdInfo_s.axe_e == GTRY_PHYS_AXE_X)
                {
                    g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_AXE_X;
                }
                else if(g_calibCmdInfo_s.axe_e == GTRY_PHYS_AXE_Y)
                {
                    g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_AXE_Y;
                }
                else if(g_calibCmdInfo_s.axe_e == GTRY_PHYS_AXE_Z)
                {
                    g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_AXE_Z;
                }
                else
                {
                    Ret_e = RC_ERROR_PARAM_INVALID;
                    ASSERT((t_uint16)g_calibCmdInfo_s.axe_e);
                }
                if(Ret_e == RC_OK)
                {
                    feedbackSts_e = APPLGC_CALIB_FBSTS_ONGOING;
                    Ret_e = RC_WARNING_PENDING;
                    FMKSRL_LOG("[GTRY][CALIB] : Start autonomous calibration for axe %d\r\n",
                               (t_sint32)g_calibCmdInfo_s.axe_e);
                }
            break;
            case GTRY_FSM_PRDTSK_CALIB_AXE_X:
                Ret_e = s_GTRY_Fsm_PrdTskCalib_Ops(GTRY_CALIB_ID_AXE_X);
                if(Ret_e == RC_OK)
                {
                    g_AxeComputePos_af32[GTRY_PHYS_AXE_X] = 0.0f;
                    g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_INIT;
                    feedbackSts_e = APPLGC_CALIB_FBSTS_REGIST_VAL_SUCCEED;
                    g_calibCmdInfo_s.reqSts_e = APPLGC_CALIB_REQSTS_IDLE;
                    g_calibCmdInfo_s.currSts_e = APPLGC_CALIB_REQSTS_IDLE;
                    g_calibCmdInfo_s.isNewCmdReceiv_b = FALSE;
                    FMKSRL_LOG("[GTRY][CALIB] : Autonomous calibration X done\r\n");
                }
                else if(Ret_e == RC_WARNING_LIMIT_REACHED)
                {
                    g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_SAFETY;
                    feedbackSts_e = APPLGC_CALIB_FBSTS_SET_VAL_FAILED;
                }
                else
                {
                    feedbackSts_e = APPLGC_CALIB_FBSTS_ONGOING;
                }
            break;
            case GTRY_FSM_PRDTSK_CALIB_AXE_Y:
                Ret_e = s_GTRY_Fsm_PrdTskCalib_Ops(GTRY_CALIB_ID_AXE_Y);
                if(Ret_e == RC_OK)
                {
                    g_AxeComputePos_af32[GTRY_PHYS_AXE_Y] = 0.0f;
                    g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_INIT;
                    feedbackSts_e = APPLGC_CALIB_FBSTS_REGIST_VAL_SUCCEED;
                    g_calibCmdInfo_s.reqSts_e = APPLGC_CALIB_REQSTS_IDLE;
                    g_calibCmdInfo_s.currSts_e = APPLGC_CALIB_REQSTS_IDLE;
                    g_calibCmdInfo_s.isNewCmdReceiv_b = FALSE;
                    FMKSRL_LOG("[GTRY][CALIB] : Autonomous calibration Y done\r\n");
                }
                else if(Ret_e == RC_WARNING_LIMIT_REACHED)
                {
                    g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_SAFETY;
                    feedbackSts_e = APPLGC_CALIB_FBSTS_SET_VAL_FAILED;
                }
                else
                {
                    feedbackSts_e = APPLGC_CALIB_FBSTS_ONGOING;
                }
            break;
            case GTRY_FSM_PRDTSK_CALIB_AXE_Z:
                Ret_e = s_GTRY_Fsm_PrdTskCalib_Ops(GTRY_CALIB_ID_AXE_Z);
                if(Ret_e == RC_OK)
                {
                    g_AxeComputePos_af32[GTRY_PHYS_AXE_Z] = 0.0f;
                    g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_INIT;
                    feedbackSts_e = APPLGC_CALIB_FBSTS_REGIST_VAL_SUCCEED;
                    g_calibCmdInfo_s.reqSts_e = APPLGC_CALIB_REQSTS_IDLE;
                    g_calibCmdInfo_s.currSts_e = APPLGC_CALIB_REQSTS_IDLE;
                    g_calibCmdInfo_s.isNewCmdReceiv_b = FALSE;
                    FMKSRL_LOG("[GTRY][CALIB] : Autonomous calibration Z done\r\n");
                }
                else if(Ret_e = RC_WARNING_PENDING)
                {
                    feedbackSts_e = APPLGC_CALIB_FBSTS_ONGOING;
                }
                else if(Ret_e < RC_OK)
                {
                    g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_SAFETY;
                    feedbackSts_e = APPLGC_CALIB_FBSTS_SET_VAL_FAILED;
                }
            break;
            case GTRY_FSM_PRDTSK_CALIB_AXE_ALL:
            default:
                feedbackSts_e = APPLGC_CALIB_FBSTS_WRONG_STATE;
                Ret_e = RC_ERROR_WRONG_STATE;
            break;
        }
    }

    (void)APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_CMD_CALIB_CURR_FEEDBACK, feedbackSts_e);
    (void)APPSIG_ForceMsgSend(APPSIG_MSG_ORIGIN_CAN, APPSIG_CAN_MSG_LGC_GTRY_CMD_CALIBRATION);
    return Ret_e;
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
                        g_Fsm_PrdTsk_CalibOpeSts_ae[currAxeId_e] = GTRY_FSM_PRDTSK_CALIB_OPE_REGISTER;
                        Ret_e = RC_WARNING_PENDING;
                    }
                    else if((Ret_e < RC_OK)
                    ||      (Ret_e == RC_WARNING_LIMIT_REACHED))
                    {
                        //---- restart operation ----//
                        if(Ret_e == RC_WARNING_LIMIT_REACHED)
                        {
                            Ret_e = RC_WARNING_PENDING;
                            FMKSRL_LOG("Retry operation for ax id =%d0", currAxeId_e);
                            g_Fsm_PrdTsk_CalibOpeSts_ae[currAxeId_e] = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
                        }
                        APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_GTRY_CALIB_ERROR,
                                                APPSDM_DIAG_ITEM_REPORT_FAIL,
                                                (t_uint16)currAxeId_e,
                                                (t_uint16)Ret_e);
                    }
                break;
                case GTRY_FSM_PRDTSK_CALIB_OPE_REGISTER:
                    Ret_e = s_GTRY_Fsm_PrdTskCalib_OpsRegister(currAxeId_e);
                    if(Ret_e == RC_OK)
                    {
                        g_Fsm_PrdTsk_CalibOpeSts_ae[currAxeId_e] = GTRY_FSM_PRDTSK_CALIB_OPE_OFFSET_AXE;
                        Ret_e = RC_WARNING_PENDING;
                    }
                    else if(Ret_e > RC_OK)
                    {
                        FMKSRL_LOG("Retry operation for ax id =%d0", currAxeId_e);
                        g_Fsm_PrdTsk_CalibOpeSts_ae[currAxeId_e] = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
                    }
                    // leave upper state deals with error
                break;
                case GTRY_FSM_PRDTSK_CALIB_OPE_OFFSET_AXE:
                    Ret_e = s_GTRY_Fsm_PrdTskCalib_OpsOffset(currAxeId_e);
                    if(Ret_e == RC_OK)
                    {
                        g_Fsm_PrdTsk_CalibOpeSts_ae[currAxeId_e] = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
                        APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_GTRY_CALIB_ERROR,
                                                APPSDM_DIAG_ITEM_REPORT_PASS,
                                                (t_uint16)currAxeId_e,
                                                (t_uint16)0);
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
    t_uAPPSPM_PrmValType minMtrFreq_u = {.prmVal_u16 = 0};
    t_uAPPSPM_PrmValType axeLenghtMm_u = {.prmVal_f32 = 0.0f};
    t_sint32 pulseToSend_s32 = 0;
    t_sint32 pulseFactor_s32;
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
                minSpeedID_e = APPSPM_PRM_GTRY_X_SPD_MIN;
                axeLenghtID_e = APPSPM_PRM_GTRY_AXE_X_LEN_MM;
            break;
            case GTRY_PHYS_AXE_Y:
                pulseFactor_s32 = GTRY_CALIB_DIR_AXE_Y;
                minSpeedID_e = APPSPM_PRM_GTRY_Y_SPD_MIN;
                axeLenghtID_e = APPSPM_PRM_GTRY_AXE_Y_LEN_MM;
            break;
            case GTRY_PHYS_AXE_Z:
                pulseFactor_s32 = GTRY_CALIB_DIR_AXE_Z;
                minSpeedID_e = APPSPM_PRM_GTRY_Z_SPD_MIN;
                axeLenghtID_e = APPSPM_PRM_GTRY_AXE_Z_LEN_MM;
            break;
            case GTRY_PHYS_AXE_NB:
            default:
                Ret_e = RC_ERROR_WRONG_STATE;
            break;
        }
        //---- 2- Parameter ----//
        if(Ret_e == RC_OK)
        {

            Ret_e = APPSPM_GetParam(axeLenghtID_e, &axeLenghtMm_u);
            
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSPM_GetParam(minSpeedID_e, &minMtrFreq_u);
            }
        }
        //---- 3- Compute and send the motor pulse to get to the reference point ----//
        if(Ret_e == RC_OK)
        {
            pulseToSend_s32 = (t_sint32)(g_algoParam_s.pulsePerMm_af32[f_PhysAxe_e] * axeLenghtMm_u.prmVal_u16);
            pulseToSend_s32 *= pulseFactor_s32;
            
            Ret_e = s_GTRY_SetAxeSetPoint(  f_PhysAxe_e,
                                            pulseToSend_s32,
                                            minMtrFreq_u.prmVal_u16,
                                            0.0f);
        }
        //---- 4- set the maxe time to wait ----//
        if(Ret_e == RC_OK)
        {
            if(pulseToSend_s32 < (t_sint32)0)
            {
                pulseToSend_s32 = -pulseToSend_s32;
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
                        if(((actMtrStsVal_f32 == APPACT_MOTOR_STS_ENDSTOP_CW)
                        || (actMtrStsVal_f32 == APPACT_MOTOR_STS_ENDSTOP_CCW))
                        || ((actMtrXRStsVal_f32 == APPACT_MOTOR_STS_ENDSTOP_CW)
                        || (actMtrXRStsVal_f32 == APPACT_MOTOR_STS_ENDSTOP_CCW)))
                        {
                            Ret_e = RC_OK;
                        }
                        else 
                        {
                            Ret_e = RC_WARNING_PENDING;
                        }
                    }
                }
                else 
                {
                    if((actMtrStsVal_f32 == APPACT_MOTOR_STS_ENDSTOP_CW)
                    || (actMtrStsVal_f32 == APPACT_MOTOR_STS_ENDSTOP_CCW))
                    {
                        Ret_e = RC_OK;
                    }
                    else 
                    {
                        Ret_e = RC_WARNING_PENDING;
                    }
                }
                if(Ret_e == RC_WARNING_PENDING) // means we waiting the motor to get to the calibration point
                {
                    if((currentTime_u32 - g_CalibWaitTimeMax_ua32[f_PhysAxe_e].startWait_u32)
                        > g_CalibWaitTimeMax_ua32[f_PhysAxe_e].maxTimeWait_u32)
                    {
                        //---- stop axes ----//
                        Ret_e = s_GTRY_AxeStop(f_PhysAxe_e, FALSE);
                        if(Ret_e == RC_OK)
                        {
                            Ret_e = RC_WARNING_LIMIT_REACHED;
                        }
                    }
                }
            }
        }        
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_Fsm_PrdTskCalib_OpsRegister
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_OpsRegister(t_eGTRY_PhysicalAxe f_PhysAxe_e)
{
    t_eReturnCode Ret_e;
    t_sAPPSNS_SnsValueInfo snsValInfo_s;
    const t_sGTRY_AxeAppCfg * axeCfg_ps;
    t_char axe_c;

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
                //---- XL calibration ----//
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XL];
                snsValInfo_s.isValueOK_b = FALSE;
                snsValInfo_s.rqstedUnity_u8 = APPSNS_MEASTYPE_RAW;
                snsValInfo_s.rawValue_f32 = 0.0F;
                snsValInfo_s.SnsValue_f32 = 0.0F;

                Ret_e = APPSNS_Get_SnsValue(axeCfg_ps->snsIfEcdrPos_e, &snsValInfo_s);
                if((Ret_e == RC_OK)
                && (snsValInfo_s.isValueOK_b))
                {
                    Ret_e = APPSNSCAL_RegisterReference(axeCfg_ps->snsIfEcdrPos_e,
                                                        snsValInfo_s.rawValue_f32,
                                                        axeCfg_ps->calibExpectValue_f32);
                    if(Ret_e == RC_OK)
                    {
                        FMKSRL_LOG("[GTRY][CALIB] : Current State -> REG_VAL, XL Set calib successfully\r\n");
                    }
                    else 
                    {
                        ASSERT((t_uint16)Ret_e);
                        FMKSRL_LOG("[GTRY][CALIB] : Current State -> REG_VAL, XL Set calib failed, Retcode -> %d\r\n", (t_sint32)Ret_e);
                    }
                }
                if(Ret_e == RC_OK)
                {
                    //---- XR calibration ----//
                    axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XR];
                    snsValInfo_s.isValueOK_b = FALSE;
                    snsValInfo_s.rqstedUnity_u8 = APPSNS_MEASTYPE_RAW;
                    snsValInfo_s.rawValue_f32 = 0.0F;
                    snsValInfo_s.SnsValue_f32 = 0.0F;

                    Ret_e = APPSNS_Get_SnsValue(axeCfg_ps->snsIfEcdrPos_e, &snsValInfo_s);
                    if((Ret_e == RC_OK)
                    && (snsValInfo_s.isValueOK_b))
                    {
                        Ret_e = APPSNSCAL_RegisterReference(axeCfg_ps->snsIfEcdrPos_e,
                                                            snsValInfo_s.rawValue_f32,
                                                            axeCfg_ps->calibExpectValue_f32);
                        if(Ret_e == RC_OK)
                        {
                            FMKSRL_LOG("[GTRY][CALIB] : Current State -> REG_VAL, XR Set calib successfully\r\n");
                        }
                        else 
                        {
                            ASSERT((t_uint16)Ret_e);
                            FMKSRL_LOG("[GTRY][CALIB] : Current State -> REG_VAL, XR Set calib failed, Retcode -> %d\r\n", (t_sint32)Ret_e);
                        }
                    }
                }

            break;
            case GTRY_PHYS_AXE_Y:
            case GTRY_PHYS_AXE_Z:
                //---- XL calibration ----//
                if(f_PhysAxe_e == GTRY_PHYS_AXE_Y)
                {
                    axe_c = 'Y';
                    axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Y];
                }
                else 
                {
                    axe_c = 'Z';
                    axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Z];
                }
                snsValInfo_s.isValueOK_b = FALSE;
                snsValInfo_s.rqstedUnity_u8 = APPSNS_MEASTYPE_RAW;
                snsValInfo_s.rawValue_f32 = 0.0F;
                snsValInfo_s.SnsValue_f32 = 0.0F;

                Ret_e = APPSNS_Get_SnsValue(axeCfg_ps->snsIfEcdrPos_e, &snsValInfo_s);
                if((Ret_e == RC_OK)
                && (snsValInfo_s.isValueOK_b))
                {
                    Ret_e = APPSNSCAL_RegisterReference(axeCfg_ps->snsIfEcdrPos_e,
                                                        snsValInfo_s.rawValue_f32,
                                                        axeCfg_ps->calibExpectValue_f32);
                    if(Ret_e == RC_OK)
                    {
                        FMKSRL_LOG("[GTRY][CALIB] : Current State -> REG_VAL, %c Set calib successfully\r\n", axe_c);
                    }
                    else 
                    {
                        ASSERT((t_uint16)Ret_e);
                        FMKSRL_LOG("[GTRY][CALIB] : Current State -> REG_VAL, %c Set calib failed, Retcode -> %d\r\n", axe_c, (t_sint32)Ret_e);
                    }
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
 * s_GTRY_Fsm_PrdTsk_Operational
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_OpsOffset(t_eGTRY_PhysicalAxe f_PhysAxe_e)
{
    t_eReturnCode Ret_e;
    t_eAPPSPM_ItemPrm calibPrm_e;
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
                minFreq_e = APPSPM_PRM_GTRY_X_SPD_MIN;
                calibPrm_e = APPSPM_PRM_GTRY_X_CALIB_OFFSET_MM;
            break;
            case GTRY_PHYS_AXE_Y:
                gtryCalibDirOpposite_s32 = -GTRY_CALIB_DIR_AXE_Y;
                minFreq_e = APPSPM_PRM_GTRY_Y_SPD_MIN;
                calibPrm_e = APPSPM_PRM_GTRY_Y_CALIB_OFFSET_MM;
            break;
            case GTRY_PHYS_AXE_Z:
                gtryCalibDirOpposite_s32 = -GTRY_CALIB_DIR_AXE_Z;
                minFreq_e = APPSPM_PRM_GTRY_Z_SPD_MIN;
                calibPrm_e = APPSPM_PRM_GTRY_Z_CALIB_OFFSET_MM;
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
                Ret_e = APPSPM_GetParam(minFreq_e, &minFreqVal_u);
            }
            if(Ret_e == RC_OK)
            {
                pulseValue_s32 =  offsetCalibVal_u.prmVal_f32 
                                * g_algoParam_s.pulsePerMm_af32[f_PhysAxe_e] 
                                * gtryCalibDirOpposite_s32;
                Ret_e = s_GTRY_SetAxeSetPoint(  f_PhysAxe_e,
                                                pulseValue_s32,
                                                (t_float32)minFreqVal_u.prmVal_u16,
                                                0.0f);
                
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

    if(g_RearmInfo_s.reqRearm_b == TRUE)
    {
        g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_SAFETY;
        return RC_OK;
    }
    if((g_calibCmdInfo_s.reqSts_e == APPLGC_CALIB_REQSTS_MOVE)
    || (g_calibCmdInfo_s.reqSts_e == APPLGC_CALIB_REQSTS_REGISTER_VALUE))
    {
        g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_CALIB_AXE;
        return RC_OK;
    }

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
 * s_GTRY_Fsm_PrdTsk_PreOperational
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTsk_PreOperational(void)
{
    t_eReturnCode Ret_e;
    //----1- Enable axes Motor ----//
    Ret_e = s_GTRY_EnableAxe(GTRY_PHYS_AXE_X);
    if(Ret_e == RC_OK)
    {
        Ret_e = s_GTRY_EnableAxe(GTRY_PHYS_AXE_Y);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_GTRY_EnableAxe(GTRY_PHYS_AXE_Z);
    }
    if(Ret_e == RC_OK)
    {
        g_FlagMotorEnable_b = TRUE;
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
    t_eAPPSDM_DiagnosticItem diagItem_e;
    t_eGTRY_PhysicalAxe diagPhysAxe_e;

    //---- Get the parameter to know if the cmd is not out of range ----//
    Ret_e = APPSPM_GetParam(APPSPM_PRM_GTRY_AXE_X_LEN_MM,
                            &axeXLenght_u);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_GTRY_AXE_Y_LEN_MM,
                                &axeYLenght_u);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_GTRY_AXE_Z_LEN_MM,
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
            if(posCmdBuffer_af32[GTRY_PHYS_AXE_X] > axeXLenght_u.prmVal_u16)
            {
                ASSERT((t_uint16)posCmdBuffer_af32[GTRY_PHYS_AXE_X]);
                diagPhysAxe_e = GTRY_PHYS_AXE_X;
                diagItem_e = APPSDM_DIAG_ITEM_GTRY_X_LIMIT_REACH;
                isCmdValid_b = FALSE;
            }
            else if(posCmdBuffer_af32[GTRY_PHYS_AXE_Y] > axeYLenght_u.prmVal_u16)
            {
                ASSERT((t_uint16)posCmdBuffer_af32[GTRY_PHYS_AXE_Y]);
                diagItem_e = APPSDM_DIAG_ITEM_GTRY_Y_LIMIT_REACH;
                diagPhysAxe_e = GTRY_PHYS_AXE_X;
                isCmdValid_b = FALSE;
            }
            else if(posCmdBuffer_af32[GTRY_PHYS_AXE_Z] > axeZLenght_u.prmVal_u16)
            {
                ASSERT((t_uint16)posCmdBuffer_af32[GTRY_PHYS_AXE_Z]);
                diagItem_e = APPSDM_DIAG_ITEM_GTRY_Z_LIMIT_REACH;
                diagPhysAxe_e = GTRY_PHYS_AXE_X;
                isCmdValid_b = FALSE;
            }
            if(isCmdValid_b == FALSE)   
            {
                Ret_e = RC_WARNING_LIMIT_REACHED;
                //---- diagnostic event ----//
                APPSDM_ReportDiagEvnt(  diagItem_e,
                                        APPSDM_DIAG_ITEM_REPORT_FAIL,
                                        (t_uint16)posCmdBuffer_af32[diagPhysAxe_e],
                                        (t_uint16)0);
                    
                //--- Delete element ----/:
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

    Ret_e = APPSPM_GetParam(APPSPM_PRM_GTRY_SENDITER_TYPE, &sendItertType_u);
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
                else 
                {
                    ASSERT((t_uint16)Ret_e);
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
    Ret_e = s_GTRY_AxeStop(GTRY_PHYS_AXE_X, TRUE);
    if(Ret_e >= RC_OK)
    {
        Ret_e = s_GTRY_AxeStop(GTRY_PHYS_AXE_Y, TRUE);
    }
    if(Ret_e >= RC_OK)
    {
        Ret_e = s_GTRY_AxeStop(GTRY_PHYS_AXE_Z, TRUE);
    }
    if((Ret_e == RC_OK)
    && (g_FlagMotorEnable_b == TRUE))
    {
        g_FlagMotorEnable_b = FALSE;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_GTRY_ApplyRearmRequest();
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

static t_eReturnCode s_GTRY_ApplyRearmRequest(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eAPPLGC_RearmFeedbackSts rearmSts_e = APP_LGC_REARM_FBSTATUS_FAILED;

    if(g_RearmInfo_s.reqRearm_b == FALSE)
    {
        Ret_e = RC_WARNING_PENDING;
    }
    else
    {
        switch(g_RearmInfo_s.rearmType_e)
        {
            case APPLGC_REARM_TYPE_SAFETY:
                //---- stay here ----//
                rearmSts_e = APP_LGC_REARM_FBSTATUS_SAFETY;
                Ret_e = RC_WARNING_PENDING;
            break;
            case APPLGC_REARM_TYPE_FSM_PRE_OPE:
            case APPLGC_REARM_TYPE_TOTAL:
                (void)LIBQUEUE_ClearAll(&g_QueueCmdPosRcvMngmt_s);
                (void)LIBQUEUE_ClearAll(&g_QueueCmdIterMngmt_as[GTRY_PHYS_AXE_X]);
                (void)LIBQUEUE_ClearAll(&g_QueueCmdIterMngmt_as[GTRY_PHYS_AXE_Y]);
                (void)LIBQUEUE_ClearAll(&g_QueueCmdIterMngmt_as[GTRY_PHYS_AXE_Z]);
                g_FlagRcvPosCmd_b = FALSE;
                g_FlagIterCmdReady_b = FALSE;
                g_FlagPosCmdPending_b = FALSE;
                g_cmdTypePending_e = GTRY_CMD_TYPE_ID_NB;
                g_calibCmdInfo_s.axe_e = GTRY_PHYS_AXE_NB;
                g_calibCmdInfo_s.reqSts_e = APPLGC_CALIB_REQSTS_IDLE;
                g_calibCmdInfo_s.currSts_e = APPLGC_CALIB_REQSTS_IDLE;
                g_calibCmdInfo_s.isNewCmdReceiv_b = FALSE;
                g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_INIT;
                g_Fsm_PrdTsk_OpeSts_e = GTRY_FSM_PRDTSK_OPE_IDLE;
                g_Fsm_PrdTsk_OpeCmdPrcssSts_e = GTRY_FSM_PRDTSK_OPE_CMDPRCSS_CMPTE_ITER;
                g_Fsm_PrdcTskSts_e = GTRY_FSM_PRD_TSK_PREOPS;

                rearmSts_e = APP_LGC_REARM_FBSTATUS_SUCCESS;
                g_RearmInfo_s.reqRearm_b = FALSE;
                g_RearmInfo_s.rearmType_e = LGC_REARM_TYPE_NB;;
            break;
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                ASSERT((t_uint16)g_RearmInfo_s.rearmType_e);
            break;
        }

        if((Ret_e == RC_OK)
        || (Ret_e == RC_WARNING_PENDING))
        {
            (void)APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_CMD_REARMAMENT_STATE, (t_float32)rearmSts_e);
        }
        else 
        {
            (void)APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_CMD_REARMAMENT_STATE, (t_float32)APP_LGC_REARM_FBSTATUS_FAILED);
        }
        (void)APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_CMD_REARMAMENT_AGID, (t_float32)APPLGC_AGENT_GANTRY);
        (void)APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_CMD_REARMAMENT_TYPE, (t_float32)g_RearmInfo_s.rearmType_e);
        (void)APPSIG_ForceMsgSend(APPSIG_MSG_ORIGIN_CAN, APPSIG_CAN_MSG_LGC_REARMAMENT_CMD);
        FMKSRL_LOG("[GTRY] : Rearm applied status -> %d\r\n", rearmSts_e);
    }

    return Ret_e;
}
/*********************************
 * s_GTRY_SendMtrIterations
 *********************************/
static t_eReturnCode s_GTRY_SendMtrIteration(t_eGTRY_PhysicalAxe f_physAxeID_e, t_sGTRY_MtrCmdIterPayload * f_MtrCmdIter_ps)
{
    t_eReturnCode Ret_e;

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
        Ret_e = s_GTRY_SetAxeSetPoint(  f_physAxeID_e,
                                        f_MtrCmdIter_ps->pulses_s32,
                                        f_MtrCmdIter_ps->frequency_f32,
                                        f_MtrCmdIter_ps->triggerTimer_f32);
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_GetPhysAxeFromSnsItf
 *********************************/
static t_eReturnCode s_GTRY_GetPhysAxeFromSnsItf(t_eAPPSNS_SnsInterface f_snsItf_e,
                                                 t_eGTRY_PhysicalAxe * f_pAxe_e)
{
    if(f_pAxe_e == NULL)
    {
        return RC_ERROR_PTR_NULL;
    }

    switch(f_snsItf_e)
    {
        case APPSNS_SNSITF_ECDR_XL_POS:
        case APPSNS_SNSITF_ECDR_XR_POS:
            *f_pAxe_e = GTRY_PHYS_AXE_X;
            return RC_OK;
        case APPSNS_SNSITF_ECDR_Y_POS:
            *f_pAxe_e = GTRY_PHYS_AXE_Y;
            return RC_OK;
        case APPSNS_SNSITF_ECDR_Z_POS:
            *f_pAxe_e = GTRY_PHYS_AXE_Z;
            return RC_OK;
        default:
            return RC_ERROR_PARAM_INVALID;
    }
}

/*********************************
 * s_GTRY_MsgReceptionCallback
 *********************************/
static void s_GTRY_MsgReceptionCallback( t_uint16 f_msgID_u16,
                                         t_uint8 f_nbSignal_u8,
                                         t_eAPPSIG_Signal *f_signal_ae,
                                         t_float32 *f_sigValue_af32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_msgID_u16 >= (t_uint16)APPSIG_CAN_MSG_NB)
    {
        ASSERT((t_uint16)f_msgID_u16);
        return;
    }
    switch(f_msgID_u16)
    {
        case APPSIG_CAN_MSG_LGC_GTRY_CMD_POSITION_COORD:
            if((f_nbSignal_u8 != (t_uint8)3)
            || (f_signal_ae[0] != APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_X)
            || (f_signal_ae[1] != APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_Y)
            || (f_signal_ae[2] != APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_Z))
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
                ASSERT((t_uint16)f_nbSignal_u8);
            }
            else
            {
                Ret_e = GANTRY_SPEC_BuildCartesianCmd(f_sigValue_af32, &g_QueueCmdPosRcvMngmt_s);
                if((Ret_e == RC_OK)
                && (g_FlagRcvPosCmd_b == FALSE))
                {
                    g_FlagRcvPosCmd_b = TRUE;
                }
            }
        break;
        case APPSIG_CAN_MSG_LGC_GTRY_CMD_POSITION_SPHERIC:
            if((f_nbSignal_u8 != (t_uint8)3)
            || (f_signal_ae[0] != APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_RAYON)
            || (f_signal_ae[1] != APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_THETHA)
            || (f_signal_ae[2] != APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_PHI))
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
                ASSERT((t_uint16)f_nbSignal_u8);
            }
            else
            {
                Ret_e = GANTRY_SPEC_BuildSphericCmd(f_sigValue_af32, &g_QueueCmdPosRcvMngmt_s);
                if((Ret_e == RC_OK)
                && (g_FlagRcvPosCmd_b == FALSE))
                {
                    g_FlagRcvPosCmd_b = TRUE;
                }
            }
        break;
        case APPSIG_CAN_MSG_LGC_GTRY_CMD_STEPS:
            if((f_nbSignal_u8 != (t_uint8)6)
            || (f_signal_ae[0] != APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_X)
            || (f_signal_ae[1] != APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_Y)
            || (f_signal_ae[2] != APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_Z)
            || (f_signal_ae[3] != APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_X)
            || (f_signal_ae[4] != APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_Y)
            || (f_signal_ae[5] != APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_Z))
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
                ASSERT((t_uint16)f_nbSignal_u8);
            }
            else
            {
                Ret_e = GANTRY_SPEC_BuildStepCmd(f_sigValue_af32, &g_QueueCmdPosRcvMngmt_s);
                if((Ret_e == RC_OK)
                && (g_FlagRcvPosCmd_b == FALSE))
                {
                    g_FlagRcvPosCmd_b = TRUE;
                }
            }
        break;
        case APPSIG_CAN_MSG_LGC_GTRY_CMD_CALIBRATION:
        {
            t_eAPPSNS_SnsInterface snsItfID_e;
            t_eAPPLGC_CalibStatus reqSts_e;
            t_eGTRY_PhysicalAxe calibAxe_e;

            if((f_nbSignal_u8 != (t_uint8)3)
            || (f_signal_ae[0] != APPSIG_SIGNAL_LGC_CMD_CALIB_ID)
            || (f_signal_ae[1] != APPSIG_SIGNAL_LGC_CMD_CALIB_REQ_STATE)
            || (f_signal_ae[2] != APPSIG_SIGNAL_LGC_CMD_CALIB_CURR_FEEDBACK))
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
                ASSERT((t_uint16)f_nbSignal_u8);
            }
            else
            {
                snsItfID_e = (t_eAPPSNS_SnsInterface)f_sigValue_af32[0];
                reqSts_e = (t_eAPPLGC_CalibStatus)f_sigValue_af32[1];
                Ret_e = s_GTRY_GetPhysAxeFromSnsItf(snsItfID_e, &calibAxe_e);
                if(Ret_e == RC_OK)
                {
                    if(reqSts_e >= APPLGC_CALIB_STS_NB)
                    {
                        Ret_e = RC_ERROR_PARAM_INVALID;
                        ASSERT((t_uint16)reqSts_e);
                    }
                    else
                    {
                        g_calibCmdInfo_s.axe_e = calibAxe_e;
                        g_calibCmdInfo_s.reqSts_e = reqSts_e;
                        g_calibCmdInfo_s.isNewCmdReceiv_b = TRUE;
                        FMKSRL_LOG("[GTRY][CALIB] : Req from msg, snsItf %d axe %d reqState %d\r\n",
                                   (t_sint32)snsItfID_e,
                                   (t_sint32)calibAxe_e,
                                   (t_sint32)reqSts_e);
                    }
                }
                else
                {
                    Ret_e = RC_WARNING_NO_OPERATION;
                }
            }
        }
        break;
        case APPSIG_CAN_MSG_LGC_REARMAMENT_CMD:
        {
            t_eAPPLGC_AgentList agent_e;
            t_eAPPLGC_RearmType rearmType_e;

            if((f_nbSignal_u8 != (t_uint8)3)
            || (f_signal_ae[0] != APPSIG_SIGNAL_LGC_CMD_REARMAMENT_AGID)
            || (f_signal_ae[1] != APPSIG_SIGNAL_LGC_CMD_REARMAMENT_TYPE)
            || (f_signal_ae[2] != APPSIG_SIGNAL_LGC_CMD_REARMAMENT_STATE))
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
                ASSERT((t_uint16)f_nbSignal_u8);
            }
            else
            {
                agent_e = (t_eAPPLGC_AgentList)f_sigValue_af32[0];
                rearmType_e = (t_eAPPLGC_RearmType)f_sigValue_af32[1];
                if(agent_e != APPLGC_AGENT_GANTRY)
                {
                    Ret_e = RC_WARNING_NO_OPERATION;
                }
                else if(rearmType_e >= LGC_REARM_TYPE_NB)
                {
                    Ret_e = RC_ERROR_PARAM_INVALID;
                    ASSERT((t_uint16)rearmType_e);
                }
                else
                {
                    g_RearmInfo_s.rearmType_e = rearmType_e;
                    g_RearmInfo_s.reqRearm_b = TRUE;
                }
            }
        }
        break;
        default:
            Ret_e = RC_WARNING_NO_OPERATION;
        break;
    }

    FMKSRL_LOG("[GTRY] : Receive msg CAN -> %d, Retcode %d\r\n", f_msgID_u16, Ret_e);
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
            t_uAPPSPM_PrmValType pulsePerRound_u = {.prmVal_f32 = 0.0f};
            t_float32 xPosMrad_f32 = 0.0f;
            t_float32 pulsePerMm_f32;
            t_float32 pulsePerRound_f32;
            
            //---- 1- Get sys option information ---//
            Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SNS_ECDR_XL, &ecdrXLCfg_u8);
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SNS_ECDR_XR, &ecdrXRCfg_u8);   
            }
            //---- 2- Get missing information ---//
            if(Ret_e == RC_OK)
            {
                Ret_e = APPLGC_GetActValue(APPACT_ACTITF_MTR_XL_PLS, &actMissXLPulse_f32);
                if(Ret_e == RC_OK)
                {
                    Ret_e = APPLGC_GetActValue(APPACT_ACTITF_MTR_XR_PLS, &actMissXRPulse_f32);
                }
                if(Ret_e == RC_OK)
                {
                    g_axeMissPulses_af32[GTRY_PHYS_AXE_X] = (actMissXLPulse_f32 + actMissXRPulse_f32) / 2.0f;
                }
            }
            //---- 3- Get sns encodor information ---//
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSPM_GetParam(c_GTRY_AlgoItemPrm_s.pulsePerRound_ae[GTRY_PHYS_AXE_X], &pulsePerRound_u);
            }
            if(Ret_e == RC_OK)
            {
                pulsePerMm_f32 = g_algoParam_s.pulsePerMm_af32[GTRY_PHYS_AXE_X];
                pulsePerRound_f32 = (t_float32)pulsePerRound_u.prmVal_u16;
                if(pulsePerMm_f32 <= 0.0f)
                {
                    Ret_e = RC_ERROR_WRONG_CONFIG;
                }
            }
            if(Ret_e == RC_OK)
            {
                if((ecdrXLCfg_u8 > APPSYS_OPT_SNS_ECDR_XL_UNUSED)
                && (ecdrXRCfg_u8 > APPSYS_OPT_SNS_ECDR_XR_UNUSED))
                {
                    Ret_e = APPLGC_GetSnsValue(APPSNS_SNSITF_ECDR_XL_POS, &ecdrXLPos_f32);
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPLGC_GetSnsValue(APPSNS_SNSITF_ECDR_XR_POS, &ecdrXRPos_f32);
                    }
                    if(Ret_e == RC_OK)
                    {
                        // XL = -XR in encoder convention, so physical X uses differential average.
                        xPosMrad_f32 = (ecdrXRPos_f32 - ecdrXLPos_f32) / 2.0f;
                        if(xPosMrad_f32 < 0.0F)
                        {
                            xPosMrad_f32 = -xPosMrad_f32;
                        }
                        g_AxesFeedbackPos_af32[GTRY_PHYS_AXE_X] = (xPosMrad_f32 * pulsePerRound_f32)
                                                                    / (CST_2PI_MRAD * pulsePerMm_f32);
                        g_axeCurrPos_af32[GTRY_PHYS_AXE_X] = g_AxesFeedbackPos_af32[GTRY_PHYS_AXE_X];
                    }
                }
                else if(ecdrXLCfg_u8 > APPSYS_OPT_SNS_ECDR_XL_UNUSED)
                {
                    Ret_e = APPLGC_GetSnsValue(APPSNS_SNSITF_ECDR_XL_POS, &ecdrXLPos_f32);
                    if(Ret_e == RC_OK)
                    {
                        xPosMrad_f32 = ecdrXLPos_f32;
                        g_AxesFeedbackPos_af32[GTRY_PHYS_AXE_X] = (xPosMrad_f32 * pulsePerRound_f32)
                                                                    / (CST_2PI_MRAD * pulsePerMm_f32);
                        g_axeCurrPos_af32[GTRY_PHYS_AXE_X] = g_AxesFeedbackPos_af32[GTRY_PHYS_AXE_X];
                    }
                }
                else if(ecdrXRCfg_u8 > APPSYS_OPT_SNS_ECDR_XR_UNUSED)
                {
                    Ret_e = APPLGC_GetSnsValue(APPSNS_SNSITF_ECDR_XR_POS, &ecdrXRPos_f32);
                    if(Ret_e == RC_OK)
                    {
                        xPosMrad_f32 = -ecdrXRPos_f32;
                        g_AxesFeedbackPos_af32[GTRY_PHYS_AXE_X] = (xPosMrad_f32 * pulsePerRound_f32)
                                                                    / (CST_2PI_MRAD * pulsePerMm_f32);
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
            t_float32 ecdrPosValue_f32 = 0.0f;
            t_float32 actMissPulse_f32 = 0.0f;
            t_uAPPSPM_PrmValType pulsePerRound_u = {.prmVal_f32 = 0.0f};
            t_float32 pulsePerMm_f32 = 0.0f;
            t_float32 pulsePerRound_f32 = 0.0f;
            t_float32 axePosMm_f32 = 0.0f;
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
                APPLGC_GetActValue(appxeCfg_ps->actifMtrSetPoint_e, &actMissPulse_f32);
                if(Ret_e == RC_OK)
                {
                    g_axeMissPulses_af32[f_idxAxe_e] = actMissPulse_f32;
                }
            }
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSPM_GetParam(c_GTRY_AlgoItemPrm_s.pulsePerRound_ae[f_idxAxe_e], &pulsePerRound_u);
            }
            if(Ret_e == RC_OK)
            {
                pulsePerMm_f32 = g_algoParam_s.pulsePerMm_af32[f_idxAxe_e];
                pulsePerRound_f32 = (t_float32)pulsePerRound_u.prmVal_u16;
                if(pulsePerMm_f32 <= 0.0f)
                {
                    Ret_e = RC_ERROR_WRONG_CONFIG;
                }
            }
            if(Ret_e == RC_OK)
            {
                if(ecdrCfg_u8 > APPSYS_OPT_SNS_ECDR_Y_UNUSED)
                {
                    Ret_e = APPLGC_GetSnsValue(appxeCfg_ps->snsIfEcdrPos_e, &ecdrPosValue_f32);
                    if(Ret_e == RC_OK)
                    {
                        axePosMm_f32 = (ecdrPosValue_f32 * pulsePerRound_f32)
                                        / (CST_2PI_MRAD * pulsePerMm_f32);
                        g_AxesFeedbackPos_af32[f_idxAxe_e] = axePosMm_f32;
                        g_axeCurrPos_af32[f_idxAxe_e] = axePosMm_f32;
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
 * s_GTRY_AxeStop
 *********************************/
static t_eReturnCode s_GTRY_AxeStop(t_eGTRY_PhysicalAxe f_idxAxe_e, t_bool f_isHardStop_b)
{
    t_eReturnCode Ret_e;
    const t_sGTRY_AxeAppCfg * appAxeCfg_ps;
    t_float32 spdValue_f32;

    if(f_idxAxe_e >= GTRY_PHYS_AXE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)0);
    }
    else 
    {
        if(f_isHardStop_b == TRUE)
        {
            spdValue_f32 = APPACT_HARD_STOP;
        }
        else 
        {
            spdValue_f32 = APPACT_SOFT_STOP;
        }
        switch(f_idxAxe_e)
        {
            case GTRY_PHYS_AXE_X:
                appAxeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XL];
                Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, spdValue_f32);
                appAxeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XR];
                Ret_e |= APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, spdValue_f32);
            break;
            case GTRY_PHYS_AXE_Y:
                appAxeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Y];
                Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, spdValue_f32);
            break;
            case GTRY_PHYS_AXE_Z:
            appAxeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Z];
            Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, spdValue_f32);
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
 * SetAxeSetPoint
 *********************************/
static t_eReturnCode s_GTRY_SetAxeSetPoint( t_eGTRY_PhysicalAxe f_idxAxe_e, 
                                            t_sint32 f_setPoint_s32,
                                            t_float32 f_speed_f32, 
                                            t_float32 f_trigTiming_f32)
{
    t_eReturnCode Ret_e;
    const t_sGTRY_AxeAppCfg * axeCfg_ps;
    t_eAPPLGC_SrvHealth axeHealth_e;
    t_uAPPSPM_PrmValType pulsePerMm_u = {.prmVal_f32 = 0.0f};

    if(f_idxAxe_e >= GTRY_PHYS_AXE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)0);
    }
    else 
    {
        switch(f_idxAxe_e)
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
                    Ret_e = APPACT_SetActValue(axeCfg_ps->actifMtrSetPoint_e, (t_float32)f_setPoint_s32);
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, f_speed_f32);
                    }
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actIfTimTrig_e, f_trigTiming_f32);
                    }
                    if(Ret_e == RC_OK)
                    {
                        axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XR];
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actifMtrSetPoint_e, (t_float32)f_setPoint_s32);
                        if(Ret_e == RC_OK)
                        {
                            Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, f_speed_f32);
                        }
                        if(Ret_e == RC_OK)
                        {
                            Ret_e = APPACT_SetActValue(axeCfg_ps->actIfTimTrig_e, f_trigTiming_f32);
                        }
                    }
                    //--- update compute position ----//
                    if(Ret_e == RC_OK)
                    {
                        g_AxeComputePos_af32[GTRY_PHYS_AXE_X] += (t_float32)f_setPoint_s32
                                                                    / g_algoParam_s.pulsePerMm_af32[GTRY_PHYS_AXE_X];
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
                    Ret_e = APPACT_SetActValue(axeCfg_ps->actifMtrSetPoint_e, (t_float32)f_setPoint_s32);
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, f_speed_f32);
                    }
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actIfTimTrig_e, f_trigTiming_f32);
                    }
                    if(Ret_e == RC_OK)
                    {
                        g_AxeComputePos_af32[GTRY_PHYS_AXE_Y] += (t_float32)f_setPoint_s32
                                                                    / g_algoParam_s.pulsePerMm_af32[GTRY_PHYS_AXE_Y];
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
                    Ret_e = APPACT_SetActValue(axeCfg_ps->actifMtrSetPoint_e, (t_float32)f_setPoint_s32);
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, f_speed_f32);
                    }
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actIfTimTrig_e, f_trigTiming_f32);
                    }
                    if(Ret_e == RC_OK)
                    {
                        g_AxeComputePos_af32[GTRY_PHYS_AXE_Z] += (t_float32)f_setPoint_s32
                                                                    / g_algoParam_s.pulsePerMm_af32[GTRY_PHYS_AXE_Z];
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
 * s_GTRY_EnableAxe 
 *********************************/
static t_eReturnCode s_GTRY_EnableAxe(t_eGTRY_PhysicalAxe f_idxAxe_e)
{
    t_eReturnCode Ret_e;
    const t_sGTRY_AxeAppCfg * appAxeCfg_ps;

    if(f_idxAxe_e >= GTRY_PHYS_AXE_NB)
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
    t_uAPPSPM_PrmValType prmScdValue_u;
    t_float32 pulsePerMm_f32;

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
            prmValue_u.prmVal_u16 = 0U;
            prmScdValue_u.prmVal_f32 = 0.0F;
            Ret_e = APPSPM_GetParam(c_GTRY_AlgoItemPrm_s.pulsePerRound_ae[idxAxe_e], &prmValue_u);
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSPM_GetParam(c_GTRY_AlgoItemPrm_s.pinionDiamMm_ae[idxAxe_e], &prmScdValue_u);
                if(Ret_e == RC_OK)
                {
                    //---- calculate the pulse per mm ----//
                    //                              pulser per round  / diameter pinion (mm)* PI (rad) (circonference)
                    pulsePerMm_f32 = (t_float32)prmValue_u.prmVal_u16 / (prmScdValue_u.prmVal_f32 * CST_PI_RAD);
                    g_algoParam_s.pulsePerMm_af32[idxAxe_e] = pulsePerMm_f32;
                }
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
            Ret_e = APPSPM_GetParam(APPSPM_PRM_GTRY_ALGO_CPTE_TYPE, &prmValue_u);
            if(Ret_e == RC_OK)
            {
                g_AlgoCpteType_e = prmValue_u.prmVal_u16;
            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_GTRYDebugRoutine 
 *********************************/
static void s_GTRYDebugRoutine()
{
    t_eReturnCode Ret_e;

    ///---- 1- Fsm Variable ----//
    Ret_e = APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_GTRY_FSM_STS, (t_float32)g_Fsm_PrdcTskSts_e);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_GTRY_FSM_CALIB, (t_float32)g_Fsm_PrdTsk_CalibSts_e);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_GTRY_FSM_CLB_AXE_X, (t_float32)g_Fsm_PrdTsk_CalibOpeSts_ae[GTRY_PHYS_AXE_X]);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_GTRY_FSM_CLB_AXE_Y, (t_float32)g_Fsm_PrdTsk_CalibOpeSts_ae[GTRY_PHYS_AXE_Y]);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_GTRY_FSM_CLB_AXE_Z, (t_float32)g_Fsm_PrdTsk_CalibOpeSts_ae[GTRY_PHYS_AXE_Z]);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_GTRY_FSM_OPE, (t_float32)g_Fsm_PrdTsk_OpeSts_e);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_GTRY_FSM_OPE_CMD_PRCSS, (t_float32)g_Fsm_PrdTsk_OpeCmdPrcssSts_e);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_GTRY_AXE_X_POS_MM, (t_float32)g_axeCurrPos_af32[GTRY_PHYS_AXE_X]);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_GTRY_AXE_Y_POS_MM, (t_float32)g_axeCurrPos_af32[GTRY_PHYS_AXE_Y]);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_GTRY_AXE_Z_POS_MM, (t_float32)g_axeCurrPos_af32[GTRY_PHYS_AXE_Z]);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_GTRY_ALGO_COMPUTE_TIME, (t_float32)g_algoComputeTime_u32);
    }
    if(Ret_e < RC_OK)
    {
        ASSERT((t_uint16)0);
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

