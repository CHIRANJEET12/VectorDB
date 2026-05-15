#include <iostream>
#include "distance.h"
using namespace std;

int main(){


    vector<float> a = {2.4,4.5,7};
    vector<float> b = {3.7,5.4,1};

    cout<<"L2 : "<< euclidean(a,b) <<endl;
    cout<<"L1 : "<< manhattan(a,b) <<endl;
    cout<<"COSINE : "<< cosine(a,b) <<endl;


    return 0;
}