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

	void setA(int); //A�� ���� ����, ���ϰ� ����, �Ű����� ����
	int getA();	//���� A�� �ִ� ���� ����, �Ű����� ����
};

