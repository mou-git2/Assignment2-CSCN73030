#include "pch.h"
#include "CppUnitTest.h"
#include "../BuildConfig.h"
#include "../StudentData.h"
#include "../PrettyPrint.h"

#include <string>
#include <vector>

#ifndef PRE_RELEASE
#error PRE_RELEASE must be enabled to run these tests.
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace PrettyPrintNativeTests
{
    TEST_CLASS(PrettyPrintTests)
    {
    private:
        static string FindLine(const string& output, const string& searchText)
        {
            size_t position = output.find(searchText);

            if (position == string::npos)
                return "";

            size_t start = output.rfind('\n', position);
            if (start == string::npos)
                start = 0;
            else
                ++start;

            size_t end = output.find('\n', position);
            if (end == string::npos)
                end = output.length();

            return output.substr(start, end - start);
        }

    public:
        TEST_METHOD(StudentsAreSortedAlphabeticallyByFullName)
        {
            vector<STUDENT_DATA> students =
            {
                {"Ryan", "Wallace", "rwallace@example.com"},
                {"Alistair", "Campbell", "acampbell@example.com"},
                {"Avaneesh", "Bhat", "abhat@example.com"},
                {"Bryan", "Antoniou", "bantoniou@example.com"}
            };

            string output = FormatStudents(students);

            size_t first = output.find("acampbell@example.com");
            size_t second = output.find("abhat@example.com");
            size_t third = output.find("bantoniou@example.com");
            size_t fourth = output.find("rwallace@example.com");

            Assert::IsTrue(
                first < second && second < third && third < fourth,
                L"Students should be sorted alphabetically by full name.");
        }

        TEST_METHOD(StudentsWithSameFirstNameAreSortedByLastName)
        {
            vector<STUDENT_DATA> students =
            {
                {"John", "Wilson", "jwilson@example.com"},
                {"John", "Anderson", "janderson@example.com"},
                {"John", "Brown", "jbrown@example.com"}
            };

            string output = FormatStudents(students);

            size_t first = output.find("janderson@example.com");
            size_t second = output.find("jbrown@example.com");
            size_t third = output.find("jwilson@example.com");

            Assert::IsTrue(
                first < second && second < third,
                L"Students with identical first names should be sorted by last name.");
        }

        TEST_METHOD(FirstNamesStartAtTheSameColumn)
        {
            vector<STUDENT_DATA> students =
            {
                {"Al", "Smith", "al@example.com"},
                {"Christopher", "Jones", "cjones@example.com"}
            };

            string output = FormatStudents(students);
            string firstLine = FindLine(output, "al@example.com");
            string secondLine = FindLine(output, "cjones@example.com");

            Assert::IsTrue(
                !firstLine.empty() && !secondLine.empty() &&
                firstLine.find("Al") == 0 && secondLine.find("Christopher") == 0,
                L"First names should start at the same column.");
        }

        TEST_METHOD(LastNamesStartAtTheSameColumn)
        {
            vector<STUDENT_DATA> students =
            {
                {"Al", "Smith", "al@example.com"},
                {"Christopher", "Jones", "cjones@example.com"}
            };

            string output = FormatStudents(students);
            string firstLine = FindLine(output, "al@example.com");
            string secondLine = FindLine(output, "cjones@example.com");

            size_t firstLastName = firstLine.find("Smith");
            size_t secondLastName = secondLine.find("Jones");

            Assert::IsTrue(
                !firstLine.empty() && !secondLine.empty() &&
                firstLastName == secondLastName,
                L"Last names should start at the same column.");
        }

        TEST_METHOD(EmailAddressesAreAlignedOnAtSign)
        {
            vector<STUDENT_DATA> students =
            {
                {"Al", "Smith", "al@example.com"},
                {"Christopher", "Jones", "christopherjones@example.com"},
                {"Ryan", "Brown", "rbrown@example.com"}
            };

            string output = FormatStudents(students);
            string firstLine = FindLine(output, "al@example.com");
            string secondLine = FindLine(output, "christopherjones@example.com");
            string thirdLine = FindLine(output, "rbrown@example.com");

            size_t firstAt = firstLine.find('@');
            size_t secondAt = secondLine.find('@');
            size_t thirdAt = thirdLine.find('@');

            Assert::IsTrue(
                firstAt != string::npos && firstAt == secondAt && secondAt == thirdAt,
                L"Email addresses should align on the @ character.");
        }

        TEST_METHOD(NameAndEmailAreSeparatedByArrow)
        {
            vector<STUDENT_DATA> students =
            {
                {"Al", "Smith", "al@example.com"}
            };

            string output = FormatStudents(students);

            Assert::IsTrue(
                output.find("-->") != string::npos,
                L"The name and email should be separated by -->.");
        }

        TEST_METHOD(EmptyCollectionProducesHeaderAndFooter)
        {
            vector<STUDENT_DATA> students;
            string output = FormatStudents(students);

            Assert::IsTrue(
                output.find("PRETTY PRINT") != string::npos &&
                output.find("END OF STUDENT DIRECTORY") != string::npos,
                L"An empty collection should still produce the header and footer.");
        }

        TEST_METHOD(SingleStudentIsFormattedCorrectly)
        {
            vector<STUDENT_DATA> students =
            {
                {"Moe", "Student", "moe@example.com"}
            };

            string output = FormatStudents(students);

            Assert::IsTrue(
                output.find("Moe") != string::npos &&
                output.find("Student") != string::npos &&
                output.find("moe@example.com") != string::npos,
                L"A single student should be formatted correctly.");
        }

        TEST_METHOD(LongNamesAndEmailAddressesAreNotTruncated)
        {
            vector<STUDENT_DATA> students =
            {
                {"Alexandria", "Montgomery", "alexandriamontgomery@example.com"},
                {"Jo", "Li", "joli@example.com"}
            };

            string output = FormatStudents(students);

            Assert::IsTrue(
                output.find("alexandriamontgomery@example.com") != string::npos &&
                output.find("Montgomery") != string::npos,
                L"Long names and email addresses should not be truncated.");
        }
    };
}
