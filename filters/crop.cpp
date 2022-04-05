#include "crop.h"

CropFilter::CropFilter(size_t width, size_t height) : width_(width), height_(height) {
}

void CropFilter::Apply(ImageHolder *image) {
    image->SetImageSizes(std::min(width_, image->GetWidth()), std::min(height_, image->GetHeight()));
}

std::unique_ptr<CropFilter> CreateCropFilter(size_t width, size_t height) {
    return std::unique_ptr<CropFilter>(new CropFilter(width, height));
}
