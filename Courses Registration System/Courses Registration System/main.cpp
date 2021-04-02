#include "function.h"
#include "student.h"

int main() {
	const char* path = "D:\\Desktop\\testdemo.csv";
	_NodeStudent* student = nullptr;
	currentDateTime();
	ReadStudent_CSV(path, student);
}