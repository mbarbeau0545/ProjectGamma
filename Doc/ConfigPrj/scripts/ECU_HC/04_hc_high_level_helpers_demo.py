from app.script_runtime_api import log
from app.script_api_head_cutter import *

log('--- HeadCutter helper API demo ---')

send_hc_joint(alpha_b_mrad=1000, alpha_c_mrad=900, knife_rpm=20, cntr_knife_rpm=20, pos_id=1, node=1)
fb = get_hc_feedback(timeout_ms=50)
log(f"feedback after single command: {fb}")

points = []
for i in range(120):
    points.append((900 + i, 1000 + (i // 2), 20, 20))

send_hc_trajectory_joint(points, dt_ms=10, start_pos_id=2, node=1)
log('joint trajectory done')
