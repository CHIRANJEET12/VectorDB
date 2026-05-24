#pragma once
#include <vector>
#include <string>

struct Document {
    int id;
    std::string text;
    std::vector<float> embedding;
};