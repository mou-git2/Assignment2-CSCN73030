// Assignment2 – Debugging.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#define PRE_RELEASE 

using namespace std;

// Struct to hold student information
#ifdef PRE_RELEASE

struct STUDENT_DATA
{
    string firstName;
    string lastName;
    string emailId;
};

#else
struct STUDENT_DATA
{
    string firstName;
    string lastName;
};
#endif

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

#endif // PRE_RELEASE

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
        cout << firstName << ","
            << lastName << ","
            << email << endl;
#else
        cout << firstName << ","
            << lastName << endl;
#endif

#endif
    }

    inputFile.close();

    return 0;
}