# BharatOPT OpenAPI 3.1 REST API Reference Specification

## 1. Overview
High-performance REST API endpoints providing programmatic access to the BharatOPT optimization engine.

Base URL: `http://localhost:8000/api/v1`

### POST /api/v1/optimize Endpoint Specification
Accepts standard MPS or JSON flowsheet payloads and executes high-speed optimization.

### Request Schema: OptimizeRequest
Defines solver choice (simplex, interior_point, qp), time limit, tolerances, and input model.

