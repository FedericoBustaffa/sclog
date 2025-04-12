#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>
#include <string>

namespace sclog
{

class MessageQueue
{
public:
    MessageQueue();

    void push(std::string&& msg);

    std::optional<std::string> pop();

    void close();

    ~MessageQueue();

private:
    std::atomic<bool> m_Closed;
    std::queue<std::string> m_Queue;

    std::mutex m_Mutex;
    std::condition_variable m_Empty, m_Full;
};

} // namespace sclog

#endif
