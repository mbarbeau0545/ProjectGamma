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
        APPSPM_PRM_LGC_GTRY_PULSE_ITER_MAX = 0,
        APPSPM_PRM_LGC_GTRY_X_RAMP_CTRL_KFACTOR,
        APPSPM_PRM_LGC_GTRY_X_RAMP_CTRL_SLOP_SPEED,
        APPSPM_PRM_LGC_GTRY_X_RAMP_CTRL_NB_STEP,
        APPSPM_PRM_LGC_GTRY_X_SPEED_MAX,
        APPSPM_PRM_LGC_GTRY_X_SPEED_MIN,
        APPSPM_PRM_LGC_GTRY_Y_RAMP_CTRL_KFACTOR,
        APPSPM_PRM_LGC_GTRY_Y_RAMP_CTRL_SLOP_SPEED,
        APPSPM_PRM_LGC_GTRY_Y_RAMP_CTRL_NB_STEP,
        APPSPM_PRM_LGC_GTRY_Y_SPEED_MAX,
        APPSPM_PRM_LGC_GTRY_Y_SPEED_MIN,
        APPSPM_PRM_LGC_GTRY_Z_RAMP_CTRL_KFACTOR,
        APPSPM_PRM_LGC_GTRY_Z_RAMP_CTRL_SLOP_SPEED,
        APPSPM_PRM_LGC_GTRY_Z_RAMP_CTRL_NB_STEP,
        APPSPM_PRM_LGC_GTRY_Z_SPEED_MAX,
        APPSPM_PRM_LGC_GTRY_Z_SPEED_MIN,
        APPSPM_PRM_SYS_OPT_SNS_ECDR_XL,
        APPSPM_PRM_SYS_OPT_SNS_ECDR_XR,
        APPSPM_PRM_SYS_OPT_SNS_ECDR_Y,
        APPSPM_PRM_SYS_OPT_SNS_ECDR_Z,
        APPSPM_PRM_SYS_MACHINE_ID,
        APPSPM_PRM_SYS_OPT_ACT_MTR_XL,
        APPSPM_PRM_SYS_OPT_ACT_MTR_XR,
        APPSPM_PRM_SYS_OPT_ACT_MTR_Y,
        APPSPM_PRM_SYS_OPT_ACT_MTR_Z,
        APPSPM_PRM_LGC_GTRY_ALGO_CPTE_TYPE,
        APPSPM_PRM_LGC_GTRY_MAX_PULSES,
        APPSPM_PRM_LGC_GTRY_CALIB_TYPE,
        APPSPM_PRM_LGC_GTRY_SENDITER_TYPE,
        APPSPM_PRM_LGC_GTRY_AXE_X_PULSE_PER_MM,
        APPSPM_PRM_LGC_GTRY_AXE_Y_PULSE_PER_MM,
        APPSPM_PRM_LGC_GTRY_AXE_Z_PULSE_PER_MM,
        APPSPM_PRM_LGC_GTRY_AXE_X_LEN,
        APPSPM_PRM_LGC_GTRY_AXE_Y_LEN,
        APPSPM_PRM_LGC_GTRY_AXE_Z_LEN,
    
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
