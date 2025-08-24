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
        t_uint16 minItemVal_u16;        //---- min value accpeted for the parameter ----//
        t_uint16 maxItemVal_u16;        //---- max value accpted for the parameter ----//
        t_uint16 DefaultItemVal_u16;    //---- default value ----//
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
        {(t_uint8)1,                    (t_uint16)1,                   (t_uint16)65535,               (t_uint16)4000,                APPSIG_SIGNAL_PRM_LGC_MTR_PULSE_ITER_MAX},           // APPSPM_PRM_LGC_MTR_PULSE_ITER_MAX
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)2,                   APPSIG_SIGNAL_PRM_LGC_MTR_XL_RAMP_CTRL_KFACTOR},     // APPSPM_PRM_LGC_MTR_XL_RAMP_CTRL_KFACTOR
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)65300,               APPSIG_SIGNAL_PRM_LGC_MTR_XL_RAMP_CTRL_SLOP_SPEED},  // APPSPM_PRM_LGC_MTR_XL_RAMP_CTRL_SLOP_SPEED
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)50,                  APPSIG_SIGNAL_PRM_LGC_MTR_XL_RAMP_CTRL_TOTAL_STEP},  // APPSPM_PRM_LGC_MTR_XL_RAMP_CTRL_TOTAL_STEP
        {(t_uint8)1,                    (t_uint16)1,                   (t_uint16)65535,               (t_uint16)26000,               APPSIG_SIGNAL_PRM_LGC_MTR_XL_SPEED_MAX},             // APPSPM_PRM_LGC_MTR_XL_SPEED_MAX
        {(t_uint8)1,                    (t_uint16)1,                   (t_uint16)65535,               (t_uint16)600,                 APPSIG_SIGNAL_PRM_LGC_MTR_XL_SPEED_MIN},             // APPSPM_PRM_LGC_MTR_XL_SPEED_MIN
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)2,                   APPSIG_SIGNAL_PRM_LGC_MTR_XR_RAMP_CTRL_KFACTOR},     // APPSPM_PRM_LGC_MTR_XR_RAMP_CTRL_KFACTOR
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)65300,               APPSIG_SIGNAL_PRM_LGC_MTR_XR_RAMP_CTRL_SLOP_SPEED},  // APPSPM_PRM_LGC_MTR_XR_RAMP_CTRL_SLOP_SPEED
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)50,                  APPSIG_SIGNAL_PRM_LGC_MTR_XR_RAMP_CTRL_TOTAL_STEP},  // APPSPM_PRM_LGC_MTR_XR_RAMP_CTRL_TOTAL_STEP
        {(t_uint8)1,                    (t_uint16)1,                   (t_uint16)65535,               (t_uint16)26000,               APPSIG_SIGNAL_PRM_LGC_MTR_XR_SPEED_MAX},             // APPSPM_PRM_LGC_MTR_XR_SPEED_MAX
        {(t_uint8)1,                    (t_uint16)1,                   (t_uint16)65535,               (t_uint16)600,                 APPSIG_SIGNAL_PRM_LGC_MTR_XR_SPEED_MIN},             // APPSPM_PRM_LGC_MTR_XR_SPEED_MIN
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)2,                   APPSIG_SIGNAL_PRM_LGC_MTR_Y_RAMP_CTRL_KFACTOR},      // APPSPM_PRM_LGC_MTR_Y_RAMP_CTRL_KFACTOR
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)65300,               APPSIG_SIGNAL_PRM_LGC_MTR_Y_RAMP_CTRL_SLOP_SPEED},   // APPSPM_PRM_LGC_MTR_Y_RAMP_CTRL_SLOP_SPEED
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)50,                  APPSIG_SIGNAL_PRM_LGC_MTR_Y_RAMP_CTRL_TOTAL_STEP},   // APPSPM_PRM_LGC_MTR_Y_RAMP_CTRL_TOTAL_STEP
        {(t_uint8)1,                    (t_uint16)1,                   (t_uint16)65535,               (t_uint16)26000,               APPSIG_SIGNAL_PRM_LGC_MTR_Y_SPEED_MAX},              // APPSPM_PRM_LGC_MTR_Y_SPEED_MAX
        {(t_uint8)1,                    (t_uint16)1,                   (t_uint16)65535,               (t_uint16)600,                 APPSIG_SIGNAL_PRM_LGC_MTR_Y_SPEED_MIN},              // APPSPM_PRM_LGC_MTR_Y_SPEED_MIN
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)2,                   APPSIG_SIGNAL_PRM_LGC_MTR_Z_RAMP_CTRL_KFACTOR},      // APPSPM_PRM_LGC_MTR_Z_RAMP_CTRL_KFACTOR
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)65300,               APPSIG_SIGNAL_PRM_LGC_MTR_Z_RAMP_CTRL_SLOP_SPEED},   // APPSPM_PRM_LGC_MTR_Z_RAMP_CTRL_SLOP_SPEED
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)50,                  APPSIG_SIGNAL_PRM_LGC_MTR_Z_RAMP_CTRL_TOTAL_STEP},   // APPSPM_PRM_LGC_MTR_Z_RAMP_CTRL_TOTAL_STEP
        {(t_uint8)1,                    (t_uint16)1,                   (t_uint16)65535,               (t_uint16)26000,               APPSIG_SIGNAL_PRM_LGC_MTR_Z_SPEED_MAX},              // APPSPM_PRM_LGC_MTR_Z_SPEED_MAX
        {(t_uint8)1,                    (t_uint16)1,                   (t_uint16)65535,               (t_uint16)600,                 APPSIG_SIGNAL_PRM_LGC_MTR_Z_SPEED_MIN},              // APPSPM_PRM_LGC_MTR_Z_SPEED_MIN
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)0,                   APPSIG_SIGNAL_NB},                                   // APPSPM_PRM_SYS_OPT_SNS_ECDR_XL
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)0,                   APPSIG_SIGNAL_NB},                                   // APPSPM_PRM_SYS_OPT_SNS_ECDR_XR
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)0,                   APPSIG_SIGNAL_NB},                                   // APPSPM_PRM_SYS_OPT_SNS_ECDR_Y
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)0,                   APPSIG_SIGNAL_NB},                                   // APPSPM_PRM_SYS_OPT_SNS_ECDR_Z
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)0,                   APPSIG_SIGNAL_NB},                                   // APPSPM_PRM_SYS_MACHINE_ID
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)0,                   APPSIG_SIGNAL_NB},                                   // APPSPM_PRM_SYS_OPT_ACT_MTR_XL
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)0,                   APPSIG_SIGNAL_NB},                                   // APPSPM_PRM_SYS_OPT_ACT_MTR_XR
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)0,                   APPSIG_SIGNAL_NB},                                   // APPSPM_PRM_SYS_OPT_ACT_MTR_Y
        {(t_uint8)1,                    (t_uint16)0,                   (t_uint16)65535,               (t_uint16)0,                   APPSIG_SIGNAL_NB},                                   // APPSPM_PRM_SYS_OPT_ACT_MTR_Z
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
