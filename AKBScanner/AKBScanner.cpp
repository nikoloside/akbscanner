// AKBScanner.cpp : 僐儞僜乕儖 傾僾儕働乕僔儑儞偺僄儞僩儕 億僀儞僩傪掕媊偟傑偡丅
//

#include "stdafx.h"

#include "../tinydir/tinydir.h"
#include <iostream>
#include <fstream> 
#include <vector>
#include <string>

#include <opencv2/opencv.hpp> // インクルードファイル指定
#include <opencv2/core.hpp> // インクルードファイル指定
#include <opencv2/imgproc.hpp> // インクルードファイル指定
#include <opencv2/highgui.hpp> // インクルードファイル指定
#include <opencv2/calib3d.hpp> // インクルードファイル指定

using namespace std;
using namespace cv; // 名前空間の指定

ofstream t_out("./Data_Serial.txt");


void get_file_names(string dir_name, vector<string> &names, vector<string> &path) {
	names.clear();
	tinydir_dir dir;
	tinydir_open(&dir, dir_name.c_str());

	while (dir.has_next){
		tinydir_file file;
		tinydir_readfile(&dir, &file);
		if (!file.is_dir)
		{
			names.push_back(file.name);
			path.push_back(file.path);
		}
		tinydir_next(&dir);
	}
	tinydir_close(&dir);
}

Mat getROI(Mat origin) {
	/*
	Mat input;
	origin.convertTo(input, CV_8U);
	vector< vector< Point > > contours;
	findContours(input, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

	// 輪郭が四角形かの判定
	for (auto contour = contours.begin(); contour != contours.end(); contour++) {
		// 輪郭を直線近似
		vector< cv::Point > approx;
		approxPolyDP(Mat(*contour), approx, 50.0, true);
		// 近似が4線かつ面積が一定以上なら四角形
		double area = contourArea(approx);
		// 面積の一番小さい外接矩形で凸図形を囲み
		RotatedRect rect = minAreaRect(Mat(*contour));
		// 外接矩形の４つの点をRotatedRect rectから変換
		Point2f vertices[4];
		rect.points(vertices);
		double width_image = rect.size.width;
		double height_image = rect.size.height;
		double rectArea = width_image * height_image;
		double WHrate = (width_image>height_image ? width_image / height_image : height_image / width_image);

		if (approx.size() == 4 && area > 200000.0 && rectArea > 200000.0 && WHrate > 0 ) {
			//polylines(result, vertices, true, Scalar(255), 2);

			//描く
			Rect i_rect = boundingRect(Mat(*contour));
			Mat ROI = origin(i_rect);

			imshow("test1", ROI);
			waitKey(0);
		}
	}
	*/
	//将方框识别出来，然后用射影变换算出正常的长方形图片 输入 原图 输出 目标方框内图片
	Rect myROI(430, 680, 700, 200);

	Mat result = origin(myROI);

	return result;

}



struct datas {
	string str;
	Mat graph;
};

vector < datas > dataset;

double coefficient(Mat& image1, Mat& image2) {


	Mat result;
	matchTemplate(image1, image2, result, CV_TM_CCOEFF_NORMED);

	//    cout<<endl;
	//    cout<<endl;

	float min = 1;
	float max = 0;

	for (int i = 0; i < result.cols; i++) {
		for (int j = 0; j < result.rows; j++) {
			float coef = result.at<float>(j, i);
			//            cout<<coef<<" ";
			if (min>coef) min = coef;
			if (max<coef) max = coef;
		}
		//        cout<<endl;
	}

	return max;

}

void initDataset() {

	const char ImportData[] = "dataset";
	char dataset_str[] = "abcdefhijkmnpqrstuvwxyz23456789";

	//cout << sizeof(dataset_str) << endl;
	for (int i = 0; i < 31; i++) {
		char temp = dataset_str[i];
		string tempstr(1, temp);
		string path = "./dataset/" + tempstr + ".jpg";
		Mat temp_g = imread(path, CV_8U);

		datas d;
		d.str = tempstr;
		d.graph = temp_g;

		//cout << tempstr << endl;

		//imshow("test_0", d.graph);
		//waitKey(0);

		dataset.push_back(d);
	}

}

string getABC(Mat input) {

	double max = 0;
	int index = -1;

	cv::Mat white_img(cv::Size(200, 200), CV_8U, 255);
	cv::Mat mat = (cv::Mat_<double>(2, 3) << 1.0, 0.0, 70, 0.0, 1.0, 70);
	cv::warpAffine(input, white_img, mat, white_img.size(), CV_INTER_LINEAR, cv::BORDER_TRANSPARENT);

	//cout << "check " << endl;

	for (int i = 0; i < dataset.size(); i++) {
		double cof = coefficient( dataset[i].graph, white_img);

		//imshow("test1", white_img);
		//imshow("test2", dataset[i].graph);

		//cout << "cof: " << cof << endl;

		waitKey(0);

		if (cof > max && cof > 0.7) {
			max = cof;
			index = i;
		}

	}

	double cofi = coefficient(dataset[7].graph, white_img);
	double cofj = coefficient(dataset[8].graph, white_img);
	if ((cofi > 0.8 && cofj > 0.8) || (cofj > 0.9)) index = 8;
	else if (index == 7 && cofi > 0.8 && cofj < 0.8) index = 7;

	if (index >= 0) return dataset[index].str;
	else return "0";

}

