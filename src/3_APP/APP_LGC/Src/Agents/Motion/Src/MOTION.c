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
#include "./MOTION.h"


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
// ///@brief Finite State Machine for Periodic Task
// typedef enum 
// {
//     HC_FSM_PRD_TSK_CFG = 0,           //---- Fsm for configuration ----//
//     HC_FSM_PRD_TSK_PRE_OPS,           //---- Fsm for pre operational ----//
//     HC_FSM_PRD_TSK_OPS,               //---- Fsm for operational ----//
//     HC_FSM_PRD_TSK_CALIB_AXE,         //---- Fsm for calibration ----//
//     HC_FSM_PRD_TSK_SAFETY,            //---- Fsm for safety ----//
//     HC_FSM_PRD_TSK_ERROR,             //---- Fsm for error ----//
// } t_eHC_FsmPeriodicTask;

// ///@brief Finite State Machine for Periodic Task Sub State Calibration
// typedef enum 
// {
//     HC_FSM_PRDTSK_CALIB_INIT = 0,       //--- Fsm for Calibration initialization -----//
//     HC_FSM_PRDTSK_CALIB_KNIFE,          //--- Fsm for Calibration head knife -----//
//     HC_FSM_PRDTSK_CALIB_CNTR_KNIFE,     //--- Fsm for Calibration head coutner knife -----//
//     HC_FSM_PRDTSK_CALIB_HOLD_KNIFE,     //--- Fsm for Calibration head hold knife -----//
// } t_eHC_FsmPrdTsk_Calib;

// typedef enum 
// {
//     HC_FSM_PRDTSK_CALIB_OPE_STOP_AXE = 0,     //----Fsm for calibration, sub state axe xxx -> stop axe ----//
//     HC_FSM_PRDTSK_CALIB_OPE_MOVE_AXE,         //----Fsm for calibration, sub state axe xxx -> move axe ----//
//     HC_FSM_PRDTSK_CALIB_OPE_WAIT_AXE,         //----Fsm for calibration, sub state axe xxx -> wait axe ----//
//     HC_FSM_PRDTSK_CALIB_OPE_OFFSET_AXE,       //----Fsm for calibration, sub state axe xxx -> wait axe ----//
// } t_eHC_FsmPrdTsk_CalibOpe;

// ///@brief Finite State Machine for Periodic Task Sub State Operational
// typedef enum 
// {
//     HC_FSM_PRDTSK_OPE_IDLE =  0,      //---- Fsm for Operational state, subState Idle ----//
//     HC_FSM_PRDTSK_OPE_CMD_CHECK,      //---- Fsm for Operational state, subState check command ----//
//     HC_FSM_PRDTSK_OPE_CMD_PROCESS,    //---- Fsm for Operational state, subState process command ----//
// } t_eHC_FsmPrdTsk_Ope;
// /* CAUTION : Automatic generated code section : Start */

// /* CAUTION : Automatic generated code section : End */
// //-----------------------------TYPEDEF TYPES---------------------------//
// ///@brief calib waiting information 
// typedef struct 
// {
//     t_uint32 startWait_u32;         //---- store the Tick where we start to wait the axes to go to the setpoint ----//
//     t_uint32 maxTimeWait_u32;       //---- Store the amount of time this is suspicious that the axe has not reach the set point yet ----//
// } t_sHC_CalibWaitInfo;

// ///@brief carthesian position 
// typedef struct 
// {
//     t_float32 x_f32;                //---- position x of the axe
//     t_float32 y_f32;                //---- position y of the axe

// } t_sHC_CarthPos;

// ///@brief calibration information
// typedef struct 
// {
//     t_eAPPSNS_SnsInterface snsItf_e;            //---- calibration ongoing ----//
//     t_float32 pulses_f32;                       //---- requested pulse for calibration ----//
//     t_float32 speed_f32;                        //---- requested speed for calibration ----//
//     t_eAPPLGC_CalibStatus reqSts_e;             //---- calibration requested from application ----//
//     t_eAPPLGC_CalibStatus currSts_e;            //---- calibration requested from application ----//
// } t_sHC_CalibCmdInfo;

// ///@brief Rearmament info 
// typedef struct 
// {
//     t_eAPPLGC_RearmType rearmType_e;          //---- rearmament type ----//
//     t_bool reqRearm_b;                      //--- rearmament is requested ----//
// } t_sHC_RearmInfo;
// // ********************************************************************
// // *                      Prototypes
// // ********************************************************************

