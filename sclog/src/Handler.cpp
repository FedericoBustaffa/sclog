#include "Handler.hpp"

#include <stdexcept>

namespace sclog
{

Handler::Handler(Handler&& other) noexcept
    : m_File(other.m_File), m_Level(other.m_Level), m_OwnFile(other.m_OwnFile),
      m_Enabled(other.m_Enabled)
{
    other.m_File = nullptr;
    other.m_Level = Level::Disabled;
    other.m_OwnFile = false;
    other.m_Enabled = false;
}

Handler& Handler::operator=(Handler&& other) noexcept
{
    if (this != &other)
    {
        if (m_OwnFile && m_File)
            std::fclose(m_File);

        m_File = other.m_File;
        m_Level = other.m_Level;
        m_OwnFile = other.m_OwnFile;
        m_Enabled = other.m_Enabled;

        other.m_File = nullptr;
        other.m_Level = Level::Disabled;
        other.m_OwnFile = false;
        other.m_Enabled = false;
    }

    return *this;
}

Handler::Handler(std::FILE* stream, Level level) : m_Level(level)
{
    if (stream != stdout && stream != stderr)
        throw std::runtime_error("unsupported stream");

    m_File = stream;
    m_OwnFile = false;
}

Handler::Handler(const std::string& filepath, const char* mode, Level level)
    : m_Level(level)
{
    m_File = std::fopen(filepath.c_str(), mode);
    if (!m_File)
        throw std::runtime_error("could not open file");

    m_OwnFile = true;
}

Handler::~Handler()
{
    if (m_OwnFile && m_File)
    {
        std::fclose(m_File);
        m_File = nullptr;
    }
}

} // namespace sclog
