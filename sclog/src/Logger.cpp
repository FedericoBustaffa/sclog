#include "Logger.hpp"

#include <fmt/core.h>

namespace sclog
{

Logger::Logger(Level level) : m_Level(level)
{
    m_Handlers.emplace_back(&std::cout);
    // m_Handlers.push_back(&std::cerr);

    auto fetch = [this]() {
        std::optional<std::string> message;
        while (true)
        {
            message = m_Queue.pop();
            if (!message.has_value())
                return;

            for (Handler& h : m_Handlers)
                fmt::print(h.stream(), "{}", message.value());
        }
    };

    m_Thread = new std::thread(fetch);
}

void Logger::addFileHandler(const std::string& filepath)
{
    m_Handlers.emplace_back(filepath);
}

Logger::~Logger()
{
    m_Queue.close();
    m_Thread->join();
    delete m_Thread;
}

} // namespace sclog
