/*********************************************************************
 * @file        HEAD_CUTTER.c
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
#include "./HEAD_CUTTER.h"
#include "APP_CFG/ConfigFiles/HEAD_CUTTER_ConfigPrivate.h"
#include "Library/QUEUE/Src/LIBQueue.h"
#include "Library/SafeMem/SafeMem.h"

#include <math.h>
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
    HC_FSM_PRD_TSK_CFG = 0,           //---- Fsm for configuration ----//
    HC_FSM_PRD_TSK_PRE_OPS,           //---- Fsm for pre operational ----//
    HC_FSM_PRD_TSK_OPS,               //---- Fsm for operational ----//
    HC_FSM_PRD_TSK_CALIB_AXE,         //---- Fsm for calibration ----//
    HC_FSM_PRD_TSK_SAFETY,            //---- Fsm for safety ----//
    HC_FSM_PRD_TSK_ERROR,             //---- Fsm for error ----//
} t_eHC_FsmPeriodicTask;

///@brief Finite State Machine for Periodic Task Sub State Calibration
typedef enum 
{
    HC_FSM_PRDTSK_CALIB_INIT = 0,       //--- Fsm for Calibration initialization -----//
    HC_FSM_PRDTSK_CALIB_KNIFE,          //--- Fsm for Calibration head knife -----//
    HC_FSM_PRDTSK_CALIB_CNTR_KNIFE,     //--- Fsm for Calibration head coutner knife -----//
    HC_FSM_PRDTSK_CALIB_HOLD_KNIFE,     //--- Fsm for Calibration head hold knife -----//
} t_eHC_FsmPrdTsk_Calib;

typedef enum 
{
    HC_FSM_PRDTSK_CALIB_OPE_STOP_AXE = 0,     //----Fsm for calibration, sub state axe xxx -> stop axe ----//
    HC_FSM_PRDTSK_CALIB_OPE_MOVE_AXE,         //----Fsm for calibration, sub state axe xxx -> move axe ----//
    HC_FSM_PRDTSK_CALIB_OPE_WAIT_AXE,         //----Fsm for calibration, sub state axe xxx -> wait axe ----//
} t_eHC_FsmPrdTsk_CalibOpe;

///@brief Finite State Machine for Periodic Task Sub State Operational
typedef enum 
{
    HC_FSM_PRDTSK_OPE_SERVO =  0,       //---- Fsm for Operational state, subState servo ----//
    HC_FSM_PRDTSK_OPE_CMD               //---- Fsm for Operational state, subState check command ----//
} t_eHC_FsmPrdTsk_Ope;
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
///@brief calib waiting information 
typedef struct 
{
    t_uint32 startWait_u32;         //---- store the Tick where we start to wait the axes to go to the setpoint ----//
    t_uint32 maxTimeWait_u32;       //---- Store the amount of time this is suspicious that the axe has not reach the set point yet ----//
} t_sHC_CalibWaitInfo;

///@brief angle joint 
typedef struct 
{
    t_float32 alpha_b_mrad;             //---- angle milliradian of joint b ----//
    t_float32 alpha_c_mrad;             //---- angle milliradian of joint c ----//
} t_sHC_JointAngle;

///@brief carthesian position 
typedef struct 
{
    t_float32 x_mm;                //---- position x of the axe
    t_float32 y_mm;                //---- position y of the axe

} t_sHC_CarthPos;

typedef union 
{
    t_sHC_CarthPos Carth_s;
    t_sHC_JointAngle Joint_s;
} t_uHC_CmdPos;


///@brief speed KNIFEs vallue
typedef struct 
{
    t_float32 knifeSpd_rpm;
    t_float32 cntrKnifeSpd_rpm;
} t_sHC_KnifeSpeed;
///@brief calibration information
typedef struct 
{
    t_eHC_AxeHandleList axeHead_e;              //---- calibration ongoing ----//
    t_float32 pulses_f32;                       //---- requested pulse for calibration ----//
    t_float32 speed_f32;                        //---- requested speed for calibration ----//
    t_eAPPLGC_CalibStatus reqSts_e;             //---- calibration requested from application ----//
    t_eAPPLGC_CalibStatus currSts_e;            //---- calibration requested from application ----//
    t_bool isNewCmdReceiv_b;
} t_sHC_CalibCmdInfo;

///@brief Rearmament info 
typedef struct 
{
    t_eAPPLGC_RearmType rearmType_e;            //---- rearmament type ----//
    t_bool reqRearm_b;                          //--- rearmament is requested ----//
} t_sHC_RearmInfo;

///@brief position command queue 
typedef struct
{
    t_uHC_CmdPos Pos_u;              //---- Carthesian position x,y -----//
    t_sHC_KnifeSpeed speed_s;
    t_uint32 timeStampID_u32;               //---- time received position or ID ----//
    t_eHC_CmdPosType cmdPosType_e;
} t_sHC_PosCmdQueueElem;

///@brief Position Information
typedef struct 
{
    t_sHC_CarthPos carthPos_s;
    t_sHC_JointAngle jointAng_s;
} t_sHC_PositionInfo;
// ********************************************************************
// *                      Prototypes
// ********************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************
///@brief the current position of the head
static t_sHC_PositionInfo g_KnifeTipCurr_s;
static t_sHC_PositionInfo g_KnifeHoldCurr_s;

///@brief the position compute or expected of the head
static t_sHC_PositionInfo g_KnifeTipCmpte_s;
static t_sHC_PositionInfo g_KnifeHoldCmpte_s;

/// @brief Pulses which are missed by the motor axes
static t_float32 g_axeMissPulses_af32[HC_AXE_HD_NB];

///@brief Finite State Machine Variables
static t_eHC_FsmPeriodicTask g_Fsm_PrdcTskSts_e;
static  t_eHC_FsmPrdTsk_Ope g_Fsm_PrdTsk_OpeSts_e;

///@brief Command Queue Variables
static t_sLIBQUEUE_QueueCore g_QueueCmdPosRcvMngmt_s;
static t_sLIBQUEUE_QueueCore g_QueueCmdIterRcvMngmt_as[HC_AXE_HD_NB];
static t_sHC_PosCmdQueueElem g_BufferCmdPosRcv_as[HC_CMD_POS_RCV_BUFFER_LEN];
static t_sHC_MtrCmdIterPayload g_BufferCmdMtrIter_as[HC_AXE_HD_NB][HC_CMD_ITER_BUFFER_LEN];

///@brief At least one Rcv Command is on the Queue
static t_bool g_FlagRcvPosCmd_b = FALSE;
///@brief At least one Iter Command is on the Queue
static t_bool g_FlagIterCmdReady_b = FALSE;
///@brief One Position cmd cannot be pushed inside PosQueue
static t_bool g_FlagPosCmdPending_b = FALSE;
///@brief Flag Motor Enable 
static t_bool g_FlagMotorEnable_b = FALSE;

///@brief Time Max to wait for the axe to go to the calibration point 
static t_sHC_CalibCmdInfo g_calibCmdInfo_s;

///@brief Information for rearmament 
static t_sHC_RearmInfo g_RearmInfo_s; 

///@brief current timestamp id apply 
static t_uint32 g_currCmdTimeStampID_u32 = 0U; 
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
static t_eReturnCode s_HC_StateMachine(void);
/**
 * @brief Function called every cyclic to check motor.
 * @details checl if there isn't Safety ECU that diagnostic something
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_HC_SafetyUpdate(void);
/**
 * @brief Update the current position of each axes
 * @details This function checck if encoder option are one,
 *          if there is for each axes, this function read the ecdr position
 *          compare it to the position compute 
 * 
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_HC_UpdatePosition(void);
/**
 * @brief This function handle the configuration state of State Machine
 * @details not much for now
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_HC_Fsm_PrdTsk_Configuration(void);
/**
 * @brief This function handle the calibration state of State Machine
 * @details If the motor are note enable we send calibration failed 
 *          Else we accept mission :
 *              -1 first, we ensure not position cmd are in queue, 
 *                  we stop the motor and, we clear the queue
 *              -2 secondly we set the motor pulse value in CALIB_STS_MOVE
 *              -3 we register value once the calib state is REGISTER_VALUE
 *          We always force send 
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_HC_Fsm_PrdTsk_Calibration(void);
/**
 * @brief This function handle the Operation state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_HC_Fsm_PrdTsk_PreOperational(void);
/**
 * @brief This function handle the Operation state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode 
 */
static t_eReturnCode s_HC_Fsm_PrdTsk_Operational(void);
/**
 * @brief This function handle the servo of knife & cntr knife
 * @brief using the delta between compute angle & current angle from encoder,
 *          we update the current position to the compute one.\n
 *        If the difference is too high, we set a diagnostic.\n
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode 
 */
static t_eReturnCode s_HC_Fsm_PrdTsk_Ope_Servo(void);
/**
 * @brief From the position command from application set the pulse cmd to each motor
 * @details 1- We read an element from PositionCommand Queue, which is the position in global
 *          referentiel A {x,y}, 
 *          2- from {x,y} we get the angle we have to apply on each joint to get to 
 *          that position.
 *          3- from current position, we calculate the delta between the actual position & the goal position
 *          4- Check that the position is possible etc
 *          5- We have the delta and we compute the equivalent number of pulse for each motor 
 *
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode 
 */
static t_eReturnCode s_HC_Fsm_PrdTsk_Ope_PosCmdMngmt(void);
/**
 * @brief Get the pulse for each motor from Queue and applied it to the motor
 * @details 1- Get the next pulses cmd from queue
 *          2- Set the value to motor, if not retry
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode 
 */
static t_eReturnCode s_HC_Fsm_PrdTsk_Ope_PulseCmdMngmt(void);
/**
 * @brief This function handle the Safety state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_HC_Fsm_PrdTsk_Safety(void);
/**
 * @brief This function handle the Error state of State Machine
 * ----------------------------------------------------------------------------
 * @return RC_OK : The state finish, pass to new state from fsm
 * @return RC_WARNNING_PENDING : The State is on going 
 * @return ohters : @ref t_eReturnCode
 */
static t_eReturnCode s_HC_Fsm_PrdTsk_Error(void);
static t_eReturnCode s_HC_ApplyRearmRequest(void);
/**
 * @brief This function handle the reception of signals from APPSIG
 * ----------------------------------------------------------------------------
 * @param[in] f_msgID_u16 : can msg id 
 * @param[in] f_nbSignal_u8 : numbe of signal inside msg
 * @param[in] f_signal_ae : signal ID's
 * @param[in] f_sigValue_af32 :signals value
 * ----------------------------------------------------------------------------
 * @return void
 */
static void s_HC_MsgReceptionCallback(  t_uint16 f_msgID_u16,
                                        t_uint8 f_nbSignal_u8,
                                        t_eAPPSIG_Signal *f_signal_ae, 
                                        t_float32 *f_sigValue_af32);
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
static t_eReturnCode s_HC_AxeStop(t_eHC_AxeHandleList f_idxAxe_e, t_bool f_isHardStop_b);
/**
 * @brief Enable the motor axes
 * 
 * ----------------------------------------------------------------------------
 * @param[in] f_idxAxe_e : axe to get informatio on
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_HC_EnableAxe(t_eHC_AxeHandleList f_idxAxe_e);
/**
 * @brief Send to the CL42T driver a command
 * 
 * ----------------------------------------------------------------------------
 * @param[in] f_idxAxe_e : axe to set new position
 * @param[in] f_setPoint_s32 : set point to reach (pulses)
 * @param[in] f_speedHz_f32 : speed of the setpoint (frequency)
 * @param[in] f_trigTiming_u32 : motor get the capabilities to store the command and set it in f_trigTiming_u32 ms
 * ----------------------------------------------------------------------------
 * @return RC_OK  : command set
 * @return RC_WARNING_BUSY  : Health of the axe is not correct 
 * @return others : @ref t_eReturnCode
 */
static t_eReturnCode s_HC_SetAxeSetPoint( t_eHC_AxeHandleList f_idxAxe_e, 
                                            t_sint32 f_setPoint_s32,
                                            t_float32 f_speedHz_f32, 
                                            t_float32 f_trigTiming_u32);
