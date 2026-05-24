#include <vector>
#include <string>
using namespace std;

vector<string> loadDocuments() {
    return {
        "Machine learning is a subset of artificial intelligence.",
        "Vector databases store high dimensional embeddings efficiently.",
        "HNSW is a graph based approximate nearest neighbor algorithm.",
        "KD Tree works well in low dimensions but fails in high dimensions.",
        "RAG combines retrieval and generation for LLM applications."
    };
}