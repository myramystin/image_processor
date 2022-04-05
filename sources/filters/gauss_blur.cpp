#include "gauss_blur.h"
#include "exception.h"
#include <cmath>
#include <algorithm>

GaussianFilter::GaussianFilter(float sigma) : sigma_(sigma) {
    if (sigma_ < ACCURACY) {
        throw input_exceptions::InvalidFilterOption();
    }
}

void GaussianFilter::ApplyOneDimensionBlur(std::vector<std::vector<Pixel>>& change,
                                           const std::vector<float>& exp, size_t height, size_t width,
                                           bool x_is_const) {
    size_t one_dim_coord;
    if (x_is_const) {
        one_dim_coord = height;
    } else {
        one_dim_coord = width;
    }
    std::vector<std::vector<Pixel>> data(height);
    for (size_t i = 0; i < height; ++i) {
        data[i].resize(width);
        for (size_t j = 0; j < width; ++j) {
            float red = 0;
            float green = 0;
            float blue = 0;
            for (size_t coord = 0; coord < one_dim_coord; ++coord) {
                if (x_is_const) {
                    red += change[coord][j].red * exp[std::max(i, coord) - std::min(i, coord)];
                    green += change[coord][j].green * exp[std::max(i, coord) - std::min(i, coord)];
                    blue += change[coord][j].blue * exp[std::max(i, coord) - std::min(i, coord)];
                } else {
                    red += change[i][coord].red * exp[std::max(j, coord) - std::min(j, coord)];
                    green += change[i][coord].green * exp[std::max(j, coord) - std::min(j, coord)];
                    blue += change[i][coord].blue * exp[std::max(j, coord) - std::min(j, coord)];
                }
                if (red >= COLOR_MAX || green >= COLOR_MAX || blue >= COLOR_MAX) {
                    red = std::min(red, static_cast<float>(COLOR_MAX));
                    green = std::min(green, static_cast<float>(COLOR_MAX));
                    blue = std::min(blue, static_cast<float>(COLOR_MAX));
                    break;
                }
            }
            data[i][j] = {static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue)};
        }
    }
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            change[i][j] = data[i][j];
        }
    }
}

void GaussianFilter::Apply(ImageHolder* image) {
    size_t width = image->GetWidth();
    size_t height = image->GetHeight();
    size_t max_dimension = std::max(width, height);
    std::vector<float> exponent_pows(max_dimension);
    FillExponentArray(max_dimension, exponent_pows, sigma_);
    auto new_data = image->GetImageData();
    ApplyOneDimensionBlur(new_data, exponent_pows, height, width, false);
    ApplyOneDimensionBlur(new_data, exponent_pows, height, width, true);
    image->SetImageData(new_data);
}

void GaussianFilter::FillExponentArray(size_t size, std::vector<float>& container, float sigma) {
    float power_component = -2 * std::pow(sigma, 2);
    float coefficient = std::sqrt(2 * M_PI * std::pow(sigma, 2));
    for (size_t i = 0; i < size; ++i) {
        container[i] = std::pow(M_E, (std::pow(i, 2)) / power_component) / coefficient;
    }
}

std::unique_ptr<GaussianFilter> CreateGaussianFilter(float sigma) {
    return std::unique_ptr<GaussianFilter>(new GaussianFilter(sigma));
}
