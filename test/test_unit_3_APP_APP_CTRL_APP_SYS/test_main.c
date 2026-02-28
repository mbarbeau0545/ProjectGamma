#include <string.h>
#include <unity.h>

#include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
#include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
#include "APP_CTRL/APP_SDM/Src/APP_SDM.h"
#include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
#include "FMK_HAL/FMK_IO/Src/FMK_IO.h"
#include "FMK_HAL/FMK_TIM/Src/FMK_TIM.h"
#include "Library/SafeMem/SafeMem.h"
#include "mock_FMKCPU.h"

#include "mock_FMKCPU.c"

#define DECL_MOD_STUB(mod) \
    t_eReturnCode mod##_Init(void) { return RC_OK; } \
    t_eReturnCode mod##_Cyclic(void) { return RC_OK; } \
    t_eReturnCode mod##_GetState(t_eCyclicModState *f_State_pe) { if(f_State_pe == NULL) { return RC_ERROR_PTR_NULL; } *f_State_pe = STATE_CYCLIC_OPE; return RC_OK; } \
    t_eReturnCode mod##_SetState(t_eCyclicModState f_State_e) { (void)f_State_e; return RC_OK; }

DECL_MOD_STUB(FMKCPU)
DECL_MOD_STUB(FMKTIM)
DECL_MOD_STUB(FMKHRT)
DECL_MOD_STUB(FMKCDA)
DECL_MOD_STUB(FMKIO)
DECL_MOD_STUB(FMKFDCAN)
DECL_MOD_STUB(FMKSRL)
DECL_MOD_STUB(APPSDM)
DECL_MOD_STUB(APPSPM)
DECL_MOD_STUB(APPSIG)
DECL_MOD_STUB(APPSNS)
DECL_MOD_STUB(APPACT)
DECL_MOD_STUB(APPLGC)

t_eReturnCode FMKCPU_Set_HardwareInit(void) { return RC_OK; }
t_eReturnCode FMKCPU_Set_SysClockCfg(t_eFMKCPU_CoreClockSpeed f_SystemCoreFreq_e) { (void)f_SystemCoreFreq_e; return RC_OK; }
t_eReturnCode FMKCPU_Set_WwdgCfg(t_eFMKCPu_WwdgResetPeriod f_period_e) { (void)f_period_e; return RC_OK; }
void FMKCPU_RearmWwdg(void) {}

t_eReturnCode FMKSRL_InitDrv(t_eFMKSRL_SerialLine f_SrlLine_e, t_sFMKSRL_DrvSerialCfg f_SerialCfg_s, t_cbFMKSRL_RcvMsgEvent * f_rcvMsgEvnt_pcb, t_cbFMKSRL_TransmitMsgEvent * f_txMsgEvnt_pcb)
{
    (void)f_SrlLine_e; (void)f_SerialCfg_s; (void)f_rcvMsgEvnt_pcb; (void)f_txMsgEvnt_pcb; return RC_OK;
}
void FMKSRL_LogUartSend(t_eFMKSRL_SerialLine f_SrlLine_e, const t_char * fmt, ...)
{
    (void)f_SrlLine_e; (void)fmt;
}

t_eReturnCode FMKIO_Set_InAnaSigCfg(t_eFMKIO_InAnaSig f_AnaSig_e, t_sFMKIO_InAnaTresHoldCfg  * f_tresHoldCfg_ps, t_bool f_enableTresholdMntor_b, t_cbFMKIO_SigErrorMngmt *f_sigErr_cb)
{
    (void)f_AnaSig_e; (void)f_tresHoldCfg_ps; (void)f_enableTresholdMntor_b; (void)f_sigErr_cb; return RC_OK;
}
t_eReturnCode FMKIO_Get_InAnaSigValue(t_eFMKIO_InAnaSig f_AnaSig_e, t_float32 *f_SigValue_pf32)
{
    (void)f_AnaSig_e;
    if(f_SigValue_pf32 == NULL) { return RC_ERROR_PTR_NULL; }
    *f_SigValue_pf32 = 1.0f;
    return RC_OK;
}

