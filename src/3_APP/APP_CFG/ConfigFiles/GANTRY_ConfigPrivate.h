/**
 * @file        CL42T_ConfigPrivate.h
 * @brief       Driver Module for Driver CL42T.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        21/01/2025
 * @version     1.0
 */
  
#ifndef GANTRY_CONFIGPRIVATE_H_INCLUDED
#define GANTRY_CONFIGPRIVATE_H_INCLUDED

    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
    #include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
    #include "APP_CTRL/APP_SNS/Src/APP_SNS.h"
    #include "APP_CTRL/APP_ACT/Src/APP_ACT.h"
    #include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
    #include "APP_LGC/Src/APP_LGC.h"

    #include "./GANTRY_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    ///@brief Fifo Buffer len define
    #define GTRY_CMD_POS_RCV_BUFFER_LEN         ((t_uint8)50)
    #define GTRY_CMD_ITER_BUFFER_LEN            ((t_uint8)50)
    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//
    ///@brief Axe Calibration List
    typedef enum 
    {
        GTRY_CALIB_ID_AXE_X = 0,       //---- Calibration of axe X ----//
        GTRY_CALIB_ID_AXE_Y,           //---- Calibration of axe Y ----//
        GTRY_CALIB_ID_AXE_Z,           //---- Calibration of axe Z ----//
    } t_eGTRY_CalibAxeId;

    ///@brief Calibration Type List 
    typedef enum 
    {
        GTRY_CALIB_TYPE_ASYNC = 0,      //---- calibration will be made in async mode, axe X then Y and Z ----//
        GTRY_CALIB_TYPE_SYNC,           //---- calibration will be made in sync mode Axe X,Y,Z at the same time ----//
    } t_eGTRY_CalibType;

    ///@brief Command User Type
    typedef enum 
    {
        GTRY_CMD_TYPE_ID_CARTESIAN = 0,     //---- Command Type Identifier for Carthesian coordinate ---//
        GTRY_CMD_TYPE_ID_SPHERIC,           //---- Command Type Identifier for Spheric coordinate ----//
        GTRY_CMD_TYPE_ID_STEPS,             //---- Command Type Identifier for steps for each axes ----//

        GTRY_CMD_TYPE_ID_NB,
    } t_eGTRY_CmdTypeId;

    ///@brief mapping between signals from appsig and cmd signal
    typedef enum 
    {
        GTRY_CMD_SIG_POS_X = 0,
        GTRY_CMD_SIG_POS_Y,
        GTRY_CMD_SIG_POS_Z,

        GTRY_CMD_SIG_POS_RAYON,
        GTRY_CMD_SIG_POS_THETHA,
        GTRY_CMD_SIG_POS_PHI,

        GTRY_CMD_SIG_STEP_X,
        GTRY_CMD_SIG_STEP_Y,
        GTRY_CMD_SIG_STEP_Z,
        GTRY_CMD_SIG_DIR_X,
        GTRY_CMD_SIG_DIR_Y,
        GTRY_CMD_SIG_DIR_Z,

        GTRY_CMD_SIG_NB
    } t_eGTRY_CmdSignals;
    //---------------------------STRUCTURE TYPES--------------------------//
    ///@brief Mapping structure beetween gantry and application
    typedef struct 
    {
        t_eAPPACT_ActInterface actIfMtrSts_e;       //---- Pulse/State actuators interface ----//
        t_eAPPACT_ActInterface actIfSpeed_e;        //---- Speed actuator interface -----//
        t_eAPPSNS_SnsInterface snsIfEcdr_e;         //---- Encoder sensors interface ----//
        t_eAPPLGC_SrvList lgcSrvID_e;               //---- Logic service Id ----//
        t_eAPPSYS_SysOptionList sysOptEcdr_e;       //---- System encoder option ----//
        t_eAPPSPM_ItemPrm prmPulsePerMm_e;          //---- Parameter to know the pulse per millimeter ----//
        t_eAPPSPM_ItemPrm prmAxeLenght_e;           //---- Parameter for axe lenght -----//  
    } t_sGTRY_AxeAppCfg;

    ///@brief Structure to gather user command from AppSig 
    typedef struct 
    {
        t_float32 value_f32;
        t_bool isRcv_b;
        t_uint32 timeStamp_u32;
    } t_sGTRY_cmdSigInfo;
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
   
    //----------------------------- TYPES---------------------------//
    /**
     * @brief Function typedef to build command from cartesian pos, spheric pos etc 
     * ----------------------------------------------------------------------------
     * @param[in] f_value : value to compute
     * ----------------------------------------------------------------------------
     * @return @ref t_eReturnCode
     */
    typedef t_eReturnCode (*t_cbGTRY_BuildCmdFunc)(t_float32 f_value);

    /// @brief Sig Cmd Group to handle signal command
    typedef struct
    {
        const t_eAPPSIG_Signal *signal_pe;    //---- pointor to a list of signals for the group -----//
        t_uint8 nbsignals_u8;                   //---- Number of signal for the group -----//
        t_uint32 timeoutMs_u32;                 //---- Time out to set a entire command -----//
        t_cbGTRY_BuildCmdFunc buildFunc_pf;     //---- Function to build the cmd ----//
    } t_sGTRY_SigGroup;
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    ///@brief variable for application mapping
    const t_sGTRY_AxeAppCfg c_GTRY_AppAxesCfg_as[GTRY_AXE_HANDLE_NB];

    ///@brief variable for signal group
    static const t_eAPPSIG_Signal c_GTRY_cartesianSigs_ae[] = {};
    static const t_eAPPSIG_Signal c_GTRY_SphericSigs_ae[] = {};
    static const t_eAPPSIG_Signal c_GTRY_StepdirSigs_ae[] = {};

    ///@brief Information for Signals Groups 
    const t_sGTRY_SigGroup c_GTRY_SigGroupInfo_as[GTRY_CMD_TYPE_ID_NB] = {
    //    signals from APPSIG        nbSignals    Timeout       function to build cmd
        {c_GTRY_cartesianSigs_ae,       3,          100,        NULL_FUNCTION},
        {c_GTRY_SphericSigs_ae,         3,          100,        NULL_FUNCTION},
        {c_GTRY_StepdirSigs_ae,         3,          100,        NULL_FUNCTION},
    }
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    
#endif // GANTRY_CONFIGPRIVATE_H_INCLUDED
//************************************************************************************
// End of File
//************************************************************************************

/**
 *	@brief
 *	@note   
 *
 *
 *	@param[in] 
 *	@param[in]
 *	 
 *
 *
 */
