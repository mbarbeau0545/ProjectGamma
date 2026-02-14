/*********************************************************************
 * @file        MOTION.c
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */






// ********************************************************************
// *                      Includes
// ********************************************************************
#include "./MOTION.h"

#include "Library/QUEUE/Src/LIBQueue.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------ENUM TYPES-----------------------------//

/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************

/* CAUTION : Automatic generated code section for Variable: Start */
/* CAUTION : Automatic generated code section for Variable: End */
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
 * @brief State Machine of the Agent.
 * @brief This function check if motors are in a logic state
 * ----------------------------------------------------------------------------
 * @return @ref t_eReturnCode
 */
//static t_eReturnCode s_HEAD_CUTTER_StateMachine(void);

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * GTRY_Init
 *********************************/
t_eReturnCode MOTION_Init(void)
{
    t_eReturnCode Ret_e;
    

    Ret_e = RC_OK;

    return Ret_e;
}

/*********************************
 * GTRY_Init
 *********************************/
t_eReturnCode MOTION_PeriodicTask(void)
{
    t_eReturnCode Ret_e = RC_OK;
    
    return Ret_e;
}

// ********************************************************************
// *                      Local Functions - Implementation
// ********************************************************************

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

