/**
 * @file        MOTION_ConfigPrivate.h
 * @brief       .
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        21/01/2025
 * @version     1.0
 */
  
#ifndef MOTION_CONFIGPRIVATE_H_INCLUDED
#define MOTION_CONFIGPRIVATE_H_INCLUDED

    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
    #include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
    #include "APP_CTRL/APP_SNS/Src/APP_SNS.h"
    #include "APP_CTRL/APP_ACT/Src/APP_ACT.h"
    #include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
    #include "APP_LGC/Src/APP_LGC.h"

    #include "./MOTION_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//
    typedef enum 
    {
        MOT_CMD_MSGSIG_HEAD = 0,
        MOT_CMD_MSGSIG_WHL_ANGLE = MOT_CMD_MSGSIG_HEAD,     //---- message is a the angle positon in milliradian ----//
        MOT_CMD_MSGSIG_PROPULSION,                          //---- message is propulsion command, control ID, either current/ or speed rad/s ----//
        MOT_CMD_MSGSIG_CALIB,                               //---- message is calibration, id, pulse, speed ----//
        MOT_CMD_MSGSIG_REARMAMENT,                          //---- message value is the rearmament commmand ----//

        MOT_CDM_MSGSIG_NB
    } t_eMOT_CmdSignals;
    //---------------------------STRUCTURE TYPES--------------------------//
    ///@brief Mapping structure beetween direction motor and application
    typedef struct 
    {
        t_eAPPACT_ActInterface actifMtrSetPoint_e;     //---- Pulse/State actuators interface (Pulses in SetActValue, Drop Pulses in GetActValue)----//
        t_eAPPACT_ActInterface actIfSpeed_e;        //---- Speed actuator interface (Freq in SetActValue, Motor Sts in GetActValue) -----//
        t_eAPPACT_ActInterface actIfTimTrig_e;       //---- Trigger Timer Actuator interface -----//
        t_eAPPSNS_SnsInterface snsIfEcdrPos_e;      //---- Encoder sensors interface ----//
        t_eAPPLGC_SrvList lgcSrvID_e;               //---- Logic service Id ----//
        t_eAPPSYS_SysOptionList sysOptEcdr_e;       //---- System encoder option ----//
        t_float32 calibValExpected_f32;          //---- calibration value expected ----//
    } t_sMOT_DirMtrCfg;

    ///@brief Structure to gather user command from AppSig 
    typedef struct 
    {
        t_float32 value_f32;
        t_bool isRcv_b;
        t_uint32 timeStamp_u32;
    } t_sMOT_cmdSigInfo;

    typedef struct
    {
        const t_eAPPSIG_Signal *signal_pe;      //---- pointor to a list of signals for the group -----//
        t_uint8 nbsignals_u8;                   //---- Number of signal for the group -----//
        t_uint32 timeoutMs_u32;                 //---- Time out to set a entire command -----//
    } t_sMOT_SigGroupInfo;
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
   
    //----------------------------- TYPES---------------------------//
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    ///@brief variable for application mapping
    const t_sMOT_DirMtrCfg c_MOT_AppWhlDirCfg_as[MOT_ACTDIR_NB] = {
        [MOT_ACTDIR_WHL_AV_L] = {
            .actifMtrSetPoint_e = APPACT_ACTITF_MTR_WHL_AV_L_PLS,
            .actIfSpeed_e = APPACT_ACTITF_MTR_WHL_AV_L_SPD,
            .actIfTimTrig_e = APPACT_ACTITF_MTR_WHL_AV_L_TRG,
            .snsIfEcdrPos_e = APPSNS_SNSITF_ECDR_WHL_AV_L_POS,
            .lgcSrvID_e = APPLGC_SRV_WHEEL_AV_L,
            .calibValExpected_f32 = 0.0F // radian
        },
        [MOT_ACTDIR_WHL_AV_R] = {
            .actifMtrSetPoint_e = APPACT_ACTITF_MTR_WHL_AV_R_PLS,
            .actIfSpeed_e = APPACT_ACTITF_MTR_WHL_AV_R_SPD,
            .actIfTimTrig_e = APPACT_ACTITF_MTR_WHL_AV_R_TRG,
            .snsIfEcdrPos_e = APPSNS_SNSITF_ECDR_WHL_AV_R_POS,
            .lgcSrvID_e = APPLGC_SRV_WHEEL_AV_R,
            .calibValExpected_f32 = (0.0F) // radian
        }
    };

    ///@brief variable for application mapping
    const t_sMOT_DirMtrCfg c_MOT_AppWhlPropCfg_as[MOT_ACTPROP_NB] = {
        [MOT_ACTPROP_WHL_AR_L] = {
            .actifMtrSetPoint_e = APPACT_ACTITF_MTR_WHL_AV_L_PLS,
            .actIfSpeed_e = APPACT_ACTITF_MTR_WHL_AV_L_SPD,
            .actIfTimTrig_e = APPACT_ACTITF_MTR_WHL_AV_L_TRG,
            .snsIfEcdrPos_e = APPSNS_SNSITF_ECDR_WHL_AV_L_POS,
            .lgcSrvID_e = APPLGC_SRV_WHEEL_AV_L,
            .calibValExpected_f32 = 0.0F // Milliradian
        },
        [MOT_ACTPROP_WHL_AR_R] = {
            .actifMtrSetPoint_e = APPACT_ACTITF_MTR_WHL_AV_R_PLS,
            .actIfSpeed_e = APPACT_ACTITF_MTR_WHL_AV_R_SPD,
            .actIfTimTrig_e = APPACT_ACTITF_MTR_WHL_AV_R_TRG,
            .snsIfEcdrPos_e = APPSNS_SNSITF_ECDR_WHL_AV_R_POS,
            .lgcSrvID_e = APPLGC_SRV_WHEEL_AV_R,
            .calibValExpected_f32 = (0.0F) // Milliradian
        }
    };

    const t_eAPPSIG_CanMsgList c_MOT_MsgMapping_ae[MOT_CDM_MSGSIG_NB] = {
        APPSIG_CAN_MSG_LGC_MOT_CMD_WHL_AV_POSITION,         // MOT_CMD_MSGSIG_WHL_ANGLE
        APPSIG_CAN_MSG_LGC_MOT_CMD_WHL_AR_PROPULSION,       // MOT_CMD_MSGSIG_PROPULSION
        APPSIG_CAN_MSG_LGC_MOT_CMD_CALIBRATION,             // MOT_CMD_MSGSIG_CALIB
        APPSIG_CAN_MSG_LGC_REARMAMENT_CMD                   // MOT_CMD_MSGSIG_REARMAMENT
    };

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    
#endif // GANTRY_CONFIGPRIVATE_H_INCLUDED
//************************************************************************************
// End of File
//************************************************************************************

/**
 *	@brief
 *	@note   
 *
 *
 *	@param[in] 
 *	@param[in]
 *	 
 *
 *
 */
