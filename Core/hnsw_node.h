
#pragma once
#include "distance.h"
#include<vector>
using namespace std;


struct HNSWNode {
    int id;
    int level;
    vector<float> vec;
    vector<vector<int>> neighbors;

    HNSWNode(int _id, int _level, const vector<float>& _vec)
        : id(_id), level(_level), vec(_vec) {
            neighbors.resize(level + 1);
        }
};

class HNSWIndex {
    private:
        vector<HNSWNode>nodes;
        int M;
        int DIM;
        int entry;
        int maxLevel;
        int randomLevel();
        int efSearch;
        int greedySearchLayer(const vector<float>& query, int entryNode, int layer, Metric metric);

    public:
        HNSWIndex(int dim, int _M, int _efSearch);

        void add(int id, const vector<float>& vec);

        vector<int> search(const vector<float>& query, int k, Metric metric);
};