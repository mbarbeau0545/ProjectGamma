#include <string.h>
#include <unity.h>

#include "APP_CTRL/APP_ACT/Src/APP_ACT.h"
#include "mock_FMKCPU.h"

#include "mock_FMKCPU.c"

#define DECL_ACT_STUB(base) \
    t_eReturnCode APPACT_SPEC_##base##_SetCfg(t_uint8 f_actDvcOpt_u8, t_eAPPACT_ActDriverList * f_DrvUsed_pe) { (void)f_actDvcOpt_u8; if(f_DrvUsed_pe != NULL) { *f_DrvUsed_pe = APPACT_DRV_NB; } return RC_OK; } \
    t_eReturnCode APPACT_SPEC_##base##_PLS_SetValue(t_float32 f_SigValue_pf32) { (void)f_SigValue_pf32; return RC_OK; } \
    t_eReturnCode APPACT_SPEC_##base##_PLS_GetValue(t_float32 *f_rawSigValue_pf32) { if(f_rawSigValue_pf32 != NULL) { *f_rawSigValue_pf32 = 10.0f; } return RC_OK; } \
    t_eReturnCode APPACT_SPEC_##base##_SPD_SetValue(t_float32 f_SigValue_pf32) { (void)f_SigValue_pf32; return RC_OK; } \
    t_eReturnCode APPACT_SPEC_##base##_SPD_GetValue(t_float32 *f_rawSigValue_pf32) { if(f_rawSigValue_pf32 != NULL) { *f_rawSigValue_pf32 = 20.0f; } return RC_OK; } \
    t_eReturnCode APPACT_SPEC_##base##_TRG_SetValue(t_float32 f_SigValue_pf32) { (void)f_SigValue_pf32; return RC_OK; } \
    t_eReturnCode APPACT_SPEC_##base##_TRG_GetValue(t_float32 *f_rawSigValue_pf32) { if(f_rawSigValue_pf32 != NULL) { *f_rawSigValue_pf32 = 30.0f; } return RC_OK; }

DECL_ACT_STUB(MTR_XL)
DECL_ACT_STUB(MTR_XR)
DECL_ACT_STUB(MTR_Y)
DECL_ACT_STUB(MTR_Z)
DECL_ACT_STUB(MTR_WHL_AV_L)
DECL_ACT_STUB(MTR_WHL_AV_R)
DECL_ACT_STUB(MTR_HD_KNF)
DECL_ACT_STUB(MTR_HD_CNTR_KNF)
DECL_ACT_STUB(MTR_HD_HOLD)

#include "APP_CTRL/APP_ACT/Src/APP_ACT.c"

typedef struct
{
    t_uint32 assertCnt_u32;
    t_uint32 addFastTaskCnt_u32;
    t_uint32 setFastTaskCnt_u32;
    t_uint32 getSysOptCnt_u32;
    t_uint32 addSigCbCnt_u32;
    t_uint32 setSigValCnt_u32;
} t_sActTestCtx;

static t_sActTestCtx g_ctx_s;

void APPSYS_AssertionTrap(t_uint16 f_Info_u16, const char * f_file_str, t_uint32 f_line_u32, t_uint32 f_captureTime_u32)
{
    (void)f_Info_u16;
    (void)f_file_str;
    (void)f_line_u32;
    (void)f_captureTime_u32;
    g_ctx_s.assertCnt_u32++;
}

t_eReturnCode APPSYS_AddFastTask(t_eAppSys_ModuleList f_ModuleId_e, t_cbAPPSYS_FastTask * f_moduleFastTask_pcb)
{
    (void)f_ModuleId_e;
    (void)f_moduleFastTask_pcb;
    g_ctx_s.addFastTaskCnt_u32++;
    return RC_OK;
}

t_eReturnCode APPSYS_SetFastTaskState(t_eAppSys_ModuleList f_ModuleId_e,  t_eAPPSYS_FastTaskState f_state_e)
{
    (void)f_ModuleId_e;
    (void)f_state_e;
    g_ctx_s.setFastTaskCnt_u32++;
    return RC_OK;
}

t_eReturnCode APPSYS_GetSysOption(t_eAPPSYS_SysOptionList f_OptionID_e, t_uint8 * f_OptVal_pu8)
{
    (void)f_OptionID_e;
    g_ctx_s.getSysOptCnt_u32++;
    if(f_OptVal_pu8 == NULL)
    {
        return RC_ERROR_PTR_NULL;
    }
    *f_OptVal_pu8 = 1u;
    return RC_OK;
}

