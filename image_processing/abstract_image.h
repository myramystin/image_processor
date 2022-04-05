#pragma once
#include <string>
#include <vector>

struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

class AbstractImage {
public:
    virtual void Save(const std::string& output_filename) = 0;
    virtual ~AbstractImage() = default;

    virtual std::vector<std::vector<Pixel>> GetData() const = 0;
    virtual void SetData(const std::vector<std::vector<Pixel>>& data) = 0;
    virtual void SetSizes(size_t width, size_t height) = 0;
    virtual void SetPixel(size_t i, size_t j, const Pixel& pixel) = 0;

    virtual size_t GetWidth() const = 0;
    virtual size_t GetHeight() const = 0;
    virtual Pixel GetPixel(size_t i, size_t j) const = 0;
    virtual std::string GetInputFile() const = 0;

};

AbstractImage* CreateImage(const std::string& input_filename);

