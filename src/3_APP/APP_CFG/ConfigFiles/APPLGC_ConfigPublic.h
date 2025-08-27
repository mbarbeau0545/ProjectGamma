/**
 * @file        CL42T_ConfigPublic.h
 * @brief       Driver Module for Driver CL42T.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        21/01/2025
 * @version     1.0
 */
  
#ifndef APPLGC_CONFIGPUBLIC_H_INCLUDED
#define APPLGC_CONFIGPUBLIC_H_INCLUDED

    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "./APPACT_ConfigPublic.h"
    #include "FMK_HAL/FMK_SRL/Src/FMK_SRL.h"                
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************

    /**
    * @brief Enum for Service Func Health Status
    */
    typedef enum 
    {
        APPLGC_SRV_HEALTH_OK = 0x00,
        APPLGC_SRV_HEALTH_ERROR,

        APPLGC_SRV_HEALTH_NB,
    } t_eAPPLGC_SrvHealth;

    /**
    * @brief Enum for Service Function Health
    */
    typedef enum 
    {
        APPLGC_SRV_STATE_STOPPED = 0x00,
        APPLGC_SRV_STATE_MOVING,

        APPLGC_SRV_STATE_NB,
    } t_eAPPLGC_SrvState;

    /* CAUTION : Automatic generated code section for Enum: Start */
    /**
    * @brief Enum for Service Function Listy
    */
    typedef enum ____t_eAPPLGC_SrvList
    {
        APPLGC_SRV_GTRY_X = 0x00,
        APPLGC_SRV_GTRY_Y,
        APPLGC_SRV_GTRY_Z,

        APPLGC_SRV_NB,
    } t_eAPPLGC_SrvList;
    /**
    * @brief Enum for Agent
    */
    typedef enum ____t_eAPPLGC_AgentList
    {
        APPLGC_AGENT_GANTRY = 0x00,          // G�re la gestion du gantry

        APPLGC_AGENT_NB,
    } t_eAPPLGC_AgentList;
    /* CAUTION : Automatic generated code section for Enum: End */
    
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */
    typedef struct 
    {
        t_eAPPLGC_SrvHealth health_e;
        t_eAPPLGC_SrvState  state_e;
    } t_sAPPLGC_ServiceInfo;

    /**
    *
    *	@brief      Set the Agent Init Function
    *
    */
    typedef t_eReturnCode (t_cbAPPLGC_AgentInit)(void);
    /**
    *
    *	@brief      Set the Agent Init Function
    *
    *   @param[in]  f_snsValues_paf32 : All Values Sensors.\n
    *   @param[in]  f_SrvInfo_pas     : All Services Infos.\n
    *
    */
    typedef t_eReturnCode (t_cbAPPLGC_AgentPeriodicTask)(   t_float32 *f_snsValues_paf32, 
                                                            t_sAPPLGC_ServiceInfo *f_SrvInfo_pas);


    //-----------------------------STRUCT TYPES---------------------------//
    typedef struct 
    {
        t_cbAPPLGC_AgentInit * init_pcb;
        t_cbAPPLGC_AgentPeriodicTask * PeriodTask_pcb;
    } t_sAPPLGC_AgentFunc;

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    
#endif // APPLGC_CONFIGPUBLIC_H_INCLUDED
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
