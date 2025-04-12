#include <fstream>
#include <thread>
#include <vector>

#include "level.hpp"
#include "logger.hpp"

namespace sc = sclog;

using namespace std::chrono_literals;

void test(sc::logger* logger)
{
    for (int i = 0; i < 10; ++i)
    {
        std::this_thread::sleep_for(200ms);
        auto id = std::this_thread::get_id();

        logger->trace("Trace message {} from thread {}\n", i + 1, id);
        logger->debug("Debug message {} from thread {}\n", i + 1, id);
        logger->info("Info message {} from thread {}\n", i + 1, id);
        logger->warning("Warning message {} from thread {}\n", i + 1, id);
        logger->error("Error message {} from thread {}\n", i + 1, id);
    }
}

int main(int argc, const char** argv)
{
    sc::logger logger(sc::level::trace);
    std::ofstream file("log.log");
    sc::handler file_handler(&file, sc::level::debug, sc::default_formatter);
    logger.add_handler(file_handler);

    std::vector<std::thread> threads;
    for (int i = 0; i < 8; ++i)
        threads.push_back(std::thread(test, i, &logger));

    for (auto& thread : threads)
        thread.join();

    return 0;
}
