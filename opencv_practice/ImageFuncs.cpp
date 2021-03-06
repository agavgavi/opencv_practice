#include "ImageFuncs.h"
#include <opencv4/opencv2/opencv.hpp>

ImageFunctions::ImageFunctions()
{
}

//! A function to load a specific image passed in on object creation.
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

//! A function that will create a blank image of the same color as the 3 elements passed into it.
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

//! A function that will do a direct copy of an image. Pass it the url of the image and it will save a copy
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

//! Adjust the brightness up and down in steps of two from the inputted int. So if amount = 20, increase brightness by 20, 40, then decrease by -20, -40
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

    return 0;
}

//! Adjust the contrast up and down in steps of two from the inputted int. So if amount = 2, increase brightness by 2, 4, then decrease by 1/2, 1/4
int ImageFunctions::EditContrast(string src_url, int amount) {

    cv::Mat image = cv::imread(src_url); // Read an image from the location provided and store it in a Mat called image. (OPENCV DOES BGR NOT RGB for channels)


    if (image.empty()) {    // If anything goes wrong, the Mat image will be empty, so we can check for that and then spit out an error message.
        cerr << endl << "ERROR: Could not locate/open image: \'" << src_url << "\'" << endl;
        return -1; // Finally we return out of the Class to allow for the program to end.
    }

    cv::Mat imageContrastHigh1, imageContrastHigh2, imageContrastLow1, imageContrastLow2; // Create 4 mats for the 4 steps of brightness we are editing.

    image.convertTo(imageContrastHigh1,-1, amount, 0); // Converts the contrast of the image for all 4 mats and saved it to an output Mat.
    image.convertTo(imageContrastHigh2,-1, amount*2, 0);
    image.convertTo(imageContrastLow1,-1, (double) 1/amount, 0);
    image.convertTo(imageContrastLow2,-1, (double) 1/(amount*2), 0);
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
    string windowNameHigh1 = "Contrast increased by x" + to_string(amount);
    string windowNameHigh2 = "Contrast increased by x" + to_string(2*amount);
    string windowNameLow1 = "Contrast decreased by x" + to_string((double) 1/amount);
    string windowNameLow2 = "Contrast decreased by x" + to_string((double) 1/(2*amount));

                                                        // Then we create all the named windows
    cv::namedWindow(windowNameOG, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameHigh1, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameHigh2, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameLow1, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameLow2, cv::WINDOW_NORMAL);

                                                        // Then we actually display all the named windows with the specific mats that correspond to them.
    cv::imshow(windowNameOG, image);
    cv::imshow(windowNameHigh1, imageContrastHigh1);
    cv::imshow(windowNameHigh2, imageContrastHigh2);
    cv::imshow(windowNameLow1, imageContrastLow1);
    cv::imshow(windowNameLow2, imageContrastLow2);

    // Here we wait for input then kill all of the window processes.
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

//! This function will equalize the intensity of the image, making it the same across the board. It can output both a grayscale equalization and a color equalization based on the value of the color bool.
int ImageFunctions::HistEqualization(string src_url, bool color) {

    cv::Mat image = cv::imread(src_url); // Read an image from the location provided and store it in a Mat called image. (OPENCV DOES BGR NOT RGB for channels)


    if (image.empty()) {    // If anything goes wrong, the Mat image will be empty, so we can check for that and then spit out an error message.
        cerr << endl << "ERROR: Could not locate/open image: \'" << src_url << "\'" << endl;
        return -1; // Finally we return out of the Class to allow for the program to end.
    }

    string grayscale = "";
    if (color == false) { // If we don't want color, make it grayscale
        cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
        grayscale = " (Grayscale)";
    }


    cv::Mat hist_equalized_image; // Declare a Mat that will store the output image

    if (color == true) { // We need to do more work if dealing with a color image
        cv::cvtColor(image, hist_equalized_image, cv::COLOR_BGR2YCrCb); // We can't equalize all 3 channels seperately since that would mess with color information and change the color of the BGR image.
                                                                        // Because of this we convert to YCrCb, where Y is the only channel with intensity information, so that channel can be equalized.
        vector<cv::Mat> vec_channels;   // We are going to need to store the 3 channels somewhere, so we make a vector of Mats.
        cv::split(hist_equalized_image, vec_channels); // We will split the image and put each channel into a different Mat in the vector.

        cv::equalizeHist(vec_channels[0], vec_channels[0]); // We need to equalize only the Y channel.

        cv::merge(vec_channels, hist_equalized_image); // Once Equalized, we can merge the layers back together to make one Mat.

        cv::cvtColor(hist_equalized_image, hist_equalized_image, cv::COLOR_YCrCb2BGR); // Then we can convert the Mat back to BGR from YCrCb.
    }
    else {
        cv::equalizeHist(image, hist_equalized_image); // If we are just using grayscale, there is only 1 channel so we don't need to do any extra conversion/splitting/merging.
    }

    string windowNameOG = "Original Image" + grayscale;                                 // All of our new windows need names so we specify them to list how much the image was edited by.
    string windowNameHist = "Histogram Equalized Image";

    cv::namedWindow(windowNameOG, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameHist, cv::WINDOW_NORMAL);

    cv::imshow(windowNameOG, image);
    cv::imshow(windowNameHist, hist_equalized_image);
    // Here we wait for input then kill all of the window processes.
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}


//! This function will apply a homogeneous and a gaussian blur to an image with a kernel size specified by amount.
int ImageFunctions::Blur(string src_url, int amount) {


    cv::Mat image = cv::imread(src_url); // Read an image from the location provided and store it in a Mat called image. (OPENCV DOES BGR NOT RGB for channels)


    if (image.empty()) {    // If anything goes wrong, the Mat image will be empty, so we can check for that and then spit out an error message.
        cerr << endl << "ERROR: Could not locate/open image: \'" << src_url << "\'" << endl;
        return -1; // Finally we return out of the Class to allow for the program to end.
    }

    cv::Mat image_blured_homogeneous, image_blured_gaussian; // Create a Mat to store blurred image
    cv::blur(image, image_blured_homogeneous, cv::Size(amount,amount)); // Perform a homogeneous blur across the whole image of a amount x amount kernel.
    cv::GaussianBlur(image, image_blured_gaussian, cv::Size(amount,amount),0); // Perform a gaussian blur across the whole image of a amount x amount kernel.

    string windowNameBluredHomogeneous = "Image Homogeneous Blured with " + to_string(amount) + " x " + to_string(amount) + " Kernel.";
    string windowNameBluredGaussian = "Image Gaussian Blured with " + to_string(amount) + " x " + to_string(amount) + " Kernel.";

    cv::namedWindow(windowNameBluredHomogeneous, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameBluredGaussian, cv::WINDOW_NORMAL);

    cv::imshow(windowNameBluredHomogeneous, image_blured_homogeneous);
    cv::imshow(windowNameBluredGaussian, image_blured_gaussian);
    // Here we wait for input then kill all of the window processes.
    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

//! This function will apply a homogeneous and a gaussian blur to an image with a 3x3 and 5x5 Kernel size.
int ImageFunctions::Blur3_5(string src_url) {


    cv::Mat image = cv::imread(src_url); // Read an image from the location provided and store it in a Mat called image. (OPENCV DOES BGR NOT RGB for channels)


    if (image.empty()) {    // If anything goes wrong, the Mat image will be empty, so we can check for that and then spit out an error message.
        cerr << endl << "ERROR: Could not locate/open image: \'" << src_url << "\'" << endl;
        return -1; // Finally we return out of the Class to allow for the program to end.
    }

    cv::Mat image_blured_homogeneous3, image_blured_gaussian3,
            image_blured_homogeneous5, image_blured_gaussian5; // Create a Mat to store blurred image

    cv::blur(image, image_blured_homogeneous3, cv::Size(3,3)); // Perform a homogeneous blur across the whole image of a 3 x 3 kernel.
    cv::GaussianBlur(image, image_blured_gaussian3, cv::Size(3,3),0); // Perform a gaussian blur across the whole image of a 3 x 3 kernel.

    cv::blur(image, image_blured_homogeneous5, cv::Size(5,5)); // Perform a homogeneous blur across the whole image of a 5 x 5 kernel.
    cv::GaussianBlur(image, image_blured_gaussian5, cv::Size(5,5),0); // Perform a gaussian blur across the whole image of a 5 x 5 kernel.

    string windowNameBluredHomogeneous3 = "Image Homogeneous Blured with 3 x 3 Kernel.";
    string windowNameBluredGaussian3 = "Image Gaussian Blured with 3 x 3 Kernel.";

    string windowNameBluredHomogeneous5 = "Image Homogeneous Blured with 5 x 5 Kernel.";
    string windowNameBluredGaussian5 = "Image Gaussian Blured with 5 x 5 Kernel.";

                                                                        // 3x3 stuff
    cv::namedWindow(windowNameBluredHomogeneous3, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameBluredGaussian3, cv::WINDOW_NORMAL);

    cv::imshow(windowNameBluredHomogeneous3, image_blured_homogeneous3);
    cv::imshow(windowNameBluredGaussian3, image_blured_gaussian3);
                                                                        // 5x5 stuff
    cv::namedWindow(windowNameBluredHomogeneous5, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameBluredGaussian5, cv::WINDOW_NORMAL);

    cv::imshow(windowNameBluredHomogeneous5, image_blured_homogeneous5);
    cv::imshow(windowNameBluredGaussian5, image_blured_gaussian5);
    // Here we wait for input then kill all of the window processes.
    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

//! This function will Invert a specified image
int ImageFunctions::InvertImage(string src_url){


    cv::Mat image = cv::imread(src_url); // Read an image from the location provided and store it in a Mat called image. (OPENCV DOES BGR NOT RGB for channels)


    if (image.empty()) {    // If anything goes wrong, the Mat image will be empty, so we can check for that and then spit out an error message.
        cerr << endl << "ERROR: Could not locate/open image: \'" << src_url << "\'" << endl;
        return -1; // Finally we return out of the Class to allow for the program to end.
    }

    cv::Mat image_inverted; // Create a Mat to store inverted image
    cv::bitwise_not(image, image_inverted); // Inverting is just 1 line, why is there an entire tutorial on this

    string windowName = "Original Image";
    string windowNameBlured = "Inverted Image";

    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameBlured, cv::WINDOW_NORMAL);

    cv::imshow(windowName, image);
    cv::imshow(windowNameBlured, image_inverted);
    // Here we wait for input then kill all of the window processes.
    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

//! This function will erode an image based on a 3x3 and 5x5 kernel size.
int ImageFunctions::Erode(string src_url, int amount) {


    cv::Mat image = cv::imread(src_url); // Read an image from the location provided and store it in a Mat called image. (OPENCV DOES BGR NOT RGB for channels)


    if (image.empty()) {    // If anything goes wrong, the Mat image will be empty, so we can check for that and then spit out an error message.
        cerr << endl << "ERROR: Could not locate/open image: \'" << src_url << "\'" << endl;
        return -1; // Finally we return out of the Class to allow for the program to end.
    }

    cv::Mat image_eroded; // Create a Mat to store eroded 3x3 image
    cv::erode(image, image_eroded, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(amount,amount))); // Perform an amount x amount erosion to the image.

    string windowName = "Original Image";
    string windowNameEroded = "Image Eroded with " + to_string(amount) + " x " + to_string(amount) + " Kernel.";

    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameEroded, cv::WINDOW_NORMAL);

    cv::imshow(windowName, image);
    cv::imshow(windowNameEroded, image_eroded);

    // Here we wait for input then kill all of the window processes.
    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

//! This function will erode an image based on a 3x3 and 5x5 kernel size.
int ImageFunctions::Erode3_5(string src_url) {


    cv::Mat image = cv::imread(src_url); // Read an image from the location provided and store it in a Mat called image. (OPENCV DOES BGR NOT RGB for channels)


    if (image.empty()) {    // If anything goes wrong, the Mat image will be empty, so we can check for that and then spit out an error message.
        cerr << endl << "ERROR: Could not locate/open image: \'" << src_url << "\'" << endl;
        return -1; // Finally we return out of the Class to allow for the program to end.
    }

    cv::Mat image_eroded3; // Create a Mat to store eroded 3x3 image
    cv::Mat image_eroded5; // Create a Mat to store eroded 5x5 image
    cv::erode(image, image_eroded3, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3))); // Perform an 3 x 3 erosion to the image.
    cv::erode(image, image_eroded5, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5,5))); // Perform an 5 x 5 erosion to the image.

    string windowName = "Original Image";
    string windowNameEroded3 = "Image Eroded with 3 x 3 Kernel.";
    string windowNameEroded5 = "Image Eroded with 5 x 5 Kernel.";

    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameEroded3, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameEroded5, cv::WINDOW_NORMAL);

    cv::imshow(windowName, image);
    cv::imshow(windowNameEroded3, image_eroded3);
    cv::imshow(windowNameEroded5, image_eroded5);

    // Here we wait for input then kill all of the window processes.
    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