/**
 * @brief Update Signal for debugging process
 * 
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static void s_HC_DebugRoutine(void);
/**
 * @brief Compute the actual position {x,y} from angle alpha_b_mrad (angle between xa & xb see drawIO)
 *          and alpha_c_mrad (angle between xb & xc)
 * 
 * ----------------------------------------------------------------------------
 * @param[in] f_alphaB_mrad : Angle MilliRadian position of joint Cntr KNIFE and support head
 * @param[in] f_alphaC_mrad : Angle MilliRadian position of joint KNIFE & CntrKNIFE
 * @param[in] f_posX_mm : Position X in ref A in millimeter
 * @param[in] f_posY_mm : Position Y in ref A in millimeter
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_HC_ComputeCarthesianFromAngle(   t_float32 f_alphaB_mrad,
                                                        t_float32 f_alphaC_mrad,
                                                        t_float32 * f_posX_pmm,
                                                        t_float32 * f_posY_pmm);
static t_eReturnCode s_HC_ComputeAngleFromCarthesian(   t_float32 f_posX_mm,
                                                        t_float32 f_posY_mm,
                                                        t_float32 * f_alphaB_pmrad,
                                                        t_float32 * f_alphaC_pmrad);
/**
 * @brief Compute the pulse corresponding to angle alpha b & c 
 * 
 * ----------------------------------------------------------------------------
 * @param[in] f_alphaB_pmrad : Angle MilliRadian position of joint Cntr KNIFE and support head
 * @param[in] f_alphaC_pmrad : Angle MilliRadian position of joint KNIFE & CntrKNIFE
 * @param[in] f_pulseKnf_pf32 : Pulse for Knife Actuators
 * @param[in] f_pulseCntrKnf_pf32 : Pulse for counter knife actuator
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */                                                  
static t_eReturnCode s_HC_ComputePulseFromAngle(t_float32 f_alphaB_mrad,
                                                t_float32 f_alphaC_mrad,
                                                t_float32 * f_pulseKnf_pf32,
                                                t_float32 * f_pulseCntrKnf_pf32);
static t_eReturnCode s_HC_ComputeAnglefromPulse( t_sint32 f_pulseKnf_s32,
                                                t_sint32 f_pulseCntrKnf_s32,
                                                t_float32 * f_alphaB_pmrad,
                                                t_float32 * f_alphaC_pmrad);
/**
 * @brief Get the actual position for computation
 * @details Whenever there is position to calculate, we get the current position
 *          From encoder and add the position command no set yet to compute 
 *          Directly from the futur postion 
 * ----------------------------------------------------------------------------
 * @param[in] f_alphaB_pmrad : Angle MilliRadian position of joint Cntr KNIFE and support head
 * @param[in] f_alphaC_pmrad : Angle MilliRadian position of joint KNIFE & CntrKNIFE
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */   
static t_eReturnCode s_HC_GetQueuedTipAngles( t_float32 * f_alphaB_pmrad,
                                                t_float32 * f_alphaC_pmrad);
/**
 * @brief Get integer pulse and save float pulse, once > 1 set it 
 * ----------------------------------------------------------------------------
 * @param[in] f_idxAxe_e : idx axe of the knife
 * @param[in] f_pulseCmd_f32 : float command to set, that has been calculate
 * ----------------------------------------------------------------------------
 * @return @ref integer pulses
 */  
static t_sint32 s_HC_QuantizePulseCmd(t_eHC_AxeHandleList f_idxAxe_e, t_float32 f_pulseCmd_f32);
/**
 * @brief Merge or Write Iteration Pulse Command
 * @details  If the position are closed in mm or angle, in order to not have 
 *              1 pulse per command, this function set a minimum of puls per command
 * ----------------------------------------------------------------------------
 * @param[in] f_queue_ps : idx axe of the knife
 * @param[in] f_cmd_ps : float command to set, that has been calculate
 * ----------------------------------------------------------------------------
 * @return @ref integer pulses
 */
static t_eReturnCode s_HC_WriteOrMergeIterCmd(t_sLIBQUEUE_QueueCore * f_queue_ps,
                                              const t_sHC_MtrCmdIterPayload * f_cmd_ps);
/**
 * @brief Check Position with boundaries limit
 * 
 * ----------------------------------------------------------------------------
 * @param[in] f_carthPos_s : position to check
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
static t_eReturnCode s_HC_CheckPositionValidity(t_sHC_CarthPos f_carthPos_s);
static t_eReturnCode s_HC_CheckAngleAssociationValidity(t_float32 f_alphaB_mrad,
                                                        t_float32 f_alphaC_mrad);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * HEAD_CUTTER_Init
 *********************************/
t_eReturnCode HEAD_CUTTER_Init(void)
{
    t_eReturnCode Ret_e;
    t_eHC_AxeHandleList idxAxe_e;
    t_eHC_CmdSignals idxHcSig_e;
    t_sLIBQUEUE_QueueCfg cmdPosFifoCfg_s;
    t_sLIBQUEUE_QueueCfg cmdIterFifoCfg_s;

    Ret_e = RC_OK;
    for(idxAxe_e = HC_AXE_HEAD ; idxAxe_e < HC_AXE_HD_NB ; idxAxe_e++)
    {
        cmdIterFifoCfg_s.bufferHead_pv = &g_BufferCmdMtrIter_as[idxAxe_e];
        cmdIterFifoCfg_s.actualSize_u16 = HC_CMD_ITER_BUFFER_LEN;
        cmdIterFifoCfg_s.elementSize_u16 = sizeof(t_sHC_MtrCmdIterPayload);
        cmdIterFifoCfg_s.enableOverwrite_b = FALSE;
        Ret_e = LIBQUEUE_Create(&g_QueueCmdIterRcvMngmt_as[idxAxe_e], cmdIterFifoCfg_s);

        if(Ret_e == RC_OK)
        {
            g_axeMissPulses_af32[idxAxe_e] = 0.0f;
        }
    }
    if(Ret_e == RC_OK)
    {
        for(idxHcSig_e = HC_CMD_MSGSIG_HEAD ; idxHcSig_e < HC_CDM_MSGSIG_NB ; idxHcSig_e++)
        {
            Ret_e = APPSIG_AddRcvMsgCallback(   c_HC_MsgMapping_ae[idxHcSig_e], 
                                                APPSIG_MSG_ORIGIN_CAN,
                                                s_HC_MsgReceptionCallback);
        }
    }
    if(Ret_e == RC_OK)
    {
        cmdPosFifoCfg_s.bufferHead_pv = &g_BufferCmdPosRcv_as[0];
        cmdPosFifoCfg_s.actualSize_u16 = HC_CMD_POS_RCV_BUFFER_LEN;
        cmdPosFifoCfg_s.elementSize_u16 = sizeof(t_sHC_PosCmdQueueElem);
        cmdPosFifoCfg_s.enableOverwrite_b = FALSE;
        Ret_e = LIBQUEUE_Create(&g_QueueCmdPosRcvMngmt_s, cmdPosFifoCfg_s);

    }
    if(Ret_e == RC_OK)
    {
        g_calibCmdInfo_s.pulses_f32 = 0.0F;
        g_calibCmdInfo_s.speed_f32 = 0.0F;
        g_calibCmdInfo_s.axeHead_e = HC_AXE_HD_NB;
        g_calibCmdInfo_s.reqSts_e = APPLGC_CALIB_REQSTS_IDLE;
        g_calibCmdInfo_s.currSts_e = APPLGC_CALIB_REQSTS_IDLE;
        g_calibCmdInfo_s.isNewCmdReceiv_b = FALSE;
    }
    if(Ret_e == RC_OK)
    {
        g_KnifeTipCmpte_s.carthPos_s.x_mm = 0.0f;
        g_KnifeTipCmpte_s.carthPos_s.y_mm = 0.0f;
        g_KnifeTipCurr_s.jointAng_s.alpha_b_mrad = 0.0F;
        g_KnifeTipCurr_s.jointAng_s.alpha_c_mrad = 0.0F;

        g_KnifeHoldCurr_s.carthPos_s.x_mm = 0.0F;
        g_KnifeHoldCurr_s.carthPos_s.y_mm = 0.0F;
        g_KnifeHoldCurr_s.jointAng_s.alpha_b_mrad = 0.0F;
        g_KnifeHoldCurr_s.jointAng_s.alpha_c_mrad = 0.0F;

        g_RearmInfo_s.rearmType_e = LGC_REARM_TYPE_NB;
        g_RearmInfo_s.reqRearm_b = FALSE;

        g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_CFG;
        g_Fsm_PrdTsk_OpeSts_e = HC_FSM_PRDTSK_OPE_SERVO;
    }

    return Ret_e;
}

/*********************************
 * HEAD_CUTTER_PeriodicTask
 *********************************/
t_eReturnCode HEAD_CUTTER_PeriodicTask(void)
{
    t_eReturnCode Ret_e;
    
    //---- 1- Call Safety Update ----//
    Ret_e = s_HC_SafetyUpdate();

    //---- 2- Update Current position ----//
    if(Ret_e == RC_OK)
    {
        Ret_e = s_HC_UpdatePosition();
    }
    //---- 3- Call State Machine ----//
    if(Ret_e == RC_OK)
    {
        Ret_e = s_HC_StateMachine();
    }

    //---- 4- Debug Routine ----//
    s_HC_DebugRoutine();

    return Ret_e;
}

// ********************************************************************
// *                      Local Functions - Implementation
// ********************************************************************
/*********************************
 * s_HC_StateMachine
 *********************************/
static t_eReturnCode s_HC_StateMachine(void)
{
    t_eReturnCode Ret_e;

    switch(g_Fsm_PrdcTskSts_e)
    {
        case HC_FSM_PRD_TSK_CFG:
            Ret_e = s_HC_Fsm_PrdTsk_Configuration();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_PRE_OPS;
            }
            else if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_ERROR;
            }
        break;
        case HC_FSM_PRD_TSK_PRE_OPS:
            Ret_e = s_HC_Fsm_PrdTsk_PreOperational();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_OPS;
                g_Fsm_PrdTsk_OpeSts_e = HC_FSM_PRDTSK_OPE_SERVO;
            }
        break;
        case HC_FSM_PRD_TSK_OPS:
            Ret_e = s_HC_Fsm_PrdTsk_Operational();
             if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_SAFETY;
            }
        break;
        case HC_FSM_PRD_TSK_CALIB_AXE:
            Ret_e = s_HC_Fsm_PrdTsk_Calibration();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_OPS;
            }
            else if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_SAFETY;
            }
        break;
        case HC_FSM_PRD_TSK_SAFETY:
            Ret_e = s_HC_Fsm_PrdTsk_Safety();
            if(Ret_e == RC_OK)
            {
                g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_CFG;
            }
            else if(Ret_e < RC_OK)
            {
                g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_ERROR;
            }
        break;
        case HC_FSM_PRD_TSK_ERROR:
            Ret_e = s_HC_Fsm_PrdTsk_Error();
            //--- no way out ----//
        break;
        default:
            Ret_e = RC_ERROR_WRONG_STATE;
        break;
    }

    return Ret_e;
}

/*********************************
 * s_HC_Fsm_PrdTsk_Configuration
 *********************************/
static t_eReturnCode s_HC_Fsm_PrdTsk_Configuration(void)
{
    t_eReturnCode Ret_e;
    Ret_e = RC_OK;
    return Ret_e;
}

/*********************************
 * s_HC_Fsm_PrdTsk_Calibration
 *********************************/
