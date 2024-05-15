#pragma once;

#include <iostream>
#include <thread>
#include <queue>
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <WinSock2.h>
#include "IO.h"
#include "User.h"
#include "Sticker_Overlay.h"
#include "IMG_com.h"

//#include "glass_test.h"

#define PI 3.141592

int User::item_select_end = 0;
int User::item_select_wait = 1;

void start_work();

int main()
{
	IO::io_init();
	IMG_com *img_com = new IMG_com();

	std::thread t3 = img_com->recv_th();
	std::thread t1([&]() {User::item_select();});
	std::thread t2(&start_work);

	t1.join();
	t2.join();
	t3.join();

	return 0;
}

void start_work()
{
	CascadeClassifier faceDetector("haarcascade_frontalface_alt2.xml");

	cv::Ptr<cv::face::Facemark> facemark = cv::face::FacemarkLBF::create();

	facemark->loadModel("lbfmodel.yaml");

	cv::VideoCapture cam(0);

	cv::Mat frame;

	/////////////////////////////////////////////////////////////
	std::string path = "saved_image\\glasses\\g1.jpg";
	/////////////////////////////////////////////////////////////

	while (cam.read(frame))
	{
		User::item_select_wait = 0;
		cv::Mat read_resize;
		cv::Mat gray;
		std::vector<cv::Rect> faces;
		cv::cvtColor(frame, gray, COLOR_BGR2GRAY);
		faceDetector.detectMultiScale(gray, faces);
		std::vector<std::vector<cv::Point2f>> landmarks;
		bool success = facemark->fit(frame, faces, landmarks);

		if (success)
		{
			int item_value = IO::item_IO_data.size();

			for (int i = 0; i < landmarks.size(); i++)
			{
				for (int j = 0; j < item_value; j++)
				{
					if (IO::item_IO_data[j].first)
					{
						if (j == 0)
							GlassSticker glassSticker(&frame, &landmarks, i);
						else
							LipSticker lipSticker(&frame, &landmarks, i);
					}
				}
			}
		}
		cv::imshow("¾ó±¼ °ËÃâ", frame);

		if (cv::waitKeyEx(1) == 27)
			break;
	}
}