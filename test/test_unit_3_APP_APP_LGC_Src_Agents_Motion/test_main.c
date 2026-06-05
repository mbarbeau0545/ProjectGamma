#include <string.h>
#include <unity.h>

#include "Constant.h"
#include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
#include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
#include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
#include "APP_CTRL/APP_ACT/Src/APP_ACT.h"
#include "APP_CTRL/APP_SNS/Src/APP_SNS_CAL.h"
#include "APP_LGC/Src/APP_LGC.h"
#include "mock_FMKCPU.h"

#include "mock_FMKCPU.c"

typedef struct
{
    t_uint32 assertCnt_u32;
    t_uint16 lastAssert_u16;

    t_cbAPPSIG_MsgRcvCallback *msgCb_apcb[APPSIG_CAN_MSG_NB];
    t_uint32 addMsgCbCnt_u32;

    t_eReturnCode sysOptRet_e;
    t_eReturnCode getSnsRet_e;
    t_eReturnCode setActRet_e;
    t_eReturnCode spmRet_e;
    t_eReturnCode srvHealthRet_e;
    t_eAPPLGC_SrvHealth srvHealth_e;

    t_float32 snsValues_af32[APPSNS_SNSITF_NB];

    t_uint32 setActCnt_u32;
    t_eAPPACT_ActInterface setActIf_ae[64];
    t_float32 setActVal_af32[64];

    t_uint32 setSignalCnt_u32;
    t_eAPPSIG_Signal lastSetSignal_e;
    t_float32 lastSetSignalVal_f32;
    t_uint32 forceMsgCnt_u32;
    t_uint16 lastForcedMsg_u16;

    t_uint32 registerRefCnt_u32;
    t_eAPPSNS_SnsInterface lastRefSns_e;
    t_float32 lastRefMeasured_f32;
    t_float32 lastRefExpected_f32;
} t_sMOTTestCtx;

static t_sMOTTestCtx g_ctx_s;

void APPSYS_AssertionTrap(t_uint16 f_Info_u16, const char *f_file_str, t_uint32 f_line_u32, t_uint32 f_captureTime_u32)
{
    (void)f_file_str;
    (void)f_line_u32;
    (void)f_captureTime_u32;
    g_ctx_s.assertCnt_u32++;
    g_ctx_s.lastAssert_u16 = f_Info_u16;
}

t_eReturnCode APPSIG_AddRcvMsgCallback(t_uint16 f_msgID_u16,
                                       t_eAPPSIG_MsgOrigin f_msgOrigin_e,
                                       t_cbAPPSIG_MsgRcvCallback *f_msgRcvCallback_pcb)
{
    if((f_msgOrigin_e >= APPSIG_MSG_ORIGIN_NB)
    || (f_msgID_u16 >= (t_uint16)APPSIG_CAN_MSG_NB)
    || (f_msgRcvCallback_pcb == NULL_FUNCTION))
    {
        return RC_ERROR_PARAM_INVALID;
    }

    g_ctx_s.msgCb_apcb[f_msgID_u16] = f_msgRcvCallback_pcb;
    g_ctx_s.addMsgCbCnt_u32++;
    return RC_OK;
}

