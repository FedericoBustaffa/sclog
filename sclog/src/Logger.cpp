#include "Logger.hpp"

#include <fmt/core.h>

namespace sclog
{

Logger::Logger(Level level) : m_Level(level)
{
    m_Handlers.emplace_back(stdout);
    m_Handlers[0].setLevel(m_Level);

    m_Handlers.emplace_back(stderr, Level::Error);

    auto fetch = [this]() {
        std::optional<std::string> message;
        while (true)
        {
            message = m_Queue.pop();
            if (!message.has_value())
                return;

            for (Handler& handler : m_Handlers)
            {
                if (handler.isEnabled() && handler.getLevel() >= m_Level)
                    fmt::print(handler.stream(), "{}", message.value());
            }
        }
    };

    m_Thread = std::thread(fetch);
}

void Logger::addHandler(const std::string& filepath, const char* mode,
                        Level level)
{
    m_Handlers.emplace_back(filepath, mode, level);
}

Logger::~Logger()
{
    m_Queue.close();
    m_Thread.join();
}

} // namespace sclog
