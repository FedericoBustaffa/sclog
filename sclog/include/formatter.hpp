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

private:
	std::string m_format;
};

} // namespace sclog

#endif