#include "level.hpp"

namespace sclog
{

std::string level_to_string(level level)
{
	switch (level)
	{
	case level::debug:
		return "DEBUG";
	case level::info:
		return "INFO";
	case level::warning:
		return "WARNING";
	case level::error:
		return "ERROR";
	default:
		return "UNKNOWN";
	}
}

std::string level_color(level level)
{
	switch (level)
	{
	case level::debug:
		return CYAN;
	case level::info:
		return GREEN;
	case level::warning:
		return YELLOW;
	case level::error:
		return RED;
	default:
		return "UNKNOWN";
	}
}

} // namespace sclog