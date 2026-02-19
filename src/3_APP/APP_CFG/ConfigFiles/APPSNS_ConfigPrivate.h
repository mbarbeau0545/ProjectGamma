/*********************************************************************
 * @file        APPSNS_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPSNS_CONFIGPRIVATE_H_INCLUDED
#define APPSNS_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APPSNS_ConfigPublic.h"
    #include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
    #include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
    /* CAUTION : Automatic generated code section for Include: Start */
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_XL.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_XL.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_XR.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_XR.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_Y.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_Y.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_Z.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_Z.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_WHL_AV_L.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_WHL_AV_L.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_WHL_AV_R.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_WHL_AV_R.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_HD_KNF.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_HD_KNF.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_HD_CNTR_KNF.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_HD_CNTR_KNF.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_HD_HOLD.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_ECDR_HD_HOLD.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_HD_UP_LEFT.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_HD_DWN_LEFT.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_HD_UP_RIGHT.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_HD_DWN_RIGHT.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_TRQ_MTR_XL.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_TRQ_MTR_XR.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_TRQ_MTR_Y.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_TRQ_MTR_Z.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_TRQ_MTR_WHL_AV_L.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_TRQ_MTR_WHL_AV_R.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_TRQ_MTR_HD_KNF.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_TRQ_MTR_CNTR_KNF.h"
    #include "APP_CFG\\ConfigSpecific\\AppSns_ConfigSpecific/APPSNS_SPEC_TRQ_MTR_HD_HOLD.h"
    /* CAUTION : Automatic generated code section for Include: End */
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define APPSNS_CFG_NB_PER_CYCLE ((t_uint8)5)
    // ********************************************************************
    // *                      Types
    // ********************************************************************
	/* CAUTION : Automatic generated code section for Enum: Start */

	/* CAUTION : Automatic generated code section for Enum: End */
    /* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
	//-----------------------------STRUCT TYPES---------------------------//
    
	//-----------------------------ENUM TYPES-----------------------------//

    //-----------------------------TYPEDEF TYPES---------------------------//
    /**
    *
    *	@brief      Set a sensor configuration 

    */
    typedef t_eReturnCode (t_cbAppSns_SetSnsCfg)(t_uint8 f_snsDvcOpt_u8, t_eAPPSNS_SnsDriverList * f_DrvUsed_pe);
    /**
    *
    *	@brief      get value for a sensor
    *
    *	@param[in] f_SnsValue_ps : structure to store value and validity
    *
    */
    typedef t_eReturnCode (t_cbAppSns_GetSigValue)(t_float32 *f_rawSigValue_pf32, t_bool * f_isValue_OK);
    /**
    *
    *	@brief      Format the value sensors depdning on how it will be treated in Logic
    *   @note       For example, if the Sensors is a temperature, no matter the signal was (digital, analogic)
    *               this function has to format it into a Temperature SI (system international) value. 
    *
    *	@param[in] rawValue_f32 : the value from ana/dig signal 
    *	@param[in] SnsValue_f32 : the value which will be used in logic
    *
    */
    typedef t_eReturnCode (t_cbAppSns_FormatValSI)(t_float32  rawValue_f32, t_float32 *SnsValue_f32);
    /**
    *
    *	@brief      Set the driver init function
    */
    typedef t_eReturnCode (t_cbAppSns_DrvInit)(void);
    /**
    *
    *	@brief      Set the driver cyclic function
    *
    */
    typedef t_eReturnCode (t_cbAppSns_DrvCyclic)(void);
    /**
    *
    *	@brief      Conversion Management function.\n
    *
    */
   typedef t_eReturnCode (t_cbAppSns_ConversionMngmt)(t_float32 f_rawValue_f32, t_float32 *f_snsValue_ps16);
	
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
    ///@brief Structure for sensors device managment 
    typedef struct 
    {
        t_eAPPSYS_SysOptionList      sysOptSnsDvc_e;
        t_cbAppSns_SetSnsCfg         * SetCfg_pcb;             /**< Reference to "set config" function */
    } t_sAPPSNS_SnsDvcOpeCfg;

	///@brief Structure to store needed functions for a sensor
    typedef struct 
    {
        t_eAPPSNS_SnsDeviceList        deviceLink_e;          /**< the name of the device which sensors interface is linked */
        t_eAPPSNS_SnsMeasType          measTyp_e;
        t_cbAppSns_GetSigValue       * GetValue_pcb;           /**< Reference to "get value" function */
        t_cbAppSns_FormatValSI       * FormatValSI_pcb;        /**< Reference to convert signal function */ 
        t_eAPPSIG_Signal               SigDebug_e;             /**< Debug signal mapping */
    } t_sAPPSNS_SysSnsCfg;

    ///@brief Structure to store needed functions for a driver
    typedef struct 
    {
        t_cbAppSns_DrvInit   * Init_pcb;
        t_cbAppSns_DrvCyclic * Cyclic_pcb;
        t_bool isFastTaskCyclic_b;
    } t_sAPPSNS_SysDrvFunc;


    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    ///@brief Variable for System Sensors Interface Ope Mngmt Info
    const t_sAPPSNS_SysSnsCfg c_AppSns_SysSns_as[APPSNS_SNSITF_NB] = {
        {APPSNS_SNSDVC_ECDR_XL,                                       APPSNS_MEASTYPE_ANGLE,                                       APPSNS_SPEC_ECDR_XL_POS_GetSigValue,                           APPSNS_SPEC_ECDR_XL_POS_FormatValue,                        APPSIG_SIGNAL_SNS_ECDR_XL_POS},//APPSNS_SNSITF_ECDR_XL_POS
        {APPSNS_SNSDVC_ECDR_XL,                                       APPSNS_MEASTYPE_ANGULAR_SPD,                                 APPSNS_SPEC_ECDR_XL_SPD_GetSigValue,                           APPSNS_SPEC_ECDR_XL_SPD_FormatValue,                        APPSIG_SIGNAL_SNS_ECDR_XL_SPD},//APPSNS_SNSITF_ECDR_XL_SPD
        {APPSNS_SNSDVC_ECDR_XR,                                       APPSNS_MEASTYPE_ANGLE,                                       APPSNS_SPEC_ECDR_XR_POS_GetSigValue,                           APPSNS_SPEC_ECDR_XR_POS_FormatValue,                        APPSIG_SIGNAL_SNS_ECDR_XR_POS},//APPSNS_SNSITF_ECDR_XR_POS
        {APPSNS_SNSDVC_ECDR_XR,                                       APPSNS_MEASTYPE_ANGULAR_SPD,                                 APPSNS_SPEC_ECDR_XR_SPD_GetSigValue,                           APPSNS_SPEC_ECDR_XR_SPD_FormatValue,                        APPSIG_SIGNAL_SNS_ECDR_XR_SPD},//APPSNS_SNSITF_ECDR_XR_SPD
        {APPSNS_SNSDVC_ECDR_Y,                                        APPSNS_MEASTYPE_ANGLE,                                       APPSNS_SPEC_ECDR_Y_POS_GetSigValue,                            APPSNS_SPEC_ECDR_Y_POS_FormatValue,                         APPSIG_SIGNAL_SNS_ECDR_Y_POS},//APPSNS_SNSITF_ECDR_Y_POS
        {APPSNS_SNSDVC_ECDR_Y,                                        APPSNS_MEASTYPE_ANGULAR_SPD,                                 APPSNS_SPEC_ECDR_Y_SPD_GetSigValue,                            APPSNS_SPEC_ECDR_Y_SPD_FormatValue,                         APPSIG_SIGNAL_SNS_ECDR_Y_SPD},//APPSNS_SNSITF_ECDR_Y_SPD
        {APPSNS_SNSDVC_ECDR_Z,                                        APPSNS_MEASTYPE_ANGLE,                                       APPSNS_SPEC_ECDR_Z_POS_GetSigValue,                            APPSNS_SPEC_ECDR_Z_POS_FormatValue,                         APPSIG_SIGNAL_SNS_ECDR_Z_POS},//APPSNS_SNSITF_ECDR_Z_POS
        {APPSNS_SNSDVC_ECDR_Z,                                        APPSNS_MEASTYPE_ANGULAR_SPD,                                 APPSNS_SPEC_ECDR_Z_SPD_GetSigValue,                            APPSNS_SPEC_ECDR_Z_SPD_FormatValue,                         APPSIG_SIGNAL_SNS_ECDR_Z_SPD},//APPSNS_SNSITF_ECDR_Z_SPD
        {APPSNS_SNSDVC_ECDR_WHL_AV_L,                                 APPSNS_MEASTYPE_ANGLE,                                       APPSNS_SPEC_ECDR_WHL_AV_L_POS_GetSigValue,                     APPSNS_SPEC_ECDR_WHL_AV_L_POS_FormatValue,                  APPSIG_SIGNAL_SNS_ECDR_WHL_AV_L_POS},//APPSNS_SNSITF_ECDR_WHL_AV_L_POS
        {APPSNS_SNSDVC_ECDR_WHL_AV_L,                                 APPSNS_MEASTYPE_ANGULAR_SPD,                                 APPSNS_SPEC_ECDR_WHL_AV_L_SPD_GetSigValue,                     APPSNS_SPEC_ECDR_WHL_AV_L_SPD_FormatValue,                  APPSIG_SIGNAL_SNS_ECDR_WHL_AV_L_SPD},//APPSNS_SNSITF_ECDR_WHL_AV_L_SPD
        {APPSNS_SNSDVC_ECDR_WHL_AV_R,                                 APPSNS_MEASTYPE_ANGLE,                                       APPSNS_SPEC_ECDR_WHL_AV_R_POS_GetSigValue,                     APPSNS_SPEC_ECDR_WHL_AV_R_POS_FormatValue,                  APPSIG_SIGNAL_SNS_ECDR_WHL_AV_R_POS},//APPSNS_SNSITF_ECDR_WHL_AV_R_POS
        {APPSNS_SNSDVC_ECDR_WHL_AV_R,                                 APPSNS_MEASTYPE_ANGULAR_SPD,                                 APPSNS_SPEC_ECDR_WHL_AV_R_SPD_GetSigValue,                     APPSNS_SPEC_ECDR_WHL_AV_R_SPD_FormatValue,                  APPSIG_SIGNAL_SNS_ECDR_WHL_AV_R_SPD},//APPSNS_SNSITF_ECDR_WHL_AV_R_SPD
        {APPSNS_SNSDVC_ECDR_HD_KNF,                                   APPSNS_MEASTYPE_ANGLE,                                       APPSNS_SPEC_ECDR_HD_KNF_POS_GetSigValue,                       APPSNS_SPEC_ECDR_HD_KNF_POS_FormatValue,                    APPSIG_SIGNAL_SNS_ECDR_HD_KNF_POS},//APPSNS_SNSITF_ECDR_HD_KNF_POS
        {APPSNS_SNSDVC_ECDR_HD_KNF,                                   APPSNS_MEASTYPE_ANGULAR_SPD,                                 APPSNS_SPEC_ECDR_HD_KNF_SPD_GetSigValue,                       APPSNS_SPEC_ECDR_HD_KNF_SPD_FormatValue,                    APPSIG_SIGNAL_SNS_ECDR_HD_KNF_SPD},//APPSNS_SNSITF_ECDR_HD_KNF_SPD
        {APPSNS_SNSDVC_ECDR_HD_CNTR_KNF,                              APPSNS_MEASTYPE_ANGLE,                                       APPSNS_SPEC_ECDR_HD_CNTR_KNF_POS_GetSigValue,                  APPSNS_SPEC_ECDR_HD_CNTR_KNF_POS_FormatValue,               APPSIG_SIGNAL_SNS_ECDR_HD_CNTR_KNF_POS},//APPSNS_SNSITF_ECDR_HD_CNTR_KNF_POS
        {APPSNS_SNSDVC_ECDR_HD_CNTR_KNF,                              APPSNS_MEASTYPE_ANGULAR_SPD,                                 APPSNS_SPEC_ECDR_HD_CNTR_KNF_SPD_GetSigValue,                  APPSNS_SPEC_ECDR_HD_CNTR_KNF_SPD_FormatValue,               APPSIG_SIGNAL_SNS_ECDR_HD_CNTR_KNF_SPD},//APPSNS_SNSITF_ECDR_HD_CNTR_KNF_SPD
        {APPSNS_SNSDVC_ECDR_HD_HOLD,                                  APPSNS_MEASTYPE_ANGLE,                                       APPSNS_SPEC_ECDR_HD_HOLD_POS_GetSigValue,                      APPSNS_SPEC_ECDR_HD_HOLD_POS_FormatValue,                   APPSIG_SIGNAL_SNS_ECDR_HD_HOLD_POS},//APPSNS_SNSITF_ECDR_HD_HOLD_POS
        {APPSNS_SNSDVC_ECDR_HD_HOLD,                                  APPSNS_MEASTYPE_ANGULAR_SPD,                                 APPSNS_SPEC_ECDR_HD_HOLD_SPD_GetSigValue,                      APPSNS_SPEC_ECDR_HD_HOLD_SPD_FormatValue,                   APPSIG_SIGNAL_SNS_ECDR_HD_HOLD_SPD},//APPSNS_SNSITF_ECDR_HD_HOLD_SPD
        {APPSNS_SNSDVC_HD_UP_LEFT,                                    APPSNS_MEASTYPE_DISTANCE,                                    APPSNS_SPEC_HD_UP_LEFT_DIST_GetSigValue,                       APPSNS_SPEC_HD_UP_LEFT_DIST_FormatValue,                    APPSIG_SIGNAL_SNS_HD_UP_LEFT_DIST},//APPSNS_SNSITF_HD_UP_LEFT_DIST
        {APPSNS_SNSDVC_HD_DWN_LEFT,                                   APPSNS_MEASTYPE_DISTANCE,                                    APPSNS_SPEC_HD_DWN_LEFT_DIST_GetSigValue,                      APPSNS_SPEC_HD_DWN_LEFT_DIST_FormatValue,                   APPSIG_SIGNAL_SNS_HD_DWN_LEFT_DIST},//APPSNS_SNSITF_HD_DWN_LEFT_DIST
        {APPSNS_SNSDVC_HD_UP_RIGHT,                                   APPSNS_MEASTYPE_DISTANCE,                                    APPSNS_SPEC_HD_UP_RIGHT_DIST_GetSigValue,                      APPSNS_SPEC_HD_UP_RIGHT_DIST_FormatValue,                   APPSIG_SIGNAL_SNS_HD_UP_RIGHT_DIST},//APPSNS_SNSITF_HD_UP_RIGHT_DIST
        {APPSNS_SNSDVC_HD_DWN_RIGHT,                                  APPSNS_MEASTYPE_DISTANCE,                                    APPSNS_SPEC_HD_DWN_RIGHT_DIST_GetSigValue,                     APPSNS_SPEC_HD_DWN_RIGHT_DIST_FormatValue,                  APPSIG_SIGNAL_SNS_HD_DWN_RIGHT_DIST},//APPSNS_SNSITF_HD_DWN_RIGHT_DIST
        {APPSNS_SNSDVC_TRQ_MTR_XL,                                    APPSNS_MEASTYPE_FORCE,                                       APPSNS_SPEC_TRQ_MTR_XL_TRQ_GetSigValue,                        APPSNS_SPEC_TRQ_MTR_XL_TRQ_FormatValue,                     APPSIG_SIGNAL_SNS_TRQ_MTR_XL_TRQ},//APPSNS_SNSITF_TRQ_MTR_XL_TRQ
        {APPSNS_SNSDVC_TRQ_MTR_XR,                                    APPSNS_MEASTYPE_FORCE,                                       APPSNS_SPEC_TRQ_MTR_XR_TRQ_GetSigValue,                        APPSNS_SPEC_TRQ_MTR_XR_TRQ_FormatValue,                     APPSIG_SIGNAL_SNS_TRQ_MTR_XR_TRQ},//APPSNS_SNSITF_TRQ_MTR_XR_TRQ
        {APPSNS_SNSDVC_TRQ_MTR_Y,                                     APPSNS_MEASTYPE_FORCE,                                       APPSNS_SPEC_TRQ_MTR_Y_TRQ_GetSigValue,                         APPSNS_SPEC_TRQ_MTR_Y_TRQ_FormatValue,                      APPSIG_SIGNAL_SNS_TRQ_MTR_Y_TRQ},//APPSNS_SNSITF_TRQ_MTR_Y_TRQ
        {APPSNS_SNSDVC_TRQ_MTR_Z,                                     APPSNS_MEASTYPE_FORCE,                                       APPSNS_SPEC_TRQ_MTR_Z_TRQ_GetSigValue,                         APPSNS_SPEC_TRQ_MTR_Z_TRQ_FormatValue,                      APPSIG_SIGNAL_SNS_TRQ_MTR_Z_TRQ},//APPSNS_SNSITF_TRQ_MTR_Z_TRQ
        {APPSNS_SNSDVC_TRQ_MTR_WHL_AV_L,                              APPSNS_MEASTYPE_FORCE,                                       APPSNS_SPEC_TRQ_MTR_WHL_AV_L_TRQ_GetSigValue,                  APPSNS_SPEC_TRQ_MTR_WHL_AV_L_TRQ_FormatValue,               APPSIG_SIGNAL_SNS_TRQ_MTR_WHL_AV_L_TRQ},//APPSNS_SNSITF_TRQ_MTR_WHL_AV_L_TRQ
        {APPSNS_SNSDVC_TRQ_MTR_WHL_AV_R,                              APPSNS_MEASTYPE_FORCE,                                       APPSNS_SPEC_TRQ_MTR_WHL_AV_R_TRQ_GetSigValue,                  APPSNS_SPEC_TRQ_MTR_WHL_AV_R_TRQ_FormatValue,               APPSIG_SIGNAL_SNS_TRQ_MTR_WHL_AV_R_TRQ},//APPSNS_SNSITF_TRQ_MTR_WHL_AV_R_TRQ
        {APPSNS_SNSDVC_TRQ_MTR_HD_KNF,                                APPSNS_MEASTYPE_FORCE,                                       APPSNS_SPEC_TRQ_MTR_HD_KNF_TRQ_GetSigValue,                    APPSNS_SPEC_TRQ_MTR_HD_KNF_TRQ_FormatValue,                 APPSIG_SIGNAL_SNS_TRQ_MTR_HD_KNF_TRQ},//APPSNS_SNSITF_TRQ_MTR_HD_KNF_TRQ
        {APPSNS_SNSDVC_TRQ_MTR_CNTR_KNF,                              APPSNS_MEASTYPE_FORCE,                                       APPSNS_SPEC_TRQ_MTR_CNTR_KNF_TRQ_GetSigValue,                  APPSNS_SPEC_TRQ_MTR_CNTR_KNF_TRQ_FormatValue,               APPSIG_SIGNAL_SNS_TRQ_MTR_CNTR_KNF_TRQ},//APPSNS_SNSITF_TRQ_MTR_CNTR_KNF_TRQ
        {APPSNS_SNSDVC_TRQ_MTR_HD_HOLD,                               APPSNS_MEASTYPE_FORCE,                                       APPSNS_SPEC_TRQ_MTR_HD_HOLD_TRQ_GetSigValue,                   APPSNS_SPEC_TRQ_MTR_HD_HOLD_TRQ_FormatValue,                APPSIG_SIGNAL_SNS_TRQ_MTR_HD_HOLD_TRQ},//APPSNS_SNSITF_TRQ_MTR_HD_HOLD_TRQ
    };

    ///@brief Variable for system Sensors Device Ope Mngmt
    const t_sAPPSNS_SnsDvcOpeCfg c_AppSns_SnsDvcOpeCfg_as[APPSNS_SNSDVC_NB] = {
        {APPSYS_OPT_ID_SNS_ECDR_XL,                                   APPSNS_SPEC_ECDR_XL_SetCfg},                                   // APPSNS_SNSDVC_ECDR_XL
        {APPSYS_OPT_ID_SNS_ECDR_XR,                                   APPSNS_SPEC_ECDR_XR_SetCfg},                                   // APPSNS_SNSDVC_ECDR_XR
        {APPSYS_OPT_ID_SNS_ECDR_Y,                                    APPSNS_SPEC_ECDR_Y_SetCfg},                                    // APPSNS_SNSDVC_ECDR_Y
        {APPSYS_OPT_ID_SNS_ECDR_Z,                                    APPSNS_SPEC_ECDR_Z_SetCfg},                                    // APPSNS_SNSDVC_ECDR_Z
        {APPSYS_OPT_ID_SNS_ECDR_WHL_AV_L,                             APPSNS_SPEC_ECDR_WHL_AV_L_SetCfg},                             // APPSNS_SNSDVC_ECDR_WHL_AV_L
        {APPSYS_OPT_ID_SNS_ECDR_WHL_AV_R,                             APPSNS_SPEC_ECDR_WHL_AV_R_SetCfg},                             // APPSNS_SNSDVC_ECDR_WHL_AV_R
        {APPSYS_OPT_ID_SNS_ECDR_HD_KNF,                               APPSNS_SPEC_ECDR_HD_KNF_SetCfg},                               // APPSNS_SNSDVC_ECDR_HD_KNF
        {APPSYS_OPT_ID_SNS_ECDR_HD_CNTR_KNF,                          APPSNS_SPEC_ECDR_HD_CNTR_KNF_SetCfg},                          // APPSNS_SNSDVC_ECDR_HD_CNTR_KNF
        {APPSYS_OPT_ID_SNS_ECDR_HD_HOLD,                              APPSNS_SPEC_ECDR_HD_HOLD_SetCfg},                              // APPSNS_SNSDVC_ECDR_HD_HOLD
        {APPSYS_OPT_ID_SNS_HD_UP_LEFT,                                APPSNS_SPEC_HD_UP_LEFT_SetCfg},                                // APPSNS_SNSDVC_HD_UP_LEFT
        {APPSYS_OPT_ID_SNS_HD_DWN_LEFT,                               APPSNS_SPEC_HD_DWN_LEFT_SetCfg},                               // APPSNS_SNSDVC_HD_DWN_LEFT
        {APPSYS_OPT_ID_SNS_HD_UP_RIGHT,                               APPSNS_SPEC_HD_UP_RIGHT_SetCfg},                               // APPSNS_SNSDVC_HD_UP_RIGHT
        {APPSYS_OPT_ID_SNS_HD_DWN_RIGHT,                              APPSNS_SPEC_HD_DWN_RIGHT_SetCfg},                              // APPSNS_SNSDVC_HD_DWN_RIGHT
        {APPSYS_OPT_ID_SNS_TRQ_MTR_XL,                                APPSNS_SPEC_TRQ_MTR_XL_SetCfg},                                // APPSNS_SNSDVC_TRQ_MTR_XL
        {APPSYS_OPT_ID_SNS_TRQ_MTR_XR,                                APPSNS_SPEC_TRQ_MTR_XR_SetCfg},                                // APPSNS_SNSDVC_TRQ_MTR_XR
        {APPSYS_OPT_ID_SNS_TRQ_MTR_Y,                                 APPSNS_SPEC_TRQ_MTR_Y_SetCfg},                                 // APPSNS_SNSDVC_TRQ_MTR_Y
        {APPSYS_OPT_ID_SNS_TRQ_MTR_Z,                                 APPSNS_SPEC_TRQ_MTR_Z_SetCfg},                                 // APPSNS_SNSDVC_TRQ_MTR_Z
        {APPSYS_OPT_ID_SNS_TRQ_MTR_WHL_AV_L,                          APPSNS_SPEC_TRQ_MTR_WHL_AV_L_SetCfg},                          // APPSNS_SNSDVC_TRQ_MTR_WHL_AV_L
        {APPSYS_OPT_ID_SNS_TRQ_MTR_WHL_AV_R,                          APPSNS_SPEC_TRQ_MTR_WHL_AV_R_SetCfg},                          // APPSNS_SNSDVC_TRQ_MTR_WHL_AV_R
        {APPSYS_OPT_ID_SNS_TRQ_MTR_HD_KNF,                            APPSNS_SPEC_TRQ_MTR_HD_KNF_SetCfg},                            // APPSNS_SNSDVC_TRQ_MTR_HD_KNF
        {APPSYS_OPT_ID_SNS_TRQ_MTR_CNTR_KNF,                          APPSNS_SPEC_TRQ_MTR_CNTR_KNF_SetCfg},                          // APPSNS_SNSDVC_TRQ_MTR_CNTR_KNF
        {APPSYS_OPT_ID_SNS_TRQ_MTR_HD_HOLD,                           APPSNS_SPEC_TRQ_MTR_HD_HOLD_SetCfg},                           // APPSNS_SNSDVC_TRQ_MTR_HD_HOLD
    };

    /**< Variable for System Sensors drivers functions*/
    const t_sAPPSNS_SysDrvFunc c_AppSns_SysDrv_as[APPSNS_DRV_NB] = {
    };

    /* CAUTION : Automatic generated code section for Variable: End */

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APPSNS_CONFIGPRIVATE_H_INCLUDED           
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
