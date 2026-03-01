/*********************************************************************
 * @file        MOTION.c
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
#include "./MOTION.h"
#include "APP_CFG/ConfigFiles/MOTION_ConfigPrivate.h"

#include "Library/QUEUE/Src/LIBQueue.h"
#include "Library/SafeMem/SafeMem.h"
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
    MOT_FSM_PRD_TSK_CFG = 0,           //---- Fsm for configuration ----//
    MOT_FSM_PRD_TSK_PRE_OPS,           //---- Fsm for pre operational ----//
    MOT_FSM_PRD_TSK_OPS,               //---- Fsm for operational ----//
    MOT_FSM_PRD_TSK_CALIB_AXE,         //---- Fsm for calibration ----//
    MOT_FSM_PRD_TSK_SAFETY,            //---- Fsm for safety ----//
    MOT_FSM_PRD_TSK_ERROR,             //---- Fsm for error ----//
} t_eMOT_FsmPeriodicTask;

///@brief Finite State Machine for Periodic Task Sub State Calibration
typedef enum 
{
    MOT_FSM_PRDTSK_CALIB_INIT = 0,       //--- Fsm for Calibration initialization -----//
    MOT_FSM_PRDTSK_CALIB_KNIFE,          //--- Fsm for Calibration head knife -----//
    MOT_FSM_PRDTSK_CALIB_CNTR_KNIFE,     //--- Fsm for Calibration head coutner knife -----//
    MOT_FSM_PRDTSK_CALIB_HOLD_KNIFE,     //--- Fsm for Calibration head hold knife -----//
} t_eMOT_FsmPrdTsk_Calib;

typedef enum 
{
    MOT_FSM_PRDTSK_CALIB_OPE_STOP_AXE = 0,     //----Fsm for calibration, sub state axe xxx -> stop axe ----//
    MOT_FSM_PRDTSK_CALIB_OPE_MOVE_AXE,         //----Fsm for calibration, sub state axe xxx -> move axe ----//
    MOT_FSM_PRDTSK_CALIB_OPE_WAIT_AXE,         //----Fsm for calibration, sub state axe xxx -> wait axe ----//
    MOT_FSM_PRDTSK_CALIB_OPE_OFFSET_AXE,       //----Fsm for calibration, sub state axe xxx -> wait axe ----//
} t_eMOT_FsmPrdTsk_CalibOpe;

///@brief Finite State Machine for Periodic Task Sub State Operational
typedef enum 
{
    MOT_FSM_PRDTSK_OPE_SERVO =  0,      //---- Fsm for Operational state, subState Idle ----//
    MOT_FSM_PRDTSK_OPE_CMD_CHECK,      //---- Fsm for Operational state, subState check command ----//
    MOT_FSM_PRDTSK_OPE_CMD_PROCESS,    //---- Fsm for Operational state, subState process command ----//
} t_eMOT_FsmPrdTsk_Ope;
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
typedef struct 
{
    t_float32 dirSetPoint_mrad;                  //---- direction setpoint in milliradian ----//
    t_float32 speed_rpm;                          //---- direction speed in rpm ----//
    t_bool isReqCmd_b;                           //---- flag cmd received ----//
} t_sMOT_MtrDirCmdPayload;

typedef struct 
{
    t_eMOT_PropMode mode_e;                     //---- control propulsion mode ----//
    t_float32 propSetPoint_f32;                 //---- propulsion setpoint in torque or milliradian/sec ----//
    t_bool isReqCmd_b;                          //---- flag cmd received ----//
} t_sMOT_MtrPropCmdPayload;
///@brief calibration information
typedef struct 
{
    t_eAPPSNS_SnsInterface snsItf_e;            //---- calibration ongoing ----//
    t_float32 pulses_f32;                       //---- requested pulse for calibration ----//
    t_float32 speed_f32;                        //---- requested speed for calibration ----//
    t_eAPPLGC_CalibStatus reqSts_e;             //---- calibration requested from application ----//
    t_eAPPLGC_CalibStatus currSts_e;            //---- calibration requested from application ----//
    t_bool isNewCmdReceiv_b;
} t_sMOT_CalibCmdInfo;

///@brief Rearmament info 
typedef struct 
{
    t_eAPPLGC_RearmType rearmType_e;          //---- rearmament type ----//
    t_bool reqRearm_b;                      //--- rearmament is requested ----//
} t_sMOT_RearmInfo;
// ********************************************************************
// *                      Prototypes
// ********************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************
/// @brief Pulses which are missed by the motor axes
static t_float32 g_axeMissPulses_af32[MOT_ACTDIR_NB];

///@brief command buffer 
static t_sMOT_MtrDirCmdPayload g_MtrDirPayload_as[MOT_ACTDIR_NB];
static t_sMOT_MtrPropCmdPayload g_MtrPropPayload_as[MOT_ACTPROP_NB];

///@brief Finite State Machine Variables
static t_eMOT_FsmPeriodicTask g_Fsm_PrdcTskSts_e;
static t_eMOT_FsmPrdTsk_Calib g_Fsm_PrdTsk_CalibSts_e;
static  t_eMOT_FsmPrdTsk_Ope g_Fsm_PrdTsk_OpeSts_e;

///@brief Flag cmd received
static t_bool g_FlagDirCmdPending_b = FALSE;
static t_bool g_FlagPropCmdPending_b = FALSE;

static t_sMOT_CalibCmdInfo g_calibCmdInfo_s;

///@brief Information for rearmament 
static t_sMOT_RearmInfo g_RearmInfo_s; 
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
static t_eReturnCode s_MOT_StateMachine(void);
/**
 * @brief Function called every cyclic to check motor.
 * @details This function check if msg timeout occurs for one of the cmd
 *          check current in Propulsion motor 
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_MOT_SafetyUpdate(void);
/**
 * @brief This function handle the configuration state of State Machine
 * @details Not much happen for now in this function
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_MOT_Fsm_PrdTsk_Configuration(void);
/**
 * @brief This function handle the calibration state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_MOT_Fsm_PrdTsk_Calibration(void);
/**
 * @brief This function handle the Operation state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_MOT_Fsm_PrdTsk_PreOperational(void);
/**
 * @brief This function handle the Operation state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_MOT_Fsm_PrdTsk_Operational(void);
/**
 * @brief Handle Direction command in operational mode
 * @details Consume command received in callback and apply a simple
 *          closed-loop correction from encoder position.
 *
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_MOT_PrdTsk_Ope_DirectionMngmt(void);
/**
 * @brief Handle propulsion command in operational mode
 * @details For now this only consumes commands and checks sys options.
 *          Actuator/encoder implementation is pending.
 *
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_MOT_PrdTsk_Ope_PropulsionMngmt(void);
/**
 * @brief This function handle the Safety state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_MOT_Fsm_PrdTsk_Safety(void);
/**
 * @brief This function handle the Error state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_MOT_Fsm_PrdTsk_Error(void);
/**
 * @brief This function handle the reception of signals from APPSIG
 * ----------------------------------------------------------------------------
 * @param[in] f_signal_e : signal ID
 * @param[in] f_sigVal_f32 :signl; value
 * ----------------------------------------------------------------------------
 * @return void
 */
