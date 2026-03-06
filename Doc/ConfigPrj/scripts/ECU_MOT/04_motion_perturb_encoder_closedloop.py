from app.script_runtime_api import (
    get_signal_sample,
    log,
    send_symbol_msg,
    set_enc_pos,
    sleep_ms,
)

# MOTION steering command symbol/signals
MOT_ANGLE_SYMBOL = "LGC_MOT_CMD_WHL_AV_POSITION"
SIG_DIR_L = "LGC_MOT_CMD_WHL_AVL_DIR"
SIG_DIR_R = "LGC_MOT_CMD_WHL_AVR_DIR"
SIG_SPD_L = "LGC_MOT_CMD_WHL_AVL_DIR_SPD"
SIG_SPD_R = "LGC_MOT_CMD_WHL_AVR_DIR_SPD"

# Feedback signals
SIG_SNS_WHL_L_POS = "SNS_ECDR_WHL_AV_L_POS"
SIG_SNS_WHL_R_POS = "SNS_ECDR_WHL_AV_R_POS"

# Encoder indices in PCSIM runtime:
# - APPSNS_SPEC_ECDR_WHL_AV_R -> FMKIO_INPUT_ENCODER_1 -> index 0
# - APPSNS_SPEC_ECDR_WHL_AV_L -> FMKIO_INPUT_ENCODER_2 -> index 1
ENC_IDX_WHL_AV_R = 0
ENC_IDX_WHL_AV_L = 1


def send_angle_command(angle_left_mrad: float,
                       angle_right_mrad: float,
                       speed_left_rpm: float,
                       speed_right_rpm: float,
                       node: int = 0) -> None:
    send_symbol_msg(
        MOT_ANGLE_SYMBOL,
        {
            SIG_DIR_L: float(angle_left_mrad),
            SIG_DIR_R: float(angle_right_mrad),
            SIG_SPD_L: float(speed_left_rpm),
            SIG_SPD_R: float(speed_right_rpm),
        },
        node=node,
    )
    log(
        f"[MOT] angle cmd: L={angle_left_mrad}mrad R={angle_right_mrad}mrad "
        f"spdL={speed_left_rpm}rpm spdR={speed_right_rpm}rpm"
    )


def _read_signal_value(signal_name: str, timeout_ms: int = 100) -> float:
    sample = get_signal_sample(signal_name, timeout_ms=timeout_ms)
    if sample is None:
        return 0.0
    val = sample.get("value", None)
    raw = sample.get("raw", 0.0)
    try:
        return float(val)
    except Exception:
        try:
            return float(raw)
        except Exception:
            return 0.0


def perturb_encoder_position(enc_idx: int, feedback_signal: str, delta_mrad: float) -> None:
    curr_pos_mrad = _read_signal_value(feedback_signal, timeout_ms=100)
    forced_pos_mrad = curr_pos_mrad + float(delta_mrad)
    set_enc_pos(enc_idx, forced_pos_mrad, forced_pos_mrad)
    log(
        f"[MOT][PERTURB] ENC[{enc_idx}] {feedback_signal}: "
        f"curr={curr_pos_mrad:.2f}mrad delta={delta_mrad:.2f}mrad "
        f"forced={forced_pos_mrad:.2f}mrad"
    )


if __name__ == "__main__":
    # 1) Start a steering closed-loop command
    send_angle_command(
        angle_left_mrad=1200.0,
        angle_right_mrad=1200.0,
        speed_left_rpm=30.0,
        speed_right_rpm=30.0,
        node=0,
    )
    sleep_ms(400)

    # 2) Inject perturbation on left encoder (positive jump)
    perturb_encoder_position(ENC_IDX_WHL_AV_L, SIG_SNS_WHL_L_POS, +800.0)
    sleep_ms(500)

    # 3) Inject perturbation on left encoder (negative jump)
    perturb_encoder_position(ENC_IDX_WHL_AV_L, SIG_SNS_WHL_L_POS, -1400.0)
    sleep_ms(500)

    # 4) Inject perturbation on right encoder
    perturb_encoder_position(ENC_IDX_WHL_AV_R, SIG_SNS_WHL_R_POS, +1000.0)
    sleep_ms(500)

    # 5) End with a neutral command
    send_angle_command(
        angle_left_mrad=0.0,
        angle_right_mrad=0.0,
        speed_left_rpm=20.0,
        speed_right_rpm=20.0,
        node=0,
    )
    log("[DONE] MOT encoder perturbation scenario finished.")
