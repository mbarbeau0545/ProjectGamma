/*********************************************************************
 * @file        FMKHRT.h
 * @brief       Offer API to interface with High Resoltion Timer.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        02/03/2025
 * @version     1.0
 */
  
#ifndef FMK_HRT_H_INCLUDED 
#define FMK_HRT_H_INCLUDED 





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "1_FMK/FMK_CFG/FMKCFG_ConfigFiles/FMKHRT_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define FMKHRT_PWM_MAX_DUTY_CYLCE ((t_uint16)1000) /**< Max duty cycle allowed */
    #define FMKHRT_PWM_MIN_DUTY_CYLCE ((t_uint16)0)    /**< Min dutyCycle allowed */
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    //----------------------------- ENUM TYPES-----------------------------//
    /**
    * @brief High Resolution Timer Configuration Available.
    */
    typedef enum 
    {
        FMKHRT_HW_MODE_PWM = 0x00,      /**< High Resolution Line Configured in PWM Mode */
        FMKHRT_HW_MODE_ADC_PWM,         /**< High Resolution Line Configured in PWM Mode with adc triggered event */
        FMKHRT_HW_MODE_HALF_BRIDGE,     /**< High Resolution Line Configured in Half Bridge Mode */
        FMKHRT_HW_MODE_FULL_BRIDGE,     /**< High Resolution Line Configured in Full Bridge Mode */

        FMKHRT_HW_MODE_NB
    } t_eFMKHRT_TimHwMode;

    /**
    * @brief Slave Timer Channel Polarity.
    */
    typedef enum 
    {
        FMKHRT_LINE_POLARITY_LOW = 0x00,    /**<  The Output is active on Low level*/
        FMKHRT_LINE_POLARITY_HIGH,          /**<  The Output is active on High level*/
        
        FMKHRT_LINE_POLARITY_NB
    } t_eFMKHRT_LinePolarity;

    /**
    * @brief Enum for callback user evnt
    */
    typedef enum 
    {
        FMKHRT_HR_LINE_EVNT_CB_PULSE_FINISH = 0x00,

        FMKHRT_HR_LINE_EVNT_CB_NB,
    } t_eFMKHRT_HrLineEvntCb;
    //----------------------------- STRUCT TYPES---------------------------//
    /**
     * @brief Structure Configure PWM WaveForm
     */
    typedef struct 
    {
        t_uint32 frequency_u32;                 /**< Frequency of the desire PWM */
        t_eFMKHRT_LinePolarity polarity_e;      /**< Polarity of the PWM */
        t_uint32 deadTime_u32;                  /**< Dead Time between transition from Low State to High State */
    } t_sFMKHRT_PwmCfg;

    /**
     * @brief Structure to update PWM WaveForm
     */
    typedef struct 
    {
        t_uint32 frequency_u32;     /**< Update Frequency of the PWM */
        t_uint16 dutyCycle_u16;     /**< Update Dutycycle of the PWM */
        t_uint16 nbPulses_u16;      /**< Update Numbers of pulses of the PWM */
    } t_sFMKHRT_PwmOpeVal;

    /**
     * @brief Enum to set bit for changing PWM Signal
     */
    typedef enum 
    {
        FMKHRT_BIT_PWM_FREQUENCY = 0x00,
        FMKHRT_BIT_PWM_DUTYCYCLE,
        FMKHRT_BIT_PWM_NB_PULSES,
    } t_eFMKHRT_BitPwmOpe;
    //----------------------------- UNION TYPES---------------------------//
    /**
     * @brief Divided Main Freq for the Frequency Timer
     *      To help user, in Excel Hardware there is a help to know 
     *      which is more adapte to your need (sheet HRTIM_FreqHelp), 
     *      basically, Main Cpu is divided/Multiplier by the number
     *      then to obtain min/max frequency do this 
     *      
     *      min = FreqTim / 65535 
     *      max = FreqTim / 1024
     */
    typedef enum 
    {
        FMKHRT_FREQRANGE_DIV_4 = 0x00,      /**< Main Cpu Frequency will be divided by 4,  */
        FMKHRT_FREQRANGE_DIV_2,      /**< Main Cpu Frequency will be divided by 4,  */
        FMKHRT_FREQRANGE_DIV_1,      /**< Main Cpu Frequency will be divided by 4,  */
        FMKHRT_FREQRANGE_MUL_2,      /**< Main Cpu Frequency will be divided by 4,  */
        FMKHRT_FREQRANGE_MUL_4,      /**< Main Cpu Frequency will be divided by 4,  */
        FMKHRT_FREQRANGE_MUL_8,      /**< Main Cpu Frequency will be divided by 4,  */
        FMKHRT_FREQRANGE_MUL_16,      /**< Main Cpu Frequency will be divided by 4,  */
        FMKHRT_FREQRANGE_MUL_32,      /**< Main Cpu Frequency will be divided by 4,  */
        
        FMKHRT_FREQRANGE_DIVMUL_NB,
    } t_eFMKHRT_FreqMulDiv;

    typedef void (t_cbFMKHRT_HrLineEvnt)(t_eFMKHRT_HighResLine f_HrLine_e, t_eFMKHRT_HrLineEvntCb f_Evnt_e);
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
    *
    *	@brief      Perform all Init action for this module.\n
    *	@note       
    *
    */
   t_eReturnCode FMKHRT_Init(void);
   /**
   *
   *	@brief      Perform all Cyclic action for this module.\n
   *	@note       
   *
   */
   t_eReturnCode FMKHRT_Cyclic(void);
   /**
   *
   *	@brief Function to know the module state.\n 
   *
   *	@param[in]  f_State_pe : store the value, value from @ref t_eCyclicModState
   *
   *   @retval RC_OK                             @ref RC_OK
   *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
   */
   t_eReturnCode FMKHRT_GetState(t_eCyclicModState *f_State_pe);
   /**
   *
   *	@brief Function to update the module state.\n
   *
   *	@param[in]  f_State_e : the new value, value from @ref t_eCyclicModState
   *
   *   @retval RC_OK                             @ref RC_OK
   */
   t_eReturnCode FMKHRT_SetState(t_eCyclicModState f_State_e);

   /**
   *
   *	@brief  Configure a Channel from a Slave Timer in PWM Mode.\n
   *    @note   This function configure bsp instance, slave timer & channel to 
   *            generate a PWM based on f_PwmCfg_s configuration. Current feedback mesure
   *            are possible (not implemented yet).
   *    @warning
   *            The frequency of the bsp Instance is shared by all slave and each slave timer
   *            have poor choices of prescaler t_eFMKHRT_FreqMulDiv ('cause it's 4 bits register).
   *            It means every channel has a minimum frequency (freqSlave / 65530 == ARR) and a maximum frequency 
   *            (freqSlave / 1024) that the user has to be aware of. 
   *            A help to calculte the min/max frequency is provide in Hardware Excel Configuration sheet HRTIM_FreqHelp.
   *            Once a slave is configured, the freqMin and freqMax are calculated and if user 
   *            are below or above this limit, the limit is take instead of the one desire.
   *            
   *
   *	@param[in]  f_HRLine_e          : High Resolution Line to Configure.
   *	@param[in]  f_CpuFreqMulDiv_e   : Prescaler Frequency to applied for the slave timer, value from @ref f_CpuFreqMulDiv_e
   *	@param[in]  f_PwmCfg_s          : Pwm Output configuration.
   *	@param[in]  f_pulseEvntCb_pcb   : pulse genration finish callback 
   *
   *   @retval RC_OK                             @ref RC_OK
   */
    t_eReturnCode FMKHRT_ConfigurePwmLine(  t_eFMKHRT_HighResLine f_HRLine_e, 
                                            t_eFMKHRT_FreqMulDiv f_CpuFreqMulDiv_e,
                                            t_sFMKHRT_PwmCfg f_PwmCfg_s,
                                            t_cbFMKHRT_HrLineEvnt * f_pulseEvntCb_pcb);
   /**
   *
   *	@brief Function to Set DutyCycle/ frequency / pulses for a High Res Line
   *
   *    @param[in]  f_HRLine_e          : High Resolution Line to Configure.
   *    @param[in]  f_PwmOpe_s          : Pwm WaveForm Value
   *    @param[in]  f_maskUpdate_u8     : mask to know which parameterr has to be upate, value from @ref t_eFMKHRT_BitPwmOpe
   *
   *    @retval RC_OK                             @ref RC_OK
   */
    t_eReturnCode FMKHRT_SetPwmLineWaveform(t_eFMKHRT_HighResLine f_HRLine_e, 
                                            t_sFMKHRT_PwmOpeVal f_PwmOpe_s,
                                            t_uint8 f_maskUpdate_u8);
    /**
   *
   *	@brief Function to Get DutyCycle/ frequency / pulses for a High Res Line
   *
   *    @param[in]  f_HRLine_e          : High Resolution Line to Configure.
   *    @param[in]  f_PwmVal_ps         : Container for Pwm WaveForm Value
   *    @param[in]  f_maskUpdate_u8     : mask to know which parameterr has to be upate, value from @ref t_eFMKHRT_BitPwmOpe
   *
   *    @retval RC_OK                             @ref RC_OK
   */
    t_eReturnCode FMKHRT_GetPwmLineWaveform(t_eFMKHRT_HighResLine f_HRLine_e, 
                                            t_sFMKHRT_PwmOpeVal * f_PwmVal_ps,
                                            t_uint8 f_maskUpdate_u8);
    /**
    *
    *	@brief      DO NOT USE, Function to get the Handle Type def for IRQN_Handler Function
    *
    *	@param[in]  f_timer_e                : enum value for the timer, value from @ref t_eFMKTIM_Timer
    *
    *
    */
    HRTIM_HandleTypeDef * FMKHRT_PRIVATE_GetHandleTypeDef(t_eFMKHRT_HighResLine f_HRLine_e);
#endif // FMK_HRT_H_INCLUDED           
//************************************************************************************
// End of File
//************************************************************************************

/**
 *
 *	@brief
 *	@note   
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