static void s_MOT_MsgReceptionCallback(  t_uint16 f_msgID_u16,
                                        t_uint8 f_nbSignal_u8,
                                        t_eAPPSIG_Signal *f_signal_ae, 
                                        t_float32 *f_sigValue_af32);
/**
 * @brief Hard Stop for all Axes Motor
 * @details This function Set an hard stop, means pin enable se to 1
 *             to release torque on each axes, this function also check if action 
 *              has to be made before hard stop motor
 * 
 * ----------------------------------------------------------------------------
 * @param[in] f_idxMtrDir_e : axe to get informatio on
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_MOT_MtrDirStop(t_eMOT_ActDirectionList f_idxMtrDir_e, t_bool f_isHardStop_b);
/**
 * @brief Enable the motor axes
 * 
 * ----------------------------------------------------------------------------
 * @param[in] f_idxMtrDir_e : axe to get informatio on
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_MOT_EnableMtrDir(t_eMOT_ActDirectionList f_idxMtrDir_e);
/**
 * @brief Send to the CL42T driver a command
 * 
 * ----------------------------------------------------------------------------
 * @param[in] f_idxMtrDir_e : axe to set new position
 * @param[in] f_setPoint_s32 : set point to reach (pulses)
 * @param[in] f_speed_f32 : speed of the setpoint (frequency)
 * @param[in] f_trigTiming_u32 : motor get the capabilities to store the command and set it in f_trigTiming_u32 ms
 * ----------------------------------------------------------------------------
 * @return RC_OK  : command set
 * @return RC_WARNING_BUSY  : Health of the axe is not correct 
 * @return others : @ref t_eReturnCode
 */
static t_eReturnCode s_MOT_SetMtrDirSetPoint(  t_eMOT_ActDirectionList f_idxMtrDir_e, 
                                            t_sint32 f_setPoint_s32,
                                            t_float32 f_speed_f32, 
                                            t_float32 f_trigTiming_u32);
/**
 * @brief Update Signal for debugging process
 * 
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static void s_MOT_DebugRoutine();

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * MOTION_Init
 *********************************/
t_eReturnCode MOTION_Init(void)
{
    t_eReturnCode Ret_e;
    t_eMOT_CmdSignals idxHcSig_e;
    t_uint8 idxActDir_u8;
    t_uint8 idxActProp_u8;

    Ret_e = RC_OK;

    for(idxHcSig_e = MOT_CMD_MSGSIG_HEAD ; idxHcSig_e < MOT_CDM_MSGSIG_NB ; idxHcSig_e++)
    {
        Ret_e = APPSIG_AddRcvMsgCallback(   c_MOT_MsgMapping_ae[idxHcSig_e], 
                                            APPSIG_MSG_ORIGIN_CAN,
                                            s_MOT_MsgReceptionCallback);
    }
    for(idxActDir_u8 = 0U ; idxActDir_u8 < MOT_ACTDIR_NB ; idxActDir_u8++)
    {
        g_MtrDirPayload_as[idxActDir_u8].dirSetPoint_mrad = 0.0F;
        g_MtrDirPayload_as[idxActDir_u8].speed_rpm = 0.0F;
        g_MtrDirPayload_as[idxActDir_u8].isReqCmd_b = FALSE;
    }
    for(idxActProp_u8 = 0U ; idxActProp_u8 < MOT_ACTPROP_NB ; idxActProp_u8++)
    {
        g_MtrPropPayload_as[idxActProp_u8].mode_e = MOT_PROPMODE_NB;
        g_MtrPropPayload_as[idxActProp_u8].propSetPoint_f32 = 0.0F;
        g_MtrPropPayload_as[idxActProp_u8].isReqCmd_b = FALSE;
    }
    if(Ret_e == RC_OK)
    {
        g_calibCmdInfo_s.pulses_f32 = 0.0F;
        g_calibCmdInfo_s.speed_f32 = 0.0F;
        g_calibCmdInfo_s.snsItf_e = APPSNS_SNSITF_NB;
        g_calibCmdInfo_s.reqSts_e = APPLGC_CALIB_REQSTS_IDLE;
        g_calibCmdInfo_s.currSts_e = APPLGC_CALIB_REQSTS_IDLE;
    }
    if(Ret_e == RC_OK)
    {
        g_RearmInfo_s.rearmType_e = LGC_REARM_TYPE_NB;
        g_RearmInfo_s.reqRearm_b = FALSE;

        g_Fsm_PrdcTskSts_e = MOT_FSM_PRD_TSK_CFG;
        g_Fsm_PrdTsk_CalibSts_e = MOT_FSM_PRDTSK_CALIB_INIT;
        g_Fsm_PrdTsk_OpeSts_e = MOT_FSM_PRDTSK_OPE_SERVO;
    }

    return Ret_e;
}

