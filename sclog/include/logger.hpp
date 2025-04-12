#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fmt/core.h>
#include <string>
#include <thread>
#include <vector>

#include "formatter.hpp"
#include "handler.hpp"
#include "level.hpp"
#include "queue.hpp"

namespace sclog
{

class logger
{
public:
    logger(level level = level::warning);
    ~logger();

    void set_level(level level);
    inline const level& get_level() const { return m_level; }

    void add_handler(const handler& handler);
    std::vector<handler>& get_handlers();

    // --- Logging functions ---
    template <typename... Args>
    void log(level lvl, const std::string& msg, Args&&... args)
    {
        std::string formatted =
            m_formatter.format(lvl, msg, std::forward<Args>(args)...);
        m_messages.push(formatted);
    }

    template <typename... Args>
    void trace(const std::string& message, Args&&... args)
    {
        log(level::trace, message, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void debug(const std::string& message, Args&&... args)
    {
        log(level::debug, message, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void info(const std::string& message, Args&&... args)
    {
        log(level::info, message, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void warning(const std::string& message, Args&&... args)
    {
        log(level::warning, message, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void error(const std::string& message, Args&&... args)
    {
        log(level::error, message, std::forward<Args>(args)...);
    }

private:
    level m_level;
    std::vector<handler> m_handlers;
    formatter m_formatter;

    queue m_messages;
    std::thread m_logger;
};

} // namespace sclog

#endif
