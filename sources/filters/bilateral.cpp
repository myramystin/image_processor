#include "bilateral.h"

BilateralFilter::BilateralFilter(float diameter, float sigma_distance, float sigma_color)
    : diameter_(diameter), sigma_distance_(sigma_distance), sigma_color_(sigma_color) {
    if ((-1 * ACCURACY < diameter_ && diameter_ < ACCURACY) ||
        (-1 * ACCURACY < sigma_distance_ && sigma_distance_ < ACCURACY) ||
        (-1 * ACCURACY < sigma_color_ && sigma_color_ < ACCURACY)) {
        throw input_exceptions::InvalidFilterOption();
    }
}

void BilateralFilter::Apply(ImageHolder* image) {
    size_t height = image->GetHeight();
    size_t width = image->GetWidth();
    size_t max_dimension = std::max(height, width);
    std::vector<float> exp_distance(max_dimension);
    GaussianFilter::FillExponentArray(max_dimension, exp_distance, sigma_distance_);
    std::vector<float> exp_color(COLOR_MAX * 3 + 1);
    GaussianFilter::FillExponentArray(COLOR_MAX * 3 + 1, exp_color, sigma_color_);
    auto new_data = image->GetImageData();
    ApplyOneDimensionBlur(new_data, exp_distance, exp_color, height, width, false);
    ApplyOneDimensionBlur(new_data, exp_distance, exp_color, height, width, true);
    image->SetImageData(new_data);
}

void FillCycleBoundaries(size_t& start, size_t& end, size_t max, size_t radius, size_t current) {
    if (current > radius) {
        start = current - radius;
    } else {
        start = 0;
    }
    if (current + radius > max) {
        end = max;
    } else {
        end = current + radius;
    }
}

void BilateralFilter::ApplyOneDimensionBlur(std::vector<std::vector<Pixel>>& change,
                                            const std::vector<float>& exp_distance, const std::vector<float>& exp_color,
                                            size_t height, size_t width, bool x_is_const) {
    size_t radius = diameter_ / 2;
    std::vector<std::vector<Pixel>> data(height);
    for (size_t i = 0; i < height; ++i) {
        data[i].resize(width);
        for (size_t j = 0; j < width; ++j) {
            float red = 0;
            float green = 0;
            float blue = 0;
            float normalization_term = 0;
            size_t start;
            size_t end;
            size_t intensity = (change[i][j].red + change[i][j].green + change[i][j].blue);
            if (x_is_const) {
                FillCycleBoundaries(start, end, height, radius, i);
            } else {
                FillCycleBoundaries(start, end, width, radius, j);
            }
            for (size_t coord = start; coord < end; ++coord) {
                float gaussian_combination;
                float gaussian_dist;

                size_t new_red;
                size_t new_blue;
                size_t new_green;
                if (x_is_const) {
                    gaussian_dist = exp_distance[std::max(i, coord) - std::min(i, coord)];
                    new_red = change[coord][j].red;
                    new_green = change[coord][j].green;
                    new_blue = change[coord][j].blue;
                } else {
                    gaussian_dist = exp_distance[std::max(j, coord) - std::min(j, coord)];
                    new_red = change[i][coord].red;
                    new_green = change[i][coord].green;
                    new_blue = change[i][coord].blue;
                }
                size_t new_intensity = new_red + new_green + new_blue;
                float gaussian_intensity =
                    exp_color[std::max(intensity, new_intensity) - std::min(intensity, new_intensity)];
                gaussian_combination = gaussian_dist * gaussian_intensity;
                red += new_red * gaussian_combination;
                green += new_green * gaussian_combination;
                blue += new_blue * gaussian_combination;
                normalization_term += gaussian_combination;
            }
            if (normalization_term > ACCURACY) {
                red /= normalization_term;
                green /= normalization_term;
                blue /= normalization_term;
            }
            uint8_t set_red = std::min(static_cast<uint8_t>(red), COLOR_MAX);
            uint8_t set_green = std::min(static_cast<uint8_t>(green), COLOR_MAX);
            uint8_t set_blue = std::min(static_cast<uint8_t>(blue), COLOR_MAX);
            data[i][j] = {set_red, set_green, set_blue};
        }
    }
    change = data;
}

std::unique_ptr<BilateralFilter> CreateBilateralFilter(float diameter, float sigma_distance, float sigma_color) {
    return std::unique_ptr<BilateralFilter>(new BilateralFilter(diameter, sigma_distance, sigma_color));
}
