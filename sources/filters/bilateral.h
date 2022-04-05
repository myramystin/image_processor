#pragma once
#include "gauss_blur.h"

class BilateralFilter : public GaussianFilter {
public:
    BilateralFilter(float diameter, float sigma_distance, float sigma_color);

    virtual void Apply(ImageHolder* image) override;
    void ApplyOneDimensionBlur(std::vector<std::vector<Pixel>>& change, const std::vector<float>& exp_distance,
                               const std::vector<float>& exp_color, size_t height, size_t width, bool x_is_const);

private:
    float diameter_;
    float sigma_distance_;
    float sigma_color_;
};

std::unique_ptr<BilateralFilter> CreateBilateralFilter(float diameter, float sigma_distance, float sigma_color);
