#include "handler.hpp"

#include <iostream>
#include <fstream>
#include <cstring>

namespace sclog
{

handler::handler(std::ostream* stream, level level)
	: m_stream(stream), m_level(level), m_formatter() {};

void handler::set_formatter(const formatter& formatter) { m_formatter = formatter; }

void handler::write(std::string& message) { *m_stream << m_formatter.format(message); }

handler::~handler() {}

} // namespace sclog