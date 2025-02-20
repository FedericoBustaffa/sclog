#include "queue.hpp"

namespace sclog
{

queue::queue() {}

queue::~queue() {}

void queue::push(const queue::message& msg)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_buffer.push(msg);
	m_condition.notify_all();
}

queue::message queue::pop()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	while (m_buffer.empty())
		m_condition.wait(lock);

	message msg = m_buffer.front();
	m_buffer.pop();

	return msg;
}

} // namespace sclog