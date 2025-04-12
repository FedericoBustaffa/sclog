#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <fmt/chrono.h>
#include <fmt/core.h>

#include "level.hpp"

namespace sclog
{

class formatter
{
public:
    formatter(const std::string& format = "");
    ~formatter();

    template <typename... Args>
    std::string format(level lvl, const std::string& msg, Args&&... args)
    {
        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);
        ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");

        return fmt::format(m_format, ss.str(), level_to_string(level), content);
    }

protected:
    std::string m_format;
};

extern formatter default_formatter;

} // namespace sclog

#endif
