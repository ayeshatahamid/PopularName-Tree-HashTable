//
// Created by Ayesha on 7/27/2021.
//

#ifndef PROJECT3REMASTERED_HASHNODE_H
#define PROJECT3REMASTERED_HASHNODE_H
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct HashNode {
    vector<pair<unsigned int, string>> female; // <count, name>
    vector<pair<unsigned int, string>> male;

    HashNode() {
        male = {};
        female = {};
    }

    HashNode(vector<pair<unsigned int, string>> f, vector<pair<unsigned int, string>> m) {
        //sort(f.begin(), f.end(), greater<pair<unsigned int, string>>());
        female = f;
        //sort(m.begin(), m.end(), greater<pair<unsigned int, string>>());
        male = m;
    }
};


#endif //PROJECT3REMASTERED_HASHNODE_H
