// #pragma once
#ifndef _PrivateAccessError_H_
#define _PrivateAccessError_H_

#endif

class PrivateAccessError {

public:
	int b;
	PrivateAccessError(int x);
	void g();

	int a;
	void f();
	PrivateAccessError();

	void setA(int); //A의 값을 설정, 리턴값 없음, 매개변수 있음
	int getA();	//현재 A에 있는 값을 리턴, 매개변수 없음
};

