#include <string.h>
#include <unity.h>

#include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
#include "mock_FMKCPU.h"

#include "mock_FMKCPU.c"
#include "APP_CTRL/APP_SPM/Src/APP_SPM.c"

typedef struct
{
    t_uint32 count_u32;
    t_uint16 info_u16;
} t_sAssertCtx;

static t_sAssertCtx g_assertCtx_s;
static t_uint32 g_addSigCbCnt_u32 = (t_uint32)0;
static t_uint32 g_setSigValCnt_u32 = (t_uint32)0;

void APPSYS_AssertionTrap(t_uint16 f_Info_u16, const char * f_file_str, t_uint32 f_line_u32, t_uint32 f_captureTime_u32)
{
    (void)f_file_str;
    (void)f_line_u32;
    (void)f_captureTime_u32;
    g_assertCtx_s.count_u32++;
    g_assertCtx_s.info_u16 = f_Info_u16;
}

t_eReturnCode APPSIG_AddRcvSigCallback(t_eAPPSIG_Signal f_signal_e, t_cbAPPSIG_SignalRcvCallback * f_msgRcvCallback_pcb)
{
    (void)f_signal_e;
    (void)f_msgRcvCallback_pcb;
    g_addSigCbCnt_u32++;
    return RC_OK;
}

t_eReturnCode APPSIG_SetSignalValue(t_eAPPSIG_Signal f_signal_e, t_float32 f_value_f32)
{
    (void)f_signal_e;
    (void)f_value_f32;
    g_setSigValCnt_u32++;
    return RC_OK;
}

void setUp(void)
{
    (void)memset(&g_assertCtx_s, 0, sizeof(g_assertCtx_s));
    g_addSigCbCnt_u32 = (t_uint32)0;
    g_setSigValCnt_u32 = (t_uint32)0;
    mock_FMKCPU_ResetTick();
    g_APPSM_ModState_e = STATE_CYCLIC_CFG;
    g_FlagParamInit_b = FALSE;
    TEST_ASSERT_EQUAL(RC_OK, APPSPM_Init());
}

void tearDown(void)
{
}

void test_APPSPM_GetState_null_returns_error(void)
{
    TEST_ASSERT_EQUAL(RC_ERROR_PTR_NULL, APPSPM_GetState((t_eCyclicModState *)NULL));
}

void test_APPSPM_GetParam_busy_before_configuration(void)
{
    t_uAPPSPM_PrmValType value_u = {0};
    TEST_ASSERT_EQUAL(RC_WARNING_BUSY, APPSPM_GetParam(APPSPM_PRM_SYS_MACHINE_ID, &value_u));
}

void test_APPSPM_Cyclic_reaches_ope_and_sets_defaults(void)
{
    t_eCyclicModState state_e = STATE_CYCLIC_ERROR;
    t_uAPPSPM_PrmValType value_u = {0};

    TEST_ASSERT_EQUAL(RC_OK, APPSPM_Cyclic());
    TEST_ASSERT_EQUAL(RC_OK, APPSPM_GetState(&state_e));
    TEST_ASSERT_EQUAL(STATE_CYCLIC_PREOPE, state_e);
    TEST_ASSERT_GREATER_THAN_UINT32(0u, g_addSigCbCnt_u32);

    TEST_ASSERT_EQUAL(RC_OK, APPSPM_Cyclic());
    TEST_ASSERT_EQUAL(RC_OK, APPSPM_GetState(&state_e));
    TEST_ASSERT_EQUAL(STATE_CYCLIC_OPE, state_e);

    TEST_ASSERT_EQUAL(RC_OK, APPSPM_GetParam(APPSPM_PRM_SYS_MACHINE_ID, &value_u));
    TEST_ASSERT_EQUAL_UINT16(1u, value_u.prmVal_u16);
}

void test_APPSPM_SetAndGetParam_nominal(void)
{
    t_uAPPSPM_PrmValType set_u = {.prmVal_u16 = 2222u};
    t_uAPPSPM_PrmValType get_u = {0};

    TEST_ASSERT_EQUAL(RC_OK, APPSPM_Cyclic());
    TEST_ASSERT_EQUAL(RC_OK, APPSPM_Cyclic());
    TEST_ASSERT_EQUAL(RC_OK, APPSPM_SetParam(APPSPM_PRM_GTRY_PULSE_ITER_MAX, set_u));
    TEST_ASSERT_EQUAL(RC_OK, APPSPM_GetParam(APPSPM_PRM_GTRY_PULSE_ITER_MAX, &get_u));
    TEST_ASSERT_EQUAL_UINT16(2222u, get_u.prmVal_u16);
}

void test_APPSPM_GetParamInfo_nominal_and_validation(void)
{
    t_float32 min_f32 = 0.0f;
    t_float32 max_f32 = 0.0f;
    t_float32 def_f32 = 0.0f;

    TEST_ASSERT_EQUAL(RC_WARNING_BUSY, APPSPM_GetParamInfo(APPSPM_PRM_SYS_MACHINE_ID, &min_f32, &max_f32, &def_f32));
    TEST_ASSERT_EQUAL(RC_OK, APPSPM_Cyclic());
    TEST_ASSERT_EQUAL(RC_OK, APPSPM_Cyclic());
    TEST_ASSERT_EQUAL(RC_OK, APPSPM_GetParamInfo(APPSPM_PRM_SYS_MACHINE_ID, &min_f32, &max_f32, &def_f32));
    TEST_ASSERT_TRUE(max_f32 >= min_f32);
    TEST_ASSERT_TRUE(def_f32 >= min_f32);
}

void test_APPSPM_Param_validation_errors(void)
{
    t_uAPPSPM_PrmValType value_u = {0};
    t_uAPPSPM_PrmValType set_u = {.prmVal_u16 = 1u};

    TEST_ASSERT_EQUAL(RC_ERROR_PARAM_INVALID, APPSPM_GetParam(APPSPM_PRM_NB + 1u, &value_u));
    TEST_ASSERT_EQUAL(RC_ERROR_PTR_NULL, APPSPM_GetParam(APPSPM_PRM_SYS_MACHINE_ID, NULL));
    TEST_ASSERT_EQUAL(RC_WARNING_BUSY, APPSPM_SetParam(APPSPM_PRM_SYS_MACHINE_ID, set_u));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_APPSPM_GetState_null_returns_error);
    RUN_TEST(test_APPSPM_GetParam_busy_before_configuration);
    RUN_TEST(test_APPSPM_Cyclic_reaches_ope_and_sets_defaults);
    RUN_TEST(test_APPSPM_SetAndGetParam_nominal);
    RUN_TEST(test_APPSPM_GetParamInfo_nominal_and_validation);
    RUN_TEST(test_APPSPM_Param_validation_errors);
    return UNITY_END();
}
