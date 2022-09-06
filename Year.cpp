#include "Year.h"

//Default constructor
Year::Year(){
    year = 0;
}

//Creates Year with the passed in value for year
Year::Year(unsigned int year) {
    this->year = year;
}

//Adds a name to the Year's correct vector
void Year::addName(bool isFemale, unsigned int count, string name) {
    if (isFemale) {
        female.push_back(make_pair(count, name));
    }else {
        male.push_back(make_pair(count, name));
    }
}

//Returns a Year
unsigned int Year::getYear() {
    return year;
}

//Returns entire vector of male names
vector<pair<unsigned int,string>> Year::returnMale() {
    return male;
}

//Returns entire vector of female names
vector<pair<unsigned int,string>> Year::returnFemale() {
    return female;
}

//Returns vector of top 10 female names
vector<pair<unsigned int, string>> Year::topTenFemale(){
    vector<pair<unsigned int, string>> top10;
    for(int i = 0; i < 10; i++){
        top10.push_back(female[i]);
    }
    return top10;
}

//Returns vector of top 10 male names
vector<pair<unsigned int, string>> Year::topTenMale(){
    vector<pair<unsigned int, string>> top10;
    for(int i = 0; i < 10; i++){
        top10.push_back(male[i]);
    }
    return top10;
}

//Sorts both name vectors by descending name counts
void Year::sortNames() {
    sort(female.begin(), female.end(), greater<pair<unsigned int, string>>());
    sort(male.begin(), male.end(), greater<pair<unsigned int, string>>());
}

//Checks if a name is in either male or female list for that year
bool Year::isInVector(string name){
    for(int i = 0; i < male.size(); i++){
        if(male[i].second == name){
            return true;
        }
    }
    for(int i = 0; i < female.size(); i++){
        if(female[i].second == name){
            return true;
        }
    }
    return false;

}

//Returns rank/count of a name in both male/female lists
pair<pair<unsigned int, unsigned int>,pair<unsigned int, unsigned int>> Year::rankOfName(string name) {

    pair<pair<unsigned int, unsigned int>,pair<unsigned int, unsigned int>> result;

    pair<unsigned int, unsigned int> femaleRank = make_pair(0,0); //Rank, count
    pair<unsigned int, unsigned int> maleRank = make_pair(0,0);

    for (int i = 0; i < female.size(); ++i) {
        if (female[i].second == name) {
            femaleRank = make_pair(i + 1, female[i].first);
        }
    }

    for (int i = 0; i < male.size(); ++i) {
        if (male[i].second == name) {
            maleRank = make_pair(i + 1, male[i].first);
        }
    }

    result = make_pair(femaleRank, maleRank);

    return result;
}

//Returns rank/count of a name in male list
pair<unsigned int, unsigned int> Year::rankOfMaleName(string name){
    pair<unsigned int, unsigned int> maleRank = make_pair(0,0);
    for (int i = 0; i < male.size(); ++i) {
        if (male[i].second == name) {
            maleRank = make_pair(i + 1, male[i].first);
        }
    }
    return maleRank;
}

//Returns rank/count of a name in female list
pair<unsigned int, unsigned int> Year::rankOfFemaleName(string name){
    pair<unsigned int, unsigned int> femaleRank = make_pair(0,0);
    for (int i = 0; i < female.size(); ++i) {
        if (female[i].second == name) {
            femaleRank = make_pair(i + 1, female[i].first);
        }
    }
    return femaleRank;
}

//Prints the number of male/female names in the respective lists
void Year::printListSizes() {
    cout << female.size() << " female names and " << male.size() << " male names for " << year << "." << endl;
}

//Prints top [number] names from both lists
void Year::printTop(int number) {
    cout << "The top " << number << " female names of " << year << " are: " << endl;

    for (int i = 0; i < number; ++i) {
        cout << i + 1 << ". " << female[i].second << endl;
    }

    cout << "The top " << number << " male names of " << year << " are: " << endl;

    for (int i = 0; i < number; ++i) {
        cout << i + 1 << ". " << male[i].second << endl;
    }
}
