#include <math.h>
#include <string.h>
#include <unity.h>

#include "APP_CFG/ConfigSpecific/GANTRY_ConfigSpecific.h"
#include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
#include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
#include "Constant.h"
#include "Library/QUEUE/Src/LIBQueue.h"
#include "Library/SafeMem/SafeMem.h"
#include "mock_FMKCPU.h"

#include "mock_FMKCPU.c"
#include "Library/SafeMem/SafeMem.c"
#include "Library/QUEUE/Src/LIBQueue.c"
#include "APP_CFG/ConfigSpecific/GANTRY_ConfigSpecific.c"

typedef struct
{
    t_uint32 assertCnt_u32;
    t_uint16 lastAssert_u16;
    t_float32 currentPos_af32[GTRY_PHYS_AXE_NB];
    t_uint16 pulsePerMm_u16[GTRY_PHYS_AXE_NB];
} t_sGantryTestCtx;

static t_sGantryTestCtx g_ctx_s;

static t_sGTRY_MtrCmdIterPayload g_axisCmd_aa[GTRY_PHYS_AXE_NB][GTRY_MAX_ITERATION];
static t_sLIBQUEUE_QueueCore g_queue_as[GTRY_PHYS_AXE_NB];
static t_uint8 g_queueBuf_au8[GTRY_PHYS_AXE_NB][GTRY_MAX_ITERATION * sizeof(t_sGTRY_MtrCmdIterPayload)];

void APPSYS_AssertionTrap(t_uint16 f_Info_u16, const char * f_file_str, t_uint32 f_line_u32, t_uint32 f_captureTime_u32)
{
    (void)f_file_str;
    (void)f_line_u32;
    (void)f_captureTime_u32;
    g_ctx_s.assertCnt_u32++;
    g_ctx_s.lastAssert_u16 = f_Info_u16;
}

t_eReturnCode GTRY_GetPosition(t_float32 f_currPos_af32[GTRY_PHYS_AXE_NB])
{
    if(f_currPos_af32 == NULL)
    {
        return RC_ERROR_PTR_NULL;
    }
    for(t_uint8 idx_u8 = (t_uint8)0; idx_u8 < (t_uint8)GTRY_PHYS_AXE_NB; idx_u8++)
    {
        f_currPos_af32[idx_u8] = g_ctx_s.currentPos_af32[idx_u8];
    }
    return RC_OK;
}

t_eReturnCode APPSPM_GetParam(t_eAPPSPM_ItemPrm f_itemId_e, t_uAPPSPM_PrmValType * f_prmValue_pu)
{
    if(f_prmValue_pu == NULL)
    {
        return RC_ERROR_PTR_NULL;
    }

    switch(f_itemId_e)
    {
        case APPSPM_PRM_GTRY_AXE_X_PULSE_PER_MM:
            f_prmValue_pu->prmVal_u16 = g_ctx_s.pulsePerMm_u16[GTRY_PHYS_AXE_X];
        break;
        case APPSPM_PRM_GTRY_AXE_Y_PULSE_PER_MM:
            f_prmValue_pu->prmVal_u16 = g_ctx_s.pulsePerMm_u16[GTRY_PHYS_AXE_Y];
        break;
        case APPSPM_PRM_GTRY_AXE_Z_PULSE_PER_MM:
            f_prmValue_pu->prmVal_u16 = g_ctx_s.pulsePerMm_u16[GTRY_PHYS_AXE_Z];
        break;
        default:
            f_prmValue_pu->prmVal_u16 = 1u;
        break;
    }
    return RC_OK;
}

static void s_init_default_algo_param(void)
{
    t_sGTRYSPEC_AlgoParameter param_s;

    (void)memset(&param_s, 0, sizeof(param_s));
    param_s.chunkSize_u16 = 10u;

    param_s.MinFreq_af32[GTRY_PHYS_AXE_X] = 100.0f;
    param_s.MinFreq_af32[GTRY_PHYS_AXE_Y] = 100.0f;
    param_s.MinFreq_af32[GTRY_PHYS_AXE_Z] = 100.0f;

    param_s.MaxFreq_af32[GTRY_PHYS_AXE_X] = 1000.0f;
    param_s.MaxFreq_af32[GTRY_PHYS_AXE_Y] = 1000.0f;
    param_s.MaxFreq_af32[GTRY_PHYS_AXE_Z] = 1000.0f;

    param_s.pulsePerMm_af32[GTRY_PHYS_AXE_X] = 10.0f;
    param_s.pulsePerMm_af32[GTRY_PHYS_AXE_Y] = 10.0f;
    param_s.pulsePerMm_af32[GTRY_PHYS_AXE_Z] = 10.0f;

    param_s.cptPrio_SafeHeight_af32[GTRY_PHYS_AXE_X] = 2.0f;
    param_s.cptPrio_SafeHeight_af32[GTRY_PHYS_AXE_Y] = 2.0f;
    param_s.cptPrio_SafeHeight_af32[GTRY_PHYS_AXE_Z] = 2.0f;

    TEST_ASSERT_EQUAL(RC_OK, GANTRY_SPEC_AlgorithmSetParam(param_s));
}

