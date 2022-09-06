//
// Created by Ayesha on 7/27/2021, modified by Xin 7/31.
//

#include "HashTable.h"

HashTable::HashTable() {
    years = new HashNode[10];
    maxSize = 10;
    currentSize = 0;
    resizeFactor = 1.5;
}

void HashTable::insert(Year y) {
    double currLoad = (double) currentSize/maxSize;
    unsigned int index = returnKey(y.getYear());

    if (currLoad >= LOAD_FACTOR) {  //resizing and rehashing the array
        int newSize = ceil(maxSize * resizeFactor);
        HashNode* temp = new HashNode[newSize];

        //copying old elements
        for (int i = 0; i < currentSize; i++) {
            temp[i] = HashNode(years[i].female, years[i].male);
        }

        //deleting old array
        delete[] years;
        maxSize = newSize;
        years = temp;
    }

    //Insert data
    if (years[index].male.empty()) {
        years[currentSize] = HashNode(y.returnFemale(), y.returnMale());
    }
    else { //Open addressing for collisions
        while (!years[index].male.empty()) {
            index++;
        }
        years[currentSize] = HashNode(y.returnFemale(), y.returnMale());
    }
    currentSize++;

}

unsigned int HashTable::returnKey(unsigned int year) {
    return year - 1880;
}

vector<pair<unsigned int, string>> HashTable::findMaleYear(int year) { //find top 10 of a certain year, y
    vector<pair<unsigned int, string>> topTen;
    int y = returnKey(year);

    for (int i = 0; i < 10; i++) { // gets the top 10 in the male vector. Already sorted
        topTen.push_back(years[y].male[i]);
    }

    return topTen;
}
vector<pair<unsigned int, string>> HashTable::findFemaleYear(int year) { //find top 10 of a certain year, y
    vector<pair<unsigned int, string>> topTen;
    int y = returnKey(year);

    for (int i = 0; i < 10; i++) { // gets the top 10 in the male vector. Already sorted
        topTen.push_back(years[y].female[i]);
    }

    return topTen;
}

vector<tuple<unsigned int, string, unsigned int>> HashTable::findTopFemale() {
    vector<tuple<unsigned int, string, unsigned int>> top10;
    vector<pair<unsigned int, string>> female;
    for (int i = 0; i < 10; i++) {
        auto female = years[0].female;
        auto temp = make_tuple(female[i].first, female[i].second, 0);
        top10.emplace_back(temp);
    }

    for (int y = 1; y < currentSize; y++) {
        for (int i = 0; i < 10; i++) {
            female = years[y].female;
            auto temp = make_tuple(female[i].first, female[i].second, y);
            top10.emplace_back(temp);
        }
        // sort them
        sort(top10.begin(), top10.end(), greater<tuple<unsigned int, string, unsigned int>>());
        //erase the bottom 10
        for (int i = 0; i < 10; i++) {
            top10.pop_back();
        }
    }

    return top10;
}

vector<tuple<unsigned int, string, unsigned int>> HashTable::findTopMale() {
    vector<tuple<unsigned int, string, unsigned int>> top10;
    vector<pair<unsigned int, string>> male;
    for (int i = 0; i < 10; i++) {
        male = years[0].male;
        auto temp = make_tuple(male[i].first, male[i].second, 0);
        top10.emplace_back(temp);
    }

    for (int y = 1; y < currentSize; y++) {
        for (int i = 0; i < 10; i++) {
            male = years[y].male;
            auto temp = make_tuple(male[i].first, male[i].second, y);
            top10.emplace_back(temp);
        }
        // sort them
        sort(top10.begin(), top10.end(), greater<tuple<unsigned int, string, unsigned int>>());
        //erase the bottom 10
        for (int i = 0; i < 10; i++) {
            top10.pop_back();
        }
    }
    return top10;
}

void HashTable::findName(string name) {
    int maxYearM = -1, maxYearF = -1;
    int maxCountM = 0;
    int maxCountF = 0;
    int rankM, rankF;
    for (int y = 0; y < currentSize; y++) {  //goes through all the years and entries to search for the maxCount of the name
        auto m = years[y].male;
        auto f = years[y].female;

        for (int i = 0; i < m.size(); i++) {
            pair<unsigned int, string> curr = m[i];
            if (curr.second == name && curr.first > maxCountM) {
                maxYearM = y + 1880;
                maxCountM = curr.first;
                rankM = i + 1;
            }
        }
        for (int i = 0; i < f.size(); i++) {
            pair<unsigned int, string> curr = f[i];
            if (curr.second == name && curr.first > maxCountF) {
                maxYearF = y + 1880;
                maxCountF = curr.first;
                rankF = i + 1;
            }
        }
    }

    if (maxYearM == -1 && maxYearF == -1) { //not replaced so not found
        cout << name << " was not found." << endl;
    }
    else {
        if (maxYearM != -1)
        cout << name << " was most popular amongst males in " << maxYearM << " with " << maxCountM
            << " entries and was rank #" << rankM << endl;
        if (maxYearF != -1)
        cout << name << " was most popular amongst females in " << maxYearF << " with " << maxCountF
             << " entires and was rank #" << rankF << endl;
    }
}
