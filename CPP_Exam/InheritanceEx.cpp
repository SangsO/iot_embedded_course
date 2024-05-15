#include <iostream>
#include <string>
using namespace std;

class Point {
private: //������ �����Ǿ����� -> private�� ����� �޾Ƶ� ������ �ش� Ŭ���������� ���� ����
	int x, y;
public :

	void set(int x, int y) { this->x = x; this->y = y; }
	void showPoint() {
		cout << "(" << x << "," << y << ")" << endl;
	}
	//***********************************************************
	
//	Point() { 
//		x = 0;
//		y = 0;
//	}
	Point(int x = 0, int y = 0) { // Point(int x, int y) �� ������ ���� �����ع���(16~19 �ڵ�� �������� �ڵ�)
		this->x = x;
		this->y = y;
	}
	//***********************************************************
};

class ColorPoint : public Point {
	string color;
public :
	void setColor(string color) { this->color = color; }
	void showColorPoint(); 
};

void ColorPoint::showColorPoint() {
	cout << color << ":";	
	showPoint();	//public �Ӽ��� ��ġ ���ο� ���ǵȰ�ó�� ����� �޾ƿ�
}

int main() {
//	Point p;
	
//	p.showPoint(); // ->�����ڰ� ���� : �����������

	ColorPoint cp;

//	cp.showPoint();

	cp.set(3, 4);
	cp.setColor("Red");
	cp.showColorPoint();
}