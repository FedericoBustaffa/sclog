#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>

namespace sclog
{

class queue
{
public:
    queue(size_t capacity = 0);

    inline size_t capacity() const { return m_capacity.load(); }

    void push(const std::string& msg);

    std::string pop();

    ~queue();

private:
    std::atomic<size_t> m_capacity;
    std::queue<std::string> m_buffer;

    std::mutex m_mutex;
    std::condition_variable m_condition;
};

} // namespace sclog

#endif
