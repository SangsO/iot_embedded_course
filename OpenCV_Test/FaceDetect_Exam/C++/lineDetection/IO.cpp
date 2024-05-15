#include "IO.h"

std::vector<std::pair<int, cv::Mat>> IO::item_IO_data;

IO::IO(){}

IO::~IO(){}

void IO::io_init()	//�̹��� ������ �°� �̸� ���� �ʱ�ȭ
{
	item_IO_data.resize(2);
	item_IO_data[0].first = 0;
	item_IO_data[1].first = 0;
}

void IO::item_setting(std::string path, int type)
{
	// ���� ������ �̹��� �Է� �κ�.
	cv::Mat img;

	img = cv::imread(path);	//user���� ��� �Է¹���
	item_IO_data[type - 1].second = img;	//�̹��� ����� ���Ϳ� ����
}

bool IO::file_check(int num, std::string file_name) //����ڰ� �Է��� �޾� ������ �����ϴ��� �˻�
{
	_finddata_t fd;
	long handle;
	int result = 1;
	std::string path;

	switch (num) {

	case 1:
		switch (User::img_type) {
		case 1:
			handle = _findfirst("new_image\\glasses\\*.*", &fd);  //���ο� �̹����� ����� ���� �� ��� ������ ã�´�.
			break;
		case 2:
			handle = _findfirst("new_image\\lips\\*.*", &fd);  //���ο� �̹����� ����� ���� �� ��� ������ ã�´�.
			break;
		}
		break;
	case 2:
		switch (User::img_type) {
		case 1:
			handle = _findfirst("saved_image\\glasses\\*.*", &fd);  //�̹����� ����� ���� �� ��� ������ ã�´�.
			break;
		case 2:
			handle = _findfirst("saved_image\\lips\\*.*", &fd);  //�̹����� ����� ���� �� ��� ������ ã�´�.
			break;
		}
		break;
	}
	if (handle == -1)
	{
		_findclose(handle);
		return false;
	}

	while (result != -1)
	{
		if (strcmp(fd.name, ".") != 0 && strcmp(fd.name, "..") != 0) {
			if (strcmp(fd.name, file_name.c_str()) == 0) {
				_findclose(handle);
				return true;
			}
		}
		result = _findnext(handle, &fd);
	}
	_findclose(handle);
	return false;
}

//png �̹��� ���� �Լ� --> ���� �ʿ�
//cv::Mat BlendingPixel(const cv::Mat& mbgrImgUnderlay, const cv::Mat& mbgraImgOverlay, const cv::Point& location)
//{
//	cv::Mat mbgrImgResult = mbgrImgUnderlay.clone();
//	for (int y = std::max(location.y, 0); y < mbgrImgUnderlay.rows; ++y)
//	{
//		int fY = y - location.y;
//		if (fY >= mbgraImgOverlay.rows)
//			break;
//		for (int x = std::max(location.x, 0); x < mbgrImgUnderlay.cols; ++x)
//		{
//			int fX = x - location.x;
//			if (fX >= mbgraImgOverlay.cols)
//				break;
//			double opacity = ((double)mbgraImgOverlay.data[fY * mbgraImgOverlay.step + fX * mbgraImgOverlay.channels() + 3]) / 255.;
//			for (int c = 0; opacity > 0 && c < mbgrImgUnderlay.channels(); ++c)
//			{
//				unsigned char overlayPx = mbgraImgOverlay.data[fY * mbgraImgOverlay.step + fX * mbgraImgOverlay.channels() + c];
//				unsigned char srcPx = mbgrImgUnderlay.data[y * mbgrImgUnderlay.step + x * mbgrImgUnderlay.channels() + c];
//				mbgrImgResult.data[y * mbgrImgUnderlay.step + mbgrImgUnderlay.channels() * x + c] = srcPx * (1. - opacity) + overlayPx * opacity;
//			}
//		}
//	}
//	return mbgrImgResult;
//}