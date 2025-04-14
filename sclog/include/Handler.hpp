#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <iostream>

namespace sclog
{

class Handler
{
public:
    Handler(std::ostream* stream);

    Handler(const std::string& filepath);

    std::ostream& stream() { return *m_Stream; }

    ~Handler();

private:
    std::ostream* m_Stream;
};

} // namespace sclog

#endif // !HANDLER_HPP
