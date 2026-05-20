
#pragma once
#include <vector>
#include "hnsw_node.h"
#include "distance.h"

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