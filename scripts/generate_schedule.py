#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""BharatOPT Multi-Period Schedule Scenario Generator."""
import json, sys

def generate_crude_arrivals(days=7):
    arrivals = []
    crudes = ['Arab_Light', 'Brent', 'Basrah_Medium', 'Mumbai_High']
    for d in range(1, days + 1):
        if d % 2 == 1:
            arrivals.append({
                'day': d,
                'vessel': f'VLCC_{100+d}',
                'crude': crudes[d % len(crudes)],
                'volume_bbl': 1000000.0,
                'laytime_hours': 36.0
            })
    return arrivals

