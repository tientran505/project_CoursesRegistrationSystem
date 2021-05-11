#include "function.h"

struct Date {
	int day, month, year;
};

//struct cho nam hoc vd: nam 2019, 2020
struct _Schoolyear {
	_Semester data;
	_Schoolyear* pNext;
};


//hoc ki
struct _Semester {       
	Date Start_Day;
	Date End_Day;
	_Year data;
	_Semester *pNext;

};


// hoc sinh nam 1 nam 2 nam 3 nam 4
struct _Year{
	_Course Course_Name;
	_Year* pNext;
};


struct _Course {
	bool regist;// 0 khong dang ki, 1// da dang ki 
	string Course_ID;    
	wstring Teacher_Name; 
	int Credits;   
	_session Time_of_Session;   

	int Max_Student_in_Class;   
	Teacher_ScoreBoard NameCourse_ScoreBoard; // cai nay bao gom student_scoreborad 
	_Course* pNext; //qua cac mon khac nhau
};


//thoi gian hoc
struct _session {
	string Day; //Mon Tue Wedn ...
	string hour;
	_session* pNext;
};

struct GPA {
	double GPA_semester;
	double GPA_overall;
};

struct Student {
	wstring FirstName;
	wstring LastName;
	unsigned int Student_ID; //use N > 0 for ID
	string Gender; //X or O
	unsigned int social_ID;
	Class Name_Of_Class;
	Date dob;
	_Course* Name_Of_Course; //truy cap vo teacher-scoreboard -> studentscoreboard de lay diem thanh phan
	//dung cho class:  lay bang diem cua lop, lay diem cuoi ki cua tat ca cac course trong semester
	GPA gpa; // cai nay thay doi theo hoc ki luon nen khong can thiet lap nam hoc, hoc ki, hoc sinh nam may;
};

struct Class {
	int num; //so thu tu sv trong lop
	_Student* pNext;
};
struct _Class {
	Class data;
	_Class* pNext;
};
struct _Student {
	Student data;
	_Student* pNext;
};
struct student_Scoreboard {
	double total_Mark;
	double final_Mark;
	double midterm_Mark;
	Other_Mark other_Mark;
	double gpa;
	string grade; // C->A+
};

struct Other_Mark {
	double data;
	Other_Mark* pNext;
};
struct _Student_Scoreboard {
	student_Scoreboard student;
	_Student_Scoreboard* pNext;
};

struct Teacher_ScoreBoard {
	int number;
	Student student;
	_Student_Scoreboard* student_score;
};

struct account {
	string id;
	string password;
};