static t_eReturnCode s_HC_Fsm_PrdTsk_Calibration(void)
{
    t_eReturnCode Ret_e;
    t_eHC_AxeHandleList idxAxe_e;
    t_uint8 sysOptHdHoldKnf_u8;
    t_eAPPLGC_CalibFeedbackSts feedbackSts_e = APPLGC_CALIB_FBSTS_UNDEFINED_ERROR;
    
    if(g_FlagMotorEnable_b == FALSE)
    {
        //---- calibration could not be done ----//
        feedbackSts_e = APPLGC_CALIB_FBSTS_MTR_DISABLE;
        Ret_e = RC_OK;
    }
    else if(g_calibCmdInfo_s.reqSts_e == APPLGC_CALIB_REQSTS_IDLE)
    {
        //---- nothing to do here ---//
        feedbackSts_e = APPLGC_CALIB_FBSTS_REGIST_VAL_FAILED;
        Ret_e = RC_OK; 
    }
    else 
    {
        Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_ACT_MTR_HD_HOLD, &sysOptHdHoldKnf_u8);
        if(Ret_e == RC_OK)
        {
            switch(g_calibCmdInfo_s.currSts_e)
            {
                case APPLGC_CALIB_REQSTS_IDLE:
                    //---- STOP pulse on going, clear queue ----//
                    Ret_e = s_HC_AxeStop(HC_AXE_HD_KNFE, FALSE);
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = s_HC_AxeStop(HC_AXE_HD_CNTR_KNFE, FALSE);
                    }
                    if((Ret_e == RC_OK)
                    && (sysOptHdHoldKnf_u8 == APPSYS_OPT_ACT_MTR_HD_HOLD_CL42T))
                    {
                        Ret_e = s_HC_AxeStop(HC_AXE_HD_HOLD_KNFE, FALSE);
                    }
                    if(Ret_e == RC_OK)
                    {
                        g_FlagPosCmdPending_b = FALSE;
                        g_FlagIterCmdReady_b = FALSE;

                        (void)LIBQUEUE_ClearAll(&g_QueueCmdIterRcvMngmt_as[HC_AXE_HD_KNFE]);
                        (void)LIBQUEUE_ClearAll(&g_QueueCmdIterRcvMngmt_as[HC_AXE_HD_CNTR_KNFE]);
                        (void)LIBQUEUE_ClearAll(&g_QueueCmdIterRcvMngmt_as[HC_AXE_HD_HOLD_KNFE]);
                        for(idxAxe_e = HC_AXE_HD_KNFE; idxAxe_e < HC_AXE_HD_NB; idxAxe_e++)
                        {
                            g_axeMissPulses_af32[idxAxe_e] = 0.0F;
                        }

                        g_calibCmdInfo_s.currSts_e = g_calibCmdInfo_s.reqSts_e;
                        feedbackSts_e = APPLGC_CALIB_FBSTS_ONGOING;
                        Ret_e = RC_WARNING_PENDING;
                    }
                    
                break;
                case APPLGC_CALIB_REQSTS_MOVE:
                {
                    t_sint32 pulsesCmd_s32;
                    //---- move ----//
                    if(g_calibCmdInfo_s.isNewCmdReceiv_b == TRUE)
                    {
                        pulsesCmd_s32 = s_HC_QuantizePulseCmd(g_calibCmdInfo_s.axeHead_e,
                                                              g_calibCmdInfo_s.pulses_f32);
                        Ret_e = s_HC_SetAxeSetPoint(g_calibCmdInfo_s.axeHead_e, 
                                                    pulsesCmd_s32,
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
                    }
                    if(g_calibCmdInfo_s.reqSts_e != g_calibCmdInfo_s.currSts_e)
                    {
                        g_calibCmdInfo_s.currSts_e = g_calibCmdInfo_s.reqSts_e;
                    }
                }
                break;
                case APPLGC_CALIB_REQSTS_REGISTER_VALUE:
                {
                    t_eAPPSNS_SnsInterface snsItfID_e = c_HC_AppAxesCfg_as[g_calibCmdInfo_s.axeHead_e].snsIfEcdrPos_e;
                    t_float32 snsVal_f32;
                    //---- get sns id value ----//
                    Ret_e = APPLGC_GetSnsValue(snsItfID_e, &snsVal_f32);
                    if(Ret_e == RC_OK)
                    {
                        Ret_e = APPSNSCAL_RegisterReference(snsItfID_e,
                                                            snsVal_f32,
                                                            c_HC_AppAxesCfg_as[g_calibCmdInfo_s.axeHead_e].caliValExpectedMrad_f32);
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
                }
                break;
                case APPLGC_CALIB_STS_NB:
                default:
                    feedbackSts_e = APPLGC_CALIB_FBSTS_UNDEFINED_ERROR;
                    ASSERT((t_uint16)g_calibCmdInfo_s.currSts_e);
                    Ret_e = RC_ERROR_WRONG_STATE;
                break;
            }
        }
    }

    (void)APPSIG_SetSignalValue(APPSIG_SIGNAL_LGC_CMD_CALIB_CURR_FEEDBACK, feedbackSts_e);
    (void)APPSIG_ForceMsgSend(  APPSIG_MSG_ORIGIN_CAN,
                                (t_uint16)APPSIG_CAN_MSG_LGC_HC_CMD_CALIBRATION);

    
    return Ret_e;
}

/*********************************
 * s_HC_Fsm_PrdTsk_PreOperational
 *********************************/
static t_eReturnCode s_HC_Fsm_PrdTsk_PreOperational(void)
{
    t_eReturnCode Ret_e;
    t_uint8 sysOptCntrKnv_u8 = 0;
    t_uint8 sysOptKnv_u8 = 0;
    t_uint8 sysOptHoldKnv_u8 = 0;

    Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_ACT_MTR_HD_KNF, &sysOptKnv_u8);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_ACT_MTR_HD_CNTR_KNF, &sysOptCntrKnv_u8);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_ACT_MTR_HD_HOLD, &sysOptHoldKnv_u8);
    }

    //---- Enable axe KNIFE ----//
    if(Ret_e == RC_OK)
    {
        if(sysOptKnv_u8 == APPSYS_OPT_ACT_MTR_HD_KNF_CL42T)
        {
            Ret_e = s_HC_EnableAxe(HC_AXE_HD_KNFE);
        }

        if(Ret_e == RC_OK)
        {
            if(sysOptCntrKnv_u8 == APPSYS_OPT_ACT_MTR_HD_CNTR_KNF_CL42T)
            {
                Ret_e = s_HC_EnableAxe(HC_AXE_HD_CNTR_KNFE);
            }
        }
        if(Ret_e == RC_OK)
        {
            if(sysOptHoldKnv_u8 == APPSYS_OPT_ACT_MTR_HD_HOLD_CL42T)
            {
                Ret_e = s_HC_EnableAxe(HC_AXE_HD_HOLD_KNFE);
            }
        }
        if(Ret_e == RC_OK)
        {
            g_FlagMotorEnable_b = TRUE;
        }
    }

    return Ret_e;
}

/*********************************
 * s_HC_Fsm_PrdTsk_Operational
 *********************************/
static t_eReturnCode s_HC_Fsm_PrdTsk_Operational(void)
{
    t_eReturnCode Ret_e;

    if(g_RearmInfo_s.reqRearm_b == TRUE)
    {
        g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_SAFETY;
        Ret_e = RC_OK;
    }
    //---- Check calibration needed for user ----//
    else if(g_calibCmdInfo_s.reqSts_e == APPLGC_CALIB_REQSTS_MOVE
    || g_calibCmdInfo_s.reqSts_e == APPLGC_CALIB_REQSTS_REGISTER_VALUE)
    {
        g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_CALIB_AXE;
        Ret_e = RC_OK;
    }
    else 
    {
        Ret_e = RC_OK;
        
        switch(g_Fsm_PrdTsk_OpeSts_e)
        {
            case HC_FSM_PRDTSK_OPE_SERVO:
            {
                Ret_e = s_HC_Fsm_PrdTsk_Ope_Servo();
                if( (Ret_e == RC_OK)
                &&  (g_FlagPosCmdPending_b == TRUE))
                {
                    g_Fsm_PrdTsk_OpeSts_e = HC_FSM_PRDTSK_OPE_CMD;
                    
                }
                // else stay here
            }
            break;
            case HC_FSM_PRDTSK_OPE_CMD:
            {
                //---- first build command from pos to pulse ----//
                Ret_e = s_HC_Fsm_PrdTsk_Ope_PosCmdMngmt();
                if(Ret_e == RC_WARNING_NO_OPERATION)
                {
                    Ret_e = RC_OK;
                    g_FlagPosCmdPending_b = FALSE;
                }
                else if(Ret_e < RC_OK)
                {
                    ASSERT((t_uint16)0);
                }
                if(Ret_e == RC_OK)
                {
                    //---- then execute pulse command ----//
                    Ret_e = s_HC_Fsm_PrdTsk_Ope_PulseCmdMngmt();
                    if(Ret_e == RC_WARNING_NO_OPERATION)
                    {
                        g_FlagIterCmdReady_b = FALSE;
                    }
                    else if(Ret_e < RC_OK)
                    {
                        ASSERT((t_uint16)0);
                    }

                    //---- check work left in this state ----//
                    if((g_FlagIterCmdReady_b == FALSE)
                    && (g_FlagPosCmdPending_b == FALSE))
                    {
                        g_Fsm_PrdTsk_OpeSts_e = HC_FSM_PRDTSK_OPE_SERVO;
                    }
                    else if((g_QueueCmdPosRcvMngmt_s.actualSize_u16 == (t_uint8)0)
                    && (g_QueueCmdIterRcvMngmt_as[HC_AXE_HD_KNFE].actualSize_u16 == (t_uint8)0)
                    && (g_QueueCmdIterRcvMngmt_as[HC_AXE_HD_CNTR_KNFE].actualSize_u16 == (t_uint8)0))
                    {
                        // If queues are empty, force idle/servo state to avoid being stuck in CMD state.
                        g_FlagPosCmdPending_b = FALSE;
                        g_FlagIterCmdReady_b = FALSE;
                        g_Fsm_PrdTsk_OpeSts_e = HC_FSM_PRDTSK_OPE_SERVO;
                    }
                }
            }
            break;
            default:
                ASSERT((t_uint16)g_Fsm_PrdTsk_OpeSts_e);
        }
    }

    return Ret_e;
}

/*********************************
 * s_HC_Fsm_PrdTsk_Safety
 *********************************/
static t_eReturnCode s_HC_Fsm_PrdTsk_Safety(void)
{
    t_eReturnCode Ret_e;
    t_uint8 sysOptCntrKnv_u8 = 0;
    t_uint8 sysOptKnv_u8 = 0;
    t_uint8 sysOptHoldKnv_u8 = 0;

    Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_ACT_MTR_HD_KNF, &sysOptKnv_u8);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_ACT_MTR_HD_CNTR_KNF, &sysOptCntrKnv_u8);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_ACT_MTR_HD_HOLD, &sysOptHoldKnv_u8);
    }

    //---- Disable axe KNIFE ----//
    if(Ret_e == RC_OK)
    {
        if(sysOptKnv_u8 == APPSYS_OPT_ACT_MTR_HD_KNF_CL42T)
        {
            Ret_e = s_HC_AxeStop(HC_AXE_HD_KNFE, TRUE);
        }

        if(Ret_e == RC_OK)
        {
            if(sysOptCntrKnv_u8 == APPSYS_OPT_ACT_MTR_HD_CNTR_KNF_CL42T)
            {
                Ret_e = s_HC_AxeStop(HC_AXE_HD_CNTR_KNFE, TRUE);
            }
        }

        if(Ret_e == RC_OK)
        {
            if(sysOptHoldKnv_u8 == APPSYS_OPT_ACT_MTR_HD_HOLD_CL42T)
            {
                Ret_e = s_HC_AxeStop(HC_AXE_HD_HOLD_KNFE, TRUE);
            }
        }

        if(Ret_e == RC_OK)
        {
            g_FlagMotorEnable_b = FALSE;
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = s_HC_ApplyRearmRequest();
        }
    }
    return Ret_e;
}

/*********************************
 * s_HC_Fsm_PrdTsk_Error
 *********************************/
static t_eReturnCode s_HC_Fsm_PrdTsk_Error(void)
{
    return RC_OK;
}

/*********************************
 * s_HC_ApplyRearmRequest
 *********************************/
static t_eReturnCode s_HC_ApplyRearmRequest(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eHC_AxeHandleList idxAxe_e;

    if(g_RearmInfo_s.reqRearm_b == FALSE)
    {
        Ret_e = RC_OK;
    }
    else
    {
        switch(g_RearmInfo_s.rearmType_e)
        {
            case APP_LGC_REARM_TYPE_FSM_PRE_OPE:
                g_FlagPosCmdPending_b = FALSE;
                g_FlagIterCmdReady_b = FALSE;
                g_calibCmdInfo_s.reqSts_e = APPLGC_CALIB_REQSTS_IDLE;
                g_calibCmdInfo_s.currSts_e = APPLGC_CALIB_REQSTS_IDLE;
                g_Fsm_PrdTsk_OpeSts_e = HC_FSM_PRDTSK_OPE_SERVO;                g_calibCmdInfo_s.isNewCmdReceiv_b = FALSE;
                //---- reset to preope ----//
                g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_PRE_OPS;
            break;

            case APP_LGC_REARM_TYPE_TOTAL:
                // Full functional reset of command/calibration runtime.
                (void)LIBQUEUE_ClearAll(&g_QueueCmdPosRcvMngmt_s);
                for(idxAxe_e = HC_AXE_HEAD ; idxAxe_e < HC_AXE_HD_NB ; idxAxe_e++)
                {
                    (void)LIBQUEUE_ClearAll(&g_QueueCmdIterRcvMngmt_as[idxAxe_e]);
                    g_axeMissPulses_af32[idxAxe_e] = 0.0F;
                }

                g_KnifeTipCmpte_s.carthPos_s.x_mm = 0.0F;
                g_KnifeTipCmpte_s.carthPos_s.y_mm = 0.0F;
                g_KnifeTipCmpte_s.jointAng_s.alpha_b_mrad = 0.0F;
                g_KnifeTipCmpte_s.jointAng_s.alpha_c_mrad = 0.0F;
                g_KnifeHoldCmpte_s.carthPos_s.x_mm = 0.0F;
                g_KnifeHoldCmpte_s.carthPos_s.y_mm = 0.0F;
                g_KnifeHoldCmpte_s.jointAng_s.alpha_b_mrad = 0.0F;
                g_KnifeHoldCmpte_s.jointAng_s.alpha_c_mrad = 0.0F;
                g_currCmdTimeStampID_u32 = (t_uint32)0;
                g_FlagPosCmdPending_b = FALSE;
                g_FlagIterCmdReady_b = FALSE;
                g_FlagRcvPosCmd_b = FALSE;
                g_calibCmdInfo_s.pulses_f32 = 0.0F;
                g_calibCmdInfo_s.speed_f32 = 0.0F;
                g_calibCmdInfo_s.reqSts_e = APPLGC_CALIB_REQSTS_IDLE;
                g_calibCmdInfo_s.currSts_e = APPLGC_CALIB_REQSTS_IDLE;
                g_calibCmdInfo_s.isNewCmdReceiv_b = FALSE;
                g_Fsm_PrdTsk_OpeSts_e = HC_FSM_PRDTSK_OPE_SERVO;
            break;

            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                ASSERT((t_uint16)g_RearmInfo_s.rearmType_e);
            break;
        }

        if(Ret_e == RC_OK)
        {
            g_RearmInfo_s.reqRearm_b = FALSE;
            g_RearmInfo_s.rearmType_e = LGC_REARM_TYPE_NB;
        }
    }

    return Ret_e;
}

