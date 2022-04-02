#include <fstream>
#include <string>
#include <vector>

#include "BMPWriter.h"

Nonogram ReadFromFile(const std::string &path) {
    std::ifstream fin(path, std::ios::in);
    size_t height = 0, width = 0;
    fin >> height >> width;

    std::vector<std::vector<int>> rows(height, std::vector<int>(0));
    std::vector<std::vector<int>> cols(width, std::vector<int>(0));

    for (size_t i = 0; i < width; ++i) {
        size_t string_len = 0;
        fin >> string_len;
        for (size_t j = 0; j < string_len; ++j) {
            int number;
            fin >> number;
            cols[i].push_back(number);
        }
    }

    for (size_t i = 0; i < height; ++i) {
        size_t string_len = 0;
        fin >> string_len;
        for (size_t j = 0; j < string_len; ++j) {
            int number;
            fin >> number;
            rows[i].push_back(number);
        }
    }

    return {Nonogram(std::move(rows), std::move(cols), width, height)};
}

int main(int argc, char *argv[]) {
    std::string input_path;
    std::string output_path;
    if (argc > 1) {
        input_path = argv[1];
        output_path = argv[2];

        Nonogram nonogram = ReadFromFile(input_path);
        nonogram.Solve();
        nonogram.Increase(8);
        Write(output_path, nonogram);
    }

    return 0;
}