//! This function will dilate an image a specific number of times based on the input variable
int ImageFunctions::Dilate(string src_url, int amount) {


    cv::Mat image = cv::imread(src_url); // Read an image from the location provided and store it in a Mat called image. (OPENCV DOES BGR NOT RGB for channels)


    if (image.empty()) {    // If anything goes wrong, the Mat image will be empty, so we can check for that and then spit out an error message.
        cerr << endl << "ERROR: Could not locate/open image: \'" << src_url << "\'" << endl;
        return -1; // Finally we return out of the Class to allow for the program to end.
    }

    cv::Mat image_dilated; // Create a Mat to store dilated image
    cv::dilate(image, image_dilated, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(amount,amount)));

    string windowName = "Original Image";
    string windowNameDilated = "Image Dilated with " + to_string(amount) + " x " + to_string(amount) + " Kernel.";

    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameDilated, cv::WINDOW_NORMAL);

    cv::imshow(windowName, image);
    cv::imshow(windowNameDilated, image_dilated);

    // Here we wait for input then kill all of the window processes.
    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

//! This function will erode an image based on a 3x3 and 5x5 kernel size.
int ImageFunctions::Dilate3_5(string src_url) {


    cv::Mat image = cv::imread(src_url); // Read an image from the location provided and store it in a Mat called image. (OPENCV DOES BGR NOT RGB for channels)


    if (image.empty()) {    // If anything goes wrong, the Mat image will be empty, so we can check for that and then spit out an error message.
        cerr << endl << "ERROR: Could not locate/open image: \'" << src_url << "\'" << endl;
        return -1; // Finally we return out of the Class to allow for the program to end.
    }

    cv::Mat image_dilated3; // Create a Mat to store dilated 3x3 image
    cv::Mat image_dilated5; // Create a Mat to store dilated 5x5 image
    cv::dilate(image, image_dilated3, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3))); // Perform an 3 x 3 dilation to the image.
    cv::dilate(image, image_dilated5, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5,5))); // Perform an 5 x 5 dilation to the image.

    string windowName = "Original Image";
    string windowNameDilated3 = "Image Dilated with 3 x 3 Kernel.";
    string windowNameDilated5 = "Image Dilated with 5 x 5 Kernel.";

    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameDilated3, cv::WINDOW_NORMAL);
    cv::namedWindow(windowNameDilated5, cv::WINDOW_NORMAL);

    cv::imshow(windowName, image);
    cv::imshow(windowNameDilated3, image_dilated3);
    cv::imshow(windowNameDilated5, image_dilated5);

    // Here we wait for input then kill all of the window processes.
    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;
}

