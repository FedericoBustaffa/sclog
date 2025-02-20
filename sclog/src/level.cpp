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

} // namespace sclog