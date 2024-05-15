package com.test.exam03;

import java.util.function.Consumer;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.function.Supplier;

import javax.print.attribute.SetOfIntegerSyntax;

@FunctionalInterface
interface MyLamdaFunction {
	int sum(int a, int b);	
}

@FunctionalInterface
interface MyPrint {
	String printLamda();
}

public class LamdaExam {
	
	public static void main(String[] args) {
		
		MyLamdaFunction lamdaFunction = (int a, int b) -> a+b; //�͸��Լ�
		System.out.println(lamdaFunction.sum(3, 4));
		
		MyPrint myPrint = ()->"Hello World 1";
		System.out.println(myPrint.printLamda());
		
		//Supplier : �Ű����� ���� ��ȯ������ ���� �Լ��� �������̽�
		
		Supplier<String> Supplier = ()->"Hello World 2";
		System.out.println(Supplier.get());
		
		//Consumer : ��ü T�� �Ű������� �޾Ƽ� ���. ��ȯ���� ����.
		Consumer<String> consumer = (str)->System.out.println(str.split(" ")[0]);
		consumer.andThen(System.out::println).accept("Hello World3");
		
		//Fuction : ��ü T�� �Ű������� �޾Ƽ� ó���� �� R�� ��ȯ�ϴ� �Լ��� �������̽�
		Function<String,Integer> function = str->str.length();
		System.out.println(function.apply("Hello World4"));
		
		//Predicate : ��ü T�� �Ű������� �޾Ƽ� ó���� �� Boolean�� ��ȯ
		Predicate<String> predicate = (str)->str.equals("Hello World5");
		System.out.println(predicate.test("Hello World5"));
		
		//�Ϲ� ������, �żҵ� ������, ������ ������...
		
		Function<String, Integer> function2 = String::length;
		System.out.println(function2.apply("Hello World"));
		
		Consumer<String> consumer2 = System.out::println;
		consumer2.accept("Hello World6");
		
		//Suplier<String> supplier1 = String::new
		
	} //main_end

} //class LamdaExam_finish
