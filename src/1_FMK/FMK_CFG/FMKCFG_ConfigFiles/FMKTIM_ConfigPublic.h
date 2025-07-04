/*********************************************************************
 * @file        FMKTIM_ConfigPublic.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        31/08/2024
 * @version     1.0
 */
  
#ifndef FMKTIM_CONFIGPUBLIC_H_INCLUDED
#define FMKTIM_CONFIGPUBLIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "FMK_CFG/FMKCFG_ConfigFiles/FMKCPU_ConfigPublic.h"
    #include "TypeCommon.h"
    #include "Constant.h"
    
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define FMKTIM_TIMER_PWM_ARR_TARGET_16_BIT   ((t_uint32)0xF80C) // 63500
    #define FMKTIM_TIMER_PWM_ARR_TARGET_32_BIT   ((t_uint32)(CST_MAX_UINT_32BIT - (t_uint32)1)) 
    #define FMKTIM_FREQ_COMPUTE_DELTA_ACCEPTANCE ((t_float32)0.5)
    #define FMKTIM_ARR_LOW_LIMIT_16BIT  ((t_uint32)0xC350)     // 50000
    #define FMKTIM_ARR_HIGH_LIMIT_16BIT ((t_uint32)0xFFFE)     // 65534
    #define FMKTIM_ARR_LOW_LIMIT_32BIT  ((t_uint32)0xB2D05E00) // 3_000_000_000
    #define FMKTIM_ARR_HIGH_LIMIT_32BIT ((t_uint32)0xFFFFFFFE) // 4_294_967_295
    #define FMKTIM_WWDG_RESET_CFG  FMKTIM_WWDG_RESET_100MS /**< default watchdogs configuration */

    /**
    * @brief This define return True if the timer is a 32 Bits timers
    */
    #define FMKTIM_IS_32B_TIMER(f_timClock_e) \
        ((f_timClock_e) == FMKCPU_RCC_CLK_TIM2 ||\
         (f_timClock_e) == FMKCPU_RCC_CLK_TIM5)
    // ********************************************************************
    // *                      Types
    // ********************************************************************

    /**< typedef enum for channel mode */
    typedef enum 
    {
        FMKTIM_HWTIM_CFG_PWM = 0x0U,        /**< Timer configuration in PWM mode */
        FMKTIM_HWTIM_CFG_IC,                /**< Timer configuration in Input Capture mode */
        FMKTIM_HWTIM_CFG_OC,                /**< Timer configuration in Ouput Compare mode */
        FMKTIM_HWTIM_CFG_OP,                /**< Timer configuration in One Pulse mode */
        FMKTIM_HWTIM_CFG_EVNT,              /**< Timer configuration in Event mode */
        FMKTIM_HWTIM_CFG_ECDR,              /**< Timer configuration in encoder mode */
        FMKTIM_HWTIM_CFG_DAC,               /**< Timer configuration in Dac mode */

        FMKTIM_HWTIM_CFG_NB,                /**< Number of timer configuration mode*/
    } t_eFMKTIM_HwTimerCfg;

    //-----------------------------ENUM TYPES-----------------------------//
    /**< Interrupt Line Type */
    typedef enum 
    {
        FMKTIM_INTERRUPT_LINE_TYPE_IO = 0x00,       /**< Timer/Channel use for PWM, IC, OC, OP Purpose */
        FMKTIM_INTERRUPT_LINE_TYPE_EVNT,            /**< Timer/Channel use for Event purpose */
        FMKTIM_INTERRUPT_LINE_TYPE_DAC,             /**< Timmer/Channel use for DAC purpose */
        FMKTIM_INTERRUPT_LINE_TYPE_NB,
    } t_eFMKTIM_InterruptLineType;
    /* CAUTION : Automatic generated code section for Enum: Start */
    /**< Number max of channel enable by timer */
     typedef enum
    {
        FMKTIM_CHANNEL_1 = 0x00,              // Reference to HAL channel 1
        FMKTIM_CHANNEL_2,              // f"Reference to HAL channel 2
        FMKTIM_CHANNEL_3,              // f"Reference to HAL channel 3
        FMKTIM_CHANNEL_4,              // f"Reference to HAL channel 4

        FMKTIM_CHANNEL_NB,
        FMKTIM_CHANNEL_ALL,
    } t_eFMKTIM_InterruptChnl;
        /**
    * @brief Number of timer enable in smt32xxx board.
    */
    typedef enum
    {
        FMKTIM_TIMER_1 = 0x0,                  /**< Reference for HAL timer_1, this timer has 4 channel(s) */
        FMKTIM_TIMER_2,                        /**< Reference for HAL timer_2, this timer has 4 channel(s) */
        FMKTIM_TIMER_3,                        /**< Reference for HAL timer_3, this timer has 4 channel(s) */
        FMKTIM_TIMER_4,                        /**< Reference for HAL timer_4, this timer has 4 channel(s) */
        FMKTIM_TIMER_5,                        /**< Reference for HAL timer_5, this timer has 4 channel(s) */
        FMKTIM_TIMER_6,                        /**< Reference for HAL timer_6, this timer has 1 channel(s) */
        FMKTIM_TIMER_7,                        /**< Reference for HAL timer_7, this timer has 1 channel(s) */
        FMKTIM_TIMER_8,                        /**< Reference for HAL timer_8, this timer has 4 channel(s) */
        FMKTIM_TIMER_15,                       /**< Reference for HAL timer_15, this timer has 2 channel(s) */
        FMKTIM_TIMER_16,                       /**< Reference for HAL timer_16, this timer has 1 channel(s) */
        FMKTIM_TIMER_17,                       /**< Reference for HAL timer_17, this timer has 1 channel(s) */
        FMKTIM_TIMER_20,                       /**< Reference for HAL timer_20, this timer has 4 channel(s) */
    
        FMKTIM_TIMER_NB,
    } t_eFMKTIM_Timer;
    /**
    * @brief Number of General Purpose Interrupt Line, for PWM, Input-Compare, Output Compare, One sPulse.
    */
    typedef enum
    {
        FMKTIM_INTERRUPT_LINE_IO_11 = 0x0,                 /**< General Purpose Timer, Reference to Timer 1 Channel 1 */
        FMKTIM_INTERRUPT_LINE_IO_12,                       /**< General Purpose Timer, Reference to Timer 1 Channel 2 */
        FMKTIM_INTERRUPT_LINE_IO_13,                       /**< General Purpose Timer, Reference to Timer 1 Channel 3 */
        FMKTIM_INTERRUPT_LINE_IO_14,                       /**< General Purpose Timer, Reference to Timer 1 Channel 4 */
        FMKTIM_INTERRUPT_LINE_IO_21,                       /**< General Purpose Timer, Reference to Timer 2 Channel 1 */
        FMKTIM_INTERRUPT_LINE_IO_22,                       /**< General Purpose Timer, Reference to Timer 2 Channel 2 */
        FMKTIM_INTERRUPT_LINE_IO_23,                       /**< General Purpose Timer, Reference to Timer 2 Channel 3 */
        FMKTIM_INTERRUPT_LINE_IO_24,                       /**< General Purpose Timer, Reference to Timer 2 Channel 4 */
        FMKTIM_INTERRUPT_LINE_IO_31,                       /**< General Purpose Timer, Reference to Timer 3 Channel 1 */
        FMKTIM_INTERRUPT_LINE_IO_32,                       /**< General Purpose Timer, Reference to Timer 3 Channel 2 */
        FMKTIM_INTERRUPT_LINE_IO_33,                       /**< General Purpose Timer, Reference to Timer 3 Channel 3 */
        FMKTIM_INTERRUPT_LINE_IO_34,                       /**< General Purpose Timer, Reference to Timer 3 Channel 4 */
        FMKTIM_INTERRUPT_LINE_IO_41,                       /**< General Purpose Timer, Reference to Timer 4 Channel 1 */
        FMKTIM_INTERRUPT_LINE_IO_42,                       /**< General Purpose Timer, Reference to Timer 4 Channel 2 */
        FMKTIM_INTERRUPT_LINE_IO_43,                       /**< General Purpose Timer, Reference to Timer 4 Channel 3 */
        FMKTIM_INTERRUPT_LINE_IO_44,                       /**< General Purpose Timer, Reference to Timer 4 Channel 4 */
        FMKTIM_INTERRUPT_LINE_IO_51,                       /**< General Purpose Timer, Reference to Timer 5 Channel 1 */
        FMKTIM_INTERRUPT_LINE_IO_52,                       /**< General Purpose Timer, Reference to Timer 5 Channel 2 */
        FMKTIM_INTERRUPT_LINE_IO_53,                       /**< General Purpose Timer, Reference to Timer 5 Channel 3 */
        FMKTIM_INTERRUPT_LINE_IO_54,                       /**< General Purpose Timer, Reference to Timer 5 Channel 4 */
        FMKTIM_INTERRUPT_LINE_IO_61,                       /**< General Purpose Timer, Reference to Timer 8 Channel 1 */
        FMKTIM_INTERRUPT_LINE_IO_62,                       /**< General Purpose Timer, Reference to Timer 8 Channel 2 */
        FMKTIM_INTERRUPT_LINE_IO_63,                       /**< General Purpose Timer, Reference to Timer 8 Channel 3 */
        FMKTIM_INTERRUPT_LINE_IO_64,                       /**< General Purpose Timer, Reference to Timer 8 Channel 4 */
        FMKTIM_INTERRUPT_LINE_IO_71,                       /**< General Purpose Timer, Reference to Timer 15 Channel 1 */
        FMKTIM_INTERRUPT_LINE_IO_72,                       /**< General Purpose Timer, Reference to Timer 15 Channel 2 */
        FMKTIM_INTERRUPT_LINE_IO_81,                       /**< General Purpose Timer, Reference to Timer 16 Channel 1 */
        FMKTIM_INTERRUPT_LINE_IO_91,                       /**< General Purpose Timer, Reference to Timer 17 Channel 1 */
        FMKTIM_INTERRUPT_LINE_IO_101,                      /**< General Purpose Timer, Reference to Timer 20 Channel 1 */
        FMKTIM_INTERRUPT_LINE_IO_102,                      /**< General Purpose Timer, Reference to Timer 20 Channel 2 */
        FMKTIM_INTERRUPT_LINE_IO_103,                      /**< General Purpose Timer, Reference to Timer 20 Channel 3 */
        FMKTIM_INTERRUPT_LINE_IO_104,                      /**< General Purpose Timer, Reference to Timer 20 Channel 4 */
    
        FMKTIM_INTERRUPT_LINE_IO_NB,
    } t_eFMKTIM_InterruptLineIO;

    /**
    * @brief Number of Event Purpose Interrupt Line.
    */
    typedef enum
    {
        FMKTIM_INTERRUPT_LINE_EVNT_1 = 0x0,                  /**< Event Purpose Timer, Reference to Timer 6 Channel 1 */
        FMKTIM_INTERRUPT_LINE_EVNT_2,                        /**< Event Purpose Timer, Reference to Timer 7 Channel 1 */
    
        FMKTIM_INTERRUPT_LINE_EVNT_NB,
    } t_eFMKTIM_InterruptLineEvnt;

    /**
    * @brief Number of DAC Purpose Interrupt Line.
    */
    typedef enum
    {
    
        FMKTIM_INTERRUPT_LINE_DAC_NB,
    } t_eFMKTIM_InterruptLineDAC;

    /* CAUTION : Automatic generated code section for Enum: End */
    
    typedef enum 
    {
        FMKTIM_BSP_CB_PERIOD_ELAPSED = 0x00,
        FMKTIM_BSP_CB_IC_CAPTURE,
        FMKTIM_BSP_CB_OC_DELAY_ELAPSED,
        FMKTIM_BSP_CB_PWM_PULSE_FINISHED,

        FMKTIM_BSP_CB_NB,
    } t_eFMKTIM_BspEvent;
    /**< Enum  for channel state */
    typedef enum
    {
        FMKTIM_CHNLST_DISACTIVATED = 0x0U,       /**< the channel is disactivated by software, not running */
        FMKTIM_CHNLST_ACTIVATED,                 /**< The channel is acitvated by software, is running */

        FMKTIM_CHNLST_NB                         /**< Number of channel state */
    } t_eFMKTIM_ChnlState;
    

    /**< Enum for channel run mode */
    typedef enum 
    {
        FMKTIM_LINE_RUNMODE_POLLING = 0x0U,     /**< The channel is running in polling mode (standard mode) */
        FMKTIM_LINE_RUNMODE_INTERRUPT,          /**< The channel is running in interrupt mode, which means HAL error callback is active,
                                                 among other things*/
        FMKTIM_LINE_RUNMODE_DMA,                /**< The channel is running in DMA Mode */

        FMKTIM_LINE_RUNMODE_NB                  /**< Number of channel run mode take in charge (DMA currently not available) */
    } t_eFMKTIM_ChnlRunMode; 
    //-----------------------------TYPEDEF TYPES---------------------------//
    /**
    *
    *	@brief  Call back function for channels
    *
    *	@param[in]      f_timer_e : timer channel 
    *	@param[out]     f_channel_e : channel which make the interruption
    *	 
    *
    */
   typedef void (t_cbFMKTIM_InterruptLine)(t_eFMKTIM_InterruptLineType f_InterruptType_e, t_uint8 f_InterruptLine_u8);

    typedef struct 
    {
        t_uint32 * BufferAdd1_pu32; /**< Dma Buffer Address 1 */
        t_uint32 * BufferAdd2_pu32; /**< Dma Buffer Address 2 */
        t_uint16 bufferLen_u16;
        t_eFMKCPU_DmaRqst RqstId_e;
    } t_sFMKTIM_ChnlDmaInfo;
    /**< Structure of information on a timer-channel*/
    typedef struct
    {
        t_eFMKTIM_ChnlState State_e;                        /**< State of the channel */
        t_eFMKTIM_ChnlRunMode RunMode_e;                    /**< Run mode for the channel */
        t_sFMKTIM_ChnlDmaInfo DmaInfo_ps;
        t_uint16 ErrState_u16;                /**< Error state of the channel */
        t_cbFMKTIM_InterruptLine *chnl_cb;                  /**< Callback function of the channel */
        t_bool IsChnlConfigure_b;                           /**< Wether or not the channel has beeen configured */
        
    } t_sFMKTIM_ChnlInfo;

    /**< Structure of information on a timer*/
    typedef struct
    {
        TIM_HandleTypeDef bspTimer_s;                       /**< The Timer structure for HAL STM32*/
        t_eFMKTIM_HwTimerCfg HwCfg_e;                       /**< The hardware configuration of the timer */
        t_sFMKTIM_ChnlInfo Channel_as[FMKTIM_CHANNEL_NB];   /**< Channels info structure */
        const t_eFMKCPU_IRQNType c_IRQNType_e;              /**< IRQN type related to the timer */
        const t_eFMKCPU_ClockPort c_clock_e;                /**< RCC clock related to the timer */
        t_uint16 timerFreqMHz_u32;                              /**< Timer frequency in Mhz */
        t_uint16 mskChnlState_u16;
        //const t_eFMKCPU_DmaRqst c_RqstDma_e;               /**< RCC clock related to the timer */
        t_bool IsTimerRunning_b;                            /**< Flag for timer is runnning */
        t_bool isConfigured_b;                              /**< flag timer is configured */  
        t_bool IsNVICTimerEnable_b;                         /**< flag timer NVCIC enable or not */
        t_bool ignoreInterrupt_b;                            /**< Flag to ignore interruption */

    } t_sFMKTIM_TimerInfo;
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // FMKTIM_CONFIGPUBLIC_H_INCLUDED           
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
