//Inlcude libraries
#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;

int main()
{

    Mat frame = imread("RedCar.bmp");
    while(1){
        imshow("Original Image", frame);

        //char large[4];

        Mat erodedG;
        Mat dilatedG;
        Mat erodedB;
        Mat dilatedB;
        Mat erodedRL;
        Mat dilatedRL;
        Mat erodedRU;
        Mat dilatedRU;
        Mat spotFilter = cv::getStructuringElement(MORPH_ELLIPSE, Size(5,5));
        Mat maskMorph = cv::getStructuringElement(MORPH_ELLIPSE, Size(10,10));


        Mat frameHSV_G;
        cvtColor(frame, frameHSV_G, COLOR_BGR2HSV);
        inRange(frameHSV_G, Scalar(40, 68, 57), Scalar(70, 255, 255), frameHSV_G);
        cv::erode(frameHSV_G,erodedG,spotFilter);
        cv::dilate(erodedG,dilatedG,maskMorph);

        Mat frameHSV_B;
        cvtColor(frame, frameHSV_B, COLOR_BGR2HSV);
        inRange(frameHSV_B, Scalar(100, 150, 0), Scalar(140, 255, 255), frameHSV_B);
        cv::erode(frameHSV_B,erodedB,spotFilter);
        cv::dilate(erodedB,dilatedB,maskMorph);

        Mat frameHSV_RL;
        cvtColor(frame, frameHSV_RL, COLOR_BGR2HSV);
        inRange(frameHSV_RL, Scalar(0, 50, 50), Scalar(10, 255, 255), frameHSV_RL);
        cv::erode(frameHSV_RL,erodedRL,spotFilter);
        cv::dilate(erodedRL,dilatedRL,maskMorph);

        Mat frameHSV_RU;
        cvtColor(frame, frameHSV_RU, COLOR_BGR2HSV);
        inRange(frameHSV_RU, Scalar(170, 50, 50), Scalar(180, 255, 255), frameHSV_RU);
        cv::erode(frameHSV_RU,erodedRU,spotFilter);
        cv::dilate(erodedRU,dilatedRU,maskMorph);

        imshow("Green Isolated", dilatedG);
        imshow("Blue Isolated", dilatedB);
        imshow("Red LOWER Isolated", dilatedRL);
        imshow("Red UPPER Isolated", dilatedRU);
        cv::waitKey(1);


        int nonzeroB;
        int nonzeroG;
        int nonzeroRU;
        int nonzeroRL;
        int nonzeroR;

        nonzeroB = countNonZero(dilatedB);
        nonzeroG = countNonZero(dilatedG);
        nonzeroRU = countNonZero(dilatedRU);
        nonzeroRL = countNonZero(dilatedRL);
        nonzeroR = nonzeroRU + nonzeroRL;

        cv::waitKey(8000);
        if (nonzeroB > nonzeroG && nonzeroB > nonzeroR){
            std::cout << "The object is Blue" << std::endl;
            break;
        }

        if (nonzeroG > nonzeroB && nonzeroG > nonzeroR){
            std::cout << "The object is Green" << std::endl;
            break;
        }

        if (nonzeroR > nonzeroG && nonzeroR > nonzeroB){
            std::cout << "The object is Red" << std::endl;
            break;
        }

        }
    destroyAllWindows();
}
