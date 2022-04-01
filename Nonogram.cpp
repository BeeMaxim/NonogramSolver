#include "Nonogram.h"

Nonogram::Nonogram(std::vector<std::vector<int>> &&rows, std::vector<std::vector<int>> &&cols, size_t width,
                   size_t height) {
    rows_ = rows;
    cols_ = cols;
    width_ = width;
    height_ = height;
}

void Nonogram::Solve() {
    matrix_.assign(height_, std::vector<int>(width_, 0));
    bool done_at_least_one_changing = true;
    while (done_at_least_one_changing) {
        done_at_least_one_changing = DoOneIteration();
    }
}

void Nonogram::Increase(size_t coefficient) {
    height_ *= coefficient;
    width_ *= coefficient;
    std::vector<std::vector<int>> matrix(height_, std::vector<int>(width_, 0));

    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            matrix[i][j] = matrix_[i / coefficient][j / coefficient];
        }
    }
    matrix_ = matrix;
}

bool Nonogram::CanMakeCorrect(std::vector<int> &correct, std::vector<int> &current) {
    std::vector<size_t> black_pref(current.size() + 1, 0);
    std::vector<size_t> white_pref(current.size() + 1, 0);
    std::vector<int> dp(current.size(), 0);
    std::vector<int> last_dp(current.size(), 0);

    for (size_t i = 0; i < current.size(); ++i) {
        black_pref[i + 1] = black_pref[i];
        white_pref[i + 1] = white_pref[i];
        black_pref[i + 1] += current[i] == 1;
        white_pref[i + 1] += current[i] == -1;
    }

    for (size_t j = 0; j < correct.size(); ++j) {
        for (size_t i = 0; i < current.size(); ++i) {
            dp[i] = 0;
            if (i > 0 && current[i] != 1 && dp[i - 1]) {
                dp[i] = 1;
                continue;
            }
            if (j == 0) {
                dp[i] = (i + 1 >= correct[j]) && (white_pref[i + 1] - white_pref[i + 1 - correct[j]] == 0) &&
                        (black_pref[i + 1 - correct[j]] == 0);
            } else {
                dp[i] = (i >= correct[j] + 1) && (white_pref[i + 1] - white_pref[i + 1 - correct[j]] == 0) &&
                        (current[i - correct[j]] != 1) && (last_dp[i - correct[j] - 1]);
            }
        }
        last_dp = dp;
    }
    return dp.back();
}

void Nonogram::TryPaintCell(size_t i, size_t j) {
    std::vector<int> col = GetColumn(j);
    std::vector<int> row = GetRow(i);

    for (int cell_color = -1; cell_color <= 1; cell_color += 2) {
        matrix_[i][j] = row[j] = col[i] = cell_color;
        if (!CanMakeCorrect(rows_[i], row) || !CanMakeCorrect(cols_[j], col)) {
            matrix_[i][j] = -cell_color;
            return;
        }
    }
    matrix_[i][j] = 0;
}

bool Nonogram::DoOneIteration() {
    bool done_at_least_one_changing = false;

    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            if (matrix_[i][j] != 0) {
                continue;
            }
            TryPaintCell(i, j);
            if (matrix_[i][j] != 0) {
                done_at_least_one_changing = true;
            }
        }
    }
    return done_at_least_one_changing;
}

std::vector<int> Nonogram::GetColumn(size_t i) const {
    std::vector<int> result(height_, 0);
    for (size_t j = 0; j < height_; ++j) {
        result[j] = (matrix_[j][i]);
    }
    return result;
}

std::vector<int> Nonogram::GetRow(size_t i) const {
    return matrix_[i];
}
