#include <iostream>
using namespace std;

class Power {
	int kick;
	int punch;
public:
	Power(int kick = 0, int punch = 0) {
		this->kick = kick; this->punch = punch;
	}
	void show();
	Power operator+ (Power& op2);//참조 연산으로 해주면 좋다 (연산량 감소)
	bool operator==(Power& op2);
};

void Power::show() {
	cout << "kick=" << kick << ',' << "punch=" << punch << endl;
}

Power Power::operator+(Power& op2) {
	Power tmp;
	tmp.kick = this->kick + op2.kick;
	tmp.punch = this->punch + op2.punch;
	return tmp; // 객체 리턴 시 복사 생성자 생성되는것 잊지말것
}

bool Power::operator==(Power & op2) { // 외부 함수
	if (kick == op2.kick && punch == op2.punch) return true;
	else return false;
}

int main() {
	Power a(3, 5), b(4, 6), c;
	c = a + b;
	a.show();
	b.show();
	c.show();
	if (a == b) cout << "두 파워 동일" << endl;
	else cout << "파워가 다름" << endl;

}