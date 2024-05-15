package com.test.thread;

public class ThreadExam3 {

    public static void main(String[] args) {
        
        new Thread(new Runnable() {

            @Override
            public void run() {
               for(int i=0; i<30; i++){
                   try{
                    Thread.sleep(1000);
                    System.out.println("Thread1이 실행");
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                } //end_for
                                
            }

        
        }).start();

        for(int i=0; i<30; i++){
            try {
                Thread.sleep(1000);
                System.out.println("Thread2 실행");
            } catch (InterruptedException e) {                
                e.printStackTrace();
            }
        }
    }
    
}
