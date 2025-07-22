/*********************************************************************
 * @file        FMKTIM_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKHRT_CONFIGPRIVATE_H_INCLUDED
#define FMKHRT_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "../FMKCFG_ConfigSpecific/FMKHRT_ConfigSpecific.h"
    #include "../FMKCFG_ConfigFiles/FMKHRT_ConfigPublic.h"
    
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define FMKHRT_BASIC_CALIBRATION HRTIM_SINGLE_CALIBRATION /**< calibration of the timer done in 0.771 sec */
    /**
    * @brief Min ARR Value for PWM 
    */
    #define FMKHRT_PWM_MIN_ARR_VALUE ((t_uint32)1024)
    /**
    * @brief Min ARR Value for PWM 
    */
    #define FMKHRT_PWM_MAX_ARR_VALUE ((t_uint32)64000)
    // ********************************************************************
    // *                      Types
    // ********************************************************************



    /**
    * @brief High Resolution Timer Hardware Mode for a slave timer.
    */
    typedef enum 
    {
        FMKHRT_HW_OPE_TIM_BASIC = 0x00,         /**< the slave timer is configured as a Basic timer */
        FMKHRT_HW_OPE_TIM_PWM,                  /**< the slave timer is configured as a PWM timer */
        FMKHRT_HW_OPE_TIM_OC,                   /**< the slave timer is configured as a PWM timer */
        FMKHRT_HW_OPE_TIM_CC,                   /**< the slave timer is configured as a Capture Compare timer */
        FMKHRT_HW_OPE_TIM_OP,                   /**< the slave timer is configured as a One pulse timer */
        FMKHRT_HW_OPE_TIM_WFC,                  /**< the slave timer is configured as a Waveform Complex timer */

        FMKHRT_HW_OPE_TIM_NB,                   /**< Number of Slave Timer Hardware Operation Mode */
    } t_eFMKHRT_HwOpeTimer;

    /* CAUTION : Automatic generated code section for Enum: End */
   /**
    *
    *	@brief    High Resolution timer Hardware Operation in Polling Mode
    *
    *	@param[in]  f_bspIstc_ps             : Instance of the HRTIM
    *	@param[in]  f_timerIdx_u32           : Timer Idx A,B,C etc
    *	@param[in]  f_timerChnl_u32          : Timer Chnl 1,2
    */
    typedef HAL_StatusTypeDef (t_cbFMKHRT_HwOpePolling)(HRTIM_HandleTypeDef * f_bspIstc_ps,
                                                        t_uint32 f_timerIdx_u32,
                                                        t_uint32 f_timerChnl_u32);
       /**
    *
    *	@brief    High Resolution timer Hardware Operation in Interrupt Mode
    *
    *	@param[in]  f_bspIstc_ps             : Instance of the HRTIM
    *	@param[in]  f_timerIdx_u32           : Timer Idx A,B,C etc
    *	@param[in]  f_timerChnl_u32          : Timer Chnl 1,2
    */
    typedef HAL_StatusTypeDef (t_cbFMKHRT_HwOpeInterrupt)(  HRTIM_HandleTypeDef * f_bspIstc_ps,
                                                            t_uint32 f_timerIdx_u32,
                                                            t_uint32 f_timerChnl_u32);
    /**
    *
    *	@brief    High Resolution timer Hardware Operation in Polling Mode
    *
    *	@param[in]  f_bspIstc_ps             : Instance of the HRTIM
    *	@param[in]  f_timerIdx_u32           : Timer Idx A,B,C etc
    *	@param[in]  f_timerChnl_u32          : Timer Chnl 1,2
    *	@param[in]  f_srcAddress_u32         : DMA Source Address
    *	@param[in]  f_destAddress_u32        : DMA Destination Address
    *	@param[in]  f_destAddress_u32        : DMA Size 
    */
    typedef HAL_StatusTypeDef (t_cbFMKHRT_HwOpeDMA)(HRTIM_HandleTypeDef * f_bspIstc_ps,
                                                    t_uint32 f_timerIdx_u32,
                                                    t_uint32 f_timerChnl_u32,
                                                    t_uint32 f_srcAddress_u32,
                                                    t_uint32 f_destAddress_u32,
                                                    t_uint32 f_size_u32);
   
    //-----------------------------STRUCT TYPES---------------------------//
    /**
     * @brief Structure that contains every Hardware Ope Mode.
    */
    typedef struct 
    {
        t_cbFMKHRT_HwOpePolling     * HwOpePoll_pcb;        /**< Hardware Ope Mode for Timer in Polling way */
        t_cbFMKHRT_HwOpeInterrupt   * HwOpeIT_pcb;          /**< Hardware Ope Mode for Timer in Interrupt way */
        t_cbFMKHRT_HwOpeDMA         * HwOpeDMA_pcb;         /**< Hardware Ope Mode for Timer in DMA way */
    } t_sFMKHRT_HwOpeMode;

    /**
     * @brief Structure that contains every Hardware Ope Mode.
    */
    typedef struct 
    {
        t_sFMKHRT_HwOpeMode HwOpeStart_apf[FMKHRT_HW_OPE_TIM_NB];         /**< Array of Function that contains the Hw Ope Mode to start a timer  */
        t_sFMKHRT_HwOpeMode HwOpeStop_apf[FMKHRT_HW_OPE_TIM_NB];          /**< Array of Function that contains the Hw Ope Mode to stop a timer  */
    } t_sFMKHRT_HwOpeState;

    /**
     * @brief Structure for High Resolution TImer Cfg.
    */
   typedef struct 
   {
        HRTIM_TypeDef * bspItsc_ps;
        const t_eFMKCPU_ClockPort c_clkPort_e;
        const t_eFMKCPU_IRQNType c_MasterIRQNType_e;
        const t_eFMKCPU_IRQNType c_SlaveTimIRQNType_ae[FMKHRT_HRTIM_SLAVE_NB];
   } t_sFMKHRT_HrTimerCfg;
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    // **********²**********************************************************
    // *                      Prototypes
    // ********************************************************************

    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /**
     * @brief Variable that contains the address of the function for set (start & stop) a timer_channel.
     */
    const t_sFMKHRT_HwOpeState c_FMKHRT_HwOpe_apf = {
        .HwOpeStart_apf = {
            [FMKHRT_HW_OPE_TIM_BASIC] = {
                .HwOpePoll_pcb = FMKHRT_HAL_HRTIM_SimpleBaseStart,
                .HwOpeIT_pcb   = FMKHRT_HAL_HRTIM_SimpleBaseStart_IT,
                .HwOpeDMA_pcb  = FMKHRT_HAL_HRTIM_SimpleBaseStart_DMA,
            },
            [FMKHRT_HW_OPE_TIM_PWM] = {
                .HwOpePoll_pcb = HAL_HRTIM_SimplePWMStart,
                .HwOpeIT_pcb   = HAL_HRTIM_SimplePWMStart,
                .HwOpeDMA_pcb  = HAL_HRTIM_SimplePWMStart_DMA,
            },
            [FMKHRT_HW_OPE_TIM_OC] = {
                .HwOpePoll_pcb = HAL_HRTIM_SimpleOCStart,
                .HwOpeIT_pcb   = HAL_HRTIM_SimpleOCStart_IT,
                .HwOpeDMA_pcb  = HAL_HRTIM_SimpleOCStart_DMA,
            },
            [FMKHRT_HW_OPE_TIM_CC] = {
                .HwOpePoll_pcb = HAL_HRTIM_SimpleCaptureStart,
                .HwOpeIT_pcb   = HAL_HRTIM_SimpleCaptureStart_IT,
                .HwOpeDMA_pcb  = HAL_HRTIM_SimpleCaptureStart_DMA,
            },
            [FMKHRT_HW_OPE_TIM_OP] = {
                .HwOpePoll_pcb = HAL_HRTIM_SimpleOnePulseStart,
                .HwOpeIT_pcb   = HAL_HRTIM_SimpleOnePulseStart_IT,
                .HwOpeDMA_pcb  = (t_cbFMKHRT_HwOpeDMA *)NULL_FUNCTION,
            },
            [FMKHRT_HW_OPE_TIM_WFC] = {
                .HwOpePoll_pcb = FMKHRT_HAL_HRTIM_WaveformStart,
                .HwOpeIT_pcb   = FMKHRT_HAL_HRTIM_WaveformStart_IT,
                .HwOpeDMA_pcb  = FMKHRT_HAL_HRTIM_WaveformStart_DMA,
            },
        },

        .HwOpeStop_apf = {
            [FMKHRT_HW_OPE_TIM_BASIC] = {
                .HwOpePoll_pcb = FMKHRT_HAL_HRTIM_SimpleBaseStop,
                .HwOpeIT_pcb   = FMKHRT_HAL_HRTIM_SimpleBaseStop_IT,
                .HwOpeDMA_pcb  = FMKHRT_HAL_HRTIM_SimpleBaseStop_DMA,
            },
            [FMKHRT_HW_OPE_TIM_PWM] = {
                .HwOpePoll_pcb = HAL_HRTIM_SimplePWMStop,
                .HwOpeIT_pcb   = HAL_HRTIM_SimplePWMStop,
                .HwOpeDMA_pcb  = FMKHRT_HAL_HRTIM_SimplePWMStop_DMA,
            },
            [FMKHRT_HW_OPE_TIM_OC] = {
                .HwOpePoll_pcb = HAL_HRTIM_SimpleOCStop,
                .HwOpeIT_pcb   = HAL_HRTIM_SimpleOCStop_IT,
                .HwOpeDMA_pcb  = FMKHRT_HAL_HRTIM_SimpleOCStop_DMA,
            },
            [FMKHRT_HW_OPE_TIM_CC] = {
                .HwOpePoll_pcb = HAL_HRTIM_SimpleCaptureStop,
                .HwOpeIT_pcb   = HAL_HRTIM_SimpleCaptureStop_IT,
                .HwOpeDMA_pcb  = FMKHRT_HAL_HRTIM_SimpleCaptureStop_DMA,
            },
            [FMKHRT_HW_OPE_TIM_OP] = {
                .HwOpePoll_pcb = HAL_HRTIM_SimpleOnePulseStop,
                .HwOpeIT_pcb   = HAL_HRTIM_SimpleOnePulseStop_IT,
                .HwOpeDMA_pcb  = (t_cbFMKHRT_HwOpeDMA *)NULL_FUNCTION,
            },
            [FMKHRT_HW_OPE_TIM_WFC] = {
                .HwOpePoll_pcb = FMKHRT_HAL_HRTIM_WaveformStop,
                .HwOpeIT_pcb   = FMKHRT_HAL_HRTIM_WaveformStop_IT,
                .HwOpeDMA_pcb  = FMKHRT_HAL_HRTIM_WaveformStop_DMA,
            },
        },
    };
    /* CAUTION : Automatic generated code section for Variable: Start */
