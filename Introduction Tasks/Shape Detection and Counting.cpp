// Include files for required libraries
#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

//Custom Functions
#include "opencv_aee.hpp"
#include "main.hpp"     // You can use this file for declaring defined values and functions



using namespace cv;


int main(int argc, char** argv)
{
        Mat frame = imread("ShapeCounter.PNG");
        Mat frameCont = imread("ShapeCounter.PNG");
        Mat frameSC = imread("ShapeCounter.PNG");

        imshow("Original Image", frame);
        waitKey(1);

        Mat frameHSV;
        Mat frameIso;
        cvtColor(frame, frameHSV, COLOR_BGR2HSV);
        inRange(frameHSV, Scalar(125,100,30), Scalar(255,255,255), frameIso);
        imshow("HSV Pink Isolated", frameIso);
        waitKey(1);

		std::vector< std::vector<cv::Point> > contours;
		std::vector<Vec4i>hierarchy;
		cv::findContours(frameIso, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE, Point(0,0));

		for(int i = 0; i < contours.size(); i++)
		{
			drawContours(frameCont, contours, i, Scalar(0,0,0), 2, LINE_8, noArray(), 0, Point());
		}


        std::vector< std::vector<cv::Point> > approxedcontours(contours.size());
        int square = 0;
        int triangle = 0;
        int circle = 0;
		for(int x = 0; x < contours.size(); x++)
		{
			cv::approxPolyDP(Mat(contours[x]),approxedcontours[x], 2, true);

			std::cout << "Size of contour " << x <<  " = " << approxedcontours[x].size() << std::endl;

			if (approxedcontours[x].size() == 4){
                square++;
			}
			if (approxedcontours[x].size() == 3){
                triangle++;
			}
			if (approxedcontours[x].size() >= 5){
                circle++;
			}
		}

		imshow("Contours", frameCont);
		std::cout << "There are " << approxedcontours.size() << " shapes" << std::endl;
		std::cout << "There are " << square << " quadrilaterals" << std::endl;
		std::cout << "There are " << triangle << " triangles" << std::endl;
		std::cout << "There are " << circle << " circles" << std::endl;



        waitKey();







}
