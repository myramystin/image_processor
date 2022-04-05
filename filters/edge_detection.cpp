
#include "edge_detection.h"
#include "grayscale.h"

void EdgeDetectionFilter::Apply(ImageHolder *image) {
    GrayScaleFilter g;
    g.Apply(image);
    MatrixFilter::Apply(image);
    for (size_t i = 0; i < image->GetHeight(); ++i) {
        for (size_t j = 0; j < image->GetWidth(); ++j) {
            if (image->GetPixel(i, j).red > threshold_) {
                image->SetPixel(i, j, {COLOR_MAX, COLOR_MAX, COLOR_MAX});
            } else {
                image->SetPixel(i, j, {0, 0, 0});
            }
        }
    }
}

EdgeDetectionFilter::EdgeDetectionFilter(size_t threshold) : MatrixFilter({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}), threshold_(threshold) {
}

std::unique_ptr<EdgeDetectionFilter> CreateEdgeDetectionFilter(size_t threshold) {
    return std::unique_ptr<EdgeDetectionFilter>(new EdgeDetectionFilter(threshold));
}

