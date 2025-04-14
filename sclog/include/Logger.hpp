#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <thread>

#include <fmt/chrono.h>
#include <fmt/format.h>
#include <fmt/std.h>

#include "Handler.hpp"
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

    void addFileHandler(const std::string& filepath);

    template <typename... Args>
    void log(Level level, const std::string& format, Args&&... args)
    {
        if (level < m_Level)
            return;

        std::string msg_fmt =
            fmt::format(fmt::runtime(format), std::forward<Args>(args)...);

        auto timestamp = std::chrono::system_clock::now();
        std::time_t ts = std::chrono::system_clock::to_time_t(timestamp);
        std::string time_fmt =
            fmt::format("{:%Y-%m-%d %H:%M:%S}", fmt::localtime(ts));

        std::string message =
            fmt::format("{} - [{}]: {}", time_fmt, level, msg_fmt);

        m_Queue.push(std::move(message));
    }

    template <typename... Args>
    void trace(const std::string& format, Args&&... args)
    {
        log(Level::Trace, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void debug(const std::string& format, Args&&... args)
    {
        log(Level::Debug, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void info(const std::string& format, Args&&... args)
    {
        log(Level::Info, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void warning(const std::string& format, Args&&... args)
    {
        log(Level::Warning, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void error(const std::string& format, Args&&... args)
    {
        log(Level::Error, format, std::forward<Args>(args)...);
    }

    ~Logger();

private:
    Level m_Level;
    MessageQueue m_Queue;
    std::thread* m_Thread;

    std::vector<Handler> m_Handlers;
};

} // namespace sclog

#endif
