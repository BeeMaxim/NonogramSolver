#include <fstream>

#include "BMPWriter.h"
#include "Nonogram.h"

const unsigned char BLACK_CELL = static_cast<unsigned char>(0);
const unsigned char WHITE_CELL = static_cast<unsigned char>(255);

void WriteByteToHeader(std::vector<unsigned char> &header, size_t index, int value) {
    header[index] = static_cast<unsigned char>(value);
}

void WriteIntToHeader(std::vector<unsigned char> &header, size_t index, int value) {
    for (size_t i = index; i < index + 4; ++i) {
        header[i] = static_cast<unsigned char>(value);
        value /= 256;
    }
}

void UpdateHeader(const Nonogram &nonogram, std::vector<unsigned char> &header) {
    size_t width = nonogram.width_;
    size_t height = nonogram.height_;
    WriteIntToHeader(header, 18, static_cast<int>(width));
    WriteIntToHeader(header, 22, static_cast<int>(height));
    size_t bitmap_size = ((3 * width + 3) / 4) * 4 * height;
    WriteIntToHeader(header, 34, static_cast<int>(bitmap_size));
    WriteIntToHeader(header, 2, static_cast<int>(bitmap_size) + 54);
}

void Write(const std::string &path, const Nonogram &nonogram) {
    std::ofstream out_stream;
    out_stream.open(path, std::ios_base::binary | std::ofstream::trunc);
    std::vector<unsigned char> header(54, BLACK_CELL);

    WriteByteToHeader(header, 0, 66);
    WriteByteToHeader(header, 1, 77);
    WriteIntToHeader(header, 10, 54);
    WriteIntToHeader(header, 14, 40);
    WriteByteToHeader(header, 26, 1);
    WriteByteToHeader(header, 28, 24);
    WriteIntToHeader(header, 38, 2835);
    WriteIntToHeader(header, 42, 2835);

    UpdateHeader(nonogram, header);

    for (size_t i = 0; i < 54; ++i) {
        out_stream << header[i];
    }

    size_t paddings = (4 - (3 * nonogram.width_) % 4) % 4;

    for (size_t i = 0; i < nonogram.height_; ++i) {
        for (size_t j = 0; j < nonogram.width_; ++j) {
            unsigned char cell = nonogram.matrix_[nonogram.height_ - i - 1][j] == 1 ? BLACK_CELL : WHITE_CELL;
            out_stream << cell << cell << cell;
            if (nonogram.width_ - j == 1) {
                unsigned char padding = 0;
                for (size_t u = 0; u < paddings; ++u) {
                    out_stream << padding;
                }
            }
        }
    }
}
