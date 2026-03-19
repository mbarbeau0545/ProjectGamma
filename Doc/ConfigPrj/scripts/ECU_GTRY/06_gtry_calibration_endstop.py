from app.script_runtime_api import (
    get_symbol_signal_sample,
    log,
    send_symbol_msg,
    sleep_ms,
    trigger_in_evnt,
)

# -----------------------------
# Symbols / signals
# -----------------------------
GTRY_CALIB_SYMBOL = "LGC_GTRY_CMD_CALIBRATION"
GTRY_CALIB_SIG_ID = "LGC_CMD_CALIB_ID"
GTRY_CALIB_SIG_REQ = "LGC_CMD_CALIB_REQ_STATE"
GTRY_CALIB_SIG_FB = "LGC_CMD_CALIB_CURR_FEEDBACK"

GTRY_DBG_FSM_SYMBOL = "LGC_GTRY_DEBUG_FSM"
GTRY_DBG_FSM_CALIB = "LGC_GTRY_FSM_CALIB"
GTRY_DBG_FSM_CLB_X = "LGC_GTRY_FSM_CLB_AXE_X"
GTRY_DBG_FSM_CLB_Y = "LGC_GTRY_FSM_CLB_AXE_Y"
GTRY_DBG_FSM_CLB_Z = "LGC_GTRY_FSM_CLB_AXE_Z"

# -----------------------------
# Raw enum values (from C / SYM)
# -----------------------------
CALIB_REQ_IDLE = 0
CALIB_REQ_MOVE = 1
CALIB_REQ_REGISTER_VALUE = 2

CALIB_FB_ONGOING = 1
CALIB_FB_REGIST_VAL_SUCCEED = 2
CALIB_FB_REGIST_VAL_FAILED = 3
CALIB_FB_WRONG_STATE = 4
CALIB_FB_SET_VAL_FAILED = 5
CALIB_FB_UNDEFINED_ERROR = 6
CALIB_FB_MTR_DISABLE = 7

GTRY_FSM_CALIB_INIT = 0
GTRY_FSM_CALIB_AXE_X = 1
GTRY_FSM_CALIB_AXE_Y = 2
GTRY_FSM_CALIB_AXE_Z = 3

GTRY_FSM_CALIB_OPE_STOP = 0
GTRY_FSM_CALIB_OPE_MOVE = 1
GTRY_FSM_CALIB_OPE_WAIT = 2

# APPSNS sensor interface IDs used by GANTRY for calibration command
SNS_ECDR_XL_POS = 0
SNS_ECDR_XR_POS = 2
SNS_ECDR_Y_POS = 4
SNS_ECDR_Z_POS = 6

AXIS_TO_SNS_ID = {
    "X": SNS_ECDR_XL_POS,  # XL or XR both map to axis X in GANTRY.c
    "Y": SNS_ECDR_Y_POS,
    "Z": SNS_ECDR_Z_POS,
}

AXIS_TO_TOP_FSM = {
    "X": GTRY_FSM_CALIB_AXE_X,
    "Y": GTRY_FSM_CALIB_AXE_Y,
    "Z": GTRY_FSM_CALIB_AXE_Z,
}

AXIS_TO_SUB_FSM_SIGNAL = {
    "X": GTRY_DBG_FSM_CLB_X,
    "Y": GTRY_DBG_FSM_CLB_Y,
    "Z": GTRY_DBG_FSM_CLB_Z,
}

# In current firmware config:
# - Y uses FMKIO_INPUT_SIGEVNT_5/6 (CW/CCW) => 0-based idx 4/5
# - Z uses FMKIO_INPUT_SIGEVNT_7/8 (CW/CCW) => 0-based idx 6/7
# - X has no endstop event lines configured in current APPACT_SPEC_MTR_XL/XR
ENDSTOP_EVNT_IDX = {
    ("XL", "CW") : 3,
    ("XL", "CCW") : 2,
    ("XR", "CW") : 0,
    ("XR", "CCW") : 1,
    ("Y", "CW"): 4,
    ("Y", "CCW"): 5,
    ("Z", "CW"): 6,
    ("Z", "CCW"): 7,
}


def _now_fb_sample(timeout_ms=50):
    return get_symbol_signal_sample(GTRY_CALIB_SYMBOL, GTRY_CALIB_SIG_FB, timeout_ms=timeout_ms)


