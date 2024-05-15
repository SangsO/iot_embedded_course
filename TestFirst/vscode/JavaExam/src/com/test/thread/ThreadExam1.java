package com.test.thread;

class ExamClass implements Runnable {

    @Override
    public void run() {
        for(int i=0; i<30; i++) {
            try {
                Thread.sleep(1000);
                System.out.println("Thread1이 실행");
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            
        }
    
    }

} // class ExamClass_finish

public class ThreadExam1 {
    
    public static void main(String[] args) {

        Thread thread = new Thread(new ExamClass());
        thread.start();

        for(int i=0; i<30; i++) {
            try {
                Thread.sleep(1000);
                System.out.println("Thread2이 실행");
            } catch (InterruptedException e) {            
                e.printStackTrace();
            }
        }
    } //ThreadExam1 main_end

} // class ThreadExam1_finish
