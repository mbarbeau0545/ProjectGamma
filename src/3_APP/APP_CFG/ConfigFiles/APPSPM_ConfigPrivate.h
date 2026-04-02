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
    #define APPSPM_SIG_SEND_PER_CYCLIC ((t_uint16)40)
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
    [APPSPM_PRM_GTRY_PULSE_ITER_MAX] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)1,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)1500,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_PULSE_ITER_MAX
    },
    [APPSPM_PRM_GTRY_X_RMP_CTRL_KFACTOR] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)2,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_X_RMP_CTRL_KFACTOR
    },
    [APPSPM_PRM_GTRY_X_RMP_CTRL_SLOP_SPD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)65300,
        .factor_f32 = (t_float32)2.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_X_RMP_CTRL_SLOP_SPD
    },
    [APPSPM_PRM_GTRY_X_RMP_CTRL_NB_STEP] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)50,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_X_RMP_CTRL_NB_STEP
    },
    [APPSPM_PRM_GTRY_X_SPD_MAX] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)1,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)20000,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_X_SPD_MAX
    },
    [APPSPM_PRM_GTRY_X_SPD_MIN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)1,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)600,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_X_SPD_MIN
    },
    [APPSPM_PRM_GTRY_X_CALIB_OFFSET_MM] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)5,
        .factor_f32 = (t_float32)0.1,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_X_CALIB_OFFSET_MM
    },
    [APPSPM_PRM_GTRY_Y_RMP_CTRL_KFACTOR] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)2,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_Y_RMP_CTRL_KFACTOR
    },
    [APPSPM_PRM_GTRY_Y_RMP_CTRL_SLOP_SPD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)65300,
        .factor_f32 = (t_float32)2.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_Y_RMP_CTRL_SLOP_SPD
    },
    [APPSPM_PRM_GTRY_Y_RMP_CTRL_NB_STEP] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)50,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_Y_RMP_CTRL_NB_STEP
    },
    [APPSPM_PRM_GTRY_Y_SPD_MAX] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)1,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)20000,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_Y_SPD_MAX
    },
    [APPSPM_PRM_GTRY_Y_SPD_MIN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)1,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)600,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_Y_SPD_MIN
    },
    [APPSPM_PRM_GTRY_Y_CALIB_OFFSET_MM] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)5,
        .factor_f32 = (t_float32)0.1,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_Y_CALIB_OFFSET_MM
    },
    [APPSPM_PRM_GTRY_Z_RMP_CTRL_KFACTOR] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)2,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_Z_RMP_CTRL_KFACTOR
    },
    [APPSPM_PRM_GTRY_Z_RMP_CTRL_SLOP_SPD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)65300,
        .factor_f32 = (t_float32)2.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_Z_RMP_CTRL_SLOP_SPD
    },
    [APPSPM_PRM_GTRY_Z_RMP_CTRL_NB_STEP] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)50,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_Z_RMP_CTRL_NB_STEP
    },
    [APPSPM_PRM_GTRY_Z_SPD_MAX] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)1,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)20000,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_Z_SPD_MAX
    },
    [APPSPM_PRM_GTRY_Z_SPD_MIN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)1,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)600,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_Z_SPD_MIN
    },
    [APPSPM_PRM_GTRY_Z_CALIB_OFFSET_MM] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)5,
        .factor_f32 = (t_float32)0.1,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_Z_CALIB_OFFSET_MM
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
    [APPSPM_PRM_GTRY_ALGO_CPTE_TYPE] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)8,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_ALGO_CPTE_TYPE
    },
    [APPSPM_PRM_GTRY_CALIB_TYPE] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_CALIB_TYPE
    },
    [APPSPM_PRM_GTRY_SENDITER_TYPE] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_SENDITER_TYPE
    },
    [APPSPM_PRM_GTRY_AXE_X_PULSE_PER_ROUND] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)32000,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_GTRY_AXE_Y_PULSE_PER_ROUND] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)32000,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_GTRY_AXE_Z_PULSE_PER_ROUND] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)32000,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_GTRY_AXE_X_LEN_MM] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)1200,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_AXE_X_LEN_MM
    },
    [APPSPM_PRM_GTRY_AXE_Y_LEN_MM] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)1200,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_AXE_Y_LEN_MM
    },
    [APPSPM_PRM_GTRY_AXE_Z_LEN_MM] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)1000,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_AXE_Z_LEN_MM
    },
    [APPSPM_PRM_GTRY_AXE_X_PINION_DIAM_MM] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)60,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_GTRY_AXE_Y_PINION_DIAM_MM] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)60,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_GTRY_AXE_Z_PINION_DIAM_MM] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)30,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_GTRY_AXE_X_SAFE_HEIGHT] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)150.0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_AXE_X_SAFE_HEIGHT
    },
    [APPSPM_PRM_GTRY_AXE_Y_SAFE_HEIGHT] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)150.0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_AXE_Y_SAFE_HEIGHT
    },
    [APPSPM_PRM_GTRY_AXE_Z_SAFE_HEIGHT] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)150.0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_GTRY_AXE_Z_SAFE_HEIGHT
    },
    [APPSPM_PRM_SYS_OPT_ACT_MTR_WHL_AV_L] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_MTR_WHL_AV_R] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_MTR_HD_KNF] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_MTR_HD_CNTR_KNF] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_MTR_HD_HOLD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_PWR_MTR_XL] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_PWR_MTR_XR] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_PWR_MTR_Y] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_PWR_MTR_Z] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_PWR_WHL_AV_L] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_PWR_WHL_AV_R] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_PWR_MTR_HD_KNF] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_PWR_MTR_HD_CNTR_KNF] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_PWR_MTR_HD_HOLD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_ECDR_WHL_AV_L] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_ECDR_WHL_AV_R] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_ECDR_HD_KNF] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_ECDR_HD_CNTR_KNF] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_ECDR_HD_HOLD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_HD_UP_LEFT] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_HD_DWN_LEFT] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_HD_UP_RIGHT] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_HD_DWN_RIGHT] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_XL] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_XR] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_Y] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_Z] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_WHL_AV_L] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_WHL_AV_R] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_HD_KNF] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_CNTR_KNF] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_HD_HOLD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_MTR_PROP_WHL_AR_L] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_ACT_MTR_PROP_WHL_AR_R] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SYS_ROBOT_DIR_FORWARD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SYS_ROBOT_DIR_BACKWARD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SYS_ROBOT_PROP_FORWARD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SYS_OPT_SYS_ROBOT_PROP_BACKWARD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)255,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT8,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_SNSCAL_ECDR_XL_OFFSET] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_XL_OFFSET
    },
    [APPSPM_PRM_SNSCAL_ECDR_XL_GAIN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_XL_GAIN
    },
    [APPSPM_PRM_SNSCAL_ECDR_XR_OFFSET] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_XR_OFFSET
    },
    [APPSPM_PRM_SNSCAL_ECDR_XR_GAIN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_XR_GAIN
    },
    [APPSPM_PRM_SNSCAL_ECDR_Y_OFFSET] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_Y_OFFSET
    },
    [APPSPM_PRM_SNSCAL_ECDR_Y_GAIN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_Y_GAIN
    },
    [APPSPM_PRM_SNSCAL_ECDR_Z_OFFSET] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_Z_OFFSET
    },
    [APPSPM_PRM_SNSCAL_ECDR_Z_GAIN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_Z_GAIN
    },
    [APPSPM_PRM_SNSCAL_ECDR_HD_KNF_OFFSET] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_KNF_OFFSET
    },
    [APPSPM_PRM_SNSCAL_ECDR_HD_KNF_GAIN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_KNF_GAIN
    },
    [APPSPM_PRM_SNSCAL_ECDR_HD_CNTR_KNF_OFFSET] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_CNTR_KNF_OFFSET
    },
    [APPSPM_PRM_SNSCAL_ECDR_HD_CNTR_KNF_GAIN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_CNTR_KNF_GAIN
    },
    [APPSPM_PRM_SNSCAL_ECDR_HD_HOLD_KNF_OFFSET] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_HOLD_KNF_OFFSET
    },
    [APPSPM_PRM_SNSCAL_ECDR_HD_HOLD_KNF_GAIN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_HOLD_KNF_GAIN
    },
    [APPSPM_PRM_SNSCAL_ECDR_WHL_AV_L_OFFSET] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_WHL_AV_L_OFFSET
    },
    [APPSPM_PRM_SNSCAL_ECDR_WHL_AV_L_GAIN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_WHL_AV_L_GAIN
    },
    [APPSPM_PRM_SNSCAL_ECDR_WHL_AV_R_OFFSET] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)0,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_WHL_AV_R_OFFSET
    },
    [APPSPM_PRM_SNSCAL_ECDR_WHL_AV_R_GAIN] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-0xFFFFFF,
        .maxItemVal_f32 = (t_float32)0xFFFFFFFF,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_PRM_SNSCAL_ECDR_WHL_AV_R_GAIN
    },
    [APPSPM_PRM_HC_LEN_FROM_REFA_TO_REFB] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)235,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_HC_LEN_HEAD_CNTR_KNIFE] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)310,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_HC_LEN_HEAD_KNIFE] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)205,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_HC_TIP_KNIFE_POS_X_MIN_MM] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-32000,
        .maxItemVal_f32 = (t_float32)32000,
        .DefaultItemVal_f32 = (t_float32)-300,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_SINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_HC_TIP_KNIFE_POS_X_MAX_MM] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-32000,
        .maxItemVal_f32 = (t_float32)32000,
        .DefaultItemVal_f32 = (t_float32)340,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_HC_TIP_KNIFE_POS_Y_MIN_MM] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-32000,
        .maxItemVal_f32 = (t_float32)32000,
        .DefaultItemVal_f32 = (t_float32)-300,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_HC_TIP_KNIFE_POS_Y_MAX_MM] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)-32000,
        .maxItemVal_f32 = (t_float32)32000,
        .DefaultItemVal_f32 = (t_float32)300,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_HC_TIP_KNIFE_MAX_DELTA_ALPHA_B] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)6284,
        .DefaultItemVal_f32 = (t_float32)100,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_HC_TIP_KNIFE_MAX_DELTA_ALPHA_C] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)6284,
        .DefaultItemVal_f32 = (t_float32)100,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_HC_CNTR_KNIFE_PULSE_TO_RAD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)3200,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_HC_KNIFE_PULSE_TO_RAD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)3200,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_HC_HOLD_KNIFE_PULSE_TO_RAD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)3200,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_HC_KNIFE_RPM_TO_HZ] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)53.33,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_HC_CNTR_KNIFE_RPM_TO_HZ] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)53.33,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_HC_HOLD_KNIFE_RPM_TO_HZ] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)53.33,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_MOT_ACTDIR_WHAVL_PULSE_TO_RAD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)3200,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_MOT_ACTDIR_WHAVR_PULSE_TO_RAD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)3200,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_MOT_ACTDIR_WHAVL_RPM_TO_HZ] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)53.33,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_MOT_ACTDIR_WHAVR_RPM_TO_HZ] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)53.33,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_FLOAT32,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_MOT_ACTDIR_WHAVL_DELTA_LIMIT_MRAD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)150,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
    },
    [APPSPM_PRM_MOT_ACTDIR_WHAVR_DELTA_LIMIT_MRAD] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)150,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB
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
