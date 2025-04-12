#include "queue.hpp"

namespace sclog
{

queue::queue(size_t capacity) : m_capacity(capacity) {}

void queue::push(const std::string& msg)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_buffer.push(msg);
    m_condition.notify_all();
}

std::string queue::pop()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while (m_buffer.empty())
        m_condition.wait(lock);

    std::string msg = std::move(m_buffer.front());
    m_buffer.pop();

    return msg;
}

queue::~queue() {}

} // namespace sclog
