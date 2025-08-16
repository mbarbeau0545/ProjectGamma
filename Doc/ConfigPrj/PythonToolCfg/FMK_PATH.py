"""
#  @file        main.py
#  @brief       Template_BriefDescription.
#  @details     TemplateDetailsDescription.\n
#
#  @author      mba
#  @date        jj/mm/yyyy
#  @version     1.0
"""
#------------------------------------------------------------------------------
#                                       IMPORT
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#                                       CONSTANT
#------------------------------------------------------------------------------
HARDWARE_CFG_PATH = r"Doc\ConfigPrj\ExcelCfg\STM32F030R8\STM32F030R8_HwCfg.xlsx"
FMKIO_CONFIGPRIVATE_PATH = r"src\\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKIO_ConfigPrivate.h"
FMKIO_ConfigPublic_PATH = r"src\\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKIO_ConfigPublic.h"
FMKIO_PATH = r"src\\1_FMK\FMK_HAL\FMK_IO\Src\FMK_IO.c"
FMKIO_CONFIGSPEC_C = r'src\\1_FMK\FMK_CFG\FMKCFG_ConfigSpecific\FMKIO_ConfigSpecific.c'

FMKCPU_CONFIGPUBLIC = r"src\\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKCPU_ConfigPublic.h"
FMKCPU_CONFIGPRIVATE = r"src\\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKCPU_ConfigPrivate.h"
FMKCPU_CONFIGSPECIFIC_C = r"src\\1_FMK\FMK_CFG\FMKCFG_ConfigSpecific\FMKCPU_ConfigSpecific.c"
FMKCPU_CONFIGSPECIFIC_H = r"src\\1_FMK\FMK_CFG\FMKCFG_ConfigSpecific\FMKCPU_ConfigSpecific.h"
FMKCPU = r"src\\1_FMK\FMK_HAL\FMK_CPU\Src\FMK_CPU.c"

FMKCDA_CONFIGPUBLIC = r"src\\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKCDA_ConfigPublic.h"
FMKCDA_CONFIGPRIVATE = r"src\\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKCDA_ConfigPrivate.h"
FMKCDA_CONFIG_SPEC = r"src\1_FMK\FMK_CFG\FMKCFG_ConfigSpecific\FMKCDA_ConfigSpecific.c"
FMKCDA = r"src\\1_FMK\FMK_HAL\FMK_CDA\Src\FMK_CDA.c"

FMKHRT_CFG_PUBLIC_PATH = r'src\\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKHRT_ConfigPublic.h'
FMKHRT_CFG_PRIVATE_PATH = r'src\\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKHRT_ConfigPrivate.h'
FMKHRT_C_FILE = r'src\\1_FMK\FMK_HAL\FMK_HRT\Src\FMK_HRT.c'
FMKHRT_CFG_SPEC = r"src\1_FMK\FMK_CFG\FMKCFG_ConfigSpecific\FMKHRT_ConfigSpecific.c"
FMKHRT_CFG_SPEC_H = r"src\1_FMK\FMK_CFG\FMKCFG_ConfigSpecific\FMKHRT_ConfigSpecific.h"

FMKSRL_CFGSPEC_C   = r'src\\1_FMK\FMK_CFG\FMKCFG_ConfigSpecific\FMKSRL_ConfigSpecific.c'
FMKSRL_CFGPUBLIC   = r'src\\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKSRL_ConfigPublic.h'
FMKSRL_CFGPRIVATE  = r'src\\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKSRL_ConfigPrivate.h'
FMKSRL_CFILE       = r'src\\1_FMK\FMK_HAL\FMK_SRL\Src\FMK_SRL.c'

FMKTIM_CFGSPEC_C   = r'src\\1_FMK\FMK_CFG\FMKCFG_ConfigSpecific\FMKTIM_ConfigSpecific.c'
FMKTIM_CFGPUBLIC   = r'src\\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKTIM_ConfigPublic.h'
FMKTIM_CFGPRIVATE  = r'src\\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKTIM_ConfigPrivate.h'
FMKTIM_CFILE       = r'src\\1_FMK\FMK_HAL\FMK_TIM\Src\FMK_TIM.c'


FMKFDCAN_CFG_PRIVATE = r'src\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKFDCAN_ConfigPrivate.h'
FMKFDCAN_CFG_PUBLIC = r'src\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKFDCAN_ConfigPublic.h'
SPACE_VARIABLE = 30

ENUM_GPIO_PORT_ROOT = "FMKIO_GPIO_PORT"
ENUM_INSIGANA_ROOT    = "FMKIO_INPUT_SIGANA"
ENUM_INSIGDIG_ROOT    = "FMKIO_INPUT_SIGDIG"
ENUM_INSIGFREQ_ROOT    = "FMKIO_INPUT_SIGFREQ"
ENUM_INSIGEVNT_ROOT    = "FMKIO_INPUT_SIGEVNT"
ENUM_OUTSIGDIG_ROOT    = "FMKIO_OUTPUT_SIGDIG"
ENUM_OUTSIGPWM_ROOT    = "FMKIO_OUTPUT_SIGPWM"
ENUM_FMKIO_ECDR_ROOT   = ' FMKIO_INPUT_ENCODER'
ENUM_FMKIO_CAN_ROOT = "FMKIO_COM_SIGNAL_CAN"
ENUM_FMKIO_SERIAL_ROOT = "FMKIO_COM_SIGNAL_SERIAL"
ENUM_FKCPU_SYS_CLK = 'FMKCPU_SYS_CLOCK'
ENUM_FMKCPU_NVIC_ROOT = "FMKCPU_NVIC"
ENUM_FMKTIM_TIMER_ROOT = "FMKTIM_TIMER"
ENUM_FMKTIM_CHANNEL_ROOT = "FMKTIM_CHANNEL"
ENUM_FMKTIM_IT_TYPE_ROOT = "FMKTIM_INTERRUPT_LINE_TYPE"
ENUM_FMKTIM_IT_DAC_ROOT = "FMKTIM_INTERRUPT_LINE_DAC"
ENUM_FMKTIM_IT_EVNT_ROOT = "FMKTIM_INTERRUPT_LINE_EVNT"
ENUM_FMKTIM_IT_GP_ROOT = "FMKTIM_INTERRUPT_LINE_IO"
ENUM_FMKTIM_EVENT_ROOT = "FMKTIM_EVENT_CHANNEL"
ENUM_FMKCPU_NVIC_PRIO_ROOT = "FMKCPU_NVIC_PRIORITY"
ENUM_FMKCPU_RCC_ROOT     ="FMKCPU_RCC_CLK"
ENUM_FMKCPU_CLOCK_PERIPH_TYPE = 'FMKCPU_CLOCK_PERIPH_EXT_TYPE'
ENUM_FMKCPU_SYS_CLOCK     = 'FMKCPU_SYS_CLOCK'
ENUM_GPIO_PIN_ROOT = "FMKIO_GPIO_PIN"
ENUM_ADC_ISCT_ROOT = "FMKCDA_ADC"
ENUM_ADC_INTERN_SENSOR = "FMKCDA_ADC_INTERN"
ENUM_ADC_CHNL_ROOT = "FMKCDA_ADC_CHANNEL"
# CAUTION : Automatic generated code section: Start #

# CAUTION : Automatic generated code section: End #
#------------------------------------------------------------------------------
#                                       CLASS
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#                             FUNCTION IMPLMENTATION
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#			                MAIN
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#		                    END OF FILE
#------------------------------------------------------------------------------
#--------------------------
# Function_name
#--------------------------

"""
    @brief
    @details

    @params[in]
    @params[out]
    @retval
"""

