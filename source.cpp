// Assignment2 – Debugging.cpp : This file contains the 'main' function.
// Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "BuildConfig.h"
#include "StudentData.h"
#include "PrettyPrint.h"


using namespace std;

// Remove newlines and other control characters so user input cannot forge log lines.
static string SanitizeForLog(const string& value)
{
    string cleaned;
    for (char c : value)
    {
        unsigned char u = static_cast<unsigned char>(c);
        if (u >= 32 && u != 127)
            cleaned += c;
    }
    return cleaned;
}

int main()
{
#ifdef PRE_RELEASE

    cout << "The application is running pre-release source code\n" << endl;

#else

    cout << "The application is running standard source code\n" << endl;

#endif

    vector<STUDENT_DATA> students;

#ifdef PRE_RELEASE

    ifstream inputFile("StudentData_Emails.txt");
    if (!inputFile)
    {
        cout << "Error opening StudentData_Emails.txt" << endl;
        return 1;
    }

#else

    ifstream inputFile("StudentData.txt");
    if (!inputFile)
    {
        cout << "Error opening StudentData.txt" << endl;
        return 1;
    }

#endif

    string line;

    while (getline(inputFile, line))
    {
        if (line.empty())
            continue;

        string lastName;
        string firstName;
        string email;

        stringstream ss(line);

#ifdef PRE_RELEASE

        getline(ss, lastName, ',');
        getline(ss, firstName, ',');
        getline(ss, email);

#else

        getline(ss, lastName, ',');
        getline(ss, firstName);

#endif

        if (!firstName.empty() && firstName[0] == ' ')
        {
            firstName.erase(0, 1);
        }

        STUDENT_DATA student;
        student.firstName = firstName;
        student.lastName = lastName;

#ifdef PRE_RELEASE
        student.emailId = email;
#endif

        students.push_back(student);

#ifdef _DEBUG

#ifdef PRE_RELEASE

        cout << SanitizeForLog(firstName) << ","
             << SanitizeForLog(lastName) << ","
             << SanitizeForLog(email) << endl;

#else

        cout << SanitizeForLog(firstName) << ","
             << SanitizeForLog(lastName) << endl;

#endif

#endif
    }

    inputFile.close();

#ifndef _DEBUG
#ifdef PRE_RELEASE
    PrettyPrint(students);
#endif
#endif

    return 0;
}
