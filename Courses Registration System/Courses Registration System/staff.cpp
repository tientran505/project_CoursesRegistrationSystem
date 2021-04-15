#include "staff.h"
#include "student.h"

void loadStudentList(string path, _Student*& head) {
	head = nullptr;
	wifstream fileIn;
	fileIn.open(path, ios_base::in);

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
		pCur->pNext = nullptr;
	}

	fileIn.close();
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
	_Student* pTmp = classPush;
	while (pTmp->pNext != nullptr) pTmp = pTmp->pNext;
	pTmp->pNext = listStack;
	listStack = classPush;
}

void listStudents(_Student*& head) {
	string path;
	string year[5] = { "first-year", "second-year","third-year", "fourth-year", "fifth-year" };
	_Student* headClass = nullptr;
	int i = 0;
	while (true) {
		cout << "0. exit input list" << endl;
		cout << "1. input next year student list" << endl;
		cout << "2. input previous year student list" << endl;
		cout << "Input to the list of " << year[i] << " students: ";
		cin >> path;

		if (path == "0") break;
		if (path == "1") {
			i++;
			if (i > 4) i = 4;
			continue;
		}

		if (path == "2") {
			i--;
			if (i < 0) i = 0;
			continue;
		}
		
		loadStudentList(dir + dirClass + path + ".csv", headClass);
		displayStudentList(dir + dirClass + path + "_Info" + ".csv", headClass);
		listPush(head, headClass);
	}
	convertAccountOfStudent(dir + dirClass + "Account" + ".txt", head);
}

void staff_Login(string& username) {
	ifstream fileIn;
	int running = true;
	string password;
	string userTmp, passTmp;
	while (running) {
		cout << "Username: ";
		cin >> username;
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
		if (!running) cout << "Login Successfully!" << endl;
		else cout << "Invalid login, please try again" << endl;
		fileIn.close();
	}
}

void turnOnVietChar() {
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
}

void turnOffVietChar() {
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
	cout << endl << "Curent Line: " << no << endl;

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
		turnOnVietChar();
		cin.ignore(1000, '\n');
		wchar_t wsTmp[101];
		wcin.get(wsTmp, 101, '\n');
		teacherName = new wchar_t[wcslen(wsTmp) + 1];
		wcscpy_s(teacherName, wcslen(wsTmp) + 1, wsTmp);
		wcin.ignore(1000, '\n');
		turnOffVietChar();

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
	fileIn.open(path, ios_base::in);

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
		turnOnVietChar();
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
		turnOffVietChar();
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

	
	fileOld.open(dir + dirCourse + "CoursesRegistration.txt", ios_base::in);
	fileNew.open(dir + dirCourse + "change.txt", ios_base::out);

	fileOld.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	fileNew.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	viewCourseList(dir + dirCourse + "CoursesRegistration.txt");
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
		turnOnVietChar();
		cin.ignore(1000, '\n');
		wcin.get(sTmp, 101, '\n');
		wchar_t* teacherName = new wchar_t[wcslen(sTmp) + 1];
		wcscpy_s(teacherName, wcslen(sTmp) + 1, sTmp);
		wcin.ignore(1000, '\n');
		turnOffVietChar();
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
		int* credit;
		cout << "Enter new credits of course: ";
		credit = new int;
		cin >> *credit;
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
		delete credit;
		break;
	}

	case 5: {
		cout << "Enter new maximum number of students in course: ";
		int* num = new int;
		cin >> *num;
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
		wstring junk;
		getline(fileOld, tmp, a);
		while (!fileOld.eof()) {
			getline(fileOld, junk);
			fileNew << junk << endl;
		}
		delete num;
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
	remove("E:/HCMUS/Sem 2/Programming Techniques/Project - A Courses Registration System/project_CoursesRegistrationSystem/Courses Registration System/Courses Registration System/Course/CoursesRegistration.txt");
	rename("E:/HCMUS/Sem 2/Programming Techniques/Project - A Courses Registration System/project_CoursesRegistrationSystem/Courses Registration System/Courses Registration System/Course/change.txt", "E:/HCMUS/Sem 2/Programming Techniques/Project - A Courses Registration System/project_CoursesRegistrationSystem/Courses Registration System/Courses Registration System/Course/CoursesRegistration.txt");
}

void delete_Courses() {
	wifstream fileOld;

	fileOld.open(dir + dirCourse + "CoursesRegistration.txt", ios_base::in);
	int line = check_Line(dir + dirCourse + "CoursesRegistration.txt");

	if (!fileOld.is_open() || line == 0) {
		cout << "NOTHING TO DELETE!\n" << "================================================" << endl;
		fileOld.close();
		return;
	}

	wofstream fileNew;
	fileNew.open(dir + dirCourse + "change.txt", ios_base::out);

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
	remove("E:/HCMUS/Sem 2/Programming Techniques/Project - A Courses Registration System/project_CoursesRegistrationSystem/Courses Registration System/Courses Registration System/Course/CoursesRegistration.txt");
	rename("E:/HCMUS/Sem 2/Programming Techniques/Project - A Courses Registration System/project_CoursesRegistrationSystem/Courses Registration System/Courses Registration System/Course/change.txt", "E:/HCMUS/Sem 2/Programming Techniques/Project - A Courses Registration System/project_CoursesRegistrationSystem/Courses Registration System/Courses Registration System/Course/CoursesRegistration.txt");
}

void showInfo_Staff(string username) {
	ifstream fileIn;
	fileIn.open(dir + dirStaff + "Staff_Info.txt", ios_base::in);
	while (!fileIn.eof()) {
		string tmp, name;
		getline(fileIn, tmp, ',');
		getline(fileIn, name);
		if (tmp == username) {
			cout << "Infomartion of staff" << endl;
			cout << "Name: " << name << endl;
			cout << "Department: Academic Staff" << endl;
			fileIn.close();
			return;
		}
	}
	cout << "Infomation of this staff is currently not existed in the system " << endl;
	fileIn.close();
}


void add_Schoolyear(Date& schoolyear) {
	int running = true;
	do {
		cout << "Input the schoolyear: ";
		int year;
		cin >> year;
		cout << "You mean " << year << "-" << year + 1 << "?";
		cout << "\nY. Yes \t N. No" << endl;
		string choose;
		cin >> choose;
		if (choose == "Y" || choose == "y") {
			schoolyear.year = year;
			running = false;
		}
	} while (running);
}