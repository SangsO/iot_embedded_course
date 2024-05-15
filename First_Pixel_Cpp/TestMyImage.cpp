#include <iostream>
#include "imageSrc/MyImage.h"

using namespace std;
int main()
{
	CByteImage image1(640, 480); // (0이면 검정색, 255는 흰색), 가로는 640픽셀, 세로는 480픽셀 (int nWidth, int nHeight)
	image1.SetConstValue(0);//쓰레기값이 있는 동적할당 공간에 640 480에 모두 0을 넣어준다 (검정색이 됨) ->  image1

	CByteImage image2(image1);
	CByteImage image3;
	image3 = image1; //대입 연산자 재정의 -> 해당 연산을 실행

	int nWidth = image1.GetWidth();
	int nHeight = image1.GetHeight();
	int nChannel = image1.GetChannel();

	double incX = 256.0 / nWidth; //x축으로 그라데이션을 할것인지
	double incY = 256.0 / nHeight; // y축으로 그라데이션을 할것인지
	int r, c;
	for (r = 0; r < nHeight; r++)
	{
		for (c = 0; c < nWidth; c++)
		{
			image2.GetAt(c, r) = (BYTE)(c * incX);
			image3.GetAt(c, r) = (BYTE)(r * incY);

			//cout << " " << r << " " << c <<endl;
			if(c < 10 || 630 < c)			
			//cout << (int)(r * incY) << " ";
			cout << (int)(c * incX) << " ";
		}
		cout << endl;
	}

	image1.SaveImage("Black.bmp");
	image2.SaveImage("GradationX.bmp");
	image3.SaveImage("GradationY.bmp");

	return 0;
}