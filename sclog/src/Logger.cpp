#include "Logger.hpp"

#include <fmt/core.h>

namespace sclog
{

Logger::Logger(Level level) : m_Level(level)
{
    auto fetch = [this]() {
        std::optional<std::string> message;
        while (true)
        {
            message = m_Queue.pop();
            if (!message.has_value())
                return;

            fmt::print("{}\n", message.value());
        }
    };

    m_Thread = new std::thread(fetch);
}

Logger::~Logger()
{
    m_Queue.close();
    m_Thread->join();
    delete m_Thread;
}

} // namespace sclog
