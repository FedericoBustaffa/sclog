#include <sclog.hpp>
#include <thread>
#include <vector>
#include <iostream>

namespace sc = sclog;

void spread(sc::logger& logger)
{
	for (int i = 0; i < 10; ++i)
	{
		auto id = std::this_thread::get_id();
		std::cout << id << std::endl;
		logger.debug("This is a DEBUG message");
		logger.info("This is a INFO message");
		logger.warning("This is a WARNING message");
		logger.error("This is a ERROR message");
	}
}

int main(int argc, const char** argv)
{
	sc::logger logger(sc::level::debug);
	logger.add_handler("history.log", sc::level::info);

	std::vector<std::thread> threads;
	for (int i = 0; i < 8; ++i)
		threads.push_back(std::thread(spread, std::ref(logger)));

	for (auto& thread : threads)
		thread.join();

	return 0;
}
