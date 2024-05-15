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
		cout << "Animal 생성" << endl;
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
		cout << "Dog 생성" << endl;		
	}
	virtual void crying() {
		cout << this->bark << endl;
	}
	

};


class Cat : public Animal {
	
public :
	Cat(string name, int age, string bark) : Animal(name, age) {
		this->bark = bark;
		cout << "Dog 생성" << endl;
	}
	virtual void crying() {
		
		cout << this-> bark << endl;
	}
	

};

void running(Animal* pAnimal) {
	cout << pAnimal->name << " 가 달린다" << endl;
}
void crying(Animal* pAnimal) {
	pAnimal->crying();
}

int main() {
	cout << " --- 추상클래스와 파생클래스 구현 ---\n";
	
	Dog* dog = new Dog("강아지", 4, "멍멍");
	Cat* cat = new Cat("고양이", 2, "야옹");

	cout << "\n --- 매개변수의 다형성 구현 ---\n";
	
	crying(dog);
	crying(cat);
	running(dog);
	running(cat);

	cout << "\n --- 기본 복사생성자 직접 구현 ---\n";

	Dog copyDog(*dog);
	cout << copyDog.getName() << endl;
	cout << copyDog.getAge() << endl;
	cout << copyDog.getBark() << endl;
	
	cout << "\n --- 소멸자 실행 ---\n";

	delete dog;
	delete cat;

	return 0;
}