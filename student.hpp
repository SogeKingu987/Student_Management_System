#pragma once // since we import this guy in two other files, pragma once just tells the program that this entire file only happens once
#include <string> // import string library
#include <vector> // vector manipulation
using namespace std; // to avoid using the hassle of std::cout and such

class student{ // class declaration
    public:
    string name;
    int ID;
    float marks;
};




void addStudent(vector<student> &students, int &NextID);
void viewstudents(const vector<student> &students);
char continuum(bool &continu);
bool saveRecord(const vector<student> &students);
int ProcessID(vector<student> &students);
bool loadRecord(vector<student> &students);
