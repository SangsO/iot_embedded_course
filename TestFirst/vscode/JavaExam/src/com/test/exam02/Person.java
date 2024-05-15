package com.test.exam02;

public class Person {
    
    private String name;  // 형식 앞에 아무것도 안쓸경우 default 접근 제한자가 생략되어있다_이하 동일
    private int age = 23;
    private String gender;

    public Person(){}

    public Person(String name, int age, String gender){

        this.name = name; //현재this의 전역변수를 말함
        this.age = age;
        this.gender = gender;


    } //public Person의 마침

    public String getName() {
        return name;  //여기의 name은 위 전역변수의 name이다.
    }
    public int getAge() {
        return age;
    }
    public String getGender() {
        return gender;
    }

    //setter 매서드
    public void setName(String name) {
        this.name = name;
    }
    public void setAge(int age) {
        this.age = age;
    }
    public void setGender(String gender) {
        this.gender = gender;
    }
    public void smile() {System.out.println("웃어라");}
    public void anger() {System.out.println("화내라");}

    
}
