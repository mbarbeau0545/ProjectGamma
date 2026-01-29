    /*********************************************************************
 * @file        FMKCPU_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKCPU_CONFIGPRIVATE_H_INCLUDED
#define FMKCPU_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "../FMKCFG_ConfigSpecific/FMKCPU_ConfigSpecific.h"
    #include "./FMKCPU_ConfigPublic.h"
    #include "FMK_HAL/FMK_CDA/Src/FMK_CDA.h"
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    ///@brief supply voltage and temp Cpu monitoring, put FMKCDA_ADC_INTERN_NB
    ///         if the intern sens does not exist.
    #define FMKPCU_ADC_INTERN_SNS_VBAT (FMKCDA_ADC_INTERN_VBAT)
    #define FMKPCU_ADC_INTERN_SNS_TEMP (FMKCDA_ADC_INTERN_TS_CAL1)

    ///@brief max/min treshold for vbatterie 
    #define FMKCPU_VBAT_TRESHOLD_MIN ((t_float32)2900.0f) // mV
    #define FMKCPU_VBAT_TRESHOLD_MAX ((t_float32)3500.0f) // mV

    ///@brief max/min treshold for Temperature
    #define FMKCPU_CPU_TEMP_TRESHOLD_MIN    ((t_float32)-20.0f)
    #define FMKCPU_CPU_TEMP_TRESHOLD_MAX    ((t_float32)60.0f)
    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //----------------------------Enum -----------------------//
    #if defined(FMKCPU_STM32_ECU_FAMILY_G4)
        /// @brief Mapping for dma channel configuration
        typedef DMA_Channel_TypeDef FMKCPU_DmaChnlTypeDef;

        /// @brief Mapping for whatchfog instance
        #define FMKCPU_WWDG_INSTANCE            ((IWDG_TypeDef *)WWDG)

        /// @brief Mapping for freeze wathdog during breakpoint
        #define FMKPCU_DISABLE_WWDG_DEBUG()       __HAL_DBGMCU_FREEZE_IWDG()

        ///@brief Controle Voltage Scaling 
        #define FMKCPU_CTRL_VOLTAGE_SCALING     (PWR_REGULATOR_VOLTAGE_SCALE1)
    #elif defined(FMKCPU_STM32_ECU_FAMILY_H7)
        /// @brief Mapping for dma channel configuration
        typedef DMA_Stream_TypeDef FMKCPU_DmaChnlTypeDef;

        /// @brief Mapping for whatchfog instance
        #define FMKCPU_WWDG_INSTANCE            (WWDG1)

        /// @brief Mapping for freeze wathdog during breakpoint
        #define FMKPCU_DISABLE_WWDG_DEBUG()       __HAL_DBGMCU_FREEZE_IWDG1()

        ///@brief Controle Voltage Scaling 
        #define FMKCPU_CTRL_VOLTAGE_SCALING     (PWR_REGULATOR_VOLTAGE_SCALE0)
    #else
        #error "FMKCDA_ADC_VBAT_MULTPIPLIER non défini : définir FMKCPU_STM32_ECU_FAMILY_G4 ou H7"
    #endif

    /**< Structure for Hardware Dma Configuration for a request type */
    typedef struct 
    {
        t_eFMKCPU_DmaController         Ctrl_e;
        t_eFMKCPU_DmaChnl               Chnl_e;
        t_eFMKCPU_DmaTransferPriority   transfPrio_e;
    } t_sFMKCPU_DmaRqstCfg;

    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */

    /**
    *
    *	@brief      HAL enable clock Function abstraction
    *	@note       This function repertory in stm32f00xx_hal_tim,
    *               is used in blocking mode 
    *
    *
    *	@param[in]      f_handleTimer_s : the bsp config structure 
    *	@param[out]     f_channel_u32   : the channel 
    *	 
    *
    *
    */
    typedef void (t_cbFMKCPU_ClockEnable)(void);
    /**
    *
    *	@brief      HAL Disable clock Function abstraction
    *	@note       This function repertory in stm32f00xx_hal_tim,
    *               is used in blocking mode 
    *
    *
    *	@param[in]      f_handleTimer_s : the bsp config structure 
    *	@param[out]     f_channel_u32   : the channel 
    *	 
    *
    *
    */
    typedef void (t_cbFMKCPU_ClockDisable)(void);

    

    //-----------------------------STRUCT TYPES---------------------------//
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */
    /**< Structure for Dma Channel Configuration */
    typedef struct 
    {
        FMKCPU_DmaChnlTypeDef * Instance;
        t_eFMKCPU_IRQNType c_IRQNType_e;
    } t_sFMKCPU_DmaChnlCfg;
    /**< Structure for Dma Configuration */
    typedef struct 
    {
        t_eFMKCPU_ClockPort c_clock_e;
        t_sFMKCPU_DmaChnlCfg chnlCfg_as[FMKCPU_DMA_CHANNEL_NB];
    } t_sFMKCPU_DmaCfg;
    /**< Structure for repertory all clock enable/disable function */
    typedef struct
    {
        t_cbFMKCPU_ClockEnable  * EnableClk_pcb;        /**< HAL_TIM function to enable rcc clock */
        t_cbFMKCPU_ClockDisable * DisableClk_pcb;       /**< HAL_TIM function to disable rcc clock */
    }t_sFMKCPU_ClkFunc;

    /**< Structure for watchdog configuration */
    typedef struct 
    {
        t_uint16 psc_u16;           /**< variable for wacthdog timer prescaler value */
        t_uint16 reload_u16;        /**< variable for wacthdog timer ARR value */
    } t_sFMKCPU_BspWwdgCfg;
    
    // **********²**********************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