/*********************************
 * MOTION_PeriodicTask
 *********************************/
t_eReturnCode MOTION_PeriodicTask(void)
{   
    t_eReturnCode Ret_e;
    
    //---- 1- Call Safety Update ----//
    Ret_e = s_MOT_SafetyUpdate();

    //---- 2- Call State Machine ----//
    if(Ret_e == RC_OK)
    {
        Ret_e = s_MOT_StateMachine();
    }

    //---- 4- Debug Routine ----//
    s_MOT_DebugRoutine();

    return Ret_e;
}

// ********************************************************************
// *                      Local Functions - Implementation
// ********************************************************************
/*********************************
 * s_MOT_StateMachine
 *********************************/
static t_eReturnCode s_MOT_StateMachine(void)
{
    t_eReturnCode Ret_e;

    switch(g_Fsm_PrdcTskSts_e)
    {
        case MOT_FSM_PRD_TSK_CFG:
            Ret_e = s_MOT_Fsm_PrdTsk_Configuration();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdcTskSts_e = MOT_FSM_PRD_TSK_PRE_OPS;
                g_Fsm_PrdTsk_CalibSts_e = MOT_FSM_PRDTSK_CALIB_INIT;
            }
            else if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcTskSts_e = MOT_FSM_PRD_TSK_ERROR;
            }
        break;
        case MOT_FSM_PRD_TSK_PRE_OPS:
            Ret_e = s_MOT_Fsm_PrdTsk_PreOperational();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdcTskSts_e = MOT_FSM_PRD_TSK_OPS;
            }
            else if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcTskSts_e = MOT_FSM_PRD_TSK_SAFETY;
            }
        break;
        case MOT_FSM_PRD_TSK_CALIB_AXE:
            Ret_e = s_MOT_Fsm_PrdTsk_Calibration();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdcTskSts_e = MOT_FSM_PRD_TSK_OPS;
                g_Fsm_PrdTsk_OpeSts_e = MOT_FSM_PRDTSK_OPE_SERVO;
            }
            else if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcTskSts_e = MOT_FSM_PRD_TSK_SAFETY;
            }
        break;
        case MOT_FSM_PRD_TSK_OPS:
            Ret_e = s_MOT_Fsm_PrdTsk_Operational();
             if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcTskSts_e = MOT_FSM_PRD_TSK_SAFETY;
            }
        break;
        case MOT_FSM_PRD_TSK_SAFETY:
            Ret_e = s_MOT_Fsm_PrdTsk_Safety();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdcTskSts_e = MOT_FSM_PRD_TSK_CFG;
            }
            else if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcTskSts_e = MOT_FSM_PRD_TSK_ERROR;
            }
        break;
        case MOT_FSM_PRD_TSK_ERROR:
            Ret_e = s_MOT_Fsm_PrdTsk_Error();
            //--- no way out ----//
        break;
        default:
            Ret_e = RC_ERROR_WRONG_STATE;
        break;
    }

    return Ret_e;
}

/*********************************
 * s_MOT_Fsm_PrdTsk_Configuration
 *********************************/
static t_eReturnCode s_MOT_Fsm_PrdTsk_Configuration(void)
{
    t_eReturnCode Ret_e;
    Ret_e = RC_OK;
    return Ret_e;
}

/*********************************
 * s_MOT_Fsm_PrdTsk_Calibration
 *********************************/
