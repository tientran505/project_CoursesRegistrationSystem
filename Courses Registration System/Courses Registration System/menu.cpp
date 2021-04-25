#include "function.h"
#include "staff.h"
#include "student.h"

void menu_Course_Staff();
void staff_Menu(string username, _Student*& headStu);

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



int MainMenu(int x, int y) {
	int temp;
	int i = 0;
	system("cls");
	ShowCur(0);
	_Student* head = nullptr;
	loadStu_Save(head);
	cout << "Load success!" << endl;
	currentDateTime();
	ChoosedStaff(x, y);
	StudentChoose(x, y);
	while (true) {
		//system("cls");
		ShowCur;
		//currentDateTime();
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

void create_SemesterMenu(string schoolyear) {
	int i = 0;
	int tmp;
	Date startDate, endDate;
	GotoXY(40, 5);
	string menu[4] = { "Semester 1" , "Semester 2", "Semester 3", "Back" };


	bool running = true;
	
	while (running) {
		system("cls");
		GotoXY(40, 3);
		cout << "Choose a semester to register for the " << schoolyear << " school year!" << endl;
		for (int k = 0; k < 4; k++) {
			if (k == i) {
				textcolor(12);
				GotoXY(39, 5 + k);
				cout << " > " << menu[k] << " < " << endl;
				textcolor(15);
			}
			else {
				textcolor(15);
				GotoXY(40, 5 + k);
				cout << " " << menu[k] << " " << endl;
			}
		}
		tmp = _getch();
		if (tmp == 's' || tmp == 'S' || tmp == 80) {
			i++;
			if (i == 4) i = 0;
		}
		if (tmp == 'w' || tmp == 'W' || tmp == 72) {
			i--;
			if (i == -1) i = 2;
		}
		if (tmp == 13 || tmp == 32) running = false;
	}
	
	if (i == 3) return;
	system("cls");
	if (!is_Created_Sem_Before(menu[i], schoolyear)) return;
	GotoXY(39, 10);
	cout << "Enter start date of " << menu[i] << " (DD/MM/YYYY): ";
	cin >> startDate.day;
	cin.ignore(10, '/');
	cin >> startDate.month;
	cin.ignore(10, '/');
	cin >> startDate.year;
	GotoXY(39, 12);
	cout << "Enter end date of " << menu[i] << " (DD/MM/YYYY): ";
	cin >> endDate.day;
	cin.ignore(10, '/');
	cin >> endDate.month;
	cin.ignore(10, '/');
	cin >> endDate.year;

	ofstream fileOut;
	fileOut.open(dir + dirSchoolYear + schoolyear + ".txt", ios_base::app);

	if (check_Line(dir + dirSchoolYear + schoolyear + ".txt") != 0) fileOut << endl;

	fileOut << menu[i] << endl;
	fileOut << startDate.day << "/" << startDate.month << "/" << startDate.year << endl;
	fileOut << endDate.day << "/" << endDate.month << "/" << endDate.year;

	GotoXY(39, 14);
	cout << "Create semester succesfully!" << endl;
	GotoXY(39, 15);
	cout << "Press any key to continue...";
	int choose = _getch();
	fileOut.close();
}

void create_SchoolyearMenu() {
	int i = 0;
	int tmp;
	GotoXY(40, 5);
	int line = check_Line(dir + dirSchoolYear + "School_Year.txt");
	if (line == 0) {
		system("cls");
		GotoXY(40, 10);
		cout << "You have not created any school year before!" << endl;
		GotoXY(40, 11);
		cout << "Enter to continue..." << endl;
		int a = _getch();
		return;
	}
	ifstream read;
	bool running = true;
	string* menu = new string[line + 1];
	read.open(dir + dirSchoolYear + "School_Year.txt", ios_base::in);
	for (int j = 0; j < line + 1; j++) {
		if (j == line) menu[j] = "Back";
		getline(read, menu[j]);
	}

	while (running) {
		system("cls");
		for (int k = 0; k < line + 1; k++) {
			if (k == i) {
				textcolor(12);
				GotoXY(39, 5 + k);
				if (k == line) cout << " > " << menu[k] << " < " << endl;
				else cout << " > " << "Create Semesters for " << menu[k] << " < " << endl;
				textcolor(15);
			}
			else {
				textcolor(15);
				GotoXY(40, 5 + k);
				if (k == line) cout << " " << menu[k] << " " << endl;
				else cout << " " << "Create Semesters for " << menu[k] << " " << endl;
			}
		}
		tmp = _getch();
		if (tmp == 's' || tmp == 'S' || tmp == 80) {
			i++;
			if (i == line + 1) i = 0;
		}
		if (tmp == 'w' || tmp == 'W' || tmp == 72) {
			i--;
			if (i == -1) i = line;
		}
		if (tmp == 13 || tmp == 32) {
			running = false;
			break;
		}
	}
	if (i == line) {
		delete[] menu;
		return;
	}
	system("cls");
	create_SemesterMenu(menu[i]);
	delete[] menu;
}

void menu_Create_SY_Tmp() {
	int i = 0;
	string menu[3] = { "1. Create new School year", "2. Create new semester", "3. Back"};
	bool running = true;
	int tmp;
	while (running) {
		while (running) {
			system("cls");
			for (int k = 0; k < 3; k++) {
				if (k == i) {
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
				i++;
				if (i == 3) i = 0;
			}
			if (tmp == 'w' || tmp == 'W' || tmp == 72) {
				i--;
				if (i == -1) i = 2;
			}
			if (tmp == 13 || tmp == 32) break;
		}
		switch (i) {
		case 0: {
			Date schoolyear;
			add_Schoolyear(schoolyear);
			break;
		}
		case 1: {
			create_SchoolyearMenu();
			break;
		}
		case 2: {
			running = false;
			break;
		}
		}
	}
	

	
}

void staff_Menu(string username, _Student*& headStu) {
	int choose;
	int i = 0;
	bool running = true;
	int temp;
	system("cls");
	ShowCur(0);
	GotoXY(40, 5);
	string menu[6] = { "1. View info","2. Create Course Registration Session", "3. Create School year/Semester System","4. Course Registration Management System", "5. Add student lists to the system" , "6. Log out" };
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
		switch (i)
		{
		case 0: {
			showInfo_Staff(username);
			cout << endl;
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 1: {
			create_Course_Registration();
			cout << endl;
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 2: {
			menu_Create_SY_Tmp();
			break;
		}
		case 3: {
			menu_Course_Staff();
			break;
		}
		case 4: {
			listStudents(headStu);
			break;
		}
		case 5: {
			running = false;
		}
		}
		
	} while (running);

}

void menu_Course_Staff() {
	int choose;
	int i = 0;
	int temp;
	system("cls");
	ShowCur(0);

	string menu[5] = { "1. Create/Add Course", "2. View list of Course", "3. Update Course infomation", "4. Delete a course", "5. Exit"};
	do {
		while (true) {
			system("cls");
			for (int j = 0; j < 5; j++) {
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
				if (i == 5) i = 0;
			}
			if (temp == 'w' || temp == 'W' || temp == 72) {
				i--;
				if (i == -1) i = 4;
			}
			if (temp == 13 || temp == 32) break;
		}
		system("cls");
		i++;
		switch (i)
		{
		case 1: {
			createCourseList(dir + dirCourse + "CoursesRegistration.txt");
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 2: {
			viewCourseList(dir + dirCourse + "CoursesRegistration.txt");
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 3: {
			update_Course_Info();
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 4: {
			delete_Courses();
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		}
	} while (i != 5);
}

void student_Course_Menu(_Student* Node) {
	bool running = true;
	int choose;
	int temp;
	int i = 0;
	string menu[4] = { "1. Register for the Course","2. Remove the Course","3. Courses registration results","4. Exit" };
	do {
		while (true) {
			system("cls");
			for (int j = 0; j < 4; j++) {
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
				if (i == 4) i = 0;
			}
			if (temp == 'w' || temp == 'W' || temp == 72) {
				i--;
				if (i == -1) i = 3;
			}
			if (temp == 13 || temp == 32) break;
		}

		system("cls");

		i++;
		switch (i) {
		case 1: {
			register_Course(Node);
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 2: {
			remove_Courses(Node);
			cout << " enter to continue";
			choose = _getch();
			break;
		}
		case 3: {
			view_Reigstration_Results(Node->subregis);
			cout << " enter to continue";
			choose = _getch();
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
	int i = 1;
	int temp;
	system("cls");
	ShowCur(0);
	GotoXY(40, 5);
	string menu[6] = { "Choose your option","[1]. View Info", "[2]. Change password","[3]. Course Registration",  "[4]. View Scoreboard",  "[5]. Logout" };
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
				if (i == 6) i = 1;
			}
			if (temp == 'w' || temp == 'W' || temp == 72) {
				i--;
				if (i == 0) i = 5;
			}
			if (temp == 13 || temp == 32) break;
		}
		system("cls");
		
		switch (i)
		{
		case 1: {
			showInfo_Student(Node);
			cout << " enter to continue";
			temp = _getch();
			break;
		}

		case 2: {
			editPassword(Node);
			cout << " enter to continue";
			temp = _getch();
			break;
		}

		case 3: {
			student_Course_Menu(Node);
			break;
		}

		case 4: {
			cout << "This feature is still in progress. Please try again later" << endl;
			cout << " enter to continue";
			temp = _getch();
			break;
		}
		}
	} while (i != 5);
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

