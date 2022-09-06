#include "SplayTree.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

//all rotations come from stepik problems/ prof amans lectures plus additional input for parent pointer

void SplayTree::rotateLeft(Node* node) {
    Node *newParent = node->right;
    Node *grandChild = node->right->left;
    node->right = grandChild;
    newParent->parent = node->parent;
    if(grandChild){
        grandChild->parent = node;
    }
    if(node->parent == nullptr){
        root = newParent;
    }
    else if(node == node->parent->right){
        node->parent->right = newParent;
    }
    else if(node == node->parent->left){
        node->parent->left = newParent;
    }
    newParent->left = node;
    node->parent = newParent;

}

void SplayTree::rotateRight(Node *node){
    Node* newParent = node->left;
    Node* grandChild = node->left->right;
    newParent->parent = node->parent;
    node->left = grandChild;
    if(grandChild){
        grandChild->parent = node;
    }
    if(node->parent == nullptr){
        root = newParent;
    }
    else if(node == node->parent->right){
        node->parent->right = newParent;
    }
    else if(node == node->parent->left){
        node->parent->left = newParent;
    }
    newParent->right = node;
    node->parent = newParent;
}


void SplayTree::Splay(Node* node) {         //splay function derived from "Jenny's Lectures" on youtube, as well as prof Amans lectures on rotations
    while(node->parent){
        if(node->parent == root){
            if(node->parent->right == node){
                rotateLeft(node->parent);
            }
            else{
                rotateRight(node->parent);
            }
        }
        else{
            Node* parent = node->parent;
            Node* grandParent = node->parent->parent;
            if(node == parent->left && parent == grandParent->left){
                rotateRight(grandParent);
                rotateRight(parent);
            }
            else if(node == parent->right && parent == grandParent->right){
                rotateLeft(grandParent);
                rotateLeft(parent);
            }
            else if(node == parent->left && parent == grandParent->right){
                rotateRight(parent);
                parent = node->parent;
                rotateLeft(parent);
            }
            else if(node == parent->right && parent == grandParent->left){
                rotateLeft(parent);
                parent = node->parent;
                rotateRight(parent);
            }

        }
    }
    root = node;

}

void SplayTree::insert(Year year){      //Insertion taken from Prof Amans Lectures/PsuedoCode on BST Insertion
    Node* curr = root;
    Node* parent = nullptr;
    bool valid = true;
    while(curr){        //find appropriate spot
        parent = curr;
        if(year.getYear() < curr->year.getYear()){
            curr = curr->left;
        }
        else if(year.getYear() > curr->year.getYear()){
            curr = curr->right;
        }
        else{
            cout << "invalid" << endl;
            valid = false;
            break;
        }
    }
    if(valid){      //when curr == nullptr, create new node and splay. Need bool to make sure curr did not hit a repeat
        Node* newNode = new Node();
        newNode->parent = parent;
        newNode->year = year;
        newNode->left = nullptr;
        newNode->right = nullptr;
        if(parent == nullptr){
            root = newNode;
        }
        else if(year.getYear()>parent->year.getYear()){
            parent->right = newNode;
        }
        else{
            parent->left = newNode;
        }
        Splay(newNode);
    }
}


void SplayTree::find(string name) {         
    int year = 0;
    int rank = 99999;
    int count = 0;
    bool found = false;
    findHelperMale(name, root, year, rank, count);      //updates the variables to the correct value for males
    if(year != 0){
        cout << name << " was most popular amongst males in " << year << " with " << count << " entries and rank #"<< rank <<endl;
        Splay(findHelperYear(year, root));      //splay the node in which the name was found in
        found = true;
    }
    year = 0;
    count = 0;
    rank = 99999;
    findHelperFemale(name, root, year, rank, count);        //updates the variables to the correct value for females
    if(year != 0){
        cout << name << " was most popular amongst females in " << year << " with " << count << " entries and was rank #" << rank << endl;
        Splay(findHelperYear(year, root));     //splay the node in which the name was found in
        found = true;
    }
    if(!found){
        cout << name << " was not found." <<endl;
    }
}


