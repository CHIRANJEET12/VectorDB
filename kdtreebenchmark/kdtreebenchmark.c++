#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "kdtree.h"

using namespace std;

vector<vector<float>> DATA;
vector<vector<float>> QUERIES;

vector<float> randomVector(int dim) {
    static mt19937 rng(42);
    static uniform_real_distribution<float> dist(0.0, 1.0);

    vector<float> v(dim);
    for (int i = 0; i < dim; i++) {
        v[i] = dist(rng);
    }
    return v;
}

int main() {

    int N = 1000;
    int DIM = 16;
    int Q = 100;
    int k = 5;

    DATA.reserve(N);
    for (int i = 0; i < N; i++) {
        DATA.push_back(randomVector(DIM));
    }

    QUERIES.reserve(Q);
    for (int i = 0; i < Q; i++) {
        QUERIES.push_back(randomVector(DIM));
    }

    KDTreeIndex index(DIM);

    auto build_start = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        index.add({i, DATA[i]});
    }

    index.build();

    auto build_end = chrono::high_resolution_clock::now();

    cout << "KDTree build time: "
         << chrono::duration<double, milli>(build_end - build_start).count()
         << " ms\n";

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < Q; i++) {
        index.search(QUERIES[i], k, Metric::EUCLIDEAN);
    }

    auto end = chrono::high_resolution_clock::now();

    double ms = chrono::duration<double, milli>(end - start).count();

    cout << "Total time for " << Q << " queries: " << ms << " ms\n";

    cout << "Average per query: " << (ms * 1000.0) / Q << " us\n";

    cout << "Memory (approx): "
         << (N * DIM * sizeof(float)) / (1024.0 * 1024.0)
         << " MB\n";

    return 0;
}