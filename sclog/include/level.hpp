#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>

namespace sclog
{

enum level
{
	debug = 10,
	info = 20,
	warning = 30,
	error = 40
};

std::string level_to_string(level level);

} // namespace sclog

#endif