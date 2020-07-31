#include "VideoFuncs.h"
#include <opencv4/opencv2/opencv.hpp>

VideoFunctions::VideoFunctions()
{

}


// This function will take in a URL for a video and the name of the window you want to display it in, open the video,
// display the FPS, and then when the video is done or the user presses 'q' the video will close.
int VideoFunctions::PlayVideo(string video_url, string windowName) {

    cv::VideoCapture cap(video_url); // Create a video capture object from the video url.

    if(cap.isOpened() == false) { // Similar check to working with images (image.empty()), only difference is if there is an error, cap.isOpened will be false.
        cerr << endl << "ERROR: Cannot open video file: \'" << video_url << "\'" << endl;
        return -1;
    }

    double fps = cap.get(cv::CAP_PROP_FPS); // Store the FPS of the video into a variable.
    cout << "Frames Per Second of \'" << video_url << "\': " << fps << endl; // And then prints it out.

    double width = cap.get(cv::CAP_PROP_FRAME_WIDTH); // Store width and height of video into variables.
    double height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    cout << "Size of \'" << video_url << "\' wxh: " << width << " x " <<height << endl; // And then prints it out.


    cv::namedWindow(windowName, cv::WINDOW_NORMAL); // User can make the window larger now since we use WINDOW_NORMAL as a flag instead of WINDOW_AUTOSIZE

    while(true) { // Run infinitely to display video. When the video is ended or a user presses something the while loop will end.

        cv::Mat frame; // Create a Mat to store a specific frame.
        bool fSuccess = cap.read(frame); // Push the frame from the video capture device to frame. If it worked, fSuccess will be true.

        if (fSuccess == false) { // When it is false, the video is over so the while loop can be broken out of.
            cout << "Finished \'" << video_url << "\'" << endl;
            break;
        }

        cv::imshow(windowName, frame); // Show the specific frame in a named window.

        if(cv::waitKey(10) == 'q') { // Wait for the 'q' key for 10 ms. If that key isn't pressed or any other key is pressed, do nothing and continue to next iteration of the loop.
                                    // If 'q' key is pressed, break out of the while loop and end the video.
            cout << "Escape Key pressed. Closing \'" << video_url << "\'" << endl;
            break;
        }
    }
    cv::destroyWindow(windowName);  // After the key is pressed we destroy the window we created earlier.
    return 0;
}

int VideoFunctions::ShowCamera(int camera_device, string windowName) {

    cv::VideoCapture cap(camera_device); // Create a video capture object from the camera int.

    if(cap.isOpened() == false) { // Similar check to working with images (image.empty()), only difference is if there is an error, cap.isOpened will be false.
        cerr << endl << "ERROR: Cannot open video camera" << endl;
        return -1;
    }
    cap.set(cv::CAP_PROP_FPS, 30);
    double fps = cap.get(cv::CAP_PROP_FPS); // Store the FPS of the camera into a variable.

    cout << "Frames Per Second of camera : " << fps << endl; // And then prints it out.

    double width = cap.get(cv::CAP_PROP_FRAME_WIDTH); // Store width and height of camera into variables.
    double height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    cout << "Resolution of camera: " << width << " x " <<height << endl; // And then prints it out.


    cv::namedWindow(windowName, cv::WINDOW_NORMAL); // User can make the window larger now since we use WINDOW_NORMAL as a flag instead of WINDOW_AUTOSIZE

    while(true) { // Run infinitely to display camera. When the camera is closed or a user presses something the while loop will end.

        cv::Mat frame; // Create a Mat to store a specific frame.
        bool fSuccess = cap.read(frame); // Push the frame from the video capture device to frame. If it worked, fSuccess will be true.

        if (fSuccess == false) { // When it is false, the camera capture is ended so the while loop can be broken out of.
            cout << "Video camera is now gone" << endl;
            break;
        }

        cv::imshow(windowName, frame); // Show the specific frame in a named window.

        if(cv::waitKey(10) == 'q') { // Wait for the 'q' key for 10 ms. If that key isn't pressed or any other key is pressed, do nothing and continue to next iteration of the loop.
                                    // If 'q' is pressed, break out of the while loop and end the camera capture.
            cout << "Escape Key pressed. Closing video camera" << endl;
            break;
        }
    }
    cv::destroyWindow(windowName);  // After the key is pressed we destroy the window we created earlier.
    return 0;
}

