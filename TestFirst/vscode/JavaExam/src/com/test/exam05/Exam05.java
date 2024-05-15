package com.test.exam05;

class A {

    private int a;
    private int b;
    static int c; // static은 컴파일 시 코드 및 데이터 영역이 생성되고 프로그램 종료 시 까지 데이터가 유지된다.

    A(){
        System.out.println("A 클래스가 생성"); 
        aa();
    } //컴파일시 자동으로 생성
       
    A(int a, int b) {
        this.a = a;
        this.b = b;
        c = bb(a, b);
    }
    
    void aa() {
        System.out.println("A 클래스의 aa매서드");
    }

    int bb(int i, int j){
        return i+j;        
    }

} //finish_class A

abstract class C { //부모 class


    int a;
    int b;

    void cc(){
        System.out.println("C 클래스");
    }

    abstract void cc1();

} //finish_class C

class D extends C{ //자식 class
    int d;
    int e;

    @Override
    void cc1() {
        System.out.println("D클래스의 cc1 매서드");        
    }

    void dd(){
        System.out.println("D클래스의 dd 매서드");
    }

        
} //finish_class D

interface E{ //청사진(설계도) 에 비유

    void ee1();
    void ee2();

} //interface E_finish

class F implements E{

    @Override
    public void ee1() {
       System.out.println("클래스 F의 ee1 매서드");
    }

    @Override
    public void ee2() {
       System.out.println("클래스 F의 ee2 매서드");
    }
    
} //class F implement E //end

class G{
    
    static class GG { // 내부 클래스는 static형태 가능

        int i = 0;
        void gg(){
            System.out.println("GG내부 클래스");
        }
    } //class GG_finish (inneer of class G)

} //class G_finish

public class Exam05 {

    public static void main(String[] args) { //static 선언 매서드 --->컴파일시 완성된다.

        A a = new A(); //인자가 없는 생성자 실행
        a.aa();
        System.out.println(a.bb(1, 2));

        A aa = new A(3,4); //참조형 변수 형태

        System.out.println(aa.c);
        System.out.println(a.c);
        
        D d = new D();
        d.cc1();

        F f = new F();
        f.ee1();
        f.ee2();

        new A();
        G.GG g = new G.GG();
        g.gg();

    } //main_public Exam05 -->가장 먼저 선언됨(main문)
    
} //public class_finish