struct cell {
	double no;
	Rect rect;
};

bool operator<(const cell& left, const cell& right)
{
	return left.no < right.no;
}

bool operator>(const cell& left, const cell& right)
{
	return left.no > right.no;
}


vector < Mat > testSplit(Mat code) {
	//把两个号码土块分割成小的土块，分开识别	 输入
	Mat dilate;

	double e_size = 2.5;
	Mat element = getStructuringElement(MORPH_RECT, Size(e_size, e_size));

	erode(code, dilate, element);

	Mat input;
	dilate.convertTo(input, CV_8U);
	vector <Mat>  contours;
	vector < cell > result;

	//cout << " next " << endl;

	findContours(input, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

	for (auto contour = contours.begin(); contour != contours.end(); contour++) {

		Rect c_rect = boundingRect(Mat(*contour));

		double area = c_rect.width * c_rect.height;
		//cout << area << " " << c_rect.width << " " << c_rect.height << endl;
		double width = c_rect.width;
		double height = c_rect.height;
		double whrate = (width > height)?(width / height):(height / width);

		//imshow("test1", dilate(c_rect));

		//waitKey(0);

		if (c_rect.width < 25 && c_rect.height < 25 || area > 20000 || area < 400 || whrate >3) continue;

		//cout << " accepted " << endl;

		double delta = 0;
		c_rect.height = c_rect.height + c_rect.y - delta;
		c_rect.y = delta;

		cell a; a.no = c_rect.x; a.rect = c_rect;
		result.push_back(a);

	}

	std::sort(result.begin(), result.end());//昇順ソート

	vector < Mat > result_img;

	for (int i = 0; i < result.size(); i++){

		Mat test = dilate(result[i].rect);

		Mat erode;
		cv::dilate(test, erode, element);

		result_img.push_back(erode);

		//imshow("test", test);

		//waitKey(0);

	}
	return result_img;
}

string getCodeNumber(Mat input, string filename) {


	Rect myROI1(0, 0, 350, 90);
	Rect myROI2(350, 0, 350, 90);

	Mat code1 = input(myROI1);
	Mat code2 = input(myROI2);

	vector < Mat > code1_list = testSplit(code1);
	vector < Mat > code2_list = testSplit(code2);

	//code1

	string result1;
	string result2;

	int a_width = 200;

	for (int i = 0; i < code1_list.size(); i++) {

		string temp_str = getABC(code1_list[i]);

		result1 = result1 + temp_str;
	}

	cout << result1 << " ";
	
	//code2
	for (int i = 0; i < code2_list.size(); i++) {


		string temp_str = getABC(code2_list[i]);

		result2 = result2 + temp_str;
	}
	
	cout << result2 << "     " << code1_list.size() + code2_list.size() << endl;
	
	return result1 + " " + result2;
}

int main()
{
	const char ImportData[] = "scanned";
	vector<string> result;
	vector<string> img_names;
	vector<string> img_paths;

	dataset.clear();

	initDataset();

	get_file_names(ImportData, img_names, img_paths);

	cout << "Find Data : (num " << img_names.size() << ") " << endl;
	for (unsigned int i = 0; i < img_names.size(); ++i)
		cout << img_names[i] << endl;
	cout << endl;

	int count = 0;

	for (unsigned int i = 0; i < img_paths.size(); ++i) {
		
		Mat src = imread(img_paths[i]);

		Mat croppedImage = getROI(src);

		Mat gray_img;

		cvtColor(croppedImage, gray_img, CV_RGB2GRAY);

		Mat binay, dilate, erode;

		threshold(gray_img, binay, 0, 255, THRESH_BINARY|THRESH_OTSU);

		double e_size = 2.5;
		Mat element = getStructuringElement(MORPH_RECT, Size(e_size, e_size));

		cv::dilate(binay, dilate, element);
		cv::erode(dilate, erode, element);
		
		result.push_back(getCodeNumber(erode, img_names[i]));

		//test block

		//imshow("ROI", erode);

		//waitKey(0);

		//test

		t_out << result[i] << endl;

		if (result[i] != "") count++;

	}

	cout << "Total Recognized : " << count << endl;

	//system("del .\\scanned\\*.jpg");

	system("pause");

	return 0;
}