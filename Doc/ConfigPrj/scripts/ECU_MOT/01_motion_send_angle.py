from app.script_runtime_api import log, send_symbol_msg, sleep_ms

MOT_ANGLE_SYMBOL = "LGC_MOT_CMD_WHL_AV_POSITION"
SIG_DIR_L = "LGC_MOT_CMD_WHL_AVL_DIR"
SIG_DIR_R = "LGC_MOT_CMD_WHL_AVR_DIR"
SIG_SPD_L = "LGC_MOT_CMD_WHL_AVL_DIR_SPD"
SIG_SPD_R = "LGC_MOT_CMD_WHL_AVR_DIR_SPD"


def send_angle_command(angle_left_mrad: float,
                       angle_right_mrad: float,
                       speed_left_rpm: float,
                       speed_right_rpm: float,
                       node : int = 0) -> None:
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

    send_angle_command(
        angle_left_mrad=1000, 
        angle_right_mrad=1000,
        speed_left_rpm= 20,
        speed_right_rpm= 20
    )
    sleep_ms(1000)

    send_angle_command(
        angle_left_mrad=-1000, 
        angle_right_mrad=-1000,
        speed_left_rpm= 20,
        speed_right_rpm= 20
    )

    sleep_ms(50)

    send_angle_command(
        angle_left_mrad=-1100, 
        angle_right_mrad=-1100,
        speed_left_rpm= 20,
        speed_right_rpm= 20
    )

    sleep_ms(50)
    
    send_angle_command(
        angle_left_mrad=-1200, 
        angle_right_mrad=-1200,
        speed_left_rpm= 20,
        speed_right_rpm= 20
    )
