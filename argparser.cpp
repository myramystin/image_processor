#include "argparser.h"

void Parser::AddPositionalArg(const std::string& arg_name, const std::string& description, Argument output) {
    positional_args_.push_back(std::make_pair(arg_name, output));
    positional_args_to_description_[arg_name] = description;
}

void Parser::AddKeywordArg(const std::string& keyword, const std::string& description, const std::vector<NameToArg> arg) {
    keyword_fields_[keyword] = arg;
    keyword_args_to_description_[keyword] = description;
}


void Parser::Parse(size_t argc, char** argv, std::vector<std::string>& queue) {
    if (argc == 1) {
        throw input_exceptions::EmptyInput();
    }
    size_t real_positional_count = 0;
    for (size_t i = 0; i < positional_args_.size(); ++i) {
        try {
            ++real_positional_count;
            ArgumentCast assign(argv[i + 1]);
            std::visit(assign, positional_args_[i].second);
        } catch (...) {
            throw input_exceptions::InvalidPositionalArgument();
        }
    }
    if (real_positional_count < positional_args_.size()) {
        throw input_exceptions::NotEnoughPositionalArguments();
    }
    for (size_t i = positional_args_.size() + 1; i < argc; ++i) {
        auto it = keyword_fields_.find(argv[i]);
        if (it == keyword_fields_.end()) {
            throw input_exceptions::InvalidFilterName();
        }
        auto in_queue = std::find(queue.begin(), queue.end(), it->first);
        if (in_queue != queue.end()) {
            queue.erase(in_queue);
        }
        queue.push_back(it->first);
        auto param_required = it->second.size();
        if (i + param_required > argc - 1) {
            throw input_exceptions::NotEnoughFilterOptions();
        }
        for (size_t j = 1; j <= param_required; ++j) {
            if (i + j < argc && argv[i + j][0] == '-') {
                throw input_exceptions::NotEnoughFilterOptions();
            }
            try {
                ArgumentCast assign(argv[i + j]);
                std::visit(assign, it->second[j - 1].second);
            } catch (...) {
                throw input_exceptions::InvalidFilterOption();
            }
        }
        i += param_required;
    }
}

std::string Parser::GetArgsDescription(bool positional) {
    if (positional) {
        return ParseMap(positional_args_to_description_);
    }
    return ParseMap(keyword_args_to_description_);
}

std::string Parser::ParseMap(const std::unordered_map<std::string, std::string> &dictionary) {
    std::string result;
    for (const auto&[name, description]: dictionary) {
        result += "*" + name + " --- " + description + "\n";
    }
    return result;
}
