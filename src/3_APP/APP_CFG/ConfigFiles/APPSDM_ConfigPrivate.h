/*********************************************************************
 * @file        APPACT_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPSDM_CONFIGPRIVATE_H_INCLUDED
#define APPSDM_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APPSDM_ConfigPublic.h"
    #include "3_APP/APP_CTRL/APP_SIG/Src/APP_SIG.h"
    #include "APP_CFG/ConfigSpecific/APPSDM_ConfigSpecific.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define APPSDM_MAX_DIAG_ITEM_MONITORING ((t_uint8)10)

    ///@brief activate deactivate diagnostic managment 
    #define APPSDM_DIAG_MNGMT_STATUS        ((t_bool)TRUE)
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
	//-----------------------------ENUM TYPES-----------------------------//
    

	/* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
	//-----------------------------STRUCT TYPES---------------------------//
    typedef struct
    {
        t_eAPPSIG_Signal itemID_e;         //----- Signal for Item ID ----//
        t_eAPPSIG_Signal diagState_e;      //----- Signal for Item State ----//
        t_eAPPSIG_Signal debugInfo1;       //----- Signal for Item Info 1 ----//
        t_eAPPSIG_Signal debugInfo2;       //----- Signal for Item Info 2 ----//
    } t_sAPPSDM_DebugSignal;
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
	//-----------------------------TYPEDEF TYPES---------------------------//
	
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
	
    /**
    *
    *	@brief      Function to inhibit actuators or sysfunction
    *
    *
    * @retval RC_OK                             @ref RC_OK
    *
    */
    typedef void (t_cbAPPSDM_AppliedDiagStrategy)(t_eAPPSDM_DiagStratOpe f_diagStratOpe_e);
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    /**
    * @brief Diagnostic Item Configuration
    */
    t_cbAPPSDM_AppliedDiagStrategy * c_AppSdm_DiagStragies_apf[APPSDM_DIAG_STRAT_NB]= {
        APPSDM_SPEC_DiagStrat_GANTRY_AXES_OFF,
        APPSDM_SPEC_DiagStrat_GANTRY_AXE_X_OFF,
        APPSDM_SPEC_DiagStrat_GANTRY_AXE_Y_OFF,
        APPSDM_SPEC_DiagStrat_GANTRY_AXE_Z_OFF,
        APPSDM_SPEC_DiagStrat_HEAD_CUTTER_OFF,
        APPSDM_SPEC_DiagStrat_MOTION_OFF,
    };

    /**
    * @brief Diagnostic Item Configuration
    */
    t_sAPPSM_DiagItemCfg c_AppSdm_DiagItemCfg_as[APPSDM_DIAG_ITEM_NB] ={
        // DebuncerCounter              Unactive Item Delay          NotifyUser                     Log Error                      Applied Startegy
        {(t_uint16)0,                  (t_uint32)0xFFFFFFFF,         (t_bool)True,                 (t_bool)True,                 APPSDM_DIAG_STRAT_NONE},        // FMK_CFG_ERROR
        {(t_uint16)20,                 (t_uint32)3000,               (t_bool)True,                 (t_bool)True,                 APPSDM_DIAG_STRAT_NONE},        // FMK_CPU_TEMP_OUT_OF_RANGE
        {(t_uint16)20,                 (t_uint32)3000,               (t_bool)True,                 (t_bool)True,                 APPSDM_DIAG_STRAT_NONE},        // FMK_SUPPLY_VOLTAGE_OUT_OF_RANGE
        {(t_uint16)5,                  (t_uint32)5000,               (t_bool)True,                 (t_bool)True,                 APPSDM_DIAG_STRAT_NONE},        // FMK_FDCAN_OPE_ERROR
        {(t_uint16)5,                  (t_uint32)5000,               (t_bool)True,                 (t_bool)True,                 APPSDM_DIAG_STRAT_NONE},        // FMK_SRL_OPE_ERROR
        {(t_uint16)5,                  (t_uint32)5000,               (t_bool)True,                 (t_bool)True,                 APPSDM_DIAG_STRAT_NONE},        // FMK_HRT_OPE_ERROR
        {(t_uint16)5,                  (t_uint32)5000,               (t_bool)True,                 (t_bool)True,                 APPSDM_DIAG_STRAT_NONE},        // FMK_TIM_OPE_ERROR
        {(t_uint16)5,                  (t_uint32)5000,               (t_bool)True,                 (t_bool)True,                 APPSDM_DIAG_STRAT_NONE},        // FMK_CDA_OPE_ERROR
        {(t_uint16)5,                  (t_uint32)5000,               (t_bool)True,                 (t_bool)True,                 APPSDM_DIAG_STRAT_NONE},        // FMK_CPU_OPE_ERROR
        {(t_uint16)5,                  (t_uint32)100,                (t_bool)False,                (t_bool)False,                APPSDM_DIAG_STRAT_NONE},        // APP_CYCLIC_TIMEOUT
        {(t_uint16)5,                  (t_uint32)100,                (t_bool)False,                (t_bool)False,                APPSDM_DIAG_STRAT_NONE},        // APP_FASTTASK_TIMEOUT
        {(t_uint16)5,                  (t_uint32)200,                (t_bool)False,                (t_bool)True,                 APPSDM_DIAG_STRAT_NONE},        // UDS_COM_ERROR
        {(t_uint16)5,                  (t_uint32)65000,              (t_bool)False,                (t_bool)True,                 APPSDM_DIAG_STRAT_GANTRY_AXES_OFF},// APPSYS_ECU_POS_ERROR
        {(t_uint16)5,                  (t_uint32)100,                (t_bool)False,                (t_bool)True,                 APPSDM_DIAG_STRAT_NONE},        // APPSIG_MSG_TIMEOUT
        {(t_uint16)0,                  (t_uint32)500,                (t_bool)True,                 (t_bool)True,                 APPSDM_DIAG_STRAT_GANTRY_AXES_OFF},// LGC_GTRY_OPE_ERROR
        {(t_uint16)0,                  (t_uint32)500,                (t_bool)True,                 (t_bool)True,                 APPSDM_DIAG_STRAT_GANTRY_AXE_X_OFF},// LGC_GTRY_X_OPE_ERROR
        {(t_uint16)0,                  (t_uint32)500,                (t_bool)True,                 (t_bool)True,                 APPSDM_DIAG_STRAT_GANTRY_AXE_Y_OFF},// LGC_GTRY_Y_OPE_ERROR
        {(t_uint16)0,                  (t_uint32)500,                (t_bool)True,                 (t_bool)True,                 APPSDM_DIAG_STRAT_GANTRY_AXE_Z_OFF},// LGC_GTRY_Z_OPE_ERROR
    };

    /* CAUTION : Automatic generated code section for Variable: End */

    const t_sAPPSDM_DebugSignal c_DebugSignals_as[APPSDM_MAX_DIAG_ITEM_MONITORING] = {
        {APPSIG_SIGNAL_SDM_DIAG_ITEM_1, APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_1, APPSIG_SIGNAL_SDM_DIAG_ITEM_1_INFO_1, APPSIG_SIGNAL_SDM_DIAG_ITEM_1_INFO_2},
        {APPSIG_SIGNAL_SDM_DIAG_ITEM_2, APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_2, APPSIG_SIGNAL_SDM_DIAG_ITEM_2_INFO_1, APPSIG_SIGNAL_SDM_DIAG_ITEM_2_INFO_2},
        {APPSIG_SIGNAL_SDM_DIAG_ITEM_3, APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_3, APPSIG_SIGNAL_SDM_DIAG_ITEM_3_INFO_1, APPSIG_SIGNAL_SDM_DIAG_ITEM_3_INFO_2},
        {APPSIG_SIGNAL_SDM_DIAG_ITEM_4, APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_4, APPSIG_SIGNAL_SDM_DIAG_ITEM_4_INFO_1, APPSIG_SIGNAL_SDM_DIAG_ITEM_4_INFO_2},
        {APPSIG_SIGNAL_SDM_DIAG_ITEM_5, APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_5, APPSIG_SIGNAL_SDM_DIAG_ITEM_5_INFO_1, APPSIG_SIGNAL_SDM_DIAG_ITEM_5_INFO_2},
        {APPSIG_SIGNAL_SDM_DIAG_ITEM_6, APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_6, APPSIG_SIGNAL_SDM_DIAG_ITEM_6_INFO_1, APPSIG_SIGNAL_SDM_DIAG_ITEM_6_INFO_2},
        {APPSIG_SIGNAL_SDM_DIAG_ITEM_7, APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_7, APPSIG_SIGNAL_SDM_DIAG_ITEM_7_INFO_1, APPSIG_SIGNAL_SDM_DIAG_ITEM_7_INFO_2},
        {APPSIG_SIGNAL_SDM_DIAG_ITEM_8, APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_8, APPSIG_SIGNAL_SDM_DIAG_ITEM_8_INFO_1, APPSIG_SIGNAL_SDM_DIAG_ITEM_8_INFO_2},
        {APPSIG_SIGNAL_SDM_DIAG_ITEM_9, APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_9, APPSIG_SIGNAL_SDM_DIAG_ITEM_9_INFO_1, APPSIG_SIGNAL_SDM_DIAG_ITEM_9_INFO_2},
        {APPSIG_SIGNAL_SDM_DIAG_ITEM_10, APPSIG_SIGNAL_SDM_DIAG_ITEM_STATE_10, APPSIG_SIGNAL_SDM_DIAG_ITEM_10_INFO_1, APPSIG_SIGNAL_SDM_DIAG_ITEM_10_INFO_2},
    };
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
