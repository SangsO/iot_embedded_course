#include<iostream>
#include<string>
using namespace std;

class Animal {
private:
	string name;
	int age;
public:
	Animal(const Animal& a) { this->name = a.name; this->age = a.age; }
	Animal() :Animal("����", 0) {  }
	Animal(string name, int age) {
		this->name = name;
		this->age = age;
		cout << "Animal ����" << endl;
	};
	~Animal() { cout << "Animal �Ҹ�" << endl; }
	friend void running(Animal* pAnimal);
	virtual void crying() = 0;
	void setName(string name) { this->name = name; }
	string getName() { return name; }
	int getAge() { return age; }
};

class Dog : public Animal {
private:
	string bark;
public:
	Dog(string name = "�����", int age = 1, string bark = "����") : Animal(name, age) {
		this->bark = bark;
		cout << "Dog ����" << endl;
	}
	~Dog() { cout << "Dog �Ҹ�" << endl; }
	string getBark() {
		return bark;
	}
	virtual void crying() {
		cout << "�������� �۸�" << endl;
	}
};

class Cat : public Animal {
private:
	string bark;
public:
	Cat(string name = "��", int age = 1, string bark = "����") : Animal(name, age) {
		this->bark = bark;
		cout << "Cat ����" << endl;
	}
	~Cat() { cout << "Cat �Ҹ�" << endl; }
	string getBark() {
		return bark;
	}
	virtual void crying() {
		cout << "����̴� �߿�" << endl;
	}
};

void running(Animal* pAnimal) {	// friend �Լ��� ����
	cout << pAnimal->name << "�� �޸���" << endl;
}

void crying(Animal* pAnimal) {
	pAnimal->crying();	// �����Լ� ����
}

int main() {
	cout << "--�߻�Ŭ������ �Ļ� Ŭ���� ����--\n";

	Dog* dog = new Dog("������", 4, "�۸�");
	Cat* cat = new Cat("�����", 2, "�߿�");

	cout << "\n--�Ű������� ������ ����--\n";
	crying(dog);
	crying(cat);
	running(dog);
	running(cat);

	cout << "\n--�⺻ ���� ������ ���� ����--\n";
	Dog copyDog(*dog);
	cout << copyDog.getName() << endl;
	cout << copyDog.getAge() << endl;
	cout << copyDog.getBark() << endl;

	cout << "\n--�Ҹ��� ����--\n";
	delete dog;
	delete cat;
	return 0;
}