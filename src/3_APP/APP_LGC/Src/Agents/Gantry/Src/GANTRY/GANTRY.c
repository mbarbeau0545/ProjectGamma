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
///@brief Command Iteration Payload
typedef struct 
{
    t_sint32 pulses_s32;        //---- pulses to send to the motor ----//
    t_float32 frequency_f32;    //---- frequency of the motor -----//
} t_sGTRY_MtrCmdIterPayload;
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************
///@brief Position Gantry Variables
static t_float32 g_AxesCmptePos_af32[GTRY_PHYS_AXE_NB];
static t_float32 g_AxesFeedbackPos_af32[GTRY_PHYS_AXE_NB];

///@brief Signal reception Managment 
t_sGTRY_cmdSigInfo g_CmdSigInfo_as[GTRY_CMD_SIG_NB];

///@brief Finite State Machine Variables
static t_eGTRY_FsmPeriodicTask g_Fsm_PrdcskSts_e;
static t_eGTRY_FsmPrdTsk_Calib g_Fsm_PrdTsk_CalibSts_e;
static t_eGTRY_FsmPrdTsk_CalibOpe g_Fsm_PrdTsk_CalibOpeSts_e;
static  t_eGTRY_FsmPrdTsk_Ope g_Fsm_PrdTsk_OpeSts_e;
static t_eGTRY_FsmPrdTsk_OpeCmdPrcss g_Fsm_PrdTsk_OpeCmdPrcssSts_e;

///@brief Command Queue Variables
static t_sLIBQUEUE_QueueCore g_QueueCmdPosRcvMngmt_s;
static t_sLIBQUEUE_QueueCore g_QueueCmdIterMngmt_as[GTRY_PHYS_AXE_NB];
static t_float32 g_BufferCmdPosRcv_af32[GTRY_PHYS_AXE_NB][GTRY_CMD_POS_RCV_BUFFER_LEN];
static t_sGTRY_MtrCmdIterPayload g_BufferCmdMtrIter_as[GTRY_PHYS_AXE_NB][GTRY_CMD_ITER_BUFFER_LEN];

///@brief At least one Rcv Command is on the Queue
static t_bool g_FlagRcvPosCmd_b = FALSE;
///@brief At least one Iter Command is on the Queue
static t_bool g_FlagIterCmdReady_b = FALSE;
///@brief One Position cmd cannot be pushed inside PosQueue
static t_bool g_FlagPosCmdPending_b = FALSE;
static t_eGTRY_CmdTypeId g_cmdTypePending_e = GTRY_CMD_TYPE_ID_NB;
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
 * @brief This function check if motors are in a logic state
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_SafetyUpdate(void);
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
 * @brief Iteration Algorithm Core
 * ----------------------------------------------------------------------------
 * @param[in] f_currentTime_u32 : Current Time
 * ----------------------------------------------------------------------------
 * @return 
 */
static t_eReturnCode s_GTRY_IterationAlgorithm(t_float32 f_posValues_af32[GTRY_PHYS_AXE_NB]);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * GTRY_Init
 *********************************/
t_eReturnCode GTRY_Init(void)
{
    t_eReturnCode Ret_e;
    // t_sLIBQUEUE_QueueCfg CmdPosFifoCfg_s = {
    //     .bufferHead_pv = &g_QueueCmdPosRcvMngmt_s[0];
    //     .elementSize_u8 = 
    //     .enableOverwrite_b
    // }
    
    // Ret_e = LIBQUEUE_Create(&g_QueueCmdPosRcvMngmt_s,
    //                         )
    return Ret_e;
}

/*********************************
 * GTRY_Init
 *********************************/
