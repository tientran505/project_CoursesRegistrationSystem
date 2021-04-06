#include "function.h"   
#include "student.h"


int main() {
	_Student* head;
	cout << "Input name of class to access: ";
	string sTmp;
	cin >> sTmp;
	loadStudentList(sTmp + ".csv", head);
	displayStudentList(sTmp + "_Info" + ".csv", head);
	convertAccountOfStudent(sTmp + "_Account" + ".txt", head);
	logInSystem_Student(head);
	deleteStudentList(head);
	return 0;
}