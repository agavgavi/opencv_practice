#include "ImageFuncs.h"
#include <opencv4/opencv2/opencv.hpp>

ImageFunctions::ImageFunctions()
{
}

// A function to load a specific image passed in on object creation.
int ImageFunctions::LoadImage(string image_name, string windowName) {
    cv::Mat image = cv::imread(image_name); // Read an image from the location provided and store it in a Mat called image. (OPENCV DOES BGR NOT RGB for channels)
                                            /* imread has some flags we can do:
                                             * IMREAD_UNCHANGED: allows for alpha channels
                                             * IMREAD_GRAYSCALE: Converts the image to grayscale
                                             * IMREAD_COLOR (DEFAULT): Normal 3 channel color image.
                                             */

    if (image.empty()) {    // If anything goes wrong, the Mat image will be empty, so we can check for that and then spit out an error message.
        cerr << endl << "ERROR: Could not locate/open image: \'" << image_name << "\'" << endl;
        return -1; // Finally we return out of the func to allow for the program to end.
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

// A function that will create a blank image of the same color as the 3 elements passed into it.
int ImageFunctions::CreateImage(string windowName, int blue, int green, int red) {

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

// A function that will do a direct copy of an image. Pass it the url of the image and it will save a copy
int ImageFunctions::CopyImage(string src_url, string dest_url) {

    cv::Mat original_image = cv::imread(src_url); // Read an image from the location provided and store it in a Mat called image. (OPENCV DOES BGR NOT RGB for channels)


    if (original_image.empty()) {    // If anything goes wrong, the Mat image will be empty, so we can check for that and then spit out an error message.
        cerr << endl << "ERROR: Could not locate/open image: \'" << src_url << "\'" << endl;
        return -1; // Finally we return out of the Class to allow for the program to end.
    }
    // When actually working with images, between above and below right here would be where the function would make edits to the photo. Right now it's just a direct copy.

    bool sSuccess = cv::imwrite(dest_url, original_image); // Write the image to a file.

    if(sSuccess == false) {
        cerr << endl << "ERROR: Could not write to image: \'" << dest_url << "\'" << endl;
        return -1; // Finally we return out of the func to allow for the program to end.
    }

    cout << "Image: \'" << dest_url << "\' written to disk successfully!" << endl; // Display a confirmation message to the console.

    string windowName = "Saved Image";
    cv::namedWindow(windowName); // We create a Window for OpenCv to use, and pass in the name of the image from the object declaration.
                                /* namedWindow has some flags that can be set:
                                 * WINDOW_AUTOSIZE (default): User can't resize the window and the image is displayed at original size.
                                 * WINDOW_NORMAL: User can resize the window.
                                 */

    cv::imshow(windowName,original_image); // We link the window that was created and the Mat that contains the image and show the window.

    cv::waitKey(0); // Finally we wait for any key to be pressed before continuing the code. The next line won't run until a key is pressed.

    cv::destroyWindow(windowName);  // After the key is pressed we destroy the window we created earlier.

    return 0;
}

// Adjust the brightness up and down in steps of two from the inputted int. So if amount = 20, increase brightness by 20, 40, then decrease by -20, -40
int ImageFunctions::EditBrightness(string src_url, int amount) {

    cv::Mat image = cv::imread(src_url); // Read an image from the location provided and store it in a Mat called image. (OPENCV DOES BGR NOT RGB for channels)


    if (image.empty()) {    // If anything goes wrong, the Mat image will be empty, so we can check for that and then spit out an error message.
        cerr << endl << "ERROR: Could not locate/open image: \'" << src_url << "\'" << endl;
        return -1; // Finally we return out of the Class to allow for the program to end.
    }

    cv::Mat imageBrightnessHigh1, imageBrightnessHigh2, imageBrightnessLow1, imageBrightnessLow2; // Create 4 mats for the 4 steps of brightness we are editing.

    image.convertTo(imageBrightnessHigh1,-1, 1, amount); // Converts the brightness of the image for all 4 mats and saved it to an output Mat.
    image.convertTo(imageBrightnessHigh2,-1, 1, amount*2);
    image.convertTo(imageBrightnessLow1,-1, 1, -amount);
    image.convertTo(imageBrightnessLow2,-1, 1, -amount*2);
                                                            // convertTo works as so:
                                                            /* It takes 4 parameters.
                                                             * m: the output mat where the edited image will be saved to. Notice that this can work in place, but by default the original image isn't touched.
                                                             * rtype: what the type of the output image is. if the value is negative, it will just base it on the input image.
                                                             * alpha: A base multiple that each value will be multipled by in the original image.
                                                             * beta: The value offset that will be added to each pixel in the base image.
                                                             *
                                                             * This loeads to a formula something like this:
                                                             * pixel value in output image = pixel value in input image * alpha + beta.
                                                             */

    string windowNameOG = "Original Image";                                 // All of our new windows need names so we specify them to list how much the image was edited by.
    string windowNameHigh1 = "Brightness increased by " + to_string(amount);
    string windowNameHigh2 = "Brightness increased by " + to_string(2*amount);
    string windowNameLow1 = "Brightness decreased by " + to_string(-amount);
    string windowNameLow2 = "Brightness decreased by " + to_string(-2*amount);

                                                        // Then we create all the named windows
    cv::namedWindow(windowNameOG, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameHigh1, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameHigh2, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameLow1, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameLow2, cv::WINDOW_NORMAL);

                                                        // Then we actually display all the named windows with the specific mats that correspond to them.
    cv::imshow(windowNameOG, image);
    cv::imshow(windowNameHigh1, imageBrightnessHigh1);
    cv::imshow(windowNameHigh2, imageBrightnessHigh2);
    cv::imshow(windowNameLow1, imageBrightnessLow1);
    cv::imshow(windowNameLow2, imageBrightnessLow2);

    // Here we wait for input then kill all of the window processes.
    cv::waitKey(0);
    cv::destroyAllWindows();
}