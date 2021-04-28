#include "function.h"

void loadStudentList(string path, _Student*& head);
void displayStudentList(string path, _Student* head);
void deleteStudentList(_Student*& head);
void convertAccountOfStudent(string path, _Student* head);
void listStudents(_Student*& head);
void loadStu_Save(_Student*& pHead);
void staff_Menu(string username, _Student*& headStu);
void staff_Login(string& username);
void showInfo_Staff(string username);
void add_Schoolyear(Date& schoolyear);
void createCourseList(string path);
void update_Course_Info();
void delete_Courses();
void create_Course_Registration();
bool is_Created_Sem_Before(string line, string schoolyear);
void arrange_Sem(string schoolyear, string sem);