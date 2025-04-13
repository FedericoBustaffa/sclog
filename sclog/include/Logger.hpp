#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <thread>

#include <fmt/chrono.h>
#include <fmt/format.h>
#include <fmt/std.h>

#include "Level.hpp"
#include "MessageQueue.hpp"

namespace sclog
{

class Logger
{
public:
    Logger(Level lvl = Level::Trace);

    inline void setLevel(Level level) { m_Level = level; }

    inline const Level& getLevel() const { return m_Level; }

    // --- Logging functions ---
    template <typename... Args>
    void log(Level level, std::string&& format, Args&&... args)
    {
        if (level < m_Level)
            return;

        std::string msg_fmt =
            fmt::format(fmt::runtime(format), std::forward<Args>(args)...);

        auto timestamp = std::chrono::system_clock::now();
        std::string time_fmt =
            fmt::format("{:%Y-%m-%d %H:%M:%S}", fmt::gmtime(timestamp));

        std::string message =
            fmt::format("{} - [{}]: {}", time_fmt, level, msg_fmt);

        m_Queue.push(std::move(message));
    }

    template <typename... Args>
    void trace(std::string&& format, Args&&... args)
    {
        log(Level::Trace, std::forward<std::string>(format),
            std::forward<Args>(args)...);
    }

    template <typename... Args>
    void debug(std::string&& format, Args&&... args)
    {
        log(Level::Debug, std::forward<std::string>(format),
            std::forward<Args>(args)...);
    }

    template <typename... Args>
    void info(std::string&& format, Args&&... args)
    {
        log(Level::Info, std::forward<std::string>(format),
            std::forward<Args>(args)...);
    }

    template <typename... Args>
    void warning(std::string&& format, Args&&... args)
    {
        log(Level::Warning, std::forward<std::string>(format),
            std::forward<Args>(args)...);
    }

    template <typename... Args>
    void error(std::string&& format, Args&&... args)
    {
        log(Level::Error, std::forward<std::string>(format),
            std::forward<Args>(args)...);
    }

    ~Logger();

private:
    Level m_Level;
    MessageQueue m_Queue;
    std::thread* m_Thread;
};

} // namespace sclog

#endif