// A function that will save the recording of the camera until the user presses the 'q' key
int VideoFunctions::SaveVideo(int camera_device, string dest_url) {

    cv::VideoCapture cap(camera_device); // Create a video capture object from the camera int.

    if(cap.isOpened() == false) { // Similar check to working with images (image.empty()), only difference is if there is an error, cap.isOpened will be false.
        cerr << endl << "ERROR: Cannot open video camera" << endl;
        return -1;
    }
    int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT)); // get the width and height of the webcam
    int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));

    cv::Size frame_size(frame_width,frame_height);
    int fps = 10; // Limit our fps to a simple 10

    cv::VideoWriter objVideoWriter(dest_url, cv::VideoWriter::fourcc('m','p','4','v'),
                                   fps, frame_size, true); // Object used to write to disk.

    if(objVideoWriter.isOpened() == false) { // Check if the VideoWriter object couldn't be opened or started.
        cerr << endl << "ERROR: Cannot save video to a file" << endl;
        return -1;
    }

    string windowName = "Saved video";
    cv::namedWindow(windowName); // User can make the window larger now since we use WINDOW_NORMAL as a flag instead of WINDOW_AUTOSIZE

    while(true) { // Run infinitely to display camera. When the camera is closed or a user presses something the while loop will end.

        cv::Mat frame; // Create a Mat to store a specific frame.
        bool fSuccess = cap.read(frame); // Push the frame from the video capture device to frame. If it worked, fSuccess will be true.

        if (fSuccess == false) { // When it is false, the camera capture is ended so the while loop can be broken out of.
            cout << "Video camera is now gone" << endl;
            break;
        }

        // DO video adjustments here before saving frame to disk.

        objVideoWriter.write(frame); // save video frame to file.

        cv::imshow(windowName, frame); // Show the specific frame in a named window.

        if(cv::waitKey(10) == 'q') { // Wait for the 'q' key for 10 ms. If that key isn't pressed or any other key is pressed, do nothing and continue to next iteration of the loop.
                                    // If 'q' is pressed, break out of the while loop and end the camera capture.
            cout << "Escape Key pressed. Closing video camera" << endl;
            break;
        }
    }

    objVideoWriter.release(); // Finish the writing and close the file.
    cout << "Finished writing to file, thank you!" << endl;

    cv::destroyWindow(windowName);  // After the key is pressed we destroy the window we created earlier.
    return 0;
}

// Edit brightness on a saved video by a specified amount. Similar to ImageFunctions::EditBrightness except with video.
int VideoFunctions::EditBrightness(string video_url, int amount) {
    cv::VideoCapture cap(video_url); // Create a video capture object from the video url.

    if(cap.isOpened() == false) { // Similar check to working with images (image.empty()), only difference is if there is an error, cap.isOpened will be false.
        cerr << endl << "ERROR: Cannot open video file: \'" << video_url << "\'" << endl;
        return -1;
    }

    double fps = cap.get(cv::CAP_PROP_FPS); // Store the FPS of the video into a variable.
    cout << "Frames Per Second of \'" << video_url << "\': " << fps << endl; // And then prints it out.

    double width = cap.get(cv::CAP_PROP_FRAME_WIDTH); // Store width and height of video into variables.
    double height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    cout << "Size of \'" << video_url << "\' wxh: " << width << " x " <<height << endl; // And then prints it out.

    string windowNameOG = "Original Video";                                 // All of our new windows need names so we specify them to list how much the video was edited by.
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

    while(true) { // Run infinitely to display video. When the video is ended or a user presses something the while loop will end.

        cv::Mat frame; // Create a Mat to store a specific frame.
        bool fSuccess = cap.read(frame); // Push the frame from the video capture device to frame. If it worked, fSuccess will be true.

        if (fSuccess == false) { // When it is false, the video is over so the while loop can be broken out of.
            cout << "Finished \'" << video_url << "\'" << endl;
            break;
        }

        cv::Mat imageBrightnessHigh1, imageBrightnessHigh2, imageBrightnessLow1, imageBrightnessLow2; // Create 4 mats for the 4 steps of brightness we are editing.

        frame.convertTo(imageBrightnessHigh1,-1, 1, amount); // Converts the brightness of the video frame for all 4 mats and saved it to an output Mat.
        frame.convertTo(imageBrightnessHigh2,-1, 1, amount*2);
        frame.convertTo(imageBrightnessLow1,-1, 1, -amount);
        frame.convertTo(imageBrightnessLow2,-1, 1, -amount*2);

        // Then we actually display all the named windows with the specific mats that correspond to them.
        cv::imshow(windowNameOG, frame);
        cv::imshow(windowNameHigh1, imageBrightnessHigh1);
        cv::imshow(windowNameHigh2, imageBrightnessHigh2);
        cv::imshow(windowNameLow1, imageBrightnessLow1);
        cv::imshow(windowNameLow2, imageBrightnessLow2);

        if(cv::waitKey(10) == 'q') { // Wait for the 'q' key for 10 ms. If that key isn't pressed or any other key is pressed, do nothing and continue to next iteration of the loop.
                                    // If 'q' key is pressed, break out of the while loop and end the video.
            cout << "Escape Key pressed. Closing \'" << video_url << "\'" << endl;
            break;
        }
    }
    cv::destroyAllWindows();  // After the key is pressed we destroy all video windows created
    return 0;
}

