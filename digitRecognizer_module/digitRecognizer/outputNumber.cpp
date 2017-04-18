//
//  outputNumber.cpp
//  digitRecognizer
//
//  Created by Sun Xi on 12/04/2017.
//  Copyright © 2017 SUNXI. All rights reserved.
//

#include "digitRecognize.h"
#include <stdio.h>
#include <stdlib.h> // Include the standard library
#include <unistd.h>



using namespace cv;

int recognize(Mat input) {
    
    //std::cout << "path to image: " << imgPath << std::endl;
    Mat cvOld = Mat(cv::Size(28, 28), CV_8UC1);
    cvOld = input; //imread(imgPath, CV_8UC1); //change the directory
    Mat cvThreshold = cvOld.clone();
    adaptiveThreshold(cvOld, cvThreshold, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, 101, 1.0);
    
    
    
    
    DigitRecognizer *dr = new DigitRecognizer();
    
    
    
    bool b = dr->train((char*)"train-images.idx3-ubyte", (char*)"train-labels.idx1-ubyte"); //change directory
    std::cout << b << std::endl;
    
    int dist = cvThreshold.rows;
    cv::Mat cell = cv::Mat(cv::Size(dist, dist), CV_8UC1);
    for (int y = 0; y < dist; y++) {
        uchar* ptr = cell.ptr(y);
        for (int x = 0; x < dist; x++) {
            ptr[x] = cvThreshold.at<uchar>(y, x);
        }
    }
    std::cout << cvThreshold.rows << " " << cvThreshold.cols << std::endl;
    
    int number = dr->classify(cell);
    std::cout << number << std::endl;
    return number;
}

