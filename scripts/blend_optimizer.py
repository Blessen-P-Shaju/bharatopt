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

