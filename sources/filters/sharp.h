#pragma once
#include "filter_factory.h"
#include "matrix_filter.h"

class SharpFilter : public MatrixFilter {
public:
    SharpFilter();

    virtual void Apply(ImageHolder* image) override;
};

std::unique_ptr<SharpFilter> CreateSharpFilter();
