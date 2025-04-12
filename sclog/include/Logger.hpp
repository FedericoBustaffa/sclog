#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <thread>

#include <fmt/chrono.h>
#include <fmt/format.h>

#include "Level.hpp"
#include "MessageQueue.hpp"

namespace sclog
{

class Logger
{
public:
    Logger(Level lvl = Level::Trace);

    void setLevel(Level level);

    inline const Level& getLevel() const { return m_Level; }

    // --- Logging functions ---
    template <typename... Args>
    void log(Level level, const std::string_view& format, Args&&... args)
    {
        std::string msg_fmt =
            fmt::format(fmt::runtime(format), std::forward<Args>(args)...);

        auto timestamp = std::chrono::system_clock::now();
        std::string time_fmt =
            fmt::format("{:%Y-%m-%d %H:%M:%S}", fmt::localtime(timestamp));

        std::string message =
            fmt::format("{} - [{}]: {}", time_fmt, level, msg_fmt);

        m_Queue.push(std::move(message));
    }

    template <typename... Args>
    void trace(const std::string_view& message, Args&&... args)
    {
        log(Level::Trace, message, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void debug(const std::string_view& message, Args&&... args)
    {
        log(Level::Debug, message, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void info(const std::string_view& message, Args&&... args)
    {
        log(Level::Info, message, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void warning(const std::string_view& message, Args&&... args)
    {
        log(Level::Warning, message, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void error(const std::string_view& message, Args&&... args)
    {
        log(Level::Error, message, std::forward<Args>(args)...);
    }

    ~Logger();

private:
    Level m_Level;

    MessageQueue m_Queue;
    std::thread m_Thread;
};

} // namespace sclog

#endif
