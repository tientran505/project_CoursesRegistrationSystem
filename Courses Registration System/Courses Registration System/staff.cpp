#include "staff.h"
#include "student.h"
#include "function.h"
#include<conio.h>
string getSchoolYear(string path) {
	ifstream fileIn;
	fileIn.open(path, ios_base::in);

	string line;
	getline(fileIn, line, '-');
	fileIn.close();
	return line;
}

void loadStudentList(string path, _Student*& head) {
	head = nullptr;
	wifstream fileIn;
	fileIn.open(path, ios_base::in);
	ifstream read;
	if (!fileIn.is_open()) {
		cout << "File is not existed!" << endl;
		fileIn.close();
		return;
	}

	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	wchar_t a = ',', b = '/';
	_Student* pCur = head;
	path.erase(path.end() - 4, path.end());
	path.erase(path.begin(), path.begin() + dir.length() + dirClass.length());
	while (!fileIn.eof()) {
		if (head == nullptr) {
			head = new _Student;
			pCur = head;
		}
		else {
			pCur->pNext = new _Student;
			pCur = pCur->pNext;
		}
		fileIn >> pCur->data.Number_In_Class >> a;
		fileIn >> pCur->data.ID_Student >> a;
		getline(fileIn, pCur->data.firstName, a);
		getline(fileIn, pCur->data.lastName, a);
		getline(fileIn, pCur->data.gender, a);
		fileIn >> pCur->data.Date_Of_Birth.day >> b;
		fileIn >> pCur->data.Date_Of_Birth.month >> b;
		fileIn >> pCur->data.Date_Of_Birth.year >> a;
		fileIn >> pCur->data.Social_ID;
		pCur->data.class_Of_Student = path;
		pCur->data.number_Of_Courses = 0;
		pCur->subregis = nullptr;
		pCur->pNext = nullptr;
	}

	fileIn.close();
}

void loadStudentList_changedPassword(string path,string path_Course ,_Student*& head) {
	head = nullptr;
	wifstream fileIn;
	wifstream readCourse;

	fileIn.open(path, ios_base::in);
	readCourse.open(path_Course, ios_base::in);

	if (!fileIn.is_open()) {
		cout << "File is not found!" << endl;
		fileIn.close();
		return;
	}

	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	readCourse.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	wchar_t a = ',', b = '/';
	_Student* pCur = head;
	path.erase(path.end() - 4, path.end());
	path.erase(path.begin(), path.begin() + dir.length() + dirClass.length());

	ifstream read;
	read.open(dir + dirClass_Save + "save_Account_" + path + ".txt", ios_base::in);

	int stuID, numOfCourse;
	wstring line;

	while (!fileIn.eof()) {
		if (head == nullptr) {
			head = new _Student;
			pCur = head;
		}
		else {
			pCur->pNext = new _Student;
			pCur = pCur->pNext;
		}
		fileIn >> pCur->data.Number_In_Class >> a;
		fileIn >> pCur->data.ID_Student >> a;
		getline(fileIn, pCur->data.firstName, a);
		getline(fileIn, pCur->data.lastName, a);
		getline(fileIn, pCur->data.gender, a);
		fileIn >> pCur->data.Date_Of_Birth.day >> b;
		fileIn >> pCur->data.Date_Of_Birth.month >> b;
		fileIn >> pCur->data.Date_Of_Birth.year >> a;
		fileIn >> pCur->data.Social_ID;

		getline(read, pCur->data.student_Account.ID, ',');
		getline(read, pCur->data.student_Account.password);

		readCourse >> stuID >> a >> numOfCourse;
		getline(readCourse, line);

		pCur->subregis = nullptr;
		_Subjects* subCur = pCur->subregis;

		for (int i = 1; i <= numOfCourse; i++) {
			if (pCur->subregis == nullptr) {
				pCur->subregis = new _Subjects;
				subCur = pCur->subregis;
				subCur->data_Prev = nullptr;
			}
			else {
				subCur->data_Next = new _Subjects;
				subCur->data_Next->data_Prev = subCur;
				subCur = subCur->data_Next;
			}
			getline(readCourse, line, a);
			subCur->subjects_Data.course_Data.course_ID = WStringToString(line);
			getline(readCourse, line, a);
			subCur->subjects_Data.course_Data.course_Name = WStringToString(line);
			getline(readCourse, subCur->subjects_Data.course_Data.Name_of_Teacher, a);
			readCourse >> subCur->subjects_Data.course_Data.credit >> a;
			getline(readCourse, line, a);
			subCur->subjects_Data.course_Data.first_Session.dayOfWeek = WStringToString(line);
			getline(readCourse, line, a);
			subCur->subjects_Data.course_Data.first_Session.session = WStringToString(line);
			getline(readCourse, line, a);
			subCur->subjects_Data.course_Data.second_Session.dayOfWeek = WStringToString(line);
			getline(readCourse, line, a);
			subCur->subjects_Data.course_Data.second_Session.session = WStringToString(line);
			getline(readCourse, line, a);
			subCur->subjects_Data.course_Data.schoolYear = WStringToString(line);
			readCourse >> subCur->subjects_Data.course_Data.semNo;
			getline(readCourse, line);
			subCur->data_Next = nullptr;
		}
		pCur->data.class_Of_Student = path;
		pCur->pNext = nullptr;
	}
	fileIn.close();
	read.close();
}

