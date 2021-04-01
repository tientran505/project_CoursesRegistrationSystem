 #include "function.h"

void loadStudentList(string path, StudentList*& head) {
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
	StudentList* pCur = head;
	while (!fileIn.eof()) {
		if (head == nullptr) {
			head = new StudentList;
			pCur = head;
		}
		else {
			pCur->pNext = new StudentList;
			pCur = pCur->pNext;
		}
		fileIn >> pCur->stu.No >> a;
		fileIn >> pCur->stu.studentID >> a;
		getline(fileIn, pCur->stu.firstName, a);
		getline(fileIn, pCur->stu.lastName, a);
		getline(fileIn, pCur->stu.gender, a);
		fileIn >> pCur->stu.dob.day >> b;
		fileIn >> pCur->stu.dob.month >> b;
		fileIn >> pCur->stu.dob.year >> a;
		fileIn >> pCur->stu.socialID;
		pCur->pNext = nullptr;
	}

	fileIn.close();
}

void displayStudentList(string path, StudentList* head) {
	wofstream fileOut;
	fileOut.open(path, ios_base::out);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	
	if (!fileOut.is_open()) {
		cout << "Cant creat file!" << endl;
		fileOut.close();
		return;
	}

	while (head->pNext != nullptr) {
		fileOut << head->stu.No << L",";
		fileOut << head->stu.studentID << L",";
		fileOut << head->stu.firstName << L",";
		fileOut << head->stu.lastName << L",";
		fileOut << head->stu.gender << L",";
		fileOut << head->stu.dob.day << L"/" << head->stu.dob.month << L"/" << head->stu.dob.year << L",";
		fileOut << head->stu.socialID << endl;
		head = head->pNext;
	}

	fileOut.close();
}

void deleteStudentList(StudentList*& head) {
	if (head == nullptr) return;
	StudentList* cur = head;
	while (head != nullptr) {
		head = head->pNext;
		delete cur;
		cur = head;
	}
}