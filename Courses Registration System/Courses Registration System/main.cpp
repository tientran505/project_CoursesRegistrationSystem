#include "function.h"
#include "student.h"

int main() {
	const char* path = "D:\\Desktop\\hello.csv";
	_NodeStudent* student = nullptr;
	currentDateTime();
	ReadStudent_CSV(path, student);
	_NodeStudent* pCur = student;
	while (pCur != nullptr)
	{
		cout << pCur->data.Firstname;
		pCur = pCur->pNext;
	}
}