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
#include <stdio.h>
#include <conio.h>
using namespace std;

const string dir = "E:/HCMUS/Sem 2/Programming Techniques/Project - A Courses Registration System/project_CoursesRegistrationSystem/Courses Registration System/Courses Registration System/";
const string dirClass = "Class/";
const string dirCourse = "Course/";
const string dirRegis = "Registration/";
const string dirStaff = "Staff/";
const string dirCourse_Student = "Registration_Student/";
const string dirClass_Save = "Class_Save/";
const string dirSchoolYear = "School Year/";


struct Date {
	int day;
	int month;
	int year;
};

struct Time {
	int hour, minute;
};

struct Session {
	string dayOfWeek;
	string session;
};

struct Course {
	string course_Name; //ten mon hoc
	string course_ID; //ma mon hoc
	int credit; // so tin chi
	wstring Name_of_Teacher;
	Session first_Session;
	Session second_Session;
};

struct Student_ScoreBoard {
	Course course_Data;
	double score;
	string grade; // C- -> A+
};

struct _Student_ScoreBoard {
	Student_ScoreBoard data_ScoreBoard;
	_Student_ScoreBoard* dataNext;
};

struct node_Semester {
	Date start_Date; // start date of sem
	Date end_Date; // end date of sem
	int numOfSem; // 1,2,3
	int schoolYearCur; //2018-2019? 2019 - 2020
};

struct Subjects {
	Course course_Data;
	int number_Of_Student;
};

struct _Subjects {
	Subjects subjects_Data;
	node_Semester sem_Info;
	_Subjects* data_Next;
	_Subjects* data_Prev;
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
	_Student_ScoreBoard stu_Score;
	double GPA_Average;
	double score_Average;
	Account student_Account;
	int number_Of_Courses;
	int schoolYear;
};

struct _Student {
	Student data;
	_Subjects* subregis;
	_Student* pNext;
};

void currentDateTime();
wstring stringToWString(string str);
string WStringToString(wstring s);

void textcolor(int color);
void ShowCur(bool CursorVisibility);
void GotoXY(int x, int y);

void viewCourseList(string path);

void log_In_System(int x, int y);
int MainMenu(int x, int y);
void FixConsoleWindow();
int check_Line(string path);
int list_Len(_Subjects* Node);
void view_Reigstration_Results(_Subjects* Node);
#endif