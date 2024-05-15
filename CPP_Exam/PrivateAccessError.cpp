#include "PrivateAccessError.h"

void PrivateAccessError::setA(int a) {

	this->a = a; //지역변수에 의해서 전역변수로 a를 선언해줘도 값이 가려지게 됨 

	//(좌변 a는 바깥에 있는 a여야함) 바깥에 있는 a에다가 지금 있는 함수 a를 넣어주려면 this를 이용

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