t_eReturnCode APPSIG_AddRcvSigCallback(t_eAPPSIG_Signal f_signal_e, t_cbAPPSIG_SignalRcvCallback * f_msgRcvCallback_pcb)
{
    (void)f_signal_e;
    (void)f_msgRcvCallback_pcb;
    g_ctx_s.addSigCbCnt_u32++;
    return RC_OK;
}

t_eReturnCode APPSIG_SetSignalValue(t_eAPPSIG_Signal f_signal_e, t_float32 f_value_f32)
{
    (void)f_signal_e;
    (void)f_value_f32;
    g_ctx_s.setSigValCnt_u32++;
    return RC_OK;
}

void setUp(void)
{
    (void)memset(&g_ctx_s, 0, sizeof(g_ctx_s));
    mock_FMKCPU_ResetTick();
    g_AppAct_ModState_e = STATE_CYCLIC_CFG;
    g_FsmCfgSts_e = APPACT_FSM_CFGSTS_INIT_DRIVER;
    TEST_ASSERT_EQUAL(RC_OK, APPACT_Init());
}

void tearDown(void)
{
}

void test_APPACT_GetState_null_returns_error(void)
{
    TEST_ASSERT_EQUAL(RC_ERROR_PTR_NULL, APPACT_GetState((t_eCyclicModState *)NULL));
}

void test_APPACT_Init_registers_fasttask(void)
{
    TEST_ASSERT_GREATER_THAN_UINT32(0u, g_ctx_s.addFastTaskCnt_u32);
}

void test_APPACT_Cyclic_reaches_ope(void)
{
    t_eCyclicModState state_e = STATE_CYCLIC_ERROR;
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, APPACT_Cyclic());
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, APPACT_Cyclic());
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, APPACT_Cyclic());
    TEST_ASSERT_EQUAL(RC_OK, APPACT_Cyclic());
    TEST_ASSERT_EQUAL(RC_OK, APPACT_GetState(&state_e));
    TEST_ASSERT_EQUAL(STATE_CYCLIC_PREOPE, state_e);
    TEST_ASSERT_EQUAL(RC_OK, APPACT_Cyclic());
    TEST_ASSERT_EQUAL(RC_OK, APPACT_GetState(&state_e));
    TEST_ASSERT_EQUAL(STATE_CYCLIC_OPE, state_e);
}

void test_APPACT_GetSetActValue_busy_when_not_ope(void)
{
    t_float32 value_f32 = 0.0f;
    TEST_ASSERT_EQUAL(RC_WARNING_MISSING_CONFIG, APPACT_GetActValue(APPACT_ACTITF_MTR_XL_PLS, &value_f32));
    TEST_ASSERT_EQUAL(RC_WARNING_BUSY, APPACT_SetActValue(APPACT_ACTITF_MTR_XL_PLS, 12.0f));
}

void test_APPACT_GetSetActValue_nominal_in_ope(void)
{
    t_float32 value_f32 = 0.0f;
    t_uint8 idx_u8;
    TEST_ASSERT_EQUAL(RC_OK, APPACT_SetState(STATE_CYCLIC_OPE));
    for(idx_u8 = (t_uint8)0; idx_u8 < (t_uint8)APPACT_ACTDVC_NB; idx_u8++)
    {
        g_ActDeviceInfo_as[idx_u8].isConfigured_b = TRUE;
    }

    TEST_ASSERT_EQUAL(RC_OK, APPACT_SetActValue(APPACT_ACTITF_MTR_XL_PLS, 88.0f));
    TEST_ASSERT_EQUAL(RC_OK, APPACT_GetActValue(APPACT_ACTITF_MTR_XL_PLS, &value_f32));
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 10.0f, value_f32);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_APPACT_GetState_null_returns_error);
    RUN_TEST(test_APPACT_Init_registers_fasttask);
    RUN_TEST(test_APPACT_Cyclic_reaches_ope);
    RUN_TEST(test_APPACT_GetSetActValue_busy_when_not_ope);
    RUN_TEST(test_APPACT_GetSetActValue_nominal_in_ope);
    return UNITY_END();
}
