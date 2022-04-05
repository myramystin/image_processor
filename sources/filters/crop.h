#pragma once
#include "filter_factory.h"

class CropFilter : public BasicFilter {
public:
    CropFilter(size_t width, size_t height);

    virtual void Apply(ImageHolder* image) override;

private:
    size_t width_;
    size_t height_;
};

std::unique_ptr<CropFilter> CreateCropFilter(size_t width, size_t height);

