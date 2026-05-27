#include <vector>
#include <string>
#include <iostream>

#include <curl/curl.h>
#include "../include/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

static size_t WriteCallback(
    void* contents,
    size_t size,
    size_t nmemb,
    string* response
){
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

vector<float> embedText(const string& text){

    CURL* curl = curl_easy_init();

    string response;

    if(!curl){
        cerr << "Failed to initialize CURL\n";
        return {};
    }

    // Request body
    json body = {
        {"model", "nomic-embed-text"},
        {"prompt", text}
    };

    string bodyStr = body.dump();

    // Set URL
    curl_easy_setopt(
        curl,
        CURLOPT_URL,
        "http://localhost:11434/api/embeddings"
    );

    // POST request body
    curl_easy_setopt(
        curl,
        CURLOPT_POSTFIELDS,
        bodyStr.c_str()
    );

    // Headers
    struct curl_slist* headers = nullptr;

    headers = curl_slist_append(
        headers,
        "Content-Type: application/json"
    );

    curl_easy_setopt(
        curl,
        CURLOPT_HTTPHEADER,
        headers
    );

    // Response callback
    curl_easy_setopt(
        curl,
        CURLOPT_WRITEFUNCTION,
        WriteCallback
    );

    curl_easy_setopt(
        curl,
        CURLOPT_WRITEDATA,
        &response
    );

    // Execute request
    CURLcode res = curl_easy_perform(curl);

    if(res != CURLE_OK){
        cerr << "CURL request failed: "
             << curl_easy_strerror(res)
             << "\n";

        curl_easy_cleanup(curl);
        return {};
    }

    curl_easy_cleanup(curl);

    // Parse JSON response
    json j = json::parse(response);

    vector<float> embedding =
        j["embedding"].get<vector<float>>();

    return embedding;
}