#ifdef FMKCPU_STM32_ECU_FAMILY_G4
    //---------Configuration Clock System---------------------------//
    const t_sFMKCPU_PllOscCfg c_FmkCpu_Pll1OscCfg_as[FMKCPU_CORE_CLOCK_SPEED_NB]= {
    //  PLLM_Divider_u32         PPLN_Multplier_u32         PLLR_Divider_u32        PLLQ_Divider_u32         PLLP_Divider_u32
        {RCC_PLLM_DIV2,         (t_uint32)12,                RCC_PLLR_DIV8,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV2},
        {RCC_PLLM_DIV4,         (t_uint32)16,                RCC_PLLR_DIV6,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV2},
        {RCC_PLLM_DIV4,         (t_uint32)48,                RCC_PLLR_DIV6,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV4},
        {RCC_PLLM_DIV4,         (t_uint32)60,                RCC_PLLR_DIV6,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV6},
        {RCC_PLLM_DIV4,         (t_uint32)72,                RCC_PLLR_DIV6,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV6},
        {RCC_PLLM_DIV4,         (t_uint32)64,                RCC_PLLR_DIV4,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV6},
        {RCC_PLLM_DIV3,         (t_uint32)60,                RCC_PLLR_DIV4,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV8},
        {RCC_PLLM_DIV3,         (t_uint32)24,                RCC_PLLR_DIV2,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV4},
        {RCC_PLLM_DIV1,         (t_uint32)16,                RCC_PLLR_DIV2,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV6},
        {RCC_PLLM_DIV1,         (t_uint32)20,                RCC_PLLR_DIV2,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV8},
    };
    const t_sFMKCPU_SysOscCfg c_FmkCpu_SysOscCfg_as[FMKCPU_CORE_CLOCK_SPEED_NB] = {
    //   AHB_Divider_u32              APB1_Divider_u32        APB2_Divider_u32
        {RCC_SYSCLK_DIV1,             RCC_HCLK_DIV1,          RCC_HCLK_DIV1}, // FMKCPU_CORE_CLOCK_SPEED_8MHZ
        {RCC_SYSCLK_DIV1,             RCC_HCLK_DIV1,          RCC_HCLK_DIV1}, //  FMKCPU_CORE_CLOCK_SPEED_16MHZ
        {RCC_SYSCLK_DIV1,             RCC_HCLK_DIV1,          RCC_HCLK_DIV1}, //  FMKCPU_CORE_CLOCK_SPEED_32MHZ
        {RCC_SYSCLK_DIV1,             RCC_HCLK_DIV1,          RCC_HCLK_DIV1}, //  FMKCPU_CORE_CLOCK_SPEED_40MHZ
        {RCC_SYSCLK_DIV1,             RCC_HCLK_DIV1,          RCC_HCLK_DIV1}, //  FMKCPU_CORE_CLOCK_SPEED_48MHZ
        {RCC_SYSCLK_DIV1,             RCC_HCLK_DIV1,          RCC_HCLK_DIV1}, //  FMKCPU_CORE_CLOCK_SPEED_64MHZ
        {RCC_SYSCLK_DIV1,             RCC_HCLK_DIV2,          RCC_HCLK_DIV2}, //  FMKCPU_CORE_CLOCK_SPEED_80MHZ
        {RCC_SYSCLK_DIV1,             RCC_HCLK_DIV2,          RCC_HCLK_DIV2}, //  FMKCPU_CORE_CLOCK_SPEED_96MHZ
        {RCC_SYSCLK_DIV1,             RCC_HCLK_DIV2,          RCC_HCLK_DIV2}, //  FMKCPU_CORE_CLOCK_SPEED_128MHZ
        {RCC_SYSCLK_DIV1,             RCC_HCLK_DIV2,          RCC_HCLK_DIV2}, //  FMKCPU_CORE_CLOCK_SPEED_160MHZ
    };

    const t_uint8 c_FmkCpu_CoreClkValue_ua8[FMKCPU_CORE_CLOCK_SPEED_NB][FMKCPU_SYS_CLOCK_NB] = 
    {//    HSE                                      HSI                             SYSTEM                           HCLK1                         AHB1                          AHB2                       APB1/PCLK1                      APB2/PCLK2                   PLLQ                          PLLP 
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)12,                   (t_uint8)12,                    (t_uint8)12,                 (t_uint8)12,                 (t_uint8)12,                    (t_uint8)12,                  (t_uint8)48,                  (t_uint8)48},  //  FMKCPU_CORE_CLOCK_SPEED_8MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)16,                   (t_uint8)16,                    (t_uint8)16,                 (t_uint8)16,                 (t_uint8)16,                    (t_uint8)16,                  (t_uint8)64,                  (t_uint8)42},  //  FMKCPU_CORE_CLOCK_SPEED_16MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)32,                   (t_uint8)32,                    (t_uint8)32,                 (t_uint8)32,                 (t_uint8)32,                    (t_uint8)32,                  (t_uint8)96,                  (t_uint8)48},  //  FMKCPU_CORE_CLOCK_SPEED_32MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)40,                   (t_uint8)40,                    (t_uint8)40,                 (t_uint8)40,                 (t_uint8)40,                    (t_uint8)40,                  (t_uint8)120,                 (t_uint8)40},  //  FMKCPU_CORE_CLOCK_SPEED_40MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)48,                   (t_uint8)48,                    (t_uint8)48,                 (t_uint8)48,                 (t_uint8)48,                    (t_uint8)48,                  (t_uint8)144,                 (t_uint8)48},  //  FMKCPU_CORE_CLOCK_SPEED_48MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)64,                   (t_uint8)64,                    (t_uint8)64,                 (t_uint8)64,                 (t_uint8)64,                    (t_uint8)64,                  (t_uint8)128,                 (t_uint8)42},  //  FMKCPU_CORE_CLOCK_SPEED_64MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)80,                   (t_uint8)80,                    (t_uint8)80,                 (t_uint8)80,                 (t_uint8)40,                    (t_uint8)40,                  (t_uint8)160,                 (t_uint8)40},  //  FMKCPU_CORE_CLOCK_SPEED_80MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)96,                   (t_uint8)96,                    (t_uint8)96,                 (t_uint8)96,                 (t_uint8)48,                    (t_uint8)48,                  (t_uint8)96,                  (t_uint8)48},  //  FMKCPU_CORE_CLOCK_SPEED_96MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)128,                  (t_uint8)128,                   (t_uint8)128,                (t_uint8)128,                (t_uint8)64,                    (t_uint8)64,                  (t_uint8)128,                 (t_uint8)42},  //  FMKCPU_CORE_CLOCK_SPEED_128MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)160,                  (t_uint8)160,                   (t_uint8)160,                (t_uint8)160,                (t_uint8)80,                    (t_uint8)80,                  (t_uint8)160,                 (t_uint8)40},  //  FMKCPU_CORE_CLOCK_SPEED_160MHZ
    };

    ///@brief variable to store the other configuration from pll
    t_sFMKCPU_PllOscCfg * c_FmkCpu_PllOtherCfg_as[FMKCPU_CORE_CLOCK_SPEED_NB]= {
        [FMKCPU_CORE_CLOCK_SPEED_8MHZ]   = NULL,
        [FMKCPU_CORE_CLOCK_SPEED_16MHZ]  = NULL,
        [FMKCPU_CORE_CLOCK_SPEED_32MHZ]  = NULL,
        [FMKCPU_CORE_CLOCK_SPEED_40MHZ]  = NULL,
        [FMKCPU_CORE_CLOCK_SPEED_48MHZ]  = NULL,
        [FMKCPU_CORE_CLOCK_SPEED_64MHZ]  = NULL,
        [FMKCPU_CORE_CLOCK_SPEED_80MHZ]  = NULL,
        [FMKCPU_CORE_CLOCK_SPEED_96MHZ]  = NULL,
        [FMKCPU_CORE_CLOCK_SPEED_128MHZ] = NULL,
        [FMKCPU_CORE_CLOCK_SPEED_160MHZ] = NULL,
    };

