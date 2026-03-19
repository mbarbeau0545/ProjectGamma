from app.script_runtime_api import log
from app.script_api_head_cutter import *

# Cartesian sweep with high-level helper
pts = []
alplha_b = 1500
alplha_c = 1500
for i in range(50):
    alplha_b = alplha_b - 30
    alplha_c = alplha_c - 30
    pts.append((alplha_b, alplha_c, 25, 25))

send_hc_trajectory_joint(pts, dt_ms=0, start_pos_id=100, node=0)
log(f"feedback end={get_hc_feedback(timeout_ms=50)}")
