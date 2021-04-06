#ifndef _STUDENT_H_
#define _STUDENT_H_
#include "function.h"

void loadStudentList(string path, _Student*& head);
void displayStudentList(string path, _Student* head);
void deleteStudentList(_Student*& head);
void convertAccountOfStudent(string path, _Student* head);
void logInSystem_Student(_Student* head);


#endif

