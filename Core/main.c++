// #include <iostream>
// #include "distance.h"
// #include "bruteforce.h"
// using namespace std;

// int main(){

// // test 1:
//     // vector<float> a = {2.4,4.5,7};
//     // vector<float> b = {3.7,5.4,1};

//     // cout<<"L2 : "<< euclidean(a,b) <<endl;
//     // cout<<"L1 : "<< manhattan(a,b) <<endl;
//     // cout<<"COSINE : "<< cosine(a,b) <<endl;


// // test 2:
//     BruteForceIndex index;
    
//     index.add({1, {1,2,3}});
//     index.add({2, {2,3,4}});
//     index.add({3, {10,10,10}});
    

//     vector<float> query = {1.5, 2.5, 3.5};

//     auto result = index.search(query, 2, Metric::COSINE);

//     for(int it : result){
//         cout<< it << " ";
//     }

//     return 0;
// }