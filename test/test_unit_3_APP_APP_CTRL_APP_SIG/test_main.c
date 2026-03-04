#include <string.h>
#include <unity.h>

#include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
#include "FMK_HAL/FMK_CAN/Src/FMK_FDCAN.h"
#include "mock_FMKCPU.h"

#include "mock_FMKCPU.c"
#include "APP_CTRL/APP_SIG/Src/APP_SIG.c"

typedef struct
{
    t_uint32 count_u32;
    t_uint16 lastInfo_u16;
} t_sAssertCtx;

static t_sAssertCtx g_assertCtx_s;

void APPSYS_AssertionTrap(t_uint16 f_Info_u16, const char * f_file_str, t_uint32 f_line_u32, t_uint32 f_captureTime_u32)
{
    (void)f_file_str;
    (void)f_line_u32;
    (void)f_captureTime_u32;
    g_assertCtx_s.count_u32++;
    g_assertCtx_s.lastInfo_u16 = f_Info_u16;
}

t_eReturnCode APPSYS_GetEcuPosition(t_eAPPSYS_EcuPos * f_ecuPos_pe)
{
    if(f_ecuPos_pe == NULL)
    {
        return RC_ERROR_PTR_NULL;
    }
    *f_ecuPos_pe = APPSYS_ECU_POS_GTRY;
    return RC_OK;
}

t_eReturnCode APPSYS_SetFastTaskState(t_eAppSys_ModuleList f_ModuleId_e,  t_eAPPSYS_FastTaskState f_state_e)
{
    (void)f_ModuleId_e;
    (void)f_state_e;
    return RC_OK;
}

t_eReturnCode APPSYS_AddFastTask(t_eAppSys_ModuleList f_ModuleId_e, t_cbAPPSYS_FastTask * f_moduleFastTask_pcb)
{
    (void)f_ModuleId_e;
    (void)f_moduleFastTask_pcb;
    return RC_OK;
}

void APPSDM_ReportDiagEvnt(t_eAPPSDM_DiagnosticItem f_item_e, t_eAPPSDM_DiagnosticReport f_reportState_e, t_uint16 f_debugInfo1_u16, t_uint16 f_debugInfo2_u16)
{
    (void)f_item_e;
    (void)f_reportState_e;
    (void)f_debugInfo1_u16;
    (void)f_debugInfo2_u16;
}

t_eReturnCode SafeMem_memcpy(void *f_destination_pv, const void *f_src_pv, t_uint16 f_size_u16)
{
    (void)memcpy(f_destination_pv, f_src_pv, f_size_u16);
    return RC_OK;
}

t_eReturnCode SafeMem_memclear(void *f_buffer_pv, t_uint16 f_size_u16)
{
    (void)memset(f_buffer_pv, 0, f_size_u16);
    return RC_OK;
}

t_eReturnCode LIBQUEUE_Create(t_sLIBQUEUE_QueueCore *f_Queue_ps, t_sLIBQUEUE_QueueCfg f_QueueCfg_s)
{
    if(f_Queue_ps == NULL)
    {
        return RC_ERROR_PTR_NULL;
    }
    f_Queue_ps->QueueCfg_s = f_QueueCfg_s;
    f_Queue_ps->head_u16 = 0u;
    f_Queue_ps->tail_u16 = 0u;
    f_Queue_ps->actualSize_u16 = 0u;
    return RC_OK;
}

t_eReturnCode LIBQUEUE_WriteElement(t_sLIBQUEUE_QueueCore *f_Queue_ps, const void *f_element_pv, t_uint16 f_size_u16)
{
    (void)f_Queue_ps;
    (void)f_element_pv;
    (void)f_size_u16;
    return RC_OK;
}

t_eReturnCode LIBQUEUE_ReadElement(t_sLIBQUEUE_QueueCore *f_Queue_ps, void * f_element_pv, t_uint16 f_size_u16)
{
    (void)f_Queue_ps;
    (void)f_element_pv;
    (void)f_size_u16;
    return RC_WARNING_NO_OPERATION;
}

t_eReturnCode FMKSRL_InitDrv(t_eFMKSRL_SerialLine f_SrlLine_e, t_sFMKSRL_DrvSerialCfg f_SerialCfg_s, t_cbFMKSRL_RcvMsgEvent * f_rcvMsgEvnt_pcb, t_cbFMKSRL_TransmitMsgEvent * f_txMsgEvnt_pcb)
{
    (void)f_SrlLine_e;
    (void)f_SerialCfg_s;
    (void)f_rcvMsgEvnt_pcb;
    (void)f_txMsgEvnt_pcb;
    return RC_OK;
}

t_eReturnCode FMKSRL_ConfigureReception(t_eFMKSRL_SerialLine f_SrlLine_e, t_eFMKSRL_RxOpeMode f_OpeMode_e, t_uint16 f_InfoOpe_u16)
{
    (void)f_SrlLine_e;
    (void)f_OpeMode_e;
    (void)f_InfoOpe_u16;
    return RC_OK;
}

t_eReturnCode FMKSRL_Transmit(t_eFMKSRL_SerialLine f_SrlLine_e, t_eFMKSRL_TxOpeMode f_OpeMode_e, t_uint8 * f_msgData_pu8, t_uint16 f_dataSize_u16, t_uint16 f_InfoMode_u16, t_bool f_EnableTxCb_b)
{
    (void)f_SrlLine_e;
    (void)f_OpeMode_e;
    (void)f_msgData_pu8;
    (void)f_dataSize_u16;
    (void)f_InfoMode_u16;
    (void)f_EnableTxCb_b;
    return RC_OK;
}