def _get_raw(symbol, signal, timeout_ms=100):
    sample = get_symbol_signal_sample(symbol, signal, timeout_ms=timeout_ms)
    if sample is None:
        return None, None
    return int(sample.get("raw", -1)), int(sample.get("timestamp_ms", 0))


def _wait_symbol_raw(symbol, signal, expected_values, timeout_ms=3000, min_ts_ms=0):
    elapsed = 0
    while elapsed <= timeout_ms:
        raw, ts = _get_raw(symbol, signal, timeout_ms=80)
        if raw is not None and ts is not None and ts >= min_ts_ms and raw in expected_values:
            return {"raw": raw, "timestamp_ms": ts}
        sleep_ms(50)
        elapsed += 20
    return None


def _send_calib_req(sensor_id, req_state, node=0):
    send_symbol_msg(
        GTRY_CALIB_SYMBOL,
        {
            GTRY_CALIB_SIG_ID: int(sensor_id),
            GTRY_CALIB_SIG_REQ: int(req_state),
        },
        node=node,
    )


def _trigger_endstop_callback(axis, direction="CW"):
    axis = str(axis).upper()
    direction = str(direction).upper()
    key = (axis, direction)
    if axis == "X":
        key = ("XL", direction)
        idx_xl = ENDSTOP_EVNT_IDX[key]
        if(direction == "CW"): direction = "CCW"
        else: direction ="CW"

        key = ("XR", direction)
        idx_xr = ENDSTOP_EVNT_IDX[key]

        trigger_in_evnt(idx_xl)
        trigger_in_evnt(idx_xr)
        log(f"[GTRY][SIM] Endstop trigger axis={axis} dir={direction} on in_evnt[{idx_xl}]")
        log(f"[GTRY][SIM] Endstop trigger axis={axis} dir={direction} on in_evnt[{idx_xr}]")
    else:
        if key not in ENDSTOP_EVNT_IDX:
            raise AssertionError(
                f"No endstop event mapping for axis={axis}, direction={direction}. "
                f"Configured mappings: {list(ENDSTOP_EVNT_IDX.keys())}."
            )

        idx = ENDSTOP_EVNT_IDX[key]
        trigger_in_evnt(idx)
        log(f"[GTRY][SIM] Endstop trigger axis={axis} dir={direction} on in_evnt[{idx}]")


def gtry_calibration_axis_success(axis, direction="CW", node=0, wait_timeout_ms=12000):
    """
    Nominal flow:
    1) send MOVE calibration request for one axis
    2) wait until top FSM = AXE_<axis> and sub FSM = WAIT
    3) trigger endstop callback (best effort)
    4) wait feedback success
    """
    axis = str(axis).upper()
    if axis not in AXIS_TO_SNS_ID:
        raise AssertionError(f"Unknown axis '{axis}', expected one of {list(AXIS_TO_SNS_ID.keys())}")

    before = _now_fb_sample(timeout_ms=100)
    min_ts = int(before.get("timestamp_ms", 0)) + 1 if before else 0

    _send_calib_req(AXIS_TO_SNS_ID[axis], CALIB_REQ_MOVE, node=node)
    log(f"[GTRY][CALIB] MOVE sent for axis={axis}")

    # Wait top calibration FSM on requested axis
    top_expected = AXIS_TO_TOP_FSM[axis]
    top_hit = _wait_symbol_raw(
        GTRY_DBG_FSM_SYMBOL,
        GTRY_DBG_FSM_CALIB,
        {top_expected},
        timeout_ms=wait_timeout_ms,
        min_ts_ms=min_ts,
    )
    if top_hit is None:
        raise AssertionError(
            f"Calibration did not enter top FSM axis state for {axis}. "
            "Possible causes: command not accepted."
        )

    # Wait sub-FSM WAIT state for this axis
    sub_sig = AXIS_TO_SUB_FSM_SIGNAL[axis]
    wait_hit = _wait_symbol_raw(
        GTRY_DBG_FSM_SYMBOL,
        sub_sig,
        {GTRY_FSM_CALIB_OPE_WAIT},
        timeout_ms=wait_timeout_ms,
        min_ts_ms=top_hit["timestamp_ms"],
    )
    if wait_hit is None:
        raise AssertionError(f"Axis {axis} never reached CALIB_OPE_WAIT.")

    sleep_ms(1000)
    _trigger_endstop_callback(axis, direction=direction)

    # Wait success feedback from calibration command message
    ok = _wait_symbol_raw(
        GTRY_CALIB_SYMBOL,
        GTRY_CALIB_SIG_FB,
        {CALIB_FB_REGIST_VAL_SUCCEED},
        timeout_ms=wait_timeout_ms,
        min_ts_ms=wait_hit["timestamp_ms"],
    )
    if ok is None:
        raise AssertionError(
            f"Calibration success not received for axis={axis}. "
            "Check endstop direction mapping and that callback is configured."
        )

    log(f"[OK] gtry_calibration_axis_success axis={axis} dir={direction} fb={ok}")
    return ok


