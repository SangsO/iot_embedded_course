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
	PrivateAccessError objA;// 생성자 PrivateAcessError는 private 으로 선언해서 접근 못함
	PrivateAccessError objB(100);
	objB.a = 10; //a는 PrivateAccessError클래스의 private 멤버라서 접근 못함
	objB.b = 20;
	objB.f();  //f는 PrivateAccessError클래스의 private 멤버라서 접근 못함
	objB.g();

}