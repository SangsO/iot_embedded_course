#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <io.h>
#include "User.h"
using namespace std;

class IO
{

public:
	IO();
	~IO();

	static std::vector<std::pair<int, cv::Mat>> item_IO_data; //first : 아이템 입출력 결정, second : 아이템 이미지 데이터

	static void io_init();	//이미지 벡터 초기화
	static void item_setting(std::string path, int type);	//이미지 표시/제거 관리
	static bool file_check(int num, string file_name);  //폴더에 파일 있는지 체크

	//static cv::Mat BlendingPixel(const cv::Mat& mbgraImgOverlay);//TODO : png 처리 추가해야함
};

