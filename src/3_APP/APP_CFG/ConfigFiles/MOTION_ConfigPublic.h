/**
 * @file        MOTION_ConfigPublic.h
 * @brief       \n.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        21/01/2025
 * @version     1.0
 */
  
#ifndef MOTION_CONFIGPUBLIC_H_INCLUDED
#define MOTION_CONFIGPUBLIC_H_INCLUDED

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
    ///@brief Actuators mapping that deal with direction
    typedef enum
    {
        MOT_ACTDIR_WHL_AV_L = 0,            //---- Motion Wheel AV Left Angle Position ----//
        MOT_ACTDIR_WHL_AV_R,                //---- Motion Wheel AV Right Angle Position ----//
        
        MOT_ACTDIR_NB
    } t_eMOT_ActDirectionList;

    /// @brief actuatord mapping that deal with propulsion
    typedef enum 
    {
        MOT_ACTPROP_WHL_AR_L = 0,            //---- Motion Propulsion from wheel back Left ----//
        MOT_ACTPROP_WHL_AR_R,                //---- Motion Propulsion from wheel back right ----//

        MOT_ACTPROP_NB
    } t_eMOT_ActPropList;

    /// @brief Propulsion asservisement managment
    typedef enum 
    {
        MOT_PROPMODE_MRAD_PER_SEC = 0,
        MOT_PROPMODE_TORQUE,

        MOT_PROPMODE_NB,
    } t_eMOT_PropMode;
    ///@brief Command Iteration Payload
    typedef struct 
    {
        t_sint32 pulses_s32;            //---- pulses to send to the motor ----//
        t_float32 frequency_f32;        //---- frequency of the motor -----//
        t_float32 triggerTimer_f32;     //---- What time relatively to the first iteration, this iteration should be send ----//
    } t_sMOT_MtrCmdIterPayload;
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
