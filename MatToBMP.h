#pragma once
#include<opencv2/opencv.hpp>

using namespace cv;

class MatToBMP
{
public:
	Mat *frame;
	struct tagBITMAPINFOHEADER headerInfo;
	struct tagBITMAPINFO bitmapInfo;
	Size imageSize;
	HDC dc;

	MatToBMP(Mat frame);
	~MatToBMP();

	HBITMAP mCreateDIBitmap(Mat &frame);



};

