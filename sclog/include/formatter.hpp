#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <fmt/core.h>
#include <fmt/color.h>

namespace sclog
{

class formatter
{
public:
	formatter(const std::string& format = "");
	virtual ~formatter();

	virtual std::string format(const std::string& content);

private:
	std::string m_format;
};

} // namespace sclog

#endif