// // ********************************************************************
// // *                      Variables
// // ********************************************************************
// ///@brief the current position of the head
// static t_sHC_CarthPos g_axeCurrPos_s;

// ///@brief the position compute or expected of the head
// static t_sHC_CarthPos g_axeComputePos_s;

// /// @brief What encoder says the position is
// static t_sHC_CarthPos g_AxesFeedbackPos_s;

// /// @brief Pulses which are missed by the motor axes
// static t_float32 g_axeMissPulses_af32[HC_AXE_HD_NB];


// ///@brief Finite State Machine Variables
// static t_eHC_FsmPeriodicTask g_Fsm_PrdcTskSts_e;
// static t_eHC_FsmPrdTsk_Calib g_Fsm_PrdTsk_CalibSts_e;
// static  t_eHC_FsmPrdTsk_Ope g_Fsm_PrdTsk_OpeSts_e;
// static t_eHC_FsmPrdTsk_CalibOpe g_Fsm_PrdTsk_CalibOpeSts_ae[HC_AXE_HD_NB];
// static t_eHC_FsmPrdTsk_Ope g_Fsm_PrdTsk_OpeCmdPrcssSts_e;

// ///@brief Command Queue Variables
// static t_sLIBQUEUE_QueueCore g_QueueCmdPosRcvMngmt_s;
// static t_sLIBQUEUE_QueueCore g_QueueCmdIterRcvMngmt_s[HC_AXE_HD_NB];
// static t_sHC_CarthPos g_BufferCmdPosRcv_as[HC_CMD_POS_RCV_BUFFER_LEN];
// static t_sHC_MtrCmdIterPayload g_BufferCmdMtrIter_as[HC_AXE_HD_NB][HC_CMD_ITER_BUFFER_LEN];

// ///@brief At least one Rcv Command is on the Queue
// static t_bool g_FlagRcvPosCmd_b = FALSE;
// ///@brief At least one Iter Command is on the Queue
// static t_bool g_FlagIterCmdReady_b = FALSE;
// ///@brief One Position cmd cannot be pushed inside PosQueue
// static t_bool g_FlagPosCmdPending_b = FALSE;

// ///@brief Time Max to wait for the axe to go to the calibration point 
// static t_sSafeMem_BlockInfo g_sfmb_calibInfoCmd_s;
// static t_sHC_CalibCmdInfo g_calibCmdInfo_s;

