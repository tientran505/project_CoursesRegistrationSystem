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

using namespace std;

struct dateOfBirth {
	int day, month, year;
};

struct Student {
	int No;
	int studentID;
	wstring firstName;
	wstring lastName;
	wstring gender;
	dateOfBirth dob;
	int socialID;
};

struct StudentList {
	Student stu;
	StudentList* pNext;
};

void currentDateTime();

#endif