void FMKSRL_LogUartSend(t_eFMKSRL_SerialLine f_SrlLine_e, const t_char * fmt, ...)
{
    (void)f_SrlLine_e;
    (void)fmt;
}

t_eReturnCode FMKFDCAN_ConfigureRxItemEvent(t_eFMKFDCAN_NodeList f_Node_e, t_sFMKFDCAN_RxItemEventCfg f_RxItemCfg_s)
{
    (void)f_Node_e;
    (void)f_RxItemCfg_s;
    return RC_OK;
}

t_eReturnCode FMKFDCAN_SendTxItem(t_eFMKFDCAN_NodeList f_Node_e, t_sFMKFDCAN_TxItem f_TxItemCfg_s)
{
    (void)f_Node_e;
    (void)f_TxItemCfg_s;
    return RC_OK;
}

static void s_TestSigCb(t_eAPPSIG_Signal f_signal_e, t_float32 f_sigValue_f32)
{
    (void)f_signal_e;
    (void)f_sigValue_f32;
}

static void s_TestMsgCb(t_uint16 f_msgID_u16, t_uint8 f_nbSignal_u8, t_eAPPSIG_Signal *f_signal_ae, t_float32 *f_sigValue_af32)
{
    (void)f_msgID_u16;
    (void)f_nbSignal_u8;
    (void)f_signal_ae;
    (void)f_sigValue_af32;
}

void setUp(void)
{
    (void)memset(&g_assertCtx_s, 0, sizeof(g_assertCtx_s));
    mock_FMKCPU_ResetTick();
    TEST_ASSERT_EQUAL(RC_OK, APPSIG_Init());
    TEST_ASSERT_EQUAL(RC_OK, APPSIG_SetState(STATE_CYCLIC_CFG));
}

void tearDown(void)
{
}

void test_APPSIG_GetState_null_returns_error(void)
{
    TEST_ASSERT_EQUAL(RC_ERROR_PTR_NULL, APPSIG_GetState((t_eCyclicModState *)NULL));
}

void test_APPSIG_SetSignal_invalid_id_returns_error(void)
{
    TEST_ASSERT_EQUAL(RC_ERROR_PARAM_INVALID, APPSIG_SetSignalValue(APPSIG_SIGNAL_NB, 1.0f));
    TEST_ASSERT_EQUAL_UINT32(1u, g_assertCtx_s.count_u32);
}

void test_APPSIG_SetGetSignal_nominal(void)
{
    t_float32 value_f32 = 0.0f;

    TEST_ASSERT_EQUAL(RC_OK, APPSIG_SetSignalValue(APPSIG_SIGNAL_APPSYS_MODSTATE, 12.5f));
    TEST_ASSERT_EQUAL(RC_WARNING_NO_OPERATION, APPSIG_GetSignalValue(APPSIG_SIGNAL_APPSYS_MODSTATE, &value_f32));

    g_signalInfo_as[APPSIG_SIGNAL_APPSYS_MODSTATE].isRcvOnce_b = TRUE;
    TEST_ASSERT_EQUAL(RC_OK, APPSIG_GetSignalValue(APPSIG_SIGNAL_APPSYS_MODSTATE, &value_f32));
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 12.5f, value_f32);
}

void test_APPSIG_AddRcvSigCallback_validation_and_limit(void)
{
    TEST_ASSERT_EQUAL(RC_ERROR_PARAM_INVALID, APPSIG_AddRcvSigCallback(APPSIG_SIGNAL_NB, s_TestSigCb));
    TEST_ASSERT_EQUAL(RC_ERROR_PTR_NULL, APPSIG_AddRcvSigCallback(APPSIG_SIGNAL_APPSYS_MODSTATE, NULL));
    TEST_ASSERT_EQUAL(RC_OK, APPSIG_AddRcvSigCallback(APPSIG_SIGNAL_APPSYS_MODSTATE, s_TestSigCb));
    TEST_ASSERT_EQUAL(RC_ERROR_LIMIT_REACHED, APPSIG_AddRcvSigCallback(APPSIG_SIGNAL_APPSYS_MODSTATE, s_TestSigCb));
}

void test_APPSIG_AddRcvMsgCallback_validation_and_limit(void)
{
    TEST_ASSERT_EQUAL(RC_ERROR_PARAM_INVALID, APPSIG_AddRcvMsgCallback(0u, APPSIG_MSG_ORIGIN_NB, s_TestMsgCb));
    TEST_ASSERT_EQUAL(RC_ERROR_PTR_NULL, APPSIG_AddRcvMsgCallback(0u, APPSIG_MSG_ORIGIN_CAN, NULL));
    TEST_ASSERT_EQUAL(RC_OK, APPSIG_AddRcvMsgCallback(0u, APPSIG_MSG_ORIGIN_CAN, s_TestMsgCb));
    TEST_ASSERT_EQUAL(RC_ERROR_LIMIT_REACHED, APPSIG_AddRcvMsgCallback(0u, APPSIG_MSG_ORIGIN_CAN, s_TestMsgCb));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_APPSIG_GetState_null_returns_error);
    RUN_TEST(test_APPSIG_SetSignal_invalid_id_returns_error);
    RUN_TEST(test_APPSIG_SetGetSignal_nominal);
    RUN_TEST(test_APPSIG_AddRcvSigCallback_validation_and_limit);
    RUN_TEST(test_APPSIG_AddRcvMsgCallback_validation_and_limit);
    return UNITY_END();
}
