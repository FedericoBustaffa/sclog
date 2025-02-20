#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>

#include "level.hpp"

namespace sclog
{

class queue
{
public:
	queue();
	~queue();

	void push(const std::string& message, level level);
	std::pair<std::string, level> pop();

private:
	std::mutex m_mutex;
	std::condition_variable m_condition;
	std::queue<std::pair<std::string, level>> m_buffer;
};

} // namespace sclog

#endif