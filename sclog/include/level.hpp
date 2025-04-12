#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <fmt/color.h>
#include <string>

namespace sclog
{

enum class level
{
    trace = 10,
    debug = 20,
    info = 30,
    warning = 40,
    error = 50
};

std::string level_to_string(level level);

fmt::color level_color(level level);

} // namespace sclog

#endif
