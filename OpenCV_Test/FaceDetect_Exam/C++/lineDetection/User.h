#pragma once
#include<iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include"IO.h"
#include <io.h>
using namespace std;
using namespace cv;

class User
{
public:
	User();
	~User();

	//����
	static void user_interface();  //����� �������̽� ���� �Լ�
	static void select_file(int num);  //���� ����
	static void sticker_attach();

	static int img_type;
	//static string file_path; //���� ��θ� 
	//static string save_path; //������ ���� ���
	//

	static int item_select_wait;
	static int item_select_end;
	static void item_select();
};