t_eReturnCode GTRY_PeriodicTask(void)
{
    t_eReturnCode Ret_e;
    
    //---- 1- Call Safety Update ----//
    Ret_e = s_GTRY_SafetyUpdate();

    //---- 2- Call State Machine ----//
    if(Ret_e == RC_OK)
    {
        Ret_e = s_GTRY_StateMachine();
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
 * s_GTRY_StateMachine
 *********************************/
static t_eReturnCode s_GTRY_StateMachine(void)
{
    t_eReturnCode Ret_e;

    switch(g_Fsm_PrdcskSts_e)
    {
        case GTRY_FSM_PRD_TSK_CFG:
            Ret_e = s_GTRY_Fsm_PrdTsk_Configuration();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdcskSts_e = GTRY_FSM_PRD_TSK_CALIB_AXE;
                g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_INIT;
            }
            else if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcskSts_e = GTRY_FSM_PRD_TSK_ERROR;
            }
        break;
        case GTRY_FSM_PRD_TSK_CALIB_AXE:
            Ret_e = s_GTRY_Fsm_PrdTsk_Calibration();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdcskSts_e = GTRY_FSM_PRD_TSK_OPS;
                g_Fsm_PrdTsk_OpeSts_e = GTRY_FSM_PRDTSK_OPE_IDLE;
            }
            else if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcskSts_e = GTRY_FSM_PRD_TSK_SAFETY;
            }
        break;
        case GTRY_FSM_PRD_TSK_OPS:
            Ret_e = s_GTRY_Fsm_PrdTsk_Operational();
             if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcskSts_e = GTRY_FSM_PRD_TSK_SAFETY;
            }
        break;
        case GTRY_FSM_PRD_TSK_SAFETY:
            Ret_e = s_GTRY_Fsm_PrdTsk_Safety();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdcskSts_e = GTRY_FSM_PRD_TSK_CFG;
            }
            else if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcskSts_e = GTRY_FSM_PRD_TSK_ERROR;
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
    g_Fsm_PrdcskSts_e = GTRY_FSM_PRD_TSK_CFG;
    g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_INIT;
    g_Fsm_PrdTsk_CalibOpeSts_e = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
    g_Fsm_PrdTsk_OpeSts_e = GTRY_FSM_PRDTSK_OPE_IDLE;
    g_Fsm_PrdTsk_OpeCmdPrcssSts_e = GTRY_FSM_PRDTSK_OPE_CMDPRCSS_CMPTE_ITER;
    return RC_OK;
}

