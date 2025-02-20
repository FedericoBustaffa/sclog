#include "sclog.hpp"

#include <iostream>
#include <fmt/core.h>

namespace sclog
{

static void handle(level& m_level, queue& messages, std::vector<handler>& handlers)
{
	while (true)
	{
		std::pair<std::string, level> message = messages.pop();
		if (message.first == "")
			break;

		std::string msg = message.first;
		level level = message.second;

		std::string formatted_string = fmt::format("[{}] {}\n", level_to_string(level), msg);
		if (level >= m_level)
			std::cout << formatted_string;

		for (handler& h : handlers)
		{
			if ((level >= m_level) & (level >= h.get_level()))
				h.write(formatted_string);
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
	m_messages.push("", level::info);
	m_logger.join();
}

void logger::set_level(level level) { m_level = level; }

void logger::add_handler(const char* filename, level level)
{
	m_handlers.emplace_back(filename, level);
}

void logger::log(const std::string& message, level level) { m_messages.push(message, level); }

void logger::debug(const std::string& message) { log(message, level::debug); }

void logger::info(const std::string& message) { log(message, level::info); }

void logger::warning(const std::string& message) { log(message, level::warning); }

void logger::error(const std::string& message) { log(message, level::error); }

} // namespace sclog