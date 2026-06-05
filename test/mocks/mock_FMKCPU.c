#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"

static t_uint32 g_mockTick_u32 = (t_uint32)0;

void FMKCPU_GetTick(t_uint32 *tick)
{
    g_mockTick_u32 += (t_uint32)10;
    *tick = g_mockTick_u32;
}

void mock_FMKCPU_ResetTick(void)
{
    g_mockTick_u32 = (t_uint32)0;
}

void mock_FMKCPU_SetTick(t_uint32 tick)
{
    g_mockTick_u32 = tick;
}
