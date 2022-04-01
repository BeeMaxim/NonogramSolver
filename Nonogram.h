#pragma once

#include <vector>

class Nonogram {
public:
    Nonogram(std::vector<std::vector<int>> &&rows, std::vector<std::vector<int>> &&cols, size_t width, size_t height);

    void Solve();

    void Increase(size_t coefficient);

    std::vector<std::vector<int>> matrix_;
    std::vector<std::vector<int>> rows_;
    std::vector<std::vector<int>> cols_;
    size_t width_ = 0;
    size_t height_ = 0;
private:
    static bool CanMakeCorrect(std::vector<int> &correct, std::vector<int> &current);

    void TryPaintCell(size_t i, size_t j);

    bool DoOneIteration();

    [[nodiscard]] std::vector<int> GetColumn(size_t i) const;

    [[nodiscard]] std::vector<int> GetRow(size_t i) const;
};
