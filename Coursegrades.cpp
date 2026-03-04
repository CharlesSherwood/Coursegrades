/*FileName:Coursegrades.cpp
Programmer Name:Charles Sherwood 
Date:03/03/2026
Requirements:This program should reasds grade data from
a file and dynamically allocates the memory to store student records and test
scores calculates the averages and assigns letter grades and 
output a formatted course grade report
*/

#include <iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;

//Create Struct
struct Student
{
	string lastName;
	int studentID;
	double* testScores;
	double average;
	char letterGrade;
};

//Create Prototypes 
bool ReadFile(const string& filename, Student*& students,
    int& numStudents, int& numTests);
void CalculateAverages(Student* students, int numStudents, int numTests);
void AssignLetterGrades(Student* students, int numStudents);
void PrintReport(const Student* students, int numStudents, int numTests);
void DeallocateMemory(Student*& students, int numStudents);

int main()
{
    string filename;
    Student* students = nullptr;
    int numStudents = 0;
    int numTests = 0;

    //Get gilename from user using getline to account for spaces 
    cout << "Enter input filename: ";
    getline(cin, filename);

    if (!ReadFile(filename, students, numStudents, numTests))
    {
        cout << "Error opening file.\n";
        return 1;
    }

    CalculateAverages(students, numStudents, numTests);
    AssignLetterGrades(students, numStudents);
    PrintReport(students, numStudents, numTests);
    DeallocateMemory(students, numStudents);

    return 0;
}


bool ReadFile(const string& filename, Student*& students,
    int& numStudents, int& numTests)
{
    ifstream infile(filename);

    if (!infile)
        return false;

    // Read header
    infile >> numStudents >> numTests;

    // Allocate student array
    students = new Student[numStudents];

    for (int i = 0; i < numStudents; i++)
    {
        infile >> students[i].lastName;
        infile >> students[i].studentID;

        // Allocate test scores array for each student
        students[i].testScores = new double[numTests];

        for (int j = 0; j < numTests; j++)
        {
            infile >> students[i].testScores[j];
        }

        students[i].average = 0.0;
        students[i].letterGrade = 'F';
    }

    infile.close();
    return true;
}

void CalculateAverages(Student* students, int numStudents, int numTests)
{
    for (int i=0; i < numStudents; i++)
    {
        double sum = 0;
        for(int j=0;j<numTests;j++)
        {
            sum += students[i].testScores[j];
        }
        students[i].average = sum / numTests;
    }

}

void AssignLetterGrades(Student* students, int numStudents)
{
    for (int i = 0; i < numStudents; i++)
    {
           double avg = students[i].average;

           if (avg >= 90)
               students[i].letterGrade = 'A';
           else if (avg >= 80)
               students[i].letterGrade = 'B';
           else if (avg >= 70)
               students[i].letterGrade = 'C';
           else if (avg >= 60)
               students[i].letterGrade = 'D';
           else
               students[i].letterGrade = 'F';
    }
}

void PrintReport(const Student* students, int numStudents, int numTests)
{
    cout << "\nCOURSE GRADE REPORT\n";
    cout << "----------------------------------";
    cout << endl;

    cout << left << setw(15) << "Last Name" << setw(12) << "Student ID"
        << setw(10) << "Average" << setw(6) << "Grade" << endl;

    cout << "----------------------------------";
    cout << endl;

    for (int i=0; i < numStudents; i++)
    {
        cout << left << setw(15) << students[i].lastName << setw(12) << students[i].studentID
            << setw(10) << fixed << setprecision(2) << students[i].average
            << setw(6) << students[i].letterGrade << endl;
    }
cout <<"----------------------------------";
}

void DeallocateMemory(Student*& students, int numStudents)
{
    for (int i=0; i < numStudents; i++)
    {
        delete[] students[i].testScores;

    }
    delete[]students;
    students = nullptr;
}