// Include files for required libraries
#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

//Custom Functions
#include "opencv_aee.hpp"
#include "main.hpp"     // You can use this file for declaring defined values and functions

//I2C Libraries
#include <wiringPi.h>
#include <wiringPiI2C.h>


using namespace cv;

void setup(void)
{
    setupCamera(320, 240);
}

int identifyImage(Mat cameraIso){
        //Load Image Templates
        Mat TemplateA = imread("RedShortCut.PNG");
        Mat TemplateB = imread("GreenShortCut.PNG");
        Mat TemplateC = imread("BlueShortCut.PNG");
        Mat TemplateD = imread("YellowShortCut.PNG");
        Mat TemplateE = imread("ShapeCounter.PNG");
        Mat TemplateF = imread("FollowBlack.PNG");

        //Prep HSV Matrices
        Mat TempAHSV;
        Mat TempBHSV;
        Mat TempCHSV;
        Mat TempDHSV;
        Mat TempEHSV;
        Mat TempFHSV;

        //Prep Isolated Matrices
        Mat TempAIso;
        Mat TempBIso;
        Mat TempCIso;
        Mat TempDIso;
        Mat TempEIso;
        Mat TempFIso;


        //Convert all to HSV
        cvtColor(TemplateA, TempAHSV, COLOR_BGR2HSV);
        cvtColor(TemplateB, TempBHSV, COLOR_BGR2HSV);
        cvtColor(TemplateC, TempCHSV, COLOR_BGR2HSV);
        cvtColor(TemplateD, TempDHSV, COLOR_BGR2HSV);
        cvtColor(TemplateE, TempEHSV, COLOR_BGR2HSV);
        cvtColor(TemplateF, TempFHSV, COLOR_BGR2HSV);

        //Isolate Pink from all
        inRange(TempAHSV, Scalar(125,100,30), Scalar(255,255,255), TempAIso);
        inRange(TempBHSV, Scalar(125,100,30), Scalar(255,255,255), TempBIso);
        inRange(TempCHSV, Scalar(125,100,30), Scalar(255,255,255), TempCIso);
        inRange(TempDHSV, Scalar(125,100,30), Scalar(255,255,255), TempDIso);
        inRange(TempEHSV, Scalar(125,100,30), Scalar(255,255,255), TempEIso);
        inRange(TempFHSV, Scalar(125,100,30), Scalar(255,255,255), TempFIso);

        //Compare camera image to templates
        float matchA = compareImages(cameraIso, TempAIso);
        float matchB = compareImages(cameraIso, TempBIso);
        float matchC = compareImages(cameraIso, TempCIso);
        float matchD = compareImages(cameraIso, TempDIso);
        float matchE = compareImages(cameraIso, TempEIso);
        float matchF = compareImages(cameraIso, TempFIso);


        //Display percentages (TROUBLESHOOTING ONLY)
        std::cout << matchA << std::endl;
        std::cout << matchB << std::endl;
        std::cout << matchC << std::endl;
        std::cout << matchD << std::endl;
        std::cout << matchE << std::endl;
        std::cout << matchF << std::endl;
        waitKey(1000);
        //Compare match percentages and return the greatest
        if(matchA > matchB && matchA > matchC && matchA > matchD && matchA > matchE && matchA > matchF && matchA > 60){
            int out = 1;
            return out;
        }
        if(matchB > matchA && matchB > matchC && matchB > matchD && matchB > matchE && matchB > matchF && matchB > 60){
            int out = 2;
            return out;
        }
        if(matchC > matchB && matchC > matchA && matchC > matchD && matchC > matchE && matchC > matchF && matchC > 60){
            int out = 3;
            return out;
        }
        if(matchD > matchB && matchD > matchC && matchD > matchA && matchD > matchE && matchD > matchF && matchD > 60){
            int out = 4;
            return out;
        }
        if(matchE > matchB && matchE > matchC && matchE > matchD && matchE > matchA && matchE > matchF && matchE > 60){
            int out = 5;
            return out;
        }
        if(matchF > matchB && matchF > matchC && matchF > matchD && matchF > matchE && matchF > matchA && matchF > 60){
            int out = 6;
            return out;
        }
        else{
            char out = 0;
            return out;
        }
}

int shapeCount(Mat cameraIso){
        std::vector< std::vector<cv::Point> > contours;
		std::vector<Vec4i>hierarchy;
		cv::findContours(cameraIso, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE, Point(0,0));

//		for(int i = 0; i < contours.size(); i++)
//		{
//			drawContours(cameraIso, contours, i, Scalar(0,0,0), 2, LINE_8, noArray(), 0, Point());
//		}


        std::vector< std::vector<cv::Point> > approxedcontours(contours.size());
        for(int x = 0; x < contours.size(); x++)
            {
			cv::approxPolyDP(Mat(contours[x]),approxedcontours[x], 2, true);
			}
        std::cout << "There are " << approxedcontours.size() << " shapes" << std::endl;
        return approxedcontours.size();
}

int main(int argc, char** argv)
{
    int fd = wiringPiI2CSetup(7);
    while(1){
        Mat cam, camCont, camSC;
        resizeCamera(320, 240);
        Mat camTp = captureFrame();
        while(cam.empty())
        cam = captureFrame();

        Mat frameHSV;
        Mat frameIso;
        Mat camBlur;
//        cv::medianBlur(cam, camBlur, 11);
        cvtColor(cam, frameHSV, COLOR_BGR2HSV);
        inRange(frameHSV, Scalar(125,100,30), Scalar(255,255,255), frameIso);
        imshow("HSV Pink Isolated", frameIso);
        std::vector<std::vector<cv::Point> > contours;
        std::vector<Vec4i> hierarchy;
        cv::findContours(frameIso, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0,0));



        if (contours.size() > 0){
            int area = 0;
            int conNum;
            std::vector< std::vector<cv::Point> > approxedcontours(contours.size());
            for (int m = 0; m < contours.size(); m++){

                cv::approxPolyDP(Mat(contours[m]),approxedcontours[m], 10, true);

                if(cv::contourArea(approxedcontours[m]) >= area && approxedcontours[m].size() == 4){
                    area = cv::contourArea(approxedcontours[m]);
                    conNum = m;
                    //std::cout<<area<<std::endl;

                }
            }
            if(approxedcontours[conNum].size() == 4){
                std::cout<<approxedcontours[conNum].size()<<std::endl;
                std::cout<<" "<<std::endl;
                drawContours(cam, approxedcontours, conNum, Scalar(0,0,255), 2, LINE_8, noArray(), 0, Point());

                Mat transformed = transformPerspective(approxedcontours[conNum], frameIso, 320, 240);
//            std::cout<<transformed<<std::endl;
                cv::Size s = transformed.size();
                if(s.height > 0){
                    imshow("Transformed", transformed);


                    }
                int identity = identifyImage(transformed);

                std::cout<< identity<<std::endl;
                if (identity == 5){
                    int num = (shapeCount(frameIso) * 10);
                    std::cout<< num << std::endl;
                    wiringPiI2CWrite(fd, num);



                }
                if (identity == 6){
                    int num = (shapeCount(frameIso) * -10);
                    std::cout<< num << std::endl;
                    wiringPiI2CWrite(fd, num);


                }
                else{
                    wiringPiI2CWrite(fd, identity);


                }
            }
        }



        imshow("Original Image", cam);


        std::cout << " " << std::endl;

        waitKey(1);





    }

}