void displayStudentList(string path, _Student* head) {
	wofstream fileOut;
	fileOut.open(path, ios_base::out);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	if (!fileOut.is_open()) {
		cout << "Cant creat file!" << endl;
		fileOut.close();
		return;
	}

	wstring strTmp;
	while (head->pNext != nullptr) {
		fileOut << head->data.Number_In_Class << ",";
		fileOut << head->data.ID_Student << ",";
		fileOut << head->data.firstName << ",";
		fileOut << head->data.lastName << ",";
		fileOut << head->data.gender << ",";
		fileOut << head->data.Date_Of_Birth.day << "/" << head->data.Date_Of_Birth.month << "/" << head->data.Date_Of_Birth.year << ",";
		fileOut << head->data.Social_ID << ",";
		wstring tmp = stringToWString(head->data.class_Of_Student);
		fileOut << tmp << endl;
		head = head->pNext;
	}

	fileOut.close();
}

void convertAccountOfStudent(string path, _Student* head) {
	ofstream fileOut;
	fileOut.open(path, ios_base::out);
	if (!fileOut.is_open()) {
		cout << "Can't creat file" << endl;
		fileOut.close();
		return;
	}

	_Student* pCur = head;
	while (pCur->pNext != nullptr) {
		pCur->data.student_Account.ID = to_string(pCur->data.ID_Student);
		string dayTmp = to_string(pCur->data.Date_Of_Birth.day);
		string monthTmp = to_string(pCur->data.Date_Of_Birth.month);
		string yearTmp = to_string(pCur->data.Date_Of_Birth.year);
		if (pCur->data.Date_Of_Birth.day < 10) {
			dayTmp = "0" + to_string(pCur->data.Date_Of_Birth.day);
		}
		if (pCur->data.Date_Of_Birth.month < 10) {
			monthTmp = "0" + to_string(pCur->data.Date_Of_Birth.month);
		}
		pCur->data.student_Account.password = dayTmp + monthTmp + yearTmp;
		fileOut << pCur->data.student_Account.ID << ",";
		fileOut << pCur->data.student_Account.password << endl;
		pCur = pCur->pNext;
	}

	fileOut.close();
}

void convertCourseOfStudent(string path, _Student* head) {
	ofstream fileOut;
	fileOut.open(path, ios_base::out);
	if (!fileOut.is_open()) {
		return;
	}

	_Student* pCur = head;
	while (pCur->pNext != nullptr) {
		if (pCur != head) fileOut << endl;
		fileOut << pCur->data.ID_Student << "," << list_Len(pCur->subregis);
		pCur = pCur->pNext;
	}
	fileOut.close();
}

void deleteStudentList(_Student*& head) {
	if (head == nullptr) return;
	_Student* cur = head;
	while (head != nullptr) {
		head = head->pNext;
		delete cur;
		cur = head;
	}
}

void listPush(_Student*& listStack, _Student* classPush) {
	if (classPush == nullptr) return;
	if (listStack == nullptr) {
		listStack = classPush;
		return;
	}
	_Student* pTmp = listStack;
	while (pTmp->pNext->pNext != nullptr) pTmp = pTmp->pNext;
	_Student* pJunk = pTmp->pNext;
	pTmp->pNext = classPush;
	delete pJunk;
}

bool is_Class_In_System(string path, string input) {
	ifstream line;
	line.open(path, ios_base::app);
	if (!line.is_open()) return true;
	string tmp;
	while (!line.eof()) {
		getline(line, tmp);
		if (input == tmp) {
			line.close();
			return false;
		}
	}
	line.close();
	return true;
}

