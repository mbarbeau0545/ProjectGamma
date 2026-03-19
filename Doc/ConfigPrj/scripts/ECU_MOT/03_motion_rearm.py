from app.script_runtime_api import log, send_symbol_msg

REARM_SYMBOL = "LGC_REARMAMENT_CMD"
SIG_REARM_AGENT = "LGC_CMD_REARMAMENT_AGID"
SIG_REARM_TYPE = "LGC_CMD_REARMAMENT_TYPE"
SIG_REARM_STATE = "LGC_CMD_REARMAMENT_STATE"

APPLGC_AGENT_MOTION = 2
REARM_SAFETY = 0
REARM_PREOPE = 1
REARM_TOTAL = 2


def send_rearm_command(rearm_type: int, node: int) -> None:
    send_symbol_msg(
        REARM_SYMBOL,
        {
            SIG_REARM_AGENT: APPLGC_AGENT_MOTION,
            SIG_REARM_TYPE: rearm_type,
            SIG_REARM_STATE: 0,
        },
        node=node,
    )
    log(f"[MOTION] rearm cmd sent node={node}: type={rearm_type}")


if __name__ == "__main__":
    # Sequence directe sans argparse.
    send_rearm_command(REARM_PREOPE, node=0)
    # send_rearm_command(REARM_TOTAL, node=0)
    log("[DONE] MOTION rearm script finished.")
