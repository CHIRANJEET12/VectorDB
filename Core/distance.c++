#include "distance.h"
#include <cmath>
#include <stdexcept>
using namespace std;


void check_dimension(const vector<float>& a, const vector<float>& b){
    if(a.size() != b.size()) throw invalid_argument("Vector dimensions should be same for being considered for metric calculation.");
}

float euclidean(const vector<float>& a, const vector<float>& b){
    check_dimension(a,b);
    
    int n = a.size();

    float sum = 0.0f;
    for(int i=0;i<n;i++){
        float dist = a[i] - b[i];
        sum += dist * dist;
    }

    return sqrt(sum);
}



float manhattan(const vector<float>& a, const vector<float>& b){
    check_dimension(a,b);
    
    int n = a.size();

    float sum = 0.0f;
    for(int i=0;i<n;i++){
        float dist = fabs(a[i] - b[i]);
        sum += dist;
    }

    return sum;
}



float cosine(const vector<float>& a, const vector<float>& b){
    check_dimension(a,b);

    int n = a.size();

    float dot_product = 0.0f;
    float sqr_a = 0.0f;
    float sqr_b = 0.0f;

    for(int i=0;i<n;i++){
        dot_product += a[i] * b[i];
        sqr_a += a[i] * a[i];
        sqr_b += b[i] * b[i];
    }

    float magnitude = (sqrt(sqr_a) * sqrt(sqr_b));

    if(magnitude == 0.0f){
        throw invalid_argument("Vector dimensions should be same for being considered for metric calculation.");
    }
    float cosineSimilarity = dot_product/magnitude;

    float cosineDistance = 1 - cosineSimilarity;

    return cosineSimilarity;
}

float computeDistanceBasedonMetrics(const vector<float>& a, const vector<float>& b, Metric metric){
    if(metric == Metric::EUCLIDEAN){
        return euclidean(a, b);
    } else if(metric == Metric::MANHATTAN){
        return manhattan(a, b);
    } else if(metric == Metric::COSINE){
        return cosine(a, b);
    }
    throw invalid_argument("Unknown metric");
}