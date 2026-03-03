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
    for (int i; i < numStudents; i++)
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

}

void DeallocateMemory(Student*& students, int numStudents)
{

}