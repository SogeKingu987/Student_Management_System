#include "student.hpp" //simply imports the header file
#include <iostream> // input output tools like cin, cout, cerr
#include <fstream> // file manipulation library
#include <iomanip> // import input/output manipulators (width & alignment manipulators)
#include <limits> // provides information about the limits of a numeric type
#include <vector> // vector manipulation
using namespace std; // to avoid using the hassle of std::cout and such

void addStudent(vector<student> &students, int &NextID){
    student s;
    s.ID = NextID; // auto assign ID
    cout << "Enter the name of the student : ";
    cin.ignore(); //kinda ignores the spaces in an input (Very useful for students with a first name and a second name... duh)
    getline(cin,s.name); //orders the program to fetch the entire line of the input and save it to s.name

    while(true){ //more like an input validation thingy
        cout << "Enter the marks : ";
        cin >> s.marks;
        if(cin.fail()){ // triggered if the input is of a wrong data type
            cout << "invalid inpuit! Please enter a number. \n"; // error message
            cin.clear(); // clears the input so that the error doesnt keep triggering infinitely
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // makes sure the entire line is cleared instead of one character at a time
            continue; // continue loop
        }
        break; // if a fail isnt detected, exit loop
    }
    students.push_back(s); // save the entire record to a row of the vector and move on
    NextID++; // sets the next candidate for a new ID
}

int ProcessID(vector<student> &students){
    int MaxID, NextID;

    if(students.empty()){ // check if the vector is empty
        NextID = 1001; // set the ID to the default first value
        return NextID; // exit function with the assigned value of NextID
    }

    MaxID = students[0].ID; // initialize the first ID of the Vector to MaxID so we can work through later

    for(const student &s : students){ // kinda helps to run through the entire vector
        if(s.ID > MaxID){ // basic maximum finding loop
            MaxID = s.ID;
        }
    }

    NextID = MaxID + 1; // now that we know the laatest existing ID, we simply do +1 to determine the next ID
    return NextID; // return value
}

char continuum(bool &continu){ // this entire funtion is simply assigning true or false values to y and n
    char c;
    cin >> c;

    switch(c){
        case 'y' :
            continu = true;
            break;
        case 'Y' : 
            continu = true;
            break;
        case 'N' :
            continu = false;
            break;
        case 'n' :
            continu = false;
            break;
    }
    return continu;
}

void viewstudents(const vector<student> &students){
    if(students.size() == 0){ // checks if the vector is empty
        cout << "\n***** No students currently exist in the records. Please add students first *****";
    }
    else{
        cout << "\n--------------------------------------------------------------------------";
        cout << "\n                          student Records";
        cout << "\n--------------------------------------------------------------------------\n";
        cout << left // align left
             << setw(15) << "ID"
             << setw(35) << "name"
             << setw(30) << "marks";
        cout << "\n--------------------------------------------------------------------------\n";

        for(const student &s: students){
            cout << left
                 << setw(15) << s.ID
                 << setw(35) << s.name 
                 << setw(30) << s.marks
                 << endl;
        }
        cout << "--------------------------------------------------------------------------\n";
    }

}

bool saveRecord(const vector<student> &students){
        ofstream file("student_record.csv"); // output file stream

        if(!file){ 
            cout << "\nError opening file !";
            return false;
        }

        file << "ID,Name,Marks\n"; // header input
        for(const student &s : students)
        {
            file << s.ID << ",";
            file << s.name<< ",";
            file << s.marks << "\n";
        }

        file.close();
        return true;
    }

bool loadRecord(vector<student> &students){
    student s;
    int location = 0;
    string line ="";
    ifstream file("student_record.csv");

    if(!file){
        cout << "\nError opening file !";
        return false;
    }

    getline(file,line); // generally used to fetch a line and save it to variable "line". used here to fetch the headers, do nothing about it
    while(getline(file,line)){ // when used again, it has already moved on to the next line.. OR ... the actual data right after the header
        
        location = line.find(','); // find the first comma in the line and assigns a numerical value 
        s.ID = stoi(line.substr(0,location)); // gets all data from index 0 - index (location) and saves it to s.ID
        line = line.substr(location+1, line.length()); // the remaining part of the line is saved to ovewrite "line"

        location = line.find(','); // repeating this will help us find the next comma
        s.name = line.substr(0,location); // same saving but "stoi" isnt used here, cuz its a string all the same.. stoi is for string to integer conversion
        line = line.substr(location+1, line.length()); // remaining part overwritten over "line"

        s.marks = stof(line); // remaining is saved to s.marks with string to float conversion using stof

        students.push_back(s); // entire record saved into vector

    } // the entire loop will end once getline determines that there is no more to fetch

    file.close();
    return true;
}
