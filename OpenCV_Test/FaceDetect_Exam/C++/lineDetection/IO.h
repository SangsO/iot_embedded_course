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

	static std::vector<std::pair<int, cv::Mat>> item_IO_data; //first : ������ ����� ����, second : ������ �̹��� ������

	static void io_init();	//�̹��� ���� �ʱ�ȭ
	static void item_setting(std::string path, int type);	//�̹��� ǥ��/���� ����
	static bool file_check(int num, string file_name);  //������ ���� �ִ��� üũ

	//static cv::Mat BlendingPixel(const cv::Mat& mbgraImgOverlay);//TODO : png ó�� �߰��ؾ���
};

