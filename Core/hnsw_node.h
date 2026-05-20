
#pragma once
#include "distance.h"
#include<vector>
using namespace std;


struct HNSWNode {
    int id;
    vector<float> vec;
    vector<int> neighbors;

    HNSWNode(int _id, const vector<float>& _vec)
        : id(_id), vec(_vec) {}
};

class HNSWIndex {
    private:
        vector<HNSWNode>nodes;
        int M;
        int DIM;
        int entry;

    public:
        HNSWIndex(int dim, int _M);

        void add(int id, const vector<float>& vec);

        vector<int> search(const vector<float>& query, int k, Metric metric);
};