/*********************************
 * s_HC_QuantizePulseCmd
 *********************************/
static t_sint32 s_HC_QuantizePulseCmd(t_eHC_AxeHandleList f_idxAxe_e, t_float32 f_pulseCmd_f32)
{
    t_float32 pulseWithResid_f32 = f_pulseCmd_f32;
    t_float32 cmdPulse_f32;
    t_sint32 cmdPulse_s32;

    if(f_idxAxe_e < HC_AXE_HD_NB)
    {
        pulseWithResid_f32 += g_axeMissPulses_af32[f_idxAxe_e];
    }

    if(pulseWithResid_f32 >= 0.0F)
    {
        cmdPulse_f32 = floorf(pulseWithResid_f32 + 0.5F);
    }
    else
    {
        cmdPulse_f32 = ceilf(pulseWithResid_f32 - 0.5F);
    }

    cmdPulse_s32 = (t_sint32)cmdPulse_f32;

    if(f_idxAxe_e < HC_AXE_HD_NB)
    {
        g_axeMissPulses_af32[f_idxAxe_e] = pulseWithResid_f32 - (t_float32)cmdPulse_s32;
    }

    return cmdPulse_s32;
}

/*********************************
 * s_HC_WriteOrMergeIterCmd
 *********************************/
static t_eReturnCode s_HC_WriteOrMergeIterCmd(t_sLIBQUEUE_QueueCore * f_queue_ps,
                                              const t_sHC_MtrCmdIterPayload * f_cmd_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sHC_MtrCmdIterPayload * lastCmd_ps;
    t_uint16 lastIdx_u16;
    t_float32 freqDiff_f32;
    t_sint32 mergedPulse_s32;

    if((f_queue_ps == NULL)
    || (f_cmd_ps == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
        ASSERT((t_uint16)0);
    }
    else if(f_cmd_ps->pulses_s32 == (t_sint32)0)
    {
        Ret_e = RC_OK;
    }
    else if(((f_cmd_ps->pulses_s32 > -(t_sint32)HC_MIN_PULSE_CMD_ABS_S32)
          && (f_cmd_ps->pulses_s32 < (t_sint32)HC_MIN_PULSE_CMD_ABS_S32)))
    {
        Ret_e = RC_OK;
    }
    else if(f_queue_ps->actualSize_u16 > (t_uint16)0)
    {
        if(f_queue_ps->tail_u16 == (t_uint16)0)
        {
            lastIdx_u16 = (t_uint16)(f_queue_ps->QueueCfg_s.actualSize_u16 - (t_uint16)1);
        }
        else
        {
            lastIdx_u16 = (t_uint16)(f_queue_ps->tail_u16 - (t_uint16)1);
        }

        lastCmd_ps = (t_sHC_MtrCmdIterPayload *)((char *)f_queue_ps->QueueCfg_s.bufferHead_pv
                                            + ((t_uint32)lastIdx_u16 * f_queue_ps->QueueCfg_s.elementSize_u16));

        freqDiff_f32 = fabsf(lastCmd_ps->frequency_f32 - f_cmd_ps->frequency_f32);
        mergedPulse_s32 = lastCmd_ps->pulses_s32 + f_cmd_ps->pulses_s32;

        if((freqDiff_f32 <= 0.1F)
        && (lastCmd_ps->triggerTimer_f32 == f_cmd_ps->triggerTimer_f32)
        && (((lastCmd_ps->pulses_s32 > (t_sint32)0) && (f_cmd_ps->pulses_s32 > (t_sint32)0))
            || ((lastCmd_ps->pulses_s32 < (t_sint32)0) && (f_cmd_ps->pulses_s32 < (t_sint32)0))))
        {
            lastCmd_ps->pulses_s32 = mergedPulse_s32;
            Ret_e = RC_OK;
        }
        else
        {
            Ret_e = LIBQUEUE_WriteElement(f_queue_ps, f_cmd_ps, sizeof(t_sHC_MtrCmdIterPayload));
        }
    }
    else
    {
        Ret_e = LIBQUEUE_WriteElement(f_queue_ps, f_cmd_ps, sizeof(t_sHC_MtrCmdIterPayload));
    }

    return Ret_e;
}

/*********************************
 * s_HC_Fsm_PrdTsk_Ope_Servo
 *********************************/
static t_eReturnCode s_HC_Fsm_PrdTsk_Ope_Servo(void)
{
    t_eReturnCode Ret_e;

    //---- variable for delta angle ----//
    t_float32 deltaAplha_b_f32 = (
          g_KnifeTipCmpte_s.jointAng_s.alpha_b_mrad 
        - g_KnifeTipCurr_s.jointAng_s.alpha_b_mrad
    );
    t_float32 deltaAplha_c_f32 = (
        g_KnifeTipCmpte_s.jointAng_s.alpha_c_mrad 
        - g_KnifeTipCurr_s.jointAng_s.alpha_c_mrad
    );

    //---- pulse correction -----//
    t_float32 pulseCorrAlpha_b_f32;
    t_float32 pulseCorrAlpha_c_f32;
    t_sint32 pulseCorrAlpha_b_s32 = 0;
    t_sint32 pulseCorrAlpha_c_s32 = 0;

    //---- variable for param max delta ----//
    t_uAPPSPM_PrmValType prmMaxDeltaAlpha_b_u;
    t_uAPPSPM_PrmValType prmMaxDeltaAlpha_c_u;

    //---- variable for getting status ----//
    const t_sHC_AxeAppCfg * hdKnfCfg_ps = &c_HC_AppAxesCfg_as[HC_AXE_HD_KNFE];
    const t_sHC_AxeAppCfg * hdCntrKnfCfg_ps = &c_HC_AppAxesCfg_as[HC_AXE_HD_CNTR_KNFE];
    t_float32 hdKnfMtrsts_f32 = 0.0F;
    t_float32 hdCntrKnfMtrsts_f32 = 0.0F;

    //---- 1- Get Info Param -----//
    Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_TIP_KNIFE_MAX_DELTA_ALPHA_B, &prmMaxDeltaAlpha_b_u);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_TIP_KNIFE_MAX_DELTA_ALPHA_C, &prmMaxDeltaAlpha_c_u);
    }
    if(Ret_e == RC_OK)
    {
        //---- 3- get motor status  -----//
        Ret_e = APPLGC_GetActValue(hdKnfCfg_ps->actIfSpeed_e, &hdKnfMtrsts_f32);
        if(Ret_e == RC_OK)
        {
            Ret_e = APPLGC_GetActValue(hdCntrKnfCfg_ps->actIfSpeed_e, &hdCntrKnfMtrsts_f32);
        }
    }
    if(Ret_e == RC_OK)
    {
        //---- 4- check only if motor are off -----//
        if((hdKnfMtrsts_f32 == APPACT_MOTOR_STS_ON)
        || (hdCntrKnfMtrsts_f32 == APPACT_MOTOR_STS_ON))
        {
            Ret_e = RC_WARNING_BUSY;
        }
    }
    if(Ret_e == RC_OK)
    {
        //---- 5- check asservissement -----//

        //---- param in milliradian ----//
        if(deltaAplha_b_f32 > (t_float32)prmMaxDeltaAlpha_b_u.prmVal_u16)
        {
            APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_HEAD_TIP_KNIVE_DELTA_LIMIT_ERROR,
                                    APPSDM_DIAG_ITEM_REPORT_FAIL,
                                    (t_uint16)(deltaAplha_b_f32 * 10), // milliradian * 10
                                    (t_uint16)(0));
        }
        else if(deltaAplha_c_f32 > (t_float32)prmMaxDeltaAlpha_c_u.prmVal_u16)
        {
            APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_HEAD_TIP_KNIVE_DELTA_LIMIT_ERROR,
                                    APPSDM_DIAG_ITEM_REPORT_FAIL,
                                    (t_uint16)(0), 
                                    (t_uint16)(deltaAplha_c_f32 * 10)); // milliradian * 10
        }
        else 
        {
            Ret_e = s_HC_ComputePulseFromAngle( deltaAplha_b_f32,
                                                deltaAplha_c_f32,
                                                &pulseCorrAlpha_b_f32,
                                                &pulseCorrAlpha_c_f32);
            if(Ret_e == RC_OK)
            {
                pulseCorrAlpha_b_s32 = s_HC_QuantizePulseCmd(HC_AXE_HD_CNTR_KNFE, pulseCorrAlpha_b_f32);
                pulseCorrAlpha_c_s32 = s_HC_QuantizePulseCmd(HC_AXE_HD_KNFE, pulseCorrAlpha_c_f32);
            }
            if((Ret_e == RC_OK)
            && (pulseCorrAlpha_b_s32 != 0))
            {
                Ret_e = s_HC_SetAxeSetPoint(HC_AXE_HD_CNTR_KNFE,
                                            pulseCorrAlpha_b_s32,
                                            HC_PULSE_SPEED_SERVO,
                                            0.0F);
                FMKSRL_LOG( "[HC] : Detect Delta b diff -> %d, correction B->%d, Retcode->%d\r\n",
                            (t_sint32)deltaAplha_b_f32,
                            (t_sint32)pulseCorrAlpha_b_s32,
                            (t_sint32)Ret_e);
            }
            if((Ret_e == RC_OK)
            && (pulseCorrAlpha_c_s32 != 0))
            {
                Ret_e = s_HC_SetAxeSetPoint(HC_AXE_HD_KNFE,
                                            pulseCorrAlpha_c_s32,
                                            HC_PULSE_SPEED_SERVO,
                                            0.0F);
                FMKSRL_LOG( "[HC] : Detect Delta c diff -> %d, correction C->%d, Retcode->%d\r\n",
                            (t_sint32)deltaAplha_c_f32,
                            (t_sint32)pulseCorrAlpha_c_s32,
                            (t_sint32)Ret_e);
            }
            
            
        }
    }
    
    return Ret_e;
}
/*********************************
 * s_HC_GetQueuedTipAngles
 *********************************/
