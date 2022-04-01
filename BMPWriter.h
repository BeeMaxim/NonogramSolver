#pragma once

#include <string>
#include <vector>

#include "Nonogram.h"

void WriteByteToHeader(std::vector<unsigned char> &header, size_t index, int value);

void WriteIntToHeader(std::vector<unsigned char> &header, size_t index, int value);

void UpdateHeader(Nonogram &nonogram, std::vector<unsigned char> &header);

void Write(const std::string &path, const Nonogram &nonogram);