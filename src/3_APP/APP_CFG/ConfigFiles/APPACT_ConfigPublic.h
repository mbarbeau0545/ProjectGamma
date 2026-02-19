/*********************************************************************
 * @file        APPACT_ConfigPublic.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPACT_CONFIGPUBLIC_H_INCLUDED
#define APPACT_CONFIGPUBLIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    ///@brief Define for normalize return function of spec files
    #define APPACT_MOTOR_STS_OFF            ((t_float32)0.0f)
    #define APPACT_MOTOR_STS_ON             ((t_float32)1.0f)
    #define APPACT_MOTOR_STS_ENDSTOP_CW     ((t_float32)2.0f)
    #define APPACT_MOTOR_STS_ENDSTOP_CCW    ((t_float32)3.0f)
    
    #define APPACT_SOFT_STOP                ((t_float32)0.0f)
    #define APPACT_HARD_STOP                ((t_float32)-1.0f)
    #define APPACT_ENABLE_MOTOR             ((t_float32)-2.0f)

    #define APPACT_ACT_MOTOR_SUPPLY_SET     ((t_float32)1.0f)
    ///@brief define normalize direction of spec files 
    #define APPACT_DIRECTION_CW ((t_float32)0.0f)
    #define APPACT_DIRECTION_CCW ((t_float32)1.0f)
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Enum: Start */
    /**
    * @brief Enum for Actuators list.
    */
    typedef enum
    {
        APPACT_ACTITF_MTR_XL_PLS = 0,         /**< Actuator Device MTR_XL, Interface PLS, Moteur XL Left PLSs */
        APPACT_ACTITF_MTR_XL_SPD,               /**< Actuator Device MTR_XL, Interface SPD, Moteur XL Left SPD */
        APPACT_ACTITF_MTR_XL_TRG,               /**< Actuator Device MTR_XL, Interface TRG, Moteur XL Left Trigger Time to plan sending PLS */
        APPACT_ACTITF_MTR_XR_PLS,               /**< Actuator Device MTR_XR, Interface PLS, Moteur XR Left PLSs */
        APPACT_ACTITF_MTR_XR_SPD,               /**< Actuator Device MTR_XR, Interface SPD, Moteur XR Left SPD */
        APPACT_ACTITF_MTR_XR_TRG,               /**< Actuator Device MTR_XR, Interface TRG, Moteur XR RightTrigger Time to plan sending PLS */
        APPACT_ACTITF_MTR_Y_PLS,                /**< Actuator Device MTR_Y, Interface PLS, Moteur Y PLSs */
        APPACT_ACTITF_MTR_Y_SPD,                /**< Actuator Device MTR_Y, Interface SPD, Moteur Y SPD */
        APPACT_ACTITF_MTR_Y_TRG,                /**< Actuator Device MTR_Y, Interface TRG, Moteur Y Trigger Time to plan sending PLS */
        APPACT_ACTITF_MTR_Z_PLS,                /**< Actuator Device MTR_Z, Interface PLS, Moteur Z PLSs */
        APPACT_ACTITF_MTR_Z_SPD,                /**< Actuator Device MTR_Z, Interface SPD, Moteur Z SPD */
        APPACT_ACTITF_MTR_Z_TRG,                /**< Actuator Device MTR_Z, Interface TRG, Moteur Z Left Trigger Time to plan sending PLS */
        APPACT_ACTITF_MTR_WHL_AV_L_PLS,         /**< Actuator Device MTR_WHL_AV_L, Interface PLS, None */
        APPACT_ACTITF_MTR_WHL_AV_L_SPD,         /**< Actuator Device MTR_WHL_AV_L, Interface SPD, None */
        APPACT_ACTITF_MTR_WHL_AV_L_TRG,         /**< Actuator Device MTR_WHL_AV_L, Interface TRG, None */
        APPACT_ACTITF_MTR_WHL_AV_R_PLS,         /**< Actuator Device MTR_WHL_AV_R, Interface PLS, None */
        APPACT_ACTITF_MTR_WHL_AV_R_SPD,         /**< Actuator Device MTR_WHL_AV_R, Interface SPD, None */
        APPACT_ACTITF_MTR_WHL_AV_R_TRG,         /**< Actuator Device MTR_WHL_AV_R, Interface TRG, None */
        APPACT_ACTITF_MTR_HD_KNF_PLS,           /**< Actuator Device MTR_HD_KNF, Interface PLS, Moteur Z PLSs */
        APPACT_ACTITF_MTR_HD_KNF_SPD,           /**< Actuator Device MTR_HD_KNF, Interface SPD, Moteur Z SPD */
        APPACT_ACTITF_MTR_HD_KNF_TRG,           /**< Actuator Device MTR_HD_KNF, Interface TRG, Moteur Z Left Trigger Time to plan sending PLS */
        APPACT_ACTITF_MTR_HD_CNTR_KNF_PLS,      /**< Actuator Device MTR_HD_CNTR_KNF, Interface PLS, Moteur Z PLSs */
        APPACT_ACTITF_MTR_HD_CNTR_KNF_SPD,      /**< Actuator Device MTR_HD_CNTR_KNF, Interface SPD, Moteur Z SPD */
        APPACT_ACTITF_MTR_HD_CNTR_KNF_TRG,      /**< Actuator Device MTR_HD_CNTR_KNF, Interface TRG, Moteur Z Left Trigger Time to plan sending PLS */
        APPACT_ACTITF_MTR_HD_HOLD_PLS,          /**< Actuator Device MTR_HD_HOLD, Interface PLS, Moteur Z PLSs */
        APPACT_ACTITF_MTR_HD_HOLD_SPD,          /**< Actuator Device MTR_HD_HOLD, Interface SPD, Moteur Z SPD */
        APPACT_ACTITF_MTR_HD_HOLD_TRG,          /**< Actuator Device MTR_HD_HOLD, Interface TRG, Moteur Z Left Trigger Time to plan sending PLS */
    
        APPACT_ACTITF_NB,
    } t_eAPPACT_ActInterface;

    /**
    * @brief Enum for Actuators drivers list.
    */
    typedef enum
    {
        APPACT_DRV_CL42T = 0,              /**< CL42T Driver  */
    
        APPACT_DRV_NB,
    } t_eAPPACT_ActDriverList;

    /**
    * @brief Enumeration of all sensors device list.
    */
    typedef enum
    {
        APPACT_ACTDVC_MTR_XL = 0,
        APPACT_ACTDVC_MTR_XR,
        APPACT_ACTDVC_MTR_Y,
        APPACT_ACTDVC_MTR_Z,
        APPACT_ACTDVC_MTR_WHL_AV_L,
        APPACT_ACTDVC_MTR_WHL_AV_R,
        APPACT_ACTDVC_MTR_HD_KNF,
        APPACT_ACTDVC_MTR_HD_CNTR_KNF,
        APPACT_ACTDVC_MTR_HD_HOLD,
    
        APPACT_ACTDVC_NB,
    } t_eAPPACT_ActDeviceList;

    /* CAUTION : Automatic generated code section for Enum: End */
	
    //-----------------------------ENUM TYPES-----------------------------//
	/* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
    /**< Union to store the idx for convert management */
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

#endif // APPACT_CONFIGPUBLIC_H_INCLUDED           
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
