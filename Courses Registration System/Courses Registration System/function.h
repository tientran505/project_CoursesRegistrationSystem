#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include "student.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

struct DATE {
	int date, month, year;
};

struct Student {
	int No;
	int studentID;
	char* firstName;
	char* lastName;
	char* gender;
	DATE dob;
};

struct Node {
	Student studentInfo;
	Node* pNext;
};

void currentDateTime();

#endif