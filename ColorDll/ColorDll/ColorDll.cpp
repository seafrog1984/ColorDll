// ColorDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "ColorDll.h"


//// 这是导出变量的一个示例
//COLORDLL_API int nColorDll=0;
//
//// 这是导出函数的一个示例。
//COLORDLL_API int fnColorDll(void)
//{
//	return 42;
//}

//// 这是已导出类的构造函数。
//// 有关类定义的信息，请参阅 ColorDll.h
//CColorDll::CColorDll()
//{
//	return;
//}

COLORDLL_API int CalROI(Mat &img, int &sx, int &sy, int &w, int &h, int roi_border)
{
	Rect rect1(sx, sy, w, h);
	Mat roi1;
	img(rect1).copyTo(roi1);

	//imshow("test", roi1);
	Mat roi_gray;
	cvtColor(roi1, roi_gray, CV_BGR2GRAY);

	double value = mean(roi_gray)[0] * 0.95;

	Mat seg;
	cv::threshold(roi_gray, seg, value, 255, THRESH_BINARY_INV);

	//imshow("seg", seg);

	int col_start = 0;
	for (int col = 0; col < seg.cols; col++)
	{
		if (seg.at<uchar>(seg.rows / 2, col) != 0)
		{
			col_start = col;
			break;
		}
	}
	col_start = col_start + roi_border;
	int col_end = seg.cols - 1;
	for (int col = seg.cols - 1; col >= 0; col--)
	{
		if (seg.at<uchar>(seg.rows / 2, col) != 0)
		{
			col_end = col;
			break;
		}
	}
	col_end = col_end - roi_border;
	int row_start = 0;
	for (int row = 0; row < seg.rows; row++)
	{
		if (seg.at<uchar>(row, col_start) != 0)
		{
			row_start = row;
			break;
		}
	}
	row_start = row_start + roi_border;
	int row_end = 0;
	for (int row = seg.rows - 1; row >= 0; row--)
	{
		if (seg.at<uchar>(row, col_start) != 0)
		{
			row_end = row;
			break;
		}
	}
	row_end = row_end - roi_border;

	int roi_w = col_end - col_start;
	int roi_h = row_end - row_start;
	if (roi_w > 0 && roi_h > 0)
	{
		//Rect rect(col_start, row_start, roi_w, roi_h);

		sx = sx + col_start;
		sy = sy + row_start;
		w = roi_w;
		h = roi_h;

	}
	else
	{
		return -1;
	}

	return 0;
}


COLORDLL_API void CalRGB(Mat &img, int &sx, int &sy, int &w, int &h, int &r, int &g, int &b)
{
	Rect rect(sx, sy, w, h);
	Mat roi;
	img(rect).copyTo(roi);


	Mat channel[3];
	split(roi, channel);
	//imshow("original", img);
	//imshow("B", channel[0]);
	//imshow("G", channel[1]);
	//imshow("R", channel[2]);

	cv::Scalar tempVal;
	int bgr[3];

	for (int i = 0; i < 3; i++)
	{

		tempVal = mean(channel[i]);

		bgr[i] = (int)(tempVal.val[0] + 0.5);
	}

	b = bgr[0];
	g = bgr[1];
	r = bgr[2];
}

COLORDLL_API int CompareRGB(int &r, int &g, int &b, int dst_r, int dst_g, int dst_b, int thre)
{

	if (r - dst_r > thre || r - dst_r < -thre)
	{
		return 1;
	}
	if (g - dst_g > thre || g - dst_g < -thre)
	{
		return 2;
	}
	if (b - dst_b > thre || b - dst_b < -thre)
	{
		return 3;
	}

	return 0;

}