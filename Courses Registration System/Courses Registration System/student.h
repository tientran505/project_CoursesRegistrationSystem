#ifndef _STUDENT_H_
#define _STUDENT_H_
#include "function.h"

void loadStudentList(string path, StudentList*& head);
void displayStudentList(string path, StudentList* head);
void deleteStudentList(StudentList*& head);

#endif