#include <string.h>
#include <unity.h>

#include "APP_CTRL/APP_SDM/Src/APP_SDM.h"
#include "APP_CFG/ConfigSpecific/APPSDM_ConfigSpecific.h"
#include "mock_FMKCPU.h"
#include "mock_FMKSRL.h"

/* Unit under test and test doubles are compiled in this TU for native tests. */
#include "mock_FMKCPU.c"
#include "mock_FMKSRL.c"
#include "APP_CTRL/APP_SDM/Src/APP_SDM.c"

typedef struct
{
    t_uint32 count_u32;
    t_uint16 lastInfo_u16;
    t_uint32 lastLine_u32;
    t_uint32 lastTick_u32;
    char lastFile_ac[128];
} t_sTestAssertCtx;

typedef struct
{
    t_uint32 count_u32;
    t_eAPPSDM_DiagnosticItem lastItem_e;
    t_eAPPSDM_DiagnosticReport lastState_e;
    t_uint16 lastDbg1_u16;
    t_uint16 lastDbg2_u16;
} t_sTestUserCbCtx;

static t_sTestAssertCtx g_assertCtx_s;
static t_sTestUserCbCtx g_userCbCtx_s;
extern t_cbAPPSDM_DiagEventBroadcast * g_UserCallback_pcb;

void APPSYS_AssertionTrap(t_uint16 f_Info_u16, const char * f_file_str, t_uint32 f_line_u32, t_uint32 f_captureTime_u32)
{
    g_assertCtx_s.count_u32++;
    g_assertCtx_s.lastInfo_u16 = f_Info_u16;
    g_assertCtx_s.lastLine_u32 = f_line_u32;
    g_assertCtx_s.lastTick_u32 = f_captureTime_u32;
    if(f_file_str != NULL)
    {
        (void)strncpy(g_assertCtx_s.lastFile_ac, f_file_str, (sizeof(g_assertCtx_s.lastFile_ac) - 1u));
        g_assertCtx_s.lastFile_ac[sizeof(g_assertCtx_s.lastFile_ac) - 1u] = '\0';
    }
}

void APPSDM_SPEC_DiagStrat_GANTRY_AXES_OFF(t_eAPPSDM_DiagStratOpe f_stratOpe_e) { (void)f_stratOpe_e; }
void APPSDM_SPEC_DiagStrat_GANTRY_AXE_X_OFF(t_eAPPSDM_DiagStratOpe f_stratOpe_e) { (void)f_stratOpe_e; }
void APPSDM_SPEC_DiagStrat_GANTRY_AXE_Y_OFF(t_eAPPSDM_DiagStratOpe f_stratOpe_e) { (void)f_stratOpe_e; }
void APPSDM_SPEC_DiagStrat_GANTRY_AXE_Z_OFF(t_eAPPSDM_DiagStratOpe f_stratOpe_e) { (void)f_stratOpe_e; }
void APPSDM_SPEC_DiagStrat_HEAD_CUTTER_OFF(t_eAPPSDM_DiagStratOpe f_stratOpe_e) { (void)f_stratOpe_e; }
void APPSDM_SPEC_DiagStrat_MOTION_OFF(t_eAPPSDM_DiagStratOpe f_stratOpe_e)
{
    (void)f_stratOpe_e;
}

static void s_TestUserDiagCb(t_eAPPSDM_DiagnosticItem f_item_e,
                             t_eAPPSDM_DiagnosticReport f_reportState_e,
                             t_uint16 f_debugInfo1_u16,
                             t_uint16 f_debugInfo2_u16)
{
    g_userCbCtx_s.count_u32++;
    g_userCbCtx_s.lastItem_e = f_item_e;
    g_userCbCtx_s.lastState_e = f_reportState_e;
    g_userCbCtx_s.lastDbg1_u16 = f_debugInfo1_u16;
    g_userCbCtx_s.lastDbg2_u16 = f_debugInfo2_u16;
}

