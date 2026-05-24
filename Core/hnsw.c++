#include "hnsw_node.h"
#include <queue>
#include <algorithm>
#include <random>

//constructor
HNSWIndex::HNSWIndex(int dim, int _M, int _efSearch) : DIM(dim), M(_M), entry(-1), efSearch(_efSearch), maxLevel(-1) {};

int HNSWIndex::randomLevel(){
    static std::mt19937 rng(42);

    static std::uniform_real_distribution<float>
        dist(0.0, 1.0);

    int level = 0;

    while(dist(rng) < 0.5f){
        level++;
    }

    return level;
}

void HNSWIndex::add(int id, const vector<float>& vec){
    int level = randomLevel();
    level = min(level, 5);
    HNSWNode newNode(id, level, vec);

    int newIndex = nodes.size();

    if(nodes.empty()){
        nodes.push_back(newNode);
        entry = 0;
        maxLevel = level;

        return;
    }

    nodes.push_back(newNode);
    

    if(level > maxLevel){
        maxLevel = level;
        entry = newIndex;
    }


    // priority_queue<pair<float,int>>pq;

    // for(int i=0;i<nodes.size();i++){
    //     float dist = computeDistanceBasedonMetrics(vec, nodes[i].vec, Metric::EUCLIDEAN);
    //     if(pq.size() < M){
    //         pq.push({dist, i});
    //     }else if(dist < pq.top().first){
    //         pq.pop();
    //         pq.push({dist, i});
    //     }
    // }

    // int newIndex = nodes.size();

    // nodes.push_back(newNode);


    // while(!pq.empty()){
    //     int neigh = pq.top().second;
    //     pq.pop();

    //     nodes[newIndex].neighbors[0].push_back(neigh);

    //     nodes[neigh].neighbors[0].push_back(newIndex);
    // }


    for(int layer = 0; layer<=level;layer++){
        priority_queue<pair<float,int>> pq;
        for(int i=0;i<newIndex;i++){
            if(nodes[i].level < layer){
                continue;
            }

            float dist = computeDistanceBasedonMetrics(vec, nodes[i].vec, Metric::EUCLIDEAN);
            if(pq.size() < M){
                pq.push({dist, i});
            }else if(dist < pq.top().first){
                pq.pop();
                pq.push({dist, i});
            }
        }

        while(!pq.empty()){
            int neigh = pq.top().second;
            pq.pop();
            nodes[newIndex].neighbors[layer].push_back(neigh);
            nodes[neigh].neighbors[layer].push_back(newIndex);
        }
    }

}



vector<int> HNSWIndex::search(const vector<float>& query, int k, Metric metric){
    int explored = 0;  
    vector<int> res;

    if(nodes.empty()) return res;

    int curr = entry;

    for(int layer = maxLevel; layer > 0; layer--){
        curr = greedySearchLayer(query, curr, layer, metric);
    }

    // min heap
    priority_queue<
        pair<float,int>,
        vector<pair<float,int>>,
        greater<pair<float,int>>
    > localPQ;

    // max heap
    priority_queue<pair<float,int>> bestPQ;

    vector<bool> visited(nodes.size(), false);

    float entryDist = computeDistanceBasedonMetrics(query, nodes[curr].vec, metric);

    localPQ.push({entryDist, curr});
    bestPQ.push({entryDist, curr});

    visited[curr] = true;

    while(!localPQ.empty() && explored < efSearch){
        pair<float,int> top = localPQ.top();
        float currDist = top.first;
        int currNode = top.second;
        localPQ.pop();
        explored++;

        for(int neigh : nodes[currNode].neighbors[0]){
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



int HNSWIndex::greedySearchLayer(const vector<float>& query, int entryNode, int layer, Metric metric){
    int currNode = entryNode;
    if(layer > nodes[currNode].level) return currNode;

    float currDist = computeDistanceBasedonMetrics(query, nodes[currNode].vec, metric);

    bool improved = true;

    while(improved){
        improved = false;
        if(layer > nodes[currNode].level) break;

        for(int neigh : nodes[currNode].neighbors[layer]){
            float dist = computeDistanceBasedonMetrics(query, nodes[neigh].vec, metric);

            if(dist < currDist){
                currDist = dist;
                currNode = neigh;

                improved = true;
            }
        }
    }

    return currNode;
}