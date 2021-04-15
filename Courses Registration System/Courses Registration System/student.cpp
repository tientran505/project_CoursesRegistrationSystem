#include "function.h"
#include "student.h"

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
		cout << "There is nothing any student lists in system. Please contact to Academic Staff for more detail" << endl;
		return nullptr;
	}
	while (true) {
		cout << "Username: ";
		cin >> userNameTmp;
		cout << "Password: ";
		cin >> passWordTmp;
		_Student* pCur = head;
		while (pCur->pNext != nullptr) {
			if (userNameTmp == pCur->data.student_Account.ID && passWordTmp == pCur->data.student_Account.password) {
				cout << "-------------------------------\n" << "Login successfully" << endl;
				return pCur;
			}
			pCur = pCur->pNext;
		}
		cout << "Invalid login, please try again" << endl;
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

void readCourse(_Student* Node) {
	int a;
	string tr;
	fstream f;
	f.open(Node->data.class_Of_Student + ".txt");
	getline(f, tr, '\n');
	a = stringToInt(tr);
	while (a != Node->data.ID_Student) {
		getline(f, tr, '\n');
		a = stringToInt(tr);
	}
	string* temp = new string[tr.size() - 8];
	for (int i = 8; i < tr.size(); i++) {
		temp[i - 8] = tr[i];
	}
	f.close();
	for (int i = 0; i < tr.size() - 8; i++) {
		cout << temp[i];
	}
	delete[] temp;
}
void CoursesRegistration(_Student* Node) {
	cout << " regist courses";
	Node->data.stu_Score == nullptr;
}
void CourseRegistrationResult(_Student* Node) {
	cout << " course registration result: ";
	int t = 0;
	while ((Node->data.stu_Score) != nullptr) {
		int n = (Node->data.stu_Score->data_ScoreBoard.course_Data.course_Name).length();
		for (int i = 0; i < n - 1; i++) {
			cout << Node->data.stu_Score->data_ScoreBoard.course_Data.course_Name[i];
		}
		t++;
		Node->data.stu_Score = Node->data.stu_Score->dataNext;
	}
	if (t == 0) { cout << " there is no result"; }
}
void subjectsList() {
	int n;
	subject sub;
	ofstream fout;
	fout.open("subjectsList.txt", ios_base::out);
	if (!fout.is_open()) {
		cout << "Can not open file..." << endl;
		return;
	}
	cout << "Please input number of subjects: ";
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cout<< endl << "Please input subject title: ";
		cin >> sub.title;
		fout << sub.title;
		cout << endl << "Please input subject ID: ";
		cin >> sub.IDsubject;
		fout << sub.IDsubject;
	}
}
void deletecourseRegis(_Student* StuCur)
{
	_Subjects* deletesub;
	cout << "Type course ID remove: ";
	cin >> deletesub->subjects_Data.course_Data.course_ID;
	_Subjects* temp = StuCur->data.subregis;
	while (deletesub->subjects_Data.course_Data.course_ID != temp->subjects_Data.course_Data.course_ID)
	{
		temp = temp->data_Next;
	}
	delete deletesub;
}