
#pragma once
#include "distance.h"
#include "bruteforce.h"
#include <vector>
#include <queue>
using namespace std;

struct KDNode {
    VectorItem item;
    int axis;
    KDNode* left;
    KDNode* right;

    KDNode(const VectorItem& it, int ax) : item(it), axis(ax), left(nullptr), right(nullptr) {}
};

class KDTreeIndex {
    public:
        void add(const VectorItem& item);
        KDTreeIndex(int dim);

        void build();

        vector<int> search(const vector<float>& query, int k, Metric metric);

    private:
        KDNode* root;
        int DIM;

        vector<VectorItem> data;

        KDNode* buildRec(vector<VectorItem>& item, int depth);

        void KnnRec(KDNode* node, const vector<float>& query, int k, Metric metric, priority_queue<pair<float,int>>& pq);
    
    };