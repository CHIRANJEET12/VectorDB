#include "bruteforce.h"
#include "distance.h"
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

void BruteForceIndex::add(const VectorItem& item){
    data.push_back(item);
}


vector<int> BruteForceIndex::search(const vector<float>& query, int k, Metric metric){

    //pair<distance, id>
    priority_queue<pair<float,int>>pq;
    
    for(auto& it : data){
        float dist = computeDistanceBasedonMetrics(query, it.vec, metric);

        if(pq.size() < k){
            pq.push({dist, it.id});
        }else if(pq.top().first > dist){
            pq.pop();
            pq.push({dist, it.id});
        }
    }


    // store the ids
    vector<int>result;
    while(!pq.empty()){
        result.push_back(pq.top().second);
        pq.pop();
    }

    // 1 2 3 ...
    reverse(result.begin(), result.end());


    return result;
}