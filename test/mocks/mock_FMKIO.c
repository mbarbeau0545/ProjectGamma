#include "1_FMK/FMK_HAL/FMK_IO/Src/FMK_IO.h"

t_eReturnCode FMKIO_Set_OutDigSigValue(t_eFMKIO_OutDigSig a, t_eFMKIO_DigValue b) {
    return RC_OK;
}

t_eReturnCode FMKIO_Set_OutPwmSigPulses(t_eFMKIO_OutPwmSig a , t_uint16 b , t_uint16 c, t_uint32 d) {
    return RC_OK;
}

t_eReturnCode FMKIO_Get_InFreqSigValue(t_uint8 a, t_float32 *val) {
    *val = 0.0f;
    return RC_OK;
}