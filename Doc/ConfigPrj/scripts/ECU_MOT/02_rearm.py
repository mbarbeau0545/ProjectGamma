from app.script_runtime_api import get_symbol_signal_sample, log, send_symbol_msg, sleep_ms

# Symbol / signal names from OpePrjMsgDefinition.sym
REARM_SYMBOL = "LGC_REARMAMENT_CMD"
SIG_REARM_AGENT = "LGC_CMD_REARMAMENT_AGID"
SIG_REARM_TYPE = "LGC_CMD_REARMAMENT_TYPE"
SIG_REARM_STATE = "LGC_CMD_REARMAMENT_STATE"

# t_eAPPLGC_RearmAgentID
APPLGC_AGENT_MOTION = 2

# t_eAPPLGC_RearmTypeID
REARM_PRE_OPE = 0
REARM_TOTAL = 1

# t_eAPPLGC_RearmStatusID
REARM_STS_SUCCESS = 255
REARM_STS_FAILED = 1


def _get_rearm_sample(timeout_ms: int = 50):
    return get_symbol_signal_sample(REARM_SYMBOL, SIG_REARM_STATE, timeout_ms=timeout_ms)


def _wait_rearm_status(expected_raw_values, min_timestamp_ms: int, timeout_ms: int = 2000):
    elapsed = 0
    timeout_ms = max(0, int(timeout_ms))
    while elapsed <= timeout_ms:
        sample = _get_rearm_sample(timeout_ms=50)
        if sample is not None:
            ts = int(sample.get("timestamp_ms", 0))
            raw = int(sample.get("raw", -1))
            if (ts >= min_timestamp_ms) and (raw in expected_raw_values):
                return sample
        sleep_ms(20)
        elapsed += 20
    return None


def _send_rearm_cmd(agent_id: int, rearm_type: int, node: int = 0):
    send_symbol_msg(
        REARM_SYMBOL,
        {
            SIG_REARM_AGENT: int(agent_id),
            SIG_REARM_TYPE: int(rearm_type),
            SIG_REARM_STATE: 0,
        },
        node=node,
    )


def mot_rearm_success(rearm_type: int = REARM_PRE_OPE, node: int = 0, timeout_ms: int = 3000):
    before = _get_rearm_sample(timeout_ms=50)
    min_ts = int(before.get("timestamp_ms", 0)) + 1 if before else 0

    _send_rearm_cmd(APPLGC_AGENT_MOTION, rearm_type, node=node)
    sample = _wait_rearm_status({REARM_STS_SUCCESS}, min_timestamp_ms=min_ts, timeout_ms=timeout_ms)
    if sample is None:
        raise AssertionError("Expected rearm SUCCESS status (255), but nothing received in time.")
    log(f"[OK] mot_rearm_success: type={rearm_type}, fb={sample}")
    return sample


def mot_rearm_fail_invalid_agent(node: int = 0, timeout_ms: int = 1500):
    before = _get_rearm_sample(timeout_ms=50)
    min_ts = int(before.get("timestamp_ms", 0)) + 1 if before else 0

    _send_rearm_cmd(agent_id=255, rearm_type=REARM_PRE_OPE, node=node)
    sample = _wait_rearm_status({REARM_STS_SUCCESS}, min_timestamp_ms=min_ts, timeout_ms=timeout_ms)
    if sample is not None:
        raise AssertionError(f"Expected failure for invalid agent id, but got SUCCESS sample={sample}")
    log("[OK] mot_rearm_fail_invalid_agent")
    return True


if __name__ == "__main__":
    mot_rearm_success(rearm_type=REARM_PRE_OPE, node=0)
    # mot_rearm_success(rearm_type=REARM_TOTAL, node=0)
    # mot_rearm_fail_invalid_agent(node=0)
    log("[DONE] MOT rearm script finished.")
