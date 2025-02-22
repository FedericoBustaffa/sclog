#include "logger.hpp"

#include <iostream>
#include <fmt/core.h>

namespace sclog
{

static void handle(level* m_level, queue* messages, std::vector<handler>* handlers)
{
	while (true)
	{
		queue::message msg = messages->pop();
		if (msg.msg == "")
			break;

		for (handler& h : *handlers)
		{
			if ((msg.lvl >= *m_level) & (msg.lvl >= h.get_level()))
				h.write(msg.msg);
		}
	}
}

logger::logger(level level) : m_level(level), m_logger(handle, &m_level, &m_messages, &m_handlers)
{
	m_handlers.emplace_back("stdout", level::info);
}

logger::~logger()
{
	m_messages.push({"", level::info});
	m_logger.join();
}

void logger::set_level(level level) { m_level = level; }

void logger::add_handler(const char* filename, level level)
{
	m_handlers.emplace_back(filename, level);
}

} // namespace sclog