static t_eReturnCode s_HC_GetQueuedTipAngles( t_float32 * f_alphaB_pmrad,
                                                t_float32 * f_alphaC_pmrad)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint16 idxCmd_u16;
    t_float32 deltaAlpha_b_f32;
    t_float32 deltaAlpha_c_f32;

    const t_sLIBQUEUE_QueueCore * queueKnf_ps = &g_QueueCmdIterRcvMngmt_as[HC_AXE_HD_KNFE];
    const t_sLIBQUEUE_QueueCore * queueCntrKnf_ps = &g_QueueCmdIterRcvMngmt_as[HC_AXE_HD_CNTR_KNFE];

    if((f_alphaB_pmrad == NULL)
    || (f_alphaC_pmrad == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
        ASSERT((t_uint16)0);
    }
    else
    {
        //---- start with what we already send ----//
        *f_alphaB_pmrad = g_KnifeTipCmpte_s.jointAng_s.alpha_b_mrad;
        *f_alphaC_pmrad = g_KnifeTipCmpte_s.jointAng_s.alpha_c_mrad;

        //---- then add queued knife delta commands ----//
        for(idxCmd_u16 = (t_uint16)0;
        (idxCmd_u16 < queueKnf_ps->actualSize_u16)
        && (Ret_e == RC_OK);
        idxCmd_u16++)
        {
            const t_uint16 knfIdx_u16 = (t_uint16)((queueKnf_ps->head_u16 + idxCmd_u16) % queueKnf_ps->QueueCfg_s.actualSize_u16);

            const t_sHC_MtrCmdIterPayload * knfCmd_ps = (const t_sHC_MtrCmdIterPayload *)((const char *)queueKnf_ps->QueueCfg_s.bufferHead_pv
                                                    + ((t_uint32)knfIdx_u16 * queueKnf_ps->QueueCfg_s.elementSize_u16));

            Ret_e = s_HC_ComputeAnglefromPulse(knfCmd_ps->pulses_s32,
                                                (t_sint32)0,
                                                &deltaAlpha_b_f32,
                                                &deltaAlpha_c_f32);
            if(Ret_e == RC_OK)
            {
                *f_alphaB_pmrad += deltaAlpha_b_f32;
                *f_alphaC_pmrad += deltaAlpha_c_f32;
            }
        }

        //---- add queued counter-knife delta commands ----//
        for(idxCmd_u16 = (t_uint16)0;
        (idxCmd_u16 < queueCntrKnf_ps->actualSize_u16)
        && (Ret_e == RC_OK);
        idxCmd_u16++)
        {
            const t_uint16 cntrKnfIdx_u16 = (t_uint16)((queueCntrKnf_ps->head_u16 + idxCmd_u16) % queueCntrKnf_ps->QueueCfg_s.actualSize_u16);

            const t_sHC_MtrCmdIterPayload * cntrKnfCmd_ps = (const t_sHC_MtrCmdIterPayload *)((const char *)queueCntrKnf_ps->QueueCfg_s.bufferHead_pv
                                                    + ((t_uint32)cntrKnfIdx_u16 * queueCntrKnf_ps->QueueCfg_s.elementSize_u16));

            Ret_e = s_HC_ComputeAnglefromPulse((t_sint32)0,
                                                cntrKnfCmd_ps->pulses_s32,
                                                &deltaAlpha_b_f32,
                                                &deltaAlpha_c_f32);
            if(Ret_e == RC_OK)
            {
                *f_alphaB_pmrad += deltaAlpha_b_f32;
                *f_alphaC_pmrad += deltaAlpha_c_f32;
            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_HC_Fsm_PrdTsk_Ope_PosCmdMngmt
 *********************************/
static t_eReturnCode s_HC_Fsm_PrdTsk_Ope_PosCmdMngmt(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxCmdTreated_u8;
    t_sHC_PosCmdQueueElem posCmd_s;
    
    //---- angle alpha variable ----//
    t_float32 alpha_b_mrad = 0.0F;
    t_float32 alpha_c_mrad = 0.0F;
    t_float32 deltaAlpha_b_f32;
    t_float32 deltaAlpha_c_f32;

    //---- expected base = current computed position + queued pulse commands ----//
    t_float32 currCmpte_alpha_b_f32 = 0.0F;
    t_float32 currCmpte_alpha_c_f32 = 0.0F;

    //---- act_pulse value ----//
    t_float32 pulseKnf_f32;
    t_float32 pulseCntrKnf_f32;

    //--- retrieve elem queue ----//
    t_sHC_MtrCmdIterPayload knfCmdIterPayload_s;
    t_sHC_MtrCmdIterPayload cntrKnfCmdIterPayload_s;

    //--- transform rpm to Hz ----//
    t_uAPPSPM_PrmValType prmKnifeRpmToHz_u;
    t_uAPPSPM_PrmValType prmCntrKnifeRpmToHz_u;


    //--- first, get the current alpha_b & aplha_c from previous build ----//
    Ret_e = s_HC_GetQueuedTipAngles(&currCmpte_alpha_b_f32,
                                    &currCmpte_alpha_c_f32);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_KNIFE_RPM_TO_HZ, &prmKnifeRpmToHz_u);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_CNTR_KNIFE_RPM_TO_HZ, &prmCntrKnifeRpmToHz_u);
    }

    for(idxCmdTreated_u8 = (t_uint8)0 ; 
    (idxCmdTreated_u8 < HC_POS_CMD_TREATED_MAX)
    && (Ret_e == RC_OK) ; 
    idxCmdTreated_u8++)
    {
        //---- clear buffer ----//
        (void)SafeMem_memclear(&posCmd_s, sizeof(posCmd_s));
        
        //---- 1 Read element from Queue ----//
        Ret_e = LIBQUEUE_PopElement(    &g_QueueCmdPosRcvMngmt_s,
                                        &posCmd_s,
                                        sizeof(t_sHC_PosCmdQueueElem));
        
        #warning special debug
        ////----1- check Id cmd with current ----//
        // if((Ret_e == RC_OK)
        // && (g_currCmdTimeStampID_u32 != posCmd_s.timeStampID_u32))
        // {
        //     Ret_e = RC_ERROR_NOT_SUPPORTED;
        //     ASSERT((t_uint16)posCmd_s.timeStampID_u32);
        //     APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_HEAD_TIP_KNIVE_POS_TIMESTAMPS_ID,
        //                             APPSDM_DIAG_ITEM_REPORT_FAIL,
        //                             (t_uint16)g_currCmdTimeStampID_u32,
        //                             (t_uint16)posCmd_s.timeStampID_u32);
        //     //---- erase value ----//
        //     (void)LIBQUEUE_ReadElement( &g_QueueCmdPosRcvMngmt_s,
        //                                 NULL,
        //                                 sizeof(t_sHC_PosCmdQueueElem));
        // }
        //----2- Depending on cmd type, build pulses ----//
        if(Ret_e == RC_OK) 
        {
            //---- Intermediary action if cmd type is carthesian ----//
            if(posCmd_s.cmdPosType_e == HC_CMD_TYPE_POS_CARTH)
            {

                Ret_e = s_HC_CheckPositionValidity(posCmd_s.Pos_u.Carth_s);
                if(Ret_e == RC_OK)
                {
                    //---- Angle to have to get to that position ----//
                    Ret_e = s_HC_ComputeAngleFromCarthesian(posCmd_s.Pos_u.Carth_s.x_mm,
                                                            posCmd_s.Pos_u.Carth_s.y_mm,
                                                            &alpha_b_mrad,
                                                            &alpha_c_mrad);
                }
            }
            else if(posCmd_s.cmdPosType_e == HC_CMD_TYPE_POS_JOINT)
            {
                alpha_b_mrad = posCmd_s.Pos_u.Joint_s.alpha_b_mrad;
                alpha_c_mrad = posCmd_s.Pos_u.Joint_s.alpha_c_mrad;
            }
            else 
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
                ASSERT((t_uint16)posCmd_s.cmdPosType_e);
            }

            //--- now we work with joint only ---//
            if(Ret_e == RC_OK)
            {
                Ret_e = s_HC_CheckAngleAssociationValidity(alpha_b_mrad, alpha_c_mrad);
            }
            if(Ret_e == RC_OK)
            {
                
                //---- 3- calculate delta ----//
                //---- delta to apply = target - current planned point ----//
                deltaAlpha_b_f32 = alpha_b_mrad - currCmpte_alpha_b_f32;
                deltaAlpha_c_f32 = alpha_c_mrad - currCmpte_alpha_c_f32;

                Ret_e = s_HC_ComputePulseFromAngle( deltaAlpha_b_f32,
                                                    deltaAlpha_c_f32,
                                                    &pulseKnf_f32,
                                                    &pulseCntrKnf_f32);
                if(Ret_e == RC_OK)
                {
                    knfCmdIterPayload_s.frequency_f32 = 
                        (t_float32)posCmd_s.speed_s.knifeSpd_rpm * prmKnifeRpmToHz_u.prmVal_f32;
                    knfCmdIterPayload_s.pulses_s32 = s_HC_QuantizePulseCmd(HC_AXE_HD_KNFE, pulseKnf_f32);
                    knfCmdIterPayload_s.triggerTimer_f32 = 0.0F;

                    cntrKnfCmdIterPayload_s.frequency_f32 = 
                        (t_float32)posCmd_s.speed_s.cntrKnifeSpd_rpm * prmCntrKnifeRpmToHz_u.prmVal_f32;
                    cntrKnfCmdIterPayload_s.pulses_s32 = s_HC_QuantizePulseCmd(HC_AXE_HD_CNTR_KNFE, pulseCntrKnf_f32);
                    cntrKnfCmdIterPayload_s.triggerTimer_f32 = 0.0F;
                    
                    //---- write element only if there is at least one pulse -----//
                    if(knfCmdIterPayload_s.pulses_s32 != (t_sint32)0)
                    {
                        Ret_e = s_HC_WriteOrMergeIterCmd(&g_QueueCmdIterRcvMngmt_as[HC_AXE_HD_KNFE],
                                                         &knfCmdIterPayload_s);
                    }
                    if((Ret_e == RC_OK)
                    && (cntrKnfCmdIterPayload_s.pulses_s32 != (t_sint32)0))
                    {
                        Ret_e = s_HC_WriteOrMergeIterCmd(&g_QueueCmdIterRcvMngmt_as[HC_AXE_HD_CNTR_KNFE],
                                                         &cntrKnfCmdIterPayload_s);
                    }
                    if(Ret_e == RC_OK) 
                    {
                        //---- clear element from pos queue ----//
                        Ret_e = LIBQUEUE_ReadElement(    &g_QueueCmdPosRcvMngmt_s,
                                                        NULL,
                                                        sizeof(t_sHC_PosCmdQueueElem));
                        //---- adapt current alpha_b & alpha_c pos 
                        currCmpte_alpha_b_f32 = alpha_b_mrad;
                        currCmpte_alpha_c_f32 = alpha_c_mrad;

                        //---- update the current time stamps ----//
                        g_currCmdTimeStampID_u32 ++;
                        if(g_currCmdTimeStampID_u32 > (t_uint32)HC_CMD_POS_TIMESTAMP_ID_MAX)
                        {
                            g_currCmdTimeStampID_u32 = (t_uint32)0;
                        }

                        if(g_FlagIterCmdReady_b == FALSE)
                        {
                            g_FlagIterCmdReady_b = TRUE;
                        }
                    }
                }
            }
        }
    }
    
    return Ret_e;
}

/*********************************
 * s_HC_Fsm_PrdTsk_Ope_PulseCmdMngmt
 *********************************/
