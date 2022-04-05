#include "filter_factory.h"
#include <algorithm>
#include "matrix_filter.h"

void FilterFactory::Register(std::string_view name, std::function<std::unique_ptr<BasicFilter>()> creator) {
    named_funcs_[name] = creator;
}

std::unique_ptr<BasicFilter> FilterFactory::Create(std::string_view name) {
    return named_funcs_[name]();
}

Pixel MatrixFilter::ApplyMatrix(const std::vector<std::vector<int>>& matrix,
                                       const std::vector<std::vector<Pixel>>& pixels) {
    int new_red = 0;
    int new_blue = 0;
    int new_green = 0;
    Pixel result;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            new_red += matrix[i][j] * pixels[i][j].red;
            new_green += matrix[i][j] * pixels[i][j].green;
            new_blue += matrix[i][j] * pixels[i][j].blue;
        }
    }
    result.red = static_cast<uint8_t>(std::max(0, std::min(static_cast<int>(COLOR_MAX), new_red)));
    result.green = static_cast<uint8_t>(std::max(0, std::min(static_cast<int>(COLOR_MAX), new_green)));
    result.blue = static_cast<uint8_t>(std::max(0, std::min(static_cast<int>(COLOR_MAX), new_blue)));
    return result;
}

void MatrixFilter::FillLine(ImageHolder* image, size_t i, size_t j, std::vector<Pixel>& container) {
    if (j == 0) {
        container.push_back(image->GetPixel(i, j));
    } else {
        container.push_back(image->GetPixel(i, j - 1));
    }
    container.push_back(image->GetPixel(i, j));
    if (j == image->GetWidth() - 1) {
        container.push_back(image->GetPixel(i, j));
    } else {
        container.push_back(image->GetPixel(i, j + 1));
    }
}

void MatrixFilter::FillSquare(ImageHolder* image, size_t i, size_t j,
                              std::vector<std::vector<Pixel>>& container) {
    container.resize(3);
    // 1
    if (i == 0) {
        MatrixFilter::FillLine(image, i, j, container[0]);
    } else {
        MatrixFilter::FillLine(image, i - 1, j, container[0]);
    }
    // 2
    MatrixFilter::FillLine(image, i, j, container[1]);
    // 3
    if (i == image->GetHeight() - 1) {
        MatrixFilter::FillLine(image, i, j, container[2]);
    } else {
        MatrixFilter::FillLine(image, i + 1, j, container[2]);
    }
}

MatrixFilter::MatrixFilter(std::vector<std::vector<int>> matrix) : matrix_(matrix) {
}

void MatrixFilter::Apply(ImageHolder *image) {
    std::vector<std::vector<Pixel>> new_data(image->GetHeight());
    new_data.resize(image->GetHeight());
    for (size_t i = 0; i < image->GetHeight(); ++i) {
        new_data[i].resize(image->GetWidth());
        for (size_t j = 0; j < image->GetWidth(); ++j) {
            std::vector<std::vector<Pixel>> pixels(3);
            MatrixFilter::FillSquare(image, i, j, pixels);
            new_data[i][j] = MatrixFilter::ApplyMatrix(matrix_, pixels);
        }
    }
    image->SetImageData(new_data);
}
