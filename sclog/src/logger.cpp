#include "logger.hpp"

#include <algorithm>
#include <iostream>
#include <fmt/core.h>

namespace sclog
{

static void handle(level* m_level, queue* messages, std::vector<handler>* handlers)
{
	while (true)
	{
		queue::message msg = messages->pop();
		if (msg.content == "")
			break;

		for (handler& h : *handlers)
		{
			if ((msg.lvl >= *m_level) & (msg.lvl >= h.get_level()))
				h.write(msg.content, msg.lvl);
		}
	}
}

logger::logger(level level) : m_level(level), m_logger(handle, &m_level, &m_messages, &m_handlers)
{
	handler stdout_handler(&std::cout, level);
	formatter formatter("[{}] - {}[{}]: {}{}");
	stdout_handler.set_formatter(formatter);
	m_handlers.push_back(stdout_handler);
}

logger::~logger()
{
	m_messages.push({"", level::info});
	m_logger.join();
}

void logger::set_level(level level) { m_level = level; }

void logger::add_handler(std::ostream* stream, level level)
{
	m_handlers.emplace_back(stream, level);
}

std::vector<handler>& logger::get_handlers() { return m_handlers; }

} // namespace sclog