// ///@brief Information for rearmament 
// static t_sHC_RearmInfo g_RearmInfo_s; 
// /* CAUTION : Automatic generated code section for Variable: Start */
// /* CAUTION : Automatic generated code section for Variable: End */
// //********************************************************************************
// //                      Local functions - Prototypes
// //********************************************************************************
// /**
//  * @brief State Machine of the Agent.
//  * @brief This function check if motors are in a logic state
//  * ----------------------------------------------------------------------------
//  * @return @ref t_eReturnCode
//  */
// static t_eReturnCode s_HC_StateMachine(void);
// /**
//  * @brief Function called every cyclic to check motor.
//  * @details This function check if motors are in a logic state
//  * ----------------------------------------------------------------------------
//  * @return @ref t_eReturnCode
//  */
// static t_eReturnCode s_HC_SafetyUpdate(void);
// /**
//  * @brief Update the current position of each axes
//  * @details This function checck if encoder option are one,
//  *          if there is for each axes, this function read the ecdr position
//  *          compare it to the position compute 
//  * 
//  * ----------------------------------------------------------------------------
//  * @return @ref t_eReturnCode
//  */
// static t_eReturnCode s_HC_UpdatePosition(void);
// /**
//  * @brief This function handle the configuration state of State Machine
//  * @details Not much happen for now in this function
//  * ----------------------------------------------------------------------------
//  * @return RC_OK : The state finish, pass to new state from fsm
//  * @return RC_WARNNING_PENDING : The State is on going 
//  * @return ohters : @ref t_eReturnCode
//  */
// static t_eReturnCode s_HC_Fsm_PrdTsk_Configuration(void);
// /**
//  * @brief This function handle the calibration state of State Machine
//  * ----------------------------------------------------------------------------
//  * @return RC_OK : The state finish, pass to new state from fsm
//  * @return RC_WARNNING_PENDING : The State is on going 
//  * @return ohters : @ref t_eReturnCode
//  */
// static t_eReturnCode s_HC_Fsm_PrdTsk_Calibration(void);
// /**
//  * @brief This function handle the Operation state of State Machine
//  * ----------------------------------------------------------------------------
//  * @return RC_OK : The state finish, pass to new state from fsm
//  * @return RC_WARNNING_PENDING : The State is on going 
//  * @return ohters : @ref t_eReturnCode
//  */
// static t_eReturnCode s_HC_Fsm_PrdTsk_PreOperational(void);
// /**
//  * @brief This function handle the Operation state of State Machine
//  * ----------------------------------------------------------------------------
//  * @return RC_OK : The state finish, pass to new state from fsm
//  * @return RC_WARNNING_PENDING : The State is on going 
//  * @return ohters : @ref t_eReturnCode
//  */
// static t_eReturnCode s_HC_Fsm_PrdTsk_Operational(void);
// /**
//  * @brief This function handle the Safety state of State Machine
//  * ----------------------------------------------------------------------------
//  * @return RC_OK : The state finish, pass to new state from fsm
//  * @return RC_WARNNING_PENDING : The State is on going 
//  * @return ohters : @ref t_eReturnCode
//  */
// static t_eReturnCode s_HC_Fsm_PrdTsk_Safety(void);
// /**
//  * @brief This function handle the Error state of State Machine
//  * ----------------------------------------------------------------------------
//  * @return RC_OK : The state finish, pass to new state from fsm
//  * @return RC_WARNNING_PENDING : The State is on going 
//  * @return ohters : @ref t_eReturnCode
//  */
// static t_eReturnCode s_HC_Fsm_PrdTsk_Error(void);
// /**
//  * @brief Enable the motor axes
//  * 
//  * ----------------------------------------------------------------------------
//  * @param[in] f_idxAxe_e : axe to get informatio on
//  * ----------------------------------------------------------------------------
//  * @return @ref t_eReturnCode
//  */
// static t_eReturnCode s_GTRY_EnableAxe(t_eHC_AxeHandleList f_idxAxe_e);
// /**
//  * @brief Hard Stop for all Axes Motor
//  * @details This function Set an hard stop, means pin enable se to 1
//  *             to release torque on each axes, this function also check if action 
//  *              has to be made before hard stop motor
//  * 
//  * ----------------------------------------------------------------------------
//  * @param[in] f_idxAxe_e : axe to get informatio on
//  * ----------------------------------------------------------------------------
//  * @return @ref t_eReturnCode
//  */
// static t_eReturnCode s_GTRY_HardAxeStop(t_eHC_AxeHandleList f_idxAxe_e);
// /**
//  * @brief This function handle the reception of signals from APPSIG
//  * ----------------------------------------------------------------------------
//  * @param[in] f_signal_e : signal ID
//  * @param[in] f_sigVal_f32 :signl; value
//  * ----------------------------------------------------------------------------
//  * @return void
//  */
// static void s_HC_MsgReceptionCallback(  t_uint16 f_msgID_u16,
//                                         t_uint8 f_nbSignal_u8,
//                                         t_eAPPSIG_Signal *f_signal_ae, 
//                                         t_float32 *f_sigValue_af32);
// /**
//  * @brief Update the current position of each axes
//  * @details This function checck if encoder option are one,
//  *          if there is for each axes, this function read the ecdr position
//  *          compare it to the position compute 
//  *          It also get the missing pulse for each axe
//  * 
//  * ----------------------------------------------------------------------------
//  * @param[in] f_idxAxe_e : axe to get informatio on
//  * ----------------------------------------------------------------------------
//  * @return @ref t_eReturnCode
//  */
// static t_eReturnCode s_HC_UpdateAxePosition(t_eHC_AxeHandleList f_idxAxe_e);
// /**
//  * @brief Hard Stop for all Axes Motor
//  * @details This function Set an hard stop, means pin enable se to 1
//  *             to release torque on each axes, this function also check if action 
//  *              has to be made before hard stop motor
//  * 
//  * ----------------------------------------------------------------------------
//  * @param[in] f_idxAxe_e : axe to get informatio on
//  * ----------------------------------------------------------------------------
//  * @return @ref t_eReturnCode
//  */
// static t_eReturnCode s_GTRY_AxeStop(t_eHC_AxeHandleList f_idxAxe_e, t_bool f_isHardStop_b);
// /**
//  * @brief Enable the motor axes
//  * 
//  * ----------------------------------------------------------------------------
//  * @param[in] f_idxAxe_e : axe to get informatio on
//  * ----------------------------------------------------------------------------
//  * @return @ref t_eReturnCode
//  */
// static t_eReturnCode s_HC_EnableAxe(t_eHC_AxeHandleList f_idxAxe_e);
// /**
//  * @brief Send to the CL42T driver a command
//  * 
//  * ----------------------------------------------------------------------------
//  * @param[in] f_idxAxe_e : axe to set new position
//  * @param[in] f_setPoint_s32 : set point to reach (pulses)
//  * @param[in] f_speed_f32 : speed of the setpoint (frequency)
//  * @param[in] f_trigTiming_u32 : motor get the capabilities to store the command and set it in f_trigTiming_u32 ms
//  * ----------------------------------------------------------------------------
//  * @return RC_OK  : command set
//  * @return RC_WARNING_BUSY  : Health of the axe is not correct 
//  * @return others : @ref t_eReturnCode
//  */
// static t_eReturnCode s_HC_SetAxeSetPoint( t_eHC_AxeHandleList f_idxAxe_e, 
//                                             t_sint32 f_setPoint_s32,
//                                             t_float32 f_speed_f32, 
//                                             t_float32 f_trigTiming_u32);
// /**
//  * @brief Update Signal for debugging process
//  * 
//  * ----------------------------------------------------------------------------
//  * @return @ref t_eReturnCode
//  */
// static void s_GTRYDebugRoutine();

