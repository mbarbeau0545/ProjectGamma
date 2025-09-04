/*********************************************************************
 * @file        APPACT_ConfigPublic.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPSIG_CONFIGPUBLIC_H_INCLUDED
#define APPSIG_CONFIGPUBLIC_H_INCLUDED

    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    ///@brief Number maximum of max subsriber a msg can have 
    #define APPSIG_MSG_RCV_SUBSRIBERS_MAX   ((t_uint8)1)
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    ///@brief ENum for Signal Encoding
    typedef enum 
    {
        APPSIG_SIG_ENCODE_INTEL = 0,
        APPSIG_SIG_ENCODE_MOTOROLA,

        APPSIG_SIG_ENCODE_NB
    } t_eAPPSIG_SigEncode;
    ///@brief Enum to know where come from the signal 
    typedef enum 
    {
        APPSIG_MSG_ORIGIN_CAN = 0,
        APPSIG_MSG_ORIGIN_SRL,

        APPSIG_MSG_ORIGIN_NB
    } t_eAPPSIG_MsgOrigin;

    ///@brief Enum to know the direction of the message
    typedef enum 
    {
        APPSIG_MSG_DIR_RX = 0,          //---- msg is expected to be receive ----//
        APPSIG_MSG_DIR_TX,              //---- msg is expected to be send and received ----//
        APPSIG_MSG_DIR_RX_TX,           //---- msg is expected to receive and transmitted ----//

        APPSIG_MSG_DIR_NB
    } t_eAPPSIG_MsgDirection;

    /* CAUTION : Automatic generated code section for Enum: Start */
    /**
    * @brief Signal list available.
    */
    typedef enum
    {
        APPSIG_SIGNAL_FMKCPU_MODSTATE = 0,
        APPSIG_SIGNAL_FMKCDA_MODSTATE,
        APPSIG_SIGNAL_FMKSRL_MODSTATE,
        APPSIG_SIGNAL_FMKFDCAN_MODSTATE,
        APPSIG_SIGNAL_FMKIO_MODSTATE,
        APPSIG_SIGNAL_FMKHRT_MODSTATE,
        APPSIG_SIGNAL_FMKTIM_MODSTATE,
        APPSIG_SIGNAL_APPSIG_MODSTATE,
        APPSIG_SIGNAL_APPSYS_MODSTATE,
        APPSIG_SIGNAL_APPSNS_MODSTATE,
        APPSIG_SIGNAL_APPACT_MODSTATE,
        APPSIG_SIGNAL_APPLGC_MODSTATE,
        APPSIG_SIGNAL_APPSDM_MODSTATE,
        APPSIG_SIGNAL_APPSPM_MODSTATE,
        APPSIG_SIGNAL_CYCLIC_DURATION,
        APPSIG_SIGNAL_FASTTASKDURATION,
        APPSIG_SIGNAL_PRM_LGC_GTRY_PULSE_ITER_MAX,
        APPSIG_SIGNAL_PRM_LGC_GTRY_X_RAMP_CTRL_KFACTOR,
        APPSIG_SIGNAL_PRM_LGC_GTRY_X_RAMP_CTRL_SLP_SPD,
        APPSIG_SIGNAL_PRM_LGC_GTRY_X_RAMP_CTRL_NB_STEP,
        APPSIG_SIGNAL_PRM_LGC_GTRY_X_SPEED_MAX,
        APPSIG_SIGNAL_PRM_LGC_GTRY_X_SPEED_MIN,
        APPSIG_SIGNAL_PRM_LGC_GTRY_Y_RAMP_CTRL_KFACTOR,
        APPSIG_SIGNAL_PRM_LGC_GTRY_Y_RAMP_CTRL_SLP_SPD,
        APPSIG_SIGNAL_PRM_LGC_GTRY_Y_RAMP_CTRL_NB_STEP,
        APPSIG_SIGNAL_PRM_LGC_GTRY_Y_SPEED_MAX,
        APPSIG_SIGNAL_PRM_LGC_GTRY_Y_SPEED_MIN,
        APPSIG_SIGNAL_PRM_LGC_GTRY_Z_RAMP_CTRL_KFACTOR,
        APPSIG_SIGNAL_PRM_LGC_GTRY_Z_RAMP_CTRL_SLP_SPD,
        APPSIG_SIGNAL_PRM_LGC_GTRY_Z_RAMP_CTRL_NB_STEP,
        APPSIG_SIGNAL_PRM_LGC_GTRY_Z_SPEED_MAX,
        APPSIG_SIGNAL_PRM_LGC_GTRY_Z_SPEED_MIN,
        APPSIG_SIGNAL_PRM_SYS_OPT_SNS_ECDR_XL,
        APPSIG_SIGNAL_PRM_SYS_OPT_SNS_ECDR_XR,
        APPSIG_SIGNAL_PRM_SYS_OPT_SNS_ECDR_Y,
        APPSIG_SIGNAL_PRM_SYS_OPT_SNS_ECDR_Z,
        APPSIG_SIGNAL_PRM_SYS_MACHINE_ID,
        APPSIG_SIGNAL_CL42T_MTR_1_STATE,
        APPSIG_SIGNAL_CL42T_MTR_2_STATE,
        APPSIG_SIGNAL_CL42T_MTR_3_STATE,
        APPSIG_SIGNAL_CL42T_MTR_4_STATE,
        APPSIG_SIGNAL_CL42T_MTR_1_CW_ENDSTOP,
        APPSIG_SIGNAL_CL42T_MTR_2_CW_ENDSTOP,
        APPSIG_SIGNAL_CL42T_MTR_3_CW_ENDSTOP,
        APPSIG_SIGNAL_CL42T_MTR_4_CW_ENDSTOP,
        APPSIG_SIGNAL_CL42T_MTR_1_CCW_ENDSTOP,
        APPSIG_SIGNAL_CL42T_MTR_2_CCW_ENDSTOP,
        APPSIG_SIGNAL_CL42T_MTR_3_CCW_ENDSTOP,
        APPSIG_SIGNAL_CL42T_MTR_4_CCW_ENDSTOP,
        APPSIG_SIGNAL_CL42T_MTR_1_DIRECTION,
        APPSIG_SIGNAL_CL42T_MTR_2_DIRECTION,
        APPSIG_SIGNAL_CL42T_MTR_3_DIRECTION,
        APPSIG_SIGNAL_CL42T_MTR_4_DIRECTION,
        APPSIG_SIGNAL_CL42T_MTR_1_DEADTIME,
        APPSIG_SIGNAL_CL42T_MTR_2_DEADTIME,
        APPSIG_SIGNAL_CL42T_MTR_3_DEADTIME,
        APPSIG_SIGNAL_CL42T_MTR_4_DEADTIME,
        APPSIG_SIGNAL_CL42T_MTR_1_HEALTH,
        APPSIG_SIGNAL_CL42T_MTR_2_HEALTH,
        APPSIG_SIGNAL_CL42T_MTR_3_HEALTH,
        APPSIG_SIGNAL_CL42T_MTR_4_HEALTH,
        APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_X,
        APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_Y,
        APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_Z,
        APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_RAYON,
        APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_THETHA,
        APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_PHI,
        APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_X,
        APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_Y,
        APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_Z,
        APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_X,
        APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_Y,
        APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_Z,
        APPSIG_SIGNAL_PRM_LGC_GTRY_ALGO_CPTE_TYPE,
        APPSIG_SIGNAL_PRM_LGC_GTRY_MAX_PULSES,
        APPSIG_SIGNAL_PRM_LGC_GTRY_CALIB_TYPE,
        APPSIG_SIGNAL_PRM_LGC_GTRY_SENDITER_TYPE,
        APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_X_PULSE_PER_MM,
        APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Y_PULSE_PER_MM,
        APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Z_PULSE_PER_MM,
        APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_X_LEN,
        APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Y_LEN,
        APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Z_LEN,
        APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_X_MIN_SPEED,
        APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Y_MIN_SPEED,
        APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Z_MIN_SPEED,
        APPSIG_SIGNAL_PRM_LGC_GTRY_X_CALIB_OFFSET,
        APPSIG_SIGNAL_PRM_LGC_GTRY_Y_CALIB_OFFSET,
        APPSIG_SIGNAL_PRM_LGC_GTRY_Z_CALIB_OFFSET,
    
        APPSIG_SIGNAL_NB,
    } t_eAPPSIG_Signal;

    /**
    * @brief message serial available.
    */
    typedef enum
    {
        APPSIG_SRL_MSG_APPLICATIONINFO1 = 0,
        APPSIG_SRL_MSG_CL42T_MOTORS_INFO,
        APPSIG_SRL_MSG_PRM_LGC_GTRY_X_RAMP_CTRL,
        APPSIG_SRL_MSG_PRM_LGC_GTRY_Y_RAMP_CTRL,
        APPSIG_SRL_MSG_PRM_LGC_GTRY_Z_RAMP_CTRL,
        APPSIG_SRL_MSG_PRM_LGC_GTRY_SPEED_CFG1,
        APPSIG_SRL_MSG_PRM_LGC_GTRY_SPEED_CFG_2,
        APPSIG_SRL_MSG_PRM_LGC_GTRY_SPEED_CFG_3,
        APPSIG_SRL_MSG_PRM_LGC_LGC_GTRY_CMD_POSITION,
        APPSIG_SRL_MSG_PRM_LGC_LGC_GTRY_CMD_SPHERIC,
        APPSIG_SRL_MSG_PRM_LGC_LGC_GTRY_CMD_STEPS,
        APPSIG_SRL_MSG_PRM_LGC_GTRY_PARAM_1,
        APPSIG_SRL_MSG_PRM_LGC_GTRY_PARAM_2,
        APPSIG_SRL_MSG_PRM_LGC_GTRY_PARAM_3,
        APPSIG_SRL_MSG_PRM_LGC_GTRY_PARAM_4,
    
        APPSIG_SRL_MSG_NB,
    } t_eAPPSIG_SrlMsgList;

    /**
    * @brief message can available.
    */
    typedef enum
    {
    
        APPSIG_CAN_MSG_NB,
    } t_eAPPSIG_CanMsgList;

    /* CAUTION : Automatic generated code section for Enum: End */
	//-----------------------------ENUM TYPES-----------------------------//

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
    
    

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APPSDM_CONFIGPUBLIC_H_INCLUDED           
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
