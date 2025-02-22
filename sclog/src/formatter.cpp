#include "formatter.hpp"

#include <iomanip>

namespace sclog
{

formatter::formatter(const std::string& format) : m_format(format) {}

std::string formatter::format(const std::string& content) { return content; }

formatter::~formatter() {}

// --- PLAIN FORMATTER ---

} // namespace sclog