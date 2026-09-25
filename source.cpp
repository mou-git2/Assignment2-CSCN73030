// Assignment2 – Debugging.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Struct to hold student information
struct STUDENT_DATA
{
    string firstName;
    string lastName;
};

int main()
{
    vector<STUDENT_DATA> students;

    ifstream inputFile("StudentData.txt");

    if (!inputFile)
    {
        cout << "Error opening StudentData.txt" << endl;
        return 1;
    }

    string line;

    while (getline(inputFile, line))
    {
        if (line.empty())
            continue;

        string lastName;
        string firstName;

        stringstream ss(line);

        getline(ss, lastName, ',');
        getline(ss, firstName);

        // Remove leading space from first name if present
        if (!firstName.empty() && firstName[0] == ' ')
        {
            firstName.erase(0, 1);
        }

        STUDENT_DATA student;
        student.firstName = firstName;
        student.lastName = lastName;

        students.push_back(student);


    }

    inputFile.close();

    return 0;
}