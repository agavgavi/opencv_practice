#include "cascadetest.h"
#include "opencv4/opencv2/objdetect.hpp"
#include "opencv4/opencv2/highgui.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/videoio.hpp"
#include <iostream>

using namespace std;

void detectAndDisplay( cv::Mat frame);

cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eyes_cascade;
CascadeTest::CascadeTest(int argc, char *argv[])
{

}
