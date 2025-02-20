#include "queue.hpp"

#include <utility>

namespace sclog
{

queue::queue() {}

queue::~queue() {}

void queue::push(const std::string& message, level level)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_buffer.push({message, level});
	m_condition.notify_all();
}

std::pair<std::string, level> queue::pop()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	while (m_buffer.empty())
		m_condition.wait(lock);

	std::pair<std::string, level> msg = m_buffer.front();
	m_buffer.pop();
	return msg;
}

} // namespace sclog