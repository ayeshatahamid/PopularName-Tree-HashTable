#include "Year.h"
#include "FileIO.cpp"
#include "HashTable.h"
#include "SplayTree.h"
#include <chrono>
#include <regex>
using namespace std;
using namespace chrono;

int main() {
    cout << " __      __       .__                                  __           " << endl;
    cout << R"(/  \    /  \ ____ |  |   ____  ____   _____   ____   _/  |_  ____   )" << endl;
    cout << R"(\   \/\/   // __ \|  | _/ ___\/  _ \ /     \_/ __ \  \   __\/  _ \  )" << endl;
    cout << R"( \        /\  ___/|  |_\  \__(  <_> )  Y Y  \  ___/   |  | (  <_> ) )" << endl;
    cout << R"(  \__/\  /  \___  >____/\___  >____/|__|_|  /\___  >  |__|  \____/  )" << endl;
    cout << R"(       \/       \/          \/            \/     \/                 )" << endl;
    cout << endl;
    cout << R"( _______                          __________                __      )" << endl;
    cout << R"( \      \ _____    _____   ____   \______   \_____    ____ |  | __  )" << endl;
    cout << R"( /   |   \\__  \  /     \_/ __ \   |       _/\__  \  /    \|  |/ /  )" << endl;
    cout << R"(/    |    \/ __ \|  Y Y  \  ___/   |    |   \ / __ \|   |  \    <   )" << endl;
    cout << R"(\____|__  (____  /__|_|  /\___  >  |____|_  /(____  /___|  /__|_ \  )" << endl;
    cout << R"(        \/     \/      \/     \/          \/      \/     \/     \/  )" << endl;
    cout << endl << "Loading data..." << endl << endl;

    FileInput f = FileInput("NationalNames.csv");
    
    HashTable hash;
    SplayTree splay;
    f.loadFromFile(hash, splay);

    regex nameRegex("[a-zA-Z]+"); //Name validation
    int option = 0;
    string input;

    while (option != 4) {
        cout << "Welcome to Name Rank!" << endl;
        cout << "1. Search by name" << endl;
        cout << "2. Search by year (1880 - 2014)" << endl;
        cout << "3. Top 10 Names by Count" << endl;
        cout << "4. Quit program" << endl;
        cout << endl << "What would you like to do?" << endl;
        cin >> option;

        while (option < 1 || option > 4) {
            cout << "Please select a valid menu option: ";
            cin >> option;
        }

        if (option == 1) {
            cout << "Please enter a name: ";
            cin >> input;
            cout << endl;

            while (!regex_match(input.begin(), input.end(), nameRegex)) {
                cout << "Please enter a valid name (letters only): ";
                cin >> input;
            }

            cout << "Splay Tree Results:" << endl;
            auto start = high_resolution_clock::now();
            splay.find(input);
            auto stop = high_resolution_clock::now();
            auto splayDuration = duration_cast<microseconds>(stop - start);

            cout << endl;

            cout << "Hash Table Results: " << endl;
            start = high_resolution_clock::now();
            hash.findName(input);
            stop = high_resolution_clock::now();
            auto hashDuration = duration_cast<microseconds>(stop - start);

            cout << endl << "Time to compute as Splay Tree: " << splayDuration.count() << " microseconds" << endl;
            cout << "Time to compute as Hash Table: " << hashDuration.count() << " microseconds" << endl << endl;

        } else if (option == 2) {
            do {
                cout << "Please enter a valid year: ";
                cin >> input;
                cout << endl;
            }while (stoi(input) < 1880 || stoi(input) > 2014);

            auto start = high_resolution_clock::now();
            auto target = splay.find(stoi(input));
            auto stop = high_resolution_clock::now();
            auto splayDuration = duration_cast<microseconds>(stop - start);

            start = high_resolution_clock::now();
            auto f = hash.findFemaleYear(stoi(input));
            auto m = hash.findMaleYear(stoi(input));
            stop = high_resolution_clock::now();
            auto hashDuration = duration_cast<microseconds>(stop - start);

            //Print out results
            cout << left << setw(20) << "Splay Tree" << '|';
            cout << right << setw(22) << "Hash Table" << endl;
            cout << setw(44) << setfill('-') << '-' << endl;
            cout << setfill(' ');

            cout << "------The Top 10 Female Names of " << input << "------" << endl;
            int count = 0;
            for (auto i = f.begin(); i != f.end(); i++) {
                target->year.sortNames();
                string print = to_string(count + 1) + ". " + target->year.returnFemale()[count].second;
                cout << left << setw(20) << print << '|'; //splay
                print = to_string(count + 1) + ". " + i->second;
                cout << setw(10) << setfill(' ') << ' ';
                cout << left << setw(16) << print << endl; //hash
                count++;
            }

            cout << "-------The Top 10 Male Names of " << input << "-------" << endl;
            count = 0;
            for (auto i = m.begin(); i != m.end(); i++) {
                string print = to_string(count + 1) + ". " + target->year.returnMale()[count].second;
                cout << left << setw(20) << print << '|'; //splay
                print = to_string(count + 1) + ". " + i->second;
                cout << setw(10) << setfill(' ') << ' ';
                cout << left << setw(16) << print << endl; //hash
                count++;
            }

            cout << endl << "Time to compute as Splay Tree: " << splayDuration.count() << " microseconds" << endl;
            cout << "Time to compute as Hash Table: " << hashDuration.count() << " microseconds" << endl << endl;

        } else if (option == 3) {
            auto start = high_resolution_clock::now();
            auto splayTen = splay.findTop10();
            auto stop = high_resolution_clock::now();
            auto splayDuration = duration_cast<microseconds>(stop - start);

            cout << endl;

            //HASHTABLE IMPLEMENTATION
            start = high_resolution_clock::now();
            auto hash10F = hash.findTopFemale();
            auto hash10M = hash.findTopMale();
            stop = high_resolution_clock::now();
            auto hashDuration = duration_cast<microseconds>(stop - start);

            cout << left << setw(32) << "Splay Tree" << '|';
            cout << right << setw(30) << "Hash Table" << endl;
            cout << setw(64) << setfill('-') << '-' << endl;
            cout << setfill(' ');

            //PRINT OUT RESULTS
            cout << "------------The Top 10 Female Names of All Time------------"<< endl;
            for(int i = 0; i < 10; i++){
                string temp = to_string(i+1) + ". " + splayTen.second[i].first.second + " in " + to_string(splayTen.second[i].second) +
                        " with " + to_string(splayTen.second[i].first.first);
                cout << left << setw(30) << temp << '|';
                cout << setw(5) << setfill(' ') << ' ';
                temp = to_string(i+1) + ". " + get<1>(hash10F[i]) + " in " + to_string(get<2>(hash10F[i]) + 1880) +
                        " with " + to_string(get<0>(hash10F[i]));
                cout << left << setw(30) << temp << endl;
            }

            cout << "-----------The Top 10 Male Names of All Time------------"<< endl;
            for(int i = 0; i < 10; i++){
                string temp = to_string(i+1) + ". " + splayTen.first[i].first.second + " in " + to_string(splayTen.first[i].second) +
                              " with " + to_string(splayTen.first[i].first.first);
                cout << left << setw(30) << temp << '|';
                cout << setw(5) << setfill(' ') << ' ';
                temp = to_string(i+1) + ". " + get<1>(hash10M[i]) + " in " + to_string(get<2>(hash10M[i]) + 1880) +
                       " with " + to_string(get<0>(hash10M[i]));
                cout << left << setw(20) << temp << endl;
            }

            cout << endl << "Time to compute as Splay Tree: " << splayDuration.count() << " microseconds" << endl;
            cout << "Time to compute as Hash Table: " << hashDuration.count() << " microseconds" << endl << endl;
        }
        else if (option == 4) {
            cout << "Thanks for using Name Rank! Goodbye!" << endl;
            cout << R"(     _____)                          /  )" << endl;
            cout << R"(   /                /) /)           /   )" << endl;
            cout << R"(  /   ___   _______(/ (/_      _   /    )" << endl;
            cout << R"( /     / ) (_)(_)(_(_/_) (_/__(/_ o     )" << endl;
            cout << R"((____ /                 .-/             )" << endl;
            cout << R"(                      (_/              )" << endl;

            break;
        }
    }
};
