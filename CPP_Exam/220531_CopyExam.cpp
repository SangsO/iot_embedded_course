#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
using namespace std;

class Person {
	char* name; // char name[10];�� ��� ������ ������ �ʴ´�
	int id;
public :
	Person(int id, const char* name);
	Person(const Person& Person); // ������
	~Person();
	void changeName(const char* name);
	void show() { cout << id << ',' << name << endl; }
};

Person::Person(int id, const char* name) {
	this->id = id;
	int len = strlen(name); //memory �Ҵ��Ϸ��� ũ����
	this->name = new char[len + 1];
	strcpy(this->name, name);
}

Person::~Person() {
	if (name)
		delete[] name;
}

Person::Person(const Person& Person) { //����Ʈ ������ -> ���� ����
//	this->name = Person.name; //����Ʈ
	this->id = Person.id;	  //����Ʈ
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
	Person daughter(father); //���� Ÿ������ ����

	cout << "daughter ��ü ���� ���� ----" << endl;

	father.show();
	daughter.show();

	daughter.changeName("Grace");
	cout << "daughter �̸��� Grace�� ���� �� ----" << endl;
	father.show();
	daughter.show();

	return 0;
}