static t_eReturnCode s_MOT_Fsm_PrdTsk_Calibration(void)
{
    t_eReturnCode Ret_e;
    t_eAPPLGC_CalibFeedbackSts feedbackSts_e = APPLGC_CALIB_FBSTS_UNDEFINED_ERROR;
    // t_uint8 sysOptWhlPropARL_u8 = 0U;
    // t_uint8 sysOptWhlPropARR_u8 = 0U;
    t_eMOT_ActDirectionList idxActDir_e;

    if(g_calibCmdInfo_s.reqSts_e == APPLGC_CALIB_REQSTS_IDLE)
    {
        //---- nothing to do here ---//
        feedbackSts_e = APPLGC_CALIB_FBSTS_REGIST_VAL_FAILED;
        Ret_e = RC_OK; 
    }
    //---- for now only just the two calibration ----//
    else if((g_calibCmdInfo_s.snsItf_e != APPSNS_SNSITF_ECDR_WHL_AV_L_POS)
    &&     (g_calibCmdInfo_s.snsItf_e != APPSNS_SNSITF_ECDR_WHL_AV_R_POS))
    {
        feedbackSts_e = APPLGC_CALIB_FBSTS_UNDEFINED_ERROR;
        Ret_e = RC_OK; 
    }
    else 
    {
        //---- after propulsion add, redirect to calibration prop or calibration dir ----//
        switch(g_calibCmdInfo_s.currSts_e)
        {
            case APPLGC_CALIB_REQSTS_IDLE:
                //---- stop pulse on going----//
                Ret_e = s_MOT_MtrDirStop(MOT_ACTDIR_WHL_AV_L,FALSE);
                if(Ret_e == RC_OK)
                {
                    Ret_e = s_MOT_MtrDirStop(MOT_ACTDIR_WHL_AV_R,FALSE);
                }
                if(Ret_e == RC_OK)
                {
                    g_FlagDirCmdPending_b = FALSE;
                    g_calibCmdInfo_s.currSts_e = g_calibCmdInfo_s.reqSts_e;
                    feedbackSts_e = APPLGC_CALIB_FBSTS_ONGOING;
                }
                break;
            case APPLGC_CALIB_REQSTS_MOVE:
                if(g_calibCmdInfo_s.isNewCmdReceiv_b == TRUE)
                {
                    idxActDir_e = 
                    (g_calibCmdInfo_s.snsItf_e == APPSNS_SNSITF_ECDR_WHL_AV_L_POS) ? 
                      MOT_ACTDIR_WHL_AV_L 
                    : MOT_ACTDIR_WHL_AV_R;
                    Ret_e = s_MOT_SetMtrDirSetPoint(idxActDir_e,
                                                    g_calibCmdInfo_s.pulses_f32,
                                                    g_calibCmdInfo_s.speed_f32,
                                                    0.0F);
                    if(Ret_e == RC_OK)
                    {
                        feedbackSts_e = APPLGC_CALIB_FBSTS_ONGOING;
                        g_calibCmdInfo_s.pulses_f32 = 0.0F;
                        g_calibCmdInfo_s.isNewCmdReceiv_b = FALSE;
                        Ret_e = RC_WARNING_PENDING;
                    }
                    else
                    {
                        feedbackSts_e = APPLGC_CALIB_FBSTS_SET_VAL_FAILED;
                    }
                    if(g_calibCmdInfo_s.reqSts_e != g_calibCmdInfo_s.currSts_e)
                    {
                        g_calibCmdInfo_s.currSts_e = g_calibCmdInfo_s.reqSts_e;
                    }
                }
                else 
                {
                    Ret_e = RC_WARNING_PENDING;
                }
                break;
            case APPLGC_CALIB_REQSTS_REGISTER_VALUE:
            {
                idxActDir_e = 
                    (g_calibCmdInfo_s.snsItf_e == APPSNS_SNSITF_ECDR_WHL_AV_L_POS) ? 
                      MOT_ACTDIR_WHL_AV_L 
                    : MOT_ACTDIR_WHL_AV_R;

                t_eAPPSNS_SnsInterface snsItfID_e = c_MOT_AppWhlDirCfg_as[idxActDir_e].snsIfEcdrPos_e;
                t_float32 snsVal_f32;

                Ret_e = APPLGC_GetSnsValue(snsItfID_e, &snsVal_f32);
                if(Ret_e == RC_OK)
                {
                    Ret_e = APPSNSCAL_RegisterReference(snsItfID_e, 
                                                        snsVal_f32,
                                                        c_MOT_AppWhlDirCfg_as[idxActDir_e].caliValExpectedMrad_f32);
                    if(Ret_e == RC_OK)
                    {
                        feedbackSts_e = APPLGC_CALIB_FBSTS_REGIST_VAL_SUCCEED;
                    }
                    else 
                    {
                        ASSERT((t_uint16)Ret_e);
                        feedbackSts_e = APPLGC_CALIB_FBSTS_REGIST_VAL_FAILED;

                    }
                }

                //---- register value ----//
                g_calibCmdInfo_s.currSts_e = APPLGC_CALIB_REQSTS_IDLE;
                g_calibCmdInfo_s.reqSts_e = APPLGC_CALIB_REQSTS_IDLE;
                break;
            }
            case APPLGC_CALIB_STS_NB:
            default:
                feedbackSts_e = APPLGC_CALIB_FBSTS_UNDEFINED_ERROR;
                ASSERT((t_uint16)g_calibCmdInfo_s.currSts_e);
                Ret_e = RC_ERROR_WRONG_STATE;
            break;
        }
    }

    (void)APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_CMD_CALIB_CURR_FEEDBACK, feedbackSts_e);
    (void)APPSIG_ForceMsgSend(  APPSIG_MSG_ORIGIN_CAN,
                                (t_uint16)APPSIG_CAN_MSG_LGC_MOT_CMD_CALIBRATION);
    return Ret_e;
}

/*********************************
 * s_MOT_Fsm_PrdTsk_PreOperational
 *********************************/
static t_eReturnCode s_MOT_Fsm_PrdTsk_PreOperational(void)
{
    t_eReturnCode Ret_e;
    t_uint8 sysOptWhlDirAv_u8 = 0U;
    t_uint8 sysOptWhlDirAr_u8 = 0U;
    t_uint8 sysOptWhlPropAv_u8 = 0U;
    t_uint8 sysOptWhlPropAr_u8 = 0U;

    Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SYS_ROBOT_DIR_FORWARD, &sysOptWhlDirAv_u8);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SYS_ROBOT_DIR_BACKWARD, &sysOptWhlDirAr_u8);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SYS_ROBOT_PROP_FORWARD, &sysOptWhlPropAv_u8);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SYS_ROBOT_PROP_BACKWARD, &sysOptWhlPropAr_u8);
    }

    //----- direction enabled ----//
    if(Ret_e == RC_OK)
    {
        //---- forward wheel direction ----//
        if(sysOptWhlDirAv_u8 == APPSYS_OPT_SYS_ROBOT_DIR_FORWARD_ENABLE)
        {
            Ret_e = s_MOT_EnableMtrDir(MOT_ACTDIR_WHL_AV_L);
            if(Ret_e == RC_OK)
            {
                Ret_e = s_MOT_EnableMtrDir(MOT_ACTDIR_WHL_AV_R);
            }
        }

        //---- backward wheel direction ----//
    }
    //----- propulsion enabled ----//
    if(Ret_e == RC_OK)
    {
        //---- backward wheel propulsion ----//
        if(sysOptWhlPropAr_u8 == APPSYS_OPT_SYS_ROBOT_PROP_BACKWARD_ENABLE)
        {
            // wrong 
        }

        //---- forward wheel propulsion ----//
    }

    return Ret_e;
}

/*********************************
 * s_MOT_Fsm_PrdTsk_Operational
 *********************************/
