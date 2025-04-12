#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <iostream>

#include "formatter.hpp"
#include "level.hpp"

namespace sclog
{

class handler
{
public:
    handler(std::ostream* stream, level level, const formatter& formatter);
    ~handler();

    inline void set_level(level level) { m_level = level; }
    inline const level& get_level() const { return m_level; }

    void set_formatter(const formatter& formatter);

    void write(std::string& message, level level);

private:
    std::ostream* m_stream;
    level m_level;
    formatter m_formatter;
};

} // namespace sclog

#endif
