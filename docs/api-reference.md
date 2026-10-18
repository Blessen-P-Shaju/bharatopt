# BharatOPT OpenAPI 3.1 REST API Reference Specification

## 1. Overview
High-performance REST API endpoints providing programmatic access to the BharatOPT optimization engine.

Base URL: `http://localhost:8000/api/v1`

### POST /api/v1/optimize Endpoint Specification
Accepts standard MPS or JSON flowsheet payloads and executes high-speed optimization.

### Request Schema: OptimizeRequest
Defines solver choice (simplex, interior_point, qp), time limit, tolerances, and input model.

### Response Schema: OptimizeResponse
Returns certified objective value, execution status (optimal, infeasible, unbounded), solve duration, and primal variable vectors.

### GET /api/v1/crude-assays Endpoint Specification
Queries crude oil assay catalog with filters by API gravity, sulfur content, and origin.

### GET /api/v1/crude-assays/{crude_id} Endpoint
Retrieves complete True Boiling Point (TBP) distillation cuts and physical properties for specified crude.

