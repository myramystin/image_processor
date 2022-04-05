#pragma once
#include "filter_factory.h"

class GrayScaleFilter : public BasicFilter {
public:
    GrayScaleFilter() = default;
    virtual void Apply(ImageHolder* image) override;

private:
    constexpr static const float RedCoefficient = 0.299;
    constexpr static const float GreenCoefficient = 0.578;
    constexpr static const float BlueCoefficient = 0.114;
};

std::unique_ptr<GrayScaleFilter> CreateGrayScaleFilter();

