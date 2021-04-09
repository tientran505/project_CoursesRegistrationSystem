#include "function.h"   
#include "student.h"
#include "staff.h"

int main() {
	currentDateTime();
	_Student* head = nullptr;
	string path;
	listStudents(path, head);
	logInSystem_Student(head);
	deleteStudentList(head);
	return 0;
}