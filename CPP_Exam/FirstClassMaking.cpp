#include <iostream>
using namespace std;

class Circle { //구조체가 아니고 !!!클래스!!!
public : // 퍼블릭이기 때문에 메인함수에서 접근이 가능하다
	int radius;
	double getArea();
};

double Circle::getArea() {
	return 3.14 * radius * radius;
}// -> 클래스 안에 넣어줄 수 있음

int main() {
	
	Circle donut;
	donut.radius = 1;
	double area = donut.getArea();
	cout << "donut 면적은 " << area << endl;
	
	Circle pizza;
	pizza.radius = 30; // pizza와 donut의 메모리 공간은 다른데에 있어서 donut의 radius는 유지되고 있다.
	area = pizza.getArea();
	cout << "pizza 면적 " << area << endl;

	return 0;
}