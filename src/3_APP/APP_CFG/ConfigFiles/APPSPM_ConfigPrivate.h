/*********************************************************************
 * @file        APPSPM_ConfigPrivate.h
 * @brief       System Parameters Managment.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPSPM_CONFIGPRIVATE_H_INCLUDED
#define APPSPM_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APPSPM_ConfigPublic.h"
    #include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    /* CAUTION : Automatic generated code section for define: Start */
    ///@brief number of msg to follow 
    #define APPSPM_SIG_MSG_NB       ((t_uint8)1)
    /* CAUTION : Automatic generated code section for define: End */
    // ********************************************************************
    // *                      Types
    // ********************************************************************
	/* CAUTION : Automatic generated code section for Enum: Start */

	/* CAUTION : Automatic generated code section for Enum: End */
	//-----------------------------ENUM TYPES-----------------------------//


	/* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
	//-----------------------------STRUCT TYPES---------------------------//
    /**
     * @brief Item Parameter Information
     */
    typedef struct 
    {
        t_uint8 version_u8;             //---- parameter version ----//
        t_float32 minItemVal_f32;        //---- min value accpeted for the parameter ----//
        t_float32 maxItemVal_f32;        //---- max value accpted for the parameter ----//
        t_float32 DefaultItemVal_f32;    //---- default value ----//
        t_float32 factor_f32;           //---- factor to apply once the param is received by EEPROM or Signal ----//
        t_sint16 offset_s16;            //---- offset to apply once the param is received by EEPROM or Signal ----//
        t_eAPPSPM_PrmType prmType_e;
        t_eAPPSIG_Signal signal_e;      //--- if signal comes from APPSIG, signal related ----//

    } t_sAPPSPM_ItemPrmCfg;

	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
	//-----------------------------TYPEDEF TYPES---------------------------//

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    ///@brief Variable for System Parameter Inforamtion
    const t_sAPPSPM_ItemPrmCfg c_AppSpm_ItemPrmInfo_as[APPSPM_PRM_NB] ={
    //version_u8                   minItemVal_u16                maxItemVal_u16                 DefaultItemVal_u16
    [APPSPM_PRM_LGC_GTRY_PULSE_ITER_MAX] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)1,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)1500,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_PULSE_ITER_MAX
    },
    [APPSPM_PRM_LGC_GTRY_X_RAMP_CTRL_KFACTOR] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)2,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_X_RAMP_CTRL_KFACTOR
    },
    [APPSPM_PRM_LGC_GTRY_X_RAMP_CTRL_SLOP_SPEED] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)65300,
        .factor_f32 = (t_float32)2.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_X_RAMP_CTRL_SLP_SPD
    },
    [APPSPM_PRM_LGC_GTRY_X_RAMP_CTRL_NB_STEP] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)50,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_X_RAMP_CTRL_NB_STEP
    },
    [APPSPM_PRM_LGC_GTRY_X_SPEED_MAX] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)1,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)10000,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_X_SPEED_MAX
    },
    [APPSPM_PRM_LGC_GTRY_X_SPEED_MIN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)1,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)600,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_X_SPEED_MIN
    },
    [APPSPM_PRM_LGC_GTRY_X_CALIB_OFFSET] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)5,
        .factor_f32 = (t_float32)0.1,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_X_CALIB_OFFSET
    },
    [APPSPM_PRM_LGC_GTRY_Y_RAMP_CTRL_KFACTOR] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)2,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_Y_RAMP_CTRL_KFACTOR
    },
    [APPSPM_PRM_LGC_GTRY_Y_RAMP_CTRL_SLOP_SPEED] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)65300,
        .factor_f32 = (t_float32)2.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_Y_RAMP_CTRL_SLP_SPD
    },
    [APPSPM_PRM_LGC_GTRY_Y_RAMP_CTRL_NB_STEP] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)50,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_Y_RAMP_CTRL_NB_STEP
    },
    [APPSPM_PRM_LGC_GTRY_Y_SPEED_MAX] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)1,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)10000,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_Y_SPEED_MAX
    },
    [APPSPM_PRM_LGC_GTRY_Y_SPEED_MIN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)1,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)600,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_Y_SPEED_MIN
    },
    [APPSPM_PRM_LGC_GTRY_Y_CALIB_OFFSET] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)5,
        .factor_f32 = (t_float32)0.1,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_Y_CALIB_OFFSET
    },
    [APPSPM_PRM_LGC_GTRY_Z_RAMP_CTRL_KFACTOR] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)2,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_Z_RAMP_CTRL_KFACTOR
    },
    [APPSPM_PRM_LGC_GTRY_Z_RAMP_CTRL_SLOP_SPEED] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)65300,
        .factor_f32 = (t_float32)2.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_Z_RAMP_CTRL_SLP_SPD
    },
    [APPSPM_PRM_LGC_GTRY_Z_RAMP_CTRL_NB_STEP] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)50,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_Z_RAMP_CTRL_NB_STEP
    },
    [APPSPM_PRM_LGC_GTRY_Z_SPEED_MAX] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)1,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)10000,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_Z_SPEED_MAX
    },
    [APPSPM_PRM_LGC_GTRY_Z_SPEED_MIN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)1,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)600,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_Z_SPEED_MIN
    },
    [APPSPM_PRM_LGC_GTRY_Z_CALIB_OFFSET] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)5,
        .factor_f32 = (t_float32)0.1,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_Z_CALIB_OFFSET
    },
    [APPSPM_PRM_SYS_OPT_SNS_ECDR_XL] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_ECDR_XR] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_ECDR_Y] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_ECDR_Z] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_MACHINE_ID] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_MTR_XL] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_MTR_XR] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_MTR_Y] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_MTR_Z] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_LGC_GTRY_ALGO_CPTE_TYPE] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)8,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_ALGO_CPTE_TYPE
    },
    [APPSPM_PRM_LGC_GTRY_CALIB_TYPE] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_CALIB_TYPE
    },
    [APPSPM_PRM_LGC_GTRY_SENDITER_TYPE] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_SENDITER_TYPE
    },
    [APPSPM_PRM_LGC_GTRY_AXE_X_PULSE_PER_MM] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)44.0,
        .factor_f32 = (t_float32)0.1,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_X_PULSE_PER_MM
    },
    [APPSPM_PRM_LGC_GTRY_AXE_Y_PULSE_PER_MM] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)44.0,
        .factor_f32 = (t_float32)0.1,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Y_PULSE_PER_MM
    },
    [APPSPM_PRM_LGC_GTRY_AXE_Z_PULSE_PER_MM] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)44.0,
        .factor_f32 = (t_float32)0.1,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Z_PULSE_PER_MM
    },
    [APPSPM_PRM_LGC_GTRY_AXE_X_LEN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)500.0,
        .factor_f32 = (t_float32)0.1,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_X_LEN
    },
    [APPSPM_PRM_LGC_GTRY_AXE_Y_LEN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)500.0,
        .factor_f32 = (t_float32)0.1,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Y_LEN
    },
    [APPSPM_PRM_LGC_GTRY_AXE_Z_LEN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)500.0,
        .factor_f32 = (t_float32)0.1,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Z_LEN
    },
    [APPSPM_PRM_LGC_GTRY_AXE_X_SAFE_HEIGHT] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)150.0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_X_SAFE_HEIGHT
    },
    [APPSPM_PRM_LGC_GTRY_AXE_Y_SAFE_HEIGHT] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)150.0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Y_SAFE_HEIGHT
    },
    [APPSPM_PRM_LGC_GTRY_AXE_Z_SAFE_HEIGHT] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)150.0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_LGC_GTRY_AXE_Z_SAFE_HEIGHT
    },
    };


    /* CAUTION : Automatic generated code section for Variable: End */

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APPSYS_CONFIGPRIVATE_H_INCLUDED           
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