static void s_init_axis_queues(t_uint8 f_capacity_u8)
{
    t_sLIBQUEUE_QueueCfg cfg_s;

    for(t_uint8 idx_u8 = (t_uint8)0; idx_u8 < (t_uint8)GTRY_PHYS_AXE_NB; idx_u8++)
    {
        (void)memset(g_queueBuf_au8[idx_u8], 0, sizeof(g_queueBuf_au8[idx_u8]));
        cfg_s.bufferHead_pv = g_queueBuf_au8[idx_u8];
        cfg_s.elementSize_u16 = (t_uint8)sizeof(t_sGTRY_MtrCmdIterPayload);
        cfg_s.actualSize_u16 = f_capacity_u8;
        cfg_s.enableOverwrite_b = False;
        TEST_ASSERT_EQUAL(RC_OK, LIBQUEUE_Create(&g_queue_as[idx_u8], cfg_s));
    }
}

static void s_drain_axis_queues(t_uint8 f_counts_au8[GTRY_PHYS_AXE_NB])
{
    for(t_uint8 idxAxe_u8 = (t_uint8)0; idxAxe_u8 < (t_uint8)GTRY_PHYS_AXE_NB; idxAxe_u8++)
    {
        t_uint8 cnt_u8 = 0u;
        t_sGTRY_MtrCmdIterPayload elem_s;
        while(LIBQUEUE_ReadElement(&g_queue_as[idxAxe_u8], &elem_s, sizeof(elem_s)) == RC_OK)
        {
            g_axisCmd_aa[idxAxe_u8][cnt_u8] = elem_s;
            cnt_u8++;
            if(cnt_u8 >= GTRY_MAX_ITERATION)
            {
                break;
            }
        }
        f_counts_au8[idxAxe_u8] = cnt_u8;
    }
}

static t_uint32 s_sum_abs_pulses(t_eGTRY_PhysicalAxe f_axe_e, t_uint8 f_count_u8)
{
    t_uint32 sum_u32 = 0u;
    for(t_uint8 idx_u8 = 0u; idx_u8 < f_count_u8; idx_u8++)
    {
        t_sint32 pulse_s32 = g_axisCmd_aa[f_axe_e][idx_u8].pulses_s32;
        if(pulse_s32 < 0)
        {
            pulse_s32 = -pulse_s32;
        }
        sum_u32 += (t_uint32)pulse_s32;
    }
    return sum_u32;
}

static void s_assert_freq_range(t_eGTRY_PhysicalAxe f_axe_e, t_uint8 f_count_u8, t_float32 f_min_f32, t_float32 f_max_f32)
{
    for(t_uint8 idx_u8 = 0u; idx_u8 < f_count_u8; idx_u8++)
    {
        t_float32 freq_f32 = g_axisCmd_aa[f_axe_e][idx_u8].frequency_f32;
        TEST_ASSERT_TRUE(freq_f32 >= (f_min_f32 - 0.01f));
        TEST_ASSERT_TRUE(freq_f32 <= (f_max_f32 + 0.01f));
    }
}

void setUp(void)
{
    (void)memset(&g_ctx_s, 0, sizeof(g_ctx_s));
    (void)memset(g_axisCmd_aa, 0, sizeof(g_axisCmd_aa));
    (void)memset(g_queue_as, 0, sizeof(g_queue_as));
    mock_FMKCPU_ResetTick();

    g_ctx_s.pulsePerMm_u16[GTRY_PHYS_AXE_X] = 10u;
    g_ctx_s.pulsePerMm_u16[GTRY_PHYS_AXE_Y] = 10u;
    g_ctx_s.pulsePerMm_u16[GTRY_PHYS_AXE_Z] = 10u;

    s_init_default_algo_param();
    s_init_axis_queues((t_uint8)GTRY_MAX_ITERATION);
}

void tearDown(void)
{
}

