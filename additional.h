#pragma once
#include <variant>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include "exception.h"

const float ACCURACY = 0.000000001;
const uint8_t COLOR_MAX = 255;

using Argument = std::variant<std::string*, float*, size_t*>;
using NameToArg = std::pair<std::string, Argument>;
using StrToStrRefs = std::vector<NameToArg>;
using StringToNamedArgs = std::unordered_map<std::string, std::vector<NameToArg>>;

struct ArgumentCast {
    ArgumentCast(const char* data);

    void operator()(std::string* s);
    void operator()(size_t* s);
    void operator()(float* s);

private:
    const char* data_;
};
