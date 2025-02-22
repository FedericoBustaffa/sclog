#include "handler.hpp"

#include <iostream>
#include <fstream>
#include <cstring>

namespace sclog
{

handler::handler(const char* name, level level) : m_level(level)
{
	if (std::strcmp(name, "stdout") == 0)
		m_stream = &std::cout;
	else if (std::strcmp(name, "stderr") == 0)
		m_stream = &std::cerr;
	else
		m_stream = new std::ofstream(name);
};

void handler::write(const std::string& message) { *m_stream << message; }

handler::~handler()
{
	if (m_stream != &std::cout && m_stream != &std::cerr)
		delete m_stream;
}

} // namespace sclog