static t_eReturnCode s_MOT_Fsm_PrdTsk_Operational(void)
{
    t_eReturnCode RetTaskDir_e;
    t_eReturnCode RetTaskProp_e;
    
    //---- direction management ----//
    RetTaskDir_e = s_MOT_PrdTsk_Ope_DirectionMngmt();
    if(RetTaskDir_e != RC_OK)
    {
        ASSERT((t_uint16)RetTaskDir_e);
    }
    //---- Propulsion management ----//
    RetTaskProp_e = s_MOT_PrdTsk_Ope_PropulsionMngmt();
    if(RetTaskProp_e != RC_OK)
    {
        ASSERT((t_uint16)RetTaskProp_e);
    }

    if(RetTaskDir_e != RC_OK)
    {
        return RetTaskDir_e;
    }

    return RetTaskProp_e;
}
/*********************************
 * s_MOT_PrdTsk_Ope_DirectionMngmt
 *********************************/
static t_eReturnCode s_MOT_PrdTsk_Ope_DirectionMngmt(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxActDir_u8;
    t_uint8 sysOptEcdrWhlAvL_u8 = 0U;
    t_uint8 sysOptEcdrWhlAvR_u8 = 0U;
    t_uAPPSPM_PrmValType prmWhlDirAvLPulseToRad_u;
    t_uAPPSPM_PrmValType prmWhlDirAvRPulseToRad_u;
    t_uAPPSPM_PrmValType prmWhlDirAvLRpmToHz_u;
    t_uAPPSPM_PrmValType prmWhlDirAvRRpmToHz_u;
    t_bool isAnyCmdPending_b = FALSE;
    t_float32 prmWhlDirPulseToRad_f32;
    t_float32 prmWhlDirRpmToHz_f32;

    Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SNS_ECDR_WHL_AV_L, &sysOptEcdrWhlAvL_u8);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SNS_ECDR_WHL_AV_R, &sysOptEcdrWhlAvR_u8);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_MOT_ACTDIR_WHAVL_PULSE_TO_RAD, &prmWhlDirAvLPulseToRad_u);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_MOT_ACTDIR_WHAVR_PULSE_TO_RAD, &prmWhlDirAvRPulseToRad_u);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_MOT_ACTDIR_WHAVL_RPM_TO_HZ, &prmWhlDirAvLRpmToHz_u);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_MOT_ACTDIR_WHAVR_RPM_TO_HZ, &prmWhlDirAvRRpmToHz_u);
    }

    for(idxActDir_u8 = 0U ; (idxActDir_u8 < MOT_ACTDIR_NB) && (Ret_e >= RC_OK) ; idxActDir_u8++)
    {
        t_bool ecdrAvailable_b;

        if(g_MtrDirPayload_as[idxActDir_u8].isReqCmd_b == FALSE)
        {
            continue;
        }

        if(idxActDir_u8 == (t_uint8)MOT_ACTDIR_WHL_AV_L)
        {
            ecdrAvailable_b = (sysOptEcdrWhlAvL_u8 > APPSYS_OPT_SNS_ECDR_WHL_AV_L_UNUSED);
            prmWhlDirPulseToRad_f32 = (t_float32)prmWhlDirAvLPulseToRad_u.prmVal_u16;
            prmWhlDirRpmToHz_f32 = (t_float32)prmWhlDirAvLRpmToHz_u.prmVal_f32;
        }
        else
        {
            ecdrAvailable_b = (sysOptEcdrWhlAvR_u8 > APPSYS_OPT_SNS_ECDR_WHL_AV_R_UNUSED);
            prmWhlDirPulseToRad_f32 = (t_float32)prmWhlDirAvRPulseToRad_u.prmVal_u16;
            prmWhlDirRpmToHz_f32 = (t_float32)prmWhlDirAvRRpmToHz_u.prmVal_f32;
        }

        if(ecdrAvailable_b == TRUE)
        {
            t_float32 currPosMrad_f32 = 0.0F;
            t_float32 deltaPosMrad_f32 = 0.0F;
            t_sint32 corrPulse_s32;
            t_float32 speedHz_f32;

            Ret_e = APPLGC_GetSnsValue(c_MOT_AppWhlDirCfg_as[idxActDir_u8].snsIfEcdrPos_e,
                                       &currPosMrad_f32);
            if(Ret_e == RC_OK)
            {
                deltaPosMrad_f32 = g_MtrDirPayload_as[idxActDir_u8].dirSetPoint_mrad - currPosMrad_f32;
                corrPulse_s32 = (t_sint32)(deltaPosMrad_f32 * (t_float32)prmWhlDirPulseToRad_f32 / CST_2PI_MRAD);
                speedHz_f32 = g_MtrDirPayload_as[idxActDir_u8].speed_rpm * prmWhlDirRpmToHz_f32;

                Ret_e = s_MOT_SetMtrDirSetPoint((t_eMOT_ActDirectionList)idxActDir_u8,
                                                corrPulse_s32,
                                                speedHz_f32,
                                                0.0F);
                if(Ret_e == RC_OK)
                {
                    g_MtrDirPayload_as[idxActDir_u8].isReqCmd_b = FALSE;
                    g_axeMissPulses_af32[idxActDir_u8] = 0.0F;
                }
                else if(Ret_e == RC_WARNING_BUSY)
                {
                    Ret_e = RC_OK;
                }
            }
        }
        else
        {
            // TODO: no steering encoder configured, fallback strategy to be defined for closed-loop direction.
            ASSERT((t_uint16)idxActDir_u8);
            g_MtrDirPayload_as[idxActDir_u8].isReqCmd_b = FALSE;
        }

        if(g_MtrDirPayload_as[idxActDir_u8].isReqCmd_b == TRUE)
        {
            isAnyCmdPending_b = TRUE;
        }
    }

    g_FlagDirCmdPending_b = isAnyCmdPending_b;

    return Ret_e;
}

/*********************************
 * s_MOT_PrdTsk_Ope_PropulsionMngmt
 *********************************/
