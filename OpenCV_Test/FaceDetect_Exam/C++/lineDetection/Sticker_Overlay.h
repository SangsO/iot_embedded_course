#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include "IO.h"

class StickerOverlay
{
protected :

	cv::Mat *frame;
	std::vector<std::vector<cv::Point2f>> *landmarks;
	int pn;

	std::pair<int, int> object_left;
	std::pair<int, int> object_right;
	std::pair<int, int> object_up;
	std::pair<int, int> object_down;
	std::pair<int, int> object_center;
	std::pair<int, int> btw_lr_range;
	std::pair<int, int> btw_ud_range;
	double object_width;
	double object_height;
	double radian;

	cv::Mat img_resize;
	cv::Mat *img_gray;

	std::vector<std::pair<int, int>> item_nobackgnd_data;

	cv::Mat contourOutput;


public :
	StickerOverlay(cv::Mat *frame, std::vector<std::vector<cv::Point2f>> *landmarks, int pn);
	~StickerOverlay();

	virtual void set_boundary() = 0;
	
	void set_object_center();
	void set_btw_lr_range();
	void set_btw_ud_range();
	void set_object_width();
	void set_object_height();
	void empty_space_erase();
	void contourse_filter(int B_height, int B_width);
	void set_item_nobackgnd_data();
	void set_radian();
	void mapping_on_frame();

};


class GlassSticker : public StickerOverlay
{
public :
	GlassSticker(cv::Mat *frame, std::vector<std::vector<cv::Point2f>> *landmarks, int pn);
	~GlassSticker();

	void set_boundary();

};

class LipSticker : public StickerOverlay
{
public :
	LipSticker(cv::Mat *frame, std::vector<std::vector<cv::Point2f>> *landmarks, int pn);
	~LipSticker();

	void set_boundary();
};