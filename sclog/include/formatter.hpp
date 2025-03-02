#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <fmt/core.h>

#include "level.hpp"

namespace sclog
{

class formatter
{
public:
	formatter(const std::string& format = "");
	~formatter();

	std::string format(const std::string& content, level level);

protected:
	std::string m_format;
};

extern formatter default_formatter;

} // namespace sclog

#endif