#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
using namespace std;

class Person {
	char* name; // char name[10];일 경우 문제가 생기지 않는다
	int id;
public :
	Person(int id, const char* name);
	Person(const Person& Person); // 생성자
	~Person();
	void changeName(const char* name);
	void show() { cout << id << ',' << name << endl; }
};

Person::Person(int id, const char* name) {
	this->id = id;
	int len = strlen(name); //memory 할당하려고 크기계산
	this->name = new char[len + 1];
	strcpy(this->name, name);
}

Person::~Person() {
	if (name)
		delete[] name;
}

Person::Person(const Person& Person) { //디폴트 생성자 -> 깊은 복사
//	this->name = Person.name; //디폴트
	this->id = Person.id;	  //디폴트
	//
	int len = strlen(Person.name); // (name)
	this->name = new char[len + 1];
	strcpy(this->name, Person.name); // name -> Person.name
}

void Person::changeName(const char* name) {
	if (strlen(name) > strlen(this->name))
		return;
	strcpy(this->name, name);
}

int main() {
	Person father(1, "Kitae");
	Person daughter(father); //참조 타입으로 받음

	cout << "daughter 객체 생성 직후 ----" << endl;

	father.show();
	daughter.show();

	daughter.changeName("Grace");
	cout << "daughter 이름을 Grace로 변경 후 ----" << endl;
	father.show();
	daughter.show();

	return 0;
}