void listStudents(_Student*& head) {
	string path;
	int i = 0;
	int temp;
	int n = 0;
	string menu[2] = { "Add First-year Student class", "Back" };
	_Student* headClass = nullptr;
	do {
		while (true) {
			system("cls");
			for (int j = 0; j < 2; j++) {
				if (n == j) {
					textcolor(12);
					GotoXY(39, 5 + j);
					cout << " > " << menu[j] << " < " << endl;
					textcolor(15);
				}
				else {
					textcolor(15);
					GotoXY(40, 5 + j);
					cout << " " << menu[j] << " " << endl;
				}
			}
			temp = _getch();
			if (temp == 's' || temp == 'S' || temp == 80) {
				n++;
				if (n == 2) n = 0;
			}
			if (temp == 'w' || temp == 'W' || temp == 72) {
				n--;
				if (n == -1) n = 1;
			}
			if (temp == 13 || temp == 32) break;
		}
		system("cls");
		if (n != 1) {
			cout << "Input name of Class to add into the system: ";
			cin >> path;
			ofstream fileOut;
			fileOut.open(dir + dirClass_Save + "classes_In_System.txt", ios_base::app);

			if (!is_Class_In_System(dir + dirClass_Save + "classes_In_System.txt", path)) {
				cout << path << " is already in system. Pls add another class" << endl;
				cout << " enter to continue";
				temp = _getch();
				continue;
			}

			loadStudentList(dir + dirClass + path + ".csv", headClass);
			displayStudentList(dir + dirClass + path + "_Info" + ".csv", headClass);
			listPush(head, headClass);
			fileOut << path << endl;
			fileOut.close();
			convertAccountOfStudent(dir + dirClass_Save + "save_Account_" + path + ".txt", headClass);
			convertCourseOfStudent(dir + dirCourse_Student + "Registered_Course_" + path + ".txt", headClass);
		}
	} while (n != 1);
}

void loadStu_Save(_Student*& pHead) {
	_Student* headClass = nullptr;
	ifstream read;
	read.open(dir + dirClass_Save + "classes_In_System.txt", ios_base::in);
	if (!read.is_open()) return;
	int line = check_Line(dir + dirClass_Save + "classes_In_System.txt");
	for (int i = 1; i <= line; i++)  {
		string path;
		getline(read, path);
		cout << "Added " << path << " in the system" << endl;
		loadStudentList_changedPassword(dir + dirClass + path + ".csv", dir + dirCourse_Student + "Registered_Course_" + path + ".txt",headClass);
		listPush(pHead, headClass);
		
	}
	read.close();
}

void staff_Login(string& username) {
	ifstream fileIn;
	int running = true;
	string password;
	int temp;
	string userTmp, passTmp;
	while (running) {
		GotoXY(37, 11);
		cout << "Username: ";
		cin >> username;
		GotoXY(37, 13);
		cout << "Password: ";
		cin >> password;

		fileIn.open(dir + dirStaff + "Staff_Account.txt", ios_base::in);
		while (!fileIn.eof()) {
			string userTmp, passTmp;
			getline(fileIn, userTmp, ',');
			getline(fileIn, passTmp);
			if (username == userTmp && passTmp == password) {
				running = false;
				break;
			}
		}
		if (!running) {
			system("cls");
			GotoXY(45, 11);
			cout << "Login Successfully!" << endl;
			Sleep(200);
			system("cls");
		}
		else {
			
			system("cls");
			GotoXY(40, 11);
			cout << "Invalid login, please try again" << endl;
			GotoXY(45, 13);
			cout << " (enter to return)"<<endl;
			temp = _getch();
			system("cls");
		}
		fileIn.close();
	}
}

void turnOnVietText() {
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
}

void turnOffVietText() {
	_setmode(_fileno(stdin), _O_TEXT);
	_setmode(_fileno(stdout), _O_TEXT);
}

int check_Line(string path) {
	ifstream f;
	f.open(path, ios_base::in);
	int lineCount = 0;
	string line;
	while (getline(f, line)) {
		lineCount++;
	}
	f.close();
	return lineCount;
}

