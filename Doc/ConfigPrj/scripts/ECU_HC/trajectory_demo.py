from app.script_runtime_api import *

# Example: send HeadCutter trajectory with helper API
# pos_type: 0=cartesian (x,y), 1=joint (alpha_b, alpha_c)

node = 0
points = []
for i in range(4):
    # joint example: alpha_b/alpha_c in mrad
    alpha_b = 900 + i
    alpha_c = 1000 + (i // 2)
    points.append((alpha_b, alpha_c, 20, 20, 1))

run_hc_position_trajectory(points, dt_ms=10, node=node, start_pos_id=1)

log('trajectory done')
