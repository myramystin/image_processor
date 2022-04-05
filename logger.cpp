#include "logger.h"
#include <iostream>

Logger &Logger::Instance() {
    static Logger logger;
    return logger;
}

void Logger::LogError(const std::string &text) {
    std::cout << text << std::endl;
}

void Logger::LogInfo(const std::string &text) {
    std::cout << text << std::endl;
}
