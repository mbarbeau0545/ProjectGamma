from argparse import ArgumentParser

from app.script_runtime_api import log, send_symbol_msg

MOT_ANGLE_SYMBOL = "LGC_MOT_CMD_WHL_AV_POSITION"
SIG_DIR_L = "LGC_MOT_CMD_WHL_AVL_DIR"
SIG_DIR_R = "LGC_MOT_CMD_WHL_AVR_DIR"
SIG_SPD_L = "LGC_MOT_CMD_WHL_AVL_DIR_SPD"
SIG_SPD_R = "LGC_MOT_CMD_WHL_AVR_DIR_SPD"


def send_angle_command(angle_left_mrad: float,
                       angle_right_mrad: float,
                       speed_left_rpm: float,
                       speed_right_rpm: float,
                       node: int) -> None:
    send_symbol_msg(
        MOT_ANGLE_SYMBOL,
        {
            SIG_DIR_L: angle_left_mrad,
            SIG_DIR_R: angle_right_mrad,
            SIG_SPD_L: speed_left_rpm,
            SIG_SPD_R: speed_right_rpm,
        },
        node=node,
    )
    log(
        f"[MOTION] angle cmd sent node={node}: "
        f"L={angle_left_mrad} mrad, R={angle_right_mrad} mrad, "
        f"spdL={speed_left_rpm} rpm, spdR={speed_right_rpm} rpm"
    )


if __name__ == "__main__":
    parser = ArgumentParser(description="Send wheel front direction angle command to ECU_MOTION")
    parser.add_argument("--left", type=float, required=True, help="Left wheel target angle (mrad)")
    parser.add_argument("--right", type=float, required=True, help="Right wheel target angle (mrad)")
    parser.add_argument("--speed-left", type=float, default=800.0, help="Left wheel speed (rpm)")
    parser.add_argument("--speed-right", type=float, default=800.0, help="Right wheel speed (rpm)")
    parser.add_argument("--node", type=int, default=2, help="CAN node (default: 2 for ECU_MOTION)")

    args = parser.parse_args()
    send_angle_command(args.left, args.right, args.speed_left, args.speed_right, args.node)
