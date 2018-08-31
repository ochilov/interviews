#include <iostream>
#include <bitset>

void print_minmax(uint32_t number) {
    using namespace std;
    bitset<32> num(number), min, max;
    for (size_t i = 0, cnt = num.count(); i < cnt; i++) {
        min.set(i);
        max.set(max.size()-1 - i);
    }
    cout << "min = " << min.to_ulong() << endl;
    cout << "max = " << max.to_ulong() << endl;
}

int main() {
	using namespace std;
    uint32_t number;

    cout << "Calculate min|max of input number complected only '1' in binnary" << endl;
    cout << "Please enter a number: ";
    cin >> number;

    cout << "Number in binary is " << bitset<32>(number) << endl;
    print_minmax(number);
	return  0;
}