// //****************************************************************************
// //                      Public functions - Implementation
// //********************************************************************************
// /*********************************
//  * HEAD_CUTTER_Init
//  *********************************/
// t_eReturnCode HEAD_CUTTER_Init(void)
// {
//     t_eReturnCode Ret_e;
//     t_eHC_AxeHandleList idxAxe_e;
//     t_eHC_CmdSignals idxHcSig_e;
//     t_sLIBQUEUE_QueueCfg cmdPosFifoCfg_s;
//     t_sLIBQUEUE_QueueCfg cmdIterFifoCfg_s;

//     Ret_e = RC_OK;
//     for(idxAxe_e = HC_AXE_HEAD ; idxAxe_e < HC_AXE_HD_NB ; idxAxe_e++)
//     {
//         cmdIterFifoCfg_s.bufferHead_pv = &g_BufferCmdMtrIter_as[idxAxe_e];
//         cmdIterFifoCfg_s.bufferSize_u8 = HC_CMD_ITER_BUFFER_LEN;
//         cmdIterFifoCfg_s.elementSize_u8 = sizeof(t_sHC_MtrCmdIterPayload);
//         cmdIterFifoCfg_s.enableOverwrite_b = FALSE;
//         Ret_e = LIBQUEUE_Create(&g_QueueCmdIterRcvMngmt_s[idxAxe_e], cmdIterFifoCfg_s);

//         if(Ret_e == RC_OK)
//         {
//             g_axeMissPulses_af32[idxAxe_e] = 0.0f;
//         }
//     }
//     if(Ret_e == RC_OK)
//     {
//         for(idxHcSig_e = HC_CMD_MSGSIG_HEAD ; idxHcSig_e < HC_CDM_MSGSIG_NB ; idxHcSig_e++)
//         {
//             Ret_e = APPSIG_AddRcvMsgCallback(c_HC_MsgMapping_ae[idxHcSig_e], s_HC_MsgReceptionCallback);
//         }
//     }
//     if(Ret_e == RC_OK)
//     {
//         cmdPosFifoCfg_s.bufferHead_pv = &g_BufferCmdPosRcv_as[0];
//         cmdPosFifoCfg_s.bufferSize_u8 = HC_CMD_POS_RCV_BUFFER_LEN;
//         cmdPosFifoCfg_s.elementSize_u8 = sizeof(t_sHC_CarthPos);
//         cmdPosFifoCfg_s.enableOverwrite_b = FALSE;
//         Ret_e = LIBQUEUE_Create(&g_QueueCmdPosRcvMngmt_s, cmdPosFifoCfg_s);

//     }
//     if(Ret_e == RC_OK)
//     {
//         g_calibCmdInfo_s.pulses_f32 = 0.0F;
//         g_calibCmdInfo_s.speed_f32 = 0.0F;
//         g_calibCmdInfo_s.snsItf_e = APPSNS_SNSITF_NB;
//         g_calibCmdInfo_s.reqSts_e = LGC_CALIB_IDLE;
//         g_calibCmdInfo_s.currSts_e = LGC_CALIB_IDLE;
//         Ret_e = SMB_SecureBlockInit(&g_sfmb_calibInfoCmd_s,
//                                     &g_calibCmdInfo_s,
//                                     sizeof(t_sHC_CalibCmdInfo),
//                                     (t_uint8)5);
//     }
//     if(Ret_e == RC_OK)
//     {
//         g_axeComputePos_s.x_f32 = 0.0f;
//         g_axeComputePos_s.y_f32 = 0.0f;
//         g_axeComputePos_s.x_f32 = 0.0f;
//         g_axeComputePos_s.y_f32 = 0.0f;
//         g_AxesFeedbackPos_s.x_f32 = 0.0f;
//         g_AxesFeedbackPos_s.y_f32 = 0.0f;

