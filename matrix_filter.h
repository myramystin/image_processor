#pragma once

class MatrixFilter : public BasicFilter {
public:
    MatrixFilter(std::vector<std::vector<int>> matrix);

    void Apply(ImageHolder* image) override;

private:
    Pixel ApplyMatrix(const std::vector<std::vector<int>>& matrix,
                          const std::vector<std::vector<Pixel>>& pixels);
    void FillLine(ImageHolder* image, size_t i, size_t j, std::vector<Pixel>& container);
    void FillSquare(ImageHolder* image, size_t i, size_t j, std::vector<std::vector<Pixel>>& container);
    std::vector<std::vector<int>> matrix_;
};
