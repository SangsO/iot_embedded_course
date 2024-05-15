#include<iostream>
#include<string>
using namespace std;

class Animal {
private:
	string name;
	int age;
public:
	Animal(const Animal& a) { this->name = a.name; this->age = a.age; }
	Animal() :Animal("미정", 0) {  }
	Animal(string name, int age) {
		this->name = name;
		this->age = age;
		cout << "Animal 생성" << endl;
	};
	~Animal() { cout << "Animal 소멸" << endl; }
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
	Dog(string name = "댕댕이", int age = 1, string bark = "무음") : Animal(name, age) {
		this->bark = bark;
		cout << "Dog 생성" << endl;
	}
	~Dog() { cout << "Dog 소멸" << endl; }
	string getBark() {
		return bark;
	}
	virtual void crying() {
		cout << "강아지는 멍멍" << endl;
	}
};

class Cat : public Animal {
private:
	string bark;
public:
	Cat(string name = "냐", int age = 1, string bark = "무음") : Animal(name, age) {
		this->bark = bark;
		cout << "Cat 생성" << endl;
	}
	~Cat() { cout << "Cat 소멸" << endl; }
	string getBark() {
		return bark;
	}
	virtual void crying() {
		cout << "고양이는 야옹" << endl;
	}
};

void running(Animal* pAnimal) {	// friend 함수로 구현
	cout << pAnimal->name << "가 달린다" << endl;
}

void crying(Animal* pAnimal) {
	pAnimal->crying();	// 가상함수 실행
}

int main() {
	cout << "--추상클래스와 파생 클래스 구현--\n";

	Dog* dog = new Dog("강아지", 4, "멍멍");
	Cat* cat = new Cat("고양이", 2, "야옹");

	cout << "\n--매개변수의 다형성 구현--\n";
	crying(dog);
	crying(cat);
	running(dog);
	running(cat);

	cout << "\n--기본 복사 생성자 직접 구현--\n";
	Dog copyDog(*dog);
	cout << copyDog.getName() << endl;
	cout << copyDog.getAge() << endl;
	cout << copyDog.getBark() << endl;

	cout << "\n--소멸자 실행--\n";
	delete dog;
	delete cat;
	return 0;
}