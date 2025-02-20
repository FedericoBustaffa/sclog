#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <thread>
#include <vector>

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
	void log(const std::string& message, level level);

	void debug(const std::string& message);

	void info(const std::string& message);

	void warning(const std::string& message);

	void error(const std::string& message);

private:
	level m_level;
	std::vector<handler> m_handlers;

	// --- Async logging ---
	queue m_messages;
	std::thread m_logger;
};

} // namespace sclog

#endif