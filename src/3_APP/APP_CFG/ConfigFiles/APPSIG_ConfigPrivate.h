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
    #define APPSIG_CAN_ID_MASK      ((t_uint32)0x18FF9FFF)
    ///@brief Configuration Gate for the module 
    #define APPSIG_PORTGATE_CAN         (APPSIG_MSG_ORIGIN_CAN)
    #define APPSIG_PORTGATE_CAN_NODE    (FMKFDCAN_NODE_1)

    #define APPSIG_PORTGATE_SRL         (APPSIG_MSG_ORIGIN_SRL)
    #define APPSIG_PORTGATE_SRL_LINE    (FMKSRL_SERIAL_LINE_2)

    #define APPSIG_PORTGATE_CFG         (1 << APPSIG_MSG_ORIGIN_SRL) // (1 << APPSIG_MSG_ORIGIN_SRL)
    /* CAUTION : Automatic generated code section for Define: Start */
    ///@brief Serial Message Id
    #define APPSIG_SRL_ID_APPLICATIONINFO1                         ((t_uint32)0x10)
    #define APPSIG_SRL_ID_MTR_XL_RAMP_CTRL                         ((t_uint32)0x91)
    #define APPSIG_SRL_ID_MTR_XR_RAMP_CTRL                         ((t_uint32)0x92)
    #define APPSIG_SRL_ID_MTR_Y_RAMP_CTRL                          ((t_uint32)0x93)
    #define APPSIG_SRL_ID_MTR_Z_RAMP_CTRL                          ((t_uint32)0x94)
    #define APPSIG_SRL_ID_MTR_SPEED_CFG1                           ((t_uint32)0x95)
    #define APPSIG_SRL_ID_MTR_SPEED_CFG_2                          ((t_uint32)0x96)
    #define APPSIG_SRL_ID_MTR_SPEED_CFG_3                          ((t_uint32)0x97)
    ///@brief CAN Message Id
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
        t_uint32 msgId_u32;                     //---- the identifier of the message ----//
        t_eAPPSIG_MsgDirection direction_e;     //---- Rx, Tx message direction ----//
        t_uint16 msgCycleSend_u16;             //---- message cyclic updated ----//
        t_uint16 msgTimeout_u16;                //---- Time upon if a msg is not receive a Deev will be raise ----//             
        const t_sAPPSIG_MsgSignalsCfg * msgSignalsCfg_pas;      //---- signal in the message ----// 
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
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_FMKCPU_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_FMKCDA_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_FMKSRL_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_FMKFDCAN_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_FMKIO_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_FMKHRT_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_FMKTIM_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_APPSIG_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_APPSYS_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_APPSNS_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_APPACT_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_APPLGC_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_APPSDM_MODSTATE
        {(t_uint8)3,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_APPSPM_MODSTATE
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_CYCLIC_DURATION
        {(t_uint8)12,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_FASTTASKDURATION
        {(t_uint8)16,                                                    APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_PULSE_ITER_MAX
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_XL_RAMP_CTRL_KFACTOR
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_XL_RAMP_CTRL_SLOP_SPEED
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_XL_RAMP_CTRL_TOTAL_STEP
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_XL_SPEED_MAX
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_XL_SPEED_MIN
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_XR_RAMP_CTRL_KFACTOR
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_XR_RAMP_CTRL_SLOP_SPEED
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_XR_RAMP_CTRL_TOTAL_STEP
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_XR_SPEED_MAX
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_XR_SPEED_MIN
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_Y_RAMP_CTRL_KFACTOR
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_Y_RAMP_CTRL_SLOP_SPEED
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_Y_RAMP_CTRL_TOTAL_STEP
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_Y_SPEED_MAX
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_Y_SPEED_MIN
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_Z_RAMP_CTRL_KFACTOR
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_Z_RAMP_CTRL_SLOP_SPEED
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_Z_RAMP_CTRL_TOTAL_STEP
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_Z_SPEED_MAX
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_LGC_MTR_Z_SPEED_MIN
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_SYS_OPT_SNS_ECDR_XL
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_SYS_OPT_SNS_ECDR_XR
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_SYS_OPT_SNS_ECDR_Y
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_SYS_OPT_SNS_ECDR_Z
        {(t_uint8)8,                                                     APPSIG_SIG_ENCODE_INTEL,                                                 (t_float32)1.0f,                                                     (t_sint16)0                                                      },// APPSIG_SIGNAL_PRM_SYS_MACHINE_ID
    };

    ///@brief Variable for decoding ApplicationInfo1
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Srl_ApplicationInfo1_as[14] = {
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


    ///@brief Variable for decoding MTR_XL_RAMP_CTRL
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Srl_MTR_XL_RAMP_CTRL_as[3] = {
        {APPSIG_SIGNAL_PRM_LGC_MTR_XL_RAMP_CTRL_KFACTOR,        (t_uint8)0                                             },
        {APPSIG_SIGNAL_PRM_LGC_MTR_XL_RAMP_CTRL_SLOP_SPEED,     (t_uint8)8                                             },
        {APPSIG_SIGNAL_PRM_LGC_MTR_XL_RAMP_CTRL_TOTAL_STEP,     (t_uint8)16                                            },
    };


    ///@brief Variable for decoding MTR_XR_RAMP_CTRL
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Srl_MTR_XR_RAMP_CTRL_as[3] = {
        {APPSIG_SIGNAL_PRM_LGC_MTR_XR_RAMP_CTRL_KFACTOR,        (t_uint8)0                                             },
        {APPSIG_SIGNAL_PRM_LGC_MTR_XR_RAMP_CTRL_SLOP_SPEED,     (t_uint8)8                                             },
        {APPSIG_SIGNAL_PRM_LGC_MTR_XR_RAMP_CTRL_TOTAL_STEP,     (t_uint8)16                                            },
    };


    ///@brief Variable for decoding MTR_Y_RAMP_CTRL
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Srl_MTR_Y_RAMP_CTRL_as[3] = {
        {APPSIG_SIGNAL_PRM_LGC_MTR_Y_RAMP_CTRL_KFACTOR,         (t_uint8)0                                             },
        {APPSIG_SIGNAL_PRM_LGC_MTR_Y_RAMP_CTRL_SLOP_SPEED,      (t_uint8)8                                             },
        {APPSIG_SIGNAL_PRM_LGC_MTR_Y_RAMP_CTRL_TOTAL_STEP,      (t_uint8)16                                            },
    };


    ///@brief Variable for decoding MTR_Z_RAMP_CTRL
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Srl_MTR_Z_RAMP_CTRL_as[3] = {
        {APPSIG_SIGNAL_PRM_LGC_MTR_Z_RAMP_CTRL_KFACTOR,         (t_uint8)0                                             },
        {APPSIG_SIGNAL_PRM_LGC_MTR_Z_RAMP_CTRL_SLOP_SPEED,      (t_uint8)8                                             },
        {APPSIG_SIGNAL_PRM_LGC_MTR_Z_RAMP_CTRL_TOTAL_STEP,      (t_uint8)16                                            },
    };


    ///@brief Variable for decoding MTR_SPEED_CFG1
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Srl_MTR_SPEED_CFG1_as[4] = {
        {APPSIG_SIGNAL_PRM_LGC_MTR_PULSE_ITER_MAX,              (t_uint8)0                                             },
        {APPSIG_SIGNAL_PRM_LGC_MTR_XL_SPEED_MAX,                (t_uint8)16                                            },
        {APPSIG_SIGNAL_PRM_LGC_MTR_XL_SPEED_MIN,                (t_uint8)24                                            },
        {APPSIG_SIGNAL_PRM_LGC_MTR_XR_SPEED_MIN,                (t_uint8)32                                            },
    };


    ///@brief Variable for decoding MTR_SPEED_CFG_2
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Srl_MTR_SPEED_CFG_2_as[3] = {
        {APPSIG_SIGNAL_PRM_LGC_MTR_XR_SPEED_MAX,                (t_uint8)0                                             },
        {APPSIG_SIGNAL_PRM_LGC_MTR_Y_SPEED_MIN,                 (t_uint8)8                                             },
        {APPSIG_SIGNAL_PRM_LGC_MTR_Y_SPEED_MAX,                 (t_uint8)16                                            },
    };


    ///@brief Variable for decoding MTR_SPEED_CFG_3
    const t_sAPPSIG_MsgSignalsCfg c_AppSig_Srl_MTR_SPEED_CFG_3_as[2] = {
        {APPSIG_SIGNAL_PRM_LGC_MTR_Z_SPEED_MAX,                 (t_uint8)0                                             },
        {APPSIG_SIGNAL_PRM_LGC_MTR_Z_SPEED_MIN,                 (t_uint8)8                                             },
    };


    ///@brief Serial Message Information
    const t_sAPPSIG_MsgCfg c_AppSig_SrlMsgCfg_as[APPSIG_SRL_MSG_NB] = {
    //  Identifier                                          Direction                                                CyclicSend                                                 TimeOut                                                         Sig Cfg                                         nbSignal
        {APPSIG_SRL_ID_APPLICATIONINFO1,                         APPSIG_MSG_DIR_TX,                                      (t_uint16)500,                                          (t_uint16)0,                                            c_AppSig_Srl_ApplicationInfo1_as,                       (t_uint8)14}, // APPSIG_SRL_APPLICATIONINFO1
        {APPSIG_SRL_ID_MTR_XL_RAMP_CTRL,                         APPSIG_MSG_DIR_RX,                                      (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Srl_MTR_XL_RAMP_CTRL_as,                       (t_uint8)3}, // APPSIG_SRL_MTR_XL_RAMP_CTRL
        {APPSIG_SRL_ID_MTR_XR_RAMP_CTRL,                         APPSIG_MSG_DIR_RX,                                      (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Srl_MTR_XR_RAMP_CTRL_as,                       (t_uint8)3}, // APPSIG_SRL_MTR_XR_RAMP_CTRL
        {APPSIG_SRL_ID_MTR_Y_RAMP_CTRL,                          APPSIG_MSG_DIR_RX,                                      (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Srl_MTR_Y_RAMP_CTRL_as,                        (t_uint8)3}, // APPSIG_SRL_MTR_Y_RAMP_CTRL
        {APPSIG_SRL_ID_MTR_Z_RAMP_CTRL,                          APPSIG_MSG_DIR_RX,                                      (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Srl_MTR_Z_RAMP_CTRL_as,                        (t_uint8)3}, // APPSIG_SRL_MTR_Z_RAMP_CTRL
        {APPSIG_SRL_ID_MTR_SPEED_CFG1,                           APPSIG_MSG_DIR_RX,                                      (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Srl_MTR_SPEED_CFG1_as,                         (t_uint8)4}, // APPSIG_SRL_MTR_SPEED_CFG1
        {APPSIG_SRL_ID_MTR_SPEED_CFG_2,                          APPSIG_MSG_DIR_RX,                                      (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Srl_MTR_SPEED_CFG_2_as,                        (t_uint8)3}, // APPSIG_SRL_MTR_SPEED_CFG_2
        {APPSIG_SRL_ID_MTR_SPEED_CFG_3,                          APPSIG_MSG_DIR_RX,                                      (t_uint16)0,                                            (t_uint16)65535,                                        c_AppSig_Srl_MTR_SPEED_CFG_3_as,                        (t_uint8)2}, // APPSIG_SRL_MTR_SPEED_CFG_3
    };

    ///@brief CAN Message Information
    const t_sAPPSIG_MsgCfg c_AppSig_CanMsgCfg_as[APPSIG_CAN_MSG_NB] = {
    //  Identifier                                          Direction                                                CyclicSend                                                 TimeOut                                                         Sig Cfg                                         nbSignal
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
