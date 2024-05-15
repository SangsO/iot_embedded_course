package com.test.exam01;

class ErrorTest{

    public void errormaking() throws ArithmeticException {

        int a =4/0;
        System.out.println("a = " + a);

    }
} //class ErrorTest 마침

class FoolException extends Exception {}

public class ExceptionExam {

    public void sayNickname(String nickname) {

        if(nickname.equals("fool"))
            try {
                throw new FoolException(); //강제적으로 예외를 발생_ throw new 후 작성해줌
            } catch (FoolException e) {
                System.err.println("FoolException가 발생했습니다.");
            }
        System.out.println("당신의 별명은 " + nickname + "입니다.");

    } //sayNickname 마침


    public static void main(String[] args) {
        

        int c;
        try{
            c = 4/0; 
                    
        } catch(ArithmeticException e) {
            c = -1; //예외 발생시 조치할 부분
                    } finally {
            System.out.println("다행이다");
        }

        System.out.println("C =" + c);

        //ErrorTest errortest = new ErrorTest();
        //errortest.errormaking();

        ExceptionExam exam = new ExceptionExam();
        exam.sayNickname("fool");
        //exam.sayNickname("genius");

    } //main 의 마침
    
} //package 의 마침
