from app.script_runtime_api import log
from app.script_api_head_cutter import *

# Cartesian sweep with high-level helper
pts = []
for i in range(100):
    x = 100 + (i % 40)
    y = -200  + (i % 40)
    pts.append((x, y, 25, 25))

send_hc_trajectory_cartesian(pts, dt_ms=15, start_pos_id=100, node=0)
log(f"feedback end={get_hc_feedback(timeout_ms=50)}")
