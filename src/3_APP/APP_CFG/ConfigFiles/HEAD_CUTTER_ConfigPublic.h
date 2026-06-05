/**
 * @file        HEAD_CUTTER_ConfigPublic.h
 * @brief       \n.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        21/01/2025
 * @version     1.0
 */
  
#ifndef HEADGE_CUTTER_CONFIGPUBLIC_H_INCLUDED
#define HEADGE_CUTTER_CONFIGPUBLIC_H_INCLUDED

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

    //-----------------------------ENUM TYPES-----------------------------//
    ///@brief Axe Handle list for Head Cutter
    typedef enum
    {
        HC_AXE_HEAD = 0,
        HC_AXE_HD_KNFE = HC_AXE_HEAD,           //---- Head Cutter knife axe ----//
        HC_AXE_HD_CNTR_KNFE,                    //---- Head Cutter counter knife axe ----//
        HC_AXE_HD_HOLD_KNFE,                    //---- Head Cutter hold knife axe ----//

        HC_AXE_HD_NB,                           //--- Head Cutter Axe Number -----//
    } t_eHC_AxeHandleList;

    ///@brief Command Iteration Payload
    typedef struct 
    {
        t_sint32 pulses_s32;            //---- pulses to send to the motor ----//
        t_float32 frequency_f32;        //---- frequency of the motor -----//
        t_float32 triggerTimer_f32;     //---- What time relatively to the first iteration, this iteration should be send ----//
    } t_sHC_MtrCmdIterPayload;
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    
#endif // GANTRY_CONFIGPUBLIC_H_INCLUDED
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
