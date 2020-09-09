#ifndef OPENCVRECOGNITION_H
#define OPENCVRECOGNITION_H


#include <opencv4/opencv2/opencv.hpp>
class OpenCVRecognition
{
public:
    OpenCVRecognition();
    cv::Mat DetectAndDisplay(cv::Mat, cv::CascadeClassifier);
};

#endif // OPENCVRECOGNITION_H
