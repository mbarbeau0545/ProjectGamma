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

///@brief Finite State Machine Variables
static t_eGTRY_FsmPeriodicTask g_Fsm_PrdcskSts_e;
static t_eGTRY_FsmPrdTsk_Calib g_Fsm_PrdTsk_CalibSts_e;
static t_eGTRY_FsmPrdTsk_CalibOpe g_Fsm_PrdTsk_CalibOpeSts_e;
static  t_eGTRY_FsmPrdTsk_Ope g_Fsm_PrdTsk_OpeSts_e;
static t_eGTRY_FsmPrdTsk_OpeCmdPrcss g_Fsm_PrdTsk_OpeCmdPrcssSts_e;

///@brief Command Queue Variables
static t_sLIBQUEUE_QueueCore g_QueueCmdPosRcvMngmt_s;
static t_sLIBQUEUE_QueueCore g_QueueCmdIterMngmt_s;
static t_float32 g_BufferCmdPosRcv_af32[GTRY_PHYS_AXE_NB][GTRY_CMD_POS_RCV_BUFFER_LEN];
static t_sGTRY_MtrCmdIterPayload g_BufferCmdMtrIter_as[GTRY_CMD_ITER_BUFFER_LEN];
/* CAUTION : Automatic generated code section for Variable: Start */
/* CAUTION : Automatic generated code section for Variable: End */
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
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
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_Ops(void);
/**
 * @brief This function handle the calibration Operationnal Movement 
 *          state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_OpsMove(void);
/**
 * @brief This function handle the calibration Operationnal Movement 
 *          state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_OpsStop(void);
/**
 * @brief This function handle the calibration Operationnal Movement 
 *          state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTskCalib_OpsWait(void);
/**
 * @brief This function handle the Operation state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_GTRY_Fsm_PrdTsk_Operational(void);
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
 * @brief Function called every cyclic to check motor.
 * @brief This function check if motors are in a logic state
 * ----------------------------------------------------------------------------
 * @param[in] f_value : value to compute
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************

// ********************************************************************
// *                      Local Functions - Implementation
// ********************************************************************

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

