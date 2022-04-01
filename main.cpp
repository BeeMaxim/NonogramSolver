#include <fstream>
#include <string>
#include <vector>

#include "BMPWriter.h"

Nonogram ReadFromFile(const std::string &path) {
    std::ifstream fin(path, std::ios::in);
    int height, width, border_height, border_width;
    fin >> height >> width >> border_height >> border_width;

    std::vector<std::vector<int>> rows(height, std::vector<int>(0));
    std::vector<std::vector<int>> cols(width, std::vector<int>(0));

    std::string paddings;
    getline(fin, paddings);
    getline(fin, paddings);
    for (size_t i = 0; i < border_height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            std::string potential_number;
            getline(fin, potential_number);
            int number = 0;
            try {
                number = stoi(potential_number);
            } catch (const std::invalid_argument &) {}
            if (number > 0) {
                cols[j].push_back(number);
            }
        }
    }
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < border_width; ++j) {
            std::string potential_number;
            getline(fin, potential_number);
            int number = 0;
            try {
                number = stoi(potential_number);
            } catch (const std::invalid_argument &) {}
            if (number > 0) {
                rows[i].push_back(number);
            }
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
