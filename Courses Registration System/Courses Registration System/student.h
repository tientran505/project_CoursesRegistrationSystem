#ifndef _STUDENT_H_
#define _STUDENT_H_
#include "function.h"

void loadStudentList(string path, _Student*& head);
void displayStudentList(string path, _Student* head);
void deleteStudentList(_Student*& head);
void convertAccountOfStudent(string path, _Student* head);
void logInSystem_Student(_Student* head);

<<<<<<< HEAD
struct Class {
	string Name_of_Subject; //ten mon hoc
	string ID_of_subject; //ma mon hoc
	int credit; // so tin chi
	string Name_of_Teacher;
};
struct Subjects {
	Class Subject; 
	bool registers; // 0: khong dang ki mon; 1: dang ki mon
	bool stranfer; // 0 khong doi lop; 1: co doi lop
	double score; // khong dang ki thi diem mac dinh -1; da dang ki thi co diem
	Subjects* pNext, * pPrevious;
};

struct Date {
	int day;
	int month;
	int year;
};
struct NodeStudent {
	int Number_In_Class; //so thu tu trong lop
	unsigned int ID;
	string Firstname;
	string Lastname;
	string Class_of_student; // lop cua sv
	string Gender; //gioi tinh
	unsigned int Social_ID;
	Date Date_Of_Birth;
	double gpa; //diem tong
	Subjects* y; //mon va diem theo mon
};

struct _NodeStudent {
	NodeStudent data;
	_NodeStudent* pNext, * pPrevious;
};
struct account {
	string id;
	string password;
};
void ReadStudent_CSV(const char* path, _NodeStudent*& students);
#endif // !FUNCTION_H_
