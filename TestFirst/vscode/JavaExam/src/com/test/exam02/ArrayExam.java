package com.test.exam02;

import java.util.Arrays;

public class ArrayExam {
	
	public static void main(String[] argv) {
		
		int[] a = new int[]{1, 2, 3, 4, 5, 6};
		
		for(int i=0; i< a.length; i++)
			System.out.print(a[i] + " ");
		
		System.out.println("\n");
		
		for(int i: a) System.out.print(i + " ");
		
		System.out.println(Arrays.toString(a));
		
		int[][] b = { {1,2,3}, {4,5,6}, {7,8,9} };
		
			for(int i=0 ; i<3 ; i++)
				for(int j=0 ; j<3 ; j++)
				System.out.println(b[i][j]);
	
		for(int i=0; i<b.length; i++)
			System.out.println(Arrays.toString(b[i]));
	

	
		int c = 5;
		String str = "Hello";
				
		
		switch(str) {
		
		case "hi": System.out.println("what");
				break;			
		case "good moring": System.out.println("what what");
				break;
		default : System.out.println("hello");
		}
		
		
	}
	
}

