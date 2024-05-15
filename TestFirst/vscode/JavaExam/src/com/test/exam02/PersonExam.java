package com.test.exam02;

public class PersonExam {

    public static void main(String[] args) {
        
        Person person = new Person();

        String name = "홍길동";
        int age = 45;
        String gender = "male";

        person.setName(name);
        System.out.println(person.getName());

        person.setAge(age);
        System.out.println(person.getAge());
        
        person.setGender(gender);
        System.out.println(person.getGender());

    } //main 의 마침
    
} //public class 의 마침
