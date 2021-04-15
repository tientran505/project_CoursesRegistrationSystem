#include "function.h"
#include "staff.h"
#include "student.h"

void staff_Menu(string username, _Student*& headStu) {
	headStu = nullptr;
	int choose;
	do {
		cout << "Choose your option" << endl;
		cout << "1. View info" << endl;
		cout << "2. Change Password" << endl;
		cout << "3. Create School year" << endl;
		cout << "4. Create Courses" << endl;
		cout << "5. Add student lists to the system" << endl;
		cout << "6. Log out" << endl;
		cin >> choose;
		switch (choose)
		{
		case 1: {
			showInfo_Staff(username);
			break;
		}
		case 2: {
			cout << "This feature is still in progress. Please try again later" << endl;
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
			string path;
			listStudents(path, headStu);
			break;
		}
		}
	} while (choose != 6);
}


void student_Menu(_Student* Node) {
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
			CoursesRegistration(Node);
			break;
		}

		case 4: {
			CourseRegistrationResult(Node);
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

void log_In_System() {
	_Student* head = nullptr;
	string username;
	int choose;
	
	int running = true;
	do {
		cout << "Log in:" << endl;
		cout << "\t1. Students of HCMUS" << endl;
		cout << "\t2. Academic Staff of HCMUS" << endl;

		cin >> choose;

		switch (choose)
		{
		case 1: {
			_Student* Node = logInSystem_Student(head);
			student_Menu(Node);
			break;
		}
		case 2: {
			staff_Login(username);
			staff_Menu(username, head);
			break;
		}
		default:
			break;
		}
	} while (running); 

	deleteStudentList(head);
}
