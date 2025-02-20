#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <fmt/core.h>

#include "level.hpp"
#include "handler.hpp"
#include "queue.hpp"

namespace sclog
{

class logger
{
public:
	logger(level level = level::warning);

	~logger();

	// --- Setters ---
	void set_level(level level);

	inline const level& get_level() const { return m_level; }

	void add_handler(const char* filename, level level = level::warning);

	// --- Logging functions ---
	template <typename... Args>
	void log(level level, const std::string& format, Args... args)
	{
		std::string name = level_to_string(level);
		m_messages.push({fmt::format("[{}]: " + format, name, args...), level});
	}

	template <typename... Args>
	void debug(const std::string& format, Args... args)
	{
		log(level::debug, format, args...);
	}

	template <typename... Args>
	void info(const std::string& format, Args... args)
	{
		log(level::info, format, args...);
	}

	template <typename... Args>
	void warning(const std::string& format, Args... args)
	{
		log(level::warning, format, args...);
	}

	template <typename... Args>
	void error(const std::string& format, Args... args)
	{
		log(level::error, format, args...);
	}

private:
	level m_level;
	std::vector<handler> m_handlers;

	// --- Async logging ---
	queue m_messages;
	std::thread m_logger;
};

} // namespace sclog

#endif