void test_balanced_conserves_pulses_and_is_time_synchronized(void)
{
    t_float32 target_af32[GTRY_PHYS_AXE_NB] = {3.7f, -2.2f, 1.0f};
    t_float32 curr_af32[GTRY_PHYS_AXE_NB] = {0.0f, 0.0f, 0.0f};
    t_float32 miss_af32[GTRY_PHYS_AXE_NB] = {0.0f, 0.0f, 0.0f};
    t_uint8 counts_au8[GTRY_PHYS_AXE_NB] = {0u, 0u, 0u};

    TEST_ASSERT_EQUAL(RC_OK, GANTRY_SPEC_AlgorithmCompute(GTRY_ALGO_COMPUTE_TYPE_BALANCED, target_af32, curr_af32, miss_af32, g_queue_as));
    s_drain_axis_queues(counts_au8);

    TEST_ASSERT_EQUAL_UINT8(counts_au8[GTRY_PHYS_AXE_X], counts_au8[GTRY_PHYS_AXE_Y]);
    TEST_ASSERT_EQUAL_UINT8(counts_au8[GTRY_PHYS_AXE_X], counts_au8[GTRY_PHYS_AXE_Z]);
    TEST_ASSERT_GREATER_THAN_UINT8(0u, counts_au8[GTRY_PHYS_AXE_X]);

    TEST_ASSERT_EQUAL_UINT32(37u, s_sum_abs_pulses(GTRY_PHYS_AXE_X, counts_au8[GTRY_PHYS_AXE_X]));
    TEST_ASSERT_EQUAL_UINT32(22u, s_sum_abs_pulses(GTRY_PHYS_AXE_Y, counts_au8[GTRY_PHYS_AXE_Y]));
    TEST_ASSERT_EQUAL_UINT32(10u, s_sum_abs_pulses(GTRY_PHYS_AXE_Z, counts_au8[GTRY_PHYS_AXE_Z]));

    for(t_uint8 idx_u8 = 0u; idx_u8 < counts_au8[GTRY_PHYS_AXE_Y]; idx_u8++)
    {
        TEST_ASSERT_TRUE(g_axisCmd_aa[GTRY_PHYS_AXE_Y][idx_u8].pulses_s32 <= 0);
    }

    for(t_uint8 idx_u8 = 0u; idx_u8 < counts_au8[GTRY_PHYS_AXE_X]; idx_u8++)
    {
        t_float32 tx_f32 = g_axisCmd_aa[GTRY_PHYS_AXE_X][idx_u8].triggerTimer_f32;
        t_float32 ty_f32 = g_axisCmd_aa[GTRY_PHYS_AXE_Y][idx_u8].triggerTimer_f32;
        t_float32 tz_f32 = g_axisCmd_aa[GTRY_PHYS_AXE_Z][idx_u8].triggerTimer_f32;
        TEST_ASSERT_FLOAT_WITHIN(0.001f, tx_f32, ty_f32);
        TEST_ASSERT_FLOAT_WITHIN(0.001f, tx_f32, tz_f32);
        if(idx_u8 > 0u)
        {
            TEST_ASSERT_TRUE(tx_f32 >= g_axisCmd_aa[GTRY_PHYS_AXE_X][idx_u8 - 1u].triggerTimer_f32);
        }
    }

    s_assert_freq_range(GTRY_PHYS_AXE_X, counts_au8[GTRY_PHYS_AXE_X], 100.0f, 1000.0f);
    s_assert_freq_range(GTRY_PHYS_AXE_Y, counts_au8[GTRY_PHYS_AXE_Y], 100.0f, 1000.0f);
    s_assert_freq_range(GTRY_PHYS_AXE_Z, counts_au8[GTRY_PHYS_AXE_Z], 100.0f, 1000.0f);
}

