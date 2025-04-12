#include "level.hpp"

#include <fmt/color.h>

namespace sclog
{

std::string level_to_string(level level)
{
    switch (level)
    {
    case level::trace:
        return "TRACE";
    case level::debug:
        return "DEBUG";
    case level::info:
        return "INFO";
    case level::warning:
        return "WARNING";
    case level::error:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

fmt::color level_color(level level)
{
    switch (level)
    {
    case level::trace:
        return fmt::color::white;
    case level::debug:
        return fmt::color::cyan;
    case level::info:
        return fmt::color::green;
    case level::warning:
        return fmt::color::yellow;
    case level::error:
        return fmt::color::red;
    }
}

} // namespace sclog
