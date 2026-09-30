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
