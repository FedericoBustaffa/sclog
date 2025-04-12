#include "logger.hpp"

#include <fmt/core.h>
#include <iostream>

namespace sclog
{

static void handle(level* m_level, queue* messages,
                   std::vector<handler>* handlers)
{
    while (true)
    {
        queue::message msg = messages->pop();
        if (msg.content == "")
            break;

        for (handler& h : *handlers)
        {
            if ((msg.lvl >= *m_level) & (msg.lvl >= h.get_level()))
                h.write(msg.content, msg.lvl);
        }
    }
}

logger::logger(level level)
    : m_level(level), m_logger(handle, &m_level, &m_messages, &m_handlers)
{
    m_handlers.emplace_back(&std::cout, level, default_formatter);
}

logger::~logger()
{
    m_messages.push({"", level::info});
    m_logger.join();
}

void logger::set_level(level level) { m_level = level; }

void logger::add_handler(const handler& handler)
{
    m_handlers.push_back(handler);
}

std::vector<handler>& logger::get_handlers() { return m_handlers; }

} // namespace sclog