static t_eReturnCode s_HC_Fsm_PrdTsk_Ope_PulseCmdMngmt(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxPulseCmdTreated_u8;
    t_uint8 nbCmdApplied_u8 = (t_uint8)0;

    //---- get info from pulse queue ----//
    t_sHC_MtrCmdIterPayload knfCmdIterPayload_s = {0};
    t_sHC_MtrCmdIterPayload cntrKnfCmdIterPayload_s = {0};

    //---- update angle position/ x,y compute position ----//
    t_float32 deltaAlpha_b_f32 = 0.0F;
    t_float32 currdeltaAlpha_b_f32 = 0.0F;

    t_float32 deltaAlpha_c_f32 = 0.0F;
    t_float32 currdeltaAlpha_c_f32 = 0.0F;

    t_float32 posXCmpte_f32;
    t_float32 posYCmpte_f32;
    t_bool hasKnfCmd_b;
    t_bool hasCntrKnfCmd_b;

    for(idxPulseCmdTreated_u8 = (t_uint8)0 ; 
    (idxPulseCmdTreated_u8 < HC_PULSE_CMD_TREATED_MAX) 
    && (Ret_e == RC_OK) ; 
        idxPulseCmdTreated_u8++)
    {
        //---- Clear buffer reception payload ----//
        (void)SafeMem_memclear(&knfCmdIterPayload_s, sizeof(t_sHC_MtrCmdIterPayload));
        (void)SafeMem_memclear(&cntrKnfCmdIterPayload_s, sizeof(t_sHC_MtrCmdIterPayload));
        hasKnfCmd_b = FALSE;
        hasCntrKnfCmd_b = FALSE;

        //---- pop element for setpoint knife & cntr knife ----//
        Ret_e = LIBQUEUE_PopElement(    &g_QueueCmdIterRcvMngmt_as[HC_AXE_HD_KNFE],
                                        &knfCmdIterPayload_s,
                                        sizeof(t_sHC_MtrCmdIterPayload));
        if(Ret_e == RC_OK)
        {
            Ret_e = s_HC_SetAxeSetPoint(HC_AXE_HD_KNFE,
                                        knfCmdIterPayload_s.pulses_s32,
                                        knfCmdIterPayload_s.frequency_f32,
                                        knfCmdIterPayload_s.triggerTimer_f32);
            if(Ret_e == RC_OK)
            {
                hasKnfCmd_b = TRUE;
                (void)LIBQUEUE_ReadElement(&g_QueueCmdIterRcvMngmt_as[HC_AXE_HD_KNFE], NULL, sizeof(t_sHC_MtrCmdIterPayload));
            }
            
        }
        else if(Ret_e == RC_WARNING_NO_OPERATION)
        {
            Ret_e = RC_OK;
        }

        
        if(Ret_e == RC_OK)
        {
            Ret_e = LIBQUEUE_PopElement(    &g_QueueCmdIterRcvMngmt_as[HC_AXE_HD_CNTR_KNFE],
                                            &cntrKnfCmdIterPayload_s,
                                            sizeof(t_sHC_MtrCmdIterPayload));
            if(Ret_e == RC_OK)
            {
                Ret_e = s_HC_SetAxeSetPoint(HC_AXE_HD_CNTR_KNFE,
                                            cntrKnfCmdIterPayload_s.pulses_s32,
                                            cntrKnfCmdIterPayload_s.frequency_f32,
                                            cntrKnfCmdIterPayload_s.triggerTimer_f32);
                if(Ret_e == RC_OK)
                {
                    hasCntrKnfCmd_b = TRUE;
                    //---- erase setpoint for knife & cntr knife ----//
                    
                    (void)LIBQUEUE_ReadElement(&g_QueueCmdIterRcvMngmt_as[HC_AXE_HD_CNTR_KNFE], NULL, sizeof(t_sHC_MtrCmdIterPayload));
                }
            }
            else if(Ret_e == RC_WARNING_NO_OPERATION)
            {
                Ret_e = RC_OK;
            }
        }

        //---- nothing available on both queues ----//
        if((Ret_e == RC_OK)
        && (hasKnfCmd_b == FALSE)
        && (hasCntrKnfCmd_b == FALSE))
        {
            if(nbCmdApplied_u8 == (t_uint8)0)
            {
                Ret_e = RC_WARNING_NO_OPERATION;
            }
            break;
        }

        //---- meaning we at least set one axe ----//
        if((Ret_e == RC_OK)
        && ((hasCntrKnfCmd_b == TRUE)
        || (hasKnfCmd_b == TRUE)))
        {
            //---- update the current delta angle position ----//
            Ret_e = s_HC_ComputeAnglefromPulse( knfCmdIterPayload_s.pulses_s32,
                                                cntrKnfCmdIterPayload_s.pulses_s32,
                                                &currdeltaAlpha_b_f32,
                                                &currdeltaAlpha_c_f32);
            if(Ret_e == RC_OK)
            {
                deltaAlpha_b_f32 += currdeltaAlpha_b_f32;
                deltaAlpha_c_f32 += currdeltaAlpha_c_f32;
            }
            if(Ret_e < RC_OK)
            {
                ASSERT((t_uint16)Ret_e);
            }
            else if(Ret_e == RC_OK)
            {
                nbCmdApplied_u8++;
            }
        }
    }

    if((nbCmdApplied_u8 > (t_uint8)0)
    && (Ret_e == RC_OK))
    {
        //---- now update the global current position ----//
        g_KnifeTipCmpte_s.jointAng_s.alpha_b_mrad += deltaAlpha_b_f32;
        g_KnifeTipCmpte_s.jointAng_s.alpha_c_mrad += deltaAlpha_c_f32;

        Ret_e = s_HC_ComputeCarthesianFromAngle(g_KnifeTipCmpte_s.jointAng_s.alpha_b_mrad,
                                                g_KnifeTipCmpte_s.jointAng_s.alpha_c_mrad,
                                                &posXCmpte_f32,
                                                &posYCmpte_f32);
        if(Ret_e == RC_OK)
        {
            g_KnifeTipCmpte_s.carthPos_s.x_mm = posXCmpte_f32;
            g_KnifeTipCmpte_s.carthPos_s.y_mm = posYCmpte_f32;
        }
    }

    return Ret_e;
}

/*********************************
 * s_HC_SafetyUpdate
 *********************************/
static t_eReturnCode s_HC_SafetyUpdate(void)
{
    t_eReturnCode Ret_e = RC_OK;
    //---- TODO: look the current that flowss into motor when 
    //          they are on to find problem, nothing for now ----//

    return Ret_e;
}

/*********************************
 * s_HC_UpdatePosition
 *********************************/
static t_eReturnCode s_HC_UpdatePosition(void)
{
    t_eReturnCode Ret_e;

    t_uint8 sysOptCntrKnv_u8 = 0;
    t_uint8 sysOptKnv_u8 = 0;
    t_uint8 sysOptHoldKnv_u8 = 0;

    //---- sns value ----//
    t_float32 snsCntrKnvAngle_f32;
    t_float32 snsKnvAngle_f32;
    t_float32 snsHoldKnvAngle_f32;

    //---- angle value ----//
    t_float32 alpha_b_mrad;
    t_float32 alpha_c_mrad;

    //--- carthesian position ---//
    t_float32 posX_f32;
    t_float32 posY_f32;

    Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SNS_ECDR_HD_KNF, &sysOptKnv_u8);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SNS_ECDR_HD_CNTR_KNF, &sysOptCntrKnv_u8);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSYS_GetSysOption(APPSYS_OPT_ID_SNS_ECDR_HD_HOLD, &sysOptHoldKnv_u8);
    }
    if(Ret_e == RC_OK)
    {

        //---- if we have the encoder value, we use it, 
        //         if not, we use the compute value -----//

        if((sysOptKnv_u8 > APPSYS_OPT_SNS_ECDR_HD_HOLD_UNUSED)
        && (sysOptCntrKnv_u8 > APPSYS_OPT_SNS_ECDR_HD_CNTR_KNF_UNUSED))
        {
            Ret_e = APPLGC_GetSnsValue(APPSNS_SNSITF_ECDR_HD_KNF_POS, &snsKnvAngle_f32);
            if(Ret_e == RC_OK)
            {
                Ret_e = APPLGC_GetSnsValue(APPSNS_SNSITF_ECDR_HD_CNTR_KNF_POS, &snsCntrKnvAngle_f32);
            }
            if(Ret_e == RC_OK)
            {
                alpha_b_mrad = snsCntrKnvAngle_f32;
                alpha_c_mrad = snsKnvAngle_f32;

                Ret_e = s_HC_ComputeCarthesianFromAngle(alpha_b_mrad,
                                                        alpha_c_mrad,
                                                        &posX_f32,
                                                        &posY_f32);
                if(Ret_e == RC_OK)
                {
                    g_KnifeTipCurr_s.carthPos_s.x_mm = posX_f32;
                    g_KnifeTipCurr_s.carthPos_s.y_mm = posY_f32;
                    g_KnifeTipCurr_s.jointAng_s.alpha_b_mrad = alpha_b_mrad;
                    g_KnifeTipCurr_s.jointAng_s.alpha_c_mrad = alpha_c_mrad;
                }
                else 
                {
                    ASSERT((t_uint16)Ret_e);
                }
            }
        }

        if((Ret_e >= RC_OK)
        && (sysOptHoldKnv_u8 > APPSYS_OPT_SNS_ECDR_HD_CNTR_KNF_UNUSED))
        {
            Ret_e = APPLGC_GetSnsValue(APPSNS_SNSITF_ECDR_HD_HOLD_POS, &snsHoldKnvAngle_f32);

            //--- compute carthesian from angle ----//
        }
    }
    
    return Ret_e;
}

/*********************************
 * s_HC_SetAxeSetPoint
 *********************************/
static t_eReturnCode s_HC_SetAxeSetPoint( t_eHC_AxeHandleList f_idxAxe_e, 
                                            t_sint32 f_setPoint_s32,
                                            t_float32 f_speedHz_f32, 
                                            t_float32 f_trigTiming_f32)
{
    t_eReturnCode Ret_e;
    const t_sHC_AxeAppCfg * appAxeCfg_ps;
    t_eAPPLGC_SrvHealth axeHealth_e;

    if(f_idxAxe_e >= HC_AXE_HD_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)0);
    }
    else 
    {
        appAxeCfg_ps = &c_HC_AppAxesCfg_as[f_idxAxe_e];

        Ret_e = APPLGC_GetServiceHealth(appAxeCfg_ps->lgcSrvID_e, &axeHealth_e);
        if(Ret_e != RC_OK)
        {
            axeHealth_e = APPLGC_SRV_HEALTH_ERROR;
        }
        if(axeHealth_e == APPLGC_SRV_HEALTH_OK)
        {
            Ret_e = APPACT_SetActValue(appAxeCfg_ps->actifMtrSetPoint_e, (t_float32)f_setPoint_s32);
            if(Ret_e == RC_OK)
            {
                Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, f_speedHz_f32);
            }
            if(Ret_e == RC_OK)
            {
                Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfTimTrig_e, f_trigTiming_f32);
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
 * s_HC_EnableAxe
 *********************************/
static t_eReturnCode s_HC_EnableAxe(t_eHC_AxeHandleList f_idxAxe_e)
{
    t_eReturnCode Ret_e;
    const t_sHC_AxeAppCfg * appAxeCfg_ps;

    if(f_idxAxe_e >= HC_AXE_HD_NB)
    {
        ASSERT((t_uint16)f_idxAxe_e);
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else 
    {
        //---- maybe make a switch case where now there is no difference 
        //          isn't a good idea, in release modify this ----//
        switch(f_idxAxe_e)
        {
            case HC_AXE_HD_KNFE:
                appAxeCfg_ps = &c_HC_AppAxesCfg_as[HC_AXE_HD_KNFE];
                Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, APPACT_ENABLE_MOTOR);
            break;
            case HC_AXE_HD_CNTR_KNFE:
                appAxeCfg_ps = &c_HC_AppAxesCfg_as[HC_AXE_HD_CNTR_KNFE];
                Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, APPACT_ENABLE_MOTOR);
            break;
            case HC_AXE_HD_HOLD_KNFE:
                appAxeCfg_ps = &c_HC_AppAxesCfg_as[HC_AXE_HD_HOLD_KNFE];
                Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, APPACT_ENABLE_MOTOR);
            break;
            case HC_AXE_HD_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
            break;
        }
    }

    return Ret_e;
}

/*********************************
 * s_HC_HardAxeStop
 *********************************/
static t_eReturnCode s_HC_AxeStop(t_eHC_AxeHandleList f_idxAxe_e, t_bool f_isHardStop_b)
{
    t_eReturnCode Ret_e;
    const t_sHC_AxeAppCfg * appAxeCfg_ps;
    t_float32 stopID_f32 = 0.0F;

    if(f_idxAxe_e >= HC_AXE_HD_NB)
    {
        ASSERT((t_uint16)f_idxAxe_e);
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else 
    {
        appAxeCfg_ps = &c_HC_AppAxesCfg_as[f_idxAxe_e];

        if(f_isHardStop_b == TRUE)
        {
            stopID_f32 = APPACT_HARD_STOP;
        }
        else 
        {
            stopID_f32 = APPACT_SOFT_STOP;
        }

        Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, stopID_f32);
    }

    return Ret_e;
}

/*********************************
 * s_HC_SigReceptionCallback
 *********************************/
