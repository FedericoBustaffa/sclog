#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <fstream>

#include "level.hpp"

namespace sclog
{

class handler
{
public:
	handler(const char* filename, level level);

	inline const level& get_level() const { return m_level; }

	void write(const std::string& message);

private:
	level m_level;
	std::ofstream m_stream;
};

} // namespace sclog

#endif