void createCourseList(string path) {
	int running = true;
	wofstream fileOut;
	char* courseID, * courseName;
	wchar_t* teacherName;
	int credits;
	int maxStu;
	char* day1, * session1;
	char* day2, * session2;
	int choose;
	char sTmp[101];

	fileOut.open(path, ios_base::app);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	if (!fileOut.is_open()) {
		cout << "Can't create file" << endl;
		return;
	}

	int no = check_Line(path); 

	do {
		cout << "INFORMATION OF COURSE!" << endl;
		cout << "Course ID: ";
		cin.ignore(1000, '\n');
		cin.get(sTmp, 101, '\n');
		courseID = new char[strlen(sTmp) + 1];
		strcpy_s(courseID, strlen(sTmp) + 1, sTmp);

		
		cout << "Course Name: ";
		cin.ignore(1000, '\n');
		
		cin.get(sTmp, 101, '\n');
		courseName = new char[strlen(sTmp) + 1];
		strcpy_s(courseName, strlen(sTmp) + 1, sTmp);

		cout << "Teacher Name: ";
		turnOnVietText();
		cin.ignore(1000, '\n');
		wchar_t wsTmp[101];
		wcin.get(wsTmp, 101, '\n');
		teacherName = new wchar_t[wcslen(wsTmp) + 1];
		wcscpy_s(teacherName, wcslen(wsTmp) + 1, wsTmp);
		wcin.ignore(1000, '\n');
		turnOffVietText();

		cout << "Number of credits: ";
		cin >> credits;

		cout << "Maximum number of students in the course: ";
		cin >> maxStu;

		cout << "Day in week (MON / TUE / WED / THU / FRI / SAT): ";
		cin.ignore(1000, '\n');
		cin.get(sTmp, 101, '\n');
		day1 = new char[strlen(sTmp) + 1];
		strcpy_s(day1, strlen(sTmp) + 1, sTmp);
		
		cout << "The session of course (S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)): ";
		cin.ignore(1000, '\n');
		cin.get(sTmp, 101, '\n');
		session1 = new char[strlen(sTmp) + 1];
		strcpy_s(session1, strlen(sTmp) + 1, sTmp);
		
		cout << "Day in week (MON / TUE / WED / THU / FRI / SAT): ";
		cin.ignore(1000, '\n');
		cin.get(sTmp, 101, '\n');
		day2 = new char[strlen(sTmp) + 1];
		strcpy_s(day2, strlen(sTmp) + 1, sTmp);
		

		cout << "The session of course (S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)): ";
		cin.ignore(1000, '\n');
		cin.get(sTmp, 101, '\n');
		session2 = new char[strlen(sTmp) + 1];
		strcpy_s(session2, strlen(sTmp) + 1, sTmp);
		cin.ignore(1000, '\n');

		if (no != 0) fileOut << endl;
		fileOut << no + 1 << ",";
		fileOut << courseID << ",";
		_setmode(_fileno(stdout), _O_U16TEXT);
		fileOut << courseName << ",";
		fileOut << teacherName << ",";
		_setmode(_fileno(stdout), _O_TEXT);
		
		fileOut << credits << ",";
		fileOut << maxStu << ",";
		fileOut << day1 << "," << session1 << ",";
		fileOut << day2 << "," << session2;

		delete[] courseID;
		delete[] courseName;
		delete[] teacherName;
		delete[] day1;
		delete[] day2;
		delete[] session1;
		delete[] session2;
		
		cout << "Successfully! Course is created" << endl;

		cout << "-------------------\n1. Continue to create course." << endl;
		cout << "2. Exit" << endl;

		cin >> choose;
		if (choose == 1) {
			++no;
		}
		else running = false;
	} while (running);
	fileOut.close();
}

void viewCourseList(string path) {
	wifstream fileIn;
	fileIn.open(dir + dirCourse + "CoursesRegistration.txt", ios_base::in);

	if (!fileIn.is_open() || check_Line(path) == 0) {
		cout << "You haven't created any course yet. Please create the course first" << endl;
		fileIn.close();
		return;
	}

	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	cout << "VIEW LIST SYSTEM" << endl;
	while (!fileIn.eof()) {
		int no, credits, max;
		wstring d1, s1, d2, s2;
		wstring courseID, courseName;
		wstring teacherName;
		wchar_t a = ',';
		wstring junk;
		turnOnVietText();
		fileIn >> no >> a;
		getline(fileIn, courseID, a);
		getline(fileIn, courseName, a);
		getline(fileIn, teacherName, a);
		fileIn >> credits >> a;
		fileIn >> max >> a;
		getline(fileIn, d1, a);
		getline(fileIn, s1, a);
		getline(fileIn, d2, a);
		getline(fileIn, s2);
		turnOffVietText();
		_setmode(_fileno(stdout), _O_U8TEXT);
		wcout << no << " - " << courseID << " - " << courseName << endl;
		wcout << "Lecturer: " << teacherName << endl;
		wcout << "Credits: " << credits << endl;
		wcout << "Num of students: " << max << endl;
		wcout << "Schedule: " << d1 << " - " << s1 << ", " << d2 << " - " << s2 << endl;
		_setmode(_fileno(stdout), _O_TEXT);
		wcout << endl;
	}
	cout <<  "TOTAL OF COURSES: " << check_Line(path) << endl;
	cout << "=============================" << endl;
	
}

