#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>
#include <string>

#include "Level.hpp"

namespace sclog
{

class MessageQueue
{
public:
    MessageQueue();

    void push(std::string&& msg, Level level);

    std::optional<std::pair<std::string, Level>> pop();

    void close();

    ~MessageQueue();

private:
    std::atomic<bool> m_Closed;
    std::queue<std::pair<std::string, Level>> m_Queue;

    std::mutex m_Mutex;
    std::condition_variable m_Empty, m_Full;
};

} // namespace sclog

#endif
