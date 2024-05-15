#include "glass_test.h"

glass_test::glass_test(cv::Mat *frame, std::vector<std::vector<cv::Point2f>> *landmarks, int pn, std::string path)
	: frame(frame), landmarks(landmarks), pn(pn)
{
	img = cv::imread(path);
	//img_resize = img.clone();
	img_resize = IO::item_IO_data[0].second.clone();

	set_boundary();
	set_object_center();
	 set_btw_lr_range();
	 set_btw_ud_range();
	 set_object_width();
	 set_object_height();
	 empty_space_erase();
	 set_item_nobackgnd_data();
	 set_radian();
	 mapping_on_frame();

}

glass_test::~glass_test(){}

void glass_test::set_boundary()
{
	object_left = std::make_pair((*landmarks)[pn][0].x, (*landmarks)[pn][0].y);
	object_right = std::make_pair((*landmarks)[pn][16].x, (*landmarks)[pn][16].y);
	object_up = std::make_pair(((*landmarks)[pn][19].x + (*landmarks)[pn][24].x) / 2, ((*landmarks)[pn][19].y + (*landmarks)[pn][24].y) / 2);
	object_down = std::make_pair((*landmarks)[pn][28].x, (*landmarks)[pn][28].y);
}

void glass_test::set_object_center()
{
	object_center.first = static_cast<int>((object_left.first + object_right.first) / 2);
	object_center.second = static_cast<int>((object_left.second + object_right.second) / 2);
}

void glass_test::set_btw_lr_range()
{
	btw_lr_range.first = object_right.first - object_left.first;
	btw_lr_range.second = object_right.second - object_left.second;
}

void glass_test::set_btw_ud_range()
{
	btw_ud_range.first = object_up.first - object_down.first;
	btw_ud_range.second = object_up.second - object_down.second;
}

void glass_test::set_object_width()
{
	object_width = sqrt((btw_lr_range.first * btw_lr_range.first) + (btw_lr_range.second * btw_lr_range.second));
}

void glass_test::set_object_height()
{
	object_height = sqrt((btw_ud_range.first * btw_ud_range.first) + (btw_ud_range.second * btw_ud_range.second));
}

void glass_test::empty_space_erase()
{
	unsigned char * p_im = img_resize.data;

	cv::Mat mono_g_im;
	cv::cvtColor(img_resize, mono_g_im, cv::COLOR_BGR2GRAY);
	unsigned char* p_mono = mono_g_im.data;
	int width = img_resize.cols;
	int height = img_resize.rows;
	int row_max = 0;
	int row_min = height;
	int col_max = 0;
	int col_min = width;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++) {
			int index = row * width + col;
			if (p_mono[index] <= 100) {
				(row_max > row) ? row_max = row_max : row_max = row;
				(row_min < row) ? row_min = row_min : row_min = row;
				(col_max > col) ? col_max = col_max : col_max = col;
				(col_min < col) ? col_min = col_min : col_min = col;
			}
		}
	}
	//빈 버퍼 만들기
	int B_height = row_max - row_min;
	int B_width = col_max - col_min;
	cv::Mat mImage_Mono_buffer(B_height, B_width, CV_8UC3);
	unsigned char* pmImage_Mono_buffer = mImage_Mono_buffer.data;

	for (int row = 0; row < B_height; row++)
	{
		for (int col = 0; col < B_width * 3; col++) {
			int orin_index = (row + row_min) * width * 3 + col + col_min * 3;
			int index = row * B_width * 3 + col;
			pmImage_Mono_buffer[index] = p_im[orin_index];
		}
	}
	img_resize = mImage_Mono_buffer;
	//// 이미지를 landmark 값 만큼 resize
	cv::resize(img_resize, img_resize, cv::Size(static_cast<int>(object_width), static_cast<int>(object_height)), 0, 0, CV_INTER_NN);

	contourse_filter(object_height, object_width);
}

void glass_test::contourse_filter(int B_height, int B_width)
{
	img_gray = new cv::Mat(B_height, B_width, CV_8UC3);////////////////////////////////////////

	cv::cvtColor(img_resize, *img_gray, CV_BGR2GRAY);
	cv::threshold(*img_gray, *img_gray, 128, 255, CV_THRESH_BINARY);

	std::vector<std::vector<cv::Point> > contours;
	contourOutput = img_gray->clone(); /////////////////// 없어도 될 것 같은데.....
	cv::findContours(contourOutput, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE); ///////////////////// 없어도 될 것 같은데.....

}

void glass_test::set_item_nobackgnd_data()
{
	int height = contourOutput.rows;
	int width = contourOutput.cols;

	unsigned char *pgim = contourOutput.data;


	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			//int index = (h * width2 * 3) + (w * 3);
			int index = (h * width) + (w);

			if (pgim[index] == 255)
				continue;

			item_nobackgnd_data.push_back(std::make_pair(w, h)); // background 아닐 경우 x, y 좌표 값 pair 형으로 대입.
		}
	}

}

void glass_test::set_radian()
{
	radian = atan2f((float)(object_left.second - object_right.second), (float)(object_left.first - object_right.first));
	radian += 3.141592f;
}

void glass_test::mapping_on_frame()
{
	unsigned char *pframe_data = frame->data;
	int width3 = img_resize.cols;
	int height3 = img_resize.rows;
	unsigned char *img_resize_data = img_resize.data;
	std::pair<int, int> resize_center(std::make_pair(width3 / 2, height3 / 2));

	for (auto g_d : item_nobackgnd_data)
	{
		int x = g_d.first;
		int y = g_d.second;
		int index = (y * 3 * width3) + (x * 3);
		unsigned char color[3];
		color[0] = img_resize_data[index];
		color[1] = img_resize_data[index + 1];
		color[2] = img_resize_data[index + 2];

		int item_x_cal = ((x - resize_center.first)*cos(radian)) - ((y - resize_center.second)*sin(radian)) + object_center.first;
		int item_y_cal = ((x - resize_center.first)*sin(radian)) + ((y - resize_center.second)*cos(radian)) + object_center.second;
		int frame_index = (item_y_cal * 3 * (frame->cols) + (item_x_cal * 3));

		if (frame_index < 0 || frame_index >= (frame->cols * frame->rows * 3)) // 범위 벗어날 경우 error 발생하여 예외조건 구현
			continue;

		for (int i = 0; i < 3; i++) // frame 의 pixel 위치에 이미지 색상 대입
			pframe_data[frame_index + i] = img_resize_data[index + i];
	}
}