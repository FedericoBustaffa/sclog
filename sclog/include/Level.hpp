#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <fmt/color.h>
#include <fmt/format.h>

namespace sclog
{

enum class Level
{
    Trace = 10,
    Debug = 20,
    Info = 30,
    Warning = 40,
    Error = 50,
    Disabled = 100,
};

fmt::color levelToColor(Level level);

} // namespace sclog

template <>
struct fmt::formatter<sclog::Level> : public fmt::formatter<std::string_view>
{
    auto format(sclog::Level level, fmt::format_context& ctx)
    {
        std::string_view name;
        switch (level)
        {
        case sclog::Level::Trace:
            name = "TRACE";
            break;
        case sclog::Level::Debug:
            name = "DEBUG";
            break;
        case sclog::Level::Info:
            name = "INFO";
            break;
        case sclog::Level::Warning:
            name = "WARNING";
            break;
        case sclog::Level::Error:
            name = "ERROR";
            break;
        case sclog::Level::Disabled:
            name = "DISABLED";
            break;
        default:
            name = "UNKNOWN";
            break;
        }

        return fmt::formatter<std::string_view>::format(name, ctx);
    }
};

#endif
