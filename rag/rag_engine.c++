#include <iostream>
#include <vector>
#include <unordered_map>

#include "../Core/hnsw_node.h"
#include "document.h"
#include "embedder.h"
#include "dataset_loader.h"

using namespace std;



unordered_map<int,string> docStore;


int main(){
    vector<string>docs = loadDocuments();

    int DIM = 16;

    HNSWIndex index(DIM,8,50);

    for(int i=0;i<docs.size();i++){
        vector<float> emb = embedText(docs[i]);

        index.add(i,emb);

        docStore[i] = docs[i];
    }

    cout << "Index built!\n";

    string query;


    while(true){
        cout<<"Enter query : ";
        getline(cin, query);

        vector<float> qvec = embedText(query);

        vector<int> res = index.search(qvec, 3, Metric::EUCLIDEAN);

        cout << "\nTop results:\n";

        for(int id : res){
            cout << "- " << docStore[id] << "\n";
        }
    }

    
}