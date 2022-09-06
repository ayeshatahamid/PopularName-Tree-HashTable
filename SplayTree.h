#pragma once
#include "Year.h"
#include <vector>
#include <tuple>

class SplayTree {
    struct Node {
        Year year;
        Node* left;
        Node* right;
        Node* parent;
    };
    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    void Splay(Node* node);
    Node* root;
    Node* findHelperYear(int year, Node* root);
    void findHelperMale(string name, Node* root, int & year, int & rank, int& count);
    void findHelperFemale(string name, Node* root, int & year, int & rank, int &  count);
    void findTop10Helper(Node* root,vector<pair<pair<unsigned int,string>, unsigned int>> & top10Males,vector<pair<pair<unsigned int,string>, unsigned int>> & top10Females );
public:
    SplayTree(){
        root = nullptr;
    }
    void insert(Year year);
    void find(string name);
    Node* find(int year);
    pair<vector<pair<pair<unsigned int,string>, unsigned int>>, vector<pair<pair<unsigned int,string>, unsigned int>>> findTop10();
};
