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

void listStudents(string path, _Student*& head) {
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

void staff_Menu() {
	//0. View info
	//0.1 change password
	//1. create a school year
	//1.1. create a semester - school year - start date - end date
	//2. creata classes for 1st year
	//3. Course Registration
	//3.1. course registration session: start date, end date.
	//3.2. Add a course to this semester
	//3
	
}