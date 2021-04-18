#include "function.h"
#include "staff.h"
#include "student.h"
#include<conio.h> // de getchar
void menu_Course_Staff();

void textcolor(int color) {
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, color);
	return;
}
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}

void GotoXY(int x, int y) {

	COORD coord;

	coord.X = x;

	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}
void FixConsoleWindow() {

	HWND consoleWindow = GetConsoleWindow();

	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);

	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);

	SetWindowLong(consoleWindow, GWL_STYLE, style);
	return;

}

void ChoosedStaff(int x, int y) {
	textcolor(3);
	GotoXY(3 + x, 2 + y); cout << "LOGIN AS STAFF";
	GotoXY(x, y);	cout << char(201);
	for (int i = x + 1; i < x + 20; i++) {
		cout << char(205);
	}
	for (int i = y + 1; i < y + 4; i++) {
		GotoXY(x, i);
		cout << char(186);
	}
	GotoXY(x, 4 + y);	cout << char(200);
	for (int i = x + 1; i < x + 20; i++) {
		cout << char(205);
	}
	GotoXY(20 + x, y);	cout << char(187);
	for (int i = y + 1; i < y + 4; i++) {
		GotoXY(20 + x, i);
		cout << char(186);
	}
	GotoXY(20 + x, 4 + y);	cout << char(188);
	textcolor(15);
}
void StaffChoose(int x, int y) {
	GotoXY(3 + x, 2 + y); cout << "LOGIN AS STAFF";
	GotoXY(x, y);
	for (int i = x; i < x + 20; i++) {
		cout << char(196);
	}
	GotoXY(x, y);
	for (int i = y; i < y + 5; i++) {
		GotoXY(x, i);
		cout << char(179);
	}
	GotoXY(x, y + 4);
	for (int i = x; i < x + 20; i++) {
		cout << char(196);
	}
	for (int i = 1; i < 4; i++) {
		GotoXY(20 + x, y + i);
		cout << char(179);
	}
	GotoXY(x, y);	cout << char(218);
	GotoXY(x, 4 + y);	cout << char(192);
	GotoXY(20 + x, y);	cout << char(191);
	GotoXY(20 + x, 4 + y);	cout << char(217);
}

void ChoosedStudent(int a, int b) {

	int x = a + 30, y = b;
	textcolor(3);
	GotoXY(3 + x, 2 + y); cout << "LOGIN AS STUDENT";
	GotoXY(x, y);	cout << char(201);
	for (int i = x + 1; i < x + 20; i++) {
		cout << char(205);
	}

	for (int i = y + 1; i < y + 4; i++) {
		GotoXY(x, i);
		cout << char(186);
	}
	GotoXY(x, 4 + y);	cout << char(200);
	for (int i = x + 1; i < x + 20; i++) {
		cout << char(205);
	}
	GotoXY(20 + x, y);	cout << char(187);
	for (int i = y + 1; i < y + 4; i++) {
		GotoXY(20 + x, i);
		cout << char(186);
	}
	GotoXY(20 + x, 4 + y);	cout << char(188);
	textcolor(15);
}

void StudentChoose(int a, int y) {
	int x = a + 30;
	GotoXY(3 + x, 2 + y); cout << "LOGIN AS STUDENT";
	GotoXY(x, y);

	for (int i = x; i <= x + 20; i++) {
		cout << char(196);
	}
	GotoXY(x, y);
	for (int i = y + 1; i < y + 5; i++) {
		GotoXY(x, i);
		cout << char(179);
	}
	GotoXY(x, y + 4);
	for (int i = x; i <= x + 20; i++) {
		cout << char(196);
	}
	for (int i = 1; i < 4; i++) {
		GotoXY(20 + x, y + i);
		cout << char(179);
	}
	GotoXY(x, y);	cout << char(218);
	GotoXY(x, 4 + y);	cout << char(192);
	GotoXY(20 + x, y);	cout << char(191);
	GotoXY(20 + x, 4 + y);	cout << char(217);
}
void staff_Menu(string username, _Student*& headStu);

