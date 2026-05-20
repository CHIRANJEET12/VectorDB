#include "kdtree.h"
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;


void KDTreeIndex::add(const VectorItem& item){
    data.push_back(item);
}


//constructor
KDTreeIndex::KDTreeIndex(int dim) : root(nullptr), DIM(dim){};

KDNode* KDTreeIndex::buildRec(vector<VectorItem>& item, int depth){
    if(item.empty()) return nullptr;

    int axis = depth % DIM;

    sort(item.begin(), item.end(), [axis](const VectorItem& a, const VectorItem& b){
        return a.vec[axis] < b.vec[axis];
    });

    int mid = item.size() / 2;

    //form the node of the mid element or median
    KDNode* node = new KDNode(item[mid], axis);

    vector<VectorItem> left(item.begin(), item.begin() + mid);
    vector<VectorItem> right(item.begin() + mid + 1, item.end());

    node->left = buildRec(left, depth + 1);
    node->right = buildRec(right, depth + 1);

    return node;
}


void KDTreeIndex::build(){
    root = buildRec(data, 0);
}



void KDTreeIndex::KnnRec(KDNode* node, const vector<float>& query, int k, Metric metric, priority_queue<pair<float,int>>& pq){
    if(!node) return;

    float dist = computeDistanceBasedonMetrics(query, node->item.vec, metric);

    if(pq.size()<k){
        pq.push({dist, node->item.id});
    }else if (dist < pq.top().first) {
        pq.pop();
        pq.push({dist, node->item.id});
    }

    int axis = node->axis;
    KDNode* front = query[axis] < node->item.vec[axis] ? node->left : node->right;
    KDNode* rear = query[axis] < node->item.vec[axis] ? node->right : node->left;

    KnnRec(front, query, k, metric, pq);

    float diff = fabs(query[axis] - node->item.vec[axis]);

    if(pq.size() < k || diff < pq.top().first){
        KnnRec(rear, query, k, metric, pq);
    }
}

vector<int> KDTreeIndex::search(const vector<float>& query, int k, Metric metric){
    priority_queue<pair<float,int>> pq;

    KnnRec(root, query, k, metric, pq);

    vector<int>result;
    while(!pq.empty()){
        result.push_back(pq.top().second);
        pq.pop();
    }
    reverse(result.begin(), result.end());

    return result;
}