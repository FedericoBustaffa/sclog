#include "Handler.hpp"

#include <fstream>

namespace sclog
{

Handler::Handler(std::ostream* stream) : m_Stream(stream) {}

Handler::Handler(const std::string& filepath)
{
    m_Stream = (std::ostream*)new std::ofstream(filepath);
}

Handler::~Handler() {}

} // namespace sclog
