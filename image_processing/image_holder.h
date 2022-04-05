#pragma once
#include "image.h"
#include "additional.h"

class ImageHolder {
public:
    ImageHolder(AbstractImage* image, const std::string& output);
    ImageHolder(const ImageHolder& rhs);

    ImageHolder operator=(const ImageHolder& rhs);
    ~ImageHolder();

    void SetImageData(std::vector<std::vector<Pixel>> data);
    std::vector<std::vector<Pixel>> GetImageData() const;
    size_t GetWidth() const;
    size_t GetHeight() const;
    Pixel GetPixel(size_t i, size_t j) const;

    void SetImageSizes(size_t width, size_t height);
    void SetPixel(size_t i, size_t j, const Pixel& pixel);


private:
    void DecreaseRefCnt();

private:
    std::string output_filename_;
    AbstractImage* image_;
    size_t* ref_counter_ = nullptr;
};
