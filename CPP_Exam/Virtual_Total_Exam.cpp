#include <iostream>
#include <string>
using namespace std;

class Animal {
private:
	string name;
	int age;
public:
	Animal();
	string bark;	
	friend void running(Animal* pAnimal);
	virtual void crying() = 0;
	Animal(string name, int age) {
		this->name = name;
		this->age = age;
		cout << "Animal ����" << endl;
	};
	
	string getName() {
		return name;
	}
	int getAge() {
		return age;
	}
	string getBark() {
		return bark;
	}

};


class Dog : public Animal {
	
public :
	Dog(string name, int age, string bark) : Animal(name, age) {
		this->bark = bark;
		cout << "Dog ����" << endl;		
	}
	virtual void crying() {
		cout << this->bark << endl;
	}
	

};


class Cat : public Animal {
	
public :
	Cat(string name, int age, string bark) : Animal(name, age) {
		this->bark = bark;
		cout << "Dog ����" << endl;
	}
	virtual void crying() {
		
		cout << this-> bark << endl;
	}
	

};

void running(Animal* pAnimal) {
	cout << pAnimal->name << " �� �޸���" << endl;
}
void crying(Animal* pAnimal) {
	pAnimal->crying();
}

int main() {
	cout << " --- �߻�Ŭ������ �Ļ�Ŭ���� ���� ---\n";
	
	Dog* dog = new Dog("������", 4, "�۸�");
	Cat* cat = new Cat("�����", 2, "�߿�");

	cout << "\n --- �Ű������� ������ ���� ---\n";
	
	crying(dog);
	crying(cat);
	running(dog);
	running(cat);

	cout << "\n --- �⺻ ��������� ���� ���� ---\n";

	Dog copyDog(*dog);
	cout << copyDog.getName() << endl;
	cout << copyDog.getAge() << endl;
	cout << copyDog.getBark() << endl;
	
	cout << "\n --- �Ҹ��� ���� ---\n";

	delete dog;
	delete cat;

	return 0;
}