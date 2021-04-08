#ifndef _STAFF_H_
#define _STAFF_H_
#include "function.h"

void loadStudentList(string path, _Student*& head);
void displayStudentList(string path, _Student* head);
void deleteStudentList(_Student*& head);
void convertAccountOfStudent(string path, _Student* head);
void listStudentsPush();

#endif