#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

void onMouse(int event, int x, int y, int flags, void* param);

int main()

{

	cv::Mat image;
	image = cv::imread("jecheon.jpg", CV_LOAD_IMAGE_GRAYSCALE); // 그레이 스케일로 영상 읽기

	cv::imshow("Jecheon", image); //Jecheon이라는 창에 이미지 출력
	cv::setMouseCallback("Jecheon", onMouse, reinterpret_cast<void*>(&image)); // 특정 창에 마우스 핸들러 설정
	cv::waitKey(0);
	return 0;

}



void onMouse(int event, int x, int y, int flags, void* param)
{
	cv::Mat* im = reinterpret_cast<cv::Mat*>(param);

	switch (event) // 이벤트 전달
	{
	case CV_EVENT_LBUTTONDOWN: // 마우스 좌클릭시 이벤트
		std::cout << "(" << x << ", " << y << "): " << static_cast<int>(im->at<uchar>(cv::Point(x, y))) << std::endl; // (x, y)에 있는 화소값 출력
		break;

	case CV_EVENT_RBUTTONDOWN: // 마우스 우클릭시 이벤트
		std::cout << "Hello!" << std::endl; // Hello! 출력

		break;

	}

}