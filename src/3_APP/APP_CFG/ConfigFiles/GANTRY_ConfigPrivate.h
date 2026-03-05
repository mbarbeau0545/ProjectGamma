/**
 * @file        CL42T_ConfigPrivate.h
 * @brief       Driver Module for Driver CL42T.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        21/01/2025
 * @version     1.0
 */
  
#ifndef GANTRY_CONFIGPRIVATE_H_INCLUDED
#define GANTRY_CONFIGPRIVATE_H_INCLUDED

    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
    #include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
    #include "APP_CTRL/APP_SNS/Src/APP_SNS.h"
    #include "APP_CTRL/APP_ACT/Src/APP_ACT.h"
    #include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
    #include "APP_LGC/Src/APP_LGC.h"

    #include "./GANTRY_ConfigPublic.h"
    #include "./APP_CFG/ConfigSpecific/GANTRY_ConfigSpecific.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    ///@brief Fifo Buffer len define
    #define GTRY_CMD_POS_RCV_BUFFER_LEN         ((t_uint8)120) // must be divided by 3, 40 cmd 
    #define GTRY_CMD_ITER_BUFFER_LEN            ((t_uint8)100)

    ///@brief direction to go to the right spot for referencing 
    #define GTRY_CALIB_DIR_AXE_X                ((t_sint32)-1)
    #define GTRY_CALIB_DIR_AXE_Y                ((t_sint32)-1)
    #define GTRY_CALIB_DIR_AXE_Z                ((t_sint32)-1)

    ///@brief Number of iteration we can send 
    #define GTRY_MTR_MAX_SEND_ITER              ((t_uint8)15)
    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//
    ///@brief Axe Calibration List
    typedef enum 
    {
        GTRY_CALIB_ID_AXE_X = 0,       //---- Calibration of axe X ----//
        GTRY_CALIB_ID_AXE_Y,           //---- Calibration of axe Y ----//
        GTRY_CALIB_ID_AXE_Z,           //---- Calibration of axe Z ----//
        GTRY_CALIB_ID_AXE_ALL,         //---- Calibration of all axes ----//

        GTRY_CALIB_ID_AXE_NB
    } t_eGTRY_CalibAxeId;

    ///@brief Calibration Type List 
    typedef enum 
    {
        GTRY_CALIB_TYPE_ASYNC = 0,      //---- calibration will be made in async mode, axe X then Y and Z ----//
        GTRY_CALIB_TYPE_SYNC,           //---- calibration will be made in sync mode Axe X,Y,Z at the same time ----//

        GTRY_CALIB_TYPE_NB,             //---- Calibration type number  ----//
    } t_eGTRY_CalibType;

    ///@brief Enumeration of the type of sending iteration
    typedef enum 
    {
        GTRY_SEND_ITER_BLOCKING = 0,     //---- Iterations are send for all axes in sync ways, if a motor 
                                            //      does not accept cmd anymore we do not try to send iter for others axes, we wait
                                            //      the blocking one is available again ----//
        GTRY_SEND_ITER_ASYNC,           //---- Iterations are send for all motor as soon as they can ----//                             

        GTRY_SEN_ITER_NB
    } t_eGTRY_SendIterType;

    ///@brief Command User Type
    typedef enum 
    {
        GTRY_CMD_TYPE_ID_CARTESIAN = 0,     //---- Command Type Identifier for Carthesian coordinate ---//
        GTRY_CMD_TYPE_ID_SPHERIC,           //---- Command Type Identifier for Spheric coordinate ----//
        GTRY_CMD_TYPE_ID_STEPS,             //---- Command Type Identifier for steps for each axes ----//

        GTRY_CMD_TYPE_ID_NB,
    } t_eGTRY_CmdTypeId;

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
        t_float32 calibExpectValue_f32;             //---- expected_value for calibration ----//
    } t_sGTRY_AxeAppCfg;

    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
   
    //----------------------------- TYPES---------------------------//
    ///@brief get the algo paramter more easily
    typedef struct
    {
        t_eAPPSPM_ItemPrm chunkSize_e;                                 //---- chunk sizes per iteraitons ----//
        t_eAPPSPM_ItemPrm MinFreq_ae[GTRY_PHYS_AXE_NB];               //---- Minimum Frequency for Axes ----//
        t_eAPPSPM_ItemPrm MaxFreq_ae[GTRY_PHYS_AXE_NB];               //---- Maximum Frequency for Axes ----//
        t_eAPPSPM_ItemPrm pulsePerRound_ae[GTRY_PHYS_AXE_NB];            //---- Pulse per Millimeter for Axes ----//
        t_eAPPSPM_ItemPrm pinionDiamMm_ae[GTRY_PHYS_AXE_NB];            //---- Pulse per Millimeter for Axes ----//
        t_eAPPSPM_ItemPrm cptPrio_SafeHeight_ae[GTRY_PHYS_AXE_NB];    //---- Height to reach for the axe priority before others can move ----//
    } t_sGTRYSPEC_AlgoItemPrm;
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    ///@brief variable for application mapping
    const t_sGTRY_AxeAppCfg c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_NB] = {
        [GTRY_AXE_HANDLE_XL] = {
            .actifMtrSetPoint_e = APPACT_ACTITF_MTR_XL_PLS,
            .actIfSpeed_e = APPACT_ACTITF_MTR_XL_SPD,
            .actIfTimTrig_e = APPACT_ACTITF_MTR_XL_TRG,
            .lgcSrvID_e = APPLGC_SRV_GTRY_X,
            .snsIfEcdrPos_e = APPSNS_SNSITF_ECDR_XL_POS,
            .sysOptEcdr_e = APPSYS_OPT_ID_SNS_ECDR_XL,
            .calibExpectValue_f32 = 0.0F
        },
        [GTRY_AXE_HANDLE_XR] = {
            .actifMtrSetPoint_e = APPACT_ACTITF_MTR_XR_PLS,
            .actIfSpeed_e = APPACT_ACTITF_MTR_XR_SPD,
            .actIfTimTrig_e = APPACT_ACTITF_MTR_XR_TRG,
            .lgcSrvID_e = APPLGC_SRV_GTRY_X,
            .snsIfEcdrPos_e = APPSNS_SNSITF_ECDR_XR_POS,
            .sysOptEcdr_e = APPSYS_OPT_ID_SNS_ECDR_XR,
            .calibExpectValue_f32 = 0.0F
        },
        [GTRY_AXE_HANDLE_Y] = {
            .actifMtrSetPoint_e = APPACT_ACTITF_MTR_Y_PLS,
            .actIfSpeed_e = APPACT_ACTITF_MTR_Y_SPD,
            .actIfTimTrig_e = APPACT_ACTITF_MTR_Y_TRG,
            .lgcSrvID_e = APPLGC_SRV_GTRY_Y,
            .snsIfEcdrPos_e = APPSNS_SNSITF_ECDR_Y_POS,
            .sysOptEcdr_e = APPSYS_OPT_ID_SNS_ECDR_Y,
            .calibExpectValue_f32 = 0.0F
        },
        [GTRY_AXE_HANDLE_Z] = {
            .actifMtrSetPoint_e = APPACT_ACTITF_MTR_Z_PLS,
            .actIfSpeed_e = APPACT_ACTITF_MTR_Z_SPD,
            .actIfTimTrig_e = APPACT_ACTITF_MTR_Z_TRG,
            .lgcSrvID_e = APPLGC_SRV_GTRY_Z,
            .snsIfEcdrPos_e = APPSNS_SNSITF_ECDR_Z_POS,
            .calibExpectValue_f32 = 0.0F
        }
    };
    /// @brief Varialbe to store item to reach for algo aprameter
    const t_sGTRYSPEC_AlgoItemPrm c_GTRY_AlgoItemPrm_s = {
        .chunkSize_e = APPSPM_PRM_GTRY_PULSE_ITER_MAX,
        .MinFreq_ae = {APPSPM_PRM_GTRY_X_SPD_MIN, APPSPM_PRM_GTRY_Y_SPD_MIN, APPSPM_PRM_GTRY_Z_SPD_MIN},
        .MaxFreq_ae = {APPSPM_PRM_GTRY_X_SPD_MAX, APPSPM_PRM_GTRY_Y_SPD_MAX, APPSPM_PRM_GTRY_Z_SPD_MAX},
        .pulsePerRound_ae = {APPSPM_PRM_GTRY_AXE_X_PULSE_PER_ROUND, APPSPM_PRM_GTRY_AXE_Y_PULSE_PER_ROUND, APPSPM_PRM_GTRY_AXE_Z_PULSE_PER_ROUND},
        .pinionDiamMm_ae = {APPSPM_PRM_GTRY_AXE_X_PINION_DIAM_MM, APPSPM_PRM_GTRY_AXE_Y_PINION_DIAM_MM, APPSPM_PRM_GTRY_AXE_Z_PINION_DIAM_MM},
        .cptPrio_SafeHeight_ae = {APPSPM_PRM_GTRY_AXE_X_SAFE_HEIGHT, APPSPM_PRM_GTRY_AXE_Y_SAFE_HEIGHT, APPSPM_PRM_GTRY_AXE_Z_SAFE_HEIGHT},
    };

    const t_eAPPSIG_CanMsgList c_GTRY_SubMsgSig_ae[GTRY_CMD_MSGSIG_NB] = {
        APPSIG_CAN_MSG_LGC_GTRY_CMD_POSITION_COORD,// GTRY_CMD_MSGSIG_POS_COORD
        APPSIG_CAN_MSG_LGC_GTRY_CMD_POSITION_SPHERIC,// GTRY_CMD_MSGSIG_POS_SPHERIC
        APPSIG_CAN_MSG_LGC_GTRY_CMD_STEPS,// GTRY_CMD_MSGSIG_POS_STEP
        APPSIG_CAN_MSG_LGC_GTRY_CMD_CALIBRATION,// GTRY_CMD_MSGSIG_CALIB
        APPSIG_CAN_MSG_LGC_REARMAMENT_CMD,// GTRY_CMD_MSGSIG_REARMAMENT
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
