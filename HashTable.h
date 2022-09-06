//
// Created by Ayesha on 7/27/2021, modified by Xin 7/31.
//

#ifndef PROJECT3REMASTERED_HASHTABLE_H
#define PROJECT3REMASTERED_HASHTABLE_H
#include <vector>
#include <iostream>
#include "Year.h"
#include <tuple>
#include <cmath>
#include "HashNode.h"
using namespace std;

class HashTable {
    HashNode* years;
    int maxSize, currentSize;
    double LOAD_FACTOR = 0.7;
    double resizeFactor;
public:
    HashTable();
    void insert(Year y);
    unsigned int returnKey(unsigned int year);

    vector<pair<unsigned int, string>> findMaleYear(int year);
    vector<pair<unsigned int, string>> findFemaleYear(int year);

    vector<tuple<unsigned int, string, unsigned int>> findTopMale();
    vector<tuple<unsigned int, string, unsigned int>> findTopFemale();
    void findName(string name);
};


#endif //PROJECT3REMASTERED_HASHTABLE_H
