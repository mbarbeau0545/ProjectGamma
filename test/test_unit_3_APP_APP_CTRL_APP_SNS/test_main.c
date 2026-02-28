#include <string.h>
#include <unity.h>

#include "APP_CTRL/APP_SNS/Src/APP_SNS.h"
#include "mock_FMKCPU.h"

#include "mock_FMKCPU.c"

#define DECL_SNS_SIG_STUB(name) \
    t_eReturnCode APPSNS_SPEC_##name##_GetSigValue(t_float32 *f_rawSigValue_pf32, t_bool * f_isValue_OK) { if(f_rawSigValue_pf32 != NULL) { *f_rawSigValue_pf32 = 100.0f; } if(f_isValue_OK != NULL) { *f_isValue_OK = TRUE; } return RC_OK; } \
    t_eReturnCode APPSNS_SPEC_##name##_FormatValue(t_float32 rawValue_f32, t_float32 *SnsValue_f32) { if(SnsValue_f32 != NULL) { *SnsValue_f32 = rawValue_f32; } return RC_OK; }

#define DECL_SNS_CFG_STUB(name) \
    t_eReturnCode APPSNS_SPEC_##name##_SetCfg(t_uint8 f_snsDvcOpt_u8, t_eAPPSNS_SnsDriverList * f_DrvUsed_pe) { (void)f_snsDvcOpt_u8; if(f_DrvUsed_pe != NULL) { *f_DrvUsed_pe = APPSNS_DRV_NB; } return RC_OK; }

DECL_SNS_SIG_STUB(ECDR_XL_POS)
DECL_SNS_SIG_STUB(ECDR_XL_SPD)
DECL_SNS_SIG_STUB(ECDR_XR_POS)
DECL_SNS_SIG_STUB(ECDR_XR_SPD)
DECL_SNS_SIG_STUB(ECDR_Y_POS)
DECL_SNS_SIG_STUB(ECDR_Y_SPD)
DECL_SNS_SIG_STUB(ECDR_Z_POS)
DECL_SNS_SIG_STUB(ECDR_Z_SPD)
DECL_SNS_SIG_STUB(ECDR_WHL_AV_L_POS)
DECL_SNS_SIG_STUB(ECDR_WHL_AV_L_SPD)
DECL_SNS_SIG_STUB(ECDR_WHL_AV_R_POS)
DECL_SNS_SIG_STUB(ECDR_WHL_AV_R_SPD)
DECL_SNS_SIG_STUB(ECDR_HD_KNF_POS)
DECL_SNS_SIG_STUB(ECDR_HD_KNF_SPD)
DECL_SNS_SIG_STUB(ECDR_HD_CNTR_KNF_POS)
DECL_SNS_SIG_STUB(ECDR_HD_CNTR_KNF_SPD)
DECL_SNS_SIG_STUB(ECDR_HD_HOLD_POS)
DECL_SNS_SIG_STUB(ECDR_HD_HOLD_SPD)
DECL_SNS_SIG_STUB(HD_UP_LEFT_DIST)
DECL_SNS_SIG_STUB(HD_DWN_LEFT_DIST)
DECL_SNS_SIG_STUB(HD_UP_RIGHT_DIST)
DECL_SNS_SIG_STUB(HD_DWN_RIGHT_DIST)
DECL_SNS_SIG_STUB(TRQ_MTR_XL_TRQ)
DECL_SNS_SIG_STUB(TRQ_MTR_XR_TRQ)
DECL_SNS_SIG_STUB(TRQ_MTR_Y_TRQ)
DECL_SNS_SIG_STUB(TRQ_MTR_Z_TRQ)
DECL_SNS_SIG_STUB(TRQ_MTR_WHL_AV_L_TRQ)
DECL_SNS_SIG_STUB(TRQ_MTR_WHL_AV_R_TRQ)
DECL_SNS_SIG_STUB(TRQ_MTR_HD_KNF_TRQ)
DECL_SNS_SIG_STUB(TRQ_MTR_CNTR_KNF_TRQ)
DECL_SNS_SIG_STUB(TRQ_MTR_HD_HOLD_TRQ)

