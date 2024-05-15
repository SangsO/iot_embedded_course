#include <iostream>
using namespace std;

class PrivateAccessError {
private :
	int a;
	void f();
	PrivateAccessError();
public:
	int b;
	PrivateAccessError(int x);
	void g();
};

PrivateAccessError::PrivateAccessError() {
	a = 1;
	b = 2;
}
PrivateAccessError::PrivateAccessError(int x) {
	a = x;
	b = x;
}

void PrivateAccessError::f() {
	a = 5;
	b = 5;
}

void PrivateAccessError::g() {
	a = 6;
	b = 6;
}

int main() {
	PrivateAccessError objA;// ������ PrivateAcessError�� private ���� �����ؼ� ���� ����
	PrivateAccessError objB(100);
	objB.a = 10; //a�� PrivateAccessErrorŬ������ private ����� ���� ����
	objB.b = 20;
	objB.f();  //f�� PrivateAccessErrorŬ������ private ����� ���� ����
	objB.g();

}