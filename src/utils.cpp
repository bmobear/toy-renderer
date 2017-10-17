/*
utils.cpp
contains helper functions

Toy Leksut
*/

#include "main.h"

// extern
void setIO(const string filelist, const string output_dir);
void transferDraw(Mat& out_img);
void writeImage(const Mat& img, const string outfile);
void showImage(const Mat& img);

///////////////////////////////////////////////////////////////////

void setIO(const string filelist, const string output_dir)
{
	// CANNOT READ FILE YET
	ifstream in;
	in.open(filelist);
	if (!in.is_open()) {
		printf("failed to open %s\n", filelist.c_str());
		exit(-1);
	}
	string str;
	while (getline(in, str))
	{
		printf(" read %s\n", str.c_str());
	}
}

void transferDraw(Mat& out_img)
{
	out_img = Mat(WINDOW_WIDTH, WINDOW_HEIGHT, CV_8UC3);
	glPixelStorei(GL_PACK_ALIGNMENT, (out_img.step & 3) ? 1 : 4);
	glPixelStorei(GL_PACK_ROW_LENGTH, out_img.step / out_img.elemSize());	glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_BGR, GL_UNSIGNED_BYTE, out_img.data);
	flip(out_img, out_img, 0);
}

void writeImage(const Mat& img, const string outfile)
{
	imwrite(outfile, img);
}

void showImage(const Mat& img)
{
	imshow("cv::imshow", img);
	waitKey(0);
}