static t_eReturnCode s_MOT_PrdTsk_Ope_PropulsionMngmt(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 sysOptWhlPropAr_u8 = 0U;
    t_uint8 sysOptWhlPropAv_u8 = 0U;
    t_uint8 idxActProp_u8;
    t_bool isAnyCmdPending_b = FALSE;

    Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SYS_ROBOT_PROP_FORWARD, &sysOptWhlPropAv_u8);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SYS_ROBOT_PROP_BACKWARD, &sysOptWhlPropAr_u8);
    }

    if(sysOptWhlPropAr_u8 == APPSYS_OPT_SYS_ROBOT_DIR_BACKWARD_ENABLE)
    {
        //---- backward wheel propulsion ----//
    }
    if(sysOptWhlPropAv_u8 == APPSYS_OPT_SYS_ROBOT_DIR_FORWARD_ENABLE)
    {
        //---- forward wheel propulsion ----//
    }

    g_FlagPropCmdPending_b = isAnyCmdPending_b;
    return Ret_e;
}

/*********************************
 * s_MOT_Fsm_PrdTsk_Safety
 *********************************/
static t_eReturnCode s_MOT_Fsm_PrdTsk_Safety(void)
{
    t_eReturnCode Ret_e;
    t_uint8 sysOptWhlDirAv_u8 = 0U;
    t_uint8 sysOptWhlDirAr_u8 = 0U;
    t_uint8 sysOptWhlPropAv_u8 = 0U;
    t_uint8 sysOptWhlPropAr_u8 = 0U;

    Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SYS_ROBOT_DIR_FORWARD, &sysOptWhlDirAv_u8);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SYS_ROBOT_DIR_BACKWARD, &sysOptWhlDirAr_u8);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SYS_ROBOT_PROP_FORWARD, &sysOptWhlPropAv_u8);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SYS_ROBOT_PROP_BACKWARD, &sysOptWhlPropAr_u8);
    }
    if(Ret_e == RC_OK)
    {
        //---- forward wheel direction ----//
        if(sysOptWhlDirAv_u8 == APPSYS_OPT_SYS_ROBOT_DIR_FORWARD_ENABLE)
        {
            Ret_e = s_MOT_MtrDirStop(MOT_ACTDIR_WHL_AV_L, TRUE);
             if(Ret_e == RC_OK)
            {
                Ret_e = s_MOT_MtrDirStop(MOT_ACTDIR_WHL_AV_L, TRUE);
            }
        }

        //---- backward wheel direction ----//


        //---- backward wheel propulsion ----//
        if(sysOptWhlPropAr_u8 == APPSYS_OPT_SYS_ROBOT_PROP_BACKWARD_ENABLE)
        {
            // wrong 
        }

        //---- Forward wheel propulsion ----//
    }
    return Ret_e;
}

/*********************************
 * s_MOT_Fsm_PrdTsk_Error
 *********************************/
static t_eReturnCode s_MOT_Fsm_PrdTsk_Error(void)
{
    return RC_OK;
}


static t_eReturnCode s_MOT_SafetyUpdate(void)
{
    return RC_OK;
}

static void s_MOT_DebugRoutine()
{
    t_eReturnCode Ret_e;
    t_float32 whlAvLDir_f32 = 0.0F;
    t_float32 whlAvRDir_f32 = 0.0F;
    t_float32 whlArLProp_f32 = 0.0F;
    t_float32 whlArRProp_f32 = 0.0F;

    Ret_e = APPLGC_GetSnsValue(APPSNS_SNSITF_ECDR_WHL_AV_L_POS,
                                &whlAvLDir_f32);
    if(Ret_e == RC_OK)
    {
        APPLGC_GetSnsValue( APPSNS_SNSITF_ECDR_WHL_AV_R_POS, 
                            &whlAvRDir_f32);
    }
    // if(Ret_e == RC_OK)
    // {
    //     APPLGC_GetSnsValue( APPSNS_SNSITF_WHL_AV_L_PROP, 
    //                         &whlArLProp_f32);
    // }
    // if(Ret_e == RC_OK)
    // {
    //     APPLGC_GetSnsValue( APPSNS_SNSITF_WHL_AV_R_PROP, 
    //                         &whlArRProp_f32);
    // }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_SetSignalValue(  APPSIG_SIGNAL_LGC_MOT_FB_WHL_AVL_DIR_POS,
                                        whlAvLDir_f32);
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSIG_SetSignalValue(  APPSIG_SIGNAL_LGC_MOT_FB_WHL_AVR_DIR_POS,
                                            whlAvRDir_f32);
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSIG_SetSignalValue(  APPSIG_SIGNAL_LGC_MOT_FB_WHL_ARL_PROP,
                                            whlArLProp_f32);
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSIG_SetSignalValue(  APPSIG_SIGNAL_LGC_MOT_FB_WHL_ARR_PROP,
                                            whlArRProp_f32);
        }
    }
    if(Ret_e != RC_OK)
    {
        ASSERT((t_uint16)Ret_e);
    }
        
    return;
}
/*********************************
 * s_MOT_SetMtrDirSetPoint
 *********************************/
