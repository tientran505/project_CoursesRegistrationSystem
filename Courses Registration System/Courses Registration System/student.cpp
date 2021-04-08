#include "student.h"
#include "function.h"
void ReadStudent_CSV(const char* path, _NodeStudent*& students)
{
	students = nullptr;
	int line = 0;
	ifstream fin(path);
	if (fin.bad())
	{
		cout << "File not found";
		exit(0);
	}

	_NodeStudent* stuCur = nullptr;
	char a = ',', b = '/';
	while (!fin.eof())
	{
		if (students == nullptr)
		{
			_NodeStudent* students = new _NodeStudent;
			stuCur = students;
		}

		else {
			stuCur->pNext = new _NodeStudent;
			stuCur = stuCur->pNext;
		}

		fin >> stuCur->data.Number_In_Class >> a;
		fin >> stuCur->data.ID >> a;
		getline(fin, stuCur->data.Firstname, ',');
		getline(fin, stuCur->data.Lastname, ',');
		getline(fin, stuCur->data.Gender, ',');
		fin >> stuCur->data.Date_Of_Birth.day >> b;
		fin >> stuCur->data.Date_Of_Birth.month >> b;
		fin >> stuCur->data.Date_Of_Birth.year;
		stuCur->pNext = nullptr;
	}
	fin.close();
}

wstring stringToWString(string str) {
	wstring tmp(str.length(), L' ');
	copy(str.begin(), str.end(), tmp.begin());
	return tmp;
}

string WStringToString(wstring s)
{
	string temp(s.length(), ' ');
	copy(s.begin(), s.end(), temp.begin());
	return temp;
}

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

void deleteStudentList(_Student*& head) {
	if (head == nullptr) return;
	_Student* cur = head;
	while (head != nullptr) {
		head = head->pNext;
		delete cur;
		cur = head;
	}
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

void logInSystem_Student(_Student* head) {
	string userNameTmp, passWordTmp;
	cout << "Username: ";
	cin >> userNameTmp;
	cout << "Password: ";
	cin >> passWordTmp;
	_Student* pCur = head;



	while (pCur->pNext != nullptr) {
		if (userNameTmp == pCur->data.student_Account.ID && passWordTmp == pCur->data.student_Account.password) {
			cout << "-------------------------------\n"<< "Login successfully" << endl;
			cout << "Information of student" << endl;
			_setmode(_fileno(stdout), _O_U8TEXT);
			wcout << "Name: " << pCur->data.firstName << L" " << pCur->data.lastName << endl;
			_setmode(_fileno(stdout), _O_TEXT);
			cout << "Student ID: " << pCur->data.ID_Student << endl;
			cout << "Gender: " << WStringToString(pCur->data.gender) << endl;
			cout << "Date of Birth: " << pCur->data.Date_Of_Birth.day << "/" << pCur->data.Date_Of_Birth.month << "/" << pCur->data.Date_Of_Birth.year << endl;
			cout << "Class: " << pCur->data.class_Of_Student << endl;
			return;
		}
		pCur = pCur->pNext;
	}
	cout << "Invalid login, please try again" << endl;
}
