#include "additional.h"

ArgumentCast::ArgumentCast(const char* data) : data_(data) {
}

void ArgumentCast::operator()(std::string* s) {
    *s = std::string(data_);
}

void ArgumentCast::operator()(size_t* s) {
    *s = std::stoul(data_);
}

void ArgumentCast::operator()(float* s) {
    *s = std::stof(data_);
}
