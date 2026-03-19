/**
 * @file        CL42T_ConfigPrivate.h
 * @brief       Driver Module for Driver CL42T.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        21/01/2025
 * @version     1.0
 */
  
#ifndef CL42T_CONFIGPRIVATE_H_INCLUDED
#define CL42T_CONFIGPRIVATE_H_INCLUDED

    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./CL42T_ConfigPublic.h"
    #include "FMK_HAL/FMK_IO/Src/FMK_IO.h"
    #include "./APPSIG_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define CL42T_DEAD_TIME_TRANSITION ((t_uint16)200)

    /**
     * @brief Define for CL42T Diagnotic Pulse
     */
    #define CL42T_ONE_PULSE     ((t_uint16)1)
    #define CL42T_TWO_PULSE     ((t_uint16)2)
    #define CL42T_THREE_PULSE   ((t_uint16)3)
    #define CL42T_FOUR_PULSE    ((t_uint16)4)
    #define CL42T_FIVE_PULSE    ((t_uint16)5)
    #define CL42T_SIX_PULSE     ((t_uint16)6)
    #define CL42T_SEVEN_PULSE   ((t_uint16)7)

    /**
     * @brief Normal duty cycle
     */
    #define CL42T_NOMINATIVE_DUTYCYCLE ((t_uint16)500)

    ///@brief Nominative Frequency 
    #define CL42T_NOMINATIVE_FREQUENCY ((t_uint32)6000)

    ///@Brief Datasheet says for the first enable motor wait 200 m before setting dir/pulse
    #define CL42T_ENABLE_MOTOR_TIMEOUT  ((t_uint16)200)

    ///@brief Datasheet says frequency diagnotic period is 0,3 sec -> ~3Hz
    #define CL42T_IN_FREQ_SAMPLING      ((t_float32)0.5)

    ///@brief number of command we can get 
    #define CL42T_CMD_QUEUE_SIZE ((t_uint8)20)
    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//
 
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
   
    //-----------------------------STRUCT TYPES---------------------------//
    typedef struct 
    {
        t_eAPPSIG_Signal mtrState_e;
        t_eAPPSIG_Signal cwEndStop_e;
        t_eAPPSIG_Signal ccwEndStop_e;
        t_eAPPSIG_Signal deadTime_e;
        t_eAPPSIG_Signal direction_e;
        t_eAPPSIG_Signal health_e;
    } t_sCL42T_MtrDebugInfo;
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    const t_sCL42T_MtrDebugInfo c_CL42T_SigMtrDebug[CL42T_MOTOR_NB] = {
        [CL42T_MOTOR_1] = {
            .mtrState_e = APPSIG_SIGNAL_CL42T_MTR_1_STATE,
            .cwEndStop_e = APPSIG_SIGNAL_CL42T_MTR_1_CW_ENDSTOP,
            .ccwEndStop_e = APPSIG_SIGNAL_CL42T_MTR_1_CCW_ENDSTOP,
            .deadTime_e = APPSIG_SIGNAL_CL42T_MTR_1_DEADTIME,
            .direction_e = APPSIG_SIGNAL_CL42T_MTR_1_DIRECTION,
            .health_e = APPSIG_SIGNAL_CL42T_MTR_1_HEALTH
        },
        [CL42T_MOTOR_2] = {
            .mtrState_e = APPSIG_SIGNAL_CL42T_MTR_2_STATE,
            .cwEndStop_e = APPSIG_SIGNAL_CL42T_MTR_2_CW_ENDSTOP,
            .ccwEndStop_e = APPSIG_SIGNAL_CL42T_MTR_2_CCW_ENDSTOP,
            .deadTime_e = APPSIG_SIGNAL_CL42T_MTR_2_DEADTIME,
            .direction_e = APPSIG_SIGNAL_CL42T_MTR_2_DIRECTION,
            .health_e = APPSIG_SIGNAL_CL42T_MTR_2_HEALTH
        },
        [CL42T_MOTOR_3] = {
            .mtrState_e = APPSIG_SIGNAL_CL42T_MTR_3_STATE,
            .cwEndStop_e = APPSIG_SIGNAL_CL42T_MTR_3_CW_ENDSTOP,
            .ccwEndStop_e = APPSIG_SIGNAL_CL42T_MTR_3_CCW_ENDSTOP,
            .deadTime_e = APPSIG_SIGNAL_CL42T_MTR_3_DEADTIME,
            .direction_e = APPSIG_SIGNAL_CL42T_MTR_3_DIRECTION,
            .health_e = APPSIG_SIGNAL_CL42T_MTR_3_HEALTH
        },
        [CL42T_MOTOR_4] = {
            .mtrState_e = APPSIG_SIGNAL_CL42T_MTR_4_STATE,
            .cwEndStop_e = APPSIG_SIGNAL_CL42T_MTR_4_CW_ENDSTOP,
            .ccwEndStop_e = APPSIG_SIGNAL_CL42T_MTR_4_CCW_ENDSTOP,
            .deadTime_e = APPSIG_SIGNAL_CL42T_MTR_4_DEADTIME,
            .direction_e = APPSIG_SIGNAL_CL42T_MTR_4_DIRECTION,
            .health_e = APPSIG_SIGNAL_CL42T_MTR_4_HEALTH
        }
    };
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    
#endif // CL42T_CONFIGPRIVATE_H_INCLUDED
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
