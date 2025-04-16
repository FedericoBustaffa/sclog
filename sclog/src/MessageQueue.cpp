#include "MessageQueue.hpp"

namespace sclog
{

MessageQueue::MessageQueue() : m_Closed(false) {}

void MessageQueue::push(std::string&& message, Level level)
{
    std::unique_lock<std::mutex> lock(m_Mutex);
    m_Queue.push({message, level});
    m_Empty.notify_one();
}

std::optional<std::pair<std::string, Level>> MessageQueue::pop()
{
    std::unique_lock<std::mutex> lock(m_Mutex);
    while (!m_Closed.load() && m_Queue.empty())
        m_Empty.wait(lock);

    if (m_Closed.load() && m_Queue.empty())
        return std::nullopt;

    std::pair<std::string, Level> message = std::move(m_Queue.front());
    m_Queue.pop();

    m_Full.notify_one();

    return message;
}

void MessageQueue::close()
{
    std::unique_lock<std::mutex> lock(m_Mutex);
    m_Closed.store(true);
    m_Empty.notify_one();
}

MessageQueue::~MessageQueue()
{
    if (!m_Closed.load())
        this->close();
}

} // namespace sclog
