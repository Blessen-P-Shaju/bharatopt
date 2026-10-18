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

### POST /api/v1/blending/evaluate Endpoint
Calculates volumetric and non-linear blend properties (RON, RVP, sulfur, flash point) for given component ratios.

### POST /api/v1/blending/optimize Endpoint
Solves least-cost linear program for automotive gasoline or diesel blending given component pool bounds.

### GET /api/v1/refinery-units Endpoint
Lists all available processing units (CDU, VDU, FCCU, HCU, CCR) with nominal capacities and yields.

### POST /api/v1/refinery-flowsheet/simulate Endpoint
Executes full flowsheet mass balance simulation across connected refinery units.

### POST /api/v1/pooling/solve Endpoint
Solves non-convex bilinear pooling model using successive linear programming (SLP).

### GET /api/v1/health & Readiness Probes
Kubernetes liveness and readiness probe endpoints returning engine status and GPU availability.

### Authentication & API Key Header Specification
Bearer token and `X-API-Key` authentication headers for enterprise multi-tenancy.

### Rate Limiting & Concurrency Policies
Token bucket rate-limiting (100 req/min) and concurrent solve job queue limits.

### Error Code Catalog: 400 Bad Request
Detailed JSON error payloads for malformed MPS files or inconsistent variable bounds.

### Error Code Catalog: 422 Unprocessable Entity
Pydantic validation failure messages with field pointer paths.

### Error Code Catalog: 500 Internal Solver Error
Diagnostic logging and crash report generation for unexpected numerical singularities.

### Streaming Solution Logs via Server-Sent Events (SSE)
Real-time streaming of simplex iteration counts and dual objective progress.

### WebSocket Protocol for Interactive Solving
Bi-directional WebSocket channel for steering solve parameters dynamically.

### Asynchronous Job Submission Protocol
Background job execution with polling or webhook callbacks for large MILP instances.

### CORS & Cross-Origin Resource Sharing Rules
Configuring allowed origins, headers, and credentials for web console integration.

