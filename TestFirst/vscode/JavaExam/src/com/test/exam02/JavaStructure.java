package com.test.exam02; //�ڹ� ������ �ֻ��

import java.util.Scanner; //�ܺ� ��Ű���κ��� Ŭ������ �ҷ��´�


public class JavaStructure {
	
	public static int sum(int a, int b) {
		
		return a+b;
	}

	public static void main(String[] argv) {
		
		int i = 10;
		long l_value = 10L;
		double d_value = 10;
		float f_value = 10;
		
		System.out.println("Integer i =" + i + "\n" + "long type l_value =" + l_value +"\n");
		System.out.println("Double d_value = " + d_value +"\n" + "float f_value = " + f_value + "\n");
		
		String[] names = new String[3];
		int size = names.length;
		
		Scanner put = new Scanner(System.in);
		
		for(int index=0; index<size; index++) {
			
			System.out.println("�̸��� �Է��ϼ���");
			names[index] = put.nextLine();
			
		}
		
		for (int index=0; index <size; index++)
			System.out.println("�̸� :" + names[index]);
			
		put.close();
	}
	
}
