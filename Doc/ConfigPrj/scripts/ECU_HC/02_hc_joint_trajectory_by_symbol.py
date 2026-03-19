from app.script_runtime_api import *

# Send HC position command by symbol/signal names (no hardcoded CAN ID/bit positions)
symbol = "LGC_HC_CMD_POSITION"
node = 1
pos_id = 1

for i in range(120):
    if stop_requested():
        break

    alpha_b = 900 + i
    alpha_c = 1000 + (i // 2)

    send_symbol_msg(symbol, {
        "LGC_HC_CMD_KNIFE_POS_X_ALPH_A": alpha_b,
        "LGC_HC_CMD_KNIFE_POS_Y_ALPH_B": alpha_c,
        "LGC_HC_CMD_KNF_POS_SPD_RPM": 20,
        "LGC_HC_CMD_CNTR_KNF_POS_SPD_RPM": 20,
        "LGC_HC_CMD_KNIFE_TYPE_ID": 1,
        "LGC_HC_CMD_KNIFE_POS_ID": pos_id,
    }, node=node)

    # optional feedback read (decoded from ECU TX frames via .sym)
    fb_b = get_signal("LGC_HC_FB_ALPHA_B_ANGLE", timeout_ms=20)
    fb_c = get_signal("LGC_HC_FB_ALPHA_C_ANGLE", timeout_ms=20)
    log(f"cmd_id={pos_id} cmd=({alpha_b},{alpha_c}) fb=({fb_b},{fb_c})")

    pos_id = (pos_id + 1) & 0xFFFF
    sleep_ms(10)

log("trajectory by symbol done")
