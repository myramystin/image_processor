#include <string>
#include <string_view>
#include <vector>
#include <fstream>
#include "abstract_image.h"

class BmpImage : public AbstractImage{
public:
    BmpImage(const std::string& input_filename);
    BmpImage(const BmpImage& other);
    virtual void Save(const std::string& output_filename) override;

    virtual std::vector<std::vector<Pixel>> GetData() const override;
    virtual void SetData(const std::vector<std::vector<Pixel>>& data) override;
    virtual void SetSizes(size_t width, size_t height) override;
    virtual void SetPixel(size_t i, size_t j, const Pixel& pixel) override;

    virtual size_t GetWidth() const override;
    virtual size_t GetHeight() const override;
    virtual Pixel GetPixel(size_t i, size_t j) const override;

    virtual std::string GetInputFile() const override;


private:
    uint8_t ReadByte(std::ifstream& input);
    void WriteByte(std::ofstream& output, uint8_t byte);
    void SaveSizeT(std::ifstream& input, size_t& value);
    void WriteSizeT(std::ofstream& output, size_t& value);

private:
    std::vector<std::vector<Pixel>> color_bytes_;
    std::vector<uint8_t> header_bytes_;
    size_t width_ = 0u;
    size_t height_ = 0u;
    size_t padding_ = 0u;
    std::string input_file_;
};