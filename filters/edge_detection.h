#pragma once
#include "filter_factory.h"
#include "matrix_filter.h"

class EdgeDetectionFilter : public MatrixFilter {
public:
    EdgeDetectionFilter(size_t threshold);

    virtual void Apply(ImageHolder* image) override;

private:
    size_t threshold_;
};

std::unique_ptr<EdgeDetectionFilter> CreateEdgeDetectionFilter(size_t threshold);

