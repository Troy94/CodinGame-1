
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	int size;

	cin >> size;

	unsigned int* a = new unsigned int[size / 16]; // <- input tab to encrypt
	unsigned int* b = new unsigned int[size / 16]; // <- output tab

	for (int i = 0; i < size / 16; i++) {   // Read size / 16 integers to a
		cin >> hex >> a[i];
	}

	

	for (int i = 0; i < size / 16; i++) {
		if (i > 0) {
			cout << ' ';
		}
		cout << setfill('0') << setw(8) << hex << b[i];       // print result
	}
	cout << endl;

	/*
	Good luck humans
	*/
	return 0;
}