#include "function.h"

void currentDateTime() {
	time_t now = time(0);

	cout << "Number of sec since January 1, 1970 is:: " << now << endl;

	tm* ltm = localtime(&now);

	cout << "Year: " << 1900 + ltm->tm_year << endl;
	cout << "Month: " << 1 + ltm->tm_mon << endl;
	cout << "Day: " << ltm->tm_mday << endl;
	cout << "Time: " << ltm->tm_hour << ":";
	cout << ltm->tm_min << ":";
	cout << ltm->tm_sec << endl;
}