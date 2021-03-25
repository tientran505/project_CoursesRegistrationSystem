#include "function.h"

int main() {
	ofstream fileOut;
	ifstream fileIn;
	fileIn.open("input.csv", ios_base::in);

	for (int i = 0; i < 10; i++) {
		fileIn >> i;
	}

	fileIn.close();
	fileOut.open("output.csv", ios_base::out);

	for (int i = 0; i < 10; i++) {
		fileOut << i << "," << i*i << endl;
	}

	fileOut.close();

	return 0;
}