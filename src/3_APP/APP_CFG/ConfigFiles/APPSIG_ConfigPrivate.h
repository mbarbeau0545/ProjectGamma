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
    #define APPSIG_RX_BUFFER_SIZE ((t_uint8)60)

    ///@brief Number of data expected to be received 
    #define APPSIG_DATA_PAYLOAD_LEN  ((t_uint8)8)       // For CAN, SERIAL
    #define APPSIG_SRL_FRAME_PAYLOAD_LEN ((t_uint8)11)    // for Serial, 2 byte of start frame + 1 byte Identifier

    ///@brief start byte for serial comm 
    #define APPSIG_SRL_START_BYTE_0 ((t_uint8)0xAA)
    #define APPSIG_SRL_START_BYTE_1 ((t_uint8)0x55)

    ///@brief Information for can id serial
    #define APPSIG_CAN_ID_COMMON    ((t_uint32)0x18FF9000)
    #define APPSIG_CAN_ID_MASK      ((t_uint32)0x1FFFF000)
    ///@brief Configuration Gate for the module 
    #define APPSIG_PORTGATE_CAN         (APPSIG_MSG_ORIGIN_CAN)
    #define APPSIG_PORTGATE_CAN_NODE    (FMKFDCAN_NODE_1)

    #define APPSIG_PORTGATE_SRL         (APPSIG_MSG_ORIGIN_SRL)
    #define APPSIG_PORTGATE_SRL_LINE    (FMKSRL_SERIAL_LINE_3)

    #define APPSIG_PORTGATE_CFG         (1 << APPSIG_MSG_ORIGIN_CAN) // (1 << APPSIG_MSG_ORIGIN_SRL)
    /* CAUTION : Automatic generated code section for Define: Start */
    ///@brief Serial Message Id
    ///@brief CAN Message Id
    #define APPSIG_CAN_ID_APPLICATIONINFO0                         ((t_uint32)0x18ff9000)
    #define APPSIG_CAN_ID_APPLICATIONINFO1                         ((t_uint32)0x18ff9001)
    #define APPSIG_CAN_ID_APPLICATIONINFO2                         ((t_uint32)0x18ff9002)
    #define APPSIG_CAN_ID_CL42T_MOTORS_INFO                        ((t_uint32)0x80)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_XL                       ((t_uint32)0x18ff9100)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_XR                       ((t_uint32)0x18ff9101)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_Y                        ((t_uint32)0x18ff9102)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_Z                        ((t_uint32)0x18ff9103)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_HD_KNF                   ((t_uint32)0x18ff9104)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_HD_CNTR_KNF              ((t_uint32)0x18ff9105)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_HD_HOLD                  ((t_uint32)0x18ff9106)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_WHL_AV_L                 ((t_uint32)0x18ff9107)
    #define APPSIG_CAN_ID_APPACT_CTRL_MTR_WHL_AV_R                 ((t_uint32)0x18ff9108)
    #define APPSIG_CAN_ID_APPACT_CTRL_ACT_PWR_MTR                  ((t_uint32)0x18ff9109)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_XL                        ((t_uint32)0x18ff9110)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_XR                        ((t_uint32)0x18ff9111)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_Y                         ((t_uint32)0x18ff9112)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_Z                         ((t_uint32)0x18ff9113)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_HD_KNF                    ((t_uint32)0x18ff9114)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_HD_CNTR_KNF               ((t_uint32)0x18ff9115)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_HD_HOLD                   ((t_uint32)0x18ff9116)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_WHL_AV_L                  ((t_uint32)0x18ff9117)
    #define APPSIG_CAN_ID_APPACT_SET_MTR_WHL_AV_R                  ((t_uint32)0x18ff9118)
    #define APPSIG_CAN_ID_APPACT_SET_ACT_PWR_MTR                   ((t_uint32)0x18ff9119)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_XL                        ((t_uint32)0x18ff9120)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_XR                        ((t_uint32)0x18ff9121)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_Y                         ((t_uint32)0x18ff9122)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_Z                         ((t_uint32)0x18ff9123)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_HD_KNF                    ((t_uint32)0x18ff9124)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_HD_CNTR_KNF               ((t_uint32)0x18ff9125)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_HD_HOLD                   ((t_uint32)0x18ff9126)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_WHL_AV_L                  ((t_uint32)0x18ff9127)
    #define APPSIG_CAN_ID_APPACT_GET_MTR_WHL_AV_R                  ((t_uint32)0x18ff9128)
    #define APPSIG_CAN_ID_APPACT_GET_ACT_PWR_MTR                   ((t_uint32)0x18ff9129)
    #define APPSIG_CAN_ID_APPSNS_GET_ECDR_GTRY_XL_XR               ((t_uint32)0x18ff9130)
    #define APPSIG_CAN_ID_APPSNS_GET_ECDR_GTRY_Y_Z                 ((t_uint32)0x18ff9131)
    #define APPSIG_CAN_ID_PRM_LGC_GTRY_X_RAMP_CTRL                 ((t_uint32)0x91)
    #define APPSIG_CAN_ID_PRM_LGC_GTRY_Y_RAMP_CTRL                 ((t_uint32)0x93)
    #define APPSIG_CAN_ID_PRM_LGC_GTRY_Z_RAMP_CTRL                 ((t_uint32)0x94)
    #define APPSIG_CAN_ID_PRM_LGC_GTRY_SPD_CFG1                    ((t_uint32)0x95)
    #define APPSIG_CAN_ID_PRM_LGC_GTRY_SPD_CFG_2                   ((t_uint32)0x96)
    #define APPSIG_CAN_ID_PRM_LGC_GTRY_SPD_CFG_3                   ((t_uint32)0x97)
    #define APPSIG_CAN_ID_PRM_LGC_LGC_GTRY_CMD_POSITION            ((t_uint32)0x70)
    #define APPSIG_CAN_ID_PRM_LGC_LGC_GTRY_CMD_SPHERIC             ((t_uint32)0x71)
    #define APPSIG_CAN_ID_PRM_LGC_LGC_GTRY_CMD_STEPS               ((t_uint32)0x72)
    #define APPSIG_CAN_ID_PRM_LGC_GTRY_PARAM_1                     ((t_uint32)0x73)
    #define APPSIG_CAN_ID_PRM_LGC_GTRY_PARAM_2                     ((t_uint32)0x74)
    #define APPSIG_CAN_ID_PRM_LGC_GTRY_PARAM_3                     ((t_uint32)0x75)
    #define APPSIG_CAN_ID_PRM_LGC_GTRY_PARAM_4                     ((t_uint32)0x76)
    #define APPSIG_CAN_ID_PRM_LGC_GTRY_PARAM_SAFE_HEIGHT           ((t_uint32)0x77)
    #define APPSIG_CAN_ID_GTRY_DEBUG_POSITION                      ((t_uint32)0x82)
    #define APPSIG_CAN_ID_GTRY_DEBUG_FSM                           ((t_uint32)0x81)
    #define APPSIG_CAN_ID_APPSDM_DIAG_ITEM_1                       ((t_uint32)0x27)
    #define APPSIG_CAN_ID_APPSDM_DIAG_ITEM_2                       ((t_uint32)0x18)
    #define APPSIG_CAN_ID_APPSDM_DIAG_ITEM_3                       ((t_uint32)0x19)
    #define APPSIG_CAN_ID_APPSDM_DIAG_ITEM_4                       ((t_uint32)0x20)
    #define APPSIG_CAN_ID_APPSDM_DIAG_ITEM_5                       ((t_uint32)0x21)
    #define APPSIG_CAN_ID_APPSDM_DIAG_ITEM_6                       ((t_uint32)0x22)
    #define APPSIG_CAN_ID_APPSDM_DIAG_ITEM_7                       ((t_uint32)0x23)
    #define APPSIG_CAN_ID_APPSDM_DIAG_ITEM_8                       ((t_uint32)0x24)
    #define APPSIG_CAN_ID_APPSDM_DIAG_ITEM_9                       ((t_uint32)0x25)
    #define APPSIG_CAN_ID_APPSDM_DIAG_ITEM_10                      ((t_uint32)0x26)
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
        t_sint16 offset_s16;                     //---- offset to add / soustract signal ----//     
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
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_FMKCPU_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_FMKCDA_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_FMKSRL_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_FMKFDCAN_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_FMKIO_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_FMKHRT_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_FMKTIM_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_APPSIG_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_APPSYS_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_APPSNS_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_APPACT_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_APPLGC_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_APPSDM_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_APPSPM_MODSTATE
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CYCLIC_DURATION
        {(t_uint8)12,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_FASTTASKDURATION
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_XL_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_XL_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_XR_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_XR_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_Y_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_Y_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_Z_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_Z_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_WHL_AV_L_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_WHL_AV_L_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_WHL_AV_R_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_WHL_AV_R_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_HD_KNF_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_HD_KNF_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_HD_CNTR_KNF_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_HD_CNTR_KNF_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_HD_HOLD_POS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_ECDR_HD_HOLD_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_HD_UP_LEFT_DIST
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_HD_DWN_LEFT_DIST
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_HD_UP_RIGHT_DIST
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_HD_DWN_RIGHT_DIST
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_XL_TRQ
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_XR_TRQ
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_Y_TRQ
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_Z_TRQ
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_WHL_AV_L_TRQ
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_WHL_AV_R_TRQ
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_HD_KNF_TRQ
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_CNTR_KNF_TRQ
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SNS_TRQ_MTR_HD_HOLD_TRQ
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_XL_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_XL_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_XL_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_XR_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_XR_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_XR_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_Y_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_Y_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_Y_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_Z_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_Z_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_Z_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_HD_KNF_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_HD_KNF_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_HD_KNF_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_HD_CNTR_KNF_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_HD_CNTR_KNF_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_HD_CNTR_KNF_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_HD_HOLD_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_HD_HOLD_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_HD_HOLD_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_L_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_L_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_L_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_R_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_R_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_R_TRG
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_PWR_MTR_XL_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_PWR_MTR_XR_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_PWR_MTR_Y_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_PWR_MTR_Z_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_PWR_WHL_AV_L_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_PWR_WHL_AV_R_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_PWR_MTR_HD_KNF_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_PWR_MTR_HD_CNTR_KNF_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_SET_PWR_MTR_HD_HOLD_RLY
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_XL_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_XL_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_XL_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_XR_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_XR_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_XR_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_Y_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_Y_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_Y_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_Z_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_Z_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_Z_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_HD_KNF_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_HD_KNF_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_HD_KNF_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_HD_CNTR_KNF_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_HD_CNTR_KNF_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_HD_CNTR_KNF_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_HD_HOLD_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_HD_HOLD_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_HD_HOLD_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_L_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_L_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_L_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_R_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_R_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_R_TRG
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_MTR_XL_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_MTR_XR_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_MTR_Y_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_MTR_Z_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_WHL_AV_L_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_WHL_AV_R_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_MTR_HD_KNF_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_MTR_HD_CNTR_KNF_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_GET_PWR_MTR_HD_HOLD_RLY
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_XL_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_XL_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_XL_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_XR_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_XR_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_XR_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_Y_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_Y_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_Y_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_Z_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_Z_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_Z_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_KNF_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_KNF_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_KNF_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_CNTR_KNF_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_CNTR_KNF_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_CNTR_KNF_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_HOLD_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_HOLD_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_HD_HOLD_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_L_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_L_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_L_TRG
        {(t_uint8)32,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_R_PLS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_R_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_R_TRG
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_XL_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_XR_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_Y_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_Z_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_PWR_WHL_AV_L_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_PWR_WHL_AV_R_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_HD_KNF_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_HD_CNTR_KNF_RLY
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_HD_HOLD_RLY
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_PULSE_ITER_MAX
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_SYS_OPT_SNS_ECDR_XL
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_SYS_OPT_SNS_ECDR_XR
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_SYS_OPT_SNS_ECDR_Y
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_SYS_OPT_SNS_ECDR_Z
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_SYS_MACHINE_ID
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_X_RAMP_CTRL_KFACTOR
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_X_RAMP_CTRL_SLOP_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_X_RAMP_CTRL_NB_STEP
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_X_SPD_MAX
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_X_SPD_MIN
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_Y_RAMP_CTRL_KFACTOR
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_Y_RAMP_CTRL_SLOP_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_Y_RAMP_CTRL_NB_STEP
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_Y_SPD_MAX
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_Y_SPD_MIN
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_Z_RAMP_CTRL_KFACTOR
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_Z_RAMP_CTRL_SLOP_SPD
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_Z_RAMP_CTRL_NB_STEP
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_Z_SPD_MAX
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_Z_SPD_MIN
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_ALGO_CPTE_TYPE
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_CALIB_TYPE
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_SENDITER_TYPE
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_X_PULSE_PER_MM
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Y_PULSE_PER_MM
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Z_PULSE_PER_MM
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_X_LEN
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Y_LEN
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Z_LEN
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_X_MIN_SPEED
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Y_MIN_SPEED
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Z_MIN_SPEED
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_X_CALIB_OFFSET
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_Y_CALIB_OFFSET
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_Z_CALIB_OFFSET
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_X_SAFE_HEIGHT
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Y_SAFE_HEIGHT
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Z_SAFE_HEIGHT
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_X
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_Y
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_Z
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_RAYON
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_THETHA
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_PHI
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_X
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_Y
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_Z
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_X
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_Y
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_Z
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_GTRY_FSM_PERIODIC_TASK
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_GTRY_FSM_PRDTSK_CALIB
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_GTRY_FSM_PRDTSK_CALIB_OPE_AXE_X
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_GTRY_FSM_PRDTSK_CALIB_OPE_AXE_Y
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_GTRY_FSM_PRDTSK_CALIB_OPE_AXE_Z
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_GTRY_FSM_PRDTSK_OPE
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_GTRY_FSM_PRDTSK_OPE_CMD_PROCESS
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)0.1,                                                   (t_sint16)0                                                      },// APPSIG_SIGNAL_GTRY_AXE_X_POSITION
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)0.1,                                                   (t_sint16)0                                                      },// APPSIG_SIGNAL_GTRY_AXE_Y_POSITION
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)0.1,                                                   (t_sint16)0                                                      },// APPSIG_SIGNAL_GTRY_AXE_Z_POSITION
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_GTRY_ALGO_COMPUTE_TIME
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_1
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_2
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_3
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_4
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_5
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_6
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_7
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_8
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_9
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_10
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_1_INFO_1
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_2_INFO_1
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_3_INFO_1
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_4_INFO_1
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_5_INFO_1
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_6_INFO_1
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_7_INFO_1
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_8_INFO_1
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_9_INFO_1
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_10_INFO_1
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_1_INFO_2
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_2_INFO_2
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_3_INFO_2
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_4_INFO_2
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_5_INFO_2
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_6_INFO_2
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_7_INFO_2
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_8_INFO_2
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_9_INFO_2
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_10_INFO_2
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_1
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_2
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_3
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_4
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_5
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_6
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_7
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_8
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_9
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_10
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_1_STATE
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_2_STATE
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_3_STATE
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_4_STATE
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_1_CW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_2_CW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_3_CW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_4_CW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_1_CCW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_2_CCW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_3_CCW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_4_CCW_ENDSTOP
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_1_DIRECTION
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_2_DIRECTION
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_3_DIRECTION
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_4_DIRECTION
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_1_DEADTIME
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_2_DEADTIME
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_3_DEADTIME
        {(t_uint8)1,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_4_DEADTIME
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_1_HEALTH
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_2_HEALTH
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_3_HEALTH
        {(t_uint8)4,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CL42T_MTR_4_HEALTH
    };

    ///@brief Variable for decoding CL42T_MTR_4_HEALTH
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
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_CL42T_MOTORS_INFO_as[24] = {
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
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_CTRL_ACT_PWR_MTR_as[9] = {
    {APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_XL_RLY,                 (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_XR_RLY,                 (t_uint8)1                                             },
    {APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_Y_RLY,                  (t_uint8)2                                             },
    {APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_Z_RLY,                  (t_uint8)3                                             },
    {APPSIG_SIGNAL_ACT_CTRL_PWR_WHL_AV_L_RLY,               (t_uint8)4                                             },
    {APPSIG_SIGNAL_ACT_CTRL_PWR_WHL_AV_R_RLY,               (t_uint8)5                                             },
    {APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_HD_KNF_RLY,             (t_uint8)6                                             },
    {APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_HD_CNTR_KNF_RLY,        (t_uint8)7                                             },
    {APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_HD_HOLD_RLY,            (t_uint8)8                                             },
    };


    ///@brief Variable for decoding ACT_CTRL_PWR_MTR_HD_HOLD_RLY
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
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPACT_SET_ACT_PWR_MTR_as[9] = {
    {APPSIG_SIGNAL_ACT_SET_PWR_MTR_XL_RLY,                  (t_uint8)0                                             },
    {APPSIG_SIGNAL_ACT_SET_PWR_MTR_XR_RLY,                  (t_uint8)1                                             },
    {APPSIG_SIGNAL_ACT_SET_PWR_MTR_Y_RLY,                   (t_uint8)2                                             },
    {APPSIG_SIGNAL_ACT_SET_PWR_MTR_Z_RLY,                   (t_uint8)3                                             },
    {APPSIG_SIGNAL_ACT_SET_PWR_WHL_AV_L_RLY,                (t_uint8)4                                             },
    {APPSIG_SIGNAL_ACT_SET_PWR_WHL_AV_R_RLY,                (t_uint8)5                                             },
    {APPSIG_SIGNAL_ACT_SET_PWR_MTR_HD_KNF_RLY,              (t_uint8)6                                             },
    {APPSIG_SIGNAL_ACT_SET_PWR_MTR_HD_CNTR_KNF_RLY,         (t_uint8)7                                             },
    {APPSIG_SIGNAL_ACT_SET_PWR_MTR_HD_HOLD_RLY,             (t_uint8)8                                             },
    };


    ///@brief Variable for decoding ACT_SET_PWR_MTR_HD_HOLD_RLY
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
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_LGC_GTRY_X_RAMP_CTRL_as[3] = {
    {APPSIG_SIGNAL_PRM_LGC_GTRY_X_RAMP_CTRL_KFACTOR,        (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_X_RAMP_CTRL_SLOP_SPD,       (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_X_RAMP_CTRL_NB_STEP,        (t_uint8)32                                            },
    };


    ///@brief Variable for decoding PRM_LGC_GTRY_X_RAMP_CTRL_NB_STEP
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_LGC_GTRY_Y_RAMP_CTRL_as[3] = {
    {APPSIG_SIGNAL_PRM_LGC_GTRY_Y_RAMP_CTRL_KFACTOR,        (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_Y_RAMP_CTRL_SLOP_SPD,       (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_Y_RAMP_CTRL_NB_STEP,        (t_uint8)32                                            },
    };


    ///@brief Variable for decoding PRM_LGC_GTRY_Y_RAMP_CTRL_NB_STEP
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_LGC_GTRY_Z_RAMP_CTRL_as[3] = {
    {APPSIG_SIGNAL_PRM_LGC_GTRY_Z_RAMP_CTRL_KFACTOR,        (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_Z_RAMP_CTRL_SLOP_SPD,       (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_Z_RAMP_CTRL_NB_STEP,        (t_uint8)32                                            },
    };


    ///@brief Variable for decoding PRM_LGC_GTRY_Z_RAMP_CTRL_NB_STEP
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_LGC_GTRY_SPD_CFG1_as[3] = {
    {APPSIG_SIGNAL_PRM_LGC_GTRY_PULSE_ITER_MAX,             (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_X_SPD_MAX,                  (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_X_SPD_MIN,                  (t_uint8)32                                            },
    };


    ///@brief Variable for decoding PRM_LGC_GTRY_X_SPD_MIN
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_LGC_GTRY_SPD_CFG_2_as[2] = {
    {APPSIG_SIGNAL_PRM_LGC_GTRY_Y_SPD_MIN,                  (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_Y_SPD_MAX,                  (t_uint8)16                                            },
    };


    ///@brief Variable for decoding PRM_LGC_GTRY_Y_SPD_MAX
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_LGC_GTRY_SPD_CFG_3_as[2] = {
    {APPSIG_SIGNAL_PRM_LGC_GTRY_Z_SPD_MAX,                  (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_Z_SPD_MIN,                  (t_uint8)16                                            },
    };


    ///@brief Variable for decoding PRM_LGC_GTRY_Z_SPD_MIN
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_LGC_LGC_GTRY_CMD_POSITION_as[3] = {
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_X,                  (t_uint8)0                                             },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_Y,                  (t_uint8)16                                            },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_Z,                  (t_uint8)32                                            },
    };


    ///@brief Variable for decoding LGC_GTRY_CMD_SIG_POS_Z
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_LGC_LGC_GTRY_CMD_SPHERIC_as[3] = {
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_RAYON,              (t_uint8)0                                             },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_THETHA,             (t_uint8)16                                            },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_POS_PHI,                (t_uint8)32                                            },
    };


    ///@brief Variable for decoding LGC_GTRY_CMD_SIG_POS_PHI
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_LGC_LGC_GTRY_CMD_STEPS_as[6] = {
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_X,                 (t_uint8)0                                             },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_Y,                 (t_uint8)16                                            },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_STEP_Z,                 (t_uint8)32                                            },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_X,                  (t_uint8)48                                            },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_Y,                  (t_uint8)49                                            },
    {APPSIG_SIGNAL_LGC_GTRY_CMD_SIG_DIR_Z,                  (t_uint8)50                                            },
    };


    ///@brief Variable for decoding LGC_GTRY_CMD_SIG_DIR_Z
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_LGC_GTRY_PARAM_1_as[3] = {
    {APPSIG_SIGNAL_PRM_LGC_GTRY_ALGO_CPTE_TYPE,             (t_uint8)24                                            },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_CALIB_TYPE,                 (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_SENDITER_TYPE,              (t_uint8)20                                            },
    };


    ///@brief Variable for decoding PRM_LGC_GTRY_SENDITER_TYPE
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_LGC_GTRY_PARAM_2_as[3] = {
    {APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_X_PULSE_PER_MM,         (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Y_PULSE_PER_MM,         (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Z_PULSE_PER_MM,         (t_uint8)32                                            },
    };


    ///@brief Variable for decoding PRM_LGC_GTRY_AXE_Z_PULSE_PER_MM
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_LGC_GTRY_PARAM_3_as[3] = {
    {APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_X_LEN,                  (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Y_LEN,                  (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Z_LEN,                  (t_uint8)32                                            },
    };


    ///@brief Variable for decoding PRM_LGC_GTRY_AXE_Z_LEN
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_LGC_GTRY_PARAM_4_as[3] = {
    {APPSIG_SIGNAL_PRM_LGC_GTRY_X_CALIB_OFFSET,             (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_Y_CALIB_OFFSET,             (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_Z_CALIB_OFFSET,             (t_uint8)32                                            },
    };


    ///@brief Variable for decoding PRM_LGC_GTRY_Z_CALIB_OFFSET
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_PRM_LGC_GTRY_PARAM_SAFE_HEIGHT_as[3] = {
    {APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_X_SAFE_HEIGHT,          (t_uint8)0                                             },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Y_SAFE_HEIGHT,          (t_uint8)16                                            },
    {APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Z_SAFE_HEIGHT,          (t_uint8)32                                            },
    };


    ///@brief Variable for decoding PRM_LGC_GTRY_AXE_Z_SAFE_HEIGHT
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_GTRY_DEBUG_POSITION_as[4] = {
    {APPSIG_SIGNAL_GTRY_AXE_X_POSITION,                     (t_uint8)0                                             },
    {APPSIG_SIGNAL_GTRY_AXE_Y_POSITION,                     (t_uint8)16                                            },
    {APPSIG_SIGNAL_GTRY_AXE_Z_POSITION,                     (t_uint8)32                                            },
    {APPSIG_SIGNAL_GTRY_ALGO_COMPUTE_TIME,                  (t_uint8)48                                            },
    };


    ///@brief Variable for decoding GTRY_ALGO_COMPUTE_TIME
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_GTRY_DEBUG_FSM_as[7] = {
    {APPSIG_SIGNAL_GTRY_FSM_PERIODIC_TASK,                  (t_uint8)0                                             },
    {APPSIG_SIGNAL_GTRY_FSM_PRDTSK_CALIB,                   (t_uint8)4                                             },
    {APPSIG_SIGNAL_GTRY_FSM_PRDTSK_CALIB_OPE_AXE_X,         (t_uint8)8                                             },
    {APPSIG_SIGNAL_GTRY_FSM_PRDTSK_CALIB_OPE_AXE_Y,         (t_uint8)12                                            },
    {APPSIG_SIGNAL_GTRY_FSM_PRDTSK_CALIB_OPE_AXE_Z,         (t_uint8)16                                            },
    {APPSIG_SIGNAL_GTRY_FSM_PRDTSK_OPE,                     (t_uint8)20                                            },
    {APPSIG_SIGNAL_GTRY_FSM_PRDTSK_OPE_CMD_PROCESS,         (t_uint8)24                                            },
    };


    ///@brief Variable for decoding GTRY_FSM_PRDTSK_OPE_CMD_PROCESS
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPSDM_DIAG_ITEM_1_as[4] = {
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_1,                         (t_uint8)0                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_1,                   (t_uint8)40                                            },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_1_INFO_1,                  (t_uint8)8                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_1_INFO_2,                  (t_uint8)24                                            },
    };


    ///@brief Variable for decoding SDM_DIAG_ITEM_1_INFO_2
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPSDM_DIAG_ITEM_2_as[4] = {
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_2,                         (t_uint8)0                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_2,                   (t_uint8)40                                            },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_2_INFO_1,                  (t_uint8)8                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_2_INFO_2,                  (t_uint8)24                                            },
    };


    ///@brief Variable for decoding SDM_DIAG_ITEM_2_INFO_2
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPSDM_DIAG_ITEM_3_as[4] = {
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_3,                         (t_uint8)0                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_3,                   (t_uint8)40                                            },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_3_INFO_1,                  (t_uint8)8                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_3_INFO_2,                  (t_uint8)24                                            },
    };


    ///@brief Variable for decoding SDM_DIAG_ITEM_3_INFO_2
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPSDM_DIAG_ITEM_4_as[4] = {
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_4,                         (t_uint8)0                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_4,                   (t_uint8)40                                            },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_4_INFO_1,                  (t_uint8)8                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_4_INFO_2,                  (t_uint8)24                                            },
    };


    ///@brief Variable for decoding SDM_DIAG_ITEM_4_INFO_2
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPSDM_DIAG_ITEM_5_as[4] = {
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_5,                         (t_uint8)0                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_5,                   (t_uint8)40                                            },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_5_INFO_1,                  (t_uint8)8                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_5_INFO_2,                  (t_uint8)24                                            },
    };


    ///@brief Variable for decoding SDM_DIAG_ITEM_5_INFO_2
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPSDM_DIAG_ITEM_6_as[4] = {
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_6,                         (t_uint8)0                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_6,                   (t_uint8)40                                            },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_6_INFO_1,                  (t_uint8)8                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_6_INFO_2,                  (t_uint8)24                                            },
    };


    ///@brief Variable for decoding SDM_DIAG_ITEM_6_INFO_2
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPSDM_DIAG_ITEM_7_as[4] = {
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_7,                         (t_uint8)0                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_7,                   (t_uint8)40                                            },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_7_INFO_1,                  (t_uint8)8                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_7_INFO_2,                  (t_uint8)24                                            },
    };


    ///@brief Variable for decoding SDM_DIAG_ITEM_7_INFO_2
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPSDM_DIAG_ITEM_8_as[4] = {
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_8,                         (t_uint8)0                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_8,                   (t_uint8)40                                            },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_8_INFO_1,                  (t_uint8)8                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_8_INFO_2,                  (t_uint8)24                                            },
    };


    ///@brief Variable for decoding SDM_DIAG_ITEM_8_INFO_2
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPSDM_DIAG_ITEM_9_as[4] = {
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_9,                         (t_uint8)0                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_9,                   (t_uint8)40                                            },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_9_INFO_1,                  (t_uint8)8                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_9_INFO_2,                  (t_uint8)24                                            },
    };


    ///@brief Variable for decoding SDM_DIAG_ITEM_9_INFO_2
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Can_APPSDM_DIAG_ITEM_10_as[4] = {
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_10,                        (t_uint8)0                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_10,                  (t_uint8)40                                            },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_10_INFO_1,                 (t_uint8)8                                             },
    {APPSIG_SIGNAL_SDM_DIAG_ITEM_10_INFO_2,                 (t_uint8)24                                            },
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
    {APPSIG_CAN_ID_CL42T_MOTORS_INFO,                        {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)10,                                           (t_uint16)65535,                                        c_AppSig_Can_CL42T_MOTORS_INFO_as,                      (t_uint8)24}, // APPSIG_CAN_CL42T_MOTORS_INFO
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_XL,                       {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_XL_as,                     (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_XL
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_XR,                       {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_XR_as,                     (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_XR
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_Y,                        {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_Y_as,                      (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_Y
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_Z,                        {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_Z_as,                      (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_Z
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_HD_KNF,                   {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_HD_KNF_as,                 (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_HD_KNF
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_HD_CNTR_KNF,              {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_HD_CNTR_KNF_as,            (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_HD_CNTR_KNF
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_HD_HOLD,                  {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_HD_HOLD_as,                (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_HD_HOLD
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_WHL_AV_L,                 {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_WHL_AV_L_as,               (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_WHL_AV_L
    {APPSIG_CAN_ID_APPACT_CTRL_MTR_WHL_AV_R,                 {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_MTR_WHL_AV_R_as,               (t_uint8)3}, // APPSIG_CAN_APPACT_CTRL_MTR_WHL_AV_R
    {APPSIG_CAN_ID_APPACT_CTRL_ACT_PWR_MTR,                  {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_RX},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_APPACT_CTRL_ACT_PWR_MTR_as,                (t_uint8)9}, // APPSIG_CAN_APPACT_CTRL_ACT_PWR_MTR
    {APPSIG_CAN_ID_APPACT_SET_MTR_XL,                        {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_XL_as,                      (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_XL
    {APPSIG_CAN_ID_APPACT_SET_MTR_XR,                        {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_XR_as,                      (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_XR
    {APPSIG_CAN_ID_APPACT_SET_MTR_Y,                         {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_Y_as,                       (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_Y
    {APPSIG_CAN_ID_APPACT_SET_MTR_Z,                         {APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_Z_as,                       (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_Z
    {APPSIG_CAN_ID_APPACT_SET_MTR_HD_KNF,                    {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_HD_KNF_as,                  (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_HD_KNF
    {APPSIG_CAN_ID_APPACT_SET_MTR_HD_CNTR_KNF,               {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_HD_CNTR_KNF_as,             (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_HD_CNTR_KNF
    {APPSIG_CAN_ID_APPACT_SET_MTR_HD_HOLD,                   {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_HD_HOLD_as,                 (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_HD_HOLD
    {APPSIG_CAN_ID_APPACT_SET_MTR_WHL_AV_L,                  {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_WHL_AV_L_as,                (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_WHL_AV_L
    {APPSIG_CAN_ID_APPACT_SET_MTR_WHL_AV_R,                  {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_TX},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_MTR_WHL_AV_R_as,                (t_uint8)3}, // APPSIG_CAN_APPACT_SET_MTR_WHL_AV_R
    {APPSIG_CAN_ID_APPACT_SET_ACT_PWR_MTR,                   {APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED,         APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_APPACT_SET_ACT_PWR_MTR_as,                 (t_uint8)9}, // APPSIG_CAN_APPACT_SET_ACT_PWR_MTR
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
    {APPSIG_CAN_ID_PRM_LGC_GTRY_X_RAMP_CTRL,                 {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_LGC_GTRY_X_RAMP_CTRL_as,               (t_uint8)3}, // APPSIG_CAN_PRM_LGC_GTRY_X_RAMP_CTRL
    {APPSIG_CAN_ID_PRM_LGC_GTRY_Y_RAMP_CTRL,                 {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_LGC_GTRY_Y_RAMP_CTRL_as,               (t_uint8)3}, // APPSIG_CAN_PRM_LGC_GTRY_Y_RAMP_CTRL
    {APPSIG_CAN_ID_PRM_LGC_GTRY_Z_RAMP_CTRL,                 {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_LGC_GTRY_Z_RAMP_CTRL_as,               (t_uint8)3}, // APPSIG_CAN_PRM_LGC_GTRY_Z_RAMP_CTRL
    {APPSIG_CAN_ID_PRM_LGC_GTRY_SPD_CFG1,                    {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_LGC_GTRY_SPD_CFG1_as,                  (t_uint8)3}, // APPSIG_CAN_PRM_LGC_GTRY_SPD_CFG1
    {APPSIG_CAN_ID_PRM_LGC_GTRY_SPD_CFG_2,                   {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_LGC_GTRY_SPD_CFG_2_as,                 (t_uint8)2}, // APPSIG_CAN_PRM_LGC_GTRY_SPD_CFG_2
    {APPSIG_CAN_ID_PRM_LGC_GTRY_SPD_CFG_3,                   {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_LGC_GTRY_SPD_CFG_3_as,                 (t_uint8)2}, // APPSIG_CAN_PRM_LGC_GTRY_SPD_CFG_3
    {APPSIG_CAN_ID_PRM_LGC_LGC_GTRY_CMD_POSITION,            {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_LGC_LGC_GTRY_CMD_POSITION_as,          (t_uint8)3}, // APPSIG_CAN_PRM_LGC_LGC_GTRY_CMD_POSITION
    {APPSIG_CAN_ID_PRM_LGC_LGC_GTRY_CMD_SPHERIC,             {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_LGC_LGC_GTRY_CMD_SPHERIC_as,           (t_uint8)3}, // APPSIG_CAN_PRM_LGC_LGC_GTRY_CMD_SPHERIC
    {APPSIG_CAN_ID_PRM_LGC_LGC_GTRY_CMD_STEPS,               {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_LGC_LGC_GTRY_CMD_STEPS_as,             (t_uint8)6}, // APPSIG_CAN_PRM_LGC_LGC_GTRY_CMD_STEPS
    {APPSIG_CAN_ID_PRM_LGC_GTRY_PARAM_1,                     {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_LGC_GTRY_PARAM_1_as,                   (t_uint8)3}, // APPSIG_CAN_PRM_LGC_GTRY_PARAM_1
    {APPSIG_CAN_ID_PRM_LGC_GTRY_PARAM_2,                     {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_LGC_GTRY_PARAM_2_as,                   (t_uint8)3}, // APPSIG_CAN_PRM_LGC_GTRY_PARAM_2
    {APPSIG_CAN_ID_PRM_LGC_GTRY_PARAM_3,                     {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_LGC_GTRY_PARAM_3_as,                   (t_uint8)3}, // APPSIG_CAN_PRM_LGC_GTRY_PARAM_3
    {APPSIG_CAN_ID_PRM_LGC_GTRY_PARAM_4,                     {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_LGC_GTRY_PARAM_4_as,                   (t_uint8)3}, // APPSIG_CAN_PRM_LGC_GTRY_PARAM_4
    {APPSIG_CAN_ID_PRM_LGC_GTRY_PARAM_SAFE_HEIGHT,           {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Can_PRM_LGC_GTRY_PARAM_SAFE_HEIGHT_as,         (t_uint8)3}, // APPSIG_CAN_PRM_LGC_GTRY_PARAM_SAFE_HEIGHT
    {APPSIG_CAN_ID_GTRY_DEBUG_POSITION,                      {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)30,                                           (t_uint16)65535,                                        c_AppSig_Can_GTRY_DEBUG_POSITION_as,                    (t_uint8)4}, // APPSIG_CAN_GTRY_DEBUG_POSITION
    {APPSIG_CAN_ID_GTRY_DEBUG_FSM,                           {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)50,                                           (t_uint16)65535,                                        c_AppSig_Can_GTRY_DEBUG_FSM_as,                         (t_uint8)7}, // APPSIG_CAN_GTRY_DEBUG_FSM
    {APPSIG_CAN_ID_APPSDM_DIAG_ITEM_1,                       {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)1000,                                         (t_uint16)65535,                                        c_AppSig_Can_APPSDM_DIAG_ITEM_1_as,                     (t_uint8)4}, // APPSIG_CAN_APPSDM_DIAG_ITEM_1
    {APPSIG_CAN_ID_APPSDM_DIAG_ITEM_2,                       {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)1000,                                         (t_uint16)65535,                                        c_AppSig_Can_APPSDM_DIAG_ITEM_2_as,                     (t_uint8)4}, // APPSIG_CAN_APPSDM_DIAG_ITEM_2
    {APPSIG_CAN_ID_APPSDM_DIAG_ITEM_3,                       {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)1000,                                         (t_uint16)65535,                                        c_AppSig_Can_APPSDM_DIAG_ITEM_3_as,                     (t_uint8)4}, // APPSIG_CAN_APPSDM_DIAG_ITEM_3
    {APPSIG_CAN_ID_APPSDM_DIAG_ITEM_4,                       {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)1000,                                         (t_uint16)65535,                                        c_AppSig_Can_APPSDM_DIAG_ITEM_4_as,                     (t_uint8)4}, // APPSIG_CAN_APPSDM_DIAG_ITEM_4
    {APPSIG_CAN_ID_APPSDM_DIAG_ITEM_5,                       {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)1000,                                         (t_uint16)65535,                                        c_AppSig_Can_APPSDM_DIAG_ITEM_5_as,                     (t_uint8)4}, // APPSIG_CAN_APPSDM_DIAG_ITEM_5
    {APPSIG_CAN_ID_APPSDM_DIAG_ITEM_6,                       {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)1000,                                         (t_uint16)65535,                                        c_AppSig_Can_APPSDM_DIAG_ITEM_6_as,                     (t_uint8)4}, // APPSIG_CAN_APPSDM_DIAG_ITEM_6
    {APPSIG_CAN_ID_APPSDM_DIAG_ITEM_7,                       {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)1000,                                         (t_uint16)65535,                                        c_AppSig_Can_APPSDM_DIAG_ITEM_7_as,                     (t_uint8)4}, // APPSIG_CAN_APPSDM_DIAG_ITEM_7
    {APPSIG_CAN_ID_APPSDM_DIAG_ITEM_8,                       {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)1000,                                         (t_uint16)65535,                                        c_AppSig_Can_APPSDM_DIAG_ITEM_8_as,                     (t_uint8)4}, // APPSIG_CAN_APPSDM_DIAG_ITEM_8
    {APPSIG_CAN_ID_APPSDM_DIAG_ITEM_9,                       {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)1000,                                         (t_uint16)65535,                                        c_AppSig_Can_APPSDM_DIAG_ITEM_9_as,                     (t_uint8)4}, // APPSIG_CAN_APPSDM_DIAG_ITEM_9
    {APPSIG_CAN_ID_APPSDM_DIAG_ITEM_10,                      {APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_RX,             APPSIG_MSG_DIR_UNUSED},          (t_uint16)1000,                                         (t_uint16)65535,                                        c_AppSig_Can_APPSDM_DIAG_ITEM_10_as,                    (t_uint8)4}, // APPSIG_CAN_APPSDM_DIAG_ITEM_10
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
