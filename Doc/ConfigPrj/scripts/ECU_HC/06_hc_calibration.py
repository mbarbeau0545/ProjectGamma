from app.script_runtime_api import (     get_signal_sample,
    get_symbol_signal_sample,
    log,
    send_symbol_msg,
    sleep_ms,
)

# Symbol / signal names from OpePrjMsgDefinition.sym
HC_CALIB_SYMBOL = "LGC_HC_CMD_CALIBRATION"
HC_CALIB_SIG_ID = "LGC_CMD_CALIB_ID"
HC_CALIB_SIG_REQ = "LGC_CMD_CALIB_REQ_STATE"
HC_CALIB_SIG_PLS = "LGC_CMD_CALIB_PLS"
HC_CALIB_SIG_SPD = "LGC_CMD_CALIB_SPD"
HC_CALIB_SIG_FB = "LGC_CMD_CALIB_CURR_FEEDBACK"

# t_eAPPSNS_SnsInterface values (APPSNS_ConfigPublic.h)
SNS_ECDR_HD_KNF_POS = 12
SNS_ECDR_HD_CNTR_KNF_POS = 14
SNS_ECDR_HD_HOLD_POS = 16

# t_eAPPLGC_CalibStatus values (APPLGC_ConfigPublic.h)
CALIB_REQ_IDLE = 0
CALIB_REQ_MOVE = 1
CALIB_REQ_REGISTER_VALUE = 2

# t_eAPPLGC_CalibFeedbackSts values (APPLGC_ConfigPublic.h)
CALIB_FB_ONGOING = 1
CALIB_FB_REGIST_VAL_SUCCEED = 2

# CL42T motor 1 state (raw enum: 0=OFF, 1=ON)
CL42T_MTR1_STATE_SIG = "CL42T_MTR_1_STATE"


def _get_feedback_sample(timeout_ms: int = 50):
    return get_symbol_signal_sample(HC_CALIB_SYMBOL, HC_CALIB_SIG_FB, timeout_ms=timeout_ms)


def _wait_feedback_in(expected_raw_values, min_timestamp_ms: int, timeout_ms: int = 2000):
    deadline_ms = max(0, int(timeout_ms))
    elapsed = 0
    while elapsed <= deadline_ms:
        sample = _get_feedback_sample(timeout_ms=50)
        if sample is not None:
            ts = int(sample.get("timestamp_ms", 0))
            raw = int(sample.get("raw", -1))
            if (ts >= min_timestamp_ms) and (raw in expected_raw_values):
                return sample
        sleep_ms(20)
        elapsed += 20
    return None


def _wait_motor1_state(expected_raw: int, timeout_ms: int = 3000):
    elapsed = 0
    timeout_ms = max(0, int(timeout_ms))
    while elapsed <= timeout_ms:
        sample = get_signal_sample(CL42T_MTR1_STATE_SIG, timeout_ms=50)
        if sample is not None:
            try:
                raw = int(sample.get("raw", -1))
            except Exception:
                raw = -1
            if raw == int(expected_raw):
                return sample
        sleep_ms(20)
        elapsed += 20
    return None


def _send_calib_cmd(calib_id: int, req_state: int, pulses: float, speed: float, node: int = 1):
    send_symbol_msg(
        HC_CALIB_SYMBOL,
        {
            HC_CALIB_SIG_ID: calib_id,
            HC_CALIB_SIG_REQ: req_state,
            HC_CALIB_SIG_PLS: pulses,
            HC_CALIB_SIG_SPD: speed,
        },
        node=node,
    )


def hc_calibration_register_success(node: int = 1):
    """Calib nominale: MOVE puis REGISTER_VALUE, et verifie feedback SUCCEED."""
    before = _get_feedback_sample(timeout_ms=50)
    min_ts = int(before.get("timestamp_ms", 0)) + 1 if before else 0

    # Start calibration move on HC knife encoder
    _send_calib_cmd(
        calib_id=SNS_ECDR_HD_KNF_POS,
        req_state=CALIB_REQ_MOVE,
        pulses=300.0,
        speed=1000,
        node=node,
    )
    _send_calib_cmd(
        calib_id=SNS_ECDR_HD_KNF_POS,
        req_state=CALIB_REQ_MOVE,
        pulses=200,
        speed=1000,
        node=node,
    )
    _send_calib_cmd(
        calib_id=SNS_ECDR_HD_KNF_POS,
        req_state=CALIB_REQ_MOVE,
        pulses=200,
        speed=1000,
        node=node,
    )
    sleep_ms(1000)
    _send_calib_cmd(
        calib_id=SNS_ECDR_HD_KNF_POS,
        req_state=CALIB_REQ_MOVE,
        pulses=-300,
        speed=1000,
        node=node,
    )

    sleep_ms(5000)
    _send_calib_cmd(
        calib_id=SNS_ECDR_HD_KNF_POS,
        req_state=CALIB_REQ_REGISTER_VALUE,
        pulses=0,
        speed=0,
        node=node,
    )

    sample = _wait_feedback_in({CALIB_FB_REGIST_VAL_SUCCEED}, min_timestamp_ms=min_ts, timeout_ms=2500)
    if sample is None:
        raise AssertionError("Calibration success test failed: expected feedback REGIST_VAL_SUCCEED (2).")
    log(f"[OK] hc_calibration_register_success: fb={sample}")
    return sample


def hc_calibration_fail_invalid_req_state(node: int = 1):
    """Echec attendu: req_state invalide, pas de feedback de progression calibration."""
    before = _get_feedback_sample(timeout_ms=50)
    min_ts = int(before.get("timestamp_ms", 0)) + 1 if before else 0

    _send_calib_cmd(
        calib_id=SNS_ECDR_HD_KNF_POS,
        req_state=99,  # invalid (> APPLGC_CALIB_STS_NB)
        pulses=150.0,
        speed=20.0,
        node=node,
    )

    sample = _wait_feedback_in(
        {CALIB_FB_ONGOING, CALIB_FB_REGIST_VAL_SUCCEED},
        min_timestamp_ms=min_ts,
        timeout_ms=1200,
    )
    if sample is not None:
        raise AssertionError(f"Expected failure (invalid req state), but got calibration feedback: {sample}")
    log("[OK] hc_calibration_fail_invalid_req_state: expected failure observed (no valid calibration feedback).")
    return True


def hc_calibration_fail_invalid_sensor_id(node: int = 1):
    """Echec attendu: sensor id invalide, pas de feedback de progression calibration."""
    before = _get_feedback_sample(timeout_ms=50)
    min_ts = int(before.get("timestamp_ms", 0)) + 1 if before else 0

    _send_calib_cmd(
        calib_id=255,  # invalid sensor interface for HeadCutter calibration
        req_state=CALIB_REQ_MOVE,
        pulses=150.0,
        speed=20.0,
        node=node,
    )

    sample = _wait_feedback_in(
        {CALIB_FB_ONGOING, CALIB_FB_REGIST_VAL_SUCCEED},
        min_timestamp_ms=min_ts,
        timeout_ms=1200,
    )
    if sample is not None:
        raise AssertionError(f"Expected failure (invalid sensor id), but got calibration feedback: {sample}")
    log("[OK] hc_calibration_fail_invalid_sensor_id: expected failure observed (no valid calibration feedback).")
    return True


if __name__ == "__main__":
    # Run nominal then 2 expected failures.
    hc_calibration_register_success(node=0)
    #hc_calibration_fail_invalid_req_state(node=0)
    #hc_calibration_fail_invalid_sensor_id(node=0)
    log("[DONE] HC calibration script finished.")
