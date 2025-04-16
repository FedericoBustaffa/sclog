#include <chrono>
#include <random>
#include <vector>

#include "Logger.hpp"

namespace sc = sclog;

void async_logging(uint32_t id, sc::Logger* logger)
{
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::discrete_distribution<int32_t> dist(100, 1000);

    std::this_thread::sleep_for(std::chrono::milliseconds(dist(eng)));
    logger->trace("trace message from thread: {}\n", id);

    std::this_thread::sleep_for(std::chrono::milliseconds(dist(eng)));
    logger->debug("debug message from thread: {}\n", id);

    std::this_thread::sleep_for(std::chrono::milliseconds(dist(eng)));
    logger->info("info message from thread: {}\n", id);

    std::this_thread::sleep_for(std::chrono::milliseconds(dist(eng)));
    logger->warning("warning message from thread: {}\n", id);

    std::this_thread::sleep_for(std::chrono::milliseconds(dist(eng)));
    logger->error("error message from thread: {}\n", id);
}

int main(int argc, const char** argv)
{
    sc::Logger logger(sc::Level::Debug);
    logger.addHandler("history.log", "w", sc::Level::Trace);

    std::vector<std::thread> workers;
    for (int i = 0; i < 1; i++)
        workers.emplace_back(async_logging, i, &logger);

    for (auto& w : workers)
        w.join();

    return 0;
}
