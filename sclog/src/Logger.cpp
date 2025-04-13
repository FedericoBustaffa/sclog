#include "Logger.hpp"

#include <fmt/core.h>

namespace sclog
{

static void async_log(MessageQueue* queue)
{
    std::optional<std::string> message;
    while (true)
    {
        message = queue->pop();
        if (!message.has_value())
            return;

        fmt::print("{}\n", message.value());
    }
}

Logger::Logger(Level level) : m_Level(level), m_Thread(async_log, &m_Queue) {}

Logger::~Logger()
{
    m_Queue.close();
    m_Thread.join();
}

} // namespace sclog
