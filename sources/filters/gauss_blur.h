#pragma once
#include "filter_factory.h"

class GaussianFilter : public BasicFilter {
public:
    GaussianFilter(float sigma = 1);

    virtual void Apply(ImageHolder* image) override;
    void FillExponentArray(size_t size, std::vector<float>& container, float sigma);

private:
    float sigma_;

    void ApplyOneDimensionBlur(std::vector<std::vector<Pixel>>& change, const std::vector<float>& exp,
                               size_t height, size_t width, bool x_is_const);
};

std::unique_ptr<GaussianFilter> CreateGaussianFilter(float sigma);