t_eReturnCode APPSYS_GetSysOption(t_eAPPSYS_SysOptionList f_OptionID_e, t_uint8 *f_OptVal_pu8)
{
    if(f_OptVal_pu8 == NULL)
    {
        return RC_ERROR_PTR_NULL;
    }
    if(g_ctx_s.sysOptRet_e != RC_OK)
    {
        return g_ctx_s.sysOptRet_e;
    }

    switch(f_OptionID_e)
    {
        case APPSYS_OPT_ID_SYS_ROBOT_DIR_FORWARD:
            *f_OptVal_pu8 = APPSYS_OPT_SYS_ROBOT_DIR_FORWARD_ENABLE;
        break;
        case APPSYS_OPT_ID_SYS_ROBOT_DIR_BACKWARD:
            *f_OptVal_pu8 = APPSYS_OPT_SYS_ROBOT_DIR_BACKWARD_ENABLE;
        break;
        case APPSYS_OPT_ID_SYS_ROBOT_PROP_FORWARD:
            *f_OptVal_pu8 = APPSYS_OPT_SYS_ROBOT_PROP_FORWARD_ENABLE;
        break;
        case APPSYS_OPT_ID_SYS_ROBOT_PROP_BACKWARD:
            *f_OptVal_pu8 = APPSYS_OPT_SYS_ROBOT_PROP_BACKWARD_ENABLE;
        break;
        case APPSYS_OPT_ID_SNS_ECDR_WHL_AV_L:
            *f_OptVal_pu8 = APPSYS_OPT_SNS_ECDR_WHL_AV_L_NEMA17;
        break;
        case APPSYS_OPT_ID_SNS_ECDR_WHL_AV_R:
            *f_OptVal_pu8 = APPSYS_OPT_SNS_ECDR_WHL_AV_R_NEMA17;
        break;
        default:
            *f_OptVal_pu8 = 1u;
        break;
    }

    return RC_OK;
}

t_eReturnCode APPSPM_GetParam(t_eAPPSPM_ItemPrm f_itemId_e, t_uAPPSPM_PrmValType *f_prmValue_pu)
{
    if(f_prmValue_pu == NULL)
    {
        return RC_ERROR_PTR_NULL;
    }
    if(g_ctx_s.spmRet_e != RC_OK)
    {
        return g_ctx_s.spmRet_e;
    }

    switch(f_itemId_e)
    {
        case APPSPM_PRM_MOT_ACTDIR_WHAVL_PULSE_TO_RAD:
        case APPSPM_PRM_MOT_ACTDIR_WHAVR_PULSE_TO_RAD:
            f_prmValue_pu->prmVal_u16 = 6283u;
        break;
        case APPSPM_PRM_MOT_ACTDIR_WHAVL_RPM_TO_HZ:
        case APPSPM_PRM_MOT_ACTDIR_WHAVR_RPM_TO_HZ:
            f_prmValue_pu->prmVal_f32 = 1.0f;
        break;
        default:
            f_prmValue_pu->prmVal_u16 = 1u;
        break;
    }

    return RC_OK;
}

t_eReturnCode APPLGC_GetServiceHealth(t_eAPPLGC_SrvList f_service_e, t_eAPPLGC_SrvHealth *f_srvHealth_pe)
{
    (void)f_service_e;
    if(f_srvHealth_pe == NULL)
    {
        return RC_ERROR_PTR_NULL;
    }
    if(g_ctx_s.srvHealthRet_e != RC_OK)
    {
        return g_ctx_s.srvHealthRet_e;
    }
    *f_srvHealth_pe = g_ctx_s.srvHealth_e;
    return RC_OK;
}

t_eReturnCode APPLGC_GetSnsValue(t_eAPPSNS_SnsInterface f_snsIfID_e, t_float32 *f_snsValue_pf32)
{
    if((f_snsIfID_e >= APPSNS_SNSITF_NB) || (f_snsValue_pf32 == NULL))
    {
        return RC_ERROR_PARAM_INVALID;
    }
    if(g_ctx_s.getSnsRet_e != RC_OK)
    {
        return g_ctx_s.getSnsRet_e;
    }

    *f_snsValue_pf32 = g_ctx_s.snsValues_af32[f_snsIfID_e];
    return RC_OK;
}

t_eReturnCode APPACT_SetActValue(t_eAPPACT_ActInterface f_actuator_e, t_float32 f_actValue_f32)
{
    if(g_ctx_s.setActCnt_u32 < 64u)
    {
        g_ctx_s.setActIf_ae[g_ctx_s.setActCnt_u32] = f_actuator_e;
        g_ctx_s.setActVal_af32[g_ctx_s.setActCnt_u32] = f_actValue_f32;
    }
    g_ctx_s.setActCnt_u32++;
    return g_ctx_s.setActRet_e;
}

