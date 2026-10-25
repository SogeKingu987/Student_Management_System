#include "student.hpp" //simply imports the header file
#include <string> // import string library
#include <iomanip> // import input/output manipulators (width & alignment manipulators)
#include <fstream> // file manipulation library
#include <vector> // vector manipulation
#include <iostream> // input output tools like cin, cout, cerr
using namespace std; // to avoid using the hassle of std::cout and such

void printmenu(); // function for printing the menu, void is used because it is simple printing what i put in the code rather than output some data type
int promptmenu(int &menuselect); //function for prompting the user to select options.. int is used because it will return an int data type in menuselect variable

int main() {
    int i, menuselect; //simple initializing
    student s; // assigning a shortform so that i can easily use s.ID instead of student.ID
    vector<student> students; // students is an array of multiple student class. so... i can students.push_back(s)
    
    if(loadRecord(students) == true){ // loadRecord function is in the student.cpp. 
        cout << "\nFile Loaded Successfully"; // basically it returns bool based on the success of opening the csv.
    } // the funtion also loads csv data into the vector. so make sure to check it out

    else{
        cout << "\nFile Loading Failed";
        return 0;
    }

    int NextID = ProcessID(students); // this guy simply assigns the next available ID after extracting data from csv file so that there isnt an ID clash

    for(i = 0; menuselect != 4; i++){ // this loop checks the value of menuselect and keeps running as long as the value isnt 4
        printmenu(); // prints the menu
        promptmenu(menuselect); // prompts the user to select an option from the printed menu
        
        switch(menuselect){
            case 1:{ // case 1, add student
                bool continu = true; //a simple variable that will be used to decide whether to continue the loop depending on whether the user want to keep adding students in one go
                while (continu == true){ // see?
                    
                    addStudent(students, NextID); // calls the vector and the NextID prepared by the ProcessID function
                    cout << "\nDo you wish to add another student (Y/N) ?" << endl;
                    continuum(continu);
                }
            break;} // breaking here instantly shoots us out of the switch case, but still within the loop. so the loop checks for the menuselect value, determines that its not 4, and continues
              
            case 2 :{
                string nothin; // hahha.. this is the most useless variable i ever made
                viewstudents(students); // a function that prints all data in the vector in a very organised manner
                cout << "\n\nEnter Any Key to go back to Main Menu : "; // see i didnt want the case to break as soon as it prints what we wanted
                cin >> nothin;                                          // so... i used this so that the user and sit and read the printed contents before moving on
            break;}

            case 3 :{ // okay, so this case says "exit", so upon exit, i want this program to properly save things
                saveRecord(students); // that's the function

                if(saveRecord(students) == true){
                    cout << "\n Saved Successfully"; // so the funtion returns bool depending on save success, so when it succeeds, 
                    menuselect = 4;                  // i force it to end loop by setting menuselect to 4.. so that once we break, the loop does it's job
                }
                else{
                    cout << "\n Save Failed !"; 
                }
                break;
            }

    }
}}

void printmenu(){
    cout << "\n--------------------------------------------------------------------------------------";
    cout << "\n                          student Record Management System";
    cout << "\n--------------------------------------------------------------------------------------";
    cout << "\n 1. Add student";
    cout << "\n 2. View students";
    cout << "\n 3. Exit";
    cout << "\n--------------------------------------------------------------------------------------";
}

int promptmenu(int &menuselect){
    cout << "\nSelect an option (1 - 3) : ";
    cin >> menuselect; // user enters menuselect value
    return menuselect; // funtion returns the value
}

