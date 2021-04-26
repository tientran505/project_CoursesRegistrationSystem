#include "function.h"
#include "student.h"
#include<conio.h>

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

void register_One_Course(_Student* Node);

void showInfo_Student(_Student* Node) {
	cout << "Information of student" << endl;
	_setmode(_fileno(stdout), _O_U8TEXT);
	wcout << "Name: " << Node->data.firstName << " " << Node->data.lastName << endl;
	_setmode(_fileno(stdout), _O_TEXT);
	cout << "Student ID: " << Node->data.ID_Student << endl;
	cout << "Gender: " << WStringToString(Node->data.gender) << endl;
	cout << "Date of Birth: " << Node->data.Date_Of_Birth.day << "/" << Node->data.Date_Of_Birth.month << "/" << Node->data.Date_Of_Birth.year << endl;
	cout << "Class: " << Node->data.class_Of_Student << endl;
}

_Student* logInSystem_Student(_Student* head) {
	string userNameTmp, passWordTmp;

	if (head == nullptr) {
		GotoXY(30, 12);
		cout << "There is nothing any student lists in system. Please contact to Academic Staff for more detail" << endl;
		return nullptr;
	}
	while (true) {
		int temp;
		system("cls");
		GotoXY(30, 12);
		cout << "Username: ";
		cin >> userNameTmp;
		GotoXY(30, 14);
		cout << "Password: ";
		cin >> passWordTmp;
		_Student* pCur = head;
		while (pCur->pNext != nullptr) {
			if (userNameTmp == pCur->data.student_Account.ID && passWordTmp == pCur->data.student_Account.password) {
				system("cls");
				GotoXY(35, 13);
				cout<<"Login successfully" << endl;
				return pCur;
			}
			pCur = pCur->pNext;
		}
		GotoXY(30,15);
		cout << "Invalid login, please try again" << endl;
		GotoXY(35, 16);
		cout << " (enter to return) "<<endl;

		temp = _getch();
	}
}

void changePass(_Student* Node) {
	string old, newPass;
	cout << "Please input password: " << endl;
	getline(cin, old);
	while (true) {
		if (old != Node->data.student_Account.password) {
			cout << "Incorrect password... Please try again..." << endl;
			getline(cin, old);
		}
		else {
			cout << "Please input new password: ";
			getline(cin, newPass);
			int check = 1; int check2 = 1;
			for (int i = 0; i < newPass.length(); i++) {
				if (int(newPass[i]) > 64 && int(newPass[i]) < 91)
					check *= 0;
				else check *= 1;
				if (int(newPass[i]) > 47 && int(newPass[i]) < 58)
					check2 *= 0;
				else check2 *= 1;
			}
			while (true) {
				if (check == 1 || check2 == 1 || newPass.length() < 8) {
					cout << "Password must include capital character(s) and number(s)..." << endl << "Please try another password..." << endl;
					getline(cin, newPass);
				}
				else {
					string confirm;
					cout << "Please input new password again to confirm..." << endl;
					while (true) {
						if (confirm == newPass) {
							Node->data.student_Account.password = newPass;
							break;
						}
						else {
							cout << "Confirm not match... One more time please! ";
							cin >> confirm;
						}
					}
					break;
				}

			}
			break;
		}
	}
}

