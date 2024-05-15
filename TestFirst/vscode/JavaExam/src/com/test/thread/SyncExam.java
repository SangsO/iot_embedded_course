package com.test.thread;

class ExamA {
    public void ExamA1(String thread){
        System.out.println("ExamA시작");
        synchronized(this) {
            for(int i=0; i<3; i++)
                System.out.println("Thread : " +  thread + ", ExamA1 : " + i);
            }
            System.out.println("ExamA1끝");
        }
        public synchronized void ExamA2(String thread){
            System.out.println("Exam2 시작");
            for(int i=0; i<3; i++)
                System.out.println("Thread : " +  thread + ", ExamA2 : " + i);
            System.out.println("ExamA2 끝");
        }   
}        
        


public class SyncExam {

    public static void main(String[] args) {
        ExamA examA = new ExamA();

        Thread thread1 = new Thread(new Runnable() {

            @Override
            public void run() { examA.ExamA1("thread1");}
                
                
            });

        Thread thread2 = new Thread(new Runnable() {

            @Override
            public void run() { examA.ExamA2("thread2");}
                    
                    
            });
            
            thread1.start();
            thread2.start();
               
    } // public_end
    
} //SyncExam_finish
