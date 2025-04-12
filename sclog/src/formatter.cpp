#include "formatter.hpp"

namespace sclog
{

// --- Empty Formatter ---
formatter::formatter(const std::string& format) : m_format(format) {}

formatter::~formatter() {}

} // namespace sclog