//         g_RearmInfo_s.rearmType_e = LGC_REARM_TYPE_NB;
//         g_RearmInfo_s.reqRearm_b = FALSE;

//         g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_CFG;
//         g_Fsm_PrdTsk_CalibSts_e = HC_FSM_PRDTSK_CALIB_INIT;
//         g_Fsm_PrdTsk_OpeSts_e = HC_FSM_PRDTSK_OPE_IDLE;
//         g_Fsm_PrdTsk_CalibOpeSts_ae[HC_AXE_HD_KNFE] = HC_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
//         g_Fsm_PrdTsk_CalibOpeSts_ae[HC_AXE_HD_CNTR_KNFE] = HC_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
//         g_Fsm_PrdTsk_CalibOpeSts_ae[HC_AXE_HD_HOLD_KNFE] = HC_FSM_PRDTSK_CALIB_OPE_STOP_AXE;
//     }

//     return Ret_e;
// }

// /*********************************
//  * HEAD_CUTTER_PeriodicTask
//  *********************************/
// t_eReturnCode HEAD_CUTTER_PeriodicTask(void)
// {
//     t_eReturnCode Ret_e = RC_OK;
    
//      t_eReturnCode Ret_e;
    
//     //---- 1- Call Safety Update ----//
//     Ret_e = s_HC_SafetyUpdate();

//     //---- 2- Update Current position ----//
//     if(Ret_e == RC_OK)
//     {
//         Ret_e = s_HC_UpdatePosition();
//     }

//     //---- 3- Call State Machine ----//
//     if(Ret_e == RC_OK)
//     {
//         Ret_e = s_HC_StateMachine();
//     }

//     //---- 4- Debug Routine ----//
//     s_GTRYDebugRoutine();
//     return Ret_e;
//     return Ret_e;
// }

// // ********************************************************************
// // *                      Local Functions - Implementation
// // ********************************************************************
// /*********************************
//  * s_HC_StateMachine
//  *********************************/
// static t_eReturnCode s_HC_StateMachine(void)
// {
//     t_eReturnCode Ret_e;

//     switch(g_Fsm_PrdcTskSts_e)
//     {
//         case HC_FSM_PRD_TSK_CFG:
//             Ret_e = s_HC_Fsm_PrdTsk_Configuration();
//             if(Ret_e == RC_OK)
//             {
//                 g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_PRE_OPS;
//                 g_Fsm_PrdTsk_CalibSts_e = HC_FSM_PRDTSK_CALIB_INIT;
//             }
//             else if(Ret_e < RC_OK)
//             {
//                 g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_ERROR;
//             }
//         break;
//         case HC_FSM_PRD_TSK_PRE_OPS:
//             Ret_e = s_HC_Fsm_PrdTsk_PreOperational();
//             if(Ret_e == RC_OK)
//             {
//                 g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_OPS;
//             }
//         case HC_FSM_PRD_TSK_CALIB_AXE:
//             Ret_e = s_HC_Fsm_PrdTsk_Calibration();
//             if(Ret_e == RC_OK)
//             {
//                 g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_OPS;
//                 g_Fsm_PrdTsk_OpeSts_e = HC_FSM_PRDTSK_OPE_IDLE;
//             }
//             else if(Ret_e < RC_OK)
//             {
//                 g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_SAFETY;
//             }
//         break;
//         case HC_FSM_PRD_TSK_OPS:
//             Ret_e = s_HC_Fsm_PrdTsk_Operational();
//              if(Ret_e < RC_OK)
//             {
//                 g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_SAFETY;
//             }
//         break;
//         case HC_FSM_PRD_TSK_SAFETY:
//             Ret_e = s_HC_Fsm_PrdTsk_Safety();
//             if(Ret_e == RC_OK)
//             {
//                 g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_CFG;
//             }
//             else if(Ret_e < RC_OK)
//             {
//                 g_Fsm_PrdcTskSts_e = HC_FSM_PRD_TSK_ERROR;
//             }
//         break;
//         case HC_FSM_PRD_TSK_ERROR:
//             Ret_e = s_HC_Fsm_PrdTsk_Error();
//             //--- no way out ----//
//         default:
//             Ret_e = RC_ERROR_WRONG_STATE;
//         break;
//     }
// }

