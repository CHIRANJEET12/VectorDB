// distace metric init header file

#pragma once
#include <vector>
using namespace std;

enum class Metric{
    EUCLIDEAN,
    MANHATTAN,
    COSINE
};

//euclidean
float euclidean(const vector<float>& a, const vector<float>& b);
//manhattan
float manhattan(const vector<float>& a, const vector<float>& b);
//cosine-sim
float cosine(const vector<float>& a, const vector<float>& b);


float computeDistanceBasedonMetrics(const vector<float>& a, vector<float>& b, Metric metric);
