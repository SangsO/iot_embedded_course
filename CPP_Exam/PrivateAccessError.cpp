#include "PrivateAccessError.h"

void PrivateAccessError::setA(int a) {

	this->a = a; //���������� ���ؼ� ���������� a�� �������൵ ���� �������� �� 

	//(�º� a�� �ٱ��� �ִ� a������) �ٱ��� �ִ� a���ٰ� ���� �ִ� �Լ� a�� �־��ַ��� this�� �̿�

}

int PrivateAccessError::getA() {

	return a;
}

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