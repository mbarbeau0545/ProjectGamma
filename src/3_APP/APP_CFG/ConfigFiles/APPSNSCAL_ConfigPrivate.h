/*********************************************************************
 * @file        APPSNSCAL_ConfigPrivate.h
 * @brief       Sensor calibration configuration (private).
 * @note        Generated default calibration table.
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPSNSCAL_CONFIGPRIVATE_H_INCLUDED
#define APPSNSCAL_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APPSNSCAL_ConfigPublic.h"
    #include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
    #include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
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
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
    typedef struct
    {
        t_eAPPSNSCAL_CalibMode mode_e;
        t_float32 offset_f32;
        t_float32 gain_f32;
        t_eAPPSPM_ItemPrm prmOffsetID_e;
        t_eAPPSPM_ItemPrm prmGainID_e;
    } t_sAPPSNSCAL_CalibCfg;
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    ///@brief Default calibration values per sensor interface.
    const t_sAPPSNSCAL_CalibCfg c_AppSnsCal_CalibCfg_as[APPSNS_SNSITF_NB] = {
        [APPSNS_SNSITF_ECDR_XL_POS] ={
            .mode_e = APPSNSCAL_CALMODE_OFFSET_GAIN,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_SNSCAL_ECDR_XL_OFFSET,
            .prmGainID_e = APPSPM_PRM_SNSCAL_ECDR_XL_GAIN,
        },
        [APPSNS_SNSITF_ECDR_XL_SPD] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_ECDR_XR_POS] ={
            .mode_e = APPSNSCAL_CALMODE_OFFSET_GAIN,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_SNSCAL_ECDR_XR_OFFSET,
            .prmGainID_e = APPSPM_PRM_SNSCAL_ECDR_XR_GAIN,
        },
        [APPSNS_SNSITF_ECDR_XR_SPD] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_ECDR_Y_POS] ={
            .mode_e = APPSNSCAL_CALMODE_OFFSET_GAIN,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_SNSCAL_ECDR_Y_OFFSET,
            .prmGainID_e = APPSPM_PRM_SNSCAL_ECDR_Y_GAIN,
        },
        [APPSNS_SNSITF_ECDR_Y_SPD] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_ECDR_Z_POS] ={
            .mode_e = APPSNSCAL_CALMODE_OFFSET_GAIN,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_SNSCAL_ECDR_Z_OFFSET,
            .prmGainID_e = APPSPM_PRM_SNSCAL_ECDR_Z_GAIN,
        },
        [APPSNS_SNSITF_ECDR_Z_SPD] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_ECDR_WHL_AV_L_POS] ={
            .mode_e = APPSNSCAL_CALMODE_OFFSET_GAIN,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_SNSCAL_ECDR_WHL_AV_L_OFFSET,
            .prmGainID_e = APPSPM_PRM_SNSCAL_ECDR_WHL_AV_L_GAIN,
        },
        [APPSNS_SNSITF_ECDR_WHL_AV_L_SPD] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_ECDR_WHL_AV_R_POS] ={
            .mode_e = APPSNSCAL_CALMODE_OFFSET_GAIN,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_SNSCAL_ECDR_WHL_AV_R_OFFSET,
            .prmGainID_e = APPSPM_PRM_SNSCAL_ECDR_WHL_AV_R_GAIN,
        },
        [APPSNS_SNSITF_ECDR_WHL_AV_R_SPD] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_ECDR_HD_KNF_POS] ={
            .mode_e = APPSNSCAL_CALMODE_OFFSET_GAIN,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_SNSCAL_ECDR_HD_KNF_OFFSET,
            .prmGainID_e = APPSPM_PRM_SNSCAL_ECDR_HD_KNF_GAIN,
        },
        [APPSNS_SNSITF_ECDR_HD_KNF_SPD] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_ECDR_HD_CNTR_KNF_POS] ={
            .mode_e = APPSNSCAL_CALMODE_OFFSET_GAIN,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_SNSCAL_ECDR_HD_CNTR_KNF_OFFSET,
            .prmGainID_e = APPSPM_PRM_SNSCAL_ECDR_HD_CNTR_KNF_GAIN,
        },
        [APPSNS_SNSITF_ECDR_HD_CNTR_KNF_SPD] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_ECDR_HD_HOLD_POS] ={
            .mode_e = APPSNSCAL_CALMODE_OFFSET_GAIN,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_SNSCAL_ECDR_HD_HOLD_KNF_OFFSET,
            .prmGainID_e = APPSPM_PRM_SNSCAL_ECDR_HD_HOLD_KNF_GAIN,
        },
        [APPSNS_SNSITF_ECDR_HD_HOLD_SPD] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_HD_UP_LEFT_DIST] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_HD_DWN_LEFT_DIST] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_HD_UP_RIGHT_DIST] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_HD_DWN_RIGHT_DIST] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_TRQ_MTR_XL_TRQ] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_TRQ_MTR_XR_TRQ] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_TRQ_MTR_Y_TRQ] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_TRQ_MTR_Z_TRQ] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_TRQ_MTR_WHL_AV_L_TRQ] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_TRQ_MTR_WHL_AV_R_TRQ] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_TRQ_MTR_HD_KNF_TRQ] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_TRQ_MTR_CNTR_KNF_TRQ] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
        [APPSNS_SNSITF_TRQ_MTR_HD_HOLD_TRQ] ={
            .mode_e = APPSNSCAL_CALMODE_BYPASS,
            .offset_f32 = (t_float32)0.0,
            .gain_f32 = (t_float32)1.0,
            .prmOffsetID_e = APPSPM_PRM_NB,
            .prmGainID_e = APPSPM_PRM_NB,
        },
    };

    /* CAUTION : Automatic generated code section for Variable: End */

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APPSNSCAL_CONFIGPRIVATE_H_INCLUDED           
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