t_eReturnCode FMKTIM_Set_EvntTimerCfg(t_eFMKTIM_InterruptLineEvnt f_EvntITLine_e, t_float32 f_periodms_f32, t_cbFMKTIM_InterruptLine f_ITLine_cb)
{
    (void)f_EvntITLine_e; (void)f_periodms_f32; (void)f_ITLine_cb; return RC_OK;
}
t_eReturnCode FMKTIM_Set_EvntLineState(t_eFMKTIM_InterruptLineEvnt f_EvntITLine_e, t_eFMKTIM_EvntOpe f_EvntOpe)
{
    (void)f_EvntITLine_e; (void)f_EvntOpe; return RC_OK;
}

t_eReturnCode APPSIG_GetSignalValue(t_eAPPSIG_Signal f_signal_e, t_float32 * f_value_pf32)
{
    (void)f_signal_e;
    if(f_value_pf32 == NULL) { return RC_ERROR_PTR_NULL; }
    *f_value_pf32 = 1.0f;
    return RC_OK;
}
t_eReturnCode APPSIG_SetSignalValue(t_eAPPSIG_Signal f_signal_e, t_float32 f_value_f32)
{
    (void)f_signal_e; (void)f_value_f32; return RC_OK;
}

t_eReturnCode APPSPM_GetParam(t_eAPPSPM_ItemPrm f_itemId_e, t_uAPPSPM_PrmValType * f_prmValue_pu)
{
    (void)f_itemId_e;
    if(f_prmValue_pu == NULL) { return RC_ERROR_PTR_NULL; }
    f_prmValue_pu->prmVal_u16 = 1u;
    return RC_OK;
}

void APPSDM_ReportDiagEvnt(t_eAPPSDM_DiagnosticItem f_item_e, t_eAPPSDM_DiagnosticReport f_reportState_e, t_uint16 f_debugInfo1_u16, t_uint16 f_debugInfo2_u16)
{
    (void)f_item_e; (void)f_reportState_e; (void)f_debugInfo1_u16; (void)f_debugInfo2_u16;
}

t_eReturnCode SMB_SecureBlockInit(t_sSafeMem_BlockInfo * f_secBlockInfo_ps, const void * f_SecureArea_pv, const t_uint16 f_sizeSecArea_u16, t_uint8 f_maxAttemptOpe_u8)
{
    if((f_secBlockInfo_ps == NULL) || (f_SecureArea_pv == NULL)) { return RC_ERROR_PTR_NULL; }
    f_secBlockInfo_ps->blockArea_pv = (void *)f_SecureArea_pv;
    f_secBlockInfo_ps->sizeBlock_u16 = f_sizeSecArea_u16;
    f_secBlockInfo_ps->maxAttemptOpe_u8 = f_maxAttemptOpe_u8;
    f_secBlockInfo_ps->isConfigured_b = TRUE;
    return RC_OK;
}
t_eReturnCode SMB_Read(t_sSafeMem_BlockInfo * f_secBlockInfo_ps, void * f_dataContainer_pv, const t_uint16 f_sizeSecArea_u16)
{
    if((f_secBlockInfo_ps == NULL) || (f_dataContainer_pv == NULL) || (f_secBlockInfo_ps->blockArea_pv == NULL)) { return RC_ERROR_PTR_NULL; }
    (void)memcpy(f_dataContainer_pv, f_secBlockInfo_ps->blockArea_pv, f_sizeSecArea_u16);
    return RC_OK;
}
t_eReturnCode SMB_Write(t_sSafeMem_BlockInfo * f_secBlockInfo_ps, void * f_dataContainer_pv, const t_uint16 f_sizeSecArea_u16)
{
    if((f_secBlockInfo_ps == NULL) || (f_dataContainer_pv == NULL) || (f_secBlockInfo_ps->blockArea_pv == NULL)) { return RC_ERROR_PTR_NULL; }
    (void)memcpy(f_secBlockInfo_ps->blockArea_pv, f_dataContainer_pv, f_sizeSecArea_u16);
    return RC_OK;
}

