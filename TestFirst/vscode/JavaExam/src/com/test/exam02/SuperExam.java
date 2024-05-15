package com.test.exam02;

class Point {

    int x = 10;
    int y = 20;

    Point(int x, int y){
        this.x = x;
        this.y = y;
    }

} //class Poinit_finish

class Point3D extends Point {

    int z = 30;

    Point3D() {
        this(100, 200, 300);
    }

    Point3D(int x, int y, int z) {
        super(x, y);
        this.z = z;
    }

} //class Point3D_finish

public class SuperExam {

    public static void main(String[] args) {
        Point3D point3d = new Point3D();
        System.out.println("Point3D의 x, y, z = " + point3d.x + " " + point3d.y + " " + point3d.z);
    }
    
} //public class SuperExam_finishhhhh
