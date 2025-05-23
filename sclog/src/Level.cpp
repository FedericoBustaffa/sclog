#include "Level.hpp"

#include <fmt/color.h>

namespace sclog
{

fmt::color levelToColor(Level level)
{
    switch (level)
    {
    case Level::Trace:
        return fmt::color::white;
    case Level::Debug:
        return fmt::color::cyan;
    case Level::Info:
        return fmt::color::green;
    case Level::Warning:
        return fmt::color::yellow;
    case Level::Error:
        return fmt::color::red;
    default:
        return fmt::color::white;
    }
}

} // namespace sclog