t_eReturnCode APPSIG_SetSignalValue(t_eAPPSIG_Signal f_signal_e, t_float32 f_value_f32)
{
    g_ctx_s.lastSetSignal_e = f_signal_e;
    g_ctx_s.lastSetSignalVal_f32 = f_value_f32;
    g_ctx_s.setSignalCnt_u32++;
    return RC_OK;
}

t_eReturnCode APPSIG_ForceMsgSend(t_eAPPSIG_MsgOrigin f_origin_e, t_uint16 f_msgID_u16)
{
    (void)f_origin_e;
    g_ctx_s.lastForcedMsg_u16 = f_msgID_u16;
    g_ctx_s.forceMsgCnt_u32++;
    return RC_OK;
}

t_eReturnCode APPSNSCAL_RegisterReference(t_eAPPSNS_SnsInterface f_sns_e,
                                          t_float32 f_measuredValue_f32,
                                          t_float32 f_expectedValue_f32)
{
    g_ctx_s.lastRefSns_e = f_sns_e;
    g_ctx_s.lastRefMeasured_f32 = f_measuredValue_f32;
    g_ctx_s.lastRefExpected_f32 = f_expectedValue_f32;
    g_ctx_s.registerRefCnt_u32++;
    return RC_OK;
}

#include "APP_LGC/Src/Agents/Motion/Src/MOTION.c"

static void s_push_dir_msg(t_float32 avlPos_mrad,
                           t_float32 avrPos_mrad,
                           t_float32 avlSpd_rpm,
                           t_float32 avrSpd_rpm)
{
    t_eAPPSIG_Signal sig_ae[4] = {
        APPSIG_SIGNAL_LGC_MOT_CMD_WHL_AVL_DIR,
        APPSIG_SIGNAL_LGC_MOT_CMD_WHL_AVR_DIR,
        APPSIG_SIGNAL_LGC_MOT_CMD_WHL_AVL_DIR_SPD,
        APPSIG_SIGNAL_LGC_MOT_CMD_WHL_AVR_DIR_SPD
    };
    t_float32 val_af32[4] = {avlPos_mrad, avrPos_mrad, avlSpd_rpm, avrSpd_rpm};
    s_MOT_MsgReceptionCallback((t_uint16)APPSIG_CAN_MSG_LGC_MOT_CMD_WHL_AV_POSITION, (t_uint8)4, sig_ae, val_af32);
}

static void s_push_calib_msg(t_eAPPSNS_SnsInterface snsItf_e,
                             t_eAPPLGC_CalibStatus reqSts_e,
                             t_float32 pulse_f32,
                             t_float32 speed_f32)
{
    t_eAPPSIG_Signal sig_ae[4] = {
        APPSIG_SIGNAL_LGC_CMD_CALIB_ID,
        APPSIG_SIGNAL_LGC_CMD_CALIB_REQ_STATE,
        APPSIG_SIGNAL_LGC_CMD_CALIB_PLS,
        APPSIG_SIGNAL_LGC_CMD_CALIB_SPD
    };
    t_float32 val_af32[4] = {(t_float32)snsItf_e, (t_float32)reqSts_e, pulse_f32, speed_f32};
    s_MOT_MsgReceptionCallback((t_uint16)APPSIG_CAN_MSG_LGC_MOT_CMD_CALIBRATION, (t_uint8)4, sig_ae, val_af32);
}

void setUp(void)
{
    t_uint16 idx_u16;
    (void)memset(&g_ctx_s, 0, sizeof(g_ctx_s));
    g_ctx_s.sysOptRet_e = RC_OK;
    g_ctx_s.getSnsRet_e = RC_OK;
    g_ctx_s.setActRet_e = RC_OK;
    g_ctx_s.spmRet_e = RC_OK;
    g_ctx_s.srvHealthRet_e = RC_OK;
    g_ctx_s.srvHealth_e = APPLGC_SRV_HEALTH_OK;
    for(idx_u16 = 0u; idx_u16 < (t_uint16)APPSNS_SNSITF_NB; idx_u16++)
    {
        g_ctx_s.snsValues_af32[idx_u16] = 0.0f;
    }
    TEST_ASSERT_EQUAL(RC_OK, MOTION_Init());
}

