#include <iostream>
#include <bitset>


template<typename T>
void PrintBits(T num) {
	unsigned int bitsCount = sizeof(T)*8;
	char* bits = new char[bitsCount];
	for (unsigned int i = 0; i < bitsCount; ++i) {
		int bitN = (1 << i);
		bits[i] = (num & bitN) ? '1' : '0';
	}

	for (unsigned int i = bitsCount; i > 0; --i) {
		std::cout << bits[i-1];
	}
	delete[] bits;
};


int main() {
	using namespace std;
	cout << "Print binary view of the decimal number" << endl;
	while (true) {
		cout << endl << "\'Ctrl + Z\' to exit" << endl;
		int num = 0;
		cout << "decimal number: ";
		cin >> num;

		cout << "binary my func: 0b";
		PrintBits(num);
		cout << endl;

		cout << "binary  bitset: 0b";
		cout << std::bitset<sizeof(num)*8>(num);
		cout << endl;
	}
	return 0;
}