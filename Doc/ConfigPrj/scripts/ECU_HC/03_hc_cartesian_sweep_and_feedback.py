from app.script_runtime_api import *

# Cartesian example: pos_type = 0
symbol = "LGC_HC_CMD_POSITION"
node = 1
pos_id = 100

x0 = 1074
y0 = 1000
amp = 40

for i in range(100):
    if stop_requested():
        break

    x = x0 + (i % amp)
    y = y0 - (i % amp)

    send_symbol_msg(symbol, {
        "LGC_HC_CMD_KNIFE_POS_X_ALPH_B": x,
        "LGC_HC_CMD_KNIFE_POS_Y_ALPH_C": y,
        "LGC_HC_CMD_KNF_POS_SPD_RPM": 25,
        "LGC_HC_CMD_CNTR_KNF_POS_SPD_RPM": 25,
        "LGC_HC_CMD_KNIFE_TYPE_ID": 0,
        "LGC_HC_CMD_KNIFE_POS_ID": pos_id,
    }, node=node)

    sample = get_symbol_signal_sample("LGC_HC_FEEDBACK_POS", "LGC_HC_FB_AXE_X_POS", timeout_ms=30)
    if sample is not None:
        log(f"id={pos_id} fb_x={sample['value']} raw={sample['raw']}")

    pos_id = (pos_id + 1) & 0xFFFF
    sleep_ms(15)

log("cartesian sweep done")