// /*********************************
//  * s_HC_Fsm_PrdTsk_Configuration
//  *********************************/
// static t_eReturnCode s_HC_Fsm_PrdTsk_Configuration(void)
// {
//     return RC_OK;
// }

// /*********************************
//  * s_HC_Fsm_PrdTsk_Calibration
//  *********************************/
// static t_eReturnCode s_HC_Fsm_PrdTsk_Calibration(void)
// {
//     return RC_OK;
// }

// /*********************************
//  * s_HC_Fsm_PrdTsk_PreOperational
//  *********************************/
// static t_eReturnCode s_HC_Fsm_PrdTsk_PreOperational(void)
// {
//     return RC_OK;
// }

// /*********************************
//  * s_HC_Fsm_PrdTsk_Operational
//  *********************************/
// static t_eReturnCode s_HC_Fsm_PrdTsk_Operational(void)
// {
//     return RC_OK;
// }

// /*********************************
//  * s_HC_Fsm_PrdTsk_Safety
//  *********************************/
// static t_eReturnCode s_HC_Fsm_PrdTsk_Safety(void)
// {
//     return RC_OK;
// }

// /*********************************
//  * s_HC_Fsm_PrdTsk_Error
//  *********************************/
// static t_eReturnCode s_HC_Fsm_PrdTsk_Error(void)
// {
//     return RC_OK;
// }

// /*********************************
//  * s_HC_SetAxeSetPoint
//  *********************************/
// static t_eReturnCode s_HC_SetAxeSetPoint( t_eHC_AxeHandleList f_idxAxe_e, 
//                                             t_sint32 f_setPoint_s32,
//                                             t_float32 f_speed_f32, 
//                                             t_float32 f_trigTiming_f32)
// {
//     t_eReturnCode Ret_e;
//     const t_sHC_AxeAppCfg * appAxeCfg_ps;
//     t_eAPPLGC_SrvHealth axeHealth_e;
//     t_eAPPSPM_ItemPrm prmPulseToRad_e;
//     t_uAPPSPM_PrmValType pulsePerRad_u = {.prmVal_f32 = 0.0f};

//     if(f_idxAxe_e >= HC_AXE_HD_NB)
//     {
//         Ret_e = RC_ERROR_PARAM_INVALID;
//         ASSERT((t_uint16)0);
//     }
//     else 
//     {
//         Ret_e = RC_OK;
//         switch(f_idxAxe_e)
//         {
//             case HC_AXE_HD_KNFE:
//                 appAxeCfg_ps = &c_HC_AppAxesCfg_as[HC_AXE_HD_KNFE];
//                 prmPulseToRad_e = APPSPM_PRM_HC_KNIFE_PULSE_TO_RAD;
//             break;
//             case HC_AXE_HD_CNTR_KNFE:
//                 appAxeCfg_ps = &c_HC_AppAxesCfg_as[HC_AXE_HD_CNTR_KNFE];
//                 prmPulseToRad_e = APPSPM_PRM_HC_CNTR_KNIFE_PULSE_TO_RAD;
//             break;
//             case HC_AXE_HD_HOLD_KNFE:
//                 appAxeCfg_ps = &c_HC_AppAxesCfg_as[HC_AXE_HD_HOLD_KNFE];
//                 prmPulseToRad_e = APPSPM_PRM_HC_HOLD_KNIFE_PULSE_TO_RAD;
//             break;
//             case HC_AXE_HD_NB:
//             default:
//                 Ret_e = RC_ERROR_PARAM_INVALID;
//             break;
//         }
//         if(Ret_e == RC_OK)
//         {
//             Ret_e = APPLGC_GetServiceHealth(appAxeCfg_ps->lgcSrvID_e, &axeHealth_e);
//             if(Ret_e != RC_OK)
//             {
//                 axeHealth_e = APPLGC_SRV_HEALTH_ERROR;
//             }
//             if(axeHealth_e == APPLGC_SRV_HEALTH_OK)
//             {
//                 Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfMtrPulse_e, (t_float32)f_setPoint_s32);
//                 if(Ret_e == RC_OK)
//                 {
//                     Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, f_speed_f32);
//                 }
//                 if(Ret_e == RC_OK)
//                 {
//                     Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfTimTrig_e, f_trigTiming_f32);
//                 }
//                 //---- compute position value ----//
//                 if(Ret_e == RC_OK)
//                 {
//                     Ret_e = APPSPM_GetParam(prmPulseToRad_e, &pulsePerRad_u);

