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
        cout << "Cannot open video file: \'" << video_url << "\'" << endl;
        cin.get();
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
        cout << "Cannot open video camera" << endl;
        cin.get();
        return -1;
    }
    cap.set(cv::CAP_PROP_FPS, 24);
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
