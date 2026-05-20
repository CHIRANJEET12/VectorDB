#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "bruteforce.h"
using namespace std;

vector<float> randomVector(int dim){
    static mt19937 rng(42);
    static uniform_real_distribution<float> dist(0.0, 1.0);

    vector<float>v(dim);
    for(int i=0;i<dim;i++){
        v[i] = dist(rng);
    }

    return v;
}

int main(){
    int n = 10000;
    int DIM = 128;
    int Q = 100;
    int k = 5;

    BruteForceIndex index;
    for(int i=0;i<n;i++){
        index.add({i, randomVector(DIM)});
    }


    //benchmark queries
    auto start = chrono::high_resolution_clock::now(); 

    for(int i=0;i<Q;i++){
        auto query = randomVector(DIM);
        index.search(query, k, Metric::EUCLIDEAN);
    }

    auto end = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(end - start).count();


    cout << "Total time for " << Q << " queries: " << ms << " ms\n";
    cout << "Average per query: " << ms / Q << " ms\n";
}