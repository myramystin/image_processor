#pragma once
#include "additional.h"
#include <memory>
#include "image_processing/image_holder.h"
#include "basicfilter.h"


using NamedFunctionPtrs = std::unordered_map<std::string_view, std::function<std::unique_ptr<BasicFilter>()>>;

class FilterFactory {
public:
    void Register(std::string_view name, std::function<std::unique_ptr<BasicFilter>()> creator);
    std::unique_ptr<BasicFilter> Create(std::string_view name);

private:
    NamedFunctionPtrs named_funcs_;
};

