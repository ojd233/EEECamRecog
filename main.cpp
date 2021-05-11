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

void setup(void)
{
    setupCamera(320, 240);
}

char identifyImage(Mat cameraIso){
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

//        //Prep Blur Matrices
//        Mat TempABlur;
//        Mat TempBBlur;
//        Mat TempCBlur;
//        Mat TempDBlur;
//        Mat TempEBlur;
//        Mat TempFBlur;
//
//        //Blur all templates
//        cv::medianBlur(TemplateA, TempABlur, 11);
//        cv::medianBlur(TemplateB, TempBBlur, 11);
//        cv::medianBlur(TemplateC, TempCBlur, 11);
//        cv::medianBlur(TemplateD, TempDBlur, 11);
//        cv::medianBlur(TemplateE, TempEBlur, 11);
//        cv::medianBlur(TemplateF, TempFBlur, 11);

        //COnvert all to HSV
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


        //Remove any background reading before comparing
        if (matchA >= 44 && matchA <= 45){

            matchA = 0;
        }
        if (matchB >= 44 && matchB <= 45){
            matchB = 0;
        }
        if (matchC >= 43 && matchC <= 45){
            matchC = 0;
        }
        if (matchD >= 44 && matchD <= 46){
            matchD = 0;
        }
        if (matchE >= 44 && matchE <= 47){
            matchE = 0;
        }
        if (matchF >= 44 && matchF <= 45){
            matchF = 0;
        }

        //Display percentages (TROUBLESHOOTING ONLY)
        std::cout << matchA << std::endl;
        std::cout << matchB << std::endl;
        std::cout << matchC << std::endl;
        std::cout << matchD << std::endl;
        std::cout << matchE << std::endl;
        std::cout << matchF << std::endl;
        //Compare match percentages and return the greatest
        if(matchA > matchB && matchA > matchC && matchA > matchD && matchA > matchE && matchA > matchF && matchA > 0){
            char out = 'A';
            return out;
        }
        if(matchB > matchA && matchB > matchC && matchB > matchD && matchB > matchE && matchB > matchF && matchB > 0){
            char out = 'B';
            return out;
        }
        if(matchC > matchB && matchC > matchA && matchC > matchD && matchC > matchE && matchC > matchF && matchC > 0){
            char out = 'C';
            return out;
        }
        if(matchD > matchB && matchD > matchC && matchD > matchA && matchD > matchE && matchD > matchF && matchD > 0){
            char out = 'D';
            return out;
        }
        if(matchE > matchB && matchE > matchC && matchE > matchD && matchE > matchA && matchE > matchF && matchE > 0){
            char out = 'E';
            return out;
        }
        if(matchF > matchB && matchF > matchC && matchF > matchD && matchF > matchE && matchF > matchA && matchF > 0){
            char out = 'F';
            return out;
        }
        else{
            char out = 'Z';
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
    while(1){
        Mat cam, camCont, camSC;
        resizeCamera(320, 240);
        Mat camTp = captureFrame();
        while(cam.empty())
        cam = captureFrame();
//        camCont = captureFrame();
//        camSC = captureFrame();

        //imshow("Camera", cam);
//        Mat frame = imread("ShapeCounter.PNG");
//        Mat frameCont = imread("ShapeCounter.PNG");
//        Mat frameSC = imread("ShapeCounter.PNG");




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

                cv::approxPolyDP(Mat(contours[m]),approxedcontours[m], 2, true);

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
                char identity = identifyImage(transformed);
                std::cout<< identity<<std::endl;
                if (identity == 'E'){
                    int num = shapeCount(frameIso);
                    std::cout<< num << std::endl;
                }
                if (identity == 'F'){
                    int num = shapeCount(frameIso);
                    std::cout<< num << std::endl;
                }
            }
        }



        imshow("Original Image", cam);


        std::cout << " " << std::endl;
//		std::vector< std::vector<cv::Point> > contours;
//		std::vector<Vec4i>hierarchy;
//		cv::findContours(frameIso, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE, Point(0,0));
//
//		for(int i = 0; i < contours.size(); i++)
//		{
//			drawContours(camCont, contours, i, Scalar(0,0,0), 2, LINE_8, noArray(), 0, Point());
//		}
//
//
//        std::vector< std::vector<cv::Point> > approxedcontours(contours.size());
//        int square = 0;
//        int triangle = 0;
//        int circle = 0;
//		for(int x = 0; x < contours.size(); x++)
//		{
//			cv::approxPolyDP(Mat(contours[x]),approxedcontours[x], 2, true);

//			std::cout << "Size of contour " << x <<  " = " << approxedcontours[x].size() << std::endl;
//
//			if (approxedcontours[x].size() == 4){
//                square++;
//			}
//			if (approxedcontours[x].size() == 3){
//                triangle++;
//			}
//			if (approxedcontours[x].size() >= 5){
//                circle++;
//			}
//		}

		//imshow("Contours", camCont);
		//std::cout << "There are " << approxedcontours.size() << " shapes" << std::endl;
//		std::cout << "There are " << square << " quadrilaterals" << std::endl;
//		std::cout << "There are " << triangle << " triangles" << std::endl;
//		std::cout << "There are " << circle << " circles" << std::endl;
//        Mat TemplateFrameA = imread("RedShortCut.PNG");
        //Mat TemplateFrameB = imread("SingleBorderTemplate.png");
//        Mat TempAHSV;
        //Mat TempBHSV;
//        Mat TempAIso;
        //Mat TempBIso;
//        Mat TempABlur;
//        cv::medianBlur(TemplateFrameA, TempABlur, 11);
//        cvtColor(TempABlur, TempAHSV, COLOR_BGR2HSV);
//        inRange(TempAHSV, Scalar(125,100,30), Scalar(255,255,255), TempAIso);
        //imshow("Template", TempAIso);

//        cvtColor(TemplateFrameB, TempBHSV, COLOR_BGR2HSV);
//        inRange(TempBHSV, Scalar(125,100,30), Scalar(255,255,255), TempBIso);

//        Point TempCentA = templateMatch(TempAIso, TempAIso, TM_SQDIFF);
//        Point TempCentB = templateMatch(TempAIso, TempBIso, TM_SQDIFF);
//        float matchPerc;
//        matchPerc = compareImages(frameIso, TempAIso);
//        std::cout << "Percentage Match = " << matchPerc << std::endl;
        //std::cout << "B" << TempCentB << std::endl;
        //imshow("TempAIso", TempAIso);


        waitKey(1);





    }

}