int MainMenu(int x, int y) {
	int temp;
	int i = 0;
	//system("cls");
	ShowCur(0);
	ChoosedStaff(x, y);
	StudentChoose(x, y);
	while (true) {
		//system("cls");
		ShowCur;
		if (i == 0) {
			StudentChoose(x, y);
			ChoosedStaff(x, y);
		}
		if (i == 1) {
			ChoosedStudent(x, y);
			StaffChoose(x, y);
		}
		temp = _getch();
		if (temp == 'a' || temp == 'A' || temp == 75) {
			if (i == 0) i++;
			else i--;
		}
		if (temp == 'd' || temp == 'D' || temp == 77) {
			if (i == 1) i--;
			else i++;
		}
		else if (temp == 13 || temp == 32) {
			switch (i) {
			case 0: system("cls");
				return 1;
			case 1:system("cls");
				return 2;
			}
		}
	}
}


void staff_Menu(string username, _Student*& headStu) {
	Date schoolyear;
	int choose;
	int i = 0;
	int temp;
	system("cls");
	ShowCur(0);
	GotoXY(40, 5);
	string menu[6] = { "1. View info","2. Create Course Registration Session", "3. Create School year","4. Course Registration Management System", "5. Add student lists to the system" , "6. Log out" };
	do {
		while (true) {
			system("cls");
			for (int j = 0; j < 6; j++) {
				if (j == i) {
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
				i++;
				if (i == 6) i = 0;
			}
			if (temp == 'w' || temp == 'W' || temp == 72) {
				i--;
				if (i == -1) i = 5;
			}
			if (temp == 13 || temp == 32) break;
		}
		system("cls");
		i++;
		switch (i)
		{
		case 1: {
			showInfo_Staff(username);
			cout << endl;
			cout << " enter to continue";
			choose = _getch();
			
			break;
		}
		case 2: {
			create_Course_Registration();
			cout << endl;
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 3: {
			add_Schoolyear(schoolyear);
			cout << endl;
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 4: {
			menu_Course_Staff();
			cout << endl;
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 5: {
			listStudents(headStu);
			cout << endl;
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		}
		
	} while (i != 6);

}


void menu_Course_Staff() {
	int choose, running = true;
	do {
		cout << "1. Create/Add Course" << endl;
		cout << "2. View list of Course" << endl;
		cout << "3. Update Course infomation" << endl;
		cout << "4. Delete a course" << endl;
		cout << "5. Exit" << endl;
		cin >> choose;

		switch (choose) {
		case 1: {
			createCourseList(dir + dirCourse + "CoursesRegistration.txt");
			break;
		}
		case 2: {
			viewCourseList(dir + dirCourse + "CoursesRegistration.txt");
			break;
		}
		case 3: {
			update_Course_Info();
			break;
		}
		case 4: {
			delete_Courses();
			break;
		}
		}
	} while (choose != 5);
}

void student_Course_Menu(_Student* Node) {
	bool running = true;
	int choose;
	do {
		cout << "1. Register for the Course" << endl;
		cout << "2. Remove the Course" << endl;
		cout << "3. Courses registration results" << endl;
		cout << "4. Exit" << endl;

		cin >> choose;
		switch (choose) {
		case 1: {
			register_Course(Node);
			break;
		}
		case 2: {
			remove_Courses(Node->data.subregis);
			break;
		}
		case 3: {
			view_Reigstration_Results(Node->data.subregis);
			break;
		}
		default: {
			running = false;
			break;
		}
		}
	} while (running);
}

void student_Menu(_Student* Node) {
	cout << "Choose your option" << endl;
	cout << "[1]. View Info" << endl;
	cout << "[2]. Change password" << endl;
	cout << "[3]. Course Registration" << endl;
	cout << "[4]. View Scoreboard" << endl;
	cout << "[5]. Logout" << endl;

	int choose;
	cin >> choose;
	while (choose != 5) {
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
			student_Course_Menu(Node);
			break;
		}

		case 4: {
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

void log_In_System(int x, int y) {
	_Student* head = nullptr;
	loadStu_Save(head);
	cout << "Load success!" << endl;
	int choose;
	string username;

	int running = true;
	do {
		choose=MainMenu(x, y);
		
		switch (choose)
		{
		case 2: {
			_Student* Node = logInSystem_Student(head);
			student_Menu(Node);
			break;
		}
		case 1: {
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