void tearDown(void)
{
}

void test_calibration_sequence_success_until_register_value(void)
{
    g_ctx_s.snsValues_af32[APPSNS_SNSITF_ECDR_WHL_AV_L_POS] = 321.0f;

    s_push_calib_msg(APPSNS_SNSITF_ECDR_WHL_AV_L_POS,
                     APPLGC_CALIB_REQSTS_MOVE,
                     100.0f,
                     200.0f);
    TEST_ASSERT_EQUAL(RC_OK, s_MOT_Fsm_PrdTsk_Calibration());
    TEST_ASSERT_EQUAL(APPLGC_CALIB_REQSTS_MOVE, g_calibCmdInfo_s.currSts_e);

    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, s_MOT_Fsm_PrdTsk_Calibration());
    TEST_ASSERT_TRUE(g_calibCmdInfo_s.isNewCmdReceiv_b == FALSE);
    TEST_ASSERT_GREATER_THAN_UINT32(0u, g_ctx_s.setActCnt_u32);

    g_calibCmdInfo_s.reqSts_e = APPLGC_CALIB_REQSTS_REGISTER_VALUE;
    g_calibCmdInfo_s.currSts_e = APPLGC_CALIB_REQSTS_REGISTER_VALUE;

    TEST_ASSERT_EQUAL(RC_OK, s_MOT_Fsm_PrdTsk_Calibration());
    TEST_ASSERT_EQUAL_UINT32(1u, g_ctx_s.registerRefCnt_u32);
    TEST_ASSERT_EQUAL(APPSNS_SNSITF_ECDR_WHL_AV_L_POS, g_ctx_s.lastRefSns_e);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 321.0f, g_ctx_s.lastRefMeasured_f32);
    TEST_ASSERT_EQUAL(APPLGC_CALIB_REQSTS_IDLE, g_calibCmdInfo_s.reqSts_e);
    TEST_ASSERT_EQUAL(APPLGC_CALIB_REQSTS_IDLE, g_calibCmdInfo_s.currSts_e);
}

void test_calibration_fails_when_setpoint_write_fails(void)
{
    s_push_calib_msg(APPSNS_SNSITF_ECDR_WHL_AV_L_POS,
                     APPLGC_CALIB_REQSTS_MOVE,
                     100.0f,
                     200.0f);
    TEST_ASSERT_EQUAL(RC_OK, s_MOT_Fsm_PrdTsk_Calibration());

    g_ctx_s.setActRet_e = RC_ERROR_WRONG_RESULT;
    TEST_ASSERT_EQUAL(RC_ERROR_WRONG_RESULT, s_MOT_Fsm_PrdTsk_Calibration());
}

