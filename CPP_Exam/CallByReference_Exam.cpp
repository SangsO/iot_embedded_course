#include <iostream>
using namespace std;

void swapRef(int& a, int& b) {

	int tmp;
	tmp = a;
	a = b;
	b = tmp;
	cout << "swapRef() : " << a << ' ' << b << endl;
}
void swap(int* a, int* b) {

	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
	cout << "swap() : " << *a << ' ' << *b << endl;
}

int main() {

	int m = 2, n = 9;
	swapRef(m, n);
	cout << "main() : " << m << ' ' << n;
}
