#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class Year {
    unsigned int year;
    vector<pair<unsigned int,string>> male, female; //Lists of counts/names per year by gender
    
public:
    //Constructors
    Year();
    Year(unsigned int year);

    //Adds a name to the Year's correct vector
    void addName(bool isFemale, unsigned int count, string name);

    //Accessors
    unsigned int getYear();
    vector<pair<unsigned int,string>> returnMale();
    vector<pair<unsigned int,string>> returnFemale();
    vector<pair<unsigned int, string>> topTenFemale();
    vector<pair<unsigned int, string>> topTenMale();

    //Sorts both name vectors for a Year
    void sortNames();

    //Accessors for a specific name in a Year 
    bool isInVector(string name);
    pair<pair<unsigned int, unsigned int>,pair<unsigned int, unsigned int>> rankOfName(string name);
    pair<unsigned int, unsigned int> rankOfMaleName(string name);
    pair<unsigned int, unsigned int> rankOfFemaleName(string name);

    //Displays information about the names in a Year
    void printListSizes();
    void printTop(int number);    
};