/*
utils.cpp
contains helper functions

Toy Leksut
*/

#include "main.h"
using namespace boost::filesystem;

// extern
void setIO(const string filelist, const string output_dir);
void transferDraw(Mat& out_img);
void writeImage(const Mat& img, const string outfile);
void showImage(const Mat& img);
bool verifyDir(const string pathstr);
bool verifyFile(const string pathstr);
vector<string> input_list;
string output_dir;

///////////////////////////////////////////////////////////////////

void setIO(const string filelist, const string output_dir)
{

	ifstream in;
	in.open(filelist.c_str());
	if (!in.is_open()) {
		printf("failed to open %s\n", filelist.c_str());
		exit(-1);
	}
	string str;
	input_list.clear();
	while (getline(in, str))
	{
		if(verifyFile(str)) {
			input_list.push_back(str);
			printf(" read %s\n", str.c_str());
		}
	}
	

}

void transferDraw(Mat& out_img)
{
	out_img = Mat(WINDOW_HEIGHT, WINDOW_WIDTH, CV_8UC3);
//	glPixelStorei(GL_PACK_ALIGNMENT, (out_img.step & 3) ? 1 : 4);
//	glPixelStorei(GL_PACK_ROW_LENGTH, out_img.step / out_img.elemSize());	
	glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_BGR, GL_UNSIGNED_BYTE, out_img.data);
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

bool verifyDir(const string pathstr)
{
	return is_directory(path(pathstr));
}

bool verifyFile(const string pathstr)
{
	return is_regular_file(path(pathstr));
}
