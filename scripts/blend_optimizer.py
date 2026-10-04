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