void update_Course_Info() {
	wifstream fileOld;
	wofstream fileNew;

	string dirOld = dir + dirCourse + "CoursesRegistration.txt";
	string dirNew = dir + dirCourse + "change.txt";

	fileOld.open(dirOld, ios_base::in);
	fileNew.open(dirNew, ios_base::out);

	fileOld.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	fileNew.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	viewCourseList(dirOld);
	wchar_t a = ',';
	cout << "Choose course to update: " << endl;
	int choose;
	cin >> choose;
	while (!fileOld.eof()) {
		int tmp;
		
		wstring junk;
		fileOld >> tmp >> a;
		

		if (tmp == choose) {
			fileNew << tmp << ",";
			break;
		}

		getline(fileOld, junk);
		fileNew << tmp << "," << junk << endl;
	}

	cout << "Choose the infomation of course to update" << endl;
	cout << "1. Course ID" << endl;
	cout << "2. Course Name" << endl;
	cout << "3. Teacher's name" << endl;
	cout << "4. Number of credits" << endl;
	cout << "5. Maximum number of students in course" << endl;
	cout << "6. Date and session" << endl;

	int change;
	cin >> change;
	switch (change)
	{
	case 1: {
		char sTmp[101];
		cout << "Enter new Course ID: ";
		cin.ignore(1000, '\n');
		cin.get(sTmp, 101, '\n');
		char* courseID = new char[strlen(sTmp) + 1];
		strcpy_s(courseID, strlen(sTmp) + 1, sTmp);
		fileNew << courseID << ",";
		wstring tmp, junk;
		getline(fileOld, tmp, a);
		while (!fileOld.eof()) {
			getline(fileOld, junk);
			fileNew << junk;
			if (!fileOld.eof()) fileNew << endl;
		}
		delete[] courseID;
		break;
	}

	case 2: {
		char sTmp[101];
		cout << "Enter new Course Name: ";
		cin.ignore(1000, '\n');
		cin.get(sTmp, 101, '\n');
		char* courseName = new char[strlen(sTmp) + 1];
		strcpy_s(courseName, strlen(sTmp) + 1, sTmp);
		wstring tmp;
		getline(fileOld, tmp, a);
		fileNew << tmp << "," << courseName << ",";
		wstring junk;
		getline(fileOld, tmp, a);
		while (!fileOld.eof()) {
			getline(fileOld, junk);
			fileNew << junk;
			if (!fileOld.eof()) fileNew << endl;
		}
		delete[] courseName;
		break;
	}

	case 3: {
		wchar_t sTmp[101];
		cout << "Enter new Teacher's name: ";
		turnOnVietText();
		cin.ignore(1000, '\n');
		wcin.get(sTmp, 101, '\n');
		wchar_t* teacherName = new wchar_t[wcslen(sTmp) + 1];
		wcscpy_s(teacherName, wcslen(sTmp) + 1, sTmp);
		wcin.ignore(1000, '\n');
		turnOffVietText();
		wstring tmp;
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		getline(fileOld, tmp, a);
		_setmode(_fileno(stdout), _O_U16TEXT);
		fileNew << tmp << "," << teacherName << ",";
		_setmode(_fileno(stdout), _O_TEXT);
		wstring junk;
		getline(fileOld, tmp, a);
		while (!fileOld.eof()) {
			getline(fileOld, junk);
			fileNew << junk;
			if (!fileOld.eof()) fileNew << endl;
		}
		delete[] teacherName;
		break;
	}

	case 4: {
		int credit;
		cout << "Enter new credits of course: ";
		cin >> credit;
		wstring tmp;
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		getline(fileOld, tmp, a);
		fileNew << tmp << "," << credit << ",";
		wstring junk;
		getline(fileOld, tmp, a);
		while (!fileOld.eof()) {
			getline(fileOld, junk);
			fileNew << junk;
			if (!fileOld.eof()) fileNew << endl;
		}
		break;
	}

	case 5: {
		cout << "Enter new maximum number of students in course: ";
		int num;
		cin >> num;
		wstring tmp;
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		int intTmp;
		fileOld >> intTmp >> a;
		fileNew << intTmp << "," << num << ",";
		wstring junk;
		getline(fileOld, tmp, a);
		while (!fileOld.eof()) {
			getline(fileOld, junk);
			fileNew << junk;
			if (!fileOld.eof()) fileNew << endl;
		}
		break;
	}

	case 6: {
		wstring d1, ss1, d2, ss2;
		cout << "Enter new date and session of this course" << endl;
		cout << "Day in week (MON / TUE / WED / THU / FRI / SAT): ";
		wcin >> d1;
		cout << "The session of course (S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)): ";
		wcin >> ss1;
		cout << "Day in week (MON / TUE / WED / THU / FRI / SAT): ";
		wcin >> d2;
		cout << "The session of course (S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)): ";
		wcin >> ss2;
		wstring tmp;
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		getline(fileOld, tmp, a);
		fileNew << tmp << ",";
		int intTmp;
		fileOld >> intTmp >> a;
		fileNew << intTmp << ",";
		fileOld >> intTmp >> a;
		fileNew << intTmp << "," << d1 << "," << ss1 << "," << d2 << "," << ss2 << endl;
		wstring junk;
		getline(fileOld, junk);
		while (!fileOld.eof()) {
			getline(fileOld, junk);
			fileNew << junk;
			if (!fileOld.eof()) fileNew << endl;
		}
		
		break;
	}
	default:
		break;
	}
	cout << "Infomation updated!" << endl;
	fileOld.close();
	fileNew.close();
	remove(dirOld.c_str());
	rename(dirNew.c_str(), dirOld.c_str());
//	remove("E:/HCMUS/Sem 2/Programming Techniques/Project - A Courses Registration System/project_CoursesRegistrationSystem/Courses Registration System/Courses Registration System/Course/CoursesRegistration.txt");
//	rename("E:/HCMUS/Sem 2/Programming Techniques/Project - A Courses Registration System/project_CoursesRegistrationSystem/Courses Registration System/Courses Registration System/Course/change.txt", "E:/HCMUS/Sem 2/Programming Techniques/Project - A Courses Registration System/project_CoursesRegistrationSystem/Courses Registration System/Courses Registration System/Course/CoursesRegistration.txt");
}