DECL_SNS_CFG_STUB(ECDR_XL)
DECL_SNS_CFG_STUB(ECDR_XR)
DECL_SNS_CFG_STUB(ECDR_Y)
DECL_SNS_CFG_STUB(ECDR_Z)
DECL_SNS_CFG_STUB(ECDR_WHL_AV_L)
DECL_SNS_CFG_STUB(ECDR_WHL_AV_R)
DECL_SNS_CFG_STUB(ECDR_HD_KNF)
DECL_SNS_CFG_STUB(ECDR_HD_CNTR_KNF)
DECL_SNS_CFG_STUB(ECDR_HD_HOLD)
DECL_SNS_CFG_STUB(HD_UP_LEFT)
DECL_SNS_CFG_STUB(HD_DWN_LEFT)
DECL_SNS_CFG_STUB(HD_UP_RIGHT)
DECL_SNS_CFG_STUB(HD_DWN_RIGHT)
DECL_SNS_CFG_STUB(TRQ_MTR_XL)
DECL_SNS_CFG_STUB(TRQ_MTR_XR)
DECL_SNS_CFG_STUB(TRQ_MTR_Y)
DECL_SNS_CFG_STUB(TRQ_MTR_Z)
DECL_SNS_CFG_STUB(TRQ_MTR_WHL_AV_L)
DECL_SNS_CFG_STUB(TRQ_MTR_WHL_AV_R)
DECL_SNS_CFG_STUB(TRQ_MTR_HD_KNF)
DECL_SNS_CFG_STUB(TRQ_MTR_CNTR_KNF)
DECL_SNS_CFG_STUB(TRQ_MTR_HD_HOLD)

#include "APP_CTRL/APP_SNS/Src/APP_SNS.c"

typedef struct
{
    t_uint32 assertCnt_u32;
    t_uint32 addFastTaskCnt_u32;
    t_uint32 setFastTaskCnt_u32;
    t_uint32 getSysOptCnt_u32;
    t_uint32 setSigValCnt_u32;
} t_sSnsTestCtx;

static t_sSnsTestCtx g_ctx_s;

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
    g_AppSns_ModState_e = STATE_CYCLIC_CFG;
    g_FsmCfgSts_e = APPSNS_FSM_CFGSTS_INIT_DRIVER;
    TEST_ASSERT_EQUAL(RC_OK, APPSNS_Init());
}

void tearDown(void)
{
}

void test_APPSNS_GetState_null_returns_error(void)
{
    TEST_ASSERT_EQUAL(RC_ERROR_PTR_NULL, APPSNS_GetState((t_eCyclicModState *)NULL));
}

void test_APPSNS_Init_registers_fasttask(void)
{
    TEST_ASSERT_GREATER_THAN_UINT32(0u, g_ctx_s.addFastTaskCnt_u32);
}

void test_APPSNS_Cyclic_reaches_ope(void)
{
    t_eCyclicModState state_e = STATE_CYCLIC_ERROR;
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, APPSNS_Cyclic());
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, APPSNS_Cyclic());
    TEST_ASSERT_EQUAL(RC_OK, APPSNS_Cyclic());
    TEST_ASSERT_EQUAL(RC_OK, APPSNS_GetState(&state_e));
    TEST_ASSERT_EQUAL(STATE_CYCLIC_PREOPE, state_e);
    TEST_ASSERT_EQUAL(RC_OK, APPSNS_Cyclic());
    TEST_ASSERT_EQUAL(RC_OK, APPSNS_GetState(&state_e));
    TEST_ASSERT_EQUAL(STATE_CYCLIC_OPE, state_e);
}

void test_APPSNS_GetValue_busy_when_not_ope(void)
{
    t_sAPPSNS_SnsValueInfo info_s = {0};
    info_s.rqstedUnity_u8 = (t_uint8)APPSNS_ANGLE_UNIT_RADIAN;
    TEST_ASSERT_EQUAL(RC_WARNING_MISSING_CONFIG, APPSNS_Get_SnsValue(APPSNS_SNSITF_ECDR_XL_POS, &info_s));
}

void test_APPSNS_GetValue_nominal_in_ope(void)
{
    t_uint8 idx_u8;
    t_sAPPSNS_SnsValueInfo info_s = {0};
    info_s.rqstedUnity_u8 = (t_uint8)APPSNS_ANGLE_UNIT_RADIAN;

    TEST_ASSERT_EQUAL(RC_OK, APPSNS_SetState(STATE_CYCLIC_OPE));
    for(idx_u8 = (t_uint8)0; idx_u8 < (t_uint8)APPSNS_SNSDVC_NB; idx_u8++)
    {
        g_SnsDeviceInfo_as[idx_u8].isConfigured_b = TRUE;
    }

    TEST_ASSERT_EQUAL(RC_OK, APPSNS_Get_SnsValue(APPSNS_SNSITF_ECDR_XL_POS, &info_s));
    TEST_ASSERT_TRUE(info_s.isValueOK_b == TRUE);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 100.0f, info_s.SnsValue_f32);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_APPSNS_GetState_null_returns_error);
    RUN_TEST(test_APPSNS_Init_registers_fasttask);
    RUN_TEST(test_APPSNS_Cyclic_reaches_ope);
    RUN_TEST(test_APPSNS_GetValue_busy_when_not_ope);
    RUN_TEST(test_APPSNS_GetValue_nominal_in_ope);
    return UNITY_END();
}