void test_x_burstfirst_moves_x_before_other_axes(void)
{
    t_float32 target_af32[GTRY_PHYS_AXE_NB] = {3.5f, 1.2f, 0.8f};
    t_float32 curr_af32[GTRY_PHYS_AXE_NB] = {0.0f, 0.0f, 0.0f};
    t_float32 miss_af32[GTRY_PHYS_AXE_NB] = {0.0f, 0.0f, 0.0f};
    t_uint8 counts_au8[GTRY_PHYS_AXE_NB] = {0u, 0u, 0u};
    t_uint8 burstIters_u8 = 4u;

    TEST_ASSERT_EQUAL(RC_OK, GANTRY_SPEC_AlgorithmCompute(GTRY_ALGO_COMPUTE_TYPE_X_BURSTFIRST, target_af32, curr_af32, miss_af32, g_queue_as));
    s_drain_axis_queues(counts_au8);

    TEST_ASSERT_EQUAL_UINT32(35u, s_sum_abs_pulses(GTRY_PHYS_AXE_X, counts_au8[GTRY_PHYS_AXE_X]));
    TEST_ASSERT_EQUAL_UINT32(12u, s_sum_abs_pulses(GTRY_PHYS_AXE_Y, counts_au8[GTRY_PHYS_AXE_Y]));
    TEST_ASSERT_EQUAL_UINT32(8u, s_sum_abs_pulses(GTRY_PHYS_AXE_Z, counts_au8[GTRY_PHYS_AXE_Z]));

    for(t_uint8 idx_u8 = 0u; idx_u8 < burstIters_u8; idx_u8++)
    {
        TEST_ASSERT_TRUE(g_axisCmd_aa[GTRY_PHYS_AXE_X][idx_u8].pulses_s32 > 0);
        TEST_ASSERT_EQUAL_INT32(0, g_axisCmd_aa[GTRY_PHYS_AXE_Y][idx_u8].pulses_s32);
        TEST_ASSERT_EQUAL_INT32(0, g_axisCmd_aa[GTRY_PHYS_AXE_Z][idx_u8].pulses_s32);
    }
}

void test_z_priority_holds_other_axes_until_safe_height_reached(void)
{
    t_float32 target_af32[GTRY_PHYS_AXE_NB] = {1.0f, 0.5f, 3.0f};
    t_float32 curr_af32[GTRY_PHYS_AXE_NB] = {0.0f, 0.0f, 0.0f};
    t_float32 miss_af32[GTRY_PHYS_AXE_NB] = {0.0f, 0.0f, 0.0f};
    t_uint8 counts_au8[GTRY_PHYS_AXE_NB] = {0u, 0u, 0u};
    t_uint32 cumZ_u32 = 0u;
    t_uint32 safePulse_u32 = 20u;

    TEST_ASSERT_EQUAL(RC_OK, GANTRY_SPEC_AlgorithmCompute(GTRY_ALGO_COMPUTE_TYPE_Z_PRIORITY, target_af32, curr_af32, miss_af32, g_queue_as));
    s_drain_axis_queues(counts_au8);

    TEST_ASSERT_EQUAL_UINT32(10u, s_sum_abs_pulses(GTRY_PHYS_AXE_X, counts_au8[GTRY_PHYS_AXE_X]));
    TEST_ASSERT_EQUAL_UINT32(5u, s_sum_abs_pulses(GTRY_PHYS_AXE_Y, counts_au8[GTRY_PHYS_AXE_Y]));
    TEST_ASSERT_EQUAL_UINT32(30u, s_sum_abs_pulses(GTRY_PHYS_AXE_Z, counts_au8[GTRY_PHYS_AXE_Z]));

    for(t_uint8 idx_u8 = 0u; idx_u8 < counts_au8[GTRY_PHYS_AXE_Z]; idx_u8++)
    {
        if(cumZ_u32 < safePulse_u32)
        {
            TEST_ASSERT_EQUAL_INT32(0, g_axisCmd_aa[GTRY_PHYS_AXE_X][idx_u8].pulses_s32);
            TEST_ASSERT_EQUAL_INT32(0, g_axisCmd_aa[GTRY_PHYS_AXE_Y][idx_u8].pulses_s32);
        }

        cumZ_u32 += (t_uint32)g_axisCmd_aa[GTRY_PHYS_AXE_Z][idx_u8].pulses_s32;
    }

    TEST_ASSERT_TRUE(cumZ_u32 >= safePulse_u32);
}