void setUp(void)
{
    (void)memset(&g_assertCtx_s, 0, sizeof(g_assertCtx_s));
    (void)memset(&g_userCbCtx_s, 0, sizeof(g_userCbCtx_s));
    mock_FMKCPU_ResetTick();
    g_UserCallback_pcb = (t_cbAPPSDM_DiagEventBroadcast *)NULL_FUNCTION;
    TEST_ASSERT_EQUAL(RC_OK, APPSDM_Init());
    TEST_ASSERT_EQUAL(RC_OK, APPSDM_SetState(STATE_CYCLIC_CFG));
}

void tearDown(void)
{
}

void test_APPSDM_GetState_null_ptr_returns_error(void)
{
    TEST_ASSERT_EQUAL(RC_ERROR_PTR_NULL, APPSDM_GetState((t_eCyclicModState *)NULL));
}

void test_APPSDM_Cyclic_transitions_cfg_to_preope_to_ope(void)
{
    t_eCyclicModState state_e = STATE_CYCLIC_ERROR;

    TEST_ASSERT_EQUAL(RC_OK, APPSDM_Cyclic());
    TEST_ASSERT_EQUAL(RC_OK, APPSDM_GetState(&state_e));
    TEST_ASSERT_EQUAL(STATE_CYCLIC_PREOPE, state_e);

    TEST_ASSERT_EQUAL(RC_OK, APPSDM_Cyclic());
    TEST_ASSERT_EQUAL(RC_OK, APPSDM_GetState(&state_e));
    TEST_ASSERT_EQUAL(STATE_CYCLIC_OPE, state_e);
}

void test_APPSDM_Report_fail_then_status_is_fail(void)
{
    t_eAPPSDM_DiagnosticReport report_e = APPSDM_DIAG_ITEM_REPORT_PASS;

    APPSDM_ReportDiagEvnt(APPSDM_DIAG_ITEM_APP_CYCLIC_TIMEOUT, APPSDM_DIAG_ITEM_REPORT_FAIL, 11u, 22u);
    TEST_ASSERT_EQUAL(RC_OK, APPSDM_GetDiagStatus(APPSDM_DIAG_ITEM_APP_CYCLIC_TIMEOUT, &report_e));
    TEST_ASSERT_EQUAL(APPSDM_DIAG_ITEM_REPORT_FAIL, report_e);
    TEST_ASSERT_EQUAL_UINT32(0u, g_assertCtx_s.count_u32);
}

void test_APPSDM_Report_pass_without_active_diag_keeps_pass(void)
{
    t_eAPPSDM_DiagnosticReport report_e = APPSDM_DIAG_ITEM_REPORT_FAIL;

    APPSDM_ReportDiagEvnt(APPSDM_DIAG_ITEM_APP_CYCLIC_TIMEOUT, APPSDM_DIAG_ITEM_REPORT_PASS, 0u, 0u);
    TEST_ASSERT_EQUAL(RC_OK, APPSDM_GetDiagStatus(APPSDM_DIAG_ITEM_APP_CYCLIC_TIMEOUT, &report_e));
    TEST_ASSERT_EQUAL(APPSDM_DIAG_ITEM_REPORT_PASS, report_e);
}

void test_APPSDM_ResetDiagEvnt_clears_registered_diag(void)
{
    t_eAPPSDM_DiagnosticReport report_e = APPSDM_DIAG_ITEM_REPORT_FAIL;

    APPSDM_ReportDiagEvnt(APPSDM_DIAG_ITEM_APP_CYCLIC_TIMEOUT, APPSDM_DIAG_ITEM_REPORT_FAIL, 1u, 2u);
    TEST_ASSERT_EQUAL(RC_OK, APPSDM_ResetDiagEvnt());
    TEST_ASSERT_EQUAL(RC_OK, APPSDM_GetDiagStatus(APPSDM_DIAG_ITEM_APP_CYCLIC_TIMEOUT, &report_e));
    TEST_ASSERT_EQUAL(APPSDM_DIAG_ITEM_REPORT_PASS, report_e);
}

