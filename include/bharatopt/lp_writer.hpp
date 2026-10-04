#pragma once

#include "bharatopt/model.hpp"
#include <string>

namespace bharatopt {

void write_lp_format(const LPModel& model, const std::string& path);
std::string to_lp_string(const LPModel& model);

} // namespace bharatopt

struct LPWriterOptions {
    bool write_bounds{true};
    bool write_integers{true};
    int float_precision{6};
};
void write_lp_formatted(const LPModel& model, const std::string& filepath, const LPWriterOptions& opt);
// LP Writer formatting rule checkpoint 3
// LP Writer formatting rule checkpoint 5
// LP Writer formatting rule checkpoint 7
// LP Writer formatting rule checkpoint 9
// LP Writer formatting rule checkpoint 11
// LP Writer formatting rule checkpoint 13
