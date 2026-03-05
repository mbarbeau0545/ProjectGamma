from argparse import ArgumentParser

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
    parser = ArgumentParser(description="Send calibration commands to ECU_MOTION")
    parser.add_argument(
        "--wheel",
        choices=["left", "right"],
        default="left",
        help="Direction wheel to calibrate",
    )
    parser.add_argument("--pulses", type=float, default=400.0, help="Move pulses before register")
    parser.add_argument("--speed", type=float, default=800.0, help="Calibration speed")
    parser.add_argument("--settle-ms", type=int, default=1500, help="Wait before register value")
    parser.add_argument("--node", type=int, default=2, help="CAN node (default: 2 for ECU_MOTION)")

    args = parser.parse_args()
    sensor = SNS_ECDR_WHL_AV_L_POS if args.wheel == "left" else SNS_ECDR_WHL_AV_R_POS
    run_nominal_calibration(sensor, args.pulses, args.speed, args.settle_ms, args.node)
