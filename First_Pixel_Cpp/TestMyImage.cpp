#include <iostream>
#include "imageSrc/MyImage.h"

using namespace std;
int main()
{
	CByteImage image1(640, 480); // (0�̸� ������, 255�� ���), ���δ� 640�ȼ�, ���δ� 480�ȼ� (int nWidth, int nHeight)
	image1.SetConstValue(0);//�����Ⱚ�� �ִ� �����Ҵ� ������ 640 480�� ��� 0�� �־��ش� (�������� ��) ->  image1

	CByteImage image2(image1);
	CByteImage image3;
	image3 = image1; //���� ������ ������ -> �ش� ������ ����

	int nWidth = image1.GetWidth();
	int nHeight = image1.GetHeight();
	int nChannel = image1.GetChannel();

	double incX = 256.0 / nWidth; //x������ �׶��̼��� �Ұ�����
	double incY = 256.0 / nHeight; // y������ �׶��̼��� �Ұ�����
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