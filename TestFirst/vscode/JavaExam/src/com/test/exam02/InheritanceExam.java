package com.test.exam02;

class Fruit{

    int color;
    int taste;
    void pop() {System.out.println("과일 개맛?��?��.");}

} //class Fruit 마침

class Apple extends Fruit {

    int price;
    int perfume;

    void cut() {System.out.println("?��과�?? 조져?��");}

} //class Apple 마침

public class InheritanceExam {

    public static void main(String[] args) {
        
        Apple apple = new Apple();

        apple.pop();

    }
    
}