static void s_HC_MsgReceptionCallback(  t_uint16 f_msgID_u16,
                                        t_uint8 f_nbSignal_u8,
                                        t_eAPPSIG_Signal *f_signal_ae, 
                                        t_float32 *f_sigValue_af32)
{
    t_eReturnCode Ret_e;

    if(f_msgID_u16 >= (t_uint16)APPSIG_CAN_MSG_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)f_msgID_u16);
    }
    else 
    {
        Ret_e = RC_OK;

        switch(f_msgID_u16)
        {
            case APPSIG_CAN_MSG_LGC_HC_CMD_POSITION:
            {
                t_sHC_PosCmdQueueElem buffPos_s;
                t_eHC_CmdPosType cmdType_e;

                if((f_nbSignal_u8 != (t_uint8)6)
                || (f_signal_ae[0] != APPSIG_SIGNAL_LGC_HC_CMD_KNIFE_POS_X_ALPH_A)
                || (f_signal_ae[1] != APPSIG_SIGNAL_LGC_HC_CMD_KNIFE_POS_Y_ALPH_B)
                || (f_signal_ae[2] != APPSIG_SIGNAL_LGC_HC_CMD_KNF_POS_SPD_RPM)
                || (f_signal_ae[3] != APPSIG_SIGNAL_LGC_HC_CMD_CNTR_KNF_POS_SPD_RPM)
                || (f_signal_ae[4] != APPSIG_SIGNAL_LGC_HC_CMD_KNIFE_TYPE_ID)
                || (f_signal_ae[5] != APPSIG_SIGNAL_LGC_HC_CMD_KNIFE_POS_ID))
                {
                    ASSERT((t_uint16)f_nbSignal_u8);
                }
                else if(f_sigValue_af32[4] >= (t_float32)HC_CMD_TYPE_POS_NB)
                {
                    ASSERT((t_uint16)f_sigValue_af32[4]);
                }
                else 
                {
                    cmdType_e = (t_eHC_CmdPosType)f_sigValue_af32[4];
                    if(cmdType_e == HC_CMD_TYPE_POS_CARTH)
                    {
                        buffPos_s.Pos_u.Carth_s.x_mm =  f_sigValue_af32[0];
                        buffPos_s.Pos_u.Carth_s.y_mm =  f_sigValue_af32[1];
                    }
                    else // HC_CMD_TYPE_POS_JOINT
                    {
                        buffPos_s.Pos_u.Joint_s.alpha_b_mrad =  f_sigValue_af32[0];
                        buffPos_s.Pos_u.Joint_s.alpha_c_mrad =  f_sigValue_af32[1];
                    }

                    buffPos_s.speed_s.knifeSpd_rpm = f_sigValue_af32[2];
                    buffPos_s.speed_s.cntrKnifeSpd_rpm =f_sigValue_af32[3];
                    buffPos_s.cmdPosType_e = cmdType_e; // f_sigValue_af32[4]
                    buffPos_s.timeStampID_u32 = (t_uint32)f_sigValue_af32[5];
                    
                    Ret_e = LIBQUEUE_WriteElement(  &g_QueueCmdPosRcvMngmt_s,
                                                    &buffPos_s,
                                                    sizeof(t_sHC_PosCmdQueueElem));
                    if(Ret_e != RC_OK)
                    {
                        ASSERT((t_uint16)Ret_e);
                    }
                    else if(g_FlagPosCmdPending_b == FALSE)
                    {
                        g_FlagPosCmdPending_b = TRUE;
                    }
                }
            }
            break;
            case APPSIG_CAN_MSG_LGC_HC_CMD_CALIBRATION:
            {
                // 0 appsns_id, 1:req_state 2:pulse 3:speed
                t_eAPPSNS_SnsInterface sigSnsID_e;
                t_eHC_AxeHandleList axeHdleHead_e;
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
                    
                    if(sigSnsID_e == APPSNS_SNSITF_ECDR_HD_CNTR_KNF_POS)
                    {
                        axeHdleHead_e = HC_AXE_HD_CNTR_KNFE;
                    }
                    else if(sigSnsID_e == APPSNS_SNSITF_ECDR_HD_KNF_POS)
                    {
                        axeHdleHead_e = HC_AXE_HD_KNFE;
                    }
                    else if(sigSnsID_e == APPSNS_SNSITF_ECDR_HD_HOLD_POS)
                    {
                        axeHdleHead_e = HC_AXE_HD_HOLD_KNFE;
                    }
                    else 
                    {
                        Ret_e = RC_ERROR_PARAM_INVALID;
                        ASSERT((t_uint16)sigSnsID_e);
                    }
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
                            g_calibCmdInfo_s.axeHead_e = axeHdleHead_e;
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
                break;
            }
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

                    if(agent_e != APPLGC_AGENT_HEAD_CUTTER)
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

    FMKSRL_LOG( "[HC] : Receive msg CAN -> %d, Retcode %d\r\n",
                f_msgID_u16,
                Ret_e);

    return;
}
/*********************************
 * s_HC_DebugRoutine
 *********************************/
static void s_HC_DebugRoutine(void)
{
    t_eReturnCode Ret_e;

    Ret_e = APPSIG_SetSignalValue(  APPSIG_SIGNAL_LGC_HC_FB_AXE_X_POS,
                                    g_KnifeTipCurr_s.carthPos_s.x_mm);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_SetSignalValue(  APPSIG_SIGNAL_LGC_HC_FB_AXE_Y_POS,
                                        g_KnifeTipCurr_s.carthPos_s.y_mm);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_SetSignalValue(  APPSIG_SIGNAL_LGC_HC_FB_ALPHA_B_ANGLE,
                                        g_KnifeTipCurr_s.jointAng_s.alpha_b_mrad);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_SetSignalValue(  APPSIG_SIGNAL_LGC_HC_FB_ALPHA_C_ANGLE,
                                        g_KnifeTipCurr_s.jointAng_s.alpha_c_mrad);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_SetSignalValue(  APPSIG_SIGNAL_LGC_HC_FSM_STS,
                                        (t_float32)g_Fsm_PrdcTskSts_e);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSIG_SetSignalValue(  APPSIG_SIGNAL_LGC_HC_FSM_OPE_STS,
                                        (t_float32)g_Fsm_PrdTsk_OpeSts_e);
    }
    if(Ret_e != RC_OK)
    {
        ASSERT((t_uint16)Ret_e);
    }
    return;
}

/*********************************
 * s_HC_ComputeCarthesianFromAngle
 *********************************/
static t_eReturnCode s_HC_ComputeCarthesianFromAngle(   t_float32 f_alphaB_mrad,
                                                        t_float32 f_alphaC_mrad,
                                                        t_float32 * f_posX_pmm,
                                                        t_float32 * f_posY_pmm)
{
    t_eReturnCode Ret_e;

    //---- parameter for head ----//
    t_uAPPSPM_PrmValType prmLenghtHeadMm_u;
    t_uAPPSPM_PrmValType prmLenghtKnifeMm_u;
    t_uAPPSPM_PrmValType prmLenghtCntrKnifeMm_u;

    //---- variable for compute ----//
    t_float32 alphaB_rad_f32 = f_alphaB_mrad / 1000.0F;
    t_float32 alphaC_rad_f32 = f_alphaC_mrad / 1000.0F;
    t_float32 cosAlphaB_f32;
    t_float32 sinAlphaB_f32;
    t_float32 cosAlphaC_f32;
    t_float32 sinAlphaC_f32;

    if((f_posX_pmm == NULL)
    || (f_posY_pmm == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
        ASSERT((t_uint16)0);
    }
    else 
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_LEN_FROM_REFA_TO_REFB, &prmLenghtHeadMm_u);
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_LEN_HEAD_KNIFE, &prmLenghtKnifeMm_u);
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_LEN_HEAD_CNTR_KNIFE, &prmLenghtCntrKnifeMm_u);
        }
        if(Ret_e == RC_OK)
        {
            //---- convention 
            //      - alplha in milliradian 
            //      - x,y en millimètre ----//
            cosAlphaB_f32 = cosf(alphaB_rad_f32);
            sinAlphaB_f32 = sinf(alphaB_rad_f32);
            cosAlphaC_f32 = cosf(alphaC_rad_f32);
            sinAlphaC_f32 = sinf(alphaC_rad_f32);
            *f_posX_pmm = (
                  (t_float32)prmLenghtHeadMm_u.prmVal_u16
                + (t_float32)prmLenghtCntrKnifeMm_u.prmVal_u16 * cosAlphaB_f32
                - (t_float32)prmLenghtKnifeMm_u.prmVal_u16 * ((cosAlphaC_f32 * cosAlphaB_f32) + (sinAlphaC_f32 * sinAlphaB_f32))
            );

            *f_posY_pmm = (
                -(t_float32)prmLenghtCntrKnifeMm_u.prmVal_u16 * sinAlphaB_f32
                + (t_float32)prmLenghtKnifeMm_u.prmVal_u16 * ((cosAlphaC_f32 * sinAlphaB_f32) - (sinAlphaC_f32 * cosAlphaB_f32))
            );
        }
    }

    return Ret_e;
}

/*********************************
 * s_HC_ComputeCarthesianFromAngle
 *********************************/
static t_eReturnCode s_HC_ComputeAngleFromCarthesian(   t_float32 f_posX_mm,
                                                        t_float32 f_posY_mm,
                                                        t_float32 * f_alphaB_pmrad,
                                                        t_float32 * f_alphaC_pmrad)
{
    t_eReturnCode Ret_e;

    //---- parameter for head ----//
    t_uAPPSPM_PrmValType prmLenghtHeadMm_u;
    t_uAPPSPM_PrmValType prmLenghtKnifeMm_u;
    t_uAPPSPM_PrmValType prmLenghtCntrKnifeMm_u;

    if((f_alphaB_pmrad == NULL)
    || (f_alphaC_pmrad == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
        ASSERT((t_uint16)0);
    }
    else 
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_LEN_FROM_REFA_TO_REFB, &prmLenghtHeadMm_u);
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_LEN_HEAD_KNIFE, &prmLenghtKnifeMm_u);
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_LEN_HEAD_CNTR_KNIFE, &prmLenghtCntrKnifeMm_u);
        }
        if(Ret_e == RC_OK)
        {
            const t_float32 cntrKnfeLen_f32 = (t_float32)prmLenghtCntrKnifeMm_u.prmVal_u16;
            const t_float32 KnfeLen_f32 = (t_float32)prmLenghtKnifeMm_u.prmVal_u16;
            const t_float32 headLen_f32 = (t_float32)prmLenghtHeadMm_u.prmVal_u16;
            const t_float32 x_mm_f32 = (t_float32)(f_posX_mm - headLen_f32);
            const t_float32 y_mm_f32 = (t_float32)(f_posY_mm - 0.0f);
            const t_float32 r2_f32 = (x_mm_f32 * x_mm_f32) + (y_mm_f32 * y_mm_f32);
            const t_float32 den_f32 = 2.0f * cntrKnfeLen_f32 * KnfeLen_f32;

            t_float32 cos_q2_f32;
            t_float32 cos_q2_raw_f32;
            t_float32 sin_q2_abs_f32;
            t_float32 sin_q2_f32;
            t_float32 phi_rad_f32;
            t_float32 q1_rad_f32;

            t_float32 b1_rad_f32;
            t_float32 c1_rad_f32;
            t_float32 b2_rad_f32;
            t_float32 c2_rad_f32;

            t_float32 err1_f32;
            t_float32 err2_f32;

            /* cos(q2) = (r^2 - L1^2 - L2^2) / (2 L1 L2) */
            cos_q2_raw_f32 = (r2_f32 - (cntrKnfeLen_f32 * cntrKnfeLen_f32) - (KnfeLen_f32 * KnfeLen_f32))
                           / den_f32;
            if((den_f32 <= 0.0f)
            || (cos_q2_raw_f32 > 1.0001f)
            || (cos_q2_raw_f32 < -1.0001f))
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }

            cos_q2_f32 = cos_q2_raw_f32;
            if(cos_q2_f32 > 1.0f)  { cos_q2_f32 = 1.0f; }
            if(cos_q2_f32 < -1.0f) { cos_q2_f32 = -1.0f; }

            if(Ret_e == RC_OK)
            {
                sin_q2_abs_f32 = sqrtf(fmaxf(0.0f, 1.0f - (cos_q2_f32 * cos_q2_f32)));
                phi_rad_f32 = atan2f(y_mm_f32, x_mm_f32);

                /* ---------------- Branche 1 : elbow = +1 ---------------- */
                sin_q2_f32 = (+1.0f) * sin_q2_abs_f32;
                q1_rad_f32 = phi_rad_f32
                        - atan2f((KnfeLen_f32 * sin_q2_f32),
                                    (cntrKnfeLen_f32 + (KnfeLen_f32 * cos_q2_f32)));

                b1_rad_f32 = -q1_rad_f32; /* convention CW */

                {
                    const t_float32 cb_f32 = cosf(b1_rad_f32);
                    const t_float32 sb_f32 = sinf(b1_rad_f32);

                    const t_float32 vAC_local_x_f32 = (cb_f32 * x_mm_f32) - (sb_f32 * y_mm_f32);
                    const t_float32 vAC_local_y_f32 = (sb_f32 * x_mm_f32) + (cb_f32 * y_mm_f32);

                    const t_float32 vBC_local_x_f32 = vAC_local_x_f32 - cntrKnfeLen_f32;
                    const t_float32 vBC_local_y_f32 = vAC_local_y_f32;

                    c1_rad_f32 = atan2f(-vBC_local_y_f32, -vBC_local_x_f32);
                }

                /* ---------------- Branche 2 : elbow = -1 ---------------- */
                sin_q2_f32 = (-1.0f) * sin_q2_abs_f32;
                q1_rad_f32 = phi_rad_f32
                        - atan2f((KnfeLen_f32 * sin_q2_f32),
                                    (cntrKnfeLen_f32 + (KnfeLen_f32 * cos_q2_f32)));

                b2_rad_f32 = -q1_rad_f32;

                {
                    const t_float32 cb_f32 = cosf(b2_rad_f32);
                    const t_float32 sb_f32 = sinf(b2_rad_f32);

                    const t_float32 vAC_local_x_f32 = (cb_f32 * x_mm_f32) - (sb_f32 * y_mm_f32);
                    const t_float32 vAC_local_y_f32 = (sb_f32 * x_mm_f32) + (cb_f32 * y_mm_f32);

                    const t_float32 vBC_local_x_f32 = vAC_local_x_f32 - cntrKnfeLen_f32;
                    const t_float32 vBC_local_y_f32 = vAC_local_y_f32;

                    c2_rad_f32 = atan2f(-vBC_local_y_f32, -vBC_local_x_f32);
                }

                /* Choix de branche IK :
                 * 1) priorite a la solution ou le point B (counter-knife) est a droite du tip cible
                 * 2) sinon (ambigu), prendre l'alpha_b le plus petit
                 * 3) fallback final sur l'erreur FK minimale
                 */
                {
                    t_float32 x1_f32;
                    t_float32 y1_f32;
                    t_float32 x2_f32;
                    t_float32 y2_f32;
                    t_float32 xB1_f32;
                    t_float32 xB2_f32;
                    t_uint8 b1IsRight_u8;
                    t_uint8 b2IsRight_u8;
                    const t_float32 rightEps_mm_f32 = 0.001F;
                    t_uint8 selectBranch2_u8 = 0u;

                    (void)s_HC_ComputeCarthesianFromAngle((b1_rad_f32 * 1000.0f), (c1_rad_f32 * 1000.0f), &x1_f32, &y1_f32);
                    (void)s_HC_ComputeCarthesianFromAngle((b2_rad_f32 * 1000.0f), (c2_rad_f32 * 1000.0f), &x2_f32, &y2_f32);

                    err1_f32 = ((x1_f32 - f_posX_mm) * (x1_f32 - f_posX_mm))
                            + ((y1_f32 - f_posY_mm) * (y1_f32 - f_posY_mm));

                    err2_f32 = ((x2_f32 - f_posX_mm) * (x2_f32 - f_posX_mm))
                            + ((y2_f32 - f_posY_mm) * (y2_f32 - f_posY_mm));

                    xB1_f32 = headLen_f32 + (cntrKnfeLen_f32 * cosf(b1_rad_f32));
                    xB2_f32 = headLen_f32 + (cntrKnfeLen_f32 * cosf(b2_rad_f32));

                    b1IsRight_u8 = (xB1_f32 >= (f_posX_mm - rightEps_mm_f32)) ? 1u : 0u;
                    b2IsRight_u8 = (xB2_f32 >= (f_posX_mm - rightEps_mm_f32)) ? 1u : 0u;

                    if((b1IsRight_u8 == 1u)
                    && (b2IsRight_u8 == 0u))
                    {
                        selectBranch2_u8 = 0u;
                    }
                    else if((b1IsRight_u8 == 0u)
                    && (b2IsRight_u8 == 1u))
                    {
                        selectBranch2_u8 = 1u;
                    }
                    else if(b2_rad_f32 < b1_rad_f32)
                    {
                        selectBranch2_u8 = 1u;
                    }
                    else if(b1_rad_f32 < b2_rad_f32)
                    {
                        selectBranch2_u8 = 0u;
                    }
                    else if(err2_f32 < err1_f32)
                    {
                        selectBranch2_u8 = 1u;
                    }

                    if(selectBranch2_u8 == 1u)
                    {
                        b1_rad_f32 = b2_rad_f32;
                        c1_rad_f32 = c2_rad_f32;
                    }
                }

                /* wrap [-pi, pi] en milli-radian */
                {
                    t_float32 b_mrad_f32 = b1_rad_f32 * 1000.0f;
                    t_float32 c_mrad_f32 = c1_rad_f32 * 1000.0f;

                    while(b_mrad_f32 > CST_PI_MRAD)  { b_mrad_f32 -= CST_2PI_MRAD; }
                    while(b_mrad_f32 < -CST_PI_MRAD) { b_mrad_f32 += CST_2PI_MRAD; }

                    while(c_mrad_f32 > CST_PI_MRAD)  { c_mrad_f32 -= CST_2PI_MRAD; }
                    while(c_mrad_f32 < -CST_PI_MRAD) { c_mrad_f32 += CST_2PI_MRAD; }

                    *f_alphaB_pmrad = b_mrad_f32;
                    *f_alphaC_pmrad = c_mrad_f32;
                }
            }
        }

    }

    return Ret_e;
}

