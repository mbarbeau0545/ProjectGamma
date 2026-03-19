from app.script_runtime_api import log, send_symbol_msg, sleep_ms

MOT_CALIB_SYMBOL = "LGC_MOT_CMD_CALIBRATION"
SIG_CALIB_ID = "LGC_CMD_CALIB_ID"
SIG_CALIB_REQ = "LGC_CMD_CALIB_REQ_STATE"
SIG_CALIB_PLS = "LGC_CMD_CALIB_PLS"
SIG_CALIB_SPD = "LGC_CMD_CALIB_SPD"

SNS_ECDR_WHL_AV_L_POS = 8
SNS_ECDR_WHL_AV_R_POS = 10

CALIB_REQ_IDLE = 0
CALIB_REQ_MOVE = 1
CALIB_REQ_REGISTER_VALUE = 2


def send_calibration_cmd(sensor_id: int,
                         req_state: int,
                         pulses: float,
                         speed: float,
                         node: int) -> None:
    send_symbol_msg(
        MOT_CALIB_SYMBOL,
        {
            SIG_CALIB_ID: sensor_id,
            SIG_CALIB_REQ: req_state,
            SIG_CALIB_PLS: pulses,
            SIG_CALIB_SPD: speed,
        },
        node=node,
    )
    log(
        f"[MOTION] calib cmd sent node={node}: "
        f"sns={sensor_id}, state={req_state}, pulses={pulses}, speed={speed}"
    )


def run_nominal_calibration(sensor_id: int,
                            move_pulses: float,
                            move_speed: float,
                            settle_ms: int,
                            node: int) -> None:
    send_calibration_cmd(sensor_id, CALIB_REQ_MOVE, move_pulses, move_speed, node)
    sleep_ms(max(0, int(settle_ms)))
    send_calibration_cmd(sensor_id, CALIB_REQ_REGISTER_VALUE, 0.0, 0.0, node)


if __name__ == "__main__":
    # Sequence directe sans argparse.
    run_nominal_calibration(
        sensor_id=SNS_ECDR_WHL_AV_L_POS,
        move_pulses=400.0,
        move_speed=800.0,
        settle_ms=1500,
        node=0,
    )
    sleep_ms(100)
    log("[DONE] MOTION calibration done for WHL_AV_L.")
    run_nominal_calibration(
        sensor_id=SNS_ECDR_WHL_AV_R_POS,
        move_pulses=-400.0,
        move_speed=800.0,
        settle_ms=1500,
        node=0,
    )
    log("[DONE] MOTION calibration done for WHL_AV_R.")
    # run_nominal_calibration(SNS_ECDR_WHL_AV_R_POS, 400.0, 800.0, 1500, 0)
    log("[DONE] MOTION calibration script finished.")
