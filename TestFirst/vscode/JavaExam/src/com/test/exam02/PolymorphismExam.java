package com.test.exam02;

class Family{

    void hello() { } //{System.out.println("인사합시다.");} -> 빈껍데기로 두어도 정상 작동
} //class Family의 마침

class kimFamily extends Family{

    void hello() {System.out.println("김선생님 안녕?");}
    void dinner() {System.out.println("밥한끼하시죠");}
    void drink() {System.out.println("술조지시죠");}
} //class kimFamily의 마침

class parkFamily extends Family {

    void hello() {System.out.println("박선생님 안녕?");}
    void fishing() {System.out.println("낚시때리시죠");}
} //class parkFamily의 마침

public class PolymorphismExam {

    public static void main(String[] args) {

        Family kimF = new kimFamily();
        kimF.hello();

        Family parkF = new parkFamily();
        parkF.hello();
        
    } //main public class 마침
    
}
