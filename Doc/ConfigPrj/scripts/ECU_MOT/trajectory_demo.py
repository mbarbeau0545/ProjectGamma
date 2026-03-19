from app.script_runtime_api import log
from app.script_api_head_cutter import send_hc_joint, get_hc_feedback

# High-level HeadCutter API
send_hc_joint(alpha_b_mrad=1000, alpha_c_mrad=900, knife_rpm=20, cntr_knife_rpm=20, pos_id=1, node=1)

fb = get_hc_feedback(timeout_ms=50)
log(f"feedback={fb}")
