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
    typedef struct 
    {
        t_float32 posX_f32;     //---- Axe X position ----//
        t_float32 posY_f32;     //---- Axe Y position ----//
        t_float32 posZ_f32;     //---- Axe Z position ----//
    } t_sGTRY_AxePosition;
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
    t_eReturnCode GTRY_Init(void);
    /**
     * @brief Function Init for Agent Gantry
     *          of state  Machine
     * ----------------------------------------------------------------------------
     * @return ohters : @ref t_eReturnCode
     */
    t_eReturnCode GTRY_PeriodicTask(void);
    /**
     * @brief Function Init for Agent Gantry
     *          of state  Machine
     * ----------------------------------------------------------------------------
     * @return ohters : @ref t_eReturnCode
     */
    t_eReturnCode GTRY_GetPosition(t_sGTRY_AxePosition * f_axePosps);
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
