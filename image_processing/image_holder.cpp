#include "image_holder.h"

ImageHolder::ImageHolder(AbstractImage* image, const std::string &output) {
    image_ = image;
    output_filename_ = output;
    ref_counter_ = new size_t(1u);
}

ImageHolder::ImageHolder(const ImageHolder &rhs)
    : output_filename_(rhs.output_filename_), image_(rhs.image_), ref_counter_(rhs.ref_counter_) {
    ++(*ref_counter_);
}

ImageHolder ImageHolder::operator=(const ImageHolder &rhs) {
    DecreaseRefCnt();
    ref_counter_ = rhs.ref_counter_;
    ++(*ref_counter_);
    image_ = rhs.image_;
    output_filename_ = rhs.output_filename_;
    return *this;
}

void ImageHolder::DecreaseRefCnt() {
    if (*ref_counter_ > 1u) {
        --(*ref_counter_);
    } else {
        image_->Save(output_filename_);
        delete ref_counter_;
        delete image_;
    }
}

ImageHolder::~ImageHolder() {
    DecreaseRefCnt();
}

void ImageHolder::SetImageData(std::vector<std::vector<Pixel>> data) {
    if (*ref_counter_ == 1u) {
        image_->SetData(data);
    } else {
        DecreaseRefCnt();
        delete ref_counter_;
        image_ = CreateImage(image_->GetInputFile());

        try {
            ref_counter_ = new size_t(1u);
            image_->SetData(data);
        } catch (...) {
            delete image_;
        }
    }
}

std::vector<std::vector<Pixel>> ImageHolder::GetImageData() const {
    return image_->GetData();
}

size_t ImageHolder::GetWidth() const {
    return image_->GetWidth();
}

size_t ImageHolder::GetHeight() const {
    return image_->GetHeight();
}

Pixel ImageHolder::GetPixel(size_t i, size_t j) const {
    return image_->GetPixel(i, j);
}

void ImageHolder::SetImageSizes(size_t width, size_t height) {
    if (*ref_counter_ == 1u) {
        image_->SetSizes(width, height);
    } else {
        DecreaseRefCnt();
        delete ref_counter_;
        image_ = CreateImage(image_->GetInputFile());

        try {
            ref_counter_ = new size_t(1u);
            image_->SetSizes(width, height);
        } catch (...) {
            delete image_;
        }
    }
}

void ImageHolder::SetPixel(size_t i, size_t j, const Pixel &pixel) {
    if (*ref_counter_ == 1u) {
        image_->SetPixel(i, j, pixel);
    } else {
        DecreaseRefCnt();
        delete ref_counter_;
        image_ = CreateImage(image_->GetInputFile());
        try {
            ref_counter_ = new size_t(1u);
            image_->SetPixel(i, j, pixel);
        } catch (...) {
            delete image_;
        }
    }
}