// Edit contrast on a saved video by a specified amount. Similar to ImageFunctions::EditContrast except with video.
int VideoFunctions::EditContrast(string video_url, int amount) {
    cv::VideoCapture cap(video_url); // Create a video capture object from the video url.

    if(cap.isOpened() == false) { // Similar check to working with images (image.empty()), only difference is if there is an error, cap.isOpened will be false.
        cerr << endl << "ERROR: Cannot open video file: \'" << video_url << "\'" << endl;
        return -1;
    }

    double fps = cap.get(cv::CAP_PROP_FPS); // Store the FPS of the video into a variable.
    cout << "Frames Per Second of \'" << video_url << "\': " << fps << endl; // And then prints it out.

    double width = cap.get(cv::CAP_PROP_FRAME_WIDTH); // Store width and height of video into variables.
    double height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    cout << "Size of \'" << video_url << "\' wxh: " << width << " x " <<height << endl; // And then prints it out.

    string windowNameOG = "Original Video";                                 // All of our new windows need names so we specify them to list how much the video was edited by.
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

    while(true) { // Run infinitely to display video. When the video is ended or a user presses something the while loop will end.

        cv::Mat frame; // Create a Mat to store a specific frame.
        bool fSuccess = cap.read(frame); // Push the frame from the video capture device to frame. If it worked, fSuccess will be true.

        if (fSuccess == false) { // When it is false, the video is over so the while loop can be broken out of.
            cout << "Finished \'" << video_url << "\'" << endl;
            break;
        }

        cv::Mat imageContrastHigh1, imageContrastHigh2, imageContrastLow1, imageContrastLow2; // Create 4 mats for the 4 steps of brightness we are editing.

        frame.convertTo(imageContrastHigh1,-1, amount, 0); // Converts the contrast of the image for all 4 mats and saved it to an output Mat.
        frame.convertTo(imageContrastHigh2,-1, amount*2, 0);
        frame.convertTo(imageContrastLow1,-1, (double) 1/amount, 0);
        frame.convertTo(imageContrastLow2,-1, (double) 1/(amount*2), 0);

        // Then we actually display all the named windows with the specific mats that correspond to them.
        cv::imshow(windowNameOG, frame);
        cv::imshow(windowNameHigh1, imageContrastHigh1);
        cv::imshow(windowNameHigh2, imageContrastHigh2);
        cv::imshow(windowNameLow1, imageContrastLow1);
        cv::imshow(windowNameLow2, imageContrastLow2);

        if(cv::waitKey(10) == 'q') { // Wait for the 'q' key for 10 ms. If that key isn't pressed or any other key is pressed, do nothing and continue to next iteration of the loop.
                                    // If 'q' key is pressed, break out of the while loop and end the video.
            cout << "Escape Key pressed. Closing \'" << video_url << "\'" << endl;
            break;
        }
    }
    cv::destroyAllWindows();  // After the key is pressed we destroy all video windows created
    return 0;
}
