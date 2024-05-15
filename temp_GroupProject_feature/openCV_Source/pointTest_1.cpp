#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

void onMouse(int event, int x, int y, int flags, void* param);

int main()

{

	cv::Mat image;
	image = cv::imread("jecheon.jpg", CV_LOAD_IMAGE_GRAYSCALE); // �׷��� �����Ϸ� ���� �б�

	cv::imshow("Jecheon", image); //Jecheon�̶�� â�� �̹��� ���
	cv::setMouseCallback("Jecheon", onMouse, reinterpret_cast<void*>(&image)); // Ư�� â�� ���콺 �ڵ鷯 ����
	cv::waitKey(0);
	return 0;

}



void onMouse(int event, int x, int y, int flags, void* param)
{
	cv::Mat* im = reinterpret_cast<cv::Mat*>(param);

	switch (event) // �̺�Ʈ ����
	{
	case CV_EVENT_LBUTTONDOWN: // ���콺 ��Ŭ���� �̺�Ʈ
		std::cout << "(" << x << ", " << y << "): " << static_cast<int>(im->at<uchar>(cv::Point(x, y))) << std::endl; // (x, y)�� �ִ� ȭ�Ұ� ���
		break;

	case CV_EVENT_RBUTTONDOWN: // ���콺 ��Ŭ���� �̺�Ʈ
		std::cout << "Hello!" << std::endl; // Hello! ���

		break;

	}

}