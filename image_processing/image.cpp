#include "image.h"
#include "../exception.h"

static const size_t BYTES_BEFORE_WIDTH = 18;
static const size_t BYTES_AFTER_HEIGHT = 28;

void BmpImage::Save(const std::string &output_filename) {
    std::ofstream output(output_filename, std::ios::binary);
    if (!output) {
        throw image_file_exceptions::InvalidOutputFilename();
    }
    for (size_t i = 0; i < BYTES_BEFORE_WIDTH; ++i) {
        WriteByte(output, header_bytes_[i]);
    }

    WriteSizeT(output, width_);
    WriteSizeT(output, height_);
    for (size_t i = BYTES_BEFORE_WIDTH; i < BYTES_BEFORE_WIDTH + BYTES_AFTER_HEIGHT; ++i) {
        WriteByte(output, header_bytes_[i]);
    }
    for (size_t y = height_; y > 0; --y) {
        for (size_t x = 0; x < width_; ++x) {
            WriteByte(output, color_bytes_[y - 1][x].blue);
            WriteByte(output, color_bytes_[y - 1][x].green);
            WriteByte(output, color_bytes_[y - 1][x].red);
        }
        for (size_t i = 0; i < padding_; ++i) {
            WriteByte(output, 0);
        }
    }
    output.close();
}

BmpImage::BmpImage(const std::string &input_filename) : input_file_(input_filename) {
    std::ifstream input(input_filename, std::ios::binary);
    if (!input) {
        throw image_file_exceptions::InvalidInputFilename();
    }
    //  save header
    for (size_t i = 0; i < BYTES_BEFORE_WIDTH; ++i) {
        header_bytes_.push_back(ReadByte(input));
    }
    SaveSizeT(input, width_);
    SaveSizeT(input, height_);
    for (size_t i = 0; i < BYTES_AFTER_HEIGHT; ++i) {
        header_bytes_.push_back(ReadByte(input));
    }
    // padding
    for (padding_ = 0; padding_ < 4; ++padding_) {
        if ((width_ * 3 + padding_) % 4 == 0) {
            break;
        }
    }
    // colors
    color_bytes_.reserve(height_);
    for (size_t i = height_; i > 0; --i) {
        std::vector<Pixel> line(width_);
        for (size_t j = 0; j < width_; ++j) {
            line[j].blue = ReadByte(input);
            line[j].green = ReadByte(input);
            line[j].red = ReadByte(input);
        }
        color_bytes_.push_back(line);
        // extra
        input.ignore(padding_);
    }
    std::reverse(color_bytes_.begin(), color_bytes_.end());
    input.close();
}

uint8_t BmpImage::ReadByte(std::ifstream &input) {
    uint8_t byte;
    input.read(reinterpret_cast<char *>(&byte), 1);
    return byte;
}

void BmpImage::SaveSizeT(std::ifstream &input, size_t &value) {
    int start_move = 8;
    for (size_t i = 0; i < 4; ++i) {
        auto byte = ReadByte(input);
        value += byte << start_move * i;
    }
}

void BmpImage::WriteByte(std::ofstream &output, uint8_t byte) {
    output.write(reinterpret_cast<char *>(&byte), 1);
}

void BmpImage::WriteSizeT(std::ofstream &output, size_t &value) {
    int start_move = 8;
    for (size_t i = 0; i < 4; ++i) {
        WriteByte(output, value >> start_move * i);
    }
}

BmpImage::BmpImage(const BmpImage &other) :color_bytes_(other.color_bytes_), header_bytes_(other.header_bytes_), width_(other.width_), height_(other.height_), padding_(other.padding_){
}

std::vector<std::vector<Pixel>> BmpImage::GetData() const {
    return color_bytes_;
}

void BmpImage::SetData(const std::vector<std::vector<Pixel>>& data) {
    color_bytes_ = data;
}

void BmpImage::SetSizes(size_t width, size_t height) {
    height_ = height;
    width_ = width;
    color_bytes_.resize(height);
    for (auto& line:color_bytes_) {
        line.resize(width);
    }
}

void BmpImage::SetPixel(size_t i, size_t j, const Pixel &pixel) {
    color_bytes_[i][j] = pixel;
}

size_t BmpImage::GetWidth() const {
    if (color_bytes_.empty()) {
        return 0;
    }
    return color_bytes_[0].size();
}

size_t BmpImage::GetHeight() const {
    return color_bytes_[0].size();
}

Pixel BmpImage::GetPixel(size_t i, size_t j) const {
    return color_bytes_[i][j];
}

std::string BmpImage::GetInputFile() const {
    return input_file_;
}





