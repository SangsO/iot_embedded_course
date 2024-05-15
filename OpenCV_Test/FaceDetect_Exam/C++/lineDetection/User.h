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

	//민지
	static void user_interface();  //사용자 인터페이스 시작 함수
	static void select_file(int num);  //파일 선택
	static void sticker_attach();

	static int img_type;
	//static string file_path; //파일 경로명 
	//static string save_path; //저장할 파일 경로
	//

	static int item_select_wait;
	static int item_select_end;
	static void item_select();
};