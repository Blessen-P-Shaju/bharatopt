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

