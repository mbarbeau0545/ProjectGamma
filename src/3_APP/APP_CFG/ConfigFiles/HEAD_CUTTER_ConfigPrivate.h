/**
 * @file        CL42T_ConfigPrivate.h
 * @brief       Driver Module for Driver CL42T.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        21/01/2025
 * @version     1.0
 */
  
#ifndef HEADGE_CUTTER_CONFIGPRIVATE_H_INCLUDED
#define HEADGE_CUTTER_CONFIGPRIVATE_H_INCLUDED

    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
    #include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
    #include "APP_CTRL/APP_SNS/Src/APP_SNS.h"
    #include "APP_CTRL/APP_ACT/Src/APP_ACT.h"
    #include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
    #include "APP_LGC/Src/APP_LGC.h"

    #include "./HEAD_CUTTER_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    ///@brief Fifo Buffer len define
    #define HC_CMD_POS_RCV_BUFFER_LEN         ((t_uint8)120) 
    #define HC_CMD_ITER_BUFFER_LEN            ((t_uint8)100)


    ///@brief Number of iteration we can send 
    #define HC_MTR_MAX_SEND_ITER              ((t_uint8)15)

    ///@brief Timestamp id max in position cpmma,d
    #define HC_CMD_POS_TIMESTAMP_ID_MAX       ((t_uint16)0xFFFF)

    ///@brief Max Pos Cmd treated in fsm ope
    #define HC_POS_CMD_TREATED_MAX              ((t_uint8)15)
    
    ///@brief Max Pos Cmd treated in fsm ope
    #define HC_PULSE_CMD_TREATED_MAX              ((t_uint8)15)
    
    ///@brief Minimum absolute pulse amount before queueing an iterative motor command.
    ///       Smaller values are ignored to avoid flooding CL42T with 1-pulse commands.
    #define HC_MIN_PULSE_CMD_ABS_S32              ((t_sint32)2)

    ///@brief When correction has to be made between compute & current position 
    ///         define the speed 
    #define HC_PULSE_SPEED_SERVO                    ((t_float32)6000.0F)

    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//
    typedef enum 
    {
        HC_CMD_MSGSIG_HEAD = 0,
        HC_CMD_MSGSIG_POSITION = HC_CMD_MSGSIG_HEAD,    //---- value is a the x positon in mm ----//
        HC_CMD_MSGSIG_CALIB,                            //---- value is a the y positon in mm ----//
        HC_CMD_MSGSIG_REARMAMENT,                       //---- value is a the y positon in mm ----//

        HC_CDM_MSGSIG_NB
    } t_eHC_CmdSignals;

    ///@brief command type for position
    typedef enum 
    {
        HC_CMD_TYPE_POS_CARTH = 0,                  //---- Command type for position is x,y of the knife in mm ----//
        HC_CMD_TYPE_POS_JOINT,                      //---- Command Type for position is angle joint in mrad ----//

        HC_CMD_TYPE_POS_NB
    } t_eHC_CmdPosType;
    //---------------------------STRUCTURE TYPES--------------------------//
    ///@brief Mapping structure beetween gantry and application
    typedef struct 
    {
        t_eAPPACT_ActInterface actifMtrSetPoint_e;     //---- Pulse/State actuators interface (Pulses in SetActValue, Drop Pulses in GetActValue)----//
        t_eAPPACT_ActInterface actIfSpeed_e;        //---- Speed actuator interface (Freq in SetActValue, Motor Sts in GetActValue) -----//
        t_eAPPACT_ActInterface actIfTimTrig_e;       //---- Trigger Timer Actuator interface -----//
        t_eAPPSNS_SnsInterface snsIfEcdrPos_e;      //---- Encoder sensors interface ----//
        t_eAPPLGC_SrvList lgcSrvID_e;               //---- Logic service Id ----//
        t_eAPPSYS_SysOptionList sysOptEcdr_e;       //---- System encoder option ----//
        t_float32 caliValExpectedMrad_f32;          //---- calibration value expected ----//
    } t_sHC_AxeAppCfg;

    ///@brief Structure to gather user command from AppSig 
    typedef struct 
    {
        t_float32 value_f32;
        t_bool isRcv_b;
        t_uint32 timeStamp_u32;
    } t_sHC_cmdSigInfo;

    typedef struct
    {
        const t_eAPPSIG_Signal *signal_pe;      //---- pointor to a list of signals for the group -----//
        t_uint8 nbsignals_u8;                   //---- Number of signal for the group -----//
        t_uint32 timeoutMs_u32;                 //---- Time out to set a entire command -----//
    } t_sHC_SigGroupInfo;
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
    const t_sHC_AxeAppCfg c_HC_AppAxesCfg_as[HC_AXE_HD_NB] = {
        [HC_AXE_HD_KNFE] = {
            .actifMtrSetPoint_e = APPACT_ACTITF_MTR_HD_KNF_PLS,
            .actIfSpeed_e = APPACT_ACTITF_MTR_HD_KNF_SPD,
            .actIfTimTrig_e = APPACT_ACTITF_MTR_HD_KNF_TRG,
            .snsIfEcdrPos_e = APPSNS_SNSITF_ECDR_HD_KNF_POS,
            .lgcSrvID_e = APPLGC_SRV_HEAD_CUTTER,
            .sysOptEcdr_e = APPSYS_OPT_ID_SNS_ECDR_HD_KNF,
            .caliValExpectedMrad_f32 = 0.0F // Milliradian
        },
        [HC_AXE_HD_CNTR_KNFE] = {
            .actifMtrSetPoint_e = APPACT_ACTITF_MTR_HD_CNTR_KNF_PLS,
            .actIfSpeed_e = APPACT_ACTITF_MTR_HD_CNTR_KNF_SPD,
            .actIfTimTrig_e = APPACT_ACTITF_MTR_HD_CNTR_KNF_TRG,
            .snsIfEcdrPos_e = APPSNS_SNSITF_ECDR_HD_CNTR_KNF_POS,
            .lgcSrvID_e = APPLGC_SRV_HEAD_CUTTER,
            .sysOptEcdr_e = APPSYS_OPT_ID_SNS_ECDR_HD_CNTR_KNF,
            .caliValExpectedMrad_f32 = (t_float32)(CST_PI_MRAD / 2.0F) // Milliradian
        },
        [HC_AXE_HD_HOLD_KNFE] = {
            .actifMtrSetPoint_e = APPACT_ACTITF_MTR_HD_HOLD_PLS,
            .actIfSpeed_e = APPACT_ACTITF_MTR_HD_HOLD_SPD,
            .actIfTimTrig_e = APPACT_ACTITF_MTR_HD_HOLD_TRG,
            .snsIfEcdrPos_e = APPSNS_SNSITF_ECDR_HD_HOLD_POS,
            .lgcSrvID_e = APPLGC_SRV_HEAD_CUTTER,
            .sysOptEcdr_e = APPSYS_OPT_ID_SNS_ECDR_HD_HOLD,
            .caliValExpectedMrad_f32 =  (t_float32)(CST_PI_MRAD / 2.0F) // Milliradian
        }
    };

    const t_eAPPSIG_CanMsgList c_HC_MsgMapping_ae[HC_CDM_MSGSIG_NB] = {
        APPSIG_CAN_MSG_LGC_HC_CMD_POSITION,     // HC_CMD_MSGSIG_POSITION
        APPSIG_CAN_MSG_LGC_HC_CMD_CALIBRATION,  // HC_CMD_MSGSIG_CALIB
        APPSIG_CAN_MSG_LGC_REARMAMENT_CMD       // HC_CMD_MSGSIG_REARMAMENT
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
