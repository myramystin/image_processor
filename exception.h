#pragma once
#include <exception>
#include <string>

namespace input_exceptions {
class EmptyInput : public std::exception {
    virtual const char* what() const noexcept override;
};

class NotEnoughPositionalArguments : public std::exception {
public:
    virtual const char* what() const noexcept override;
};
class InvalidPositionalArgument : public std::exception {
    virtual const char* what() const noexcept override;
};

class NotEnoughFilterOptions : public std::exception {
public:
    virtual const char* what() const noexcept override;
};
class InvalidFilterOption : public std::exception {
    virtual const char* what() const noexcept override;
};
class InvalidFilterName : public std::exception {
    virtual const char* what() const noexcept override;
};
}  // namespace input_exceptions

namespace image_file_exceptions {
class InvalidInputFilename : public std::exception {
    virtual const char* what() const noexcept override;
};
class InvalidOutputFilename : public std::exception {
    virtual const char* what() const noexcept override;
};
}  // namespace image_file_exceptions