void editPassword(_Student* Node) {
	string curPassword, newPassword, retype;
	cout << "Change password" << endl;
	cout << "It's a good idea to use a strong password that you don't use elsewhere" << endl;
	while (true) {
		cout << "Current password: ";
		cin >> curPassword;
		if (curPassword == Node->data.student_Account.password) {
			cout << "New password: ";
			cin >> newPassword;
			cout << "Retype new password: ";
			cin >> retype;
			while (retype != newPassword) {
				cout << "Passwords do not match. Try again" << endl;
				cout << "New password: ";
				cin >> newPassword;
				cout << "Retype new password: ";
				cin >> retype;
			}
			Node->data.student_Account.password = newPassword;
			cout << "Change password successfully" << endl;
			ifstream readFile;
			ofstream fileOut;
			readFile.open(dir + dirClass_Save + "save_Account_" + Node->data.class_Of_Student + ".txt", ios_base::in);
			fileOut.open(dir + dirClass_Save + "change.txt", ios_base::out);
			int i = 0;
			while (!readFile.eof()) {
				string idTmp;
				if (i != 0) fileOut << endl;
				getline(readFile, idTmp, ',');
				fileOut << idTmp << ",";
				if (idTmp == Node->data.student_Account.ID) {
					fileOut << Node->data.student_Account.password;
					getline(readFile, idTmp);
				}
				else {
					getline(readFile, newPassword);
					fileOut << newPassword;
				}
				i++;
			}
			readFile.close();
			fileOut.close();
			
			string tmp = dir + dirClass_Save + "save_Account_" + Node->data.class_Of_Student + ".txt";
			char* newName = new char[tmp.length() + 1];
			strcpy_s(newName, tmp.length() + 1, tmp.c_str());
			remove(newName);
			string oldNameTmp = dir + dirClass_Save + "change.txt";
			char* oldName = new char[oldNameTmp.length() + 1];
			strcpy_s(oldName, oldNameTmp.length() + 1, oldNameTmp.c_str());
			rename(oldName, newName);
			delete[] newName;
			delete[] oldName;
			return;
		}
		else cout << "Enter a valid password and try again." << endl;
	}
}

int stringToInt(string str) {
	int sum = 0;
	for (int i = 0; i < 8; i++) {
		sum *= 10;
		sum += (int)(str[i] - 48);
	}
	return sum;
}

