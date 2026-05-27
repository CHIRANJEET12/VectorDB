#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

#include "../Core/hnsw_node.h"
#include "../Core/bruteforce.h"
#include "document.h"
#include "embedder.h"
#include "dataset_loader.h"

using namespace std;

void normalize(vector<float>& vec){
    float norm = 0.0f;

    for(float x : vec){
        norm += x * x;
    }

    norm = sqrt(norm);

    if(norm == 0) return;

    for(float& x : vec){
        x /= norm;
    }
}



unordered_map<int,string> docStore;


int main(){
    vector<string>docs = loadDocuments();

    int DIM = 768;

    HNSWIndex index(DIM,8,50);
    BruteForceIndex ind;

    for(int i=0;i<docs.size();i++){
        vector<float> emb = embedText(docs[i]);

        normalize(emb);

        // Keep this same as in index.search in line number 44.
        // Options available(Euclidean, Manhattan, Cosine)
        index.add(i,emb,Metric::COSINE);
        ind.add({i, emb});

        docStore[i] = docs[i];
    }

    cout << "Index built!\n";

    string query;


    while(true){
        cout<<"Enter query : ";
        getline(cin, query);

        vector<float> qvec = embedText(query);

        normalize(qvec);

        // (misleading) test for recall //

        // vector<int> exact = ind.search(qvec, 5, Metric::EUCLIDEAN);
        // vector<int> approx = index.search(qvec, 5, Metric::EUCLIDEAN);

        // int c = 0;
        // for(int x : approx){
        //     for(int y : exact){
        //         if(x==y) c++;
        //     }
        // }

        // cout<<"Recall : "<< c/5 << endl;



        vector<int> res = index.search(qvec, 50, Metric::COSINE);

        vector<pair<float,int>>reranked;

        for(int id : res){
            float dist = computeDistanceBasedonMetrics(qvec, ind.getVector(id), Metric::EUCLIDEAN);
            reranked.push_back({dist, id});
        }

        sort(reranked.begin(), reranked.end());

        cout << "\nTop results:\n";

        // for(int i : res){
        //     cout << docStore[i] << endl;
        // }

        for(int i=0;i<5;i++){
            int id = reranked[i].second;
            
            cout << docStore[id] << "\n";
        }
    }

    
}