void delete_Courses() {
	wifstream fileOld;

	string dirFileOld = dir + dirCourse + "CoursesRegistration.txt";
	fileOld.open(dirFileOld, ios_base::in);
	int line = check_Line(dir + dirCourse + "CoursesRegistration.txt");

	if (!fileOld.is_open() || line == 0) {
		cout << "NOTHING TO DELETE!\n" << "================================================" << endl;
		fileOld.close();
		return;
	}

	wofstream fileNew;
	string dirFileNew = dir + dirCourse + "change.txt";
	fileNew.open(dirFileNew, ios_base::out);

	fileOld.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	fileNew.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	viewCourseList(dir + dirCourse + "CoursesRegistration.txt");
	wchar_t a = ',';
	cout << "TOTAL OF COURSES: " << line << endl;
	cout << "Choose course to delete: " << endl;
	int choose, count;
	cin >> choose;
	if (choose > line) {
		cout << "Your chosen course is exceed the number of courses! Please try again!" << endl << "===================================" << endl;
		fileOld.close();
		fileNew.close();
		return;
	}
	wstring junk;
	_setmode(_fileno(stdout), _O_U16TEXT);
	
	while (!fileOld.eof()) {
		fileOld >> count >> a;

		if (count == choose) break;

		getline(fileOld, junk);
		if (count != 1) fileNew << endl;
		fileNew << count << "," << junk;
	}

	getline(fileOld, junk);
	while (!fileOld.eof()) {
		fileOld >> count >> a;
		getline(fileOld, junk);
		if (count != 2) fileNew << endl;
		fileNew << count - 1 << "," << junk;
	}
	_setmode(_fileno(stdout), _O_TEXT);
	cout << "Successfully deleted the course!" << endl;

	fileOld.close();
	fileNew.close();
	remove(dirFileOld.c_str());
	rename(dirFileNew.c_str(), dirFileOld.c_str());
}

void showInfo_Staff(string username,int x,int y) {
	ifstream fileIn;
	fileIn.open(dir + dirStaff + "Staff_Info.txt", ios_base::in);
	while (!fileIn.eof()) {
		string tmp, name;
		getline(fileIn, tmp, ',');
		getline(fileIn, name);
		if (tmp == username) {
			GotoXY(x, y);
			cout << "Infomartion of staff" << endl;
			GotoXY(x, y+1);
			cout << "Name: " << name << endl;
			GotoXY(x, y+2);
			cout << "Department: Academic Staff" << endl;
			GotoXY(x, y+3);
			fileIn.close();
			
			return;
		}
	}
	cout << "Infomation of this staff is currently not existed in the system " << endl;
	fileIn.close();
}

void create_Course_Registration() {
	ofstream fileOut;
	bool running = true;

	fileOut.open(dir + dirRegis + "Registration.txt", ios_base::out);

	if (!fileOut.is_open()) {
		cout << "Can't create Courese Registration. Pls try again!" << endl;
		fileOut.close();
		return;
	}

	Date dayStart, dayEnd;
	int hourStart, hourEnd, minuteStart, minuteEnd;

	do {
		cout << "Input Date Course registration session is open (DD/MM/YYYY): ";
		cin >> dayStart.day;
		cin.ignore(10, '/');
		cin >> dayStart.month;
		cin.ignore(10, '/');
		cin >> dayStart.year;
		cout << "Time (24 Clock - HH:MM): ";
		cin >> hourStart;
		cin.ignore(10, ':');
		cin >> minuteStart;

		cout << "Input Date Course registration seesion is close (DD/MM/YYYY): ";
		cin >> dayEnd.day;
		cin.ignore(10, '/');
		cin >> dayEnd.month;
		cin.ignore(10, '/');
		cin >> dayEnd.year;
		cout << "Time (24h Clock - HH:MM): ";
		cin >> hourEnd;
		cin.ignore(10, ':');
		cin >> minuteEnd;

		string minuteTmp = to_string(minuteStart);
		if (minuteStart < 10) minuteTmp = "0" + minuteTmp;

		cout << "Pls confirm before creating registration session (Press Y to confirm, N to type again!" << endl;
		cout << "Start Date: " << dayStart.day << "/" << dayStart.month << "/" << dayStart.year << endl;
		cout << "Time: " << hourStart << ":" << minuteTmp << endl;

		string minuteTmp_End = to_string(minuteEnd);
		if (minuteEnd < 10) minuteTmp_End = "0" + minuteTmp_End;

		cout << "End Date: " << dayEnd.day << "/" << dayEnd.month << "/" << dayEnd.year << endl;
		cout << "Time: " << hourEnd << ":" << minuteTmp_End << endl;

		string choose;
		cout << "Confirm? ";
		cin >> choose;

		if (choose == "Y" || choose == "y") {
			cout << "Course Registration completely created!" << endl;

			fileOut << dayStart.day << "/" << dayStart.month << "/" << dayStart.year << ",";
			fileOut << hourStart << ":" << minuteTmp << endl;
			fileOut << dayEnd.day << "/" << dayEnd.month << "/" << dayEnd.year << ",";
			fileOut << hourEnd << ":" << minuteTmp_End;

			running = false;
		}
	} while (running);
	

	fileOut.close();
}

