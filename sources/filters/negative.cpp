
#include "negative.h"

void NegativeFilter::Apply(ImageHolder *image) {
    for (size_t i = 0; i < image->GetHeight(); ++i) {
        for (size_t j = 0; j < image->GetWidth(); ++j) {
            auto current_pixel = image->GetPixel(i, j);
            uint8_t new_red = COLOR_MAX - current_pixel.red;
            uint8_t new_green = COLOR_MAX - current_pixel.green;
            uint8_t new_blue = COLOR_MAX - current_pixel.blue;
            image->SetPixel(i, j, {new_red, new_green, new_blue});
        }
    }
}

std::unique_ptr<NegativeFilter> CreateNegativeFilter() {
    return std::unique_ptr<NegativeFilter>(new NegativeFilter());
}

