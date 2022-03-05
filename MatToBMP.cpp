#include "pch.h"
#include "MatToBMP.h"

MatToBMP::MatToBMP(Mat frame)
{
	this->frame = new Mat(frame);
	ZeroMemory(&headerInfo, sizeof(headerInfo));
	ZeroMemory(&bitmapInfo, sizeof(bitmapInfo));

	auto convertOpenCVBitDepthToBits = [](const int32_t value)
	{
		auto regular = 0u;

		switch (value)
		{
		case CV_8U:
		case CV_8S:
			regular = 8u;
			break;

		case CV_16U:
		case CV_16S:
			regular = 16u;
			break;

		case CV_32S:
		case CV_32F:
			regular = 32u;
			break;

		case CV_64F:
			regular = 64u;
			break;

		default:
			regular = 0u;
			break;
		}

		return regular;
	};

	imageSize = frame.size();
	assert(imageSize.width && "invalid size provided by frame");
	assert(imageSize.height && "invalid size provided by frame");


	if (imageSize.width && imageSize.height)
	{
		headerInfo.biSize = sizeof(headerInfo);
		headerInfo.biWidth = imageSize.width;
		headerInfo.biHeight = -(imageSize.height); // negative otherwise it will be upsidedown
		headerInfo.biPlanes = 1;// must be set to 1 as per documentation frame.channels();

		const auto bits = convertOpenCVBitDepthToBits(frame.depth());
		headerInfo.biBitCount = frame.channels() * bits;

		bitmapInfo.bmiHeader = headerInfo;
		bitmapInfo.bmiColors->rgbBlue = 0;
		bitmapInfo.bmiColors->rgbGreen = 0;
		bitmapInfo.bmiColors->rgbRed = 0;
		bitmapInfo.bmiColors->rgbReserved = 0;

		dc = GetDC(nullptr);
		assert(dc != nullptr && "Failure to get DC");


	}


}

MatToBMP::~MatToBMP()
{
	if (frame != nullptr)
	{
		delete frame;
		frame = nullptr;
	}

}


HBITMAP MatToBMP::mCreateDIBitmap(Mat& frame)
{
	auto bmp = CreateDIBitmap(dc,
		&headerInfo,
		CBM_INIT,
		frame.data,
		&bitmapInfo,
		DIB_RGB_COLORS);
	return bmp;
}
