#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"



void FMKCPU_GetTick(t_uint32 *tick) {
    static t_uint32 fake = 0;
    *tick = fake += 10; // incrémente le temps
    return;
}