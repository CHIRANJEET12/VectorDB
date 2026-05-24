#include <vector>
#include <string>
using namespace std;

vector<float> embedText(const string& text){
    vector<float> vec(16, 0.0);

    for(int i=0;i<text.size();i++){
        vec[i%16] += (text[i] % 10) * 0.01;
    }

    return vec;
}