#include <stdarg.h>
#include <string.h>
#include <unity.h>

#include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
#include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
#include "CL42T/Src/CL42T.h"
#include "Library/QUEUE/Src/LIBQueue.h"
#include "Library/SafeMem/SafeMem.h"
#include "mock_FMKCPU.h"

#include "mock_FMKCPU.c"
#include "Library/SafeMem/SafeMem.c"
#include "Library/QUEUE/Src/LIBQueue.c"

void __disable_irq(void) {}
void __enable_irq(void) {}

void APPSYS_AssertionTrap(t_uint16 f_Info_u16, const char * f_file_str, t_uint32 f_line_u32, t_uint32 f_captureTime_u32)
{
    (void)f_Info_u16;
    (void)f_file_str;
    (void)f_line_u32;
    (void)f_captureTime_u32;
}

t_eReturnCode APPSIG_SetSignalValue(t_eAPPSIG_Signal f_signal_e, t_float32 f_value_f32)
{
    (void)f_signal_e;
    (void)f_value_f32;
    return RC_OK;
}

void FMKSRL_LogUartSend(t_eFMKSRL_SerialLine f_SrlLine_e, const t_char * fmt, ...)
{
    (void)f_SrlLine_e;
    (void)fmt;
}

t_eReturnCode FMKIO_Set_OutDigSigValue(t_eFMKIO_OutDigSig f_signal_e, t_eFMKIO_DigValue f_value_e)
{
    (void)f_signal_e;
    (void)f_value_e;
    return RC_OK;
}

t_eReturnCode FMKIO_Set_OutPwmSigCfg(t_eFMKIO_OutPwmSig f_signal_e,
                                     t_sFMKIO_PwmWaveformCfg f_sigPwmCfg_s,
                                     t_sFMKIO_PwmControlPrm f_sigCtrlPrm_s,
                                     t_cbFMKIO_PulseEvent * f_pulseEvnt_pcb,
                                     t_cbFMKIO_SigErrorMngmt * f_sigErr_cb)
{
    (void)f_signal_e;
    (void)f_sigPwmCfg_s;
    (void)f_sigCtrlPrm_s;
    (void)f_pulseEvnt_pcb;
    (void)f_sigErr_cb;
    return RC_OK;
}

t_eReturnCode FMKIO_Set_OutDigSigCfg(t_eFMKIO_OutDigSig f_signal_e, t_eFMKIO_PullMode f_pull_e, t_eFMKIO_SpdMode f_spd_e)
{
    (void)f_signal_e;
    (void)f_pull_e;
    (void)f_spd_e;
    return RC_OK;
}

t_eReturnCode FMKIO_Set_InFreqSigCfg(t_eFMKIO_InFreqSig f_signal_e,
                                     t_eFMKIO_SigTrigCptr f_trigger_e,
                                     t_eFMKIO_FreqMeas f_freqMeas_e,
                                     t_float32 f_samplingHz_f32,
                                     t_cbFMKIO_SigErrorMngmt *f_sigErr_cb)
{
    (void)f_signal_e;
    (void)f_trigger_e;
    (void)f_freqMeas_e;
    (void)f_samplingHz_f32;
    (void)f_sigErr_cb;
    return RC_OK;
}

t_eReturnCode FMKIO_Set_InEvntSigCfg(t_eFMKIO_InEvntSig f_signal_e,
                                     t_eFMKIO_PullMode f_pull_e,
                                     t_eFMKIO_SigTrigCptr f_trigger_e,
                                     t_uint32 f_debouncDelay_u32,
                                     t_cbFMKIO_EventFunc * f_Evnt_cb,
                                     t_cbFMKIO_SigErrorMngmt *f_sigErr_cb)
{
    (void)f_signal_e;
    (void)f_pull_e;
    (void)f_trigger_e;
    (void)f_debouncDelay_u32;
    (void)f_Evnt_cb;
    (void)f_sigErr_cb;
    return RC_OK;
}

t_eReturnCode FMKIO_Set_OutPwmSigPulses(t_eFMKIO_OutPwmSig f_signal_e,
                                        t_float32 f_frequency_f32,
                                        t_uint16 f_dutyCycle_u16,
                                        t_uint16 f_pulses_u16)
{
    (void)f_signal_e;
    (void)f_frequency_f32;
    (void)f_dutyCycle_u16;
    (void)f_pulses_u16;
    return RC_OK;
}

t_eReturnCode FMKIO_Set_OutPwmSigDutyCycle(t_eFMKIO_OutPwmSig f_signal_e, t_uint16 f_dutyCycle_u16)
{
    (void)f_signal_e;
    (void)f_dutyCycle_u16;
    return RC_OK;
}

t_eReturnCode FMKIO_Set_OutPwmSigFrequency(t_eFMKIO_OutPwmSig f_signal_e, t_float32 f_frequency_f32)
{
    (void)f_signal_e;
    (void)f_frequency_f32;
    return RC_OK;
}

t_eReturnCode FMKIO_Get_OutDigSigValue(t_eFMKIO_OutDigSig f_signal_e, t_eFMKIO_DigValue *f_value_pe)
{
    (void)f_signal_e;
    if(f_value_pe == NULL)
    {
        return RC_ERROR_PTR_NULL;
    }
    *f_value_pe = FMKIO_DIG_VALUE_LOW;
    return RC_OK;
}

t_eReturnCode FMKIO_Get_OutPwmSigFrequency(t_eFMKIO_OutPwmSig f_signal_e, t_float32 * f_frequency_pf32)
{
    (void)f_signal_e;
    if(f_frequency_pf32 == NULL)
    {
        return RC_ERROR_PTR_NULL;
    }
    *f_frequency_pf32 = 0.0f;
    return RC_OK;
}

t_eReturnCode FMKIO_Get_InFreqSigValue(t_eFMKIO_InFreqSig f_signal_e, t_float32 *f_value_pf32)
{
    (void)f_signal_e;
    if(f_value_pf32 == NULL)
    {
        return RC_ERROR_PTR_NULL;
    }
    *f_value_pf32 = 0.0f;
    return RC_OK;
}

#include "CL42T/Src/CL42T.c"

void setUp(void)
{
    mock_FMKCPU_ResetTick();
}

void tearDown(void)
{
}

void test_CL42T_Init_returns_ok(void)
{
    TEST_ASSERT_EQUAL(RC_OK, CL42T_Init());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_CL42T_Init_returns_ok);
    return UNITY_END();
}
