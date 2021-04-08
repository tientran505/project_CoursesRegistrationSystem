#include "function.h"   
#include "student.h"
#include "staff.h"

int main() {
	currentDateTime();
	_Student* head;
	cout << "Input name of class to access: ";
	string sTmp;
	cin >> sTmp;
	loadStudentList(dir + dirClass + sTmp + ".csv", head);
	displayStudentList(dir + dirClass + sTmp + "_Info" + ".csv", head);
	convertAccountOfStudent(dir + dirClass + sTmp + "_Account" + ".txt", head);
	logInSystem_Student(head);
	deleteStudentList(head);
	return 0;
}