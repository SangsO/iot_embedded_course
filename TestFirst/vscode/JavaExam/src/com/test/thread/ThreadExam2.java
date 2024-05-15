package com.test.thread;

class ExamClass2 extends Thread {

    @Override
    public void run() {
        for(int i=0; i<30; i++) {
            try {
                Thread.sleep(1000);
                System.out.println("Thread1이 실행");
            } catch (InterruptedException e) {  
                e.printStackTrace(); }
        } //end_for            
                   
           
    }    

}//claass ExamClasss2 extends thread_finish

public class ThreadExam2 {

    public static void main(String[] args) {
        ExamClass2 examclass2 = new ExamClass2();
        examclass2.start();
        for(int i=0; i<30; i++) {
            try {
                Thread.sleep(1000);
                System.out.println("Thread2이 실행");
            } catch (InterruptedException e) {                
                e.printStackTrace();
            }
            
        } //end_for
        

    } //ThreadExam2 MAIN_end
    
} // public class ThreadExam2_finish
