#include "BuildConfig.h"
#include "PrettyPrint.h"


#ifdef PRE_RELEASE

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Generate the full name of a student.
string GetFullName(STUDENT_DATA student)
{
    return student.firstName + " " + student.lastName;
}

// Generate the section header.
string PrintHeader()
{
    return
        "\n==============================================\n"
        "       PRETTY PRINT - STUDENT DIRECTORY       \n"
        "==============================================\n\n";
}

// Sort students alphabetically by their entire name.
void SortStudents(vector<STUDENT_DATA>& students)
{
    for (int i = 0; i < students.size(); i++)
    {
        for (int j = 0; j < students.size() - i - 1; j++)
        {
            string name1 = GetFullName(students[j]);
            string name2 = GetFullName(students[j + 1]);

            if (name1 > name2)
            {
                STUDENT_DATA temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// Calculate the maximum column widths.
void CalculateColumnWidths(
    vector<STUDENT_DATA> students,
    int& firstNameWidth,
    int& lastNameWidth,
    int& emailLocalWidth)
{
    firstNameWidth = 0;
    lastNameWidth = 0;
    emailLocalWidth = 0;

    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].firstName.length() > firstNameWidth)
            firstNameWidth = students[i].firstName.length();

        if (students[i].lastName.length() > lastNameWidth)
            lastNameWidth = students[i].lastName.length();

        size_t position = students[i].emailId.find('@');
        string emailLocal = students[i].emailId.substr(0, position);

        if (emailLocal.length() > emailLocalWidth)
            emailLocalWidth = emailLocal.length();
    }
}

// Print one student record.
void PrintStudent(
    stringstream& output,
    STUDENT_DATA student,
    int firstNameWidth,
    int lastNameWidth,
    int emailLocalWidth)
{
    size_t position = student.emailId.find('@');

    string emailLocal = student.emailId.substr(0, position);
    string emailDomain = student.emailId.substr(position);

    output << left
        << setw(firstNameWidth + 4)
        << student.firstName;

    output << left
        << setw(lastNameWidth + 3)
        << student.lastName;

    output << "-->";

    output << right
        << setw(emailLocalWidth)
        << emailLocal;

    output << emailDomain << endl;
}

// Generate the section footer.
string PrintFooter()
{
    return
        "\n==============================================\n"
        "          END OF STUDENT DIRECTORY            \n"
        "==============================================\n";
}

// Generate the complete formatted output.
string FormatStudents(vector<STUDENT_DATA> students)
{
    stringstream output;

    int firstNameWidth;
    int lastNameWidth;
    int emailLocalWidth;

    output << PrintHeader();

    SortStudents(students);

    CalculateColumnWidths(
        students,
        firstNameWidth,
        lastNameWidth,
        emailLocalWidth);

    for (int i = 0; i < students.size(); i++)
    {
        PrintStudent(
            output,
            students[i],
            firstNameWidth,
            lastNameWidth,
            emailLocalWidth);
    }

    output << PrintFooter();

    return output.str();
}

// Display the formatted student directory.
void PrettyPrint(vector<STUDENT_DATA> students)
{
    cout << FormatStudents(students);
}

#endif // PRE_RELEASE