bool is_Created_Schoolyear_Before(string line) {
	ifstream read;
	read.open(dir + dirSchoolYear + "School_Year.txt", ios_base::in);

	if (!read.is_open()) return true;

	string check;

	while (!read.eof()) {
		getline(read, check, '-');
		if (check == line) {
			read.close();
			return false;
		}
		getline(read, check);
	}
	read.close();
	return true;
}

bool is_Created_Sem_Before(string line, string schoolyear) {
	ifstream read;
	read.open(dir + dirSchoolYear + schoolyear + ".txt", ios_base::out);

	string check;
	while (!read.eof()) {
		getline(read, check);
		if (line == check) {
			read.close();
			return false;
		}
		for (int i = 0; i < 2; i++) getline(read, check);
	}

	read.close();
	return true;
}

void arrange_Sem(string schoolyear, string sem) {
	ifstream read;
	ofstream fileNew;
	
	string oldName = dir + dirSchoolYear + schoolyear + ".txt";
	string newName = dir + dirSchoolYear + "tmp.txt";

	read.open(oldName, ios_base::in);
	fileNew.open(newName, ios_base::out);

	string check, line;
	while (!read.eof()) {
		getline(read, check);
		if (check == sem) {
			Date startDate, endDate;
			GotoXY(39, 16);
			cout << "Enter start date of " << sem << " (DD/MM/YYYY): ";
			cin >> startDate.day;
			cin.ignore(10, '/');
			cin >> startDate.month;
			cin.ignore(10, '/');
			cin >> startDate.year;
			GotoXY(39, 18);
			cout << "Enter end date of " << sem << " (DD/MM/YYYY): ";
			cin >> endDate.day;
			cin.ignore(10, '/');
			cin >> endDate.month;
			cin.ignore(10, '/');
			cin >> endDate.year;
			if (check_Line(newName) != 0) fileNew << endl;
			fileNew << sem << endl;
			fileNew << startDate.day << "/" << startDate.month << "/" << startDate.year << endl;
			fileNew << endDate.day << "/" << endDate.month << "/" << endDate.year;
			for (int i = 0; i < 2; i++) getline(read, line);
		}
		else {
			if (check_Line(newName) != 0) fileNew << endl;
			fileNew << check;
			for (int i = 0; i < 2; i++) {
				getline(read, line);
				fileNew << endl << line;
			}
		}
	}
	read.close();
	fileNew.close();
	remove(oldName.c_str());
	rename(newName.c_str(), oldName.c_str());
}

void add_Schoolyear(Date& schoolyear) {
	bool running = true;
	do {
		cout << "Input the schoolyear: ";
		int year;
		cin >> year;
		if (!is_Created_Schoolyear_Before(to_string(year))) {
			cout << "You have created school year " << to_string(year) << " before!" << endl;
			cout << "Press any key to continue or Esc to exit" << endl;
			int choose = _getch();
			if (choose == 27) return;
		}
		else {
			cout << "You mean " << year << "-" << year + 1 << "?";
			cout << "\nY. Yes \t N. No" << endl;
			string choose;
			cin >> choose;
			if (choose == "Y" || choose == "y") {
				ofstream out;
				ofstream outFile;
				outFile.open(dir + dirSchoolYear + "School_Year.txt", ios_base::app);
				out.open(dir + dirSchoolYear + to_string(year) + "-" + to_string(year + 1) + ".txt", ios_base::out);
				if (!out.is_open()) {
					cout << "Can't create School year!" << endl;
				}
				if (check_Line(dir + dirSchoolYear + "School_Year.txt") != 0) outFile << endl;
				outFile << year << "-" << year + 1;
				outFile.close();
				out.close();
				schoolyear.year = year;
				running = false;
			}
		}
	} while (running);
}

void create_Semester() {

}

