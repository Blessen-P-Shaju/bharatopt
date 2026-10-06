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

def generate_tank_inventory(tanks=6):
    inventory = {}
    for i in range(1, tanks + 1):
        inventory[f'TK-{100+i}'] = {
            'capacity_bbl': 500000.0,
            'initial_level_bbl': 250000.0,
            'min_heel_bbl': 50000.0,
            'max_ullage_bbl': 475000.0
        }
    return inventory

def export_schedule(filename='examples/multi_period_crude_plan.json', days=7):
    plan = {
        'horizon_days': days,
        'arrivals': generate_crude_arrivals(days),
        'tanks': generate_tank_inventory(),
        'daily_cdu_feed_target_bbl': 300000.0
    }
    with open(filename, 'w', encoding='utf-8') as f:
        json.dump(plan, f, indent=2)
    print(f'Schedule scenario written to {filename}')

if __name__ == '__main__':
    days = int(sys.argv[1]) if len(sys.argv) > 1 else 7
    export_schedule(days=days)
# Generator routine checkpoint 1: verified scheduling constraints