void test_whl_av_position_command_reaches_direction_mngmt_and_sets_coherent_pulse_and_speed(void)
{
    t_float32 leftPosNow_mrad = 200.0f;
    t_float32 rightPosNow_mrad = -100.0f;
    t_sint32 leftExpectedPulse_s32 = 800;
    t_sint32 rightExpectedPulse_s32 = -400;
    t_float32 leftExpectedHz_f32 = 120.0f;
    t_float32 rightExpectedHz_f32 = 60.0f;

    g_ctx_s.snsValues_af32[APPSNS_SNSITF_ECDR_WHL_AV_L_POS] = leftPosNow_mrad;
    g_ctx_s.snsValues_af32[APPSNS_SNSITF_ECDR_WHL_AV_R_POS] = rightPosNow_mrad;

    s_push_dir_msg(1000.0f, -500.0f, 120.0f, 60.0f);

    TEST_ASSERT_EQUAL(RC_OK, s_MOT_PrdTsk_Ope_DirectionMngmt());
    TEST_ASSERT_TRUE(g_MtrDirPayload_as[MOT_ACTDIR_WHL_AV_L].isReqCmd_b == FALSE);
    TEST_ASSERT_TRUE(g_MtrDirPayload_as[MOT_ACTDIR_WHL_AV_R].isReqCmd_b == FALSE);

    TEST_ASSERT_GREATER_OR_EQUAL_UINT32(6u, g_ctx_s.setActCnt_u32);
    TEST_ASSERT_EQUAL(APPACT_ACTITF_MTR_WHL_AV_L_PLS, g_ctx_s.setActIf_ae[0]);
    TEST_ASSERT_FLOAT_WITHIN(1.0f, (t_float32)leftExpectedPulse_s32, g_ctx_s.setActVal_af32[0]);
    TEST_ASSERT_EQUAL(APPACT_ACTITF_MTR_WHL_AV_L_SPD, g_ctx_s.setActIf_ae[1]);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, leftExpectedHz_f32, g_ctx_s.setActVal_af32[1]);
    TEST_ASSERT_EQUAL(APPACT_ACTITF_MTR_WHL_AV_R_PLS, g_ctx_s.setActIf_ae[3]);
    TEST_ASSERT_FLOAT_WITHIN(1.0f, (t_float32)rightExpectedPulse_s32, g_ctx_s.setActVal_af32[3]);
    TEST_ASSERT_EQUAL(APPACT_ACTITF_MTR_WHL_AV_R_SPD, g_ctx_s.setActIf_ae[4]);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, rightExpectedHz_f32, g_ctx_s.setActVal_af32[4]);
}

void test_state_machine_preops_negative_retcode_goes_to_safety(void)
{
    g_ctx_s.sysOptRet_e = RC_ERROR_WRONG_CONFIG;
    g_Fsm_PrdcTskSts_e = MOT_FSM_PRD_TSK_PRE_OPS;

    TEST_ASSERT_EQUAL(RC_ERROR_WRONG_CONFIG, s_MOT_StateMachine());
    TEST_ASSERT_EQUAL(MOT_FSM_PRD_TSK_SAFETY, g_Fsm_PrdcTskSts_e);
}

void test_state_machine_calibration_negative_retcode_goes_to_safety(void)
{
    g_ctx_s.getSnsRet_e = RC_ERROR_WRONG_RESULT;
    g_Fsm_PrdcTskSts_e = MOT_FSM_PRD_TSK_CALIB_AXE;
    g_calibCmdInfo_s.reqSts_e = APPLGC_CALIB_REQSTS_REGISTER_VALUE;
    g_calibCmdInfo_s.currSts_e = APPLGC_CALIB_REQSTS_REGISTER_VALUE;
    g_calibCmdInfo_s.snsItf_e = APPSNS_SNSITF_ECDR_WHL_AV_L_POS;

    TEST_ASSERT_EQUAL(RC_ERROR_WRONG_RESULT, s_MOT_StateMachine());
    TEST_ASSERT_EQUAL(MOT_FSM_PRD_TSK_SAFETY, g_Fsm_PrdcTskSts_e);
}

void test_state_machine_ops_negative_retcode_goes_to_safety(void)
{
    s_push_dir_msg(1000.0f, -500.0f, 120.0f, 60.0f);
    g_ctx_s.spmRet_e = RC_ERROR_WRONG_CONFIG;
    g_Fsm_PrdcTskSts_e = MOT_FSM_PRD_TSK_OPS;

    TEST_ASSERT_EQUAL(RC_ERROR_WRONG_CONFIG, s_MOT_StateMachine());
    TEST_ASSERT_EQUAL(MOT_FSM_PRD_TSK_SAFETY, g_Fsm_PrdcTskSts_e);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_calibration_sequence_success_until_register_value);
    RUN_TEST(test_calibration_fails_when_setpoint_write_fails);
    RUN_TEST(test_whl_av_position_command_reaches_direction_mngmt_and_sets_coherent_pulse_and_speed);
    RUN_TEST(test_state_machine_preops_negative_retcode_goes_to_safety);
    RUN_TEST(test_state_machine_calibration_negative_retcode_goes_to_safety);
    RUN_TEST(test_state_machine_ops_negative_retcode_goes_to_safety);
    return UNITY_END();
}
