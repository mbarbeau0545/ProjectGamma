/*********************************************************************
 * @file        GANTRY.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef GANTRY_H_INCLUDED
#define GANTRY_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "APP_CFG/ConfigFiles/GANTRY_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************
	/* CAUTION : Automatic generated code section for Enum: Start */

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
    /**
     * @brief Function Init for Agent Gantry
     *          of state  Machine
     * ----------------------------------------------------------------------------
     * @return ohters : @ref t_eReturnCode
     */
    t_eReturnCode GANTRY_Init(void);
    /**
     * @brief Function Init for Agent Gantry
     *          of state  Machine
     * ----------------------------------------------------------------------------
     * @return ohters : @ref t_eReturnCode
     */
    t_eReturnCode GANTRY_PeriodicTask(void);
    /**
     * @brief Function to get the position in mm
     * @details Depending on the activation of encoder option
     *          this function return either the exact current position 
     *          of the axes if the ecdr for the axe is ope
     *          Or the expected position after all iterations to reach 
     *          the last cmd position will be made
     * ----------------------------------------------------------------------------
     * @param[in] f_currPos_af32 : Contianer for current position
     * ----------------------------------------------------------------------------
     * @return ohters : @ref t_eReturnCode
     */
    t_eReturnCode GTRY_GetPosition(t_float32 f_currPos_af32[GTRY_PHYS_AXE_NB]);
#endif // APP_LGC_H_INCLUDED           
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