void test_frequency_is_clamped_to_axis_min_and_max(void)
{
    t_sGTRYSPEC_AlgoParameter prm_s;
    t_float32 target_af32[GTRY_PHYS_AXE_NB] = {5.0f, 5.0f, 0.5f};
    t_float32 curr_af32[GTRY_PHYS_AXE_NB] = {0.0f, 0.0f, 0.0f};
    t_float32 miss_af32[GTRY_PHYS_AXE_NB] = {0.0f, 0.0f, 0.0f};
    t_uint8 counts_au8[GTRY_PHYS_AXE_NB] = {0u, 0u, 0u};
    t_bool yMaxClampHit_b = FALSE;
    t_bool zMinClampHit_b = FALSE;

    (void)memset(&prm_s, 0, sizeof(prm_s));
    prm_s.chunkSize_u16 = 10u;
    prm_s.MinFreq_af32[GTRY_PHYS_AXE_X] = 100.0f;
    prm_s.MaxFreq_af32[GTRY_PHYS_AXE_X] = 1000.0f;
    prm_s.MinFreq_af32[GTRY_PHYS_AXE_Y] = 50.0f;
    prm_s.MaxFreq_af32[GTRY_PHYS_AXE_Y] = 200.0f;
    prm_s.MinFreq_af32[GTRY_PHYS_AXE_Z] = 300.0f;
    prm_s.MaxFreq_af32[GTRY_PHYS_AXE_Z] = 700.0f;
    prm_s.pulsePerMm_af32[GTRY_PHYS_AXE_X] = 10.0f;
    prm_s.pulsePerMm_af32[GTRY_PHYS_AXE_Y] = 10.0f;
    prm_s.pulsePerMm_af32[GTRY_PHYS_AXE_Z] = 10.0f;
    prm_s.cptPrio_SafeHeight_af32[GTRY_PHYS_AXE_X] = 1.0f;
    prm_s.cptPrio_SafeHeight_af32[GTRY_PHYS_AXE_Y] = 1.0f;
    prm_s.cptPrio_SafeHeight_af32[GTRY_PHYS_AXE_Z] = 1.0f;
    TEST_ASSERT_EQUAL(RC_OK, GANTRY_SPEC_AlgorithmSetParam(prm_s));

    TEST_ASSERT_EQUAL(RC_OK, GANTRY_SPEC_AlgorithmCompute(GTRY_ALGO_COMPUTE_TYPE_BALANCED, target_af32, curr_af32, miss_af32, g_queue_as));
    s_drain_axis_queues(counts_au8);

    for(t_uint8 idx_u8 = 0u; idx_u8 < counts_au8[GTRY_PHYS_AXE_Y]; idx_u8++)
    {
        if((g_axisCmd_aa[GTRY_PHYS_AXE_Y][idx_u8].pulses_s32 > 0)
        && (fabsf(g_axisCmd_aa[GTRY_PHYS_AXE_Y][idx_u8].frequency_f32 - 200.0f) < 0.01f))
        {
            yMaxClampHit_b = TRUE;
            break;
        }
    }

    for(t_uint8 idx_u8 = 0u; idx_u8 < counts_au8[GTRY_PHYS_AXE_Z]; idx_u8++)
    {
        if((g_axisCmd_aa[GTRY_PHYS_AXE_Z][idx_u8].pulses_s32 > 0)
        && (fabsf(g_axisCmd_aa[GTRY_PHYS_AXE_Z][idx_u8].frequency_f32 - 300.0f) < 0.01f))
        {
            zMinClampHit_b = TRUE;
            break;
        }
    }

    TEST_ASSERT_TRUE(yMaxClampHit_b == TRUE);
    TEST_ASSERT_TRUE(zMinClampHit_b == TRUE);
}

void test_returns_warning_when_queue_capacity_is_too_small(void)
{
    t_float32 target_af32[GTRY_PHYS_AXE_NB] = {4.0f, 2.0f, 1.0f};
    t_float32 curr_af32[GTRY_PHYS_AXE_NB] = {0.0f, 0.0f, 0.0f};
    t_float32 miss_af32[GTRY_PHYS_AXE_NB] = {0.0f, 0.0f, 0.0f};

    s_init_axis_queues(2u);
    TEST_ASSERT_EQUAL(RC_WARNING_LIMIT_REACHED, GANTRY_SPEC_AlgorithmCompute(GTRY_ALGO_COMPUTE_TYPE_BALANCED, target_af32, curr_af32, miss_af32, g_queue_as));
    TEST_ASSERT_EQUAL_UINT8(0u, g_queue_as[GTRY_PHYS_AXE_X].actualSize_u16);
    TEST_ASSERT_EQUAL_UINT8(0u, g_queue_as[GTRY_PHYS_AXE_Y].actualSize_u16);
    TEST_ASSERT_EQUAL_UINT8(0u, g_queue_as[GTRY_PHYS_AXE_Z].actualSize_u16);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_balanced_conserves_pulses_and_is_time_synchronized);
    RUN_TEST(test_x_burstfirst_moves_x_before_other_axes);
    RUN_TEST(test_z_priority_holds_other_axes_until_safe_height_reached);
    RUN_TEST(test_frequency_is_clamped_to_axis_min_and_max);
    RUN_TEST(test_returns_warning_when_queue_capacity_is_too_small);
    return UNITY_END();
}
