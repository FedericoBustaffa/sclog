#include "handler.hpp"

namespace sclog
{

handler::handler(const char* filename, level level) : m_level(level), m_stream(filename) {};

void handler::write(const std::string& message) { m_stream << message; }

} // namespace sclog