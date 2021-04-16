#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <iostream>
#include <fcntl.h>
#include <fstream>
#include <io.h>
#include <codecvt>
#include <string>
#include <locale>
#include <ctime>
#include <windows.h>

using namespace std;

const string dir = "E:/HCMUS/Sem 2/Programming Techniques/Project - A Courses Registration System/project_CoursesRegistrationSystem/Courses Registration System/Courses Registration System/";
const string dirClass = "Class/";
const string dirCourse = "Course/";
const string dirRegis = "Registration/";
const string dirStaff = "Staff/";
const string dirCourse_Student = "Registration_Student/";



struct Date {
	int day;
	int month;
	int year;
};

struct Time {
	int hour, minute;
};

struct Student_Schedule {
	Date date_Sched;
	Time time_Sched;
};

struct Course {
	int number_Order_Course;
	string course_Name; //ten mon hoc
	string course_ID; //ma mon hoc
	int credit; // so tin chi
	wstring Name_of_Teacher;
};

struct Student_ScoreBoard {
	Course course_Data;
	double total_Mark;
	double final_Mark;
	double midterm_Mark;
	double GPA;
	string grade; // C- -> A+
};

struct _Student_ScoreBoard {
	Student_ScoreBoard data_ScoreBoard;
	_Student_ScoreBoard* dataNext;
};

struct Subjects {
	Course course_Data;
	int number_Of_Student;
	int session;
	Student_Schedule study_Schedule;
};

struct _Subjects {
	Subjects subjects_Data;
	_Subjects* data_Next;
};

struct Account {
	string ID;
	string password;
};

struct Student {
	int Number_In_Class; //so thu tu trong lop
	int ID_Student;
	wstring firstName;
	wstring lastName;
	string class_Of_Student; // lop cua sv
	wstring gender; //gioi tinh
	int Social_ID;
	Date Date_Of_Birth;
	string email_Student;
	_Student_ScoreBoard stu_Score;
	double GPA_Average;
	double score_Average;
	Account student_Account;
	_Subjects* subregis;
};

struct _Student {
	Student data;
	_Student* pNext;
};

struct subject {
	string title;
	string IDsubject;
};

void currentDateTime();
wstring stringToWString(string str);
string WStringToString(wstring s);
void viewCourseList(string path);
void log_In_System(int x, int y);
void MainMenu(int x, int y);
void FixConsoleWindow();
#endif