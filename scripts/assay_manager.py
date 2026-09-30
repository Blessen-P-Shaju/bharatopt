#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""BharatOPT Crude Assay Manager CLI Tool."""
import json, os, sys

ASSAY_FILE = os.path.join(os.path.dirname(__file__), '..', 'data', 'crude_assays.json')

def load_assays():
    with open(ASSAY_FILE, 'r', encoding='utf-8') as f:
        return json.load(f)

def list_crudes():
    assays = load_assays()
    for k, v in assays.items():
        if k == 'metadata': continue
        print(f"{k:15} | {v['name']:20} | API: {v['api_gravity']:4.1f} | S: {v['sulfur_wt_pct']:4.2f}%")

def get_cuts(crude_id):
    assays = load_assays()
    if crude_id not in assays:
        print(f"Unknown crude: {crude_id}")
        return None
    return assays[crude_id]['yield_cuts_pct']

def blend_api_gravity(crudes_fractions):
    assays = load_assays()
    tot_vol = sum(crudes_fractions.values())
    tot_sg = sum((141.5 / (assays[k]['api_gravity'] + 131.5)) * frac for k, frac in crudes_fractions.items())
    avg_sg = tot_sg / tot_vol
    return (141.5 / avg_sg) - 131.5

def blend_sulfur_wt_pct(crudes_fractions):
    assays = load_assays()
    tot_vol = sum(crudes_fractions.values())
    tot_s = sum(assays[k]['sulfur_wt_pct'] * frac for k, frac in crudes_fractions.items())
    return tot_s / tot_vol

if __name__ == '__main__':
    if len(sys.argv) > 1 and sys.argv[1] == 'list':
        list_crudes()
    else:
        print('Usage: python assay_manager.py [list]')
# Validated for Python 3.10+ with UTF-8 encoding support
