#include "function.h"

void currentDateTime() {
	time_t now = time(0);
	tm* ltm = localtime(&now);

	cout << "Date: " << ltm->tm_mday << "/" << ltm->tm_mon + 1 << "/" << 1900 + ltm->tm_year << endl;
	cout << "Time: " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl;
}