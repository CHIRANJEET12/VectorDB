#include "hnsw_node.h"
#include <queue>
#include <algorithm>


//constructor
HNSWIndex::HNSWIndex(int dim, int _M) : DIM(dim), M(_M), entry(-1) {};

void HNSWIndex::add(int id, const vector<float>& vec){
    HNSWNode newNode(id, vec);

    if(nodes.empty()){
        nodes.push_back(newNode);
        entry = 0;
        return;
    }

    priority_queue<pair<float,int>>pq;

    for(int i=0;i<nodes.size();i++){
        float dist = computeDistanceBasedonMetrics(vec, nodes[i].vec, Metric::EUCLIDEAN);
        if(pq.size() < M){
            pq.push({dist, i});
        }else if(dist < pq.top().first){
            pq.pop();
            pq.push({dist, i});
        }
    }

    int newIndex = nodes.size();

    nodes.push_back(newNode);


    while(!pq.empty()){
        int neigh = pq.top().second;
        pq.pop();

        nodes[newIndex].neighbors.push_back(neigh);

        nodes[neigh].neighbors.push_back(newIndex);
    }

}



vector<int> HNSWIndex::search(const vector<float>& query, int k, Metric metric){
    int efSearch = 50;
    int explored = 0;  
    vector<int> res;

    if(nodes.empty()) return res;

    // min heap
    priority_queue<
        pair<float,int>,
        vector<pair<float,int>>,
        greater<pair<float,int>>
    > localPQ;

    // max heap
    priority_queue<pair<float,int>> bestPQ;

    vector<bool> visited(nodes.size(), false);

    float entryDist = computeDistanceBasedonMetrics(query, nodes[entry].vec, metric);

    localPQ.push({entryDist, entry});
    bestPQ.push({entryDist, entry});

    visited[entry] = true;

    while(!localPQ.empty() && explored < efSearch){
        pair<float,int> top = localPQ.top();
        float currDist = top.first;
        int currNode = top.second;
        localPQ.pop();
        explored++;

        for(int neigh : nodes[currNode].neighbors){
            if(!visited[neigh]){
                visited[neigh] = true;
                float dist = computeDistanceBasedonMetrics(query, nodes[neigh].vec, metric);

                localPQ.push({dist, neigh});

                if(bestPQ.size() < k){
                    bestPQ.push({dist, neigh});
                }
                else if(dist < bestPQ.top().first){
                    bestPQ.pop();
                    bestPQ.push({dist, neigh});
                }
            }
        }
    }

    while(!bestPQ.empty()){
        res.push_back(bestPQ.top().second);
        bestPQ.pop();
    }

    reverse(res.begin(), res.end());

    return res;
}