/*********************************
 * s_GTRY_Fsm_PrdTsk_Configuration
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTsk_Calibration(void)
{   
    t_eReturnCode Ret_e;

    switch(g_Fsm_PrdTsk_CalibSts_e)
    {
        case GTRY_FSM_PRDTSK_CALIB_INIT:
        {
            t_uint16 calibType_u16 = 0;
            //---- Get the parameter that define the type of calibration ----//
            Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_CALIB_TYPE, &calibType_u16);
            //---- If not accessible take default one ----//
            if((Ret_e != RC_OK)
            || calibType_u16 >= GTRY_CALIB_TYPE_NB)
            {
                ASSERT((t_uint16)calibType_u16);
                calibType_u16 = GTRY_CALIB_TYPE_ASYNC;
            }
            //---- Reset Fsm State ----//
            g_Fsm_PrdTsk_CalibOpeSts_e = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
            //--- redirect to the right state of state machine ----//
            if(calibType_u16 == (t_uint16)GTRY_CALIB_TYPE_ASYNC)
            {
                g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_AXE_X;
            }
            else if(calibType_u16 == GTRY_CALIB_TYPE_SYNC)
            {
                g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_AXE_ALL;
            }
            else 
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }            
        }
        break;
        case GTRY_FSM_PRDTSK_CALIB_AXE_X:
        {
            Ret_e = s_GTRY_Fsm_PrdTskCalib_Ops(GTRY_CALIB_ID_AXE_X);
            if(Ret_e == RC_OK)
            {
                Ret_e = RC_WARNING_PENDING;
                g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_AXE_Y;
            }
        }
        break;
        case GTRY_FSM_PRDTSK_CALIB_AXE_Y:
        {
            Ret_e = s_GTRY_Fsm_PrdTskCalib_Ops(GTRY_CALIB_ID_AXE_Y);
            if(Ret_e == RC_OK)
            {
                Ret_e = RC_WARNING_PENDING;
                g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_AXE_Z;
            }
        }
        break;
        case GTRY_FSM_PRDTSK_CALIB_AXE_Z:
        {
            Ret_e = s_GTRY_Fsm_PrdTskCalib_Ops(GTRY_CALIB_ID_AXE_Y);
            if(Ret_e == RC_OK)
            {
                //--- out of state calibration ----//
                g_Fsm_PrdTsk_CalibSts_e = GTRY_FSM_PRDTSK_CALIB_INIT;
            }
            break;
        }
        case GTRY_FSM_PRDTSK_CALIB_AXE_ALL:
        {
            Ret_e = s_GTRY_Fsm_PrdTskCalib_Ops(GTRY_CALIB_ID_AXE_ALL);
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
    t_eGTRY_CalibAxeId startAxeId_e;
    t_eGTRY_CalibAxeId endAxeId_e;
    static t_eGTRY_CalibAxeId s_currAxeId_e = GTRY_CALIB_ID_AXE_NB;

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
        //---- 2- Initialisation of static  s_curIdxAxe_e ----//
        if(s_currAxeId_e == GTRY_CALIB_ID_AXE_NB)
        {
            s_currAxeId_e = startAxeId_e;
        }
        //---- 3- state machine calib Ope 
        //      we loop on one axe or all, if return Code OK, we pass
        //      to the other axe, if not OK, we get out and retry with this
        //      axe on next cyclic ----//
        Ret_e = RC_OK;
        for( /* s_currAxeId_e */ ; 
            (s_currAxeId_e < endAxeId_e) && (Ret_e == RC_OK) ; 
            s_currAxeId_e++)
        {
            switch(g_Fsm_PrdTsk_CalibOpeSts_e)
            {
                case GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE:
                    Ret_e = s_GTRY_Fsm_PrdTskCalib_OpsStop(s_currAxeId_e);
                break;
                case GTRY_FSM_PRDTSK_CALIB_OPE_MOVE_AXE:
                    Ret_e = s_GTRY_Fsm_PrdTskCalib_OpsMove(s_currAxeId_e);
                break;
                case GTRY_FSM_PRDTSK_CALIB_OPE_WAIT_AXE:
                    Ret_e = s_GTRY_Fsm_PrdTskCalib_OpsWait(s_currAxeId_e);
                break;
            }
        }
        //--- Ret_e == PENDING ?? Means we stay the same state ----//
        if(Ret_e == RC_OK)
        {
            //---- move to the next state machine -----//
            g_Fsm_PrdTsk_CalibOpeSts_e += (t_eGTRY_FsmPrdTsk_CalibOpe)1;
            //---- check boundaries, means we finished ----//
            if(g_Fsm_PrdTsk_CalibOpeSts_e > GTRY_FSM_PRDTSK_CALIB_OPE_WAIT_AXE)
            {   
                // Ret_e = RC_OK;
                s_currAxeId_e = GTRY_CALIB_ID_AXE_NB;
                g_Fsm_PrdTsk_CalibOpeSts_e = GTRY_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
            }
            else 
            {
                Ret_e = RC_WARNING_PENDING;
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
    t_sGTRY_AxeAppCfg * axeCfg_ps;

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
                Ret_e = APPACT_SetActValue(axeCfg_ps->actIfMtrPulse_e, 0.0f);
                if(Ret_e == RC_OK)
                {
                    axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XR];
                    Ret_e = APPACT_SetActValue(axeCfg_ps->actIfMtrPulse_e, 0.0f);
                }
            break;
            case GTRY_PHYS_AXE_Y:
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Y];
                Ret_e = APPACT_SetActValue(axeCfg_ps->actIfMtrPulse_e, 0.0f);
            break;
            case GTRY_PHYS_AXE_Z:
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Z];
                Ret_e = APPACT_SetActValue(axeCfg_ps->actIfMtrPulse_e, 0.0f);
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
    t_sGTRY_AxeAppCfg * axeCfg_ps;
    t_uint16 pulsePerMm_u16 = 0;
    t_uint16 minMtrFreq_u16 = 0;
    t_uint16 axeLenghtMm_u16 = 0;
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
                minSpeedID_e = APPSPM_PRM_LGC_GTRY_AXE_X_MIN_SPEED;
                axeLenghtID_e = APPSPM_PRM_LGC_GTRY_AXE_X_LEN;
            break;
            case GTRY_PHYS_AXE_Y:
                pulseFactor_s32 = GTRY_CALIB_DIR_AXE_Y;
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Y];
                pulseperMmID_e = APPSPM_PRM_LGC_GTRY_AXE_Y_PULSE_PER_MM;
                minSpeedID_e = APPSPM_PRM_LGC_GTRY_AXE_Y_MIN_SPEED;
                axeLenghtID_e = APPSPM_PRM_LGC_GTRY_AXE_Y_LEN;
            break;
            case GTRY_PHYS_AXE_Z:
                pulseFactor_s32 = GTRY_CALIB_DIR_AXE_Z;
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_Z];
                pulseperMmID_e = APPSPM_PRM_LGC_GTRY_AXE_Z_PULSE_PER_MM;
                minSpeedID_e = APPSPM_PRM_LGC_GTRY_AXE_Z_MIN_SPEED;
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
            Ret_e = APPSPM_GetParam(pulsePerMm_u16, &pulsePerMm_u16);
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSPM_GetParam(axeLenghtID_e, &axeLenghtMm_u16);
            }
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSPM_GetParam(minSpeedID_e, &minMtrFreq_u16);
            }
        }
        //---- 3- Compute and send the motor pulse to get to the reference point ----//
        if(Ret_e == RC_OK)
        {
            pulseToSend_s32 = (t_sint32)(pulsePerMm_u16 * axeLenghtMm_u16);
            pulseToSend_s32 *= pulseFactor_s32;

            Ret_e = APPACT_SetActValue(axeCfg_ps->actIfMtrPulse_e, pulseToSend_s32);
            if(Ret_e == RC_OK)
            {
                Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, (t_float32)minMtrFreq_u16);
            }

            //---- for axe X get the XR also ----//
            if(f_PhysAxe_e == GTRY_PHYS_AXE_X)
            {
                axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XR];
                Ret_e = APPACT_SetActValue(axeCfg_ps->actIfMtrPulse_e, pulseToSend_s32);
                if(Ret_e == RC_OK)
                {
                    Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, (t_float32)minMtrFreq_u16);
                }
            }
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
    t_sGTRY_AxeAppCfg * axeCfg_ps;
    t_float32 actMtrStsVal_f32 = 0.0f;
    t_float32 actMtrXRStsVal_f32 = 0.0f;

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
                        if((actMtrStsVal_f32 != APPACT_MOTOR_OFF)
                        && (actMtrXRStsVal_f32 != APPACT_MOTOR_OFF))
                        {
                            Ret_e = RC_WARNING_PENDING;
                        }
                        // else Ret_e alredy RC_OK
                    }
                }
                else 
                {
                    if(actMtrStsVal_f32 == APPACT_MOTOR_ON)
                    {
                        Ret_e = RC_WARNING_PENDING;
                    }
                    // else Ret_e alredy RC_OK
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
                g_Fsm_PrdTsk_OpeCmdPrcssSts_e = GTRY_FSM_PRDTSK_OPE_CMDPRCSS_CMPTE_ITER;
                g_Fsm_PrdTsk_OpeSts_e = GTRY_FSM_PRDTSK_OPE_CMD_PROCESS;
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
    t_uint16 axeXLenght_u16 = 0;
    t_uint16 axeYLenght_u16 = 0;
    t_uint16 axeZLenght_u16 = 0;

    //---- Get the parameter to know if the cmd is not out of range ----//
    Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_AXE_X_LEN,
                            &axeXLenght_u16);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_AXE_Y_LEN,
                                &axeYLenght_u16);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_AXE_Z_LEN,
                                &axeZLenght_u16);
    }
    if(Ret_e == RC_OK)
    {
        //---- Get a fifo cmd pos ----//
        Ret_e = LIBQUEUE_PopElement(&g_QueueCmdPosRcvMngmt_s,
                                    posCmdBuffer_af32,
                                    GTRTY_SIZEOF_ELEM_POSCMD_QUEUE);
    }
    if(Ret_e == RC_OK)
    {
        if(posCmdBuffer_af32[GTRY_PHYS_AXE_X] > axeXLenght_u16)
        {
            ASSERT((t_uint16)posCmdBuffer_af32[GTRY_PHYS_AXE_X]);
            isCmdValid_b = FALSE;
        }
        else if(posCmdBuffer_af32[GTRY_PHYS_AXE_Y] > axeYLenght_u16)
        {
            ASSERT((t_uint16)posCmdBuffer_af32[GTRY_PHYS_AXE_Y]);
            isCmdValid_b = FALSE;
        }
        else if(posCmdBuffer_af32[GTRY_PHYS_AXE_Z] > axeZLenght_u16)
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

    return Ret_e;
}


