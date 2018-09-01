#include <iostream>

/*
Написать функцию, вычисляющую первые N простых чисел и помещающую эти числа в переданный ей массив.
*/

int FindPrimeNumbers(int count, int * find_list) {
    if (count < 1)
        return 0;
    find_list[0] = 2;
    int find_count = 1;

    for (int i = 3; find_count < count; i+=2) {
        bool is_prime = true;
        for (int j = 0; j < find_count; ++j) {
            if (i % find_list[j] == 0) {
                is_prime = false;
                break;
            }
        }
        if (!is_prime)
            continue;

        find_list[find_count++] = i;
    }
    return find_count;
};

int main() {
    using namespace std;
    int count = 0;

    cout << "Find prime numbers" << endl;
    cout << "Please enter the required count of simple numbers: ";
    cin >> count;

    int *primes_list = new int[count];
    FindPrimeNumbers(count, primes_list);

    cout << "Found list:" << endl; 
    for (int i = 0; i < count; ++i)
        cout << primes_list[i] << " ";
    cout << "." << endl; 
    delete[] primes_list;

    return  0;
}
