/**
 * @file        CL42T_ConfigPublic.h
 * @brief       Driver Module for Driver CL42T.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        21/01/2025
 * @version     1.0
 */
  
#ifndef GANTRY_CONFIGPUBLIC_H_INCLUDED
#define GANTRY_CONFIGPUBLIC_H_INCLUDED

    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define GTRY_MAX_ITERATION      ((t_sint32)50)
    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//
    ///@brief Axe Handle list for Gantry
    typedef enum
    {
        GTRY_AXE_HANDLE_HEAD = 0,                    //---- Gantry Head for Loop ----//
        GTRY_AXE_HANDLE_XL = GTRY_AXE_HANDLE_HEAD,    //--- Gantry Axe X left side -----//
        GTRY_AXE_HANDLE_XR,                          //--- Gantry Axe X right side -----//
        GTRY_AXE_HANDLE_Y,                           //--- Gantry Axe Y  ----//
        GTRY_AXE_HANDLE_Z,                           //--- Gantry Axe Z  -----//

        GTRY_AXE_HANDLE_NB,                                //--- Gantry Axe Number -----//
    } t_eGTRY_AxeHandleList;

    ///@brief Axe Id Number
    typedef enum 
    {
        GTRY_PHYS_AXE_HEAD = 0,                 //---- Gantry Physical Axe to Loop ----//
        GTRY_PHYS_AXE_X = GTRY_PHYS_AXE_HEAD,   //---- Gantry Physical Axe X ----//
        GTRY_PHYS_AXE_Y,                        //---- Gantry Physical Axe Y ----//
        GTRY_PHYS_AXE_Z,                        //---- Gantry Physical Axe Z ----//

        GTRY_PHYS_AXE_NB,                        //---- Gantry Physical Axe Number ----//
    } t_eGTRY_PhysicalAxe;

    ///@brief Command Iteration Payload
    typedef struct 
    {
        t_sint32 pulses_s32;            //---- pulses to send to the motor ----//
        t_float32 frequency_f32;        //---- frequency of the motor -----//
        t_float32 triggerTimer_f32;     //---- What time relatively to the first iteration, this iteration should be send ----//
    } t_sGTRY_MtrCmdIterPayload;
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
