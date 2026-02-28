#pragma once

#include "FMK_HAL/FMK_SRL/Src/FMK_SRL.h"

void FMKSRL_LogUartSend(t_eFMKSRL_SerialLine f_SrlLine_e, const t_char * fmt, ...);
t_eReturnCode FMKSRL_Transmit(t_eFMKSRL_SerialLine f_SrlLine_e,
                              t_eFMKSRL_TxOpeMode f_OpeMode_e,
                              t_uint8 * f_msgData_pu8,
                              t_uint16 f_dataSize_u16,
                              t_uint16 f_InfoMode_u16,
                              t_bool f_EnableTxCb_b);
