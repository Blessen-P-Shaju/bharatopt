#pragma once
#include <string>
#include "bharatopt/model.hpp"
namespace bharatopt {
LPModel parse_mps(const std::string& path);
void write_mps(const LPModel& model, const std::string& path);
LPModel make_refinery_demo();
LPModel make_milp_demo();
}
struct MPSReadOptions {
    bool allow_free_variables{true};
    bool strict_fixed_format{false};
    double zero_coefficient_tolerance{1e-12};
};
struct MPSStats {
    int rows{0};
    int cols{0};
    int non_zeros{0};
    double density_pct{0.0};
};
MPSStats inspect_mps_stream(const std::string& path);
// MPS robust token parsing parser checkpoint 5
// MPS robust token parsing parser checkpoint 7