/*********************************
 * s_HC_ComputePulseFromAngle
 *********************************/
static t_eReturnCode s_HC_ComputePulseFromAngle(t_float32 f_alphaB_mrad,
                                                t_float32 f_alphaC_mrad,
                                                t_float32 * f_pulseKnf_pf32,
                                                t_float32 * f_pulseCntrKnf_pf32)
{
    t_eReturnCode Ret_e;

    //---- prm pulse per radian ----//
    t_uAPPSPM_PrmValType prmPulsePerRadKnf_u;
    t_uAPPSPM_PrmValType prmPulsePerRadCntrKnf_u;

    if((f_pulseKnf_pf32 == NULL)
    || (f_pulseCntrKnf_pf32 == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
        ASSERT((t_uint16)0);
    }
    else 
    {
        //---- 1- get pulse per radian parameter ----//
        Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_KNIFE_PULSE_TO_RAD, &prmPulsePerRadKnf_u);
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_CNTR_KNIFE_PULSE_TO_RAD, &prmPulsePerRadCntrKnf_u);
        }
        if(Ret_e == RC_OK)
        {
            //---- 2- get pulse per radian parameter ----//
            //---- parameter give the pulse for 2PI radian ----//
            *f_pulseKnf_pf32 = (
                  f_alphaC_mrad 
                * (t_float32)prmPulsePerRadKnf_u.prmVal_u16
                / CST_2PI_MRAD
            );
            *f_pulseCntrKnf_pf32 = (
                f_alphaB_mrad
                * (t_float32)prmPulsePerRadCntrKnf_u.prmVal_u16
                / CST_2PI_MRAD
            );
        }
    }

    return Ret_e;
}
/*********************************
 * s_HC_ComputeAnglefromPulse
 *********************************/
static t_eReturnCode s_HC_ComputeAnglefromPulse( t_sint32 f_pulseKnf_s32,
                                                t_sint32 f_pulseCntrKnf_s32,
                                                t_float32 * f_alphaB_pmrad,
                                                t_float32 * f_alphaC_pmrad)
{
    t_eReturnCode Ret_e;
    t_uAPPSPM_PrmValType prmPulsePerRadKnf_u;
    t_uAPPSPM_PrmValType prmPulsePerRadCntrKnf_u;

    if((f_alphaB_pmrad == NULL)
    || (f_alphaC_pmrad == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
        ASSERT((t_uint16)0);
    }
    else
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_KNIFE_PULSE_TO_RAD, &prmPulsePerRadKnf_u);
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_CNTR_KNIFE_PULSE_TO_RAD, &prmPulsePerRadCntrKnf_u);
        }
        if((Ret_e == RC_OK)
        && (prmPulsePerRadKnf_u.prmVal_u16 > (t_uint16)0)
        && (prmPulsePerRadCntrKnf_u.prmVal_u16 > (t_uint16)0))
        {
            *f_alphaB_pmrad = ((t_float32)f_pulseCntrKnf_s32 * CST_2PI_MRAD)
                            / (t_float32)prmPulsePerRadKnf_u.prmVal_u16;
            *f_alphaC_pmrad = ((t_float32)f_pulseKnf_s32 * CST_2PI_MRAD)
                            / (t_float32)prmPulsePerRadCntrKnf_u.prmVal_u16;
        }
        else if(Ret_e == RC_OK)
        {
            Ret_e = RC_ERROR_WRONG_RESULT;
            ASSERT((t_uint16)0);
        }
    }

    return Ret_e;
}
/*********************************
 * s_HC_CheckPositionValidity
 *********************************/
static t_eReturnCode s_HC_CheckPositionValidity(t_sHC_CarthPos f_carthPos_s)
{
    t_eReturnCode Ret_e;

    t_uAPPSPM_PrmValType prmPosXMax_u;
    t_uAPPSPM_PrmValType prmPosYMax_u;
    t_uAPPSPM_PrmValType prmPosXMin_u;
    t_uAPPSPM_PrmValType prmPosYMin_u;

    Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_TIP_KNIFE_POS_X_MAX_MM, &prmPosXMax_u);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_TIP_KNIFE_POS_Y_MAX_MM, &prmPosYMax_u);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_TIP_KNIFE_POS_X_MIN_MM, &prmPosXMin_u);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_TIP_KNIFE_POS_Y_MIN_MM, &prmPosYMin_u);
    }
    if(Ret_e == RC_OK)
    {
        //---- comparing mm & mm ----//
        if((f_carthPos_s.x_mm > (t_float32)prmPosXMax_u.prmVal_s16)
        || (f_carthPos_s.x_mm < (t_float32)prmPosXMin_u.prmVal_s16))
        {
            Ret_e = RC_ERROR_LIMIT_REACHED;
            ASSERT((t_uint16)f_carthPos_s.x_mm);
            APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_HEAD_TIP_KNIVE_POS_LIMIT_ERROR,
                                    APPSDM_DIAG_ITEM_REPORT_FAIL,
                                    (t_uint16)f_carthPos_s.x_mm,
                                    (t_uint16)0);
        }
        else if((f_carthPos_s.y_mm > (t_float32)prmPosYMax_u.prmVal_s16)
        ||      (f_carthPos_s.y_mm < (t_float32)prmPosYMin_u.prmVal_s16))
        {
            Ret_e = RC_ERROR_LIMIT_REACHED;
            ASSERT((t_uint16)f_carthPos_s.y_mm);
            APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_HEAD_TIP_KNIVE_POS_LIMIT_ERROR,
                                    APPSDM_DIAG_ITEM_REPORT_FAIL,
                                    (t_uint16)0,
                                    (t_uint16)f_carthPos_s.y_mm);
        }
        else 
        {
            Ret_e = RC_OK;
        }
    }

    return Ret_e;
}

/*********************************
 * s_HC_CheckAngleAssociationValidity
 *********************************/
static t_eReturnCode s_HC_CheckAngleAssociationValidity(t_float32 f_alphaB_mrad,
                                                        t_float32 f_alphaC_mrad)
{
    t_eReturnCode Ret_e;
    t_float32 posX_mm_f32 = 0.0F;
    t_float32 posY_mm_f32 = 0.0F;

    t_uAPPSPM_PrmValType prmLenghtHeadMm_u;
    t_uAPPSPM_PrmValType prmLenghtKnifeMm_u;
    t_uAPPSPM_PrmValType prmLenghtCntrKnifeMm_u;

    t_float32 relX_mm_f32;
    t_float32 relY_mm_f32;
    t_float32 distAC_mm_f32;
    t_float32 minReach_mm_f32;
    t_float32 maxReach_mm_f32;
    const t_float32 distTol_mm_f32 = 0.5F;

    Ret_e = s_HC_ComputeCarthesianFromAngle(f_alphaB_mrad,
                                            f_alphaC_mrad,
                                            &posX_mm_f32,
                                            &posY_mm_f32);
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_LEN_FROM_REFA_TO_REFB, &prmLenghtHeadMm_u);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_LEN_HEAD_KNIFE, &prmLenghtKnifeMm_u);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPSPM_GetParam(APPSPM_PRM_HC_LEN_HEAD_CNTR_KNIFE, &prmLenghtCntrKnifeMm_u);
    }
    if(Ret_e == RC_OK)
    {
        relX_mm_f32 = posX_mm_f32 - (t_float32)prmLenghtHeadMm_u.prmVal_u16;
        relY_mm_f32 = posY_mm_f32;
        distAC_mm_f32 = sqrtf((relX_mm_f32 * relX_mm_f32) + (relY_mm_f32 * relY_mm_f32));
        minReach_mm_f32 = fabsf((t_float32)prmLenghtCntrKnifeMm_u.prmVal_u16
                                - (t_float32)prmLenghtKnifeMm_u.prmVal_u16);
        maxReach_mm_f32 = (t_float32)prmLenghtCntrKnifeMm_u.prmVal_u16
                        + (t_float32)prmLenghtKnifeMm_u.prmVal_u16;

        if((distAC_mm_f32 < (minReach_mm_f32 - distTol_mm_f32))
        || (distAC_mm_f32 > (maxReach_mm_f32 + distTol_mm_f32))
        || (posY_mm_f32 > (t_float32)(0.0F + distTol_mm_f32)))
        {
            Ret_e = RC_ERROR_LIMIT_REACHED;
            APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_HEAD_TIP_KNIVE_POS_LIMIT_ERROR,
                                    APPSDM_DIAG_ITEM_REPORT_FAIL,
                                    (t_uint16)f_alphaB_mrad,
                                    (t_uint16)f_alphaC_mrad);
            ASSERT((t_uint16)Ret_e);
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

