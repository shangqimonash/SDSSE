//
// Created by shangqi on 2021/4/20.
//

#ifndef FBDSSE_SDSSECQSCLIENT_H
#define FBDSSE_SDSSECQSCLIENT_H

#include "SDSSECQSServer.h"

enum OP {
    INS, DEL
};

class SDSSECQSClient {
private:
    // keys
    uint8_t *K = (unsigned char*) "0123456789123456";
    uint8_t *K_s = (unsigned char*) "0123456789654321";
    uint8_t *K_t = (unsigned char*) "9876543210123456";
    uint8_t *K_X = (unsigned char*) "0123456789123456";
    uint8_t *K_x = (unsigned char*) "0123456789654321";
    uint8_t *K_I = (unsigned char*) "0123456789123456";
    uint8_t *K_Z = (unsigned char*) "0123456789654321";
    uint8_t *K_z = (unsigned char*) "9876543210123456";
    uint8_t *sk_T = (unsigned char*) "0123456789123456";
    uint8_t *sk_X = (unsigned char*) "0123456789654321";
    uint8_t *iv = (unsigned char*) "9876543210123456";

    // deletion map
    unordered_map<string, BloomFilter<32, GGM_SIZE, HASH_SIZE>*> MSK_T;
    unordered_map<string, BloomFilter<32, GGM_SIZE, HASH_SIZE>*> MSK_X;

    // search count map
    unordered_map<string, int> CT_T;
    unordered_map<string, int> CT_X;

    // update map
    unordered_map<string, int> CT;
    unordered_map<string, uint8_t[DIGEST_SIZE]> ST_T;
    unordered_map<string, int> CX;
    unordered_map<string, uint8_t[DIGEST_SIZE]> ST_X;

    // GGM Tree
    GGMTree *tree;

    // pairing and GT element
    Pairing *e;
    GT g;

    // SSE Server
    SDSSECQSServer *server;

    Zr Fp(uint8_t *input, size_t input_size, uint8_t *key);
    vector<GGMNode> rev_key_generation(BloomFilter<32, 65536, 3>* deletion_map, uint8_t *key);
public:
    SDSSECQSClient();
    void update(OP op, const string& keyword, int ind);
    vector<int> search(int count, ...);
};


#endif //FBDSSE_SDSSECQCLIENT_H