#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""BharatOPT Crude Assay Manager CLI Tool."""
import json, os, sys

ASSAY_FILE = os.path.join(os.path.dirname(__file__), '..', 'data', 'crude_assays.json')

def load_assays():
    with open(ASSAY_FILE, 'r', encoding='utf-8') as f:
        return json.load(f)