static t_eReturnCode s_MOT_SetMtrDirSetPoint( t_eMOT_ActDirectionList f_idxMtrDir_e, 
                                            t_sint32 f_setPoint_s32,
                                            t_float32 f_speed_f32, 
                                            t_float32 f_trigTiming_f32)
{
    t_eReturnCode Ret_e;
    const t_sMOT_DirMtrCfg * appMtrDirCfg_ps;
    t_eAPPLGC_SrvHealth mtrDirHeath_e;

    if(f_idxMtrDir_e >= MOT_ACTDIR_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)0);
    }
    else 
    {
        appMtrDirCfg_ps = &c_MOT_AppWhlDirCfg_as[f_idxMtrDir_e];
        Ret_e = APPLGC_GetServiceHealth(appMtrDirCfg_ps->lgcSrvID_e, &mtrDirHeath_e);
        if(Ret_e != RC_OK)
        {
            mtrDirHeath_e = APPLGC_SRV_HEALTH_ERROR;
        }
        if(mtrDirHeath_e == APPLGC_SRV_HEALTH_OK)
        {
            Ret_e = APPACT_SetActValue(appMtrDirCfg_ps->actifMtrSetPoint_e, (t_float32)f_setPoint_s32);
            if(Ret_e == RC_OK)
            {
                Ret_e = APPACT_SetActValue(appMtrDirCfg_ps->actIfSpeed_e, f_speed_f32);
            }
            if(Ret_e == RC_OK)
            {
                Ret_e = APPACT_SetActValue(appMtrDirCfg_ps->actIfTimTrig_e, f_trigTiming_f32);
            }
        }
        else 
        {
            Ret_e = RC_WARNING_BUSY;
        }
    }

    return Ret_e;
}

/*********************************
 * s_MOT_EnableMtrDir
 *********************************/
