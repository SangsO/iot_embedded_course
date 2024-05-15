package com.test.exam01;

class Number{

    static int a = 0;
    int b = 0;

    static void print() {
        System.out.println("static method test!!!");

    }

    void print1(){
        System.out.println("instance method test!!!");

    }
} //Number 클래스의 마침

public class StaticExam {

    public static void main(String[] args) {
        
        Number number1 = new Number();
        Number number2 = new Number();

        Number.a = 1;
        number1.b = 1;

        System.out.println(Number.a + " " + number2.b);

        Number.print();
        number1.print1();

    }
    
} //public class StaticExam 마침
