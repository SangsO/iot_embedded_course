#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include "drawLandmarks.hpp"

using namespace std;
using namespace cv;
using namespace cv::face;
void overlayImage(const Mat &background, const Mat &foreground,	Mat &output, Point2i location);
int main(int argc, char** argv)
{
	// Load Face Detector
	CascadeClassifier faceDetector("haarcascade_frontalface_alt2.xml");
	// Create an instance of Facemark
	Ptr<Facemark> facemark = FacemarkLBF::create();
	// Load landmark detector
	facemark->loadModel("lbfmodel.yaml");
	// Set up webcam for video capture
	VideoCapture cam(0);
	// Variable to store a video frame and its grayscale 
	Mat frame, gray;
	cv::Mat src = imread("D:\\image\\pignose2.jpg", IMREAD_UNCHANGED);
	cv::resize(src, src, cv::Size(64, 59), 0, 0, CV_INTER_NN);

	// Read a frame
	while (cam.read(frame))
	{
		// Find face
		vector<Rect> faces;
		// Convert frame to grayscale because
		// faceDetector requires grayscale image.
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		// Detect faces
		faceDetector.detectMultiScale(gray, faces);
		// Variable for landmarks. 
		// Landmarks for one face is a vector of points
		// There can be more than one face in the image. Hence, we 
		// use a vector of vector of points. 
		vector< vector<Point2f> > landmarks;

		// Run landmark detector
		bool success = facemark->fit(frame, faces, landmarks);

		if (success)
		{
			// If successful, render the landmarks on the face
			for (int i = 0; i < landmarks.size(); i++)
			{
				//drawLandmarks(frame, landmarks[i]);
				src.copyTo(frame(cv::Rect(landmarks[i][30].x - src.cols/2, landmarks[i][30].y - src.rows/2, src.cols, src.rows)));
				//overlayImage(frame, src, frame, cv::Point(landmarks[i][30].x - src.cols / 2, landmarks[i][30].y - src.rows / 2));
			}
		}
		// Display results 
		imshow("Facial Landmark Detection", frame);
		// Exit loop if ESC is pressed
		if (waitKey(1) == 27) break;
	}
	return 0;
}
void overlayImage(const Mat &background, const Mat &foreground,	Mat &output, Point2i location)
{
	background.copyTo(output);


	// start at the row indicated by location, or at row 0 if location.y is negative.
	for (int y = std::max(location.y, 0); y < background.rows; ++y)
	{
		int fY = y - location.y; // because of the translation

								 // we are done of we have processed all rows of the foreground image.
		if (fY >= foreground.rows)
			break;

		// start at the column indicated by location, 

		// or at column 0 if location.x is negative.
		for (int x = std::max(location.x, 0); x < background.cols; ++x)
		{
			int fX = x - location.x; // because of the translation.

									 // we are done with this row if the column is outside of the foreground image.
			if (fX >= foreground.cols)
				break;

			// determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
			double opacity =
				((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3])

				/ 255.;


			// and now combine the background and foreground pixel, using the opacity, 

			// but only if opacity > 0.
			for (int c = 0; opacity > 0 && c < output.channels(); ++c)
			{
				unsigned char foregroundPx =
					foreground.data[fY * foreground.step + fX * foreground.channels() + c];
				unsigned char backgroundPx =
					background.data[y * background.step + x * background.channels() + c];
				output.data[y*output.step + output.channels()*x + c] =
					backgroundPx * (1. - opacity) + foregroundPx * opacity;
			}
		}
	}
}

