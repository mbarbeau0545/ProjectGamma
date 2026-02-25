/*********************************************************************
 * @file        APPSPM_ConfigPrivate.h
 * @brief       System Paramters Managment.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
  
#ifndef APPSPM_CONFIGPUBLIC_H_INCLUDED
#define APPSPM_CONFIGPUBLIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************

    ///@brief union to set/get parameter
    typedef union
    {
        t_uint8 prmVal_u8;
        t_uint16 prmVal_u16;
        t_uint32 prmVal_u32;
        t_sint8 prmVal_s8;
        t_sint16 prmVal_s16;
        t_sint32 prmVal_s32;
        t_float32 prmVal_f32;
    } t_uAPPSPM_PrmValType;

    ///@brief enumeration of type of parameter 
    typedef enum 
    {
        APPSPM_PRM_TYPE_UINT8 = 0,
        APPSPM_PRM_TYPE_UINT16,
        APPSPM_PRM_TYPE_UINT32,
        APPSPM_PRM_TYPE_SINT8,
        APPSPM_PRM_TYPE_SINT16,
        APPSPM_PRM_TYPE_SINT32,
        APPSPM_PRM_TYPE_FLOAT32,

        APPSPM_PRM_TYPE_NB,
    } t_eAPPSPM_PrmType;
    /* CAUTION : Automatic generated code section for Enum: Start */
    /**
    * @brief Enum for listong every parameter.
    */
    typedef enum
    {
        APPSPM_PRM_GTRY_PULSE_ITER_MAX = 0,
        APPSPM_PRM_GTRY_X_RMP_CTRL_KFACTOR,
        APPSPM_PRM_GTRY_X_RMP_CTRL_SLOP_SPD,
        APPSPM_PRM_GTRY_X_RMP_CTRL_NB_STEP,
        APPSPM_PRM_GTRY_X_SPD_MAX,
        APPSPM_PRM_GTRY_X_SPD_MIN,
        APPSPM_PRM_GTRY_X_CALIB_OFFSET,
        APPSPM_PRM_GTRY_Y_RMP_CTRL_KFACTOR,
        APPSPM_PRM_GTRY_Y_RMP_CTRL_SLOP_SPD,
        APPSPM_PRM_GTRY_Y_RMP_CTRL_NB_STEP,
        APPSPM_PRM_GTRY_Y_SPD_MAX,
        APPSPM_PRM_GTRY_Y_SPD_MIN,
        APPSPM_PRM_GTRY_Y_CALIB_OFFSET,
        APPSPM_PRM_GTRY_Z_RMP_CTRL_KFACTOR,
        APPSPM_PRM_GTRY_Z_RMP_CTRL_SLOP_SPD,
        APPSPM_PRM_GTRY_Z_RMP_CTRL_NB_STEP,
        APPSPM_PRM_GTRY_Z_SPD_MAX,
        APPSPM_PRM_GTRY_Z_SPD_MIN,
        APPSPM_PRM_GTRY_Z_CALIB_OFFSET,
        APPSPM_PRM_SYS_OPT_SNS_ECDR_XL,
        APPSPM_PRM_SYS_OPT_SNS_ECDR_XR,
        APPSPM_PRM_SYS_OPT_SNS_ECDR_Y,
        APPSPM_PRM_SYS_OPT_SNS_ECDR_Z,
        APPSPM_PRM_SYS_MACHINE_ID,
        APPSPM_PRM_SYS_OPT_ACT_MTR_XL,
        APPSPM_PRM_SYS_OPT_ACT_MTR_XR,
        APPSPM_PRM_SYS_OPT_ACT_MTR_Y,
        APPSPM_PRM_SYS_OPT_ACT_MTR_Z,
        APPSPM_PRM_GTRY_ALGO_CPTE_TYPE,
        APPSPM_PRM_GTRY_CALIB_TYPE,
        APPSPM_PRM_GTRY_SENDITER_TYPE,
        APPSPM_PRM_GTRY_AXE_X_PULSE_PER_MM,
        APPSPM_PRM_GTRY_AXE_Y_PULSE_PER_MM,
        APPSPM_PRM_GTRY_AXE_Z_PULSE_PER_MM,
        APPSPM_PRM_GTRY_AXE_X_LEN,
        APPSPM_PRM_GTRY_AXE_Y_LEN,
        APPSPM_PRM_GTRY_AXE_Z_LEN,
        APPSPM_PRM_GTRY_AXE_X_SAFE_HEIGHT,
        APPSPM_PRM_GTRY_AXE_Y_SAFE_HEIGHT,
        APPSPM_PRM_GTRY_AXE_Z_SAFE_HEIGHT,
        APPSPM_PRM_SYS_OPT_ACT_MTR_WHL_AV_L,
        APPSPM_PRM_SYS_OPT_ACT_MTR_WHL_AV_R,
        APPSPM_PRM_SYS_OPT_ACT_MTR_HD_KNF,
        APPSPM_PRM_SYS_OPT_ACT_MTR_HD_CNTR_KNF,
        APPSPM_PRM_SYS_OPT_ACT_MTR_HD_HOLD,
        APPSPM_PRM_SYS_OPT_ACT_PWR_MTR_XL,
        APPSPM_PRM_SYS_OPT_ACT_PWR_MTR_XR,
        APPSPM_PRM_SYS_OPT_ACT_PWR_MTR_Y,
        APPSPM_PRM_SYS_OPT_ACT_PWR_MTR_Z,
        APPSPM_PRM_SYS_OPT_ACT_PWR_WHL_AV_L,
        APPSPM_PRM_SYS_OPT_ACT_PWR_WHL_AV_R,
        APPSPM_PRM_SYS_OPT_ACT_PWR_MTR_HD_KNF,
        APPSPM_PRM_SYS_OPT_ACT_PWR_MTR_HD_CNTR_KNF,
        APPSPM_PRM_SYS_OPT_ACT_PWR_MTR_HD_HOLD,
        APPSPM_PRM_SYS_OPT_SNS_ECDR_WHL_AV_L,
        APPSPM_PRM_SYS_OPT_SNS_ECDR_WHL_AV_R,
        APPSPM_PRM_SYS_OPT_SNS_ECDR_HD_KNF,
        APPSPM_PRM_SYS_OPT_SNS_ECDR_HD_CNTR_KNF,
        APPSPM_PRM_SYS_OPT_SNS_ECDR_HD_HOLD,
        APPSPM_PRM_SYS_OPT_SNS_HD_UP_LEFT,
        APPSPM_PRM_SYS_OPT_SNS_HD_DWN_LEFT,
        APPSPM_PRM_SYS_OPT_SNS_HD_UP_RIGHT,
        APPSPM_PRM_SYS_OPT_SNS_HD_DWN_RIGHT,
        APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_XL,
        APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_XR,
        APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_Y,
        APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_Z,
        APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_WHL_AV_L,
        APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_WHL_AV_R,
        APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_HD_KNF,
        APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_CNTR_KNF,
        APPSPM_PRM_SYS_OPT_SNS_TRQ_MTR_HD_HOLD,
        APPSPM_PRM_HC_LEN_FROM_REFA_TO_REFB,
        APPSPM_PRM_HC_LEN_HEAD_CNTR_KNIFE,
        APPSPM_PRM_HC_LEN_HEAD_KNIFE,
        APPSPM_PRM_HC_CNTR_KNIFE_PULSE_TO_RAD,
        APPSPM_PRM_HC_KNIFE_PULSE_TO_RAD,
        APPSPM_PRM_HC_HOLD_KNIFE_PULSE_TO_RAD,
    
        APPSPM_PRM_NB,
    } t_eAPPSPM_ItemPrm;

    /* CAUTION : Automatic generated code section for Enum: End */

	//-----------------------------ENUM TYPES-----------------------------//

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
