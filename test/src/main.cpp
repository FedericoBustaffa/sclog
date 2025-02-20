#include <thread>
#include <chrono>
#include <vector>
#include <iostream>

#include "sclog.hpp"

namespace sc = sclog;

using namespace std::chrono_literals;

void test(sc::logger& logger)
{
	for (int i = 0; i < 10; ++i)
	{
		std::this_thread::sleep_for(200ms);
		logger.debug("This is the {} debug message\n", i + 1);
		logger.info("This is the {} info message\n", i + 1);
		logger.warning("This is the {} warning message\n", i + 1);
		logger.error("This is the {} error message\n", i + 1);
	}
}

int main(int argc, const char** argv)
{
	sc::logger logger(sc::level::debug);
	logger.add_handler("log.log", sc::level::debug);

	std::vector<std::thread> threads;
	for (int i = 0; i < 8; ++i)
		threads.push_back(std::thread(test, std::ref(logger)));

	for (auto& thread : threads)
		thread.join();

	return 0;
}