bool can_Register_Course(Date dateCur, Date dateStart, Date dateEnd, Time timeCur, Time timeStart, Time timeEnd) { // check dateFirst whether if is in betwwen dateStart & dateEnd
	if (dateCur.year >= dateStart.year && dateCur.year <= dateEnd.year) {
		if (dateCur.month >= dateStart.month && dateCur.month <= dateEnd.month) {
			if (dateCur.day > dateStart.day && dateCur.day < dateEnd.day) return true;
			else if (dateCur.day == dateStart.day) {
				if (timeCur.hour > timeStart.hour) return true;
				else if (timeCur.hour == timeStart.hour) return (timeCur.minute >= timeStart.minute);
				else return false;
			}
			else if (dateCur.day == dateEnd.day) {
				if (timeCur.hour < timeEnd.hour) return true;
				else if (timeCur.hour == timeEnd.hour) return (timeCur.minute < timeEnd.minute);
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}

bool is_Same_Course(_Subjects* Node, string nameCourse) {
	if (Node == nullptr) return true;
	while (Node != nullptr) {
		if (Node->subjects_Data.course_Data.course_Name == nameCourse) return false;
		Node = Node->data_Next;
	}
	return true;
}

_Subjects* is_Same_Session(_Subjects* Node, Session ss1, Session ss2) {
	if (Node == nullptr) return nullptr;
	while (Node != nullptr) {
		Session ssTmp = Node->subjects_Data.course_Data.first_Session;
		if (ssTmp.dayOfWeek == ss1.dayOfWeek || ssTmp.dayOfWeek == ss2.dayOfWeek) {
			if (ssTmp.session == ss1.session || ssTmp.session == ss2.session) return Node;
		}
ssTmp = Node->subjects_Data.course_Data.second_Session;
if (ssTmp.dayOfWeek == ss1.dayOfWeek || ssTmp.dayOfWeek == ss2.dayOfWeek) {
	if (ssTmp.session == ss1.session || ssTmp.session == ss2.session) return Node;
}
Node = Node->data_Next;
	}
	return nullptr;
}

int list_Len(_Subjects* Node) {
	if (Node == nullptr) return 0;
	int count = 0;
	while (Node != nullptr) {
		Node = Node->data_Next;
		count++;
	}
	return count;
}

void register_Course(_Student* Node) {
	time_t now = time(0);
	tm* ltm = localtime(&now);

	ifstream read;
	read.open(dir + dirRegis + "Registration.txt", ios_base::in);

	if (!read.is_open()) {
		cout << "Staff had not create the course registration session. Please contact staff department for more detail!" << endl;
		read.close();
		return;
	}

	Date dateStart, dateEnd;
	Time timeStart, timeEnd;

	char a = '/', b = ':', c = ',';

	read >> dateStart.day >> a >> dateStart.month >> a >> dateStart.year >> c;
	read >> timeStart.hour >> b >> timeStart.minute;

	read >> dateEnd.day >> a >> dateEnd.month >> a >> dateEnd.year >> c;
	read >> timeEnd.hour >> b >> timeEnd.minute;

	read.close();

	Date dateCur;
	dateCur.year = 1900 + ltm->tm_year;
	dateCur.month = ltm->tm_mon + 1;
	dateCur.day = ltm->tm_mday;

	Time timeCur;
	timeCur.hour = ltm->tm_hour;
	timeCur.minute = ltm->tm_min;

	cout << "Date: " << dateCur.day << "/" << dateCur.month << "/" << dateCur.year << endl;
	cout << "Time: " << timeCur.hour << ":" << timeCur.minute << endl;

	if (!can_Register_Course(dateCur, dateStart, dateEnd, timeCur, timeStart, timeEnd)) {
		cout << "Registration has expired!" << endl;
		return;
	}

	bool running = true;
	do {
		if (list_Len(Node->subregis) >= 5) {
			cout << "Only 5 courses are allowed per semester!" << endl;
			return;
		}
		viewCourseList(dir + dirCourse + "CoursesRegistration.txt");
		register_One_Course(Node);
		cout << "1. Continue to register the course\t2.Exit" << endl;
		int option;
		cin >> option;
		if (option == 1) {
			if (list_Len(Node->subregis) >= 5) {
				cout << "Only 5 courses are allowed per semester!" << endl;
				running = false;
			}
		}
		else running = false;
	} while (running);
}

void register_One_Course_TextFile(_Student* Node) {
	wifstream fileOld;
	wofstream fileNew;

	string oldName = dir + dirCourse_Student + "Registered_Course_" + Node->data.class_Of_Student + ".txt";
	string newName = dir + dirCourse_Student + "Tmp" + Node->data.class_Of_Student + ".txt";
	fileOld.open(oldName, ios_base::in);
	fileNew.open(newName, ios_base::out);

	fileOld.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	fileNew.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	wstring line;
	int courseID;
	int numOfCourse;
	wchar_t a = ',';
	int k = 0;
	while (!fileOld.eof()) {
		fileOld >> courseID >> a;
		if (k != 0) fileNew << endl;
		fileNew << courseID << ",";
		if (to_string(courseID) == Node->data.student_Account.ID) {
			fileOld >> numOfCourse;
			fileNew << numOfCourse + 1;
			getline(fileOld, line);
			for (int i = 1; i <= numOfCourse; i++) {
				getline(fileOld, line);
				fileNew << endl << line;
			}
			_Subjects* cur = Node->subregis;
			for (int i = 1; i <= numOfCourse; i++) cur = cur->data_Next;
			fileNew << endl << stringToWString(cur->subjects_Data.course_Data.course_ID) << ",";
			fileNew << stringToWString(cur->subjects_Data.course_Data.course_Name) << ",";
			fileNew << cur->subjects_Data.course_Data.Name_of_Teacher << ",";
			fileNew << cur->subjects_Data.course_Data.credit << ",";
			fileNew << stringToWString(cur->subjects_Data.course_Data.first_Session.dayOfWeek) << ",";
			fileNew << stringToWString(cur->subjects_Data.course_Data.first_Session.session) << ",";
			fileNew << stringToWString(cur->subjects_Data.course_Data.second_Session.dayOfWeek) << ",";
			fileNew << stringToWString(cur->subjects_Data.course_Data.second_Session.session);
		}
		else {
			fileOld >> numOfCourse;
			fileNew << numOfCourse;
			getline(fileOld, line);
			for (int i = 1; i <= numOfCourse; i++) {
				getline(fileOld, line);
				fileNew << endl << line;
			}
		}
		k++;
	}

	fileOld.close();
	fileNew.close();

	remove(oldName.c_str());
	rename(newName.c_str(), oldName.c_str());
}

void register_One_Course(_Student* Node) {
	wifstream read;
	read.open(dir + dirCourse + "CoursesRegistration.txt", ios_base::in);
	read.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	wchar_t a = ',';
	wstring nameCourse, line, nameTeacher;
	int numberOfCredits, numOfStud;
	wstring ss1, ss2, d1, d2;
	Session session1, session2;
	bool running = true;
	cout << "Choose number of course the register: ";
	int choose;
	cin >> choose;
	while (!read.eof()) {
		int no;
		read >> no >> a;
		if (no == choose) {
			getline(read, line, a);
			getline(read, nameCourse, a);
			getline(read, nameTeacher, a);
			read >> numberOfCredits >> a;
			read >> numOfStud >> a;
			getline(read, d1, a);
			getline(read, ss1, a);
			getline(read, d2, a);
			getline(read, ss2);

			string NameCourses = WStringToString(nameCourse);
			session1.dayOfWeek = WStringToString(d1);
			session1.session = WStringToString(ss1);
			session2.dayOfWeek = WStringToString(d2);
			session2.session = WStringToString(ss2);

			if (!is_Same_Course(Node->subregis, NameCourses)) {
				cout << "You have already registered " << NameCourses << ". Pls register another course!" << endl;
				return;
			}

			_Subjects* course_Confilct = new _Subjects;
			course_Confilct = is_Same_Session(Node->subregis, session1, session2);
		
			if (course_Confilct != nullptr) {
				cout << NameCourses << " is conflicted with " << course_Confilct->subjects_Data.course_Data.course_Name << "! Pls register anthore corse" << endl;
				return;
			}
			delete course_Confilct;

			_Subjects* cur = Node->subregis;

			if (Node->subregis == nullptr) {
				Node->subregis = new _Subjects;
				cur = Node->subregis;
				cur->data_Prev = nullptr;
			}

			else {
				while (cur->data_Next != nullptr) cur = cur->data_Next;
				cur->data_Next = new _Subjects;
				cur->data_Next->data_Prev = cur;
				cur = cur->data_Next;
			}

			cur->subjects_Data.course_Data.course_ID = WStringToString(line);
			cur->subjects_Data.course_Data.course_Name = NameCourses;
			cur->subjects_Data.course_Data.Name_of_Teacher = nameTeacher;
			cur->subjects_Data.course_Data.credit = numberOfCredits;
			cur->subjects_Data.course_Data.first_Session.dayOfWeek = session1.dayOfWeek;
			cur->subjects_Data.course_Data.first_Session.session = session1.session;
			cur->subjects_Data.course_Data.second_Session.dayOfWeek = session2.dayOfWeek;
			cur->subjects_Data.course_Data.second_Session.session = session2.session;
			cur->data_Next = nullptr;

			register_One_Course_TextFile(Node);

			wofstream fileOut;
			fileOut.open(dir + dirCourse_Student + NameCourses + ".csv", ios_base::app);
			fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

			int num_Of_Line = check_Line(dir + dirCourse_Student + NameCourses + ".csv");
			if (num_Of_Line != 0) fileOut << endl;

			fileOut << num_Of_Line + 1 << ",";
			fileOut << Node->data.ID_Student << ",";
			fileOut << Node->data.firstName << " " << Node->data.lastName << ",";
			fileOut << Node->data.gender << ",";
			fileOut << Node->data.Date_Of_Birth.day << "/" << Node->data.Date_Of_Birth.month << "/" << Node->data.Date_Of_Birth.year;
			fileOut << "," << stringToWString(Node->data.class_Of_Student);

			wcout << nameCourse << " completely registered" << endl;
			read.close();
			fileOut.close();
			return;
		}
		else getline(read, line);
	}
}

void view_Reigstration_Results(_Subjects* Node) {
	if (Node == nullptr) {
		cout << "You have not registered any courses" << endl;
		return;
	}
	int count = 1;
	while (Node != nullptr) {
		cout << "-----------------------------------------------" << endl;
		cout << count++ << ". " << Node->subjects_Data.course_Data.course_Name << endl;
		cout << "ID Course: " << Node->subjects_Data.course_Data.course_ID << endl;
		_setmode(_fileno(stdout), _O_U8TEXT);
		wcout << L"Lecturer: " << Node->subjects_Data.course_Data.Name_of_Teacher << endl;
		_setmode(_fileno(stdout), _O_TEXT);
		cout << "Number of credits: " << Node->subjects_Data.course_Data.credit << endl;
		cout << "Schedule: " << endl;
		cout << "- Session 1: " << Node->subjects_Data.course_Data.first_Session.dayOfWeek << " - " << Node->subjects_Data.course_Data.first_Session.session << endl;
		cout << "- Session 2: " << Node->subjects_Data.course_Data.second_Session.dayOfWeek << " - " << Node->subjects_Data.course_Data.second_Session.session << endl;
		cout << "-----------------------------------------------" << endl;
		Node = Node->data_Next;
	}
}

void remove_Courses_TextFile(_Student* Node, string courseID) {
	wifstream fileOld;
	wofstream fileNew;

	string oldName = dir + dirCourse_Student + "Registered_Course_" + Node->data.class_Of_Student + ".txt";
	string newName = dir + dirCourse_Student + "Tmp" + Node->data.class_Of_Student + ".txt";

	fileOld.open(oldName, ios_base::in);
	fileNew.open(newName, ios_base::out);

	fileOld.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	fileNew.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	int k = 0;
	wstring line;
	int IDStu, numOfCourse;
	wchar_t a = ',';
	while (!fileOld.eof()) {
		if (k != 0) fileNew << endl;
		fileOld >> IDStu >> a;
		fileNew << IDStu << ",";
		if (IDStu == Node->data.ID_Student) {
			fileOld >> numOfCourse;
			fileNew << numOfCourse - 1;
			getline(fileOld, line);
			for (int i = 1; i <= numOfCourse; i++) {
				getline(fileOld, line, a);
				if (line == stringToWString(courseID)) getline(fileOld, line);
				else {
					fileNew << endl << line << ",";
					getline(fileOld, line);
					fileNew << line;
				}
			}
		}

		else {
			fileOld >> numOfCourse;
			fileNew << numOfCourse;
			getline(fileOld, line);
			for (int i = 1; i <= numOfCourse; i++) {
				getline(fileOld, line);
				fileNew << endl << line;
			}
		}
		k++;
	}
	
	fileOld.close();
	fileNew.close();

	remove(oldName.c_str());
	rename(newName.c_str(), oldName.c_str());
}

void remove_From_List(_Student* Node, string courseName) {
	string oldName = dir + dirCourse_Student + courseName + ".csv";
	string newName = dir + dirCourse_Student + "change.csv";
	
	if (check_Line(oldName) == 1) {
		remove(oldName.c_str());
		return;
	}

	wifstream fileOld;
	wofstream fileNew;

	fileOld.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	fileNew.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	fileOld.open(oldName, ios_base::in);
	fileNew.open(newName, ios_base::out);

	int no, stuID;
	int noTmp;
	wstring line;
	wchar_t a = ',';
	int i = 1;
	while (!fileOld.eof()) {
		fileOld >> no >> a;
		fileOld >> stuID >> a;
		if (stuID == Node->data.ID_Student) getline(fileOld, line);
		else {
			if (i != 1) fileNew << endl;
			fileNew << i << "," << stuID << ",";
			getline(fileOld, line);
			fileNew << line;
			i++;
		}
	}

	fileOld.close();
	fileNew.close();

	remove(oldName.c_str());
	rename(newName.c_str(), oldName.c_str());
}

void remove_Courses(_Student*& Node) {
	bool running = true;
	int choose;
	ifstream fileOld;
	ofstream fileNew;
	do {
		if (Node == nullptr) {
			cout << "Nothing to delete" << endl;
			return;
		}
		view_Reigstration_Results(Node->subregis);
		cout << "Enter the number of course to remove (0 to exit): ";
		int choose;
		cin >> choose;
		if (choose <= 0) {
			running = false;
		}

		else if (choose > list_Len(Node->subregis)) cout << "Your chosen course is exceed the number of courses! Please try again!" << endl;
		else {
			_Subjects* cur = Node->subregis;
			for (int i = 1; i < choose; i++) cur = cur->data_Next;
			string courseName = cur->subjects_Data.course_Data.course_Name;
			remove_From_List(Node, courseName);
			remove_Courses_TextFile(Node, cur->subjects_Data.course_Data.course_ID);
			if (cur->data_Next != nullptr) cur->data_Next->data_Prev = cur->data_Prev;
			if (cur->data_Prev != nullptr) cur->data_Prev->data_Next = cur->data_Next;
			if (cur == Node->subregis) Node->subregis = Node->subregis->data_Next;
			delete cur;
			cout << courseName << " had been completely deleted!" << endl;
			cout << "1. Continue\t2.Exit" << endl;
			cin >> choose;
			if (choose == 2) running = false;
		}
	} while (running);
}