int ImageFunctions::TrackbarEdit(string src_url) {

    cv::Mat image = cv::imread(src_url); // Read an image from the location provided and store it in a Mat called image. (OPENCV DOES BGR NOT RGB for channels)


    if (image.empty()) {    // If anything goes wrong, the Mat image will be empty, so we can check for that and then spit out an error message.
        cerr << endl << "ERROR: Could not locate/open image: \'" << src_url << "\'" << endl;
        return -1; // Finally we return out of the Class to allow for the program to end.
    }


    string windowName = "Trackbar Editable Image";

    cv::namedWindow(windowName);
    int SliderVal1 = 50;
    cv::createTrackbar("Brightness", windowName, &SliderVal1, 100);

    int SliderVal2 = 50;
    cv::createTrackbar("Contrast", windowName, &SliderVal2, 100);

    while(true) {
        cv::Mat dest;
        int Brightness = SliderVal1 - 50;
        double Contrast = SliderVal2 / 50.0;
        image.convertTo(dest, -1,Contrast,Brightness);
        cv::imshow(windowName, dest);
        if(cv::waitKey(10) == 'q') { // Wait for the 'q' key for 10 ms. If that key isn't pressed or any other key is pressed, do nothing and continue to next iteration of the loop.
                                    // If 'q' key is pressed, break out of the while loop and end the video.
            cout << "Escape Key pressed. Closing \'" << src_url << "\'" << endl;
            break;
        }
    }

    cv::destroyAllWindows();
    return 0;
}
