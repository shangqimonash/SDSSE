#ifndef AURA_SSESERVERHANDLER_H
#define AURA_SSESERVERHANDLER_H

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

#include "BloomFilter.h"
extern "C" {
#include "CommonUtil.h"
}
#include "GGMTree.h"

using namespace chrono;
using namespace std;

class SSEServerHandler {
private:
    unordered_map<string, string> tags;
    unordered_map<string, vector<string>> dict;
    unordered_map<long, uint8_t*> keys;
    unordered_map<long, long> root_key_map;
    int GGM_SIZE;

    void compute_leaf_key_maps(const vector<GGMNode>& node_list, int level);
public:
    explicit SSEServerHandler(int GGM_SIZE);
    void add_entries(const string& label, const string& tag, vector<string> ciphertext_list);
    vector<string> search(uint8_t *token, const vector<GGMNode>& node_list, int level);
};


#endif //AURA_SSESERVERHANDLER_H
