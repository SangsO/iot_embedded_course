#include <iostream>
using namespace std;

class Circle { //����ü�� �ƴϰ� !!!Ŭ����!!!
public : // �ۺ��̱� ������ �����Լ����� ������ �����ϴ�
	int radius;
	double getArea();
};

double Circle::getArea() {
	return 3.14 * radius * radius;
}// -> Ŭ���� �ȿ� �־��� �� ����

int main() {
	
	Circle donut;
	donut.radius = 1;
	double area = donut.getArea();
	cout << "donut ������ " << area << endl;
	
	Circle pizza;
	pizza.radius = 30; // pizza�� donut�� �޸� ������ �ٸ����� �־ donut�� radius�� �����ǰ� �ִ�.
	area = pizza.getArea();
	cout << "pizza ���� " << area << endl;

	return 0;
}