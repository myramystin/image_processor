
#include "sharp.h"

void SharpFilter::Apply(ImageHolder *image) {
    MatrixFilter::Apply(image);
}

SharpFilter::SharpFilter() : MatrixFilter({{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}){

}

std::unique_ptr<SharpFilter> CreateSharpFilter() {
    return std::unique_ptr<SharpFilter>(new SharpFilter());
}
