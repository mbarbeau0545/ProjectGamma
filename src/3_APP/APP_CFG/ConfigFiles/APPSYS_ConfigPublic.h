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
        APPSYS_MACHINE_GTRY = 0,
        APPSYS_MACHINE_HD,
        APPSYS_MACHINE_MOTION,
    
        APPSYS_MACHINE_NB,
    } t_eAPPSYS_MachineList;

    /**
    * @brief Enum Option list for  ACT_MTR_HD_HOLD.
    */
    typedef enum
    {
        APPSYS_OPT_ACT_MTR_HD_HOLD_UNUSED = 0,
        APPSYS_OPT_ACT_MTR_HD_HOLD_CL42T,
        APPSYS_OPT_ACT_MTR_HD_HOLD_APPSIG,
    
        APPSYS_OPT_ACT_MTR_HD_HOLD_NB,
    } t_eAPPSYS_OptActMtrHdHold;

    /**
    * @brief Enum Option list for  ACT_MTR_HD_CNTR_KNF.
    */
    typedef enum
    {
        APPSYS_OPT_ACT_MTR_HD_CNTR_KNF_UNUSED = 0,
        APPSYS_OPT_ACT_MTR_HD_CNTR_KNF_CL42T,
        APPSYS_OPT_ACT_MTR_HD_CNTR_KNF_APPSIG,
    
        APPSYS_OPT_ACT_MTR_HD_CNTR_KNF_NB,
    } t_eAPPSYS_OptActMtrHdCntrKnf;

    /**
    * @brief Enum Option list for  ACT_MTR_HD_KNF.
    */
    typedef enum
    {
        APPSYS_OPT_ACT_MTR_HD_KNF_UNUSED = 0,
        APPSYS_OPT_ACT_MTR_HD_KNF_CL42T,
        APPSYS_OPT_ACT_MTR_HD_KNF_APPSIG,
    
        APPSYS_OPT_ACT_MTR_HD_KNF_NB,
    } t_eAPPSYS_OptActMtrHdKnf;

    /**
    * @brief Enum Option list for  ACT_MTR_WHL_AV_R.
    */
    typedef enum
    {
        APPSYS_OPT_ACT_MTR_WHL_AV_R_UNUSED = 0,
        APPSYS_OPT_ACT_MTR_WHL_AV_R_CL42T,
        APPSYS_OPT_ACT_MTR_WHL_AV_R_APPSIG,
    
        APPSYS_OPT_ACT_MTR_WHL_AV_R_NB,
    } t_eAPPSYS_OptActMtrWhlAvR;

    /**
    * @brief Enum Option list for  ACT_MTR_WHL_AV_L.
    */
    typedef enum
    {
        APPSYS_OPT_ACT_MTR_WHL_AV_L_UNUSED = 0,
        APPSYS_OPT_ACT_MTR_WHL_AV_L_CL42T,
        APPSYS_OPT_ACT_MTR_WHL_AV_L_APPSIG,
    
        APPSYS_OPT_ACT_MTR_WHL_AV_L_NB,
    } t_eAPPSYS_OptActMtrWhlAvL;

    /**
    * @brief Enum Option list for  ACT_MTR_Z.
    */
    typedef enum
    {
        APPSYS_OPT_ACT_MTR_Z_UNUSED = 0,
        APPSYS_OPT_ACT_MTR_Z_CL42T,
        APPSYS_OPT_ACT_MTR_Z_APPSIG,
    
        APPSYS_OPT_ACT_MTR_Z_NB,
    } t_eAPPSYS_OptActMtrZ;

    /**
    * @brief Enum Option list for  ACT_MTR_Y.
    */
    typedef enum
    {
        APPSYS_OPT_ACT_MTR_Y_UNUSED = 0,
        APPSYS_OPT_ACT_MTR_Y_CL42T,
        APPSYS_OPT_ACT_MTR_Y_APPSIG,
    
        APPSYS_OPT_ACT_MTR_Y_NB,
    } t_eAPPSYS_OptActMtrY;

    /**
    * @brief Enum Option list for  ACT_MTR_XR.
    */
    typedef enum
    {
        APPSYS_OPT_ACT_MTR_XR_UNUSED = 0,
        APPSYS_OPT_ACT_MTR_XR_CL42T,
        APPSYS_OPT_ACT_MTR_XR_APPSIG,
    
        APPSYS_OPT_ACT_MTR_XR_NB,
    } t_eAPPSYS_OptActMtrXr;

    /**
    * @brief Enum Option list for  ACT_MTR_XL.
    */
    typedef enum
    {
        APPSYS_OPT_ACT_MTR_XL_UNUSED = 0,
        APPSYS_OPT_ACT_MTR_XL_CL42T,
        APPSYS_OPT_ACT_MTR_XL_APPSIG,
    
        APPSYS_OPT_ACT_MTR_XL_NB,
    } t_eAPPSYS_OptActMtrXl;

    /**
    * @brief Enum Option list for  SNS_TRQ_MTR_HD_HOLD.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_TRQ_MTR_HD_HOLD_UNUSED = 0,
        APPSYS_OPT_SNS_TRQ_MTR_HD_HOLD_ACS716,
        APPSYS_OPT_SNS_TRQ_MTR_HD_HOLD_APPSIG,
    
        APPSYS_OPT_SNS_TRQ_MTR_HD_HOLD_NB,
    } t_eAPPSYS_OptSnsTrqMtrHdHold;

    /**
    * @brief Enum Option list for  SNS_TRQ_MTR_CNTR_KNF.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_TRQ_MTR_CNTR_KNF_UNUSED = 0,
        APPSYS_OPT_SNS_TRQ_MTR_CNTR_KNF_ACS716,
        APPSYS_OPT_SNS_TRQ_MTR_CNTR_KNF_APPSIG,
    
        APPSYS_OPT_SNS_TRQ_MTR_CNTR_KNF_NB,
    } t_eAPPSYS_OptSnsTrqMtrCntrKnf;

    /**
    * @brief Enum Option list for  SNS_TRQ_MTR_HD_KNF.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_TRQ_MTR_HD_KNF_UNUSED = 0,
        APPSYS_OPT_SNS_TRQ_MTR_HD_KNF_ACS716,
        APPSYS_OPT_SNS_TRQ_MTR_HD_KNF_APPSIG,
    
        APPSYS_OPT_SNS_TRQ_MTR_HD_KNF_NB,
    } t_eAPPSYS_OptSnsTrqMtrHdKnf;

    /**
    * @brief Enum Option list for  SNS_TRQ_MTR_WHL_AV_R.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_TRQ_MTR_WHL_AV_R_UNUSED = 0,
        APPSYS_OPT_SNS_TRQ_MTR_WHL_AV_R_ACS716,
        APPSYS_OPT_SNS_TRQ_MTR_WHL_AV_R_APPSIG,
    
        APPSYS_OPT_SNS_TRQ_MTR_WHL_AV_R_NB,
    } t_eAPPSYS_OptSnsTrqMtrWhlAvR;

    /**
    * @brief Enum Option list for  SNS_TRQ_MTR_WHL_AV_L.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_TRQ_MTR_WHL_AV_L_UNUSED = 0,
        APPSYS_OPT_SNS_TRQ_MTR_WHL_AV_L_ACS716,
        APPSYS_OPT_SNS_TRQ_MTR_WHL_AV_L_APPSIG,
    
        APPSYS_OPT_SNS_TRQ_MTR_WHL_AV_L_NB,
    } t_eAPPSYS_OptSnsTrqMtrWhlAvL;

    /**
    * @brief Enum Option list for  SNS_TRQ_MTR_Z.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_TRQ_MTR_Z_UNUSED = 0,
        APPSYS_OPT_SNS_TRQ_MTR_Z_ACS716,
        APPSYS_OPT_SNS_TRQ_MTR_Z_APPSIG,
    
        APPSYS_OPT_SNS_TRQ_MTR_Z_NB,
    } t_eAPPSYS_OptSnsTrqMtrZ;

    /**
    * @brief Enum Option list for  SNS_TRQ_MTR_Y.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_TRQ_MTR_Y_UNUSED = 0,
        APPSYS_OPT_SNS_TRQ_MTR_Y_ACS716,
        APPSYS_OPT_SNS_TRQ_MTR_Y_APPSIG,
    
        APPSYS_OPT_SNS_TRQ_MTR_Y_NB,
    } t_eAPPSYS_OptSnsTrqMtrY;

    /**
    * @brief Enum Option list for  SNS_TRQ_MTR_XR.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_TRQ_MTR_XR_UNUSED = 0,
        APPSYS_OPT_SNS_TRQ_MTR_XR_ACS716,
        APPSYS_OPT_SNS_TRQ_MTR_XR_APPSIG,
    
        APPSYS_OPT_SNS_TRQ_MTR_XR_NB,
    } t_eAPPSYS_OptSnsTrqMtrXr;

    /**
    * @brief Enum Option list for  SNS_TRQ_MTR_XL.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_TRQ_MTR_XL_UNUSED = 0,
        APPSYS_OPT_SNS_TRQ_MTR_XL_ACS716,
        APPSYS_OPT_SNS_TRQ_MTR_XL_APPSIG,
    
        APPSYS_OPT_SNS_TRQ_MTR_XL_NB,
    } t_eAPPSYS_OptSnsTrqMtrXl;

    /**
    * @brief Enum Option list for  SNS_HD_DWN_RIGHT.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_HD_DWN_RIGHT_UNUSED = 0,
        APPSYS_OPT_SNS_HD_DWN_RIGHT_CAPTEUR_DIST,
        APPSYS_OPT_SNS_HD_DWN_RIGHT_APPSIG,
    
        APPSYS_OPT_SNS_HD_DWN_RIGHT_NB,
    } t_eAPPSYS_OptSnsHdDwnRight;

    /**
    * @brief Enum Option list for  SNS_HD_UP_RIGHT.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_HD_UP_RIGHT_UNUSED = 0,
        APPSYS_OPT_SNS_HD_UP_RIGHT_CAPTEUR_DIST,
        APPSYS_OPT_SNS_HD_UP_RIGHT_APPSIG,
    
        APPSYS_OPT_SNS_HD_UP_RIGHT_NB,
    } t_eAPPSYS_OptSnsHdUpRight;

    /**
    * @brief Enum Option list for  SNS_HD_DWN_LEFT.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_HD_DWN_LEFT_UNUSED = 0,
        APPSYS_OPT_SNS_HD_DWN_LEFT_CAPTEUR_DIST,
        APPSYS_OPT_SNS_HD_DWN_LEFT_APPSIG,
    
        APPSYS_OPT_SNS_HD_DWN_LEFT_NB,
    } t_eAPPSYS_OptSnsHdDwnLeft;

    /**
    * @brief Enum Option list for  SNS_HD_UP_LEFT.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_HD_UP_LEFT_UNUSED = 0,
        APPSYS_OPT_SNS_HD_UP_LEFT_CAPTEUR_DIST,
        APPSYS_OPT_SNS_HD_UP_LEFT_APPSIG,
    
        APPSYS_OPT_SNS_HD_UP_LEFT_NB,
    } t_eAPPSYS_OptSnsHdUpLeft;

    /**
    * @brief Enum Option list for  SNS_ECDR_HD_HOLD.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_ECDR_HD_HOLD_UNUSED = 0,
        APPSYS_OPT_SNS_ECDR_HD_HOLD_NEMA17,
        APPSYS_OPT_SNS_ECDR_HD_HOLD_APPSIG,
    
        APPSYS_OPT_SNS_ECDR_HD_HOLD_NB,
    } t_eAPPSYS_OptSnsEcdrHdHold;

    /**
    * @brief Enum Option list for  SNS_ECDR_HD_CNTR_KNF.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_ECDR_HD_CNTR_KNF_UNUSED = 0,
        APPSYS_OPT_SNS_ECDR_HD_CNTR_KNF_NEMA17,
        APPSYS_OPT_SNS_ECDR_HD_CNTR_KNF_APPSIG,
    
        APPSYS_OPT_SNS_ECDR_HD_CNTR_KNF_NB,
    } t_eAPPSYS_OptSnsEcdrHdCntrKnf;

    /**
    * @brief Enum Option list for  SNS_ECDR_HD_KNF.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_ECDR_HD_KNF_UNUSED = 0,
        APPSYS_OPT_SNS_ECDR_HD_KNF_NEMA17,
        APPSYS_OPT_SNS_ECDR_HD_KNF_APPSIG,
    
        APPSYS_OPT_SNS_ECDR_HD_KNF_NB,
    } t_eAPPSYS_OptSnsEcdrHdKnf;

    /**
    * @brief Enum Option list for  SNS_ECDR_WHL_AV_R.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_ECDR_WHL_AV_R_UNUSED = 0,
        APPSYS_OPT_SNS_ECDR_WHL_AV_R_NEMA17,
        APPSYS_OPT_SNS_ECDR_WHL_AV_R_APPSIG,
    
        APPSYS_OPT_SNS_ECDR_WHL_AV_R_NB,
    } t_eAPPSYS_OptSnsEcdrWhlAvR;

    /**
    * @brief Enum Option list for  SNS_ECDR_WHL_AV_L.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_ECDR_WHL_AV_L_UNUSED = 0,
        APPSYS_OPT_SNS_ECDR_WHL_AV_L_NEMA17,
        APPSYS_OPT_SNS_ECDR_WHL_AV_L_APPSIG,
    
        APPSYS_OPT_SNS_ECDR_WHL_AV_L_NB,
    } t_eAPPSYS_OptSnsEcdrWhlAvL;

    /**
    * @brief Enum Option list for  SNS_ECDR_Z.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_ECDR_Z_UNUSED = 0,
        APPSYS_OPT_SNS_ECDR_Z_NEMA17,
        APPSYS_OPT_SNS_ECDR_Z_APPSIG,
    
        APPSYS_OPT_SNS_ECDR_Z_NB,
    } t_eAPPSYS_OptSnsEcdrZ;

    /**
    * @brief Enum Option list for  SNS_ECDR_Y.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_ECDR_Y_UNUSED = 0,
        APPSYS_OPT_SNS_ECDR_Y_NEMA17,
        APPSYS_OPT_SNS_ECDR_Y_APPSIG,
    
        APPSYS_OPT_SNS_ECDR_Y_NB,
    } t_eAPPSYS_OptSnsEcdrY;

    /**
    * @brief Enum Option list for  SNS_ECDR_XR.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_ECDR_XR_UNUSED = 0,
        APPSYS_OPT_SNS_ECDR_XR_NEMA17,
        APPSYS_OPT_SNS_ECDR_XR_APPSIG,
    
        APPSYS_OPT_SNS_ECDR_XR_NB,
    } t_eAPPSYS_OptSnsEcdrXr;

    /**
    * @brief Enum Option list for  SNS_ECDR_XL.
    */
    typedef enum
    {
        APPSYS_OPT_SNS_ECDR_XL_UNUSED = 0,
        APPSYS_OPT_SNS_ECDR_XL_NEMA17,
        APPSYS_OPT_SNS_ECDR_XL_APPSIG,
    
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
        APPSYS_OPT_ID_SNS_ECDR_WHL_AV_L,
        APPSYS_OPT_ID_SNS_ECDR_WHL_AV_R,
        APPSYS_OPT_ID_SNS_ECDR_HD_KNF,
        APPSYS_OPT_ID_SNS_ECDR_HD_CNTR_KNF,
        APPSYS_OPT_ID_SNS_ECDR_HD_HOLD,
        APPSYS_OPT_ID_SNS_HD_UP_LEFT,
        APPSYS_OPT_ID_SNS_HD_DWN_LEFT,
        APPSYS_OPT_ID_SNS_HD_UP_RIGHT,
        APPSYS_OPT_ID_SNS_HD_DWN_RIGHT,
        APPSYS_OPT_ID_SNS_TRQ_MTR_XL,
        APPSYS_OPT_ID_SNS_TRQ_MTR_XR,
        APPSYS_OPT_ID_SNS_TRQ_MTR_Y,
        APPSYS_OPT_ID_SNS_TRQ_MTR_Z,
        APPSYS_OPT_ID_SNS_TRQ_MTR_WHL_AV_L,
        APPSYS_OPT_ID_SNS_TRQ_MTR_WHL_AV_R,
        APPSYS_OPT_ID_SNS_TRQ_MTR_HD_KNF,
        APPSYS_OPT_ID_SNS_TRQ_MTR_CNTR_KNF,
        APPSYS_OPT_ID_SNS_TRQ_MTR_HD_HOLD,
        APPSYS_OPT_ID_ACT_MTR_XL,
        APPSYS_OPT_ID_ACT_MTR_XR,
        APPSYS_OPT_ID_ACT_MTR_Y,
        APPSYS_OPT_ID_ACT_MTR_Z,
        APPSYS_OPT_ID_ACT_MTR_WHL_AV_L,
        APPSYS_OPT_ID_ACT_MTR_WHL_AV_R,
        APPSYS_OPT_ID_ACT_MTR_HD_KNF,
        APPSYS_OPT_ID_ACT_MTR_HD_CNTR_KNF,
        APPSYS_OPT_ID_ACT_MTR_HD_HOLD,
    
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