static t_eReturnCode s_MOT_EnableMtrDir(t_eMOT_ActDirectionList f_idxMtrDir_e)
{
    t_eReturnCode Ret_e;
    const t_sMOT_DirMtrCfg * appMtrDirCfg_ps;

    if(f_idxMtrDir_e >= MOT_ACTDIR_NB)
    {
        ASSERT((t_uint16)f_idxMtrDir_e);
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else 
    {
        appMtrDirCfg_ps = &c_MOT_AppWhlDirCfg_as[f_idxMtrDir_e];

        Ret_e = APPACT_SetActValue(appMtrDirCfg_ps->actIfSpeed_e, APPACT_ENABLE_MOTOR);
    }

    return Ret_e;
}

/*********************************
 * s_MOT_HardAxeStop
 *********************************/
static t_eReturnCode s_MOT_MtrDirStop(t_eMOT_ActDirectionList f_idxMtrDir_e, t_bool f_isHardStop_b)
{
    t_eReturnCode Ret_e;
    const t_sMOT_DirMtrCfg * appMtrDirCfg_ps;
    t_float32 stopID_f32 = 0.0F;

    if(f_idxMtrDir_e >= MOT_ACTDIR_NB)
    {
        ASSERT((t_uint16)f_idxMtrDir_e);
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else 
    {
        appMtrDirCfg_ps = &c_MOT_AppWhlDirCfg_as[f_idxMtrDir_e];

        if(f_isHardStop_b == TRUE)
        {
            stopID_f32 = APPACT_HARD_STOP;
        }
        else 
        {
            stopID_f32 = APPACT_SOFT_STOP;
        }

        Ret_e = APPACT_SetActValue(appMtrDirCfg_ps->actIfSpeed_e, stopID_f32);
    }

    return Ret_e;
}
/*********************************
 * s_MOT_SigReceptionCallback
 *********************************/
static void s_MOT_MsgReceptionCallback(  t_uint16 f_msgID_u16,
                                        t_uint8 f_nbSignal_u8,
                                        t_eAPPSIG_Signal *f_signal_ae, 
                                        t_float32 *f_sigValue_af32)
{
    t_eReturnCode Ret_e;

    if(f_msgID_u16 >= (t_uint16)APPSIG_CAN_MSG_NB)
    {
        ASSERT((t_uint16)f_msgID_u16);
    }
    else 
    {
        Ret_e = RC_OK;

        switch(f_msgID_u16)
        {
            case APPSIG_CAN_MSG_LGC_MOT_CMD_WHL_AV_POSITION:
            {// 0: AVL_POS, 1: AVR_POS, 2:AVL_POS_SPD, 3:AVR_POS_SPD
                if((f_nbSignal_u8 != (t_uint8)4)
                || (f_signal_ae[0] != APPSIG_SIGNAL_LGC_MOT_CMD_WHL_AVL_DIR)
                || (f_signal_ae[1] != APPSIG_SIGNAL_LGC_MOT_CMD_WHL_AVR_DIR)
                || (f_signal_ae[2] != APPSIG_SIGNAL_LGC_MOT_CMD_WHL_AVL_DIR_SPD)
                || (f_signal_ae[3] != APPSIG_SIGNAL_LGC_MOT_CMD_WHL_AVR_DIR_SPD))
                {
                    ASSERT((t_uint16)f_nbSignal_u8);
                }
                else 
                {
                    g_MtrDirPayload_as[MOT_ACTDIR_WHL_AV_L].dirSetPoint_mrad = 
                        f_sigValue_af32[0];
                    g_MtrDirPayload_as[MOT_ACTDIR_WHL_AV_R].dirSetPoint_mrad = 
                        f_sigValue_af32[1];
                    g_MtrDirPayload_as[MOT_ACTDIR_WHL_AV_L].speed_rpm = 
                        f_sigValue_af32[2];
                    g_MtrDirPayload_as[MOT_ACTDIR_WHL_AV_R].speed_rpm = 
                        f_sigValue_af32[3];

                    g_MtrDirPayload_as[MOT_ACTDIR_WHL_AV_L].isReqCmd_b = TRUE;
                    g_MtrDirPayload_as[MOT_ACTDIR_WHL_AV_R].isReqCmd_b = TRUE;
                    g_FlagDirCmdPending_b = TRUE;
                }
            }
            break;
            case APPSIG_CAN_MSG_LGC_MOT_CMD_WHL_AR_PROPULSION:
            {// 0: ARL_PROP, 1: ARR_PROP, 2:ARL_PROP_SPEED, 3:ARR_PROP_SPEED
                if((f_nbSignal_u8 != (t_uint8)4)
                || (f_signal_ae[0] != APPSIG_SIGNAL_LGC_MOT_CMD_WHL_ARL_PROP_MODE)
                || (f_signal_ae[1] != APPSIG_SIGNAL_LGC_MOT_CMD_WHL_ARR_PROP_MODE)
                || (f_signal_ae[2] != APPSIG_SIGNAL_LGC_MOT_CMD_WHL_ARL_PROP_SPD)
                || (f_signal_ae[3] != APPSIG_SIGNAL_LGC_MOT_CMD_WHL_ARR_PROP_SPD))
                {
                    ASSERT((t_uint16)f_nbSignal_u8);
                }
                else if((f_sigValue_af32[0] >= (t_float32)MOT_PROPMODE_NB)  
                ||      (f_sigValue_af32[1] >= (t_float32)MOT_PROPMODE_NB))
                {
                    ASSERT((t_uint16)0);
                }
                else 
                {
                    g_MtrPropPayload_as[MOT_ACTPROP_WHL_AR_L].mode_e = f_sigValue_af32[0];
                    g_MtrPropPayload_as[MOT_ACTPROP_WHL_AR_R].mode_e = f_sigValue_af32[1];

                    g_MtrPropPayload_as[MOT_ACTPROP_WHL_AR_L].propSetPoint_f32 = f_sigValue_af32[2];
                    g_MtrPropPayload_as[MOT_ACTPROP_WHL_AR_R].propSetPoint_f32 = f_sigValue_af32[3];

                    g_MtrPropPayload_as[MOT_ACTPROP_WHL_AR_L].isReqCmd_b = TRUE;
                    g_MtrPropPayload_as[MOT_ACTPROP_WHL_AR_R].isReqCmd_b = TRUE;
                    g_FlagPropCmdPending_b = TRUE;
                }

            }
            break;
            case APPSIG_CAN_MSG_LGC_MOT_CMD_CALIBRATION:
            {
                // 0 appsns_id, 1:req_state 2:pulse 3:speed
                t_eAPPSNS_SnsInterface sigSnsID_e;
                t_eAPPLGC_CalibStatus reqSts_e;
                t_float32 cmdPulses_f32;
                t_float32 cmdSpeed_f32;

                if((f_nbSignal_u8 != (t_uint8)4)
                || (f_signal_ae[0] != APPSIG_SIGNAL_LGC_CMD_CALIB_ID)
                || (f_signal_ae[1] != APPSIG_SIGNAL_LGC_CMD_CALIB_REQ_STATE)
                || (f_signal_ae[2] != APPSIG_SIGNAL_LGC_CMD_CALIB_PLS)
                || (f_signal_ae[3] != APPSIG_SIGNAL_LGC_CMD_CALIB_SPD))
                {
                    ASSERT((t_uint16)f_nbSignal_u8);
                }
                else
                {
                    sigSnsID_e = (t_eAPPSNS_SnsInterface)(f_sigValue_af32[0]);
                    reqSts_e = (t_eAPPLGC_CalibStatus)(f_sigValue_af32[1]);
                    cmdPulses_f32 = (f_sigValue_af32[2]);
                    cmdSpeed_f32 = (f_sigValue_af32[3]);
                    if(Ret_e == RC_OK)
                    {                        
                        //---- pulses are add if in the same sense 
                        //      pulses are reset to 0 is sens != from previous ----//
                        if(g_calibCmdInfo_s.pulses_f32 == (t_sint32)0)
                        {
                            g_calibCmdInfo_s.pulses_f32 = cmdPulses_f32;
                        }
                        else if(((g_calibCmdInfo_s.pulses_f32 > (t_sint32)0)
                            &&  (cmdPulses_f32 < (t_sint32)0))
                        ||       ((g_calibCmdInfo_s.pulses_f32 < (t_sint32)0)
                            &&  (cmdPulses_f32 > (t_sint32)0)))
                        {
                            g_calibCmdInfo_s.pulses_f32 = cmdPulses_f32;
                        }
                        else 
                        {
                            g_calibCmdInfo_s.pulses_f32 += cmdPulses_f32;
                        }

                        if(reqSts_e >= APPLGC_CALIB_STS_NB)
                        {
                            ASSERT((t_uint16)reqSts_e);
                        }
                        else 
                        {
                            g_calibCmdInfo_s.snsItf_e = sigSnsID_e;
                            g_calibCmdInfo_s.reqSts_e = reqSts_e;
                            g_calibCmdInfo_s.speed_f32 = cmdSpeed_f32;
                            g_calibCmdInfo_s.isNewCmdReceiv_b = TRUE;
                            
                        }  
                        if(Ret_e != RC_OK)
                        {
                            ASSERT((t_uint16)Ret_e);
                        }
                    }
                    else 
                    {
                        ASSERT((t_uint16)sigSnsID_e);
                    }
                }
            }
            break;
            case APPSIG_CAN_MSG_LGC_REARMAMENT_CMD:
            {
                // 0 : rearm agent ID, 1: rearm_type 2
                t_eAPPLGC_AgentList agent_e;
                t_eAPPLGC_RearmType rearmType_e;
                
                if((f_nbSignal_u8 != (t_uint8)2)
                || (f_signal_ae[0] != APPSIG_SIGNAL_LGC_CMD_REARMAMENT_AGID)
                || (f_signal_ae[1] != APPSIG_SIGNAL_LGC_CMD_REARMAMENT_TYPE))
                {
                    ASSERT((t_uint16)f_nbSignal_u8);
                }
                else
                {
                    agent_e = (t_eAPPLGC_AgentList)f_sigValue_af32[0];
                    rearmType_e = (t_eAPPLGC_RearmType)f_sigValue_af32[1];

                    if(agent_e != APPLGC_AGENT_MOTION)
                    {
                        //---- every ecu received but for debug, leave assertion ----//
                        ASSERT((t_uint16)agent_e);
                    }
                    else if(rearmType_e >= LGC_REARM_TYPE_NB)
                    {
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
        }
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

