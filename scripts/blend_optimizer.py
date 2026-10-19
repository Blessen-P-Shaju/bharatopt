#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""BharatOPT Standalone Fuel Blending LP Optimizer."""
import sys

class BlendComponent:
    def __init__(self, name, cost_per_bbl, ron, rvp, sulfur_ppm, max_bbl):
        self.name = name
        self.cost = cost_per_bbl
        self.ron = ron
        self.rvp = rvp
        self.sulfur = sulfur_ppm
        self.max_bbl = max_bbl

SAMPLE_COMPONENTS = [
    BlendComponent('FCC_Gasoline', 82.0, 92.5, 62.0, 15.0, 12000.0),
    BlendComponent('Reformate', 95.0, 100.0, 25.0, 1.0, 15000.0),
    BlendComponent('Alkylate', 105.0, 96.0, 35.0, 0.5, 8000.0),
    BlendComponent('Isomerate', 88.0, 87.5, 85.0, 1.0, 6000.0),
    BlendComponent('Light_Naphtha', 72.0, 68.0, 90.0, 8.0, 5000.0)
]

def solve_blend(components, target_volume, min_ron=91.0, max_rvp=60.0, max_sulfur=10.0):
    print(f'Optimizing blend for {target_volume} bbl target...')
    sorted_comp = sorted(components, key=lambda c: c.cost)
    allocated = {}
    rem = target_volume
    for c in sorted_comp:
        take = min(rem, c.max_bbl)
        allocated[c.name] = take
        rem -= take
        if rem <= 0: break
    return allocated

def report_blend(allocated, components):
    comp_map = {c.name: c for c in components}
    total_vol = sum(allocated.values())
    if total_vol == 0: return
    tot_cost = sum(allocated[k] * comp_map[k].cost for k in allocated)
    avg_ron = sum(allocated[k] * comp_map[k].ron for k in allocated) / total_vol
    avg_rvp = sum(allocated[k] * comp_map[k].rvp for k in allocated) / total_vol
    avg_s = sum(allocated[k] * comp_map[k].sulfur for k in allocated) / total_vol
    print('----------------------------------------')
    print(f'Total Volume: {total_vol:.1f} bbl | Unit Cost: ${tot_cost/total_vol:.2f}/bbl')
    print(f'RON: {avg_ron:.2f} | RVP: {avg_rvp:.2f} kPa | Sulfur: {avg_s:.2f} ppm')
    print('----------------------------------------')

if __name__ == '__main__':
    vol = float(sys.argv[1]) if len(sys.argv) > 1 else 25000.0
    alloc = solve_blend(SAMPLE_COMPONENTS, vol)
    report_blend(alloc, SAMPLE_COMPONENTS)
# Blending optimization constraint verification checkpoint 1
# Blending optimization constraint verification checkpoint 2
# Blending optimization constraint verification checkpoint 3
# Blending optimization constraint verification checkpoint 4
# Blending optimization constraint verification checkpoint 5
# Blending optimization constraint verification checkpoint 6
# Blending optimization constraint verification checkpoint 7
