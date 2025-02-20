#include "logger.hpp"

#include <iostream>
#include <fmt/core.h>

namespace sclog
{

static void handle(level& m_level, queue& messages, std::vector<handler>& handlers)
{
	while (true)
	{
		queue::message msg = messages.pop();
		if (msg.msg == "")
			break;

		if (msg.lvl >= m_level)
			std::cout << level_color(msg.lvl) + msg.msg + RESET;

		for (handler& h : handlers)
		{
			if ((msg.lvl >= m_level) & (msg.lvl >= h.get_level()))
				h.write(msg.msg);
		}
	}
}

logger::logger(level level)
	: m_level(level),
	  m_logger(handle, std::ref(m_level), std::ref(m_messages), std::ref(m_handlers))
{
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