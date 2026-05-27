
#pragma once
#include <vector>
#include "distance.h"
using namespace std;

struct VectorItem {
    int id;
    vector<float> vec;
};

class BruteForceIndex {
    public:
        void add(const VectorItem& item);
        vector<int> search(const vector<float>& query, int k, Metric mertic);
        const vector<float>& getVector(int id) const;

    private: 
        vector<VectorItem> data;
    
};