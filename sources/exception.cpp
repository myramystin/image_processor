#include "exception.h"

const char *input_exceptions::NotEnoughPositionalArguments::what() const noexcept {
    return "not enough position arguments";
}

const char *input_exceptions::NotEnoughFilterOptions::what() const noexcept {
    return "not enough filter options";
}

const char *input_exceptions::InvalidFilterOption::what() const noexcept {
    return "invalid filter option";
}

const char *image_file_exceptions::InvalidInputFilename::what() const noexcept {
    return "invalid input file name";
}

const char *image_file_exceptions::InvalidOutputFilename::what() const noexcept {
    return "invalid output file name";
}

const char *input_exceptions::InvalidPositionalArgument::what() const noexcept {
    return "invalid positional argument";
}

const char *input_exceptions::InvalidFilterName::what() const noexcept {
    return "invalid filter name";
}

const char *input_exceptions::EmptyInput::what() const noexcept {
    return "input is empty";
}