/**<  High Resolution Timer Cfg */
const t_sFMKHRT_HrTimerCfg c_FmkHrt_HrTimCfg_as[FMKHRT_HIGH_RES_TIMER_NB] = {
    [FMKHRT_HIGH_RES_TIMER_1] = {
        .bspItsc_ps = HRTIM1,
        .c_clkPort_e = FMKCPU_RCC_CLK_HRTIM1,
        .c_MasterIRQNType_e = FMKCPU_NVIC_HRTIM1_MASTER_IRQN,
            .c_SlaveTimIRQNType_ae = {
                [FMKHRT_HRTIM_SLAVE_1] = FMKCPU_NVIC_HRTIM1_TIMA_IRQN,
                [FMKHRT_HRTIM_SLAVE_2] = FMKCPU_NVIC_HRTIM1_TIMB_IRQN,
                [FMKHRT_HRTIM_SLAVE_3] = FMKCPU_NVIC_HRTIM1_TIMC_IRQN,
                [FMKHRT_HRTIM_SLAVE_4] = FMKCPU_NVIC_HRTIM1_TIMD_IRQN,
                [FMKHRT_HRTIM_SLAVE_5] = FMKCPU_NVIC_HRTIM1_TIME_IRQN,
                [FMKHRT_HRTIM_SLAVE_6] = FMKCPU_NVIC_HRTIM1_TIMF_IRQN,
            }
    },
};
    /**< Interrupt Line/Channel Mapping for  High Resolution Line */
    const t_eFMKHRT_HighResLine c_FMkHrt_ChnlLineMapp_ae[FMKHRT_HIGH_RES_TIMER_NB][FMKHRT_HRTIM_SLAVE_NB][FMKHRT_HRTIM_CHANNEL_NB] = {
    [FMKHRT_HIGH_RES_TIMER_1] = {
            [FMKHRT_HRTIM_SLAVE_1] = {
                FMKHRT_HR_LINE_1,
                FMKHRT_HR_LINE_2,
            },
            [FMKHRT_HRTIM_SLAVE_2] = {
                FMKHRT_HR_LINE_3,
                FMKHRT_HR_LINE_4,
            },
            [FMKHRT_HRTIM_SLAVE_3] = {
                FMKHRT_HR_LINE_5,
                FMKHRT_HR_LINE_6,
            },
            [FMKHRT_HRTIM_SLAVE_4] = {
                FMKHRT_HR_LINE_7,
                FMKHRT_HR_LINE_8,
            },
            [FMKHRT_HRTIM_SLAVE_5] = {
                FMKHRT_HR_LINE_9,
                FMKHRT_HR_LINE_10,
            },
            [FMKHRT_HRTIM_SLAVE_6] = {
                FMKHRT_HR_LINE_11,
                FMKHRT_HR_LINE_12,
            },
        },
    };
    /* CAUTION : Automatic generated code section for Variable: End */

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    /* CAUTION : Automatic generated code section for IRQ Handler: Start */
    void HRTIM1_TIMA_IRQHandler(void)
    {
        HAL_HRTIM_IRQHandler(   FMKHRT_PRIVATE_GetHandleTypeDef(FMKHRT_HIGH_RES_TIMER_1),
                                HRTIM_TIMERINDEX_TIMER_A);
        return;
    }
    void HRTIM1_TIMB_IRQHandler(void)
    {
        HAL_HRTIM_IRQHandler(   FMKHRT_PRIVATE_GetHandleTypeDef(FMKHRT_HIGH_RES_TIMER_1),
                                HRTIM_TIMERINDEX_TIMER_B);
        return;
    }
    void HRTIM1_TIMC_IRQHandler(void)
    {
        HAL_HRTIM_IRQHandler(   FMKHRT_PRIVATE_GetHandleTypeDef(FMKHRT_HIGH_RES_TIMER_1),
                                HRTIM_TIMERINDEX_TIMER_C);
        return;
    }
    void HRTIM1_TIMD_IRQHandler(void)
    {
        HAL_HRTIM_IRQHandler(   FMKHRT_PRIVATE_GetHandleTypeDef(FMKHRT_HIGH_RES_TIMER_1),
                                HRTIM_TIMERINDEX_TIMER_D);
        return;
    }
    void HRTIM1_TIME_IRQHandler(void)
    {
        HAL_HRTIM_IRQHandler(   FMKHRT_PRIVATE_GetHandleTypeDef(FMKHRT_HIGH_RES_TIMER_1),
                                HRTIM_TIMERINDEX_TIMER_E);
        return;
    }
    void HRTIM1_TIMF_IRQHandler(void)
    {
        HAL_HRTIM_IRQHandler(   FMKHRT_PRIVATE_GetHandleTypeDef(FMKHRT_HIGH_RES_TIMER_1),
                                HRTIM_TIMERINDEX_TIMER_F);
        return;
    }
    void HRTIM1_Master_IRQHandler(void)
    {
        HAL_HRTIM_IRQHandler(   FMKHRT_PRIVATE_GetHandleTypeDef(FMKHRT_HIGH_RES_TIMER_1),
                                HRTIM_TIMERINDEX_MASTER);
        return;
    }
    /* CAUTION : Automatic generated code section for IRQ Handler: Stop */
#endif // FMKHRT_CONFIGPRIVATE_H_INCLUDED
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
