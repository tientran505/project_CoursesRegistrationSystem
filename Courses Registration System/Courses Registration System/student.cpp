#include "function.h"

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

void menu_Student(_Student* Node);

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

void logInSystem_Student(_Student* head) {
	string userNameTmp, passWordTmp;

	while (true) {
		cout << "Username: ";
		cin >> userNameTmp;
		cout << "Password: ";
		cin >> passWordTmp;
		_Student* pCur = head;
		while (pCur->pNext != nullptr) {
			if (userNameTmp == pCur->data.student_Account.ID && passWordTmp == pCur->data.student_Account.password) {
				cout << "-------------------------------\n" << "Login successfully" << endl;
				menu_Student(pCur);
				return;
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



void menu_Student(_Student* Node) {
	cout << "Choose your option" << endl;
	cout << "[1]. View Info" << endl;
	cout << "[2]. Change password" << endl;
	cout << "[3]. Sign up for the course" << endl;
	cout << "[4]. Courses registration results" << endl;
	cout << "[5]. View Scoreboard" << endl;
	cout << "[6]. Logout" << endl;

	int choose;
	cin >> choose;
	while (choose != 6) {
		switch (choose)
		{
		case 1: {
			showInfo_Student(Node);
			break;
		}

		case 2: {
			editPassword(Node);
			break;
		}

		case 3: {
			cout << "This feature is still in progress. Please try again later" << endl;
			break;
		}

		case 4: {
			cout << "This feature is still in progress. Please try again later" << endl;
			break;
		}

		case 5: {
			cout << "This feature is still in progress. Please try again later" << endl;
			break;

		}
		}
		cout << "--------------------------------------\nChoose your option" << endl;
		cout << "[1]. View Info" << endl;
		cout << "[2]. Change password" << endl;
		cout << "[3]. Sign up for the course" << endl;
		cout << "[4]. Courses registration results" << endl;
		cout << "[5]. View Scoreboard" << endl;
		cout << "[6]. Logout" << endl;
		cin >> choose;
	}
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
		cout<<"Please input subject title: ";
		cin >> sub.title;
		fout << sub.title;
		cout << endl << "Please input subject ID: ";
		cin >> sub.IDsubject;
		fout << sub.IDsubject;
	}
}