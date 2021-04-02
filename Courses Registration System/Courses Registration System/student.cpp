#include "student.h"
#include "function.h"
void ReadStudent_CSV(const char* path, _NodeStudent*& students)
{
	students = nullptr;
	int line = 0;
	ifstream fin(path);
	if (fin.bad())
	{
		cout << "File not found";
		exit(0);
	}
	
	_NodeStudent* stuCur = nullptr;
	char a = ',',b = '/';
	while (!fin.eof())
	{
		if (students == nullptr)
		{
			_NodeStudent* students = new _NodeStudent;
			stuCur = students;
		}

		else {
			stuCur->pNext = new _NodeStudent;
			stuCur = stuCur->pNext;
		}

		fin >> stuCur->data.Number_In_Class >> a; 
		fin >> stuCur->data.ID >> a;
		getline(fin, stuCur->data.Firstname, ',');
		getline(fin, stuCur->data.Lastname, ',');
		getline(fin, stuCur->data.Gender, ',');
		fin >> stuCur->data.Date_Of_Birth.day >> b;
		fin >> stuCur->data.Date_Of_Birth.month >> b;
		fin >> stuCur->data.Date_Of_Birth.year;
		stuCur->pNext = nullptr;
	}
	fin.close();
}
