#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <iostream>

#include "level.hpp"

namespace sclog
{

class handler
{
public:
	handler(const char* name, level level);
	~handler();

	inline const level& get_level() const { return m_level; }

	void write(const std::string& message);

private:
	level m_level;
	std::ostream* m_stream;
};

} // namespace sclog

#endif