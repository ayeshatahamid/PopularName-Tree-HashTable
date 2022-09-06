#include <iostream>
#include "HashTable.h"
#include "SplayTree.h"
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

class FileInput {
    string filename;
public:
    //Based on: https://www.geeksforgeeks.org/csv-file-management-using-c/
    FileInput(string filename) {
        this->filename = filename;
    }

    void loadFromFile(HashTable& hash, SplayTree& splay) {
        ifstream file(filename);
        unsigned int currentYear = 1880;
        unsigned year, count;
        string line, name, gender, temp;
        Year currentObject = Year(1880);

        if (file.is_open()) {

            getline(file, line); //Gets rid of header

            while (getline(file, line)) {
                stringstream s(line);

                getline(s, name, ','); //ID
                getline(s, name, ','); //Name
                getline(s, temp, ','); //Year
                year = stoi(temp);
                getline(s, gender, ','); //Gender
                getline(s, temp, ','); //Count
                count = stoi(temp);

                if (currentYear == year) { //Next line is still for same year
                    //add to current year object
                    if(gender == "F") {
                        currentObject.addName(true, count, name);
                    }else {
                        currentObject.addName(false, count, name);
                    }
                }else {
                    //Adds to Splay Tree/Hash Table after sorting
                    currentObject.sortNames();
                    hash.insert(currentObject);
                    splay.insert(currentObject);
                    //create new year object
                    currentObject = Year(year);
                    currentYear = year;
                    //add to year object
                    if(gender == "F") {
                        currentObject.addName(true, count, name);
                    }else {
                        currentObject.addName(false, count, name);
                    }
                }
            }
            //Adds very last object from file
            hash.insert(currentObject);
            splay.insert(currentObject);
        }
    }
};