//                     if(Ret_e == RC_OK)
//                     {
//                         #warning(add function to compute from pulses)
//                     }
//                 }                
//             }
//         }
//     }

//     return Ret_e
// }

// /*********************************
//  * s_GTRY_EnableAxe
//  *********************************/
// static t_eReturnCode s_GTRY_EnableAxe(t_eHC_AxeHandleList f_idxAxe_e)
// {
//     t_eReturnCode Ret_e;
//     const t_sHC_AxeAppCfg * appAxeCfg_ps;

//     if(f_idxAxe_e >= HC_AXE_HD_NB)
//     {
//         ASSERT((t_uint16)f_idxAxe_e);
//         Ret_e = RC_ERROR_PARAM_INVALID;
//     }
//     else 
//     {
//         //---- maybe make a switch case where now there is no difference 
//         //          isn't a good idea, in release modify this ----//
//         switch(f_idxAxe_e)
//         {
//             case HC_AXE_HD_KNFE:
//                 appAxeCfg_ps = &c_HC_AppAxesCfg_as[HC_AXE_HD_KNFE];
//                 Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, APPACT_ENABLE_MOTOR);
//             break;
//             case HC_AXE_HD_CNTR_KNFE:
//                 appAxeCfg_ps = &c_HC_AppAxesCfg_as[HC_AXE_HD_CNTR_KNFE];
//                 Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, APPACT_ENABLE_MOTOR);
//             break;
//             case HC_AXE_HD_HOLD_KNFE:
//                 appAxeCfg_ps = &c_HC_AppAxesCfg_as[HC_AXE_HD_HOLD_KNFE];
//                 Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, APPACT_ENABLE_MOTOR);
//             break;
//             case HC_AXE_HD_NB:
//             default:
//                 Ret_e = RC_ERROR_PARAM_INVALID;
//             break;
//         }
//     }

//     return Ret_e;
// }

// /*********************************
//  * s_GTRY_HardAxeStop
//  *********************************/
// static t_eReturnCode s_GTRY_AxeStop(t_eHC_AxeHandleList f_idxAxe_e, t_bool f_isHardStop_b)
// {
//     t_eReturnCode Ret_e;
//     const t_sHC_AxeAppCfg * appAxeCfg_ps;
//     t_float32 stopID_f32 = 0.0F;

//     if(f_idxAxe_e >= HC_AXE_HD_NB)
//     {
//         ASSERT((t_uint16)f_idxAxe_e);
//         Ret_e = RC_ERROR_PARAM_INVALID;
//     }
//     else 
//     {
//         appAxeCfg_ps = &c_HC_AppAxesCfg_as[f_idxAxe_e];

//         if(f_isHardStop_b == TRUE)
//         {
//             stopID_f32 = APPACT_HARD_STOP;
//         }
//         else 
//         {
//             stopID_f32 = APPACT_SOFT_STOP;
//         }

//         Ret_e = APPACT_SetActValue(appAxeCfg_ps->actIfSpeed_e, stopID_f32);
//     }

//     return Ret_e;
// }
// /*********************************
//  * s_HC_SigReceptionCallback
//  *********************************/
// static void s_HC_MsgReceptionCallback(  t_uint16 f_msgID_u16,
//                                         t_uint8 f_nbSignal_u8,
//                                         t_eAPPSIG_Signal *f_signal_ae, 
//                                         t_float32 *f_sigValue_af32)
// {
//     t_uint32 currentTime_u32;
//     t_uint8 idxSignal_u8;
//     t_eHC_CmdSignals currCmdSig_e;
//     t_eReturnCode Ret_e;

//     if(f_msgID_u16 >= (t_uint16)APPSIG_CAN_MSG_NB)
//     {
//         ASSERT((t_uint16)f_msgID_u16);
//     }
//     else 
//     {
//         Ret_e = RC_OK;

//         switch(f_msgID_u16)
//         {
//             case APPSIG_CAN_MSG_LGC_HC_CMD_POSITION:
//             {
//                 t_sHC_CarthPos buffPos_s;
//                 // 0 : x_position, 1:y_position
//                 buffPos_s.x_f32 = f_sigValue_af32[0];
//                 buffPos_s.y_f32 = f_sigValue_af32[1];
                
