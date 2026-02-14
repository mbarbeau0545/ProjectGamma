/*********************************************************************
 * @file        APPACT_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPACT_CONFIGPRIVATE_H_INCLUDED
#define APPACT_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APPACT_ConfigPublic.h"
    #include "./APPSYS_ConfigPublic.h"
    #include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
    #include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
    /* CAUTION : Automatic generated code section for Include: Start */
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_XL.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_XL.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_XL.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_XR.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_XR.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_XR.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_Y.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_Y.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_Y.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_Z.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_Z.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_Z.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_WHL_AV_L.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_WHL_AV_L.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_WHL_AV_L.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_WHL_AV_R.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_WHL_AV_R.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_WHL_AV_R.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_HD_KNF.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_HD_KNF.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_HD_KNF.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_HD_CNTR_KNF.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_HD_CNTR_KNF.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_HD_CNTR_KNF.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_HD_HOLD.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_HD_HOLD.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_MTR_HD_HOLD.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_PWR_MTR_XL.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_PWR_MTR_XR.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_PWR_MTR_Y.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_PWR_MTR_Z.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_PWR_WHL_AV_L.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_PWR_WHL_AV_R.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_PWR_MTR_HD_KNF.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_PWR_MTR_HD_CNTR_KNF.h"
    #include "APP_CFG\\ConfigSpecific\\AppAct_ConfigSpecific/APPACT_SPEC_PWR_MTR_HD_HOLD.h"
    /* CAUTION : Automatic generated code section for Include: End */

    #include "2_DRV/CL42T/Src/CL42T.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define APPACT_CFG_NB_PER_CYCLE ((t_uint8)5)
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
    typedef t_eReturnCode (t_cbAppAct_SetActCfg)(t_uint8 f_actDvcOpt_u8, t_eAPPACT_ActDriverList * f_DrvUsed_pe);
    /**
    *
    *	@brief      get value for a sensor
    *
    *	@param[in] f_SnsValue_ps : structure to store value and validity
    *
    */
    typedef t_eReturnCode (t_cbAppAct_GetIfValue)(t_float32 *f_rawSigValue_pf32);
    /**
    *
    *	@brief      get value for a sensor
    *
    *	@param[in] f_SnsValue_ps : structure to store value and validity
    *
    */
    typedef t_eReturnCode (t_cbAppAct_SetIfValue)(t_float32 f_SigValue_pf32);
    /**
    *
    *	@brief      Set the driver init function
    */
    typedef t_eReturnCode (t_cbAppAct_DrvInit)(void);
    /**
    *
    *	@brief      Set the driver cyclic function
    *
    */
    typedef t_eReturnCode (t_cbAppAct_DrvCyclic)(void);
	
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
    ///@brief Structure for sensors device managment 
    typedef struct 
    {
        t_eAPPSYS_SysOptionList      sysOptSnsDvc_e;
        t_cbAppAct_SetActCfg         * SetCfg_pcb;             /**< Reference to "set config" function */
    } t_sAPPACT_ActDvcOpeCfg;

	///@brief Structure to store needed functions for a sensor
    typedef struct 
    {
        t_eAPPACT_ActDeviceList        deviceLink_e;          /**< the name of the device which sensors interface is linked */
        t_cbAppAct_SetIfValue       * SetValue_pcb;
        t_cbAppAct_GetIfValue       * GetValue_pcb;           /**< Reference to "get value" function */ 
        t_eAPPSIG_Signal              SigSetDebug_e;          /**< Debug signal mapping, Set actuator Value */
        t_eAPPSIG_Signal              SigGetDebug_e;          /**< Debug signal mapping, Get actuator Value */
        t_eAPPSIG_Signal              SigCtrlDebug_e;         /**< Debug signal mapping, Control actuator Value */
    } t_sAPPACT_SysActCfg;

    ///@brief Structure to store needed functions for a driver
    typedef struct 
    {
        t_cbAppAct_DrvInit   * Init_pcb;
        t_cbAppAct_DrvCyclic * Cyclic_pcb;
        t_bool isFastTaskCyclic_b;
    } t_sAPPACT_SysDrvFunc;


    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    ///@brief Variable for System Actuators Interface Ope Mngmt Info
    const t_sAPPACT_SysActCfg c_AppAct_SysAct_as[APPACT_ACTITF_NB] = {
        {APPACT_ACTDVC_MTR_XL,                                        APPACT_SPEC_MTR_XL_PLS_SetValue,                            APPACT_SPEC_MTR_XL_PLS_GetValue,                            APPSIG_SIGNAL_ACT_SET_MTR_XL_PLS,                            APPSIG_SIGNAL_ACT_GET_MTR_XL_PLS,                            APPSIG_SIGNAL_ACT_CTRL_MTR_XL_PLS},//APPACT_ACTITF_MTR_XL_PLS
        {APPACT_ACTDVC_MTR_XL,                                        APPACT_SPEC_MTR_XL_SPD_SetValue,                            APPACT_SPEC_MTR_XL_SPD_GetValue,                            APPSIG_SIGNAL_ACT_SET_MTR_XL_SPD,                            APPSIG_SIGNAL_ACT_GET_MTR_XL_SPD,                            APPSIG_SIGNAL_ACT_CTRL_MTR_XL_SPD},//APPACT_ACTITF_MTR_XL_SPD
        {APPACT_ACTDVC_MTR_XL,                                        APPACT_SPEC_MTR_XL_TRG_SetValue,                            APPACT_SPEC_MTR_XL_TRG_GetValue,                            APPSIG_SIGNAL_ACT_SET_MTR_XL_TRG,                            APPSIG_SIGNAL_ACT_GET_MTR_XL_TRG,                            APPSIG_SIGNAL_ACT_CTRL_MTR_XL_TRG},//APPACT_ACTITF_MTR_XL_TRG
        {APPACT_ACTDVC_MTR_XR,                                        APPACT_SPEC_MTR_XR_PLS_SetValue,                            APPACT_SPEC_MTR_XR_PLS_GetValue,                            APPSIG_SIGNAL_ACT_SET_MTR_XR_PLS,                            APPSIG_SIGNAL_ACT_GET_MTR_XR_PLS,                            APPSIG_SIGNAL_ACT_CTRL_MTR_XR_PLS},//APPACT_ACTITF_MTR_XR_PLS
        {APPACT_ACTDVC_MTR_XR,                                        APPACT_SPEC_MTR_XR_SPD_SetValue,                            APPACT_SPEC_MTR_XR_SPD_GetValue,                            APPSIG_SIGNAL_ACT_SET_MTR_XR_SPD,                            APPSIG_SIGNAL_ACT_GET_MTR_XR_SPD,                            APPSIG_SIGNAL_ACT_CTRL_MTR_XR_SPD},//APPACT_ACTITF_MTR_XR_SPD
        {APPACT_ACTDVC_MTR_XR,                                        APPACT_SPEC_MTR_XR_TRG_SetValue,                            APPACT_SPEC_MTR_XR_TRG_GetValue,                            APPSIG_SIGNAL_ACT_SET_MTR_XR_TRG,                            APPSIG_SIGNAL_ACT_GET_MTR_XR_TRG,                            APPSIG_SIGNAL_ACT_CTRL_MTR_XR_TRG},//APPACT_ACTITF_MTR_XR_TRG
        {APPACT_ACTDVC_MTR_Y,                                         APPACT_SPEC_MTR_Y_PLS_SetValue,                             APPACT_SPEC_MTR_Y_PLS_GetValue,                             APPSIG_SIGNAL_ACT_SET_MTR_Y_PLS,                             APPSIG_SIGNAL_ACT_GET_MTR_Y_PLS,                             APPSIG_SIGNAL_ACT_CTRL_MTR_Y_PLS},//APPACT_ACTITF_MTR_Y_PLS
        {APPACT_ACTDVC_MTR_Y,                                         APPACT_SPEC_MTR_Y_SPD_SetValue,                             APPACT_SPEC_MTR_Y_SPD_GetValue,                             APPSIG_SIGNAL_ACT_SET_MTR_Y_SPD,                             APPSIG_SIGNAL_ACT_GET_MTR_Y_SPD,                             APPSIG_SIGNAL_ACT_CTRL_MTR_Y_SPD},//APPACT_ACTITF_MTR_Y_SPD
        {APPACT_ACTDVC_MTR_Y,                                         APPACT_SPEC_MTR_Y_TRG_SetValue,                             APPACT_SPEC_MTR_Y_TRG_GetValue,                             APPSIG_SIGNAL_ACT_SET_MTR_Y_TRG,                             APPSIG_SIGNAL_ACT_GET_MTR_Y_TRG,                             APPSIG_SIGNAL_ACT_CTRL_MTR_Y_TRG},//APPACT_ACTITF_MTR_Y_TRG
        {APPACT_ACTDVC_MTR_Z,                                         APPACT_SPEC_MTR_Z_PLS_SetValue,                             APPACT_SPEC_MTR_Z_PLS_GetValue,                             APPSIG_SIGNAL_ACT_SET_MTR_Z_PLS,                             APPSIG_SIGNAL_ACT_GET_MTR_Z_PLS,                             APPSIG_SIGNAL_ACT_CTRL_MTR_Z_PLS},//APPACT_ACTITF_MTR_Z_PLS
        {APPACT_ACTDVC_MTR_Z,                                         APPACT_SPEC_MTR_Z_SPD_SetValue,                             APPACT_SPEC_MTR_Z_SPD_GetValue,                             APPSIG_SIGNAL_ACT_SET_MTR_Z_SPD,                             APPSIG_SIGNAL_ACT_GET_MTR_Z_SPD,                             APPSIG_SIGNAL_ACT_CTRL_MTR_Z_SPD},//APPACT_ACTITF_MTR_Z_SPD
        {APPACT_ACTDVC_MTR_Z,                                         APPACT_SPEC_MTR_Z_TRG_SetValue,                             APPACT_SPEC_MTR_Z_TRG_GetValue,                             APPSIG_SIGNAL_ACT_SET_MTR_Z_TRG,                             APPSIG_SIGNAL_ACT_GET_MTR_Z_TRG,                             APPSIG_SIGNAL_ACT_CTRL_MTR_Z_TRG},//APPACT_ACTITF_MTR_Z_TRG
        {APPACT_ACTDVC_MTR_WHL_AV_L,                                  APPACT_SPEC_MTR_WHL_AV_L_PLS_SetValue,                      APPACT_SPEC_MTR_WHL_AV_L_PLS_GetValue,                      APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_L_PLS,                      APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_L_PLS,                      APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_L_PLS},//APPACT_ACTITF_MTR_WHL_AV_L_PLS
        {APPACT_ACTDVC_MTR_WHL_AV_L,                                  APPACT_SPEC_MTR_WHL_AV_L_SPD_SetValue,                      APPACT_SPEC_MTR_WHL_AV_L_SPD_GetValue,                      APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_L_SPD,                      APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_L_SPD,                      APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_L_SPD},//APPACT_ACTITF_MTR_WHL_AV_L_SPD
        {APPACT_ACTDVC_MTR_WHL_AV_L,                                  APPACT_SPEC_MTR_WHL_AV_L_TRG_SetValue,                      APPACT_SPEC_MTR_WHL_AV_L_TRG_GetValue,                      APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_L_TRG,                      APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_L_TRG,                      APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_L_TRG},//APPACT_ACTITF_MTR_WHL_AV_L_TRG
        {APPACT_ACTDVC_MTR_WHL_AV_R,                                  APPACT_SPEC_MTR_WHL_AV_R_PLS_SetValue,                      APPACT_SPEC_MTR_WHL_AV_R_PLS_GetValue,                      APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_R_PLS,                      APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_R_PLS,                      APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_R_PLS},//APPACT_ACTITF_MTR_WHL_AV_R_PLS
        {APPACT_ACTDVC_MTR_WHL_AV_R,                                  APPACT_SPEC_MTR_WHL_AV_R_SPD_SetValue,                      APPACT_SPEC_MTR_WHL_AV_R_SPD_GetValue,                      APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_R_SPD,                      APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_R_SPD,                      APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_R_SPD},//APPACT_ACTITF_MTR_WHL_AV_R_SPD
        {APPACT_ACTDVC_MTR_WHL_AV_R,                                  APPACT_SPEC_MTR_WHL_AV_R_TRG_SetValue,                      APPACT_SPEC_MTR_WHL_AV_R_TRG_GetValue,                      APPSIG_SIGNAL_ACT_SET_MTR_WHL_AV_R_TRG,                      APPSIG_SIGNAL_ACT_GET_MTR_WHL_AV_R_TRG,                      APPSIG_SIGNAL_ACT_CTRL_MTR_WHL_AV_R_TRG},//APPACT_ACTITF_MTR_WHL_AV_R_TRG
        {APPACT_ACTDVC_MTR_HD_KNF,                                    APPACT_SPEC_MTR_HD_KNF_PLS_SetValue,                        APPACT_SPEC_MTR_HD_KNF_PLS_GetValue,                        APPSIG_SIGNAL_ACT_SET_MTR_HD_KNF_PLS,                        APPSIG_SIGNAL_ACT_GET_MTR_HD_KNF_PLS,                        APPSIG_SIGNAL_ACT_CTRL_MTR_HD_KNF_PLS},//APPACT_ACTITF_MTR_HD_KNF_PLS
        {APPACT_ACTDVC_MTR_HD_KNF,                                    APPACT_SPEC_MTR_HD_KNF_SPD_SetValue,                        APPACT_SPEC_MTR_HD_KNF_SPD_GetValue,                        APPSIG_SIGNAL_ACT_SET_MTR_HD_KNF_SPD,                        APPSIG_SIGNAL_ACT_GET_MTR_HD_KNF_SPD,                        APPSIG_SIGNAL_ACT_CTRL_MTR_HD_KNF_SPD},//APPACT_ACTITF_MTR_HD_KNF_SPD
        {APPACT_ACTDVC_MTR_HD_KNF,                                    APPACT_SPEC_MTR_HD_KNF_TRG_SetValue,                        APPACT_SPEC_MTR_HD_KNF_TRG_GetValue,                        APPSIG_SIGNAL_ACT_SET_MTR_HD_KNF_TRG,                        APPSIG_SIGNAL_ACT_GET_MTR_HD_KNF_TRG,                        APPSIG_SIGNAL_ACT_CTRL_MTR_HD_KNF_TRG},//APPACT_ACTITF_MTR_HD_KNF_TRG
        {APPACT_ACTDVC_MTR_HD_CNTR_KNF,                               APPACT_SPEC_MTR_HD_CNTR_KNF_PLS_SetValue,                   APPACT_SPEC_MTR_HD_CNTR_KNF_PLS_GetValue,                   APPSIG_SIGNAL_ACT_SET_MTR_HD_CNTR_KNF_PLS,                   APPSIG_SIGNAL_ACT_GET_MTR_HD_CNTR_KNF_PLS,                   APPSIG_SIGNAL_ACT_CTRL_MTR_HD_CNTR_KNF_PLS},//APPACT_ACTITF_MTR_HD_CNTR_KNF_PLS
        {APPACT_ACTDVC_MTR_HD_CNTR_KNF,                               APPACT_SPEC_MTR_HD_CNTR_KNF_SPD_SetValue,                   APPACT_SPEC_MTR_HD_CNTR_KNF_SPD_GetValue,                   APPSIG_SIGNAL_ACT_SET_MTR_HD_CNTR_KNF_SPD,                   APPSIG_SIGNAL_ACT_GET_MTR_HD_CNTR_KNF_SPD,                   APPSIG_SIGNAL_ACT_CTRL_MTR_HD_CNTR_KNF_SPD},//APPACT_ACTITF_MTR_HD_CNTR_KNF_SPD
        {APPACT_ACTDVC_MTR_HD_CNTR_KNF,                               APPACT_SPEC_MTR_HD_CNTR_KNF_TRG_SetValue,                   APPACT_SPEC_MTR_HD_CNTR_KNF_TRG_GetValue,                   APPSIG_SIGNAL_ACT_SET_MTR_HD_CNTR_KNF_TRG,                   APPSIG_SIGNAL_ACT_GET_MTR_HD_CNTR_KNF_TRG,                   APPSIG_SIGNAL_ACT_CTRL_MTR_HD_CNTR_KNF_TRG},//APPACT_ACTITF_MTR_HD_CNTR_KNF_TRG
        {APPACT_ACTDVC_MTR_HD_HOLD,                                   APPACT_SPEC_MTR_HD_HOLD_PLS_SetValue,                       APPACT_SPEC_MTR_HD_HOLD_PLS_GetValue,                       APPSIG_SIGNAL_ACT_SET_MTR_HD_HOLD_PLS,                       APPSIG_SIGNAL_ACT_GET_MTR_HD_HOLD_PLS,                       APPSIG_SIGNAL_ACT_CTRL_MTR_HD_HOLD_PLS},//APPACT_ACTITF_MTR_HD_HOLD_PLS
        {APPACT_ACTDVC_MTR_HD_HOLD,                                   APPACT_SPEC_MTR_HD_HOLD_SPD_SetValue,                       APPACT_SPEC_MTR_HD_HOLD_SPD_GetValue,                       APPSIG_SIGNAL_ACT_SET_MTR_HD_HOLD_SPD,                       APPSIG_SIGNAL_ACT_GET_MTR_HD_HOLD_SPD,                       APPSIG_SIGNAL_ACT_CTRL_MTR_HD_HOLD_SPD},//APPACT_ACTITF_MTR_HD_HOLD_SPD
        {APPACT_ACTDVC_MTR_HD_HOLD,                                   APPACT_SPEC_MTR_HD_HOLD_TRG_SetValue,                       APPACT_SPEC_MTR_HD_HOLD_TRG_GetValue,                       APPSIG_SIGNAL_ACT_SET_MTR_HD_HOLD_TRG,                       APPSIG_SIGNAL_ACT_GET_MTR_HD_HOLD_TRG,                       APPSIG_SIGNAL_ACT_CTRL_MTR_HD_HOLD_TRG},//APPACT_ACTITF_MTR_HD_HOLD_TRG
        {APPACT_ACTDVC_PWR_MTR_XL,                                    APPACT_SPEC_PWR_MTR_XL_RLY_SetValue,                        APPACT_SPEC_PWR_MTR_XL_RLY_GetValue,                        APPSIG_SIGNAL_ACT_SET_PWR_MTR_XL_RLY,                        APPSIG_SIGNAL_ACT_GET_PWR_MTR_XL_RLY,                        APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_XL_RLY},//APPACT_ACTITF_PWR_MTR_XL_RLY
        {APPACT_ACTDVC_PWR_MTR_XR,                                    APPACT_SPEC_PWR_MTR_XR_RLY_SetValue,                        APPACT_SPEC_PWR_MTR_XR_RLY_GetValue,                        APPSIG_SIGNAL_ACT_SET_PWR_MTR_XR_RLY,                        APPSIG_SIGNAL_ACT_GET_PWR_MTR_XR_RLY,                        APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_XR_RLY},//APPACT_ACTITF_PWR_MTR_XR_RLY
        {APPACT_ACTDVC_PWR_MTR_Y,                                     APPACT_SPEC_PWR_MTR_Y_RLY_SetValue,                         APPACT_SPEC_PWR_MTR_Y_RLY_GetValue,                         APPSIG_SIGNAL_ACT_SET_PWR_MTR_Y_RLY,                         APPSIG_SIGNAL_ACT_GET_PWR_MTR_Y_RLY,                         APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_Y_RLY},//APPACT_ACTITF_PWR_MTR_Y_RLY
        {APPACT_ACTDVC_PWR_MTR_Z,                                     APPACT_SPEC_PWR_MTR_Z_RLY_SetValue,                         APPACT_SPEC_PWR_MTR_Z_RLY_GetValue,                         APPSIG_SIGNAL_ACT_SET_PWR_MTR_Z_RLY,                         APPSIG_SIGNAL_ACT_GET_PWR_MTR_Z_RLY,                         APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_Z_RLY},//APPACT_ACTITF_PWR_MTR_Z_RLY
        {APPACT_ACTDVC_PWR_WHL_AV_L,                                  APPACT_SPEC_PWR_WHL_AV_L_RLY_SetValue,                      APPACT_SPEC_PWR_WHL_AV_L_RLY_GetValue,                      APPSIG_SIGNAL_ACT_SET_PWR_WHL_AV_L_RLY,                      APPSIG_SIGNAL_ACT_GET_PWR_WHL_AV_L_RLY,                      APPSIG_SIGNAL_ACT_CTRL_PWR_WHL_AV_L_RLY},//APPACT_ACTITF_PWR_WHL_AV_L_RLY
        {APPACT_ACTDVC_PWR_WHL_AV_R,                                  APPACT_SPEC_PWR_WHL_AV_R_RLY_SetValue,                      APPACT_SPEC_PWR_WHL_AV_R_RLY_GetValue,                      APPSIG_SIGNAL_ACT_SET_PWR_WHL_AV_R_RLY,                      APPSIG_SIGNAL_ACT_GET_PWR_WHL_AV_R_RLY,                      APPSIG_SIGNAL_ACT_CTRL_PWR_WHL_AV_R_RLY},//APPACT_ACTITF_PWR_WHL_AV_R_RLY
        {APPACT_ACTDVC_PWR_MTR_HD_KNF,                                APPACT_SPEC_PWR_MTR_HD_KNF_RLY_SetValue,                    APPACT_SPEC_PWR_MTR_HD_KNF_RLY_GetValue,                    APPSIG_SIGNAL_ACT_SET_PWR_MTR_HD_KNF_RLY,                    APPSIG_SIGNAL_ACT_GET_PWR_MTR_HD_KNF_RLY,                    APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_HD_KNF_RLY},//APPACT_ACTITF_PWR_MTR_HD_KNF_RLY
        {APPACT_ACTDVC_PWR_MTR_HD_CNTR_KNF,                           APPACT_SPEC_PWR_MTR_HD_CNTR_KNF_RLY_SetValue,               APPACT_SPEC_PWR_MTR_HD_CNTR_KNF_RLY_GetValue,               APPSIG_SIGNAL_ACT_SET_PWR_MTR_HD_CNTR_KNF_RLY,               APPSIG_SIGNAL_ACT_GET_PWR_MTR_HD_CNTR_KNF_RLY,               APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_HD_CNTR_KNF_RLY},//APPACT_ACTITF_PWR_MTR_HD_CNTR_KNF_RLY
        {APPACT_ACTDVC_PWR_MTR_HD_HOLD,                               APPACT_SPEC_PWR_MTR_HD_HOLD_RLY_SetValue,                   APPACT_SPEC_PWR_MTR_HD_HOLD_RLY_GetValue,                   APPSIG_SIGNAL_ACT_SET_PWR_MTR_HD_HOLD_RLY,                   APPSIG_SIGNAL_ACT_GET_PWR_MTR_HD_HOLD_RLY,                   APPSIG_SIGNAL_ACT_CTRL_PWR_MTR_HD_HOLD_RLY},//APPACT_ACTITF_PWR_MTR_HD_HOLD_RLY
    };

    ///@brief Variable for system Actuators Device Ope Mngmt
    const t_sAPPACT_ActDvcOpeCfg c_AppAct_ActDvcOpeCfg_as[APPACT_ACTDVC_NB] = {
        {APPSYS_OPT_ID_ACT_MTR_XL,                                    APPACT_SPEC_MTR_XL_SetCfg},                                    // APPACT_ACTDVC_MTR_XL
        {APPSYS_OPT_ID_ACT_MTR_XR,                                    APPACT_SPEC_MTR_XR_SetCfg},                                    // APPACT_ACTDVC_MTR_XR
        {APPSYS_OPT_ID_ACT_MTR_Y,                                     APPACT_SPEC_MTR_Y_SetCfg},                                     // APPACT_ACTDVC_MTR_Y
        {APPSYS_OPT_ID_ACT_MTR_Z,                                     APPACT_SPEC_MTR_Z_SetCfg},                                     // APPACT_ACTDVC_MTR_Z
        {APPSYS_OPT_ID_ACT_MTR_WHL_AV_L,                              APPACT_SPEC_MTR_WHL_AV_L_SetCfg},                              // APPACT_ACTDVC_MTR_WHL_AV_L
        {APPSYS_OPT_ID_ACT_MTR_WHL_AV_R,                              APPACT_SPEC_MTR_WHL_AV_R_SetCfg},                              // APPACT_ACTDVC_MTR_WHL_AV_R
        {APPSYS_OPT_ID_ACT_MTR_HD_KNF,                                APPACT_SPEC_MTR_HD_KNF_SetCfg},                                // APPACT_ACTDVC_MTR_HD_KNF
        {APPSYS_OPT_ID_ACT_MTR_HD_CNTR_KNF,                           APPACT_SPEC_MTR_HD_CNTR_KNF_SetCfg},                           // APPACT_ACTDVC_MTR_HD_CNTR_KNF
        {APPSYS_OPT_ID_ACT_MTR_HD_HOLD,                               APPACT_SPEC_MTR_HD_HOLD_SetCfg},                               // APPACT_ACTDVC_MTR_HD_HOLD
        {APPSYS_OPT_ID_ACT_PWR_MTR_XL,                                APPACT_SPEC_PWR_MTR_XL_SetCfg},                                // APPACT_ACTDVC_PWR_MTR_XL
        {APPSYS_OPT_ID_ACT_PWR_MTR_XR,                                APPACT_SPEC_PWR_MTR_XR_SetCfg},                                // APPACT_ACTDVC_PWR_MTR_XR
        {APPSYS_OPT_ID_ACT_PWR_MTR_Y,                                 APPACT_SPEC_PWR_MTR_Y_SetCfg},                                 // APPACT_ACTDVC_PWR_MTR_Y
        {APPSYS_OPT_ID_ACT_PWR_MTR_Z,                                 APPACT_SPEC_PWR_MTR_Z_SetCfg},                                 // APPACT_ACTDVC_PWR_MTR_Z
        {APPSYS_OPT_ID_ACT_PWR_WHL_AV_L,                              APPACT_SPEC_PWR_WHL_AV_L_SetCfg},                              // APPACT_ACTDVC_PWR_WHL_AV_L
        {APPSYS_OPT_ID_ACT_PWR_WHL_AV_R,                              APPACT_SPEC_PWR_WHL_AV_R_SetCfg},                              // APPACT_ACTDVC_PWR_WHL_AV_R
        {APPSYS_OPT_ID_ACT_PWR_MTR_HD_KNF,                            APPACT_SPEC_PWR_MTR_HD_KNF_SetCfg},                            // APPACT_ACTDVC_PWR_MTR_HD_KNF
        {APPSYS_OPT_ID_ACT_PWR_MTR_HD_CNTR_KNF,                       APPACT_SPEC_PWR_MTR_HD_CNTR_KNF_SetCfg},                       // APPACT_ACTDVC_PWR_MTR_HD_CNTR_KNF
        {APPSYS_OPT_ID_ACT_PWR_MTR_HD_HOLD,                           APPACT_SPEC_PWR_MTR_HD_HOLD_SetCfg},                           // APPACT_ACTDVC_PWR_MTR_HD_HOLD
    };

    /**< Variable for System Actuators drivers functions*/
    const t_sAPPACT_SysDrvFunc c_AppAct_SysDrvCfg_as[APPACT_DRV_NB] = {
        {(t_cbAppAct_DrvInit *)CL42T_Init,                    (t_cbAppAct_DrvCyclic *)CL42T_Cyclic,TRUE}                                // APPACT_DRV_CL42T
    };

    /* CAUTION : Automatic generated code section for Variable: End */

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APPACT_CONFIGPRIVATE_H_INCLUDED           
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
