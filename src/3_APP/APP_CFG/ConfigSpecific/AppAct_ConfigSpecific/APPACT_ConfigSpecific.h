/*********************************************************************
 * @file        TemplateName.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
#ifndef APPACT_CONFIG_SPECIFIC
#define APPACT_CONFIG_SPECIFIC






    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "CL42T/Src/CL42T.h"
    #include "TypeCommon.h"
    #include "APP_CFG/ConfigFiles/APPACT_ConfigPublic.h"
    #include "APP_CTRL/APP_SDM/Src/APP_SDM.h"
    #include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************
	/* CAUTION : Automatic generated code section for Enum: Start */

	/* CAUTION : Automatic generated code section for Enum: End */
	//-----------------------------ENUM TYPES-----------------------------//


	//-----------------------------STRUCT TYPES---------------------------//
    ///@brief structure to send the iteration for CL42T (required)
    typedef struct 
    {
        t_sint32 nbPulses_s32;              //---- NbPulse to send ----//
        t_uint32 frequency_f32;             //---- speed of pulses in Hz ----//
        t_uint32 trigTimer_u32;             //---- Trigger time, when to send pulse to hardware driver ----//
        t_uint32 lastCmdSet_u32;             //---- All Cmd has to reveived from APPACT in a interval of APPSYS_ELAPSED_TIME_CYCLIC / 2 ----//
        t_bool isPulsesRcv_b;               //---- Flag pulse receive ----//
        t_bool isFreqRcv_b;                 //---- Flag speed receive ----//
        t_bool isTrigTimerRcv_b;            //---- Flag trigTime receive ----//
    } t_sAPPACT_SPEC_CL42T_ShadowCmd;
	/* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
	//-----------------------------TYPEDEF TYPES---------------------------//
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************


    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    /**
     * @brief This function handle the reception of signals from APPSIG
     * ----------------------------------------------------------------------------
     * @param[in] f_signal_e : signal ID
     * @param[in] f_sigVal_f32 :signl; value
     * ----------------------------------------------------------------------------
     * @return 
     */
    t_eReturnCode APPACT_SPEC_CL42T_SPD_SetValue(   t_float32 f_SigValue_pf32, 
                                                    t_eCL42T_MotorId f_MotorId_e,
                                                    t_sint32 f_dirPositive_s32,
                                                    t_eAPPSIG_Signal f_sigMtrRelay_e,
                                                    t_sAPPACT_SPEC_CL42T_ShadowCmd * f_shadowCmd_ps);
    /**
     * @brief This function handle the reception of signals from APPSIG
     * ----------------------------------------------------------------------------
     * @param[in] f_signal_e : signal ID
     * @param[in] f_sigVal_f32 :signl; value
     * ----------------------------------------------------------------------------
     * @return 
     */
    t_eReturnCode APPACT_SPEC_CL42T_TRG_SetValue(  t_float32 f_SigValue_pf32, 
                                                    t_eCL42T_MotorId f_MotorId_e,
                                                    t_sint32 f_dirPositive_s32,
                                                    t_eAPPSIG_Signal f_sigMtrRelay_e,
                                                    t_sAPPACT_SPEC_CL42T_ShadowCmd * f_shadowCmd_ps);
    /**
     * @brief This function handle the reception of signals from APPSIG
     * ----------------------------------------------------------------------------
     * @param[in] f_signal_e : signal ID
     * @param[in] f_sigVal_f32 :signl; value
     * ----------------------------------------------------------------------------
     * @return 
     */
    t_eReturnCode APPACT_SPEC_CL42T_SPD_GetValue(   t_float32 * f_SigValue_pf32,
                                                    t_eAPPSIG_Signal f_sigMtrRelay_e,
                                                    t_eCL42T_MotorId f_MotorId_e);
    /**
     * @brief This function handle the reception of signals from APPSIG
     * ----------------------------------------------------------------------------
     * @param[in] f_signal_e : signal ID
     * @param[in] f_sigVal_f32 :signl; value
     * ----------------------------------------------------------------------------
     * @return 
     */
    t_eReturnCode APPACT_SPEC_CL42T_PLS_SetValue( t_float32 f_SigValue_pf32, 
                                                    t_eCL42T_MotorId f_MotorId_e,
                                                    t_sint32 f_dirPositive_s32,
                                                    t_eAPPSIG_Signal f_sigMtrRelay_e,
                                                    t_sAPPACT_SPEC_CL42T_ShadowCmd * f_shadowCmd_ps);
    /**
     * @brief This function handle the reception of signals from APPSIG
     * ----------------------------------------------------------------------------
     * @param[in] f_signal_e : signal ID
     * @param[in] f_sigVal_f32 :signl; value
     * ----------------------------------------------------------------------------
     * @return 
     */
    void APPACT_SPEC_CL42T_Diagnostic(  t_eCL42T_DiagError f_defaultInfo_e,
                                        t_eCL42T_MotorId f_MotorId_e,
                                        t_eAPPSDM_DiagnosticItem f_DiagITem_e);
#endif            
//************************************************************************************
// End of File
//************************************************************************************

/**
 *
 *	@brief
 *	@note   
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