/*********************************
 * s_GTRY_Fsm_PrdTskOpe_CmdProcess
 *********************************/
static t_eReturnCode s_GTRY_Fsm_PrdTskOpe_CmdProcess(void)
{
    t_eReturnCode Ret_e;
    t_sGTRY_MtrCmdIterPayload cmdIter_s = {
        .frequency_f32 = 0.0f,
        .pulses_s32 = 0
    };
    t_uint8 idxSendCmd_u8;
    static t_eGTRY_PhysicalAxe currPhysAxe_e = GTRY_PHYS_AXE_NB;

    switch(g_Fsm_PrdTsk_OpeCmdPrcssSts_e)
    {
        case GTRY_FSM_PRDTSK_OPE_CMDPRCSS_CMPTE_ITER:
            Ret_e = s_GTRY_Fsm_PrdTskOpeCmdPrcss_ComputeIter();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdTsk_OpeCmdPrcssSts_e = GTRY_FSM_PRDTSK_OPE_CMDPRCSS_SEND_ITERS;
            }
        break;
        case GTRY_FSM_PRDTSK_OPE_CMDPRCSS_SEND_ITERS:
            Ret_e = s_GTRY_Fsm_PrdTskOpeCmdPrcss_SendIter();
            if(Ret_e == RC_OK)
            {
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
    }
    Ret_e = LIBQUEUE_PopElement(&g_QueueCmdPosRcvMngmt_s,
                                        posCmdBuffer_af32,
                                        GTRTY_SIZEOF_ELEM_POSCMD_QUEUE);
    if(Ret_e == RC_OK)
    {
        Ret_e = s_GTRY_IterationAlgorithm(posCmdBuffer_af32);

        if((Ret_e == RC_OK)
        && (g_FlagIterCmdReady_b == FALSE))
        {
            g_FlagIterCmdReady_b = TRUE;
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
    t_uint16 sendItertType_u16 = 0;
    t_uint8 mskAxeNoCmdLeft_u8 = (t_uint8)0;

    Ret_e = APPSPM_GetParam(APPSPM_PRM_LGC_GTRY_SENDITER_TYPE, &sendItertType_u16);
    if((Ret_e != RC_OK)
    || (sendItertType_u16 > (t_uint16)GTRY_SEN_ITER_NB))
    {
        ASSERT((t_uint16)Ret_e);
        sendItertType_u16 = GTRY_SEND_ITER_ASYNC;
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
            currPhysAxe_e < GTRY_PHYS_AXE_NB ; 
            currPhysAxe_e++)
        {
            Ret_e = LIBQUEUE_PopElement(&g_QueueCmdIterMngmt_as[currPhysAxe_e],
                                        &cmdIter_s,
                                        GTRTY_SIZEOF_ELEM_ITERCMD_QUEUE);
            if(Ret_e == RC_OK)
            {
                Ret_e = s_GTRY_SendMtrIteration(currPhysAxe_e, &cmdIter_s);
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
                    if(sendItertType_u16 == GTRY_SEND_ITER_BLOCKING)
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
 * s_GTRY_SendMtrIterations
 *********************************/
static t_eReturnCode s_GTRY_SendMtrIteration(t_eGTRY_PhysicalAxe f_physAxeID_e, t_sGTRY_MtrCmdIterPayload * f_MtrCmdIter_ps)
{
    t_eReturnCode Ret_e;
    t_sGTRY_AxeAppCfg * axeCfg_ps;
    t_eAPPLGC_SrvHealth axeHealth_e;

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
    else
    {
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
                        axeCfg_ps = &c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_XR];
                        Ret_e = APPACT_SetActValue(axeCfg_ps->actIfMtrPulse_e, f_MtrCmdIter_ps->pulses_s32);
                        if(Ret_e == RC_OK)
                        {
                            Ret_e = APPACT_SetActValue(axeCfg_ps->actIfSpeed_e, f_MtrCmdIter_ps->frequency_f32);
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
        if(g_Fsm_PrdcskSts_e == GTRY_FSM_PRD_TSK_OPS)
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
                    Ret_e = RC_WARNING_NO_OPERATION;
                    ASSERT((t_uint16)f_signal_e);
            }
        }
        if(Ret_e == RC_OK)
        {
            g_CmdSigInfo_as[currCmdSig_e].value_f32 = f_sigVal_f32;
            g_CmdSigInfo_as[currCmdSig_e].isRcv_b = TRUE;
            g_CmdSigInfo_as[currCmdSig_e].timeStamp_u32 = currentTime_u32;
            S_GTRY_CheckAndBuilCommand(cmdIdType_e, currentTime_u32);
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
    t_sGTRY_SigGroupInfo * grpInfo_ps;
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

