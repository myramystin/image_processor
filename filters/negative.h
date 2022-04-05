#pragma once
#include "filter_factory.h"

class NegativeFilter : public BasicFilter {
public:
    NegativeFilter() = default;

    virtual void Apply(ImageHolder* image) override;

};

std::unique_ptr<NegativeFilter> CreateNegativeFilter();
