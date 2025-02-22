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
	struct message
	{
		std::string content;
		level lvl;
	};

	void push(const message& msg);
	queue::message pop();

private:
	std::mutex m_mutex;
	std::condition_variable m_condition;
	std::queue<message> m_buffer;
};

} // namespace sclog

#endif