#elif defined(FMKCPU_STM32_ECU_FAMILY_H7)
    ///@brief PLL 1 Configuration
    const t_sFMKCPU_PllOscCfg c_FmkCpu_Pll1OscCfg_as[FMKCPU_CORE_CLOCK_SPEED_NB]= {
    //  PLLM_Divider_u32         PPLN_Multplier_u32         PLLR_Divider_u32        PLLQ_Divider_u32         PLLP_Divider_u32   PLL1RGE_Range_u32               PLL1VCOSEL_u32                  PLL1FRACN_u32
        {(t_uint32)4,               (t_uint32)12,                (t_uint32)2,        (t_uint32)2,            (t_uint32)2,       (t_uint32)RCC_PLL1VCIRANGE_3,   (t_uint32)RCC_PLL1VCOWIDE,      (t_uint32)4096}, //  FMKCPU_CORE_CLOCK_SPEED_100MHZ
        {(t_uint32)4,               (t_uint32)25,                (t_uint32)2,        (t_uint32)4,            (t_uint32)2,       (t_uint32)RCC_PLL1VCIRANGE_3,   (t_uint32)RCC_PLL1VCOWIDE,      (t_uint32)0}, //  FMKCPU_CORE_CLOCK_SPEED_200MHZ
        {(t_uint32)4,               (t_uint32)50,                (t_uint32)2,        (t_uint32)8,            (t_uint32)2,       (t_uint32)RCC_PLL1VCIRANGE_3,   (t_uint32)RCC_PLL1VCOWIDE,      (t_uint32)0}, //  FMKCPU_CORE_CLOCK_SPEED_400MHZ
        {(t_uint32)4,               (t_uint32)60,                (t_uint32)2,        (t_uint32)8,            (t_uint32)2,       (t_uint32)RCC_PLL1VCIRANGE_3,   (t_uint32)RCC_PLL1VCOWIDE,      (t_uint32)0}, //  FMKCPU_CORE_CLOCK_SPEED_480MHZ
    };

    ///@brief PLL 2 Configuration
    const t_sFMKCPU_PllOscCfg c_FmkCpu_Pll2OscCfg_as[FMKCPU_CORE_CLOCK_SPEED_NB]= {
    //  PLLM_Divider_u32         PPLN_Multplier_u32         PLLR_Divider_u32        PLLQ_Divider_u32         PLLP_Divider_u32   PLL1RGE_Range_u32    PLL1VCOSEL_u32         PLL1FRACN_u32
        {(t_uint32)4,         (t_uint32)10,                (t_uint32)2,             (t_uint32)1,            (t_uint32)2,        (t_uint32)2,        (t_uint32)2,            (t_uint32)2}, //  FMKCPU_CORE_CLOCK_SPEED_100MHZ
        {(t_uint32)4,         (t_uint32)10,                (t_uint32)2,             (t_uint32)1,            (t_uint32)2,        (t_uint32)2,        (t_uint32)4,            (t_uint32)2}, //  FMKCPU_CORE_CLOCK_SPEED_200MHZ
        {(t_uint32)4,         (t_uint32)10,                (t_uint32)2,             (t_uint32)1,            (t_uint32)2,        (t_uint32)2,        (t_uint32)8,            (t_uint32)2}, //  FMKCPU_CORE_CLOCK_SPEED_400MHZ
        {(t_uint32)4,         (t_uint32)10,                (t_uint32)2,             (t_uint32)1,            (t_uint32)2,        (t_uint32)2,        (t_uint32)8,            (t_uint32)2}, //  FMKCPU_CORE_CLOCK_SPEED_480MHZ
    };

    ///@brief PLL 3 Configuration
    const t_sFMKCPU_PllOscCfg c_FmkCpu_Pll3OscCfg_as[FMKCPU_CORE_CLOCK_SPEED_NB]= {
    //  PLLM_Divider_u32         PPLN_Multplier_u32         PLLR_Divider_u32        PLLQ_Divider_u32         PLLP_Divider_u32   PLL1RGE_Range_u32    PLL1VCOSEL_u32         PLL1FRACN_u32
        {(t_uint32)32,        (t_uint32)200,               (t_uint32)8,             (t_uint32)4,            (t_uint32)2,        (t_uint32)2,        (t_uint32)2,            (t_uint32)2}, //  FMKCPU_CORE_CLOCK_SPEED_100MHZ
        {(t_uint32)32,        (t_uint32)200,               (t_uint32)8,             (t_uint32)4,            (t_uint32)2,        (t_uint32)2,        (t_uint32)4,            (t_uint32)2}, //  FMKCPU_CORE_CLOCK_SPEED_200MHZ
        {(t_uint32)32,        (t_uint32)200,               (t_uint32)8,             (t_uint32)4,            (t_uint32)2,        (t_uint32)2,        (t_uint32)8,            (t_uint32)2}, //  FMKCPU_CORE_CLOCK_SPEED_400MHZ
        {(t_uint32)32,        (t_uint32)200,               (t_uint32)8,             (t_uint32)4,            (t_uint32)2,        (t_uint32)2,        (t_uint32)8,            (t_uint32)2}, //  FMKCPU_CORE_CLOCK_SPEED_480MHZ
    };

    /// @brief Sys oscillator main configuration
    const t_sFMKCPU_SysOscCfg c_FmkCpu_SysOscCfg_as[FMKCPU_CORE_CLOCK_SPEED_NB] = {
    //   SysClkDivider                AHB_Divider_u32                  APB1_Divider_u32        APB2_Divider_u32      APB3_Divider_u32        APB4_Divider_u32
        {RCC_SYSCLK_DIV1,             RCC_SYSCLK_DIV1,             RCC_HCLK_DIV1,          RCC_HCLK_DIV1,        RCC_HCLK_DIV1,          RCC_HCLK_DIV1}, // FMKCPU_CORE_CLOCK_SPEED_100MHZ
        {RCC_SYSCLK_DIV1,             RCC_SYSCLK_DIV1,             RCC_HCLK_DIV1,          RCC_HCLK_DIV2,        RCC_HCLK_DIV1,          RCC_HCLK_DIV1}, //  FMKCPU_CORE_CLOCK_SPEED_200MHZ
        {RCC_SYSCLK_DIV1,             RCC_SYSCLK_DIV2,             RCC_HCLK_DIV2,          RCC_HCLK_DIV2,        RCC_HCLK_DIV2,          RCC_HCLK_DIV2}, //  FMKCPU_CORE_CLOCK_SPEED_400MHZ
        {RCC_SYSCLK_DIV1,             RCC_SYSCLK_DIV2,             RCC_HCLK_DIV2,          RCC_HCLK_DIV2,        RCC_HCLK_DIV2,          RCC_HCLK_DIV2}, //  FMKCPU_CORE_CLOCK_SPEED_480MHZ
    };

    /// @brief Oscillator Clock value based on configuration below 
    const t_uint16 c_FmkCpu_CoreClkValue_ua8[FMKCPU_CORE_CLOCK_SPEED_NB][FMKCPU_SYS_CLOCK_NB] = 
    {//    HSE               HSI               SYSTEM              AHB1                   AHB2               AHB3                  AHB4                APB1                 APB2              APB3                 APB4                PLL1P                 PLL1Q            PLL1R               PLL2P              LL2Q             PLL2R                  PLL3P                 PLL3Q            PLL3R       
        {(t_uint16)8,    (t_uint16)16,     (t_uint16)200,      (t_uint16)100,       (t_uint16)100,       (t_uint16)100,       (t_uint16)100,       (t_uint16)50,        (t_uint16)50,    (t_uint16)50,        (t_uint16)50,        (t_uint16)100,       (t_uint16)100,   (t_uint16)100,       (t_uint16)80,        (t_uint16)160,   (t_uint16)80,         (t_uint16)200,       (t_uint16)100,   (t_uint16)50},  //  FMKCPU_CORE_CLOCK_SPEED_200MHZ
        {(t_uint16)8,    (t_uint16)16,     (t_uint16)400,      (t_uint16)200,       (t_uint16)200,       (t_uint16)200,       (t_uint16)200,       (t_uint16)100,       (t_uint16)100,   (t_uint16)100,       (t_uint16)100,       (t_uint16)400,       (t_uint16)100,   (t_uint16)400,       (t_uint16)80,        (t_uint16)160,   (t_uint16)80,         (t_uint16)200,       (t_uint16)100,   (t_uint16)50},  //  FMKCPU_CORE_CLOCK_SPEED_400MHZ
        {(t_uint16)8,    (t_uint16)16,     (t_uint16)480,      (t_uint16)240,       (t_uint16)240,       (t_uint16)240,       (t_uint16)240,       (t_uint16)120,       (t_uint16)120,   (t_uint16)120,       (t_uint16)120,       (t_uint16)480,       (t_uint16)120,   (t_uint16)480,       (t_uint16)80,        (t_uint16)180,   (t_uint16)80,         (t_uint16)200,       (t_uint16)100,   (t_uint16)50},  //  FMKCPU_CORE_CLOCK_SPEED_480MHZ
    };

    ///@brief variable to store the other configuration from pll
    const t_sFMKCPU_PllOscCfg * c_FmkCpu_PllOtherCfg_as[FMKCPU_CORE_CLOCK_SPEED_NB][FMKCPU_SYS_OSC_PLL_NB]= {
        [FMKCPU_CORE_CLOCK_SPEED_100MHZ] = {
            &c_FmkCpu_Pll2OscCfg_as[FMKCPU_CORE_CLOCK_SPEED_100MHZ], 
            &c_FmkCpu_Pll3OscCfg_as[FMKCPU_CORE_CLOCK_SPEED_100MHZ]
        },
        [FMKCPU_CORE_CLOCK_SPEED_200MHZ] = {
            &c_FmkCpu_Pll2OscCfg_as[FMKCPU_CORE_CLOCK_SPEED_200MHZ],
            &c_FmkCpu_Pll3OscCfg_as[FMKCPU_CORE_CLOCK_SPEED_200MHZ],
        },
        [FMKCPU_CORE_CLOCK_SPEED_400MHZ] = {
            &c_FmkCpu_Pll2OscCfg_as[FMKCPU_CORE_CLOCK_SPEED_400MHZ],
            &c_FmkCpu_Pll3OscCfg_as[FMKCPU_CORE_CLOCK_SPEED_400MHZ],
        },
        [FMKCPU_CORE_CLOCK_SPEED_480MHZ] = {
            &c_FmkCpu_Pll2OscCfg_as[FMKCPU_CORE_CLOCK_SPEED_480MHZ],
            &c_FmkCpu_Pll3OscCfg_as[FMKCPU_CORE_CLOCK_SPEED_480MHZ],
        }
    };
