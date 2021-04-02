#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "function.h"   
#include "student.h"
using namespace std;

int main() {
	_Student* head;
	cout << "Input name of class to input: ";
	string sTmp;
	cin >> sTmp;
	loadStudentList(sTmp + ".csv", head);
	string s;
	
	cout << "Name the file of List: ";
	cin >> s;
	displayStudentList(s + ".csv", head);
	deleteStudentList(head);
	return 0;
}