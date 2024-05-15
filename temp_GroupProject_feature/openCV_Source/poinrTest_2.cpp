#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		cout << "Left Mouse Click : Where ->  = (" << x << ", " << y << ")" << endl;
	}
}
int main(int argc, char** argv)
{
	Mat img_original, img_gray;
	
	img_original = imread("pointTest_2.png", IMREAD_COLOR);
	if (img_original.empty())
	{
		cout << "Image loading Error!!!" << std::endl;
		return -1;
	}
	
	cvtColor(img_original, img_gray, COLOR_BGR2GRAY);
	
	namedWindow("original image", WINDOW_AUTOSIZE);
	namedWindow("gray image", WINDOW_AUTOSIZE);
	
	imshow("original image", img_original);
	imshow("gray image", img_gray);
	
	setMouseCallback("gray image", CallBackFunc, NULL);

	
	waitKey(0);
	return 0;
}