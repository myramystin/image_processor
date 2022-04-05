
#include "grayscale.h"

void GrayScaleFilter::Apply(ImageHolder* image) {
    for (size_t i = 0; i < image->GetHeight(); ++i) {
        for (size_t j = 0; j < image->GetWidth(); ++j) {
            auto current_pixel = image->GetPixel(i, j);
            float new_red = RedCoefficient * current_pixel.red;
            float new_green = GreenCoefficient * current_pixel.green;
            float new_blue = BlueCoefficient * current_pixel.blue;
            uint8_t value = std::min(static_cast<uint8_t>(new_red + new_green + new_blue), COLOR_MAX);
            image->SetPixel(i, j, {value, value, value});
        }
    }
}

std::unique_ptr<GrayScaleFilter> CreateGrayScaleFilter() {
    return std::unique_ptr<GrayScaleFilter>(new GrayScaleFilter());
}

