#include <iostream>
#include <string.h>

void RemoveDups(char* p) {
	char* pre_p = p++;
	for (; *p != 0; ++p) {
		if (*pre_p == *p) {
			continue;
		}
		*(++pre_p) = *p;
	}
	*(++pre_p) = *p;
};


int main() {
	using namespace std;
	cout << "Removing duplicate symbols from text" << endl;
	while (true) {
		cout << endl << "\'Ctrl + Z\' to exit" << endl;
		cout << "input  text: ";
		char buff[256];
		cin.getline(buff, sizeof(buff));
		if (strcasecmp("x", buff) == 0) {
			break;
		}
		RemoveDups(buff);
		cout << "output text: " << buff << endl << endl;
	}
	return 0;
}