void SplayTree::findHelperMale(string name, Node *root, int& year, int& rank, int& count) {     //implements a concept similar to inorder traversal
    if(!root)
        return;
    else{
        findHelperMale(name, root->left, year, rank, count);
        if(root->year.rankOfMaleName(name).first != 0){         //if there is the target name in the specified year
            if(root->year.rankOfMaleName(name).second > count){     //if the count of that name is greater than current count, update
                rank = root->year.rankOfMaleName(name).first;
                count = root->year.rankOfMaleName(name).second;
                year = root->year.getYear();
            }
        }
        findHelperMale(name, root->right, year, rank, count);
    }
}

void SplayTree::findHelperFemale(string name, Node *root, int & year, int & rank, int & count) {
    if(!root)
        return;
    else{
        findHelperFemale(name, root->left, year, rank, count);
        if(root->year.rankOfFemaleName(name).first!= 0){             //if there is the target name in the specified year
            if(root->year.rankOfFemaleName(name).second > count){       //if the count of that name is greater than current count, update
                rank = root->year.rankOfFemaleName(name).first;
                count = root->year.rankOfFemaleName(name).second;
                year = root->year.getYear();
            }
        }
        findHelperFemale(name, root->right, year, rank, count);
    }
}
SplayTree::Node* SplayTree::findHelperYear(int year, Node* root) {      //returns the year object that matches has the same year integer as the input
    if(root == nullptr){
        return nullptr;
    }
    else if(root->year.getYear() == year){
        return root;
    }
    else if(year > root->year.getYear()){
        return findHelperYear(year, root->right);
    }
    else{
        return findHelperYear(year, root->left);
    }
}
SplayTree::Node* SplayTree::find(int num) {
    Node* target = findHelperYear(num, root);       
    if(target){
        target->year.sortNames();

        Splay(target);                     //splay the target node
    }
    else{
        cout << num <<" was not found." << endl;
    }
    return target;
}

pair<vector<pair<pair<unsigned int,string>, unsigned int>>, vector<pair<pair<unsigned int,string>, unsigned int>>> SplayTree::findTop10() {
    vector<pair<pair<unsigned int,string>, unsigned int>> topTenM;
    vector<pair<pair<unsigned int,string>, unsigned int>> topTenF;
    findTop10Helper(this->root, topTenM, topTenF);

    return make_pair(topTenM, topTenF);             //returns the pair to print in main
}
void SplayTree::findTop10Helper(Node* root,vector<pair<pair<unsigned int,string>,unsigned int> > & top10Males, vector<pair<pair<unsigned int,string>,unsigned int >> & top10Females){
    if(!root)                   //implements an inOrderTraversal type system to conduct a linear search through each object's vectors
        return;             
    else{
        findTop10Helper(root->left, top10Males, top10Females);
        vector<pair<unsigned int, string>> topTenYearM = root->year.topTenMale();       //top ten males and their count
        vector<pair<unsigned int, string>> topTenYearF = root->year.topTenFemale();
        vector<pair<pair<unsigned int, string>, unsigned int>> tempF;       //temp variable to strore above vector as well as the year of the pair
        vector<pair<pair<unsigned int, string>, unsigned int>>tempM;

        for(int i = 0; i < 10; i++){
            top10Males.push_back(make_pair(topTenYearM[i], root->year.getYear()));      //take top 10 from the current years vector, and push it to the return vector
            top10Females.push_back(make_pair(topTenYearF[i], root->year.getYear()));
        }
        sort(top10Females.begin(), top10Females.end(), greater<pair<pair<unsigned int, string>, unsigned int>>());      //sort the updated list
        sort(top10Males.begin(), top10Males.end(), greater<pair<pair<unsigned int, string>, unsigned int>>());

        tempM = top10Males;
        tempF = top10Females;
        top10Males.clear();
        top10Females.clear();   
        for(int i = 0; i < 10; i++){        //trim the new vector so that it only holds 10 names instead of a possible 20
            top10Males.push_back(tempM[i]);
            top10Females.push_back(tempF[i]);
        }

        findTop10Helper(root->right, top10Males, top10Females);
    }
}

