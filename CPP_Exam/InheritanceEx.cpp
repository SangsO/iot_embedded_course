#include <iostream>
#include <string>
using namespace std;

class Point {
private: //원래는 생략되어있음 -> private은 상속을 받아도 무조건 해당 클래스에서만 접근 가능
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
	Point(int x = 0, int y = 0) { // Point(int x, int y) 를 디폴드 값을 지정해버림(16~19 코드와 합쳐지는 코드)
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
	showPoint();	//public 속성이 마치 내부에 정의된것처럼 상속을 받아옴
}

int main() {
//	Point p;
	
//	p.showPoint(); // ->생성자가 없다 : 정의해줘야함

	ColorPoint cp;

//	cp.showPoint();

	cp.set(3, 4);
	cp.setColor("Red");
	cp.showColorPoint();
}