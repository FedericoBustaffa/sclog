#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>

namespace sclog
{

enum class level
{
	trace = 10,
	debug = 20,
	info = 30,
	warning = 40,
	error = 50
};

std::string level_to_string(level level);

#define RESET "\033[0m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RED "\033[31m"

std::string level_color(level level);

} // namespace sclog

#endif