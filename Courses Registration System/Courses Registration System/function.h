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

//const string dir = "E:/HCMUS/Sem 2/Programming Techniques/Project - A Courses Registration System/project_CoursesRegistrationSystem/Courses Registration System/Courses Registration System/";
const string dirClass = "Class\\";
const string dirCourse = "Course\\";
const string dirRegis = "Registration\\";
const string dirStaff = "Staff\\";
const string dirCourse_Student = "Registration_Student\\";
const string dirClass_Save = "Class_Save\\";
const string dirSchoolYear = "School Year\\";


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

struct scoreBoard {
	bool isScore = false;
	float finalMark;
	float totalMark;
	float midtermMark;
	float otherMark;
};

struct Course {
	string course_Name; //ten mon hoc
	string course_ID; //ma mon hoc
	int credit; // so tin chi
	wstring Name_of_Teacher;
	Session first_Session;
	Session second_Session;
	int semNo;
	string schoolYear;
	scoreBoard score;
};

struct Subjects {
	Course course_Data;
	int number_Of_Student;
};

struct _Subjects {
	Subjects subjects_Data;
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
void view_Reigstration_Results(_Subjects* Node, string schoolyear, int sem);
int list_Len_Available_Score(_Subjects* Node, string schoolyear, int semCur);
#endif