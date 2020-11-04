#ifndef OPENCVRECOGNITION_H
#define OPENCVRECOGNITION_H


#include <opencv4/opencv2/opencv.hpp>
class OpenCVRecognition
{
public:
    OpenCVRecognition(std::string folder_);
    cv::Mat DetectAndDisplay(cv::Mat, cv::CascadeClassifier);
private:
    cv::Mat getAlphaLevel(cv::Mat&);
    bool saveImage(std::string, cv::Mat);
    int faces_amt;
    std::string folder;
    int imCount;
};

#endif // OPENCVRECOGNITION_H
