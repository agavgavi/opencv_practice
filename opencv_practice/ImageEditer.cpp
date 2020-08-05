#include "ImageEditer.h"

#include <opencv4/opencv2/opencv.hpp>

ImageEditer::ImageEditer()
{

}

int ImageEditer::newEditor(string src_url, string dest_url) {
    cv::Mat original_image = cv::imread(src_url); // Read an image from the location provided and store it in a Mat called image. (OPENCV DOES BGR NOT RGB for channels)


    if (original_image.empty()) {    // If anything goes wrong, the Mat image will be empty, so we can check for that and then spit out an error message.
        cerr << endl << "ERROR: Could not locate/open image: \'" << src_url << "\'" << endl;
        return -1; // Finally we return out of the Class to allow for the program to end.
    }

    string windowName = "Saved Image";
    cv::namedWindow(windowName); // We create a Window for OpenCv to use, and pass in the name of the image from the object declaration.
                                /* namedWindow has some flags that can be set:
                                 * WINDOW_AUTOSIZE (default): User can't resize the window and the image is displayed at original size.
                                 * WINDOW_NORMAL: User can resize the window.
                                 */

    int SliderVal1 = 50;
    cv::createTrackbar("Brightness", windowName, &SliderVal1, 100);

    int SliderVal2 = 50;
    cv::createTrackbar("Contrast", windowName, &SliderVal2, 100);
    cv::Mat dest;
    while(true) {

        int Brightness = SliderVal1 - 50;
        double Contrast = SliderVal2 / 50.0;
        original_image.convertTo(dest, -1,Contrast,Brightness);
        cv::imshow(windowName, dest);
        if(cv::waitKey(10) == 'q') { // Wait for the 'q' key for 10 ms. If that key isn't pressed or any other key is pressed, do nothing and continue to next iteration of the loop.
                                    // If 'q' key is pressed, break out of the while loop and end the video.
            cout << "Escape Key pressed. Closing \'" << src_url << "\'" << endl;
            break;
        }
    }

    bool sSuccess = cv::imwrite(dest_url, dest); // Write the image to a file.

    if(sSuccess == false) {
        cerr << endl << "ERROR: Could not write to image: \'" << dest_url << "\'" << endl;
        return -1; // Finally we return out of the func to allow for the program to end.
    }

    cout << "Image: \'" << dest_url << "\' written to disk successfully!" << endl; // Display a confirmation message to the console.

    cv::destroyWindow(windowName);  // After the key is pressed we destroy the window we created earlier.

    return 0;
}
