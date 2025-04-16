#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <cstdio>
#include <string>

#include "Level.hpp"

namespace sclog
{

class Handler
{
public:
    Handler() = delete;

    Handler(const Handler&) = delete;
    Handler& operator=(const Handler&) = delete;

    Handler(Handler&&) noexcept;
    Handler& operator=(Handler&&) noexcept;

    Handler(std::FILE* stream, Level level = Level::Trace);
    Handler(const std::string& filepath, const char* mode = "w",
            Level level = Level::Trace);

    inline std::FILE* stream() const { return m_File; }

    inline void setLevel(Level level) { m_Level = level; }
    inline Level getLevel() { return m_Level; }

    inline void enable() { m_Enabled = true; }
    inline void disable() { m_Enabled = false; }
    inline bool isEnabled() const { return m_Enabled; }

    ~Handler();

private:
    std::FILE* m_File = nullptr;
    Level m_Level;
    bool m_OwnFile = false;
    bool m_Enabled = true;
};

} // namespace sclog

#endif // !HANDLER_HPP
