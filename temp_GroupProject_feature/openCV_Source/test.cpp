#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

using namespace cv;
using namespace std;

int main(int, char**) {

	Mat frame;
	VideoCapture cap;
	cap.open(0);

	int count = 0;
	char saveFile[200];
	if (!cap.isOpened()) {

		cout << "ERROR! Cannot Open Cam" << endl;
		return -1;
	}

	while (1)
	{
		cap.read(frame);
		imshow("Live", frame);

		resize(frame, frame, Size(100, 100), 0, 0, INTER_CUBIC);

		sprintf(saveFile,"image%d.jpg", count++);
		imwrite(saveFile, frame);

		if (waitKey(5) >= 0)
			break;
	}
	return 0;
}