#elif defined FMKCPU_STM32_ECU_FAMILY_F
    const t_sFMKCPU_SysOscCfg c_FmkCpu_SysOscCfg_s = {
    // PLLM_Divider_u32         PPLN_Multplier_u32          PLLR_Divider_u32        PLLQ_Divider_u32         PLLP_Divider_u32            AHB_Divider_u32                  APB1_Divider_u32        APB2_Divider_u32
    };
    const t_uint8 c_FmkCpu_CoreClkValue_ua8[FMKCPU_SYS_CLOCK_NB] = 
    {
        (t_uint8)0,     // FMKCPU_SYS_CLOCK_HSI
        (t_uint8)0,    // FMKCPU_SYS_CLOCK_CORE
        (t_uint8)0,    // FMKCPU_SYS_CLOCK_HCLK
        (t_uint8)0,    // FMKCPU_SYS_CLOCK_APB1
        (t_uint8)0,    // FMKCPU_SYS_CLOCK_APB2
        (t_uint8)0,     // FMKCPU_SYS_CLOCK_PLLQ
        (t_uint8)0,     // FMKCPU_SYS_CLOCK_PLLP
    };
#endif

    /**< Hardware configuration watchdog Period Timer */
    const t_sFMKCPU_BspWwdgCfg c_FMKCPU_WwdgPeriodcfg_ua16[FMKCPU_WWDG_RESET_NB] = {
        // prescaler value         reload value
        {IWDG_PRESCALER_32,          49}, // FMKCPU_WWDG_RESET_50MS
        {IWDG_PRESCALER_32,          99}, // FMKCPU_WWDG_RESET_100MS
        {IWDG_PRESCALER_32,          199}, // FMKCPU_WWDG_RESET_200MS
        {IWDG_PRESCALER_32,          499},// FMKCPU_WWDG_RESET_500MS
    };

    /* CAUTION : Automatic generated code section for Variable: Start */
    /**< Variable to Dma Configuration */
    const t_sFMKCPU_DmaCfg c_FmkCpu_DmaCfg_as[FMKCPU_DMA_CTRL_NB] = {
        [FMKCPU_DMA_CTRL_1] = {
            .c_clock_e = FMKCPU_RCC_CLK_DMA1,
            .chnlCfg_as = {
                [FMKCPU_DMA_CHANNEL_1] = {
                    .Instance = DMA1_Channel1,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA1_CHANNEL1_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_2] = {
                    .Instance = DMA1_Channel2,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA1_CHANNEL2_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_3] = {
                    .Instance = DMA1_Channel3,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA1_CHANNEL3_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_4] = {
                    .Instance = DMA1_Channel4,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA1_CHANNEL4_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_5] = {
                    .Instance = DMA1_Channel5,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA1_CHANNEL5_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_6] = {
                    .Instance = DMA1_Channel6,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA1_CHANNEL6_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_7] = {
                    .Instance = DMA1_Channel7,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA1_CHANNEL7_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_8] = {
                    .Instance = DMA1_Channel8,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA1_CHANNEL8_IRQN,
                },

            },
        },
        [FMKCPU_DMA_CTRL_2] = {
            .c_clock_e = FMKCPU_RCC_CLK_DMA2,
            .chnlCfg_as = {
                [FMKCPU_DMA_CHANNEL_1] = {
                    .Instance = DMA2_Channel1,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA2_CHANNEL1_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_2] = {
                    .Instance = DMA2_Channel2,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA2_CHANNEL2_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_3] = {
                    .Instance = DMA2_Channel3,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA2_CHANNEL3_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_4] = {
                    .Instance = DMA2_Channel4,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA2_CHANNEL4_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_5] = {
                    .Instance = DMA2_Channel5,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA2_CHANNEL5_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_6] = {
                    .Instance = DMA2_Channel6,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA2_CHANNEL6_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_7] = {
                    .Instance = DMA2_Channel7,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA2_CHANNEL7_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_8] = {
                    .Instance = DMA2_Channel8,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA2_CHANNEL8_IRQN,
                },

            },
        },
    };

    /**< Set the NVIC Priority for all NVIC_IRqn Priority */
    const t_eFMKCPU_NVICPriority c_FMKCPU_IRQNPriority_ae[FMKCPU_NVIC_NB] = {
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  ADC1_2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  ADC3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  ADC4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  ADC5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  COMP1_2_3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  COMP4_5_6_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  COMP7_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  CORDIC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  CRS_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel6_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel7_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel8_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Channel1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Channel2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Channel3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Channel4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Channel5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Channel6_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Channel7_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Channel8_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMAMUX_OVR_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI0_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI15_10_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI9_5_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN1_IT0_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN1_IT1_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN2_IT0_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN2_IT1_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN3_IT0_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN3_IT1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  FLASH_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  FMAC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  FMC_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FPU_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  HRTIM1_FLT_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  HRTIM1_Master_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  HRTIM1_TIMA_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  HRTIM1_TIMB_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  HRTIM1_TIMC_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  HRTIM1_TIMD_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  HRTIM1_TIME_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  HRTIM1_TIMF_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C1_ER_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C1_EV_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C2_ER_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C2_EV_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C3_ER_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C3_EV_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C4_ER_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C4_EV_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  LPTIM1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  LPUART1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  PVD_PVM_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  QUADSPI_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  RCC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  RNG_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  RTC_Alarm_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  RTC_TAMP_LSECSS_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  RTC_WKUP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SAI1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPI1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPI2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPI3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPI4_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM1_BRK_TIM15_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM1_CC_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM1_TRG_COM_TIM17_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM1_UP_TIM16_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM2_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM20_BRK_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM20_CC_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM20_TRG_COM_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM20_UP_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM3_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM4_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM5_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM6_DAC_IRQn
        FMKCPU_NVIC_PRIORITY_LOW,                         //  TIM7_DAC_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM8_BRK_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM8_CC_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM8_TRG_COM_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM8_UP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  UART4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  UART5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  UCPD1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USART1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USART2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USART3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USB_HP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USB_LP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USBWakeUp_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  WWDG_IRQn
    };

    /**< Referencing all Enable/Disable Rcc clock function */
    const t_sFMKCPU_ClkFunc c_FMKCPU_ClkFunctions_apcb[FMKCPU_NVIC_NB] = {
        {FMKCPU_Enable_DMA1_Clock,      FMKCPU_Disable_DMA1_Clock},     // FMKCPU_RCC_CLK_DMA1
        {FMKCPU_Enable_DMA2_Clock,      FMKCPU_Disable_DMA2_Clock},     // FMKCPU_RCC_CLK_DMA2
        {FMKCPU_Enable_DMAMUX1_Clock,   FMKCPU_Disable_DMAMUX1_Clock},  // FMKCPU_RCC_CLK_DMAMUX1
        {FMKCPU_Enable_CORDIC_Clock,    FMKCPU_Disable_CORDIC_Clock},   // FMKCPU_RCC_CLK_CORDIC
        {FMKCPU_Enable_FMAC_Clock,      FMKCPU_Disable_FMAC_Clock},     // FMKCPU_RCC_CLK_FMAC
        {FMKCPU_Enable_FLASH_Clock,     FMKCPU_Disable_FLASH_Clock},    // FMKCPU_RCC_CLK_FLASH
        {FMKCPU_Enable_CRC_Clock,       FMKCPU_Disable_CRC_Clock},      // FMKCPU_RCC_CLK_CRC
        {FMKCPU_Enable_GPIOG_Clock,     FMKCPU_Disable_GPIOG_Clock},    // FMKCPU_RCC_CLK_GPIOG
        {FMKCPU_Enable_GPIOF_Clock,     FMKCPU_Disable_GPIOF_Clock},    // FMKCPU_RCC_CLK_GPIOF
        {FMKCPU_Enable_GPIOE_Clock,     FMKCPU_Disable_GPIOE_Clock},    // FMKCPU_RCC_CLK_GPIOE
        {FMKCPU_Enable_GPIOD_Clock,     FMKCPU_Disable_GPIOD_Clock},    // FMKCPU_RCC_CLK_GPIOD
        {FMKCPU_Enable_GPIOC_Clock,     FMKCPU_Disable_GPIOC_Clock},    // FMKCPU_RCC_CLK_GPIOC
        {FMKCPU_Enable_GPIOB_Clock,     FMKCPU_Disable_GPIOB_Clock},    // FMKCPU_RCC_CLK_GPIOB
        {FMKCPU_Enable_GPIOA_Clock,     FMKCPU_Disable_GPIOA_Clock},    // FMKCPU_RCC_CLK_GPIOA
        {FMKCPU_Enable_ADC12_Clock,     FMKCPU_Disable_ADC12_Clock},    // FMKCPU_RCC_CLK_ADC12
        {FMKCPU_Enable_ADC345_Clock,    FMKCPU_Disable_ADC345_Clock},   // FMKCPU_RCC_CLK_ADC345
        {FMKCPU_Enable_DAC1_Clock,      FMKCPU_Disable_DAC1_Clock},     // FMKCPU_RCC_CLK_DAC1
        {FMKCPU_Enable_DAC2_Clock,      FMKCPU_Disable_DAC2_Clock},     // FMKCPU_RCC_CLK_DAC2
        {FMKCPU_Enable_DAC3_Clock,      FMKCPU_Disable_DAC3_Clock},     // FMKCPU_RCC_CLK_DAC3
        {FMKCPU_Enable_DAC4_Clock,      FMKCPU_Disable_DAC4_Clock},     // FMKCPU_RCC_CLK_DAC4
        {FMKCPU_Enable_RNG_Clock,       FMKCPU_Disable_RNG_Clock},      // FMKCPU_RCC_CLK_RNG
        {FMKCPU_Enable_FMC_Clock,       FMKCPU_Disable_FMC_Clock},      // FMKCPU_RCC_CLK_FMC
        {FMKCPU_Enable_QSPI_Clock,      FMKCPU_Disable_QSPI_Clock},     // FMKCPU_RCC_CLK_QSPI
        {FMKCPU_Enable_TIM2_Clock,      FMKCPU_Disable_TIM2_Clock},     // FMKCPU_RCC_CLK_TIM2
        {FMKCPU_Enable_TIM3_Clock,      FMKCPU_Disable_TIM3_Clock},     // FMKCPU_RCC_CLK_TIM3
        {FMKCPU_Enable_TIM4_Clock,      FMKCPU_Disable_TIM4_Clock},     // FMKCPU_RCC_CLK_TIM4
        {FMKCPU_Enable_TIM5_Clock,      FMKCPU_Disable_TIM5_Clock},     // FMKCPU_RCC_CLK_TIM5
        {FMKCPU_Enable_TIM6_Clock,      FMKCPU_Disable_TIM6_Clock},     // FMKCPU_RCC_CLK_TIM6
        {FMKCPU_Enable_TIM7_Clock,      FMKCPU_Disable_TIM7_Clock},     // FMKCPU_RCC_CLK_TIM7
        {FMKCPU_Enable_CRS_Clock,       FMKCPU_Disable_CRS_Clock},      // FMKCPU_RCC_CLK_CRS
        {FMKCPU_Enable_RTCAPB_Clock,    FMKCPU_Disable_RTCAPB_Clock},   // FMKCPU_RCC_CLK_RTCAPB
        {FMKCPU_Enable_WWDG_Clock,      FMKCPU_Disable_WWDG_Clock},     // FMKCPU_RCC_CLK_WWDG
        {FMKCPU_Enable_SPI2_Clock,      FMKCPU_Disable_SPI2_Clock},     // FMKCPU_RCC_CLK_SPI2
        {FMKCPU_Enable_SPI3_Clock,      FMKCPU_Disable_SPI3_Clock},     // FMKCPU_RCC_CLK_SPI3
        {FMKCPU_Enable_USART2_Clock,    FMKCPU_Disable_USART2_Clock},   // FMKCPU_RCC_CLK_USART2
        {FMKCPU_Enable_USART3_Clock,    FMKCPU_Disable_USART3_Clock},   // FMKCPU_RCC_CLK_USART3
        {FMKCPU_Enable_UART4_Clock,     FMKCPU_Disable_UART4_Clock},    // FMKCPU_RCC_CLK_UART4
        {FMKCPU_Enable_UART5_Clock,     FMKCPU_Disable_UART5_Clock},    // FMKCPU_RCC_CLK_UART5
        {FMKCPU_Enable_I2C2_Clock,      FMKCPU_Disable_I2C2_Clock},     // FMKCPU_RCC_CLK_I2C2
        {FMKCPU_Enable_USB_Clock,       FMKCPU_Disable_USB_Clock},      // FMKCPU_RCC_CLK_USB
        {FMKCPU_Enable_FDCAN_Clock,     FMKCPU_Disable_FDCAN_Clock},    // FMKCPU_RCC_CLK_FDCAN
        {FMKCPU_Enable_PWR_Clock,       FMKCPU_Disable_PWR_Clock},      // FMKCPU_RCC_CLK_PWR
        {FMKCPU_Enable_I2C3_Clock,      FMKCPU_Disable_I2C3_Clock},     // FMKCPU_RCC_CLK_I2C3
        {FMKCPU_Enable_LPTIM1_Clock,    FMKCPU_Disable_LPTIM1_Clock},   // FMKCPU_RCC_CLK_LPTIM1
        {FMKCPU_Enable_UCPD1_Clock,     FMKCPU_Disable_UCPD1_Clock},    // FMKCPU_RCC_CLK_UCPD1
        {FMKCPU_Enable_SYSCFG_Clock,    FMKCPU_Disable_SYSCFG_Clock},   // FMKCPU_RCC_CLK_SYSCFG
        {FMKCPU_Enable_TIM1_Clock,      FMKCPU_Disable_TIM1_Clock},     // FMKCPU_RCC_CLK_TIM1
        {FMKCPU_Enable_SPI1_Clock,      FMKCPU_Disable_SPI1_Clock},     // FMKCPU_RCC_CLK_SPI1
        {FMKCPU_Enable_TIM8_Clock,      FMKCPU_Disable_TIM8_Clock},     // FMKCPU_RCC_CLK_TIM8
        {FMKCPU_Enable_USART1_Clock,    FMKCPU_Disable_USART1_Clock},   // FMKCPU_RCC_CLK_USART1
        {FMKCPU_Enable_SPI4_Clock,      FMKCPU_Disable_SPI4_Clock},     // FMKCPU_RCC_CLK_SPI4
        {FMKCPU_Enable_TIM15_Clock,     FMKCPU_Disable_TIM15_Clock},    // FMKCPU_RCC_CLK_TIM15
        {FMKCPU_Enable_TIM16_Clock,     FMKCPU_Disable_TIM16_Clock},    // FMKCPU_RCC_CLK_TIM16
        {FMKCPU_Enable_TIM17_Clock,     FMKCPU_Disable_TIM17_Clock},    // FMKCPU_RCC_CLK_TIM17
        {FMKCPU_Enable_TIM20_Clock,     FMKCPU_Disable_TIM20_Clock},    // FMKCPU_RCC_CLK_TIM20
        {FMKCPU_Enable_SAI1_Clock,      FMKCPU_Disable_SAI1_Clock},     // FMKCPU_RCC_CLK_SAI1
        {FMKCPU_Enable_HRTIM1_Clock,    FMKCPU_Disable_HRTIM1_Clock},   // FMKCPU_RCC_CLK_HRTIM1
    };

    const t_eFMKCPU_SysClkOsc c_FmkCpu_RccClockOscSrc_ae[FMKCPU_RCC_CLK_NB] = {
        FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_DMA1
        FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_DMA2
        FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_DMAMUX1
        FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_CORDIC
        FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_FMAC
        FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_FLASH
        FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_CRC
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_GPIOG
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_GPIOF
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_GPIOE
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_GPIOD
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_GPIOC
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_GPIOB
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_GPIOA
        FMKCPU_SYS_CLOCK_PLLP,            // FMKCPU_RCC_CLK_ADC12
        FMKCPU_SYS_CLOCK_PLLP,            // FMKCPU_RCC_CLK_ADC345
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_DAC1
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_DAC2
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_DAC3
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_DAC4
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_RNG
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_FMC
        FMKCPU_SYS_CLOCK_PLLQ,            // FMKCPU_RCC_CLK_QSPI
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM2
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM3
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM4
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM5
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM6
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM7
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_CRS
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_RTCAPB
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_WWDG
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_SPI2
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_SPI3
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_USART2
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_USART3
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_UART4
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_UART5
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_I2C2
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_USB
        FMKCPU_SYS_CLOCK_PLLQ,            // FMKCPU_RCC_CLK_FDCAN
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_PWR
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_I2C3
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_LPTIM1
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_UCPD1
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_SYSCFG
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM1
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_SPI1
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM8
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_USART1
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_SPI4
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM15
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM16
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM17
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM20
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_SAI1
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_HRTIM1
    };

    /**< Variable to mapp every Dma Mux to a Rcc Clock */
    const t_eFMKCPU_ClockPort c_FMKCPU_DmaMuxRccMapp_ae[FMKCPU_DMA_MUX_NB] ={
           FMKCPU_RCC_CLK_DMAMUX1
    };

    /**< Variable to mapp every Dma Request to a Dma Channel */
    const t_sFMKCPU_DmaRqstCfg c_FMKCPU_DmaRqstCfg_as[FMKCPU_DMA_RQSTYPE_NB] ={
        {FMKCPU_DMA_CTRL_1,             FMKCPU_DMA_CHANNEL_5,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_ADC1
        {FMKCPU_DMA_CTRL_1,             FMKCPU_DMA_CHANNEL_4,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_ADC2
        {FMKCPU_DMA_CTRL_1,             FMKCPU_DMA_CHANNEL_3,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_ADC3
        {FMKCPU_DMA_CTRL_2,             FMKCPU_DMA_CHANNEL_4,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_ADC4
        {FMKCPU_DMA_CTRL_2,             FMKCPU_DMA_CHANNEL_5,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_ADC5
        {FMKCPU_DMA_CTRL_2,             FMKCPU_DMA_CHANNEL_1,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_UART4_RX
        {FMKCPU_DMA_CTRL_2,             FMKCPU_DMA_CHANNEL_2,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_UART4_TX
        {FMKCPU_DMA_CTRL_2,             FMKCPU_DMA_CHANNEL_6,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_USART1_RX
        {FMKCPU_DMA_CTRL_2,             FMKCPU_DMA_CHANNEL_7,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_USART1_TX
        {FMKCPU_DMA_CTRL_1,             FMKCPU_DMA_CHANNEL_2,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_USART2_RX
        {FMKCPU_DMA_CTRL_1,             FMKCPU_DMA_CHANNEL_1,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_USART2_TX
        {FMKCPU_DMA_CTRL_1,             FMKCPU_DMA_CHANNEL_6,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_USART3_RX
        {FMKCPU_DMA_CTRL_1,             FMKCPU_DMA_CHANNEL_7,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_USART3_TX
        {FMKCPU_DMA_CTRL_2,             FMKCPU_DMA_CHANNEL_3,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_TIM8_CH1
    };

    /* CAUTION : Automatic generated code section for Variable: End */
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    /* CAUTION : Automatic generated code section for DMA_Channel IRQHandler: Start */
    /**
    * @brief This function handles DMA Channel1 interrupt.
    */
    void DMA2_Channel1_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_2, FMKCPU_DMA_CHANNEL_1));
    return;
    }

    /**
    * @brief This function handles DMA Channel2 interrupt.
    */
    void DMA2_Channel2_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_2, FMKCPU_DMA_CHANNEL_2));
    return;
    }

    /**
    * @brief This function handles DMA Channel3 interrupt.
    */
    void DMA2_Channel3_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_2, FMKCPU_DMA_CHANNEL_3));
    return;
    }

    /**
    * @brief This function handles DMA Channel4 interrupt.
    */
    void DMA2_Channel4_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_2, FMKCPU_DMA_CHANNEL_4));
    return;
    }

    /**
    * @brief This function handles DMA Channel5 interrupt.
    */
    void DMA2_Channel5_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_2, FMKCPU_DMA_CHANNEL_5));
    return;
    }

    /**
    * @brief This function handles DMA Channel1 interrupt.
    */
    void DMA1_Channel1_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_1, FMKCPU_DMA_CHANNEL_1));
    return;
    }

    /**
    * @brief This function handles DMA Channel2 interrupt.
    */
    void DMA1_Channel2_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_1, FMKCPU_DMA_CHANNEL_2));
    return;
    }

    /**
    * @brief This function handles DMA Channel3 interrupt.
    */
    void DMA1_Channel3_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_1, FMKCPU_DMA_CHANNEL_3));
    return;
    }

    /**
    * @brief This function handles DMA Channel4 interrupt.
    */
    void DMA1_Channel4_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_1, FMKCPU_DMA_CHANNEL_4));
    return;
    }

    /**
    * @brief This function handles DMA Channel5 interrupt.
    */
    void DMA1_Channel5_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_1, FMKCPU_DMA_CHANNEL_5));
    return;
    }

    /**
    * @brief This function handles DMA Channel6 interrupt.
    */
    void DMA1_Channel6_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_1, FMKCPU_DMA_CHANNEL_6));
    return;
    }

    /**
    * @brief This function handles DMA Channel7 interrupt.
    */
    void DMA1_Channel7_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_1, FMKCPU_DMA_CHANNEL_7));
    return;
    }

    /* CAUTION : Automatic generated code section for DMA_Channel IRQHandler: End */
#endif // FMKCPU_CONFIGPRIVATE_H_INCLUDED           
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
