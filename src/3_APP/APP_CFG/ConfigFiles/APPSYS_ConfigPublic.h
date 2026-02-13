/*********************************************************************
 * @file        APPSYS_ConfigPublic.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPSYS_CONFIGPUBLIC_H_INCLUDED
#define APPSYS_CONFIGPUBLIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "string.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define BASE_PATH "src\\"
    #define SHORTEN_PATH(path) (strstr(path, BASE_PATH) ? strstr(path, BASE_PATH) : path)

    ///@brief Optional Module
    #define APPSYS_MODULE_FMKHRT_ENABLE
    #define APPSYS_MODULE_FMKCAN_ENABLE
    #define APPSYS_MODULE_FMKSRL_ENABLE
    #define APPSYS_MODULE_APPLGC_ENABLE
    #define APPSYS_MODULE_APP_SPM_ENABLE

    #define APPSYS_ELAPSED_TIME_CYCLIC ((t_uint8)40)     /**< Elapsed time (in ms) between cyclic function call*/
    #define APPSYS_ITLINE_FASTTASK FMKTIM_INTERRUPT_LINE_EVNT_1 /**< Timer Line use for FastTask */
    #define APPSYS_ELASPED_TIME_FASTTASK ((t_uint32)5)  /**< Fast Task every 5 ms */
    

    #define APPSYS_MACHINE_ID           (APPSYS_MACHINE_POC_1)
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    
    typedef enum 
    {
        APPSYS_ECU_POS_GTRY = 0,
        APPSYS_ECU_POS_GTRY_HEAD,
        APPSYS_ECU_POS_MOTION,

        APPSYS_ECU_POS_NB
    } t_eAPPSYS_EcuPos;

    /* CAUTION : Automatic generated code section for Enum: Start */
    typedef enum
    {
        APPSYS_MACHINE_POC_1 = 0,
        APPSYS_MACHINE_POC_2,
    
        APPSYS_MACHINE_NB,
    } t_eAPPSYS_MachineList;

    /**
    * @brief Enum Option list for  ACT_MTR_Z.
    */
    typedef enum
    {
        APPSYS_OPT_ACT_MTR_Z_UNUSED = 0,
        APPSYS_OPT_ACT_MTR_Z_CL42T,
    
        APPSYS_OPT_ACT_MTR_Z_NB,
    } t_eAPPSYS_OptActMtrZ;

    /**
    * @brief Enum Option list for  ACT_MTR_Y.
    */
    typedef enum
    {
        APPSYS_OPT_ACT_MTR_Y_UNUSED = 0,
        APPSYS_OPT_ACT_MTR_Y_CL42T,
    
        APPSYS_OPT_ACT_MTR_Y_NB,
    } t_eAPPSYS_OptActMtrY;

    /**
    * @brief Enum Option list for  ACT_MTR_XR.
    */
    typedef enum
    {
        APPSYS_OPT_ACT_MTR_XR_UNUSED = 0,
        APPSYS_OPT_ACT_MTR_XR_CL42T,
    
        APPSYS_OPT_ACT_MTR_XR_NB,
    } t_eAPPSYS_OptActMtrXr;

    /**
    * @brief Enum Option list for  ACT_MTR_XL.
    */
    typedef enum
    {
        APPSYS_OPT_ACT_MTR_XL_UNUSED = 0,
        APPSYS_OPT_ACT_MTR_XL_CL42T,
    
        APPSYS_OPT_ACT_MTR_XL_NB,
    } t_eAPPSYS_OptActMtrXl;

    /**
    * @brief Enum Option list for  SNS_ECDR_Z.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_ECDR_Z_UNUSED = 0,
        APPSYS_OPT_SNS_ECDR_Z_NEMA17,
        APPSYS_OPT_SNS_ECDR_Z_EMS22A,
    
        APPSYS_OPT_SNS_ECDR_Z_NB,
    } t_eAPPSYS_OptSnsEcdrZ;

    /**
    * @brief Enum Option list for  SNS_ECDR_Y.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_ECDR_Y_UNUSED = 0,
        APPSYS_OPT_SNS_ECDR_Y_NEMA17,
        APPSYS_OPT_SNS_ECDR_Y_EMS22A,
    
        APPSYS_OPT_SNS_ECDR_Y_NB,
    } t_eAPPSYS_OptSnsEcdrY;

    /**
    * @brief Enum Option list for  SNS_ECDR_XR.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_ECDR_XR_UNUSED = 0,
        APPSYS_OPT_SNS_ECDR_XR_NEMA17,
        APPSYS_OPT_SNS_ECDR_XR_EMS22A,
    
        APPSYS_OPT_SNS_ECDR_XR_NB,
    } t_eAPPSYS_OptSnsEcdrXr;

    /**
    * @brief Enum Option list for  SNS_ECDR_XL.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_ECDR_XL_UNUSED = 0,
        APPSYS_OPT_SNS_ECDR_XL_NEMA17,
        APPSYS_OPT_SNS_ECDR_XL_EMS22A,
    
        APPSYS_OPT_SNS_ECDR_XL_NB,
    } t_eAPPSYS_OptSnsEcdrXl;

    /**
    * @brief System Option List.
    */
    typedef enum
    {
        APPSYS_OPT_ID_SNS_ECDR_XL = 0,
        APPSYS_OPT_ID_SNS_ECDR_XR,
        APPSYS_OPT_ID_SNS_ECDR_Y,
        APPSYS_OPT_ID_SNS_ECDR_Z,
        APPSYS_OPT_ID_ACT_MTR_XL,
        APPSYS_OPT_ID_ACT_MTR_XR,
        APPSYS_OPT_ID_ACT_MTR_Y,
        APPSYS_OPT_ID_ACT_MTR_Z,
    
        APPSYS_OPT_ID_NB,
    } t_eAPPSYS_SysOptionList;

    /* CAUTION : Automatic generated code section for Enum: End */

	//-----------------------------ENUM TYPES-----------------------------//
    // Flag automatic generate code
    /**< enum for module list */
    typedef enum
    {
        APPSYS_MODULE_FMK_CPU = 0,
        APPSYS_MODULE_FMK_TIM,
        APPSYS_MODULE_FMK_HRT,
        APPSYS_MODULE_FMK_CDA,
        APPSYS_MODULE_FMK_IO,
#ifdef APPSYS_MODULE_FMKCAN_ENABLE
        APPSYS_MODULE_FMK_CAN,
#endif // APPSYS_MODULE_FMKCAN_ENABLE

#ifdef APPSYS_MODULE_FMKSRL_ENABLE
        APPSYS_MODULE_FMK_SERIAL,
#endif // APPSYS_MODULE_FMKSRL_ENABLE
        APPSYS_MODULE_APP_SDM,
        APPSYS_MODULE_APP_SPM,
        APPSYS_MODULE_APP_SIG,
        APPSYS_MODULE_APP_SNS,
        APPSYS_MODULE_APP_ACT,
        APPSYS_MODULE_APP_LGC,

        APPSYS_MODULE_NB
    } t_eAppSys_ModuleList;

	/* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
	//-----------------------------STRUCT TYPES---------------------------//
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

#endif // APPSYS_CONFIGPUBLIC_H_INCLUDED           
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
