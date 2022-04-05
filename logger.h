#pragma once
#include "additional.h"

class Logger {
public:
    static Logger& Instance();
    void LogError(const std::string& text);
    void LogInfo(const std::string& text);

private:
    Logger() = default;
};