//                 Ret_e = LIBQUEUE_WriteElement(  &g_QueueCmdPosRcvMngmt_s,
//                                                 &buffPos_s,
//                                                 sizeof(t_sHC_CarthPos));
//                 if(Ret_e != RC_OK)
//                 {
//                     ASSERT((t_uint16)Ret_e);
//                 }
//                 else if(g_FlagPosCmdPending_b == FALSE)
//                 {
//                     g_FlagPosCmdPending_b = TRUE;
//                 }
//             }
//             break;
//             case APPSIG_CAN_MSG_LGC_HC_CMD_CALIBRATION:
//                 // 0 appsns_id, 1:req_state 2:pulse 3:speed
//                 t_eAPPSIG_Signal sigSnsID_e = (t_eAPPSIG_Signal)(f_sigValue_af32[0]);
//                 t_eAPPLGC_CalibStatus reqSts_e = (t_eAPPLGC_CalibStatus)(f_sigValue_af32[1]);
//                 t_float32 cmdPulses_f32 = (f_sigValue_af32[2]);
//                 t_float32 cmdSpeed_f32 = (f_sigValue_af32[3]);

//                 t_sHC_CalibCmdInfo calibCmdInfo_s;

//                 if((sigSnsID_e == APPSNS_SNSITF_ECDR_HD_CNTR_KNF_POS)
//                 || (sigSnsID_e == APPSNS_SNSITF_ECDR_HD_KNF_POS)
//                 || (sigSnsID_e == APPSNS_SNSITF_ECDR_HD_HOLD_POS))
//                 {
//                     Ret_e = SMB_Read(   &g_sfmb_calibInfoCmd_s,
//                                         &calibCmdInfo_s,
//                                         sizeof(t_sHC_CalibCmdInfo));
//                     if(Ret_e == RC_OK)
//                     {
                        
//                         //---- pulses are add if in the same sense 
//                         //      pulses are reset to 0 is sens != ----//
//                         if(calibCmdInfo_s.pulses_f32 == (t_sint32)0)
//                         {
//                             calibCmdInfo_s.pulses_f32 = cmdPulses_f32;
//                         }
//                         else if(((calibCmdInfo_s.pulses_f32 > (t_sint32)0)
//                             &&  (cmdPulses_f32 < (t_sint32)0))
//                         ||       ((calibCmdInfo_s.pulses_f32 < (t_sint32)0)
//                             &&  (cmdPulses_f32 > (t_sint32)0)))
//                         {
//                             calibCmdInfo_s.pulses_f32 = cmdPulses_f32;
//                         }
//                         else 
//                         {
//                             calibCmdInfo_s.pulses_f32 += cmdPulses_f32;
//                         }
//                         if(reqSts_e >= APPLGC_CALIB_STS_NB)
//                         {
//                             ASSERT((t_uint16)reqSts_e);
//                         }
//                         else 
//                         {
//                             calibCmdInfo_s.snsItf_e = sigSnsID_e;
//                             calibCmdInfo_s.reqSts_e = reqSts_e;
//                             calibCmdInfo_s.speed_f32 = f_sigValue_af32[2];

//                             Ret_e = SMB_Write(  &g_sfmb_calibInfoCmd_s,
//                                                 &calibCmdInfo_s,
//                                                 sizeof(t_sHC_CalibCmdInfo));
//                         }  
//                     }
//                     if(Ret_e != RC_OK)
//                     {
//                         ASSERT((t_uint16)Ret_e);
//                     }
//                 }
//                 else 
//                 {
//                     ASSERT((t_uint16)sigSnsID_e);
//                 }
//             break;
//             case APPSIG_CAN_MSG_LGC_REARMAMENT_CMD:
//             {
//                 // 0 : rearm agent ID, 1: rearm_type 2
//                 t_eAPPLGC_AgentList agent_e = f_sigValue_af32[0];
//                 t_eAPPLGC_RearmType rearmType_e = f_sigValue_af32[1];

//                 if(agent_e != APPLGC_AGENT_HEAD_CUTTER)
//                 {
//                     //---- every ecu received but for debug, leave assertion ----//
//                     ASSERT((t_uint16)agent_e);
//                 }
//                 else if(rearmType_e >= LGC_REARM_TYPE_NB)
//                 {
//                     ASSERT((t_uint16)rearmType_e);
//                 }
//                 else 
//                 {
//                     g_RearmInfo_s.rearmType_e = rearmType_e;
//                     g_RearmInfo_s.reqRearm_b = TRUE;
//                 }
//             }
//             break;
//         }
//     }
// }
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

