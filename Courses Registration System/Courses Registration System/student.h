#ifndef FUNCTION_H_
#define FUNCTION_H_

#include<iostream> 
using namespace std;

struct Class {
	wstring Name_of_Subject; //ten mon hoc
	string ID_of_subject; //ma mon hoc
	int credit; // so tin chi
	string schedule_theory;
	string schedule_lab;
	string Name_of_Teacher;
};
struct student_Scoreboard {
	double total_Mark;
	double final_Mark;
	double midterm_Mark;
	double gpa;
	string grade; // C->A+
};
struct Subjects {
	Class Subject; 
	bool registers; // 0: khong dang ki mon; 1: dang ki mon
	bool stranfer; // 0 khong doi lop; 1: co doi lop so voi lop duoc sap vao
	bool retake; // 0: khong hoc lai; 1: hoc lai
	student_Scoreboard score;
	int semester;
	int year;
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
	wstring Firstname;
	wstring Lastname;
	string Class_of_student; // lop cua sv
	string Gender; //gioi tinh
	unsigned int Social_ID;
	Date Date_Of_Birth;
	string email_Student;
	string email;
	string phone_number;
	double gpa; //diem tong
	Subjects y; //mon va diem theo mon
};

struct _NodeStudent {
	NodeStudent data;
	_NodeStudent* pNext, * pPrevious;
};
struct account {
	string id;
	string password;
};
#endif // !FUNCTION_H_