#include "APP_CTRL/APP_SYS/Src/APP_SYS.c"

void setUp(void)
{
    mock_FMKCPU_ResetTick();
    APPSYS_Init();
}

void tearDown(void)
{
}

static void s_DummyFastTask(void)
{
}

void test_APPSYS_AddFastTask_validation(void)
{
    TEST_ASSERT_EQUAL(RC_ERROR_PARAM_INVALID, APPSYS_AddFastTask(APPSYS_MODULE_NB, s_DummyFastTask));
    TEST_ASSERT_EQUAL(RC_ERROR_PARAM_INVALID, APPSYS_AddFastTask(APPSYS_MODULE_APP_SIG, NULL));
    TEST_ASSERT_EQUAL(RC_OK, APPSYS_AddFastTask(APPSYS_MODULE_APP_SIG, s_DummyFastTask));
}

void test_APPSYS_SetFastTaskState_validation_and_nominal(void)
{
    TEST_ASSERT_EQUAL(RC_ERROR_PARAM_INVALID, APPSYS_SetFastTaskState(APPSYS_MODULE_NB, APPSYS_FAST_TASK_ENABLE));
    TEST_ASSERT_EQUAL(RC_OK, APPSYS_SetFastTaskState(APPSYS_MODULE_APP_SIG, APPSYS_FAST_TASK_ENABLE));
    TEST_ASSERT_EQUAL(RC_OK, APPSYS_SetFastTaskState(APPSYS_MODULE_APP_SIG, APPSYS_FAST_TASK_DISABLE));
}

void test_APPSYS_GetSysOption_busy_then_ok(void)
{
    t_uint8 val_u8 = 0u;
    TEST_ASSERT_EQUAL(RC_WARNING_BUSY, APPSYS_GetSysOption(APPSYS_OPT_ID_ACT_MTR_XL, &val_u8));
    g_AppSysModuleState_e = STATE_CYCLIC_OPE;
    TEST_ASSERT_EQUAL(RC_OK, APPSYS_GetSysOption(APPSYS_OPT_ID_ACT_MTR_XL, &val_u8));
}

void test_APPSYS_GetEcuPosition_busy_then_ok(void)
{
    t_eAPPSYS_EcuPos ecuPos_e = APPSYS_ECU_POS_NB;
    TEST_ASSERT_EQUAL(RC_WARNING_BUSY, APPSYS_GetEcuPosition(&ecuPos_e));
    g_isEcuPosValid_b = TRUE;
    g_ecuPos_e = APPSYS_ECU_POS_GTRY;
    TEST_ASSERT_EQUAL(RC_OK, APPSYS_GetEcuPosition(&ecuPos_e));
    TEST_ASSERT_EQUAL(APPSYS_ECU_POS_GTRY, ecuPos_e);
}

void test_APPSYS_AssertionTrap_lock_behavior(void)
{
    g_lockAssert_b = FALSE;
    g_AssertInfo_s.debugInfo_u16 = 0u;
    APPSYS_AssertionTrap(10u, "a.c", 12u, 100u);
    APPSYS_AssertionTrap(20u, "b.c", 42u, 200u);
    TEST_ASSERT_EQUAL_UINT16(10u, g_AssertInfo_s.debugInfo_u16);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_APPSYS_AddFastTask_validation);
    RUN_TEST(test_APPSYS_SetFastTaskState_validation_and_nominal);
    RUN_TEST(test_APPSYS_GetSysOption_busy_then_ok);
    RUN_TEST(test_APPSYS_GetEcuPosition_busy_then_ok);
    RUN_TEST(test_APPSYS_AssertionTrap_lock_behavior);
    return UNITY_END();
}
