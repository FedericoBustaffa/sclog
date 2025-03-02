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

	void add_handler(const handler& handler);

	std::vector<handler>& get_handlers();

	// --- Logging functions ---
	template <typename... Args>
	void log(level level, const std::string& message, Args... args)
	{
		m_messages.push({fmt::format(message, args...), level});
	}

	template <typename... Args>
	void trace(const std::string& message, Args... args)
	{
		log(level::trace, message, args...);
	}

	template <typename... Args>
	void debug(const std::string& message, Args... args)
	{
		log(level::debug, message, args...);
	}

	template <typename... Args>
	void info(const std::string& message, Args... args)
	{
		log(level::info, message, args...);
	}

	template <typename... Args>
	void warning(const std::string& message, Args... args)
	{
		log(level::warning, message, args...);
	}

	template <typename... Args>
	void error(const std::string& message, Args... args)
	{
		log(level::error, message, args...);
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