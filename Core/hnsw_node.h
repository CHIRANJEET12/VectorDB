
#pragma once
#include<vector>
using namespace std;


struct HNSWNode {
    int id;
    vector<float> vec;
    vector<int> neighbors;

    HNSWNode(int _id, const vector<float>& _vec)
        : id(_id), vec(_vec) {}
};