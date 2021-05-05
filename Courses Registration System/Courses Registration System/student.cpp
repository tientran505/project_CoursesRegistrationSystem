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
	GotoXY(39, 6);
	cout << "Information of student" << endl;
	_setmode(_fileno(stdout), _O_U8TEXT);
	GotoXY(39, 7);
	wcout << "Name: " << Node->data.firstName << " " << Node->data.lastName << endl;
	_setmode(_fileno(stdout), _O_TEXT);
	GotoXY(39, 8);
	cout << "Student ID: " << Node->data.ID_Student << endl;
	GotoXY(39, 9);
	cout << "Gender: " << WStringToString(Node->data.gender) << endl;
	GotoXY(39, 10);
	cout << "Date of Birth: " << Node->data.Date_Of_Birth.day << "/" << Node->data.Date_Of_Birth.month << "/" << Node->data.Date_Of_Birth.year << endl;
	GotoXY(39, 11);
	cout << "Class: " << Node->data.class_Of_Student << endl;
}

_Student* logInSystem_Student(_Student* head) {
	string userNameTmp, passWordTmp;

	if (head == nullptr) {
		
		
		
		
		(34, 10);
		cout << "There is nothing any student lists in system" << endl;
		GotoXY(34, 11);
		cout << "Please contact to Academic Staff for more detail" << endl;
		return nullptr;
	}
	while (true) {
		int temp;
		system("cls");
		GotoXY(42, 11);
		cout << "Username: ";
		cin >> userNameTmp;
		GotoXY(42, 13);
		cout << "Password: ";
		cin >> passWordTmp;
		_Student* pCur = head;
		while (pCur->pNext != nullptr) {
			if (userNameTmp == pCur->data.student_Account.ID && passWordTmp == pCur->data.student_Account.password) {
				system("cls");
				GotoXY(40, 12);
				Sleep(200);
				cout<<"Login successfully" << endl;
				return pCur;
			}
			pCur = pCur->pNext;
		}
		GotoXY(35,15);
		cout << "Invalid login, please try again" << endl;
		GotoXY(40, 16);
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
	GotoXY(45, 5);
	cout << "Change password" << endl;
	GotoXY(20, 6);
	cout << "It's a good idea to use a strong password that you don't use elsewhere" << endl;
	while (true) {
		GotoXY(45, 5);
		cout << "Change password" << endl;
		GotoXY(20, 6);
		cout << "It's a good idea to use a strong password that you don't use elsewhere" << endl;
		GotoXY(40, 7);
		cout << "Current password: ";
		cin >> curPassword;
		if (curPassword == Node->data.student_Account.password) {
			GotoXY(40, 8);
			cout << "New password: ";
			cin >> newPassword;
			GotoXY(40, 9);
			cout << "Retype new password: ";
			cin >> retype;
			while (retype != newPassword) {
				GotoXY(30, 10);
				cout << "Passwords do not match. Try again" << endl;
				GotoXY(40, 11);
				cout << "New password: ";
				cin >> newPassword;
				GotoXY(40, 12);
				cout << "Retype new password: ";
				cin >> retype;
			}
			Node->data.student_Account.password = newPassword;
			GotoXY(35, 10);
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
		
		else {
			GotoXY(35, 12);
			cout << "Enter a valid password and try again." << endl;
			_getch();
			system("cls");
		}
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
	if (dateCur.year >= dateStart.year && dateCur.year == dateEnd.year) {
		if (dateCur.month == dateStart.month && dateCur.month == dateEnd.month) {
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
		else if (dateCur.month > dateStart.month && dateCur.month == dateEnd.month) {
			if (dateCur.day < dateEnd.day) return true;
			else if (dateCur.day == dateEnd.day) {
				if (timeCur.hour < timeEnd.hour) return true;
				else if (timeCur.hour == timeEnd.hour) return (timeCur.minute < timeEnd.minute);
				else return false;
			}
		}
		else if (dateCur.month >= dateStart.month && dateCur.month < dateEnd.month) return true;
		else return false;
	}
	else if (dateCur.year >= dateStart.year && dateCur.year < dateEnd.year) return true;
	else return false;
}

string schoolYearCurrent(int& sem) {
	string schoolyear;
	ifstream readSY;
	readSY.open(dir + dirSchoolYear + "School_Year.txt", ios_base::in);

	if (!readSY.is_open()) return 0;

	while (!readSY.eof()) {
		getline(readSY, schoolyear);
	}
	readSY.close();

	ifstream fRead;
	fRead.open(dir + dirSchoolYear + schoolyear + ".txt", ios_base::in);

	string line;
	while (!fRead.eof()) {
		getline(fRead, line, ' ');
		fRead >> sem;
		for (int i = 0; i < 3; i++) getline(fRead, line);
	}
	fRead.close();
	return schoolyear;
}

bool is_Same_Course(_Subjects* Node, string nameCourse, string schoolyearCur, int semCur) {
	if (Node == nullptr) return true;
	while (Node->subjects_Data.course_Data.schoolYear != schoolyearCur || Node->subjects_Data.course_Data.semNo != semCur) {
		Node = Node->data_Next;
		if (Node == nullptr) return true;
	}
	while (Node != nullptr) {
		if (Node->subjects_Data.course_Data.course_Name == nameCourse) return false;
		Node = Node->data_Next;
	}
	return true;
}

_Subjects* is_Same_Session(_Subjects* Node, Session ss1, Session ss2, string schoolyearCur, int semCur) {
	if (Node == nullptr) return nullptr; 	
	while (Node->subjects_Data.course_Data.schoolYear != schoolyearCur || Node->subjects_Data.course_Data.semNo != semCur) {
		Node = Node->data_Next;
		if (Node == nullptr) return nullptr;
	}

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

int list_Len_In_Sem(_Subjects* Node, string schoolYear, int sem) {
	if (Node == nullptr) return 0;
	int count = 0;
	while (Node != nullptr) {
		if (Node->subjects_Data.course_Data.semNo == sem && Node->subjects_Data.course_Data.schoolYear == schoolYear) count++;
		Node = Node->data_Next;
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

	if (!can_Register_Course(dateCur, dateStart, dateEnd, timeCur, timeStart, timeEnd)) {
		cout << "Registration has expired!" << endl;
		return;
	}

	bool running = true;
	int semCur = NULL;
	string schoolYear = schoolYearCurrent(semCur);
	do {
		if (list_Len_In_Sem(Node->subregis, schoolYear, semCur) >= 5) {
			cout << "Only 5 courses are allowed per semester!" << endl;
			return;
		}
		viewCourseList(dir + dirCourse + "CoursesRegistration.txt");
		register_One_Course(Node);
		cout << "1. Continue to register the course\t2.Exit" << endl;
		int option;
		cin >> option;
		if (option == 1) {
			if (list_Len_In_Sem(Node->subregis, schoolYear, semCur) >= 5) {
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
			fileNew << stringToWString(cur->subjects_Data.course_Data.second_Session.session) << "|";
			fileNew << stringToWString(cur->subjects_Data.course_Data.schoolYear) << ",";
			fileNew << cur->subjects_Data.course_Data.semNo;
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
	int semCur = NULL;
	string schoolYearCur = schoolYearCurrent(semCur);
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

			if (!is_Same_Course(Node->subregis, NameCourses, schoolYearCur, semCur)) {
				cout << "You have already registered " << NameCourses << ". Pls register another course!" << endl;
				return;
			}

			_Subjects* course_Confilct = new _Subjects;

			course_Confilct = is_Same_Session(Node->subregis, session1, session2, schoolYearCur, semCur);
		
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

			cur->subjects_Data.course_Data.schoolYear = schoolYearCur;
			cur->subjects_Data.course_Data.semNo = semCur;
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
			
			wcout << nameCourse << " completely registered" << endl;
			read.close();
			fileOut.close();
			return;
		}
		else getline(read, line);
	}
}

void view_Reigstration_Results(_Subjects* Node, string schoolyear, int sem) {
	if (Node == nullptr) {
		cout << "You have not registered any courses" << endl;
		return;
	}
	int count = 1;
	while (Node != nullptr) {
		if (Node->subjects_Data.course_Data.schoolYear == schoolyear && Node->subjects_Data.course_Data.semNo == sem) {
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
		}
		Node = Node->data_Next;
	}
}

void remove_Courses_TextFile(_Student* Node, string courseID, string schoolyearCur, int semCur) {
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
	wstring lineTmp, schoolyear;
	int sem;
	int IDStu, numOfCourse;
	wchar_t a = ',';
	wchar_t b = '|';
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
				getline(fileOld, lineTmp, b);
				getline(fileOld, schoolyear, a);
				fileOld >> sem;
				if (line == stringToWString(courseID) && schoolyear == stringToWString(schoolyearCur) && sem == semCur) getline(fileOld, line);
				else {
					fileNew << endl << line << "," << lineTmp << "|" << schoolyear << "," << sem;
					getline(fileOld, line);
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
	time_t now = time(0);
	tm* ltm = localtime(&now);

	ifstream read;
	read.open(dir + dirRegis + "Registration.txt", ios_base::in);

	if (!read.is_open()) {
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

	if (!can_Register_Course(dateCur, dateStart, dateEnd, timeCur, timeStart, timeEnd)) {
		cout << "Registration has expired!" << endl;
		return;
	}


	bool running = true;
	int choose;
	ifstream fileOld;
	ofstream fileNew;
	do {
		if (Node->subregis == nullptr) {
			cout << "Nothing to delete" << endl;
			return;
		}

		int semCur = NULL;
		string schoolyearCur = schoolYearCurrent(semCur);

		view_Reigstration_Results(Node->subregis, schoolyearCur, semCur);

		cout << "Enter the number of course to remove (0 to exit): ";
		int choose;
		cin >> choose;
		if (choose <= 0) {
			running = false;
		}

		else if (choose > list_Len_In_Sem(Node->subregis, schoolyearCur, semCur)) cout << "Your chosen course is exceed the number of courses! Please try again!" << endl;
		else {
			_Subjects* cur = Node->subregis;
			while (cur->subjects_Data.course_Data.schoolYear != schoolyearCur || cur->subjects_Data.course_Data.semNo != semCur) cur = cur->data_Next;
			for (int i = 1; i < choose; i++) cur = cur->data_Next;
			string courseName = cur->subjects_Data.course_Data.course_Name;
			remove_From_List(Node, courseName);
			remove_Courses_TextFile(Node, cur->subjects_Data.course_Data.course_ID, schoolyearCur, semCur);
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

void menu_ScoreBoard_Student(_Student* Node) {
	ifstream readSem, readSchoolyear;

	readSchoolyear.open(dir + dirSchoolYear + "School_Year.txt", ios_base::in);

	int numOfLine = check_Line(dir + dirSchoolYear + "School_Year.txt");
	int sumLine = 0;
	string line, schoolyear;

	for (int i = 0; i < numOfLine; i++) {
		getline(readSchoolyear, line);
		sumLine += check_Line(dir + dirSchoolYear + line + ".txt") / 3;
	}

	readSchoolyear.seekg(0, readSchoolyear.beg);

	string* menu = new string[sumLine + 1];

	menu[sumLine] = "Back";
	int i = sumLine - 1;
	for (int k = 0; k < numOfLine; k++) {
		getline(readSchoolyear, schoolyear);
		readSem.open(dir + dirSchoolYear + schoolyear + ".txt", ios_base::in);
		int lineTmp = check_Line(dir + dirSchoolYear + schoolyear + ".txt") / 3;
		for (int k = 0; k < lineTmp; k++) {
			getline(readSem, line);
			menu[i] = line + " " + schoolyear;
			for (int j = 0; j < 2; j++) getline(readSem, line);
			i--;
		}
		readSem.close();
	}

	int step = 0, tmp;
	bool running = true;
	while (running) {
		while (true) {
			system("cls");
			for (int k = 0; k < sumLine + 1; k++) {
				if (k == step) {
					textcolor(12);
					GotoXY(44, 10 + k);
					cout << " > " << menu[k] << " < " << endl;
					textcolor(15);
				}
				else {
					textcolor(15);
					GotoXY(45, 10 + k);
					cout << " " << menu[k] << " " << endl;
				}
			}
			tmp = _getch();
			if (tmp == 's' || tmp == 'S' || tmp == 80) {
				step++;
				if (step >= sumLine + 1) step = 0;
			}
			if (tmp == 'w' || tmp == 'W' || tmp == 72) {
				step--;
				if (step < 0) step = sumLine;
			}
			if (tmp == 13 || tmp == 32) break;
		}
		if (step == sumLine) {
			delete[] menu;
			running = false;
			return;
		}
		else {
			for (int k = 0; k < 9; k++) schoolyear[k] = menu[step][11 + k];
			int sem = menu[step][9] - 48;
			system("cls");
			displayScoreboard_Student(Node->subregis, schoolyear, sem);
			cout << endl << "Press any key to exit..." << endl;
			int sth = _getch();
		}
	}
}

void displayScoreboard_Student(_Subjects* Node, string schoolyear, int semCur) {
	system("cls");
	GotoXY(12, 4);
	cout << char(218); for (int i = 0; i < 94; i++) {
		GotoXY(13 + i, 4);
		if (i == 13 || i == 25 || i == 56 || i == 64 || i == 70 || i == 78 || i == 86) cout << char(194);
		else cout << char(196);
	}
	cout << char(191) << endl;
	GotoXY(12, 5); cout << char(179);

	GotoXY(16, 5); cout << "Semester";
	GotoXY(26, 5); cout << char(179) << " Course ID";
	GotoXY(38, 5); cout << char(179); GotoXY(47, 5); cout << "Name of Course";
	GotoXY(69, 5); cout << char(179) << "Credits";
	GotoXY(77, 5); cout << char(179) << " Mid";
	GotoXY(83, 5); cout << char(179) << " Other";
	GotoXY(91, 5); cout << char(179) << " Final";
	GotoXY(99, 5); cout << char(179) << " Total";
	GotoXY(107, 5); cout << char(179);

	GotoXY(12, 6); cout << char(195);
	for (int i = 0; i < 94; i++) {
		if (i == 13 || i == 25 || i == 56 || i == 64 || i == 70 || i == 78 || i == 86) cout << char(197);
		else cout << char(196);
	}
	cout << char(180) << endl;
	
	int numSub = list_Len_Available_Score(Node, schoolyear, semCur);

	_Subjects* cur = Node;
	while (cur->subjects_Data.course_Data.schoolYear != schoolyear || cur->subjects_Data.course_Data.semNo != semCur) cur = cur->data_Next;

	for (int i = 0; i <= 2 * numSub - 1; i++) {
		if (i % 2 == 0) {
			while (!(cur->subjects_Data.course_Data.score.isScore)) cur = cur->data_Next;
 			GotoXY(12, 7 + i); cout << char(179) << "HK" + to_string(semCur) + " " + schoolyear;
			GotoXY(26, 7 + i); cout << char(179);
			GotoXY(28, 7 + i); cout << cur->subjects_Data.course_Data.course_ID;
			GotoXY(38, 7 + i); cout << char(179);
			GotoXY(39, 7 + i); cout << cur->subjects_Data.course_Data.course_Name;
			GotoXY(69, 7 + i); cout << char(179);
			GotoXY(73, 7 + i); cout << cur->subjects_Data.course_Data.credit;
			GotoXY(77, 7 + i); cout << char(179);
			GotoXY(78, 7 + i); cout << cur->subjects_Data.course_Data.score.midtermMark;
			GotoXY(83, 7 + i); cout << char(179);
			GotoXY(84, 7 + i); cout << cur->subjects_Data.course_Data.score.otherMark;
			GotoXY(91, 7 + i); cout << char(179);
			GotoXY(92, 7 + i); cout << cur->subjects_Data.course_Data.score.finalMark;
			GotoXY(99, 7 + i); cout << char(179);
			GotoXY(100, 7 + i); cout << cur->subjects_Data.course_Data.score.totalMark;
			GotoXY(107, 7 + i); cout << char(179);
			cur = cur->data_Next;
		}
		else {
			GotoXY(12, 7 + i);
			if (i == 2 * numSub - 1) cout << char(192);
			else cout << char(195);
			for (int k = 0; k < 94; k++) {
				GotoXY(13 + k, 7 + i);
				if (k == 13 || k == 25 || k == 56 || k == 64 || k == 70 || k == 78 || k == 86) {
					if (i == 2 * numSub - 1) cout << char(193);
					else cout << char(197);
				}
				else cout << char(196);
			}
			if (i == 2 * numSub - 1) cout << char(217);
			else cout << char(180);
		}
	}
}