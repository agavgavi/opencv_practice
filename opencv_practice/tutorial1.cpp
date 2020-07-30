#include "tutorial1.h"
#include <opencv4/opencv2/opencv.hpp>

Tutorial1::Tutorial1()
{
}

// A function to load a specific image passed in on object creation.
int Tutorial1::LoadImage(string image_name, string windowName) {
    cv::Mat image = cv::imread(image_name); // Read an image from the location provided and store it in a Mat called image. (OPENCV DOES BGR NOT RGB for channels)
                                            /* imread has some flags we can do:
                                             * IMREAD_UNCHANGED: allows for alpha channels
                                             * IMREAD_GRAYSCALE: Converts the image to grayscale
                                             * IMREAD_COLOR (DEFAULT): Normal 3 channel color image.
                                             */

    if (image.empty()) {    // If anything goes wrong, the Mat image will be empty, so we can check for that and then spit out an error message.
        cout << "Could not locate/open image: \'" << image_name << "\'" << endl;
        cin.get(); // We wait for any keypress before returning.
        return -1; // Finally we return out of the Class to allow for the program to end.
    }

    cv::namedWindow(windowName); // We create a Window for OpenCv to use, and pass in the name of the image from the object declaration.
                                /* namedWindow has some flags that can be set:
                                 * WINDOW_AUTOSIZE (default): User can't resize the window and the image is displayed at original size.
                                 * WINDOW_NORMAL: User can resize the window.
                                 */

    cv::imshow(windowName,image); // We link the window that was created and the Mat that contains the image and show the window.

    cv::waitKey(0); // Finally we wait for any key to be pressed before continuing the code. The next line won't run until a key is pressed.

    cv::destroyWindow(windowName);  // After the key is pressed we destroy the window we created earlier.

    return 0;
}


int Tutorial1::CreateImage(string windowName, int blue, int green, int red) {

    cv::Mat image(600,800, CV_8UC3, cv::Scalar(blue,green,red)); // Create a material instead of from an image or video on disk but through the constructor. There are many options for parameters.
                                                                 /* The constructor takes:
                                                                  * rows: (height of the image in pixels)
                                                                  * cols: (width of the image in pixels)
                                                                  * type: Data type of the 2D array, there are many openCV ones,
                                                                  *       we picked CV_8UC3, which means each location in the array in an unsigned 8 bit int and there are 3 channels for Blue, Green, and Red.
                                                                  * s: A Scalar value that can initialize every element in the array (also known as the pixels) to a given color from this tuple.
                                                                  */

    cv::namedWindow(windowName); // We create a Window for OpenCv to use, and pass in the name of the image from the object declaration.
                                /* namedWindow has some flags that can be set:
                                 * WINDOW_AUTOSIZE (default): User can't resize the window and the image is displayed at original size.
                                 * WINDOW_NORMAL: User can resize the window.
                                 */

    cv::imshow(windowName,image); // We link the window that was created and the Mat that contains the image and show the window.

    cv::waitKey(0); // Finally we wait for any key to be pressed before continuing the code. The next line won't run until a key is pressed.

    cv::destroyWindow(windowName);  // After the key is pressed we destroy the window we created earlier.
    return 0;
}
