#pragma once
#include "additional.h"

class Parser {
public:
    Parser() = default;

    void AddPositionalArg(const std::string& arg_name, const std::string& description, Argument output);
    void AddKeywordArg(const std::string& keyword, const std::string& description, const std::vector<NameToArg> arg = {});

    void Parse(size_t argc, char** argv, std::vector<std::string>& queue);

    std::string GetArgsDescription(bool positional);

private:
    StrToStrRefs positional_args_;
    StringToNamedArgs keyword_fields_;
    std::unordered_map<std::string, std::string> positional_args_to_description_;
    std::unordered_map<std:: string, std::string> keyword_args_to_description_;
private:
    std::string ParseMap(const std::unordered_map<std::string, std::string>& dictionary);
};