void studentRegisterSub(_Student* head) {
	string sub;
	string cl;
	_Student* cur = head;
	cout << "Input the subject title: ";
	cin.ignore(1000, '\n');
	getline(cin, sub);
	cout << endl << "Input the class: ";
	cin.ignore(1000, '\n');
	getline(cin, cl);
	wifstream fileIn;
	wofstream fileOut;
	int count = 0;
	wchar_t a = ',';
	wstring dob;
	fileIn.open(cl + ".csv", ios_base::in);
	if (!fileIn.is_open()) return;
	fileOut.open(cl + "_" + sub + ".csv", ios_base::out);
	if (!fileOut.is_open()) return;
	fileOut << "No" << a << "ID" << a << "First Name" << a << "Last Name" << a << "Gender" << a << "Social ID" << endl;
	while (!fileIn.eof()) {
		while (cur != nullptr) {
			fileIn >> cur->data.Number_In_Class >> a >> cur->data.ID_Student >> a >> cur->data.firstName >> a >> cur->data.lastName >> a >> cur->data.gender >> a >> dob >> a >> cur->data.Social_ID >> a;
			while (cur->subregis != nullptr) {
				if (cur->subregis->subjects_Data.course_Data.course_Name == sub) {
					count++;
					fileOut<<count<<a<<cur->data.ID_Student << a << cur->data.firstName << a << cur->data.lastName << a << cur->data.gender << a << dob << a << cur->data.Social_ID << a <<endl;
				}
				cur->subregis = cur->subregis->data_Next;
			}
			cur = cur->pNext;
		}
	}
	fileIn.close();
	fileOut.close();
}


//void viewScoreClass(_Student* head) {
//	string cl;
//	string sub;
//	_Student* cur = head;
//	wchar_t a = ',';
//	wstring dob;
//	wifstream fileIn;
//	wofstream fileOut;
//	cout << "Please inter name of class: ";
//	cin >> cl;
//	cout << endl << "Please inter subject: ";
//	cin >> sub;
//	fileIn.open(cl + ".csv", ios_base::in);
//	if (!fileIn.is_open()) return;
//	fileOut.open(cl + "_" + sub + ".csv", ios_base::out);
//	if (!fileOut.is_open()) return;
//	fileOut << "No" << a << "ID" << a << "Full name" << a << "Total mark" << a << "Final mark" << a << "Midterm mark" << a << "Other mark" << a;
//	while (!fileIn.eof()) {
//		while (cur != nullptr) {
//			fileIn >> cur->data.Number_In_Class >> a >> cur->data.ID_Student >> a >> cur->data.firstName >> a >> cur->data.lastName >> a >> cur->data.gender >> a >> dob >> a >> cur->data.Social_ID >> a;
//			fileOut << cur->data.Number_In_Class << a << cur->data.ID_Student << a << cur->data.firstName << " " << cur->data.lastName << a;
//			while (cur->data.stu_Score.data_ScoreBoard.course_Data.course_Name != sub ) {
//				/*cur->data.stu_Score = cur->data.stu_Score.dataNext;*/
//			}
//			cur = cur->pNext;
//		}
//	}
//	fileIn.close();
//	fileOut.close();
//}

//void viewScoreClass(_Student* head) {
//	string cl;
//	string sub;
//	_Student* cur;
//	wchar_t a = ',';
//	wstring dob;
//	wifstream fileIn;
//	wofstream fileOut;
//	cout << "Please inter name of class: ";
//	cin >> cl;
//	cout << endl << "Please inter subject: ";
//	cin >> sub;
//	fileIn.open(cl + ".csv", ios_base::in);
//	if (!fileIn.is_open()) return;
//	fileOut.open(cl + "_" + sub + ".csv", ios_base::out);
//	if (!fileOut.is_open()) return;
//	fileOut << "No" << a << "ID" << a << "Full name" << a << "Total mark" << a << "Final mark" << a << "Midterm mark" << a << "Other mark" << a;
//	while (!fileIn.eof()) {
//		fileIn >> cur->data.Number_In_Class >> a >> cur->data.ID_Student >> a >> cur->data.firstName >> a >> cur->data.lastName >> a >> cur->data.gender >> a >> dob >> a >> cur->data.Social_ID >> a;
//		while (cur->subregis->subjects_Data.course_Data.course_Name != sub) cur->subregis = cur->subregis->data_Next;
//		if (cur->subregis) {
//			fileOut << cur->data.Number_In_Class << a << cur->data.ID_Student << a << cur->data.firstName << " " << cur->data.lastName << a << cur->subregis->subjects_Data.course_Data.score.totalMark << a;
//			fileOut << cur->subregis->subjects_Data.course_Data.score.midtermMark << a << cur->subregis->subjects_Data.course_Data.score.finalMark << a;
//		}
//		cur = cur->pNext;
//	}
//	fileIn.close();
//	fileOut.close();
//}