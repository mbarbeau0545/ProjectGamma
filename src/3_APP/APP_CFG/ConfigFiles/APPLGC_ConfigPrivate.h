/**
 * @file        CL42T_ConfigPrivate.h
 * @brief       Driver Module for Driver CL42T.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        21/01/2025
 * @version     1.0
 */
  
#ifndef APPLGC_CONFIGPRIVATE_H_INCLUDED
#define APPLGC_CONFIGPRIVATE_H_INCLUDED

    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APPLGC_ConfigPublic.h"
    #include "APP_CFG/ConfigFiles/APPACT_ConfigPublic.h"
    #include "APP_CFG/ConfigFiles/APPSNS_ConfigPublic.h"

    //---- agent include ----//
    #include "APP_LGC/Src/Agents/Gantry/Src/GANTRY.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//
 
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
   
    //-----------------------------STRUCT TYPES---------------------------//

    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    ///@brief Sensors Computaion type 
    const t_uint8 c_APPLGC_SnsIfCompType_au8[APPSNS_SNSITF_NB] = {
        APPSNS_DISTANCE_UNIT_MILLIMETER,// APPSNS_SNSITF_ECDR_XL_POS
        APPSNS_ANGULARSPD_DEGREE_PER_SEC,// APPSNS_SNSITF_ECDR_XL_SPEED
        APPSNS_DISTANCE_UNIT_MILLIMETER,// APPSNS_SNSITF_ECDR_XR_POS
        APPSNS_ANGULARSPD_DEGREE_PER_SEC,// APPSNS_SNSITF_ECDR_XR_SPEED
        APPSNS_DISTANCE_UNIT_MILLIMETER,// APPSNS_SNSITF_ECDR_Y_POS
        APPSNS_ANGULARSPD_DEGREE_PER_SEC,// APPSNS_SNSITF_ECDR_Y_SPEED
        APPSNS_DISTANCE_UNIT_MILLIMETER,// APPSNS_SNSITF_ECDR_Z_POS
        APPSNS_ANGULARSPD_DEGREE_PER_SEC,// APPSNS_SNSITF_ECDR_Z_SPEED
    };
    /* CAUTION : Automatic generated code section for Variable: Start */
    /**
    * @brief Agent Configuration Function
    */
    const t_sAPPLGC_AgentFunc c_AppLGc_AgentInfo_as[APPLGC_AGENT_NB] ={
        {GANTRY_Init,                       GANTRY_PeriodicTask},// APPLGC_AGENT_GANTRY
        {HEAD_CUTTER_Init,                  HEAD_CUTTER_PeriodicTask},// APPLGC_AGENT_HEAD_CUTTER
        {MOTION_Init,                       MOTION_PeriodicTask},// APPLGC_AGENT_MOTION
    };

    /* CAUTION : Automatic generated code section for Variable: End */
    
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    
#endif // APPLGC_CONFIGPRIVATE_H_INCLUDED
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
