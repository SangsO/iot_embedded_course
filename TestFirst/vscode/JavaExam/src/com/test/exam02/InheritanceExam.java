package com.test.exam02;

class Fruit{

    int color;
    int taste;
    void pop() {System.out.println("Í≥ºÏùº Í∞úÎßõ?ûà?ñ¥.");}

} //class Fruit ÎßàÏπ®

class Apple extends Fruit {

    int price;
    int perfume;

    void cut() {System.out.println("?Ç¨Í≥ºÎ?? Ï°∞Ï†∏?öî");}

} //class Apple ÎßàÏπ®

public class InheritanceExam {

    public static void main(String[] args) {
        
        Apple apple = new Apple();

        apple.pop();

    }
    
}
