/*********************************************************************
 * @file        APPACT_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPSIG_CONFIGPRIVATE_H_INCLUDED
#define APPSIG_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APPSIG_ConfigPublic.h"
    #include "TypeCommon.h"
    //uncomment
    #include "FMK_HAL/FMK_SRL/Src/FMK_SRL.h"
    #include "FMK_HAL/FMK_CAN/Src/FMK_FDCAN.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************


    ///@brief Define to set the end of signal in the MSg
    #define APPSIG_SIGNAL_NONE (APPSIG_SIGNAL_NB)

    ///@brief Define the number of max element we can put in the queue 
    #define APPSIG_RX_BUFFER_SIZE ((t_uint8)120)

    ///@brief Number of data expected to be received 
    #define APPSIG_DATA_PAYLOAD_LEN  ((t_uint8)8)       // For CAN, SERIAL
    #define APPSIG_SRL_FRAME_PAYLOAD_LEN ((t_uint8)11)    // for Serial, 2 byte of start frame + 1 byte Identifier

    ///@brief start byte for serial comm 
    #define APPSIG_SRL_START_BYTE_0 ((t_uint8)0xAA)
    #define APPSIG_SRL_START_BYTE_1 ((t_uint8)0x55)

    ///@brief Information for can id serial
    #define APPSIG_CAN_ID_COMMON    ((t_uint32)0x18FF0000)
    #define APPSIG_CAN_ID_MASK      ((t_uint32)0x18FF0000)
    ///@brief Configuration Gate for the module 
    #define APPSIG_PORTGATE_CAN         (APPSIG_MSG_ORIGIN_CAN)
    #define APPSIG_PORTGATE_CAN_NODE    (FMKFDCAN_NODE_1)

    #define APPSIG_PORTGATE_SRL         (APPSIG_MSG_ORIGIN_SRL)
    #define APPSIG_PORTGATE_SRL_LINE    (FMKSRL_SERIAL_LINE_3)

    #define APPSIG_PORTGATE_CFG         (1 << APPSIG_MSG_ORIGIN_CAN) // (1 << APPSIG_MSG_ORIGIN_SRL)
    /* CAUTION : Automatic generated code section for Define: Start */
    ///@brief Serial Message Id
    ///@brief CAN Message Id
    #define APPSIG_CAN_ID_APPLICATIONINFO0                         ((t_uint32)0x18ff0000)
    #define APPSIG_CAN_ID_APPLICATIONINFO1                         ((t_uint32)0x18ff1000)
    #define APPSIG_CAN_ID_APPLICATIONINFO2                         ((t_uint32)0x18ff2000)
    #define APPSIG_CAN_ID_APPLICATIONDIAGNOSTIC0                   ((t_uint32)0x18ff0001)
    #define APPSIG_CAN_ID_APPLICATIONDIAGNOSTIC1                   ((t_uint32)0x18ff1001)
    #define APPSIG_CAN_ID_APPLICATIONDIAGNOSTIC2                   ((t_uint32)0x18ff2001)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_XL                       ((t_uint32)0x18fff000)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_XR                       ((t_uint32)0x18fff001)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_Y                        ((t_uint32)0x18fff002)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_Z                        ((t_uint32)0x18fff003)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_HD_KNF                   ((t_uint32)0x18fff004)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_HD_CNTR_KNF              ((t_uint32)0x18fff005)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_HD_HOLD                  ((t_uint32)0x18fff006)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_WHL_AV_L                 ((t_uint32)0x18fff007)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_WHL_AV_R                 ((t_uint32)0x18fff008)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_XL                        ((t_uint32)0x18ff0110)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_XR                        ((t_uint32)0x18ff0111)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_Y                         ((t_uint32)0x18ff0112)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_Z                         ((t_uint32)0x18ff0113)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_HD_KNF                    ((t_uint32)0x18ff1114)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_HD_CNTR_KNF               ((t_uint32)0x18ff1115)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_HD_HOLD                   ((t_uint32)0x18ff1116)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_WHL_AV_L                  ((t_uint32)0x18ff2117)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_WHL_AV_R                  ((t_uint32)0x18ff2118)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_XL                        ((t_uint32)0x18ff0120)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_XR                        ((t_uint32)0x18ff0121)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_Y                         ((t_uint32)0x18ff0122)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_Z                         ((t_uint32)0x18ff0123)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_HD_KNF                    ((t_uint32)0x18ff1124)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_HD_CNTR_KNF               ((t_uint32)0x18ff1125)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_HD_HOLD                   ((t_uint32)0x18ff1126)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_WHL_AV_L                  ((t_uint32)0x18ff2127)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_WHL_AV_R                  ((t_uint32)0x18ff2128)
    #define APPSIG_CAN_ID_APPACT_GET_ACT_PWR_MTR                   ((t_uint32)0x18ff1129)
    #define APPSIG_CAN_ID_APPSNS_GET_ECDR_GTRY_XL_XR               ((t_uint32)0x18ff0130)
    #define APPSIG_CAN_ID_APPSNS_GET_ECDR_GTRY_Y_Z                 ((t_uint32)0x18ff0131)
    #define APPSIG_CAN_ID_PRM_SEND_STATUS_ECU_0                    ((t_uint32)0x18ff03ff)
    #define APPSIG_CAN_ID_PRM_SEND_STATUS_ECU_1                    ((t_uint32)0x18ff03fe)
    #define APPSIG_CAN_ID_PRM_SEND_STATUS_ECU_2                    ((t_uint32)0x18ff03fd)
    #define APPSIG_CAN_ID_PRM_GTRY_X_RAMP_CTRL                     ((t_uint32)0x18ff0300)
    #define APPSIG_CAN_ID_PRM_GTRY_Y_RAMP_CTRL                     ((t_uint32)0x18ff0301)
    #define APPSIG_CAN_ID_PRM_GTRY_Z_RAMP_CTRL                     ((t_uint32)0x18ff0302)
    #define APPSIG_CAN_ID_PRM_GTRY_SPD_CFG1                        ((t_uint32)0x18ff0303)
    #define APPSIG_CAN_ID_PRM_GTRY_SPD_CFG_2                       ((t_uint32)0x18ff0304)
    #define APPSIG_CAN_ID_PRM_GTRY_SPD_CFG_3                       ((t_uint32)0x18ff0305)
    #define APPSIG_CAN_ID_PRM_LGC_GTRY_CMD_SPHERIC                 ((t_uint32)0x18ff0306)
    #define APPSIG_CAN_ID_PRM_GTRY_PARAM_1                         ((t_uint32)0x18ff0307)
    #define APPSIG_CAN_ID_PRM_GTRY_PARAM_2                         ((t_uint32)0x18ff0308)
    #define APPSIG_CAN_ID_PRM_GTRY_PARAM_3                         ((t_uint32)0x18ff0309)
    #define APPSIG_CAN_ID_PRM_GTRY_PARAM_4                         ((t_uint32)0x18ff0310)
    #define APPSIG_CAN_ID_PRM_GTRY_PARAM_SAFE_HEIGHT               ((t_uint32)0x18ff0311)
    #define APPSIG_CAN_ID_LGC_CL42T_MOTORS_INFO_GTRY               ((t_uint32)0x18ff0404)
    #define APPSIG_CAN_ID_LGC_CL42T_MOTORS_INFO_HEAD_GTRY          ((t_uint32)0x18ff0405)
    #define APPSIG_CAN_ID_LGC_CL42T_MOTORS_INFO_MOTION             ((t_uint32)0x18ff0406)
    #define APPSIG_CAN_ID_LGC_GTRY_CMD_POSITION                    ((t_uint32)0x18ff0400)
    #define APPSIG_CAN_ID_LGC_GTRY_CMD_STEPS                       ((t_uint32)0x18ff0401)
    #define APPSIG_CAN_ID_LGC_GTRY_POSITION                        ((t_uint32)0x18ff0402)
    #define APPSIG_CAN_ID_LGC_GTRY_DEBUG_FSM                       ((t_uint32)0x18ff0403)
    /* CAUTION : Automatic generated code section for Define: End */
    

    ///@brief number of queue element treated per cycle 
    #define APPSIG_TREAT_ELEM_NB        ((t_uint8)15)

    #define APPSIG_MSG_RX_ONLY          ((t_uint32)0xFFFF)
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
	//-----------------------------ENUM TYPES-----------------------------//
    

	/* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
	//-----------------------------STRUCT TYPES---------------------------//
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
	//-----------------------------TYPEDEF TYPES---------------------------//
    ///@brief Information for a signal 
	typedef struct 
    {
        t_uint8 bitLenght_u8;                    //---- the lenght of the signal ----//
        t_eAPPSIG_SigEncode sigEncode_e;         //---- to know if the decode has to be made in little or big Endian
        t_float32 factor_f32;                    //---- multiply factor for the signal ----//
        t_sint32 offset_s32;                     //---- offset to add / soustract signal ----//     
    } t_sAPPSIG_SigCfg;

    ///@brief Structure to identify the signals into a message
    typedef struct 
    {
        t_eAPPSIG_Signal signal_e;
        t_uint8 startBit_u8;
    } t_sAPPSIG_MsgSignalsCfg;
    
    ///@brief Information for a message 
    typedef struct 
    {
        t_uint32 msgId_u32;                                         //---- the identifier of the message ----//
        t_eAPPSIG_MsgDirection direction_ae[APPSYS_ECU_POS_NB];      //---- Rx, Tx message direction ----//
        t_uint16 msgCycleSend_u16;                                  //---- message cyclic updated ----//
        t_uint16 msgTimeout_u16;                                    //---- Time upon if a msg is not receive a Deev will be raise ----//             
        const t_sAPPSIG_MsgSignalsCfg * msgSignalsCfg_pas;          //---- signal in the message ----// 
        t_uint8 nbSignal_u8;
    } t_sAPPSIG_MsgCfg;

    
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
	
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    ///@brief Signal Configuration
    const t_sAPPSIG_SigCfg c_AppSig_SignalCfg_as[APPSIG_SIGNAL_NB] = {
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_FMKCPU_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_FMKCDA_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_FMKSRL_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_FMKFDCAN_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_FMKIO_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_FMKHRT_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_FMKTIM_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_APPSIG_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_APPSYS_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_APPSNS_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_APPACT_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_APPLGC_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_APPSDM_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_APPSPM_MODSTATE
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CYCLIC_DURATION
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_REPORT_STATUS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_DEBUG_INFO_1
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_DEBUG_INFO_2
        {(t_uint8)12,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_FASTTASKDURATION
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_XL_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_XL_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_XR_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_XR_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_Y_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_Y_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_Z_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_Z_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_WHL_AV_L_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_WHL_AV_L_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_WHL_AV_R_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_WHL_AV_R_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_HD_KNF_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_HD_KNF_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_HD_CNTR_KNF_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_HD_CNTR_KNF_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_HD_HOLD_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_HD_HOLD_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_HD_UP_LEFT_DIST
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_HD_DWN_LEFT_DIST
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_HD_UP_RIGHT_DIST
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_HD_DWN_RIGHT_DIST
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_XL_TRQ
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_XR_TRQ
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_Y_TRQ
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_Z_TRQ
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_WHL_AV_L_TRQ
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_WHL_AV_R_TRQ
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_HD_KNF_TRQ
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_CNTR_KNF_TRQ
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_HD_HOLD_TRQ
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_SET_MTR_XL_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_XL_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_XL_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_SET_MTR_XR_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_XR_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_XR_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_SET_MTR_Y_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_Y_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_Y_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_SET_MTR_Z_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_Z_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_Z_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_SET_MTR_HD_KNF_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_HD_KNF_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_HD_KNF_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_SET_MTR_HD_CNTR_KNF_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_HD_CNTR_KNF_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_HD_CNTR_KNF_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_SET_MTR_HD_HOLD_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_HD_HOLD_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_HD_HOLD_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_L_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_L_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_L_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_R_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_R_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_R_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_GET_MTR_XL_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_XL_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_XL_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_GET_MTR_XR_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_XR_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_XR_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_GET_MTR_Y_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_Y_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_Y_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_GET_MTR_Z_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_Z_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_Z_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_GET_MTR_HD_KNF_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_HD_KNF_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_HD_KNF_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_GET_MTR_HD_CNTR_KNF_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_HD_CNTR_KNF_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_HD_CNTR_KNF_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_GET_MTR_HD_HOLD_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_HD_HOLD_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_HD_HOLD_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_L_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_L_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_L_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_R_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_R_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_R_TRG
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_MTR_XL_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_MTR_XR_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_MTR_Y_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_MTR_Z_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_WHL_AV_L_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_WHL_AV_R_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_MTR_HD_KNF_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_MTR_HD_CNTR_KNF_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_MTR_HD_HOLD_RLY
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_CTRL_MTR_XL_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_XL_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_XL_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_CTRL_MTR_XR_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_XR_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_XR_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_CTRL_MTR_Y_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_Y_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_Y_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_CTRL_MTR_Z_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_Z_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_Z_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_KNF_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_KNF_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_KNF_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_CNTR_KNF_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_CNTR_KNF_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_CNTR_KNF_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_HOLD_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_HOLD_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_HOLD_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_L_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_L_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_L_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)-1048576                                               },// APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_R_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_R_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_R_TRG
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_FLAG_PARAM_SEND_OK
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_PULSE_ITER_MAX
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_SYS_OPT_SNS_ECDR_XL
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_SYS_OPT_SNS_ECDR_XR
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_SYS_OPT_SNS_ECDR_Y
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_SYS_OPT_SNS_ECDR_Z
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_SYS_MACHINE_ID
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_X_RMP_CTRL_KFACTOR
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_X_RMP_CTRL_SLOP_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_X_RMP_CTRL_NB_STEP
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_X_SPD_MAX
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_X_SPD_MIN
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_Y_RMP_CTRL_KFACTOR
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_Y_RMP_CTRL_SLOP_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_Y_RMP_CTRL_NB_STEP
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_Y_SPD_MAX
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_Y_SPD_MIN
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_Z_RMP_CTRL_KFACTOR
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_Z_RMP_CTRL_SLOP_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_Z_RMP_CTRL_NB_STEP
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_Z_SPD_MAX
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_Z_SPD_MIN
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_ALGO_CPTE_TYPE
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_CALIB_TYPE
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_SENDITER_TYPE
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_AXE_X_PULSE_PER_MM
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_AXE_Y_PULSE_PER_MM
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_AXE_Z_PULSE_PER_MM
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_AXE_X_LEN
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_AXE_Y_LEN
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_AXE_Z_LEN
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_AXE_X_MIN_SPEED
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_AXE_Y_MIN_SPEED
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_AXE_Z_MIN_SPEED
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_X_CALIB_OFFSET
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_Y_CALIB_OFFSET
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_Z_CALIB_OFFSET
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_AXE_X_SAFE_HEIGHT
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_AXE_Y_SAFE_HEIGHT
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_PRM_GTRY_AXE_Z_SAFE_HEIGHT
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_X
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_Y
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_Z
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_RAYON
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_THETHA
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_PHI
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_X
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_Y
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_Z
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_X
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_Y
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_Z
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_FSM_STS
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_FSM_CALIB
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_FSM_CLB_AXE_X
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_FSM_CLB_AXE_Y
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_FSM_CLB_AXE_Z
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_FSM_OPE
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_FSM_OPE_CMD_PRCSS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)0.1,                                                   (t_sint32)0                                                      },// APPSIG_SIGNAL_GTRY_AXE_X_POSITION
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)0.1,                                                   (t_sint32)0                                                      },// APPSIG_SIGNAL_GTRY_AXE_Y_POSITION
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)0.1,                                                   (t_sint32)0                                                      },// APPSIG_SIGNAL_GTRY_AXE_Z_POSITION
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_GTRY_ALGO_COMPUTE_TIME
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_1_STATE
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_2_STATE
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_3_STATE
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_4_STATE
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_5_STATE
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_6_STATE
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_7_STATE
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_8_STATE
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_9_STATE
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_10_STATE
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_1_CW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_2_CW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_3_CW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_4_CW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_5_CW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_6_CW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_7_CW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_8_CW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_9_CW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_10_CW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_1_CCW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_2_CCW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_3_CCW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_4_CCW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_5_CCW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_6_CCW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_7_CCW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_8_CCW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_9_CCW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_10_CCW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_1_DIRECTION
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_2_DIRECTION
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_3_DIRECTION
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_4_DIRECTION
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_5_DIRECTION
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_6_DIRECTION
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_7_DIRECTION
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_8_DIRECTION
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_9_DIRECTION
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_10_DIRECTION
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_1_DEADTIME
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_2_DEADTIME
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_3_DEADTIME
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_4_DEADTIME
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_5_DEADTIME
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_6_DEADTIME
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_7_DEADTIME
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_8_DEADTIME
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_9_DEADTIME
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_10_DEADTIME
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_1_HEALTH
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_2_HEALTH
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_3_HEALTH
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_4_HEALTH
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_5_HEALTH
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_6_HEALTH
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_7_HEALTH
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_8_HEALTH
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_9_HEALTH
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint32)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_10_HEALTH
    };

    ///@brief Variable for decoding CL42T_MTR_10_HEALTH
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_ApplicationInfo0_as[14] = {
    {APPSIG_SIGNAL_FMKCPU_MODSTATE,                         (t_uint8)0                                             },
    {APPSIG_SIGNAL_APPACT_MODSTATE,                         (t_uint8)3                                             },
    {APPSIG_SIGNAL_APPLGC_MODSTATE,                         (t_uint8)6                                             },
    {APPSIG_SIGNAL_APPSDM_MODSTATE,                         (t_uint8)9                                             },
    {APPSIG_SIGNAL_APPSIG_MODSTATE,                         (t_uint8)12                                            },
    {APPSIG_SIGNAL_APPSNS_MODSTATE,                         (t_uint8)15                                            },
    {APPSIG_SIGNAL_APPSPM_MODSTATE,                         (t_uint8)18                                            },
    {APPSIG_SIGNAL_FMKCDA_MODSTATE,                         (t_uint8)24                                            },
    {APPSIG_SIGNAL_FMKFDCAN_MODSTATE,                       (t_uint8)27                                            },
    {APPSIG_SIGNAL_FMKHRT_MODSTATE,                         (t_uint8)30                                            },
    {APPSIG_SIGNAL_FMKIO_MODSTATE,                          (t_uint8)33                                            },
    {APPSIG_SIGNAL_FMKSRL_MODSTATE,                         (t_uint8)36                                            },
    {APPSIG_SIGNAL_FMKTIM_MODSTATE,                         (t_uint8)21                                            },
    {APPSIG_SIGNAL_CYCLIC_DURATION,                         (t_uint8)40                                            },
    };


    ///@brief Variable for decoding CYCLIC_DURATION
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_ApplicationInfo1_as[14] = {
    {APPSIG_SIGNAL_FMKCPU_MODSTATE,                         (t_uint8)0                                             },
    {APPSIG_SIGNAL_APPACT_MODSTATE,                         (t_uint8)3                                             },
    {APPSIG_SIGNAL_APPLGC_MODSTATE,                         (t_uint8)6                                             },
    {APPSIG_SIGNAL_APPSDM_MODSTATE,                         (t_uint8)9                                             },
    {APPSIG_SIGNAL_APPSIG_MODSTATE,                         (t_uint8)12                                            },
    {APPSIG_SIGNAL_APPSNS_MODSTATE,                         (t_uint8)15                                            },
    {APPSIG_SIGNAL_APPSPM_MODSTATE,                         (t_uint8)18                                            },
    {APPSIG_SIGNAL_FMKCDA_MODSTATE,                         (t_uint8)24                                            },
    {APPSIG_SIGNAL_FMKFDCAN_MODSTATE,                       (t_uint8)27                                            },
    {APPSIG_SIGNAL_FMKHRT_MODSTATE,                         (t_uint8)30                                            },
    {APPSIG_SIGNAL_FMKIO_MODSTATE,                          (t_uint8)33                                            },
    {APPSIG_SIGNAL_FMKSRL_MODSTATE,                         (t_uint8)36                                            },
    {APPSIG_SIGNAL_FMKTIM_MODSTATE,                         (t_uint8)21                                            },
    {APPSIG_SIGNAL_CYCLIC_DURATION,                         (t_uint8)40                                            },
    };


    ///@brief Variable for decoding CYCLIC_DURATION
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_ApplicationInfo2_as[14] = {
    {APPSIG_SIGNAL_FMKCPU_MODSTATE,                         (t_uint8)0                                             },
    {APPSIG_SIGNAL_APPACT_MODSTATE,                         (t_uint8)3                                             },
    {APPSIG_SIGNAL_APPLGC_MODSTATE,                         (t_uint8)6                                             },
    {APPSIG_SIGNAL_APPSDM_MODSTATE,                         (t_uint8)9                                             },
    {APPSIG_SIGNAL_APPSIG_MODSTATE,                         (t_uint8)12                                            },
    {APPSIG_SIGNAL_APPSNS_MODSTATE,                         (t_uint8)15                                            },
    {APPSIG_SIGNAL_APPSPM_MODSTATE,                         (t_uint8)18                                            },
    {APPSIG_SIGNAL_FMKCDA_MODSTATE,                         (t_uint8)24                                            },
    {APPSIG_SIGNAL_FMKFDCAN_MODSTATE,                       (t_uint8)27                                            },
    {APPSIG_SIGNAL_FMKHRT_MODSTATE,                         (t_uint8)30                                            },
    {APPSIG_SIGNAL_FMKIO_MODSTATE,                          (t_uint8)33                                            },
    {APPSIG_SIGNAL_FMKSRL_MODSTATE,                         (t_uint8)36                                            },
    {APPSIG_SIGNAL_FMKTIM_MODSTATE,                         (t_uint8)21                                            },
    {APPSIG_SIGNAL_CYCLIC_DURATION,                         (t_uint8)40                                            },
    };


    ///@brief Variable for decoding CYCLIC_DURATION
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_ApplicationDiagnostic0_as[4] = {
    {APPSIG_SIGNAL_SDM_DIAG_ITEM,                           (t_uint8)0                                             },
    {APPSIG_SIGNAL_SDM_DIAG_REPORT_STATUS,                  (t_uint8)16                                            },
    {APPSIG_SIGNAL_SDM_DIAG_DEBUG_INFO_1,                   (t_uint8)32                                            },
    {APPSIG_SIGNAL_SDM_DIAG_DEBUG_INFO_2,                   (t_uint8)48                                            },
    };


    ///@brief Variable for decoding SDM_DIAG_DEBUG_INFO_2
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_ApplicationDiagnostic1_as[4] = {
    {APPSIG_SIGNAL_SDM_DIAG_ITEM,                           (t_uint8)0                                             },
    {APPSIG_SIGNAL_SDM_DIAG_REPORT_STATUS,                  (t_uint8)16                                            },
    {APPSIG_SIGNAL_SDM_DIAG_DEBUG_INFO_1,                   (t_uint8)32                                            },
    {APPSIG_SIGNAL_SDM_DIAG_DEBUG_INFO_2,                   (t_uint8)48                                            },
    };


    ///@brief Variable for decoding SDM_DIAG_DEBUG_INFO_2
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_ApplicationDiagnostic2_as[4] = {
    {APPSIG_SIGNAL_SDM_DIAG_ITEM,                           (t_uint8)0                                             },
    {APPSIG_SIGNAL_SDM_DIAG_REPORT_STATUS,                  (t_uint8)16                                            },
    {APPSIG_SIGNAL_SDM_DIAG_DEBUG_INFO_1,                   (t_uint8)32                                            },
    {APPSIG_SIGNAL_SDM_DIAG_DEBUG_INFO_2,                   (t_uint8)48                                            },
    };


    ///@brief Variable for decoding SDM_DIAG_DEBUG_INFO_2
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_CTRL_MTR_XL_as[3] = {
    {APPSIG_SIGNAL_ACT_CTRL_MTR_XL_PLS,                     (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_XL_SPD,                     (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_XL_TRG,                     (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_CTRL_MTR_XL_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_CTRL_MTR_XR_as[3] = {
    {APPSIG_SIGNAL_ACT_CTRL_MTR_XR_PLS,                     (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_XR_SPD,                     (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_XR_TRG,                     (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_CTRL_MTR_XR_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_CTRL_MTR_Y_as[3] = {
    {APPSIG_SIGNAL_ACT_CTRL_MTR_Y_PLS,                      (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_Y_SPD,                      (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_Y_TRG,                      (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_CTRL_MTR_Y_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_CTRL_MTR_Z_as[3] = {
    {APPSIG_SIGNAL_ACT_CTRL_MTR_Z_PLS,                      (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_Z_SPD,                      (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_Z_TRG,                      (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_CTRL_MTR_Z_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_CTRL_MTR_HD_KNF_as[3] = {
    {APPSIG_SIGNAL_ACT_CTRL_MTR_HD_KNF_PLS,                 (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_HD_KNF_SPD,                 (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_HD_KNF_TRG,                 (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_CTRL_MTR_HD_KNF_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_CTRL_MTR_HD_CNTR_KNF_as[3] = {
    {APPSIG_SIGNAL_ACT_CTRL_MTR_HD_CNTR_KNF_PLS,            (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_HD_CNTR_KNF_SPD,            (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_HD_CNTR_KNF_TRG,            (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_CTRL_MTR_HD_CNTR_KNF_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_CTRL_MTR_HD_HOLD_as[3] = {
    {APPSIG_SIGNAL_ACT_CTRL_MTR_HD_HOLD_PLS,                (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_HD_HOLD_SPD,                (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_HD_HOLD_TRG,                (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_CTRL_MTR_HD_HOLD_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_CTRL_MTR_WHL_AV_L_as[3] = {
    {APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_L_PLS,               (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_L_SPD,               (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_L_TRG,               (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_CTRL_MTR_WHL_AV_L_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_CTRL_MTR_WHL_AV_R_as[3] = {
    {APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_R_PLS,               (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_R_SPD,               (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_R_TRG,               (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_CTRL_MTR_WHL_AV_R_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_SET_MTR_XL_as[3] = {
    {APPSIG_SIGNAL_ACT_SET_MTR_XL_PLS,                      (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_SET_MTR_XL_SPD,                      (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_SET_MTR_XL_TRG,                      (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_SET_MTR_XL_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_SET_MTR_XR_as[3] = {
    {APPSIG_SIGNAL_ACT_SET_MTR_XR_PLS,                      (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_SET_MTR_XR_SPD,                      (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_SET_MTR_XR_TRG,                      (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_SET_MTR_XR_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_SET_MTR_Y_as[3] = {
    {APPSIG_SIGNAL_ACT_SET_MTR_Y_PLS,                       (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_SET_MTR_Y_SPD,                       (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_SET_MTR_Y_TRG,                       (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_SET_MTR_Y_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_SET_MTR_Z_as[3] = {
    {APPSIG_SIGNAL_ACT_SET_MTR_Z_PLS,                       (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_SET_MTR_Z_SPD,                       (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_SET_MTR_Z_TRG,                       (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_SET_MTR_Z_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_SET_MTR_HD_KNF_as[3] = {
    {APPSIG_SIGNAL_ACT_SET_MTR_HD_KNF_PLS,                  (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_SET_MTR_HD_KNF_SPD,                  (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_SET_MTR_HD_KNF_TRG,                  (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_SET_MTR_HD_KNF_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_SET_MTR_HD_CNTR_KNF_as[3] = {
    {APPSIG_SIGNAL_ACT_SET_MTR_HD_CNTR_KNF_PLS,             (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_SET_MTR_HD_CNTR_KNF_SPD,             (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_SET_MTR_HD_CNTR_KNF_TRG,             (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_SET_MTR_HD_CNTR_KNF_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_SET_MTR_HD_HOLD_as[3] = {
    {APPSIG_SIGNAL_ACT_SET_MTR_HD_HOLD_PLS,                 (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_SET_MTR_HD_HOLD_SPD,                 (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_SET_MTR_HD_HOLD_TRG,                 (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_SET_MTR_HD_HOLD_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_SET_MTR_WHL_AV_L_as[3] = {
    {APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_L_PLS,                (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_L_SPD,                (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_L_TRG,                (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_SET_MTR_WHL_AV_L_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_SET_MTR_WHL_AV_R_as[3] = {
    {APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_R_PLS,                (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_R_SPD,                (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_R_TRG,                (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_SET_MTR_WHL_AV_R_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_GET_MTR_XL_as[3] = {
    {APPSIG_SIGNAL_ACT_GET_MTR_XL_PLS,                      (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_GET_MTR_XL_SPD,                      (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_GET_MTR_XL_TRG,                      (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_GET_MTR_XL_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_GET_MTR_XR_as[3] = {
    {APPSIG_SIGNAL_ACT_GET_MTR_XR_PLS,                      (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_GET_MTR_XR_SPD,                      (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_GET_MTR_XR_TRG,                      (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_GET_MTR_XR_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_GET_MTR_Y_as[3] = {
    {APPSIG_SIGNAL_ACT_GET_MTR_Y_PLS,                       (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_GET_MTR_Y_SPD,                       (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_GET_MTR_Y_TRG,                       (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_GET_MTR_Y_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_GET_MTR_Z_as[3] = {
    {APPSIG_SIGNAL_ACT_GET_MTR_Z_PLS,                       (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_GET_MTR_Z_SPD,                       (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_GET_MTR_Z_TRG,                       (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_GET_MTR_Z_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_GET_MTR_HD_KNF_as[3] = {
    {APPSIG_SIGNAL_ACT_GET_MTR_HD_KNF_PLS,                  (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_GET_MTR_HD_KNF_SPD,                  (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_GET_MTR_HD_KNF_TRG,                  (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_GET_MTR_HD_KNF_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_GET_MTR_HD_CNTR_KNF_as[3] = {
    {APPSIG_SIGNAL_ACT_GET_MTR_HD_CNTR_KNF_PLS,             (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_GET_MTR_HD_CNTR_KNF_SPD,             (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_GET_MTR_HD_CNTR_KNF_TRG,             (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_GET_MTR_HD_CNTR_KNF_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_GET_MTR_HD_HOLD_as[3] = {
    {APPSIG_SIGNAL_ACT_GET_MTR_HD_HOLD_PLS,                 (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_GET_MTR_HD_HOLD_SPD,                 (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_GET_MTR_HD_HOLD_TRG,                 (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_GET_MTR_HD_HOLD_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_GET_MTR_WHL_AV_L_as[3] = {
    {APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_L_PLS,                (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_L_SPD,                (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_L_TRG,                (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_GET_MTR_WHL_AV_L_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_GET_MTR_WHL_AV_R_as[3] = {
    {APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_R_PLS,                (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_R_SPD,                (t_uint8)32                                            },
    {APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_R_TRG,                (t_uint8)48                                            },
    };


    ///@brief Variable for decoding ACT_GET_MTR_WHL_AV_R_TRG
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_GET_ACT_PWR_MTR_as[9] = {
    {APPSIG_SIGNAL_ACT_GET_PWR_MTR_XL_RLY,                  (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_GET_PWR_MTR_XR_RLY,                  (t_uint8)1                                             },
    {APPSIG_SIGNAL_ACT_GET_PWR_MTR_Y_RLY,                   (t_uint8)2                                             },
    {APPSIG_SIGNAL_ACT_GET_PWR_MTR_Z_RLY,                   (t_uint8)3                                             },
    {APPSIG_SIGNAL_ACT_GET_PWR_WHL_AV_L_RLY,                (t_uint8)4                                             },
    {APPSIG_SIGNAL_ACT_GET_PWR_WHL_AV_R_RLY,                (t_uint8)5                                             },
    {APPSIG_SIGNAL_ACT_GET_PWR_MTR_HD_KNF_RLY,              (t_uint8)6                                             },
    {APPSIG_SIGNAL_ACT_GET_PWR_MTR_HD_CNTR_KNF_RLY,         (t_uint8)7                                             },
    {APPSIG_SIGNAL_ACT_GET_PWR_MTR_HD_HOLD_RLY,             (t_uint8)8                                             },
    };


    ///@brief Variable for decoding ACT_GET_PWR_MTR_HD_HOLD_RLY
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPSNS_GET_ECDR_GTRY_XL_XR_as[4] = {
    {APPSIG_SIGNAL_SNS_ECDR_XL_POS,                         (t_uint8)0                                             },
    {APPSIG_SIGNAL_SNS_ECDR_XL_SPD,                         (t_uint8)16                                            },
    {APPSIG_SIGNAL_SNS_ECDR_XR_POS,                         (t_uint8)32                                            },
    {APPSIG_SIGNAL_SNS_ECDR_XR_SPD,                         (t_uint8)48                                            },
    };


    ///@brief Variable for decoding SNS_ECDR_XR_SPD
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPSNS_GET_ECDR_GTRY_Y_Z_as[4] = {
    {APPSIG_SIGNAL_SNS_ECDR_XL_POS,                         (t_uint8)0                                             },
    {APPSIG_SIGNAL_SNS_ECDR_XL_SPD,                         (t_uint8)16                                            },
    {APPSIG_SIGNAL_SNS_ECDR_XR_POS,                         (t_uint8)32                                            },
    {APPSIG_SIGNAL_SNS_ECDR_XR_SPD,                         (t_uint8)48                                            },
    };


    ///@brief Variable for decoding SNS_ECDR_XR_SPD
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_SEND_STATUS_ECU_0_as[1] = {
    {APPSIG_SIGNAL_PRM_FLAG_PARAM_SEND_OK,                  (t_uint8)0                                             },
    };


    ///@brief Variable for decoding PRM_FLAG_PARAM_SEND_OK
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_SEND_STATUS_ECU_1_as[1] = {
    {APPSIG_SIGNAL_PRM_FLAG_PARAM_SEND_OK,                  (t_uint8)0                                             },
    };


    ///@brief Variable for decoding PRM_FLAG_PARAM_SEND_OK
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_SEND_STATUS_ECU_2_as[1] = {
    {APPSIG_SIGNAL_PRM_FLAG_PARAM_SEND_OK,                  (t_uint8)0                                             },
    };


    ///@brief Variable for decoding PRM_FLAG_PARAM_SEND_OK
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_GTRY_X_RAMP_CTRL_as[3] = {
    {APPSIG_SIGNAL_PRM_GTRY_X_RMP_CTRL_KFACTOR,             (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_GTRY_X_RMP_CTRL_SLOP_SPD,            (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_GTRY_X_RMP_CTRL_NB_STEP,             (t_uint8)32                                            },
    };


    ///@brief Variable for decoding PRM_GTRY_X_RMP_CTRL_NB_STEP
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_GTRY_Y_RAMP_CTRL_as[3] = {
    {APPSIG_SIGNAL_PRM_GTRY_Y_RMP_CTRL_KFACTOR,             (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_GTRY_Y_RMP_CTRL_SLOP_SPD,            (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_GTRY_Y_RMP_CTRL_NB_STEP,             (t_uint8)32                                            },
    };


    ///@brief Variable for decoding PRM_GTRY_Y_RMP_CTRL_NB_STEP
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_GTRY_Z_RAMP_CTRL_as[3] = {
    {APPSIG_SIGNAL_PRM_GTRY_Z_RMP_CTRL_KFACTOR,             (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_GTRY_Z_RMP_CTRL_SLOP_SPD,            (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_GTRY_Z_RMP_CTRL_NB_STEP,             (t_uint8)32                                            },
    };


    ///@brief Variable for decoding PRM_GTRY_Z_RMP_CTRL_NB_STEP
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_GTRY_SPD_CFG1_as[3] = {
    {APPSIG_SIGNAL_PRM_GTRY_PULSE_ITER_MAX,                 (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_GTRY_X_SPD_MAX,                      (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_GTRY_X_SPD_MIN,                      (t_uint8)32                                            },
    };


    ///@brief Variable for decoding PRM_GTRY_X_SPD_MIN
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_GTRY_SPD_CFG_2_as[2] = {
    {APPSIG_SIGNAL_PRM_GTRY_Y_SPD_MIN,                      (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_GTRY_Y_SPD_MAX,                      (t_uint8)16                                            },
    };


    ///@brief Variable for decoding PRM_GTRY_Y_SPD_MAX
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_GTRY_SPD_CFG_3_as[2] = {
    {APPSIG_SIGNAL_PRM_GTRY_Z_SPD_MAX,                      (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_GTRY_Z_SPD_MIN,                      (t_uint8)16                                            },
    };


    ///@brief Variable for decoding PRM_GTRY_Z_SPD_MIN
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_LGC_GTRY_CMD_SPHERIC_as[3] = {
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_RAYON,              (t_uint8)0                                             },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_THETHA,             (t_uint8)16                                            },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_PHI,                (t_uint8)32                                            },
    };


    ///@brief Variable for decoding LGC_GTRY_CMD_SIG_POS_PHI
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_GTRY_PARAM_1_as[3] = {
    {APPSIG_SIGNAL_PRM_GTRY_ALGO_CPTE_TYPE,                 (t_uint8)24                                            },
    {APPSIG_SIGNAL_PRM_GTRY_CALIB_TYPE,                     (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_GTRY_SENDITER_TYPE,                  (t_uint8)20                                            },
    };


    ///@brief Variable for decoding PRM_GTRY_SENDITER_TYPE
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_GTRY_PARAM_2_as[3] = {
    {APPSIG_SIGNAL_PRM_GTRY_AXE_X_PULSE_PER_MM,             (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_GTRY_AXE_Y_PULSE_PER_MM,             (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_GTRY_AXE_Z_PULSE_PER_MM,             (t_uint8)32                                            },
    };


    ///@brief Variable for decoding PRM_GTRY_AXE_Z_PULSE_PER_MM
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_GTRY_PARAM_3_as[3] = {
    {APPSIG_SIGNAL_PRM_GTRY_AXE_X_LEN,                      (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_GTRY_AXE_Y_LEN,                      (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_GTRY_AXE_Z_LEN,                      (t_uint8)32                                            },
    };


    ///@brief Variable for decoding PRM_GTRY_AXE_Z_LEN
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_GTRY_PARAM_4_as[3] = {
    {APPSIG_SIGNAL_PRM_GTRY_X_CALIB_OFFSET,                 (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_GTRY_Y_CALIB_OFFSET,                 (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_GTRY_Z_CALIB_OFFSET,                 (t_uint8)32                                            },
    };


    ///@brief Variable for decoding PRM_GTRY_Z_CALIB_OFFSET
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_GTRY_PARAM_SAFE_HEIGHT_as[3] = {
    {APPSIG_SIGNAL_PRM_GTRY_AXE_X_SAFE_HEIGHT,              (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_GTRY_AXE_Y_SAFE_HEIGHT,              (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_GTRY_AXE_Z_SAFE_HEIGHT,              (t_uint8)32                                            },
    };


    ///@brief Variable for decoding PRM_GTRY_AXE_Z_SAFE_HEIGHT
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_LGC_CL42T_MOTORS_INFO_GTRY_as[24] = {
    {APPSIG_SIGNAL_CL42T_MTR_1_STATE,                       (t_uint8)0                                             },
    {APPSIG_SIGNAL_CL42T_MTR_2_STATE,                       (t_uint8)1                                             },
    {APPSIG_SIGNAL_CL42T_MTR_3_STATE,                       (t_uint8)2                                             },
    {APPSIG_SIGNAL_CL42T_MTR_4_STATE,                       (t_uint8)3                                             },
    {APPSIG_SIGNAL_CL42T_MTR_1_CW_ENDSTOP,                  (t_uint8)4                                             },
    {APPSIG_SIGNAL_CL42T_MTR_2_CW_ENDSTOP,                  (t_uint8)5                                             },
    {APPSIG_SIGNAL_CL42T_MTR_3_CW_ENDSTOP,                  (t_uint8)6                                             },
    {APPSIG_SIGNAL_CL42T_MTR_4_CW_ENDSTOP,                  (t_uint8)7                                             },
    {APPSIG_SIGNAL_CL42T_MTR_1_CCW_ENDSTOP,                 (t_uint8)8                                             },
    {APPSIG_SIGNAL_CL42T_MTR_2_CCW_ENDSTOP,                 (t_uint8)9                                             },
    {APPSIG_SIGNAL_CL42T_MTR_3_CCW_ENDSTOP,                 (t_uint8)10                                            },
    {APPSIG_SIGNAL_CL42T_MTR_4_CCW_ENDSTOP,                 (t_uint8)11                                            },
    {APPSIG_SIGNAL_CL42T_MTR_1_DIRECTION,                   (t_uint8)12                                            },
    {APPSIG_SIGNAL_CL42T_MTR_2_DIRECTION,                   (t_uint8)13                                            },
    {APPSIG_SIGNAL_CL42T_MTR_3_DIRECTION,                   (t_uint8)14                                            },
    {APPSIG_SIGNAL_CL42T_MTR_4_DIRECTION,                   (t_uint8)15                                            },
    {APPSIG_SIGNAL_CL42T_MTR_1_DEADTIME,                    (t_uint8)16                                            },
    {APPSIG_SIGNAL_CL42T_MTR_2_DEADTIME,                    (t_uint8)17                                            },
    {APPSIG_SIGNAL_CL42T_MTR_3_DEADTIME,                    (t_uint8)18                                            },
    {APPSIG_SIGNAL_CL42T_MTR_4_DEADTIME,                    (t_uint8)19                                            },
    {APPSIG_SIGNAL_CL42T_MTR_4_HEALTH,                      (t_uint8)20                                            },
    {APPSIG_SIGNAL_CL42T_MTR_3_HEALTH,                      (t_uint8)24                                            },
    {APPSIG_SIGNAL_CL42T_MTR_2_HEALTH,                      (t_uint8)28                                            },
    {APPSIG_SIGNAL_CL42T_MTR_1_HEALTH,                      (t_uint8)32                                            },
    };


    ///@brief Variable for decoding CL42T_MTR_1_HEALTH
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_LGC_CL42T_MOTORS_INFO_HEAD_GTRY_as[18] = {
    {APPSIG_SIGNAL_CL42T_MTR_5_STATE,                       (t_uint8)0                                             },
    {APPSIG_SIGNAL_CL42T_MTR_6_STATE,                       (t_uint8)1                                             },
    {APPSIG_SIGNAL_CL42T_MTR_7_STATE,                       (t_uint8)2                                             },
    {APPSIG_SIGNAL_CL42T_MTR_5_CW_ENDSTOP,                  (t_uint8)3                                             },
    {APPSIG_SIGNAL_CL42T_MTR_6_CW_ENDSTOP,                  (t_uint8)4                                             },
    {APPSIG_SIGNAL_CL42T_MTR_7_CW_ENDSTOP,                  (t_uint8)5                                             },
    {APPSIG_SIGNAL_CL42T_MTR_5_CCW_ENDSTOP,                 (t_uint8)6                                             },
    {APPSIG_SIGNAL_CL42T_MTR_6_CCW_ENDSTOP,                 (t_uint8)7                                             },
    {APPSIG_SIGNAL_CL42T_MTR_7_CCW_ENDSTOP,                 (t_uint8)8                                             },
    {APPSIG_SIGNAL_CL42T_MTR_5_DIRECTION,                   (t_uint8)9                                             },
    {APPSIG_SIGNAL_CL42T_MTR_6_DIRECTION,                   (t_uint8)10                                            },
    {APPSIG_SIGNAL_CL42T_MTR_7_DIRECTION,                   (t_uint8)11                                            },
    {APPSIG_SIGNAL_CL42T_MTR_5_DEADTIME,                    (t_uint8)12                                            },
    {APPSIG_SIGNAL_CL42T_MTR_6_DEADTIME,                    (t_uint8)13                                            },
    {APPSIG_SIGNAL_CL42T_MTR_7_DEADTIME,                    (t_uint8)14                                            },
    {APPSIG_SIGNAL_CL42T_MTR_5_HEALTH,                      (t_uint8)15                                            },
    {APPSIG_SIGNAL_CL42T_MTR_6_HEALTH,                      (t_uint8)19                                            },
    {APPSIG_SIGNAL_CL42T_MTR_7_HEALTH,                      (t_uint8)23                                            },
    };


    ///@brief Variable for decoding CL42T_MTR_7_HEALTH
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_LGC_CL42T_MOTORS_INFO_MOTION_as[12] = {
    {APPSIG_SIGNAL_CL42T_MTR_8_STATE,                       (t_uint8)0                                             },
    {APPSIG_SIGNAL_CL42T_MTR_9_STATE,                       (t_uint8)1                                             },
    {APPSIG_SIGNAL_CL42T_MTR_8_CW_ENDSTOP,                  (t_uint8)2                                             },
    {APPSIG_SIGNAL_CL42T_MTR_9_CW_ENDSTOP,                  (t_uint8)3                                             },
    {APPSIG_SIGNAL_CL42T_MTR_8_CCW_ENDSTOP,                 (t_uint8)4                                             },
    {APPSIG_SIGNAL_CL42T_MTR_9_CCW_ENDSTOP,                 (t_uint8)5                                             },
    {APPSIG_SIGNAL_CL42T_MTR_8_DIRECTION,                   (t_uint8)6                                             },
    {APPSIG_SIGNAL_CL42T_MTR_9_DIRECTION,                   (t_uint8)7                                             },
    {APPSIG_SIGNAL_CL42T_MTR_8_DEADTIME,                    (t_uint8)8                                             },
    {APPSIG_SIGNAL_CL42T_MTR_9_DEADTIME,                    (t_uint8)9                                             },
    {APPSIG_SIGNAL_CL42T_MTR_8_HEALTH,                      (t_uint8)10                                            },
    {APPSIG_SIGNAL_CL42T_MTR_9_HEALTH,                      (t_uint8)14                                            },
    };


    ///@brief Variable for decoding CL42T_MTR_9_HEALTH
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_LGC_GTRY_CMD_POSITION_as[3] = {
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_X,                  (t_uint8)0                                             },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_Y,                  (t_uint8)16                                            },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_Z,                  (t_uint8)32                                            },
    };


    ///@brief Variable for decoding LGC_GTRY_CMD_SIG_POS_Z
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_LGC_GTRY_CMD_STEPS_as[6] = {
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_X,                 (t_uint8)0                                             },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_Y,                 (t_uint8)16                                            },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_Z,                 (t_uint8)32                                            },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_X,                  (t_uint8)48                                            },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_Y,                  (t_uint8)49                                            },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_Z,                  (t_uint8)50                                            },
    };


    ///@brief Variable for decoding LGC_GTRY_CMD_SIG_DIR_Z
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_LGC_GTRY_POSITION_as[4] = {
    {APPSIG_SIGNAL_GTRY_AXE_X_POSITION,                     (t_uint8)0                                             },
    {APPSIG_SIGNAL_GTRY_AXE_Y_POSITION,                     (t_uint8)16                                            },
    {APPSIG_SIGNAL_GTRY_AXE_Z_POSITION,                     (t_uint8)32                                            },
    {APPSIG_SIGNAL_GTRY_ALGO_COMPUTE_TIME,                  (t_uint8)48                                            },
    };


    ///@brief Variable for decoding GTRY_ALGO_COMPUTE_TIME
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_LGC_GTRY_DEBUG_FSM_as[7] = {
    {APPSIG_SIGNAL_LGC_GTRY_FSM_STS,                        (t_uint8)0                                             },
    {APPSIG_SIGNAL_LGC_GTRY_FSM_CALIB,                      (t_uint8)4                                             },
    {APPSIG_SIGNAL_LGC_GTRY_FSM_CLB_AXE_X,                  (t_uint8)8                                             },
    {APPSIG_SIGNAL_LGC_GTRY_FSM_CLB_AXE_Y,                  (t_uint8)12                                            },
    {APPSIG_SIGNAL_LGC_GTRY_FSM_CLB_AXE_Z,                  (t_uint8)16                                            },
    {APPSIG_SIGNAL_LGC_GTRY_FSM_OPE,                        (t_uint8)20                                            },
    {APPSIG_SIGNAL_LGC_GTRY_FSM_OPE_CMD_PRCSS,              (t_uint8)24                                            },
    };


    ///@brief Serial Message Information
    const t_sAPPSIG_MsgCfg c_AppSig_SrlMsgCfg_as[APPSIG_SRL_MSG_NB] = {
    //  Identifier                                          Direction                                                CyclicSend                                                 TimeOut                                                         Sig Cfg                                         nbSignal
    };

    ///@brief CAN Message Information
    const t_sAPPSIG_MsgCfg c_AppSig_CanMsgCfg_as[APPSIG_CAN_MSG_NB] = {
    //  Identifier                                          Direction                                                CyclicSend                                                 TimeOut                                                         Sig Cfg                                         nbSignal
    {APPSIG_CAN_ID_APPLICATIONINFO0,                         {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)500,                                          (t_uint16)65535,                                        c_AppSig_Can_ApplicationInfo0_as,                       (t_uint8)14}, // APPSIG_CAN_APPLICATIONINFO0
    {APPSIG_CAN_ID_APPLICATIONINFO1,                         {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)500,                                          (t_uint16)65535,                                        c_AppSig_Can_ApplicationInfo1_as,                       (t_uint8)14}, // APPSIG_CAN_APPLICATIONINFO1
    {APPSIG_CAN_ID_APPLICATIONINFO2,                         {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX},          (t_uint16)500,                                          (t_uint16)65535,                                        c_AppSig_Can_ApplicationInfo2_as,                       (t_uint8)14}, // APPSIG_CAN_APPLICATIONINFO2
    {APPSIG_CAN_ID_APPLICATIONDIAGNOSTIC0,                   {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)1000,                                         (t_uint16)65535,                                        c_AppSig_Can_ApplicationDiagnostic0_as,                 (t_uint8)4}, // APPSIG_CAN_APPLICATIONDIAGNOSTIC0
    {APPSIG_CAN_ID_APPLICATIONDIAGNOSTIC1,                   {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)1000,                                         (t_uint16)65535,                                        c_AppSig_Can_ApplicationDiagnostic1_as,                 (t_uint8)4}, // APPSIG_CAN_APPLICATIONDIAGNOSTIC1
    {APPSIG_CAN_ID_APPLICATIONDIAGNOSTIC2,                   {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX},          (t_uint16)1000,                                         (t_uint16)65535,                                        c_AppSig_Can_ApplicationDiagnostic2_as,                 (t_uint8)4}, // APPSIG_CAN_APPLICATIONDIAGNOSTIC2
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_XL,                       {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_XL_as,                     (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_XL
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_XR,                       {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_XR_as,                     (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_XR
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_Y,                        {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_Y_as,                      (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_Y
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_Z,                        {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_Z_as,                      (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_Z
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_HD_KNF,                   {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_HD_KNF_as,                 (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_HD_KNF
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_HD_CNTR_KNF,              {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_HD_CNTR_KNF_as,            (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_HD_CNTR_KNF
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_HD_HOLD,                  {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_HD_HOLD_as,                (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_HD_HOLD
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_WHL_AV_L,                 {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_WHL_AV_L_as,               (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_WHL_AV_L
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_WHL_AV_R,                 {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_WHL_AV_R_as,               (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_WHL_AV_R
    {APPSIG_CAN_ID_APPACT_SET_MTR_XL,                        {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_XL_as,                      (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_XL
    {APPSIG_CAN_ID_APPACT_SET_MTR_XR,                        {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_XR_as,                      (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_XR
    {APPSIG_CAN_ID_APPACT_SET_MTR_Y,                         {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_Y_as,                       (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_Y
    {APPSIG_CAN_ID_APPACT_SET_MTR_Z,                         {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_Z_as,                       (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_Z
    {APPSIG_CAN_ID_APPACT_SET_MTR_HD_KNF,                    {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_HD_KNF_as,                  (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_HD_KNF
    {APPSIG_CAN_ID_APPACT_SET_MTR_HD_CNTR_KNF,               {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_HD_CNTR_KNF_as,             (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_HD_CNTR_KNF
    {APPSIG_CAN_ID_APPACT_SET_MTR_HD_HOLD,                   {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_HD_HOLD_as,                 (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_HD_HOLD
    {APPSIG_CAN_ID_APPACT_SET_MTR_WHL_AV_L,                  {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_WHL_AV_L_as,                (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_WHL_AV_L
    {APPSIG_CAN_ID_APPACT_SET_MTR_WHL_AV_R,                  {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_WHL_AV_R_as,                (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_WHL_AV_R
    {APPSIG_CAN_ID_APPACT_GET_MTR_XL,                        {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_GET_MTR_XL_as,                      (t_uint8)3}, // APPSIG_CAN_APPACT_GET_MTR_XL
    {APPSIG_CAN_ID_APPACT_GET_MTR_XR,                        {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_GET_MTR_XR_as,                      (t_uint8)3}, // APPSIG_CAN_APPACT_GET_MTR_XR
    {APPSIG_CAN_ID_APPACT_GET_MTR_Y,                         {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_GET_MTR_Y_as,                       (t_uint8)3}, // APPSIG_CAN_APPACT_GET_MTR_Y
    {APPSIG_CAN_ID_APPACT_GET_MTR_Z,                         {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_GET_MTR_Z_as,                       (t_uint8)3}, // APPSIG_CAN_APPACT_GET_MTR_Z
    {APPSIG_CAN_ID_APPACT_GET_MTR_HD_KNF,                    {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_GET_MTR_HD_KNF_as,                  (t_uint8)3}, // APPSIG_CAN_APPACT_GET_MTR_HD_KNF
    {APPSIG_CAN_ID_APPACT_GET_MTR_HD_CNTR_KNF,               {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_GET_MTR_HD_CNTR_KNF_as,             (t_uint8)3}, // APPSIG_CAN_APPACT_GET_MTR_HD_CNTR_KNF
    {APPSIG_CAN_ID_APPACT_GET_MTR_HD_HOLD,                   {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_GET_MTR_HD_HOLD_as,                 (t_uint8)3}, // APPSIG_CAN_APPACT_GET_MTR_HD_HOLD
    {APPSIG_CAN_ID_APPACT_GET_MTR_WHL_AV_L,                  {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_GET_MTR_WHL_AV_L_as,                (t_uint8)3}, // APPSIG_CAN_APPACT_GET_MTR_WHL_AV_L
    {APPSIG_CAN_ID_APPACT_GET_MTR_WHL_AV_R,                  {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_GET_MTR_WHL_AV_R_as,                (t_uint8)3}, // APPSIG_CAN_APPACT_GET_MTR_WHL_AV_R
    {APPSIG_CAN_ID_APPACT_GET_ACT_PWR_MTR,                   {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX},          (t_uint16)50,                                           (t_uint16)200,                                          c_AppSig_Can_APPACT_GET_ACT_PWR_MTR_as,                 (t_uint8)9}, // APPSIG_CAN_APPACT_GET_ACT_PWR_MTR
    {APPSIG_CAN_ID_APPSNS_GET_ECDR_GTRY_XL_XR,               {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX},          (t_uint16)50,                                           (t_uint16)200,                                          c_AppSig_Can_APPSNS_GET_ECDR_GTRY_XL_XR_as,             (t_uint8)4}, // APPSIG_CAN_APPSNS_GET_ECDR_GTRY_XL_XR
    {APPSIG_CAN_ID_APPSNS_GET_ECDR_GTRY_Y_Z,                 {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX},          (t_uint16)50,                                           (t_uint16)200,                                          c_AppSig_Can_APPSNS_GET_ECDR_GTRY_Y_Z_as,               (t_uint8)4}, // APPSIG_CAN_APPSNS_GET_ECDR_GTRY_Y_Z
    {APPSIG_CAN_ID_PRM_SEND_STATUS_ECU_0,                    {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_SEND_STATUS_ECU_0_as,                  (t_uint8)1}, // APPSIG_CAN_PRM_SEND_STATUS_ECU_0
    {APPSIG_CAN_ID_PRM_SEND_STATUS_ECU_1,                    {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_SEND_STATUS_ECU_1_as,                  (t_uint8)1}, // APPSIG_CAN_PRM_SEND_STATUS_ECU_1
    {APPSIG_CAN_ID_PRM_SEND_STATUS_ECU_2,                    {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_RX},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_SEND_STATUS_ECU_2_as,                  (t_uint8)1}, // APPSIG_CAN_PRM_SEND_STATUS_ECU_2
    {APPSIG_CAN_ID_PRM_GTRY_X_RAMP_CTRL,                     {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_GTRY_X_RAMP_CTRL_as,                   (t_uint8)3}, // APPSIG_CAN_PRM_GTRY_X_RAMP_CTRL
    {APPSIG_CAN_ID_PRM_GTRY_Y_RAMP_CTRL,                     {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_GTRY_Y_RAMP_CTRL_as,                   (t_uint8)3}, // APPSIG_CAN_PRM_GTRY_Y_RAMP_CTRL
    {APPSIG_CAN_ID_PRM_GTRY_Z_RAMP_CTRL,                     {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_GTRY_Z_RAMP_CTRL_as,                   (t_uint8)3}, // APPSIG_CAN_PRM_GTRY_Z_RAMP_CTRL
    {APPSIG_CAN_ID_PRM_GTRY_SPD_CFG1,                        {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_GTRY_SPD_CFG1_as,                      (t_uint8)3}, // APPSIG_CAN_PRM_GTRY_SPD_CFG1
    {APPSIG_CAN_ID_PRM_GTRY_SPD_CFG_2,                       {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_GTRY_SPD_CFG_2_as,                     (t_uint8)2}, // APPSIG_CAN_PRM_GTRY_SPD_CFG_2
    {APPSIG_CAN_ID_PRM_GTRY_SPD_CFG_3,                       {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_GTRY_SPD_CFG_3_as,                     (t_uint8)2}, // APPSIG_CAN_PRM_GTRY_SPD_CFG_3
    {APPSIG_CAN_ID_PRM_LGC_GTRY_CMD_SPHERIC,                 {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_LGC_GTRY_CMD_SPHERIC_as,               (t_uint8)3}, // APPSIG_CAN_PRM_LGC_GTRY_CMD_SPHERIC
    {APPSIG_CAN_ID_PRM_GTRY_PARAM_1,                         {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_GTRY_PARAM_1_as,                       (t_uint8)3}, // APPSIG_CAN_PRM_GTRY_PARAM_1
    {APPSIG_CAN_ID_PRM_GTRY_PARAM_2,                         {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_GTRY_PARAM_2_as,                       (t_uint8)3}, // APPSIG_CAN_PRM_GTRY_PARAM_2
    {APPSIG_CAN_ID_PRM_GTRY_PARAM_3,                         {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_GTRY_PARAM_3_as,                       (t_uint8)3}, // APPSIG_CAN_PRM_GTRY_PARAM_3
    {APPSIG_CAN_ID_PRM_GTRY_PARAM_4,                         {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_GTRY_PARAM_4_as,                       (t_uint8)3}, // APPSIG_CAN_PRM_GTRY_PARAM_4
    {APPSIG_CAN_ID_PRM_GTRY_PARAM_SAFE_HEIGHT,               {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_GTRY_PARAM_SAFE_HEIGHT_as,             (t_uint8)3}, // APPSIG_CAN_PRM_GTRY_PARAM_SAFE_HEIGHT
    {APPSIG_CAN_ID_LGC_CL42T_MOTORS_INFO_GTRY,               {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_LGC_CL42T_MOTORS_INFO_GTRY_as,             (t_uint8)24}, // APPSIG_CAN_LGC_CL42T_MOTORS_INFO_GTRY
    {APPSIG_CAN_ID_LGC_CL42T_MOTORS_INFO_HEAD_GTRY,          {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_LGC_CL42T_MOTORS_INFO_HEAD_GTRY_as,        (t_uint8)18}, // APPSIG_CAN_LGC_CL42T_MOTORS_INFO_HEAD_GTRY
    {APPSIG_CAN_ID_LGC_CL42T_MOTORS_INFO_MOTION,             {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_LGC_CL42T_MOTORS_INFO_MOTION_as,           (t_uint8)12}, // APPSIG_CAN_LGC_CL42T_MOTORS_INFO_MOTION
    {APPSIG_CAN_ID_LGC_GTRY_CMD_POSITION,                    {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_LGC_GTRY_CMD_POSITION_as,                  (t_uint8)3}, // APPSIG_CAN_LGC_GTRY_CMD_POSITION
    {APPSIG_CAN_ID_LGC_GTRY_CMD_STEPS,                       {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_LGC_GTRY_CMD_STEPS_as,                     (t_uint8)6}, // APPSIG_CAN_LGC_GTRY_CMD_STEPS
    {APPSIG_CAN_ID_LGC_GTRY_POSITION,                        {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_LGC_GTRY_POSITION_as,                      (t_uint8)4}, // APPSIG_CAN_LGC_GTRY_POSITION
    {APPSIG_CAN_ID_LGC_GTRY_DEBUG_FSM,                       {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_LGC_GTRY_DEBUG_FSM_as,                     (t_uint8)7}, // APPSIG_CAN_LGC_GTRY_DEBUG_FSM
    };

    /* CAUTION : Automatic generated code section for Variable: End */
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APPSDM_CONFIGPRIVATE_H_INCLUDED           
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
