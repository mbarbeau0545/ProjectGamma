from app.script_runtime_api import get_symbol_signal_sample, log, send_symbol_msg, sleep_ms

# Symbol / signal names from OpePrjMsgDefinition.sym
MOT_CALIB_SYMBOL = "LGC_MOT_CMD_CALIBRATION"
SIG_CALIB_ID = "LGC_CMD_CALIB_ID"
SIG_CALIB_REQ = "LGC_CMD_CALIB_REQ_STATE"
SIG_CALIB_PLS = "LGC_CMD_CALIB_PLS"
SIG_CALIB_SPD = "LGC_CMD_CALIB_SPD"
SIG_CALIB_FB = "LGC_CMD_CALIB_CURR_FEEDBACK"

# APPSNS t_eAPPSNS_SnsInterface
SNS_ECDR_WHL_AV_L_POS = 8
SNS_ECDR_WHL_AV_R_POS = 10

# APPLGC t_eAPPLGC_CalibStatus
CALIB_REQ_IDLE = 0
CALIB_REQ_MOVE = 1
CALIB_REQ_REGISTER_VALUE = 2

# APPLGC t_eAPPLGC_CalibFeedbackSts
CALIB_FB_ONGOING = 1
CALIB_FB_REGIST_VAL_SUCCEED = 2


def _get_feedback_sample(timeout_ms: int = 50):
    return get_symbol_signal_sample(MOT_CALIB_SYMBOL, SIG_CALIB_FB, timeout_ms=timeout_ms)


def _wait_feedback_in(expected_raw_values, min_timestamp_ms: int, timeout_ms: int = 2500):
    elapsed = 0
    timeout_ms = max(0, int(timeout_ms))
    while elapsed <= timeout_ms:
        sample = _get_feedback_sample(timeout_ms=50)
        if sample is not None:
            ts = int(sample.get("timestamp_ms", 0))
            raw = int(sample.get("raw", -1))
            if (ts >= min_timestamp_ms) and (raw in expected_raw_values):
                return sample
        sleep_ms(20)
        elapsed += 20
    return None


def _send_calib_cmd(calib_id: int, req_state: int, pulses: float, speed: float, node: int = 0):
    send_symbol_msg(
        MOT_CALIB_SYMBOL,
        {
            SIG_CALIB_ID: int(calib_id),
            SIG_CALIB_REQ: int(req_state),
            SIG_CALIB_PLS: float(pulses),
            SIG_CALIB_SPD: float(speed),
        },
        node=node,
    )


def mot_calibration_register_success(sensor_id: int = SNS_ECDR_WHL_AV_L_POS,
                                     node: int = 0,
                                     pulses: float = 400.0,
                                     speed: float = 800.0,
                                     settle_ms: int = 1500):
    before = _get_feedback_sample(timeout_ms=50)
    min_ts = int(before.get("timestamp_ms", 0)) + 1 if before else 0

    _send_calib_cmd(sensor_id, CALIB_REQ_MOVE, pulses, speed, node=node)
    sleep_ms(max(0, int(settle_ms)))
    _send_calib_cmd(sensor_id, CALIB_REQ_REGISTER_VALUE, 0.0, 0.0, node=node)

    sample = _wait_feedback_in({CALIB_FB_REGIST_VAL_SUCCEED}, min_timestamp_ms=min_ts, timeout_ms=3000)
    if sample is None:
        raise AssertionError(
            "Calibration success test failed: expected feedback REGIST_VAL_SUCCEED (2)."
        )
    log(f"[OK] mot_calibration_register_success sensor={sensor_id}: fb={sample}")
    return sample


def mot_calibration_fail_invalid_req_state(sensor_id: int = SNS_ECDR_WHL_AV_L_POS, node: int = 0):
    before = _get_feedback_sample(timeout_ms=50)
    min_ts = int(before.get("timestamp_ms", 0)) + 1 if before else 0

    _send_calib_cmd(sensor_id, 99, 100.0, 500.0, node=node)
    sample = _wait_feedback_in({CALIB_FB_ONGOING, CALIB_FB_REGIST_VAL_SUCCEED},
                               min_timestamp_ms=min_ts,
                               timeout_ms=1200)
    if sample is not None:
        raise AssertionError(f"Expected failure (invalid req state), but got calibration feedback: {sample}")
    log("[OK] mot_calibration_fail_invalid_req_state")
    return True


def mot_calibration_fail_invalid_sensor_id(node: int = 0):
    before = _get_feedback_sample(timeout_ms=50)
    min_ts = int(before.get("timestamp_ms", 0)) + 1 if before else 0

    _send_calib_cmd(255, CALIB_REQ_MOVE, 100.0, 500.0, node=node)
    sample = _wait_feedback_in({CALIB_FB_ONGOING, CALIB_FB_REGIST_VAL_SUCCEED},
                               min_timestamp_ms=min_ts,
                               timeout_ms=1200)
    if sample is not None:
        raise AssertionError(f"Expected failure (invalid sensor id), but got calibration feedback: {sample}")
    log("[OK] mot_calibration_fail_invalid_sensor_id")
    return True


if __name__ == "__main__":
    mot_calibration_register_success(sensor_id=SNS_ECDR_WHL_AV_L_POS, node=0)
    # mot_calibration_register_success(sensor_id=SNS_ECDR_WHL_AV_R_POS, node=0)
    # mot_calibration_fail_invalid_req_state(sensor_id=SNS_ECDR_WHL_AV_L_POS, node=0)
    # mot_calibration_fail_invalid_sensor_id(node=0)
    log("[DONE] MOT calibration script finished.")