def gtry_calibration_fail_invalid_req_state(axis="Y", node=0, timeout_ms=1500):
    axis = str(axis).upper()
    sensor_id = AXIS_TO_SNS_ID.get(axis, SNS_ECDR_Y_POS)

    before = _now_fb_sample(timeout_ms=80)
    min_ts = int(before.get("timestamp_ms", 0)) + 1 if before else 0

    _send_calib_req(sensor_id, 99, node=node)

    got = _wait_symbol_raw(
        GTRY_CALIB_SYMBOL,
        GTRY_CALIB_SIG_FB,
        {CALIB_FB_ONGOING, CALIB_FB_REGIST_VAL_SUCCEED},
        timeout_ms=timeout_ms,
        min_ts_ms=min_ts,
    )
    if got is not None:
        raise AssertionError(f"Expected failure on invalid req_state, but got feedback={got}")

    log("[OK] gtry_calibration_fail_invalid_req_state")
    return True


def gtry_calibration_fail_invalid_sensor_id(node=0, timeout_ms=1500):
    before = _now_fb_sample(timeout_ms=80)
    min_ts = int(before.get("timestamp_ms", 0)) + 1 if before else 0

    _send_calib_req(255, CALIB_REQ_MOVE, node=node)

    got = _wait_symbol_raw(
        GTRY_CALIB_SYMBOL,
        GTRY_CALIB_SIG_FB,
        {CALIB_FB_ONGOING, CALIB_FB_REGIST_VAL_SUCCEED},
        timeout_ms=timeout_ms,
        min_ts_ms=min_ts,
    )
    if got is not None:
        raise AssertionError(f"Expected failure on invalid sensor_id, but got feedback={got}")

    log("[OK] gtry_calibration_fail_invalid_sensor_id")
    return True


def gtry_calibration_fail_timeout_no_endstop(axis="Y", node=0, timeout_ms=10000):
    """
    Starts calibration but does NOT trigger endstop callback.
    Expected: no success feedback in given timeout window.
    """
    axis = str(axis).upper()
    if axis not in AXIS_TO_SNS_ID:
        raise AssertionError(f"Unknown axis '{axis}', expected one of {list(AXIS_TO_SNS_ID.keys())}")

    before = _now_fb_sample(timeout_ms=80)
    min_ts = int(before.get("timestamp_ms", 0)) + 1 if before else 0

    _send_calib_req(AXIS_TO_SNS_ID[axis], CALIB_REQ_MOVE, node=node)

    got = _wait_symbol_raw(
        GTRY_CALIB_SYMBOL,
        GTRY_CALIB_SIG_FB,
        {CALIB_FB_REGIST_VAL_SUCCEED},
        timeout_ms=timeout_ms,
        min_ts_ms=min_ts,
    )
    if got is not None:
        raise AssertionError(f"Expected timeout/failure without endstop, but got success feedback={got}")

    log("[OK] gtry_calibration_fail_timeout_no_endstop")
    return True


if __name__ == "__main__":
    # Example run sequence (adapt node if needed):
    # - nominal tests on Y and Z with endstop trigger simulation
    # - failure tests
    gtry_calibration_axis_success("X", direction="CW", node=0)
    gtry_calibration_axis_success("Y", direction="CW", node=0)
    gtry_calibration_axis_success("Z", direction="CW", node=0)

    # gtry_calibration_fail_invalid_req_state(axis="Y", node=0)
    # gtry_calibration_fail_invalid_sensor_id(node=0)
    # gtry_calibration_fail_timeout_no_endstop(axis="Y", node=0)

    log("[DONE] GTRY calibration tests finished.")
