#include <iostream>
#include <vector>
#include <random>
#include <chrono>

#include "hnsw_index.h"
#include "kdtree.h"
#include "bruteforce.h"

using namespace std;

vector<vector<float>> DATA;
vector<vector<float>> QUERIES;

vector<float> randomVector(int dim){
    static mt19937 rng(42);
    static uniform_real_distribution<float> dist(0.0, 1.0);

    vector<float> v(dim);
    for(int i=0;i<dim;i++) v[i] = dist(rng);
    return v;
}

void benchmarkHNSW(int N, int DIM, int Q, int k, Metric metric){
    cout << "\n================ HNSW ================\n";

    HNSWIndex index(DIM,8);

    auto build_start = chrono::high_resolution_clock::now();

    for(int i=0;i<N;i++){
        index.add(i, DATA[i]);
    }

    auto build_end = chrono::high_resolution_clock::now();

    cout << "Build time: "
         << chrono::duration<double, milli>(build_end - build_start).count()
         << " ms\n";

    for(int i=0;i<10;i++)
        index.search(QUERIES[0], k, metric);

    auto start = chrono::high_resolution_clock::now();
    for(int i=0;i<Q;i++)
        index.search(QUERIES[i], k, metric);
    auto end = chrono::high_resolution_clock::now();

    double ms = chrono::duration<double, milli>(end - start).count();

    cout << "Total query time: " << ms << " ms\n";
    cout << "Per query: " << (ms*1000.0)/Q << " us\n";

}

void benchmarkKDTree(int N, int DIM, int Q, int k, Metric metric){
    cout << "\n================ KD-TREE ================\n";

    KDTreeIndex index(DIM);

    auto build_start = chrono::high_resolution_clock::now();
    for(int i=0;i<N;i++)
        index.add({i, DATA[i]});
    index.build();
    auto build_end = chrono::high_resolution_clock::now();

    cout << "Build time: "
         << chrono::duration<double, milli>(build_end - build_start).count()
         << " ms\n";

    // warmup
    for(int i=0;i<10;i++)
        index.search(QUERIES[0], k, metric);

    auto start = chrono::high_resolution_clock::now();
    for(int i=0;i<Q;i++)
        index.search(QUERIES[i], k, metric);
    auto end = chrono::high_resolution_clock::now();

    double ms = chrono::duration<double, milli>(end - start).count();

    cout << "Total query time: " << ms << " ms\n";
    cout << "Per query: " << (ms*1000.0)/Q << " us\n";
}

void benchmarkBrute(int N, int DIM, int Q, int k, Metric metric){
    cout << "\n============= BRUTE FORCE ==============\n";

    BruteForceIndex index;
    for(int i=0;i<N;i++)
        index.add({i, DATA[i]});

    // warmup
    for(int i=0;i<10;i++)
        index.search(QUERIES[0], k, metric);

    auto start = chrono::high_resolution_clock::now();
    for(int i=0;i<Q;i++)
        index.search(QUERIES[i], k, metric);
    auto end = chrono::high_resolution_clock::now();

    double ms = chrono::duration<double, milli>(end - start).count();

    cout << "Total query time: " << ms << " ms\n";
    cout << "Per query: " << (ms*1000.0)/Q << " us\n";
}

int main(){
    int N = 1000;
    int DIM = 16;
    int Q = 100;
    int k = 5;

    Metric metric = Metric::EUCLIDEAN;  // SAME metric for both

    // Generate shared data
    DATA.reserve(N);
    for(int i=0;i<N;i++)
        DATA.push_back(randomVector(DIM));

    QUERIES.reserve(Q);
    for(int i=0;i<Q;i++)
        QUERIES.push_back(randomVector(DIM));

    cout << "N=" << N << " DIM=" << DIM << " Q=" << Q << " k=" << k << "\n";

    benchmarkKDTree(N, DIM, Q, k, metric);
    benchmarkBrute(N, DIM, Q, k, metric);
    benchmarkHNSW(N, DIM, Q, k, metric);
}