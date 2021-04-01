#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "function.h"   
#include "student.h"
using namespace std;

int main() {
	StudentList* head;
	loadStudentList("testdemo.csv", head);
	string s;
	cout << "Name the file of List: ";
	cin >> s;
	displayStudentList(s + ".csv", head);
	deleteStudentList(head);
	
	return 0;
}