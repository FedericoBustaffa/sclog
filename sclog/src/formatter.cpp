#include "formatter.hpp"

#include <iomanip>
#include <chrono>
#include <fmt/core.h>
#include <level.hpp>

namespace sclog
{

formatter::formatter(const std::string& format) : m_format(format) {}

std::string formatter::format(const std::string& content, level level)
{
	auto now = std::chrono::system_clock::now();
	auto now_time = std::chrono::system_clock::to_time_t(now);
	std::stringstream ss;
	ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");

	return fmt::format(m_format, ss.str(), level_color(level), level_to_string(level), content,
					   RESET);
}

formatter::~formatter() {}

} // namespace sclog