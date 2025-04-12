#include "Logger.hpp"

namespace sc = sclog;

int main(int argc, const char** argv)
{
    sc::Logger logger(sc::Level::Trace);

    logger.trace("trace message");
    logger.debug("debug message");
    logger.info("info message");
    logger.warning("warning message");
    logger.error("error message");

    return 0;
}