void test_APPSDM_AddCallback_validation(void)
{
    TEST_ASSERT_EQUAL(RC_ERROR_PTR_NULL, APPSDM_AddCallbackEvnt((t_cbAPPSDM_DiagEventBroadcast *)NULL_FUNCTION));
    TEST_ASSERT_EQUAL(RC_OK, APPSDM_AddCallbackEvnt(s_TestUserDiagCb));
    TEST_ASSERT_EQUAL(RC_ERROR_ALREADY_CONFIGURED, APPSDM_AddCallbackEvnt(s_TestUserDiagCb));
}

void test_APPSDM_GetDiagStatus_validation(void)
{
    t_eAPPSDM_DiagnosticReport report_e = APPSDM_DIAG_ITEM_REPORT_PASS;
    TEST_ASSERT_EQUAL(RC_ERROR_PARAM_INVALID, APPSDM_GetDiagStatus(APPSDM_DIAG_ITEM_NB, &report_e));
    TEST_ASSERT_EQUAL(RC_ERROR_PTR_NULL, APPSDM_GetDiagStatus(APPSDM_DIAG_ITEM_FMK_CFG_ERROR, (t_eAPPSDM_DiagnosticReport *)NULL));
}

void test_APPSDM_UserCallback_fail_periodic_and_pass_end(void)
{
    t_uint16 idx_u16;
    t_uint32 cbCountBeforePass_u32;

    TEST_ASSERT_EQUAL(RC_OK, APPSDM_AddCallbackEvnt(s_TestUserDiagCb));
    APPSDM_ReportDiagEvnt(APPSDM_DIAG_ITEM_FMK_CFG_ERROR, APPSDM_DIAG_ITEM_REPORT_FAIL, 77u, 88u);
    TEST_ASSERT_EQUAL(RC_OK, APPSDM_SetState(STATE_CYCLIC_OPE));

    for(idx_u16 = (t_uint16)0; idx_u16 < (t_uint16)120; idx_u16++)
    {
        TEST_ASSERT_EQUAL(RC_OK, APPSDM_Cyclic());
    }

    TEST_ASSERT_GREATER_THAN_UINT32(0u, g_userCbCtx_s.count_u32);
    TEST_ASSERT_EQUAL(APPSDM_DIAG_ITEM_FMK_CFG_ERROR, g_userCbCtx_s.lastItem_e);
    TEST_ASSERT_EQUAL(APPSDM_DIAG_ITEM_REPORT_FAIL, g_userCbCtx_s.lastState_e);
    cbCountBeforePass_u32 = g_userCbCtx_s.count_u32;

    APPSDM_ReportDiagEvnt(APPSDM_DIAG_ITEM_FMK_CFG_ERROR, APPSDM_DIAG_ITEM_REPORT_PASS, 99u, 111u);
    TEST_ASSERT_EQUAL(RC_OK, APPSDM_Cyclic());
    TEST_ASSERT_GREATER_THAN_UINT32(cbCountBeforePass_u32, g_userCbCtx_s.count_u32);
    TEST_ASSERT_EQUAL(APPSDM_DIAG_ITEM_REPORT_PASS, g_userCbCtx_s.lastState_e);
}

void test_APPSDM_Report_with_invalid_item_triggers_assertion(void)
{
    APPSDM_ReportDiagEvnt(APPSDM_DIAG_ITEM_NB, APPSDM_DIAG_ITEM_REPORT_FAIL, 0u, 0u);
    TEST_ASSERT_EQUAL_UINT32(1u, g_assertCtx_s.count_u32);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_APPSDM_GetState_null_ptr_returns_error);
    RUN_TEST(test_APPSDM_Cyclic_transitions_cfg_to_preope_to_ope);
    RUN_TEST(test_APPSDM_Report_fail_then_status_is_fail);
    RUN_TEST(test_APPSDM_Report_pass_without_active_diag_keeps_pass);
    RUN_TEST(test_APPSDM_ResetDiagEvnt_clears_registered_diag);
    RUN_TEST(test_APPSDM_AddCallback_validation);
    RUN_TEST(test_APPSDM_GetDiagStatus_validation);
    RUN_TEST(test_APPSDM_UserCallback_fail_periodic_and_pass_end);
    RUN_TEST(test_APPSDM_Report_with_invalid_item_triggers_assertion);
    return UNITY_END();
}
