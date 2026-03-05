from argparse import ArgumentParser

from app.script_runtime_api import log, send_symbol_msg

REARM_SYMBOL = "LGC_REARMAMENT_CMD"
SIG_REARM_AGENT = "LGC_CMD_REARMAMENT_AGID"
SIG_REARM_TYPE = "LGC_CMD_REARMAMENT_TYPE"
SIG_REARM_STATE = "LGC_CMD_REARMAMENT_STATE"

APPLGC_AGENT_MOTION = 2
REARM_PRE_OPE = 0
REARM_TOTAL = 1


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
    parser = ArgumentParser(description="Send rearm command to ECU_MOTION")
    parser.add_argument(
        "--type",
        choices=["pre_ope", "total"],
        default="pre_ope",
        help="Rearm type",
    )
    parser.add_argument("--node", type=int, default=2, help="CAN node (default: 2 for ECU_MOTION)")

    args = parser.parse_args()
    rearm_type = REARM_PRE_OPE if args.type == "pre_ope" else REARM_TOTAL
    send_rearm_command(rearm_type, args.node)
