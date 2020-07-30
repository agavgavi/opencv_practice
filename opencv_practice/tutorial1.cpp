#include "tutorial1.h"
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
Tutorial1::Tutorial1(string image_name, string windowName)
{
    Mat image = imread(image_name);

    if (image.empty()) {
        cout << "Could not locate/open image: \'" << image_name << "\'" << endl;
        cin.ignore().get();
        return;
    }
    namedWindow(windowName);
    imshow(windowName,image);
    waitKey(0);
    destroyWindow(windowName);
}
