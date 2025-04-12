#include "Logger.hpp"

namespace sclog
{

static void handle(Level* level, MessageQueue* queue)
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

Logger::Logger(Level level)
    : m_Level(level), m_Thread(handle, &m_Level, &m_Queue)
{
}

Logger::~Logger()
{
    m_Queue.close();
    m_Thread.join();
}

void Logger::setLevel(Level level) { m_Level = level; }

} // namespace sclog
