#include "mainwindow.h"
#include "ImageFuncs.h"
#include "VideoFuncs.h"

#include <QApplication>

// Dedicated function for all image manipulation tasks.
int image_funcs(ImageFunctions& img) {
    int status = 0;
    status = img.LoadImage("../images/eagle.png", "My First OpenCV Program"); // Load image from disk and display.

    if(status == -1) {
        return -1;
    }

    status = img.CreateImage("Window with Blank Green Image", 100, 250, 30);   // Display a new fresh window with the BGR colors passed in.

    if(status == -1) {
        return -1;
    }

//    status = img.CopyImage("../images/eagle.png", "../images/newEagle.png"); // Load image from disk and save it under a new name.

//    if(status == -1) {
//        return -1;
//    }

    status = img.EditBrightness("../images/eagle.png", 50); // Adjust brightness of image by +- 50 and +-100

    if(status == -1) {
        return -1;
    }

    status = img.EditContrast("../images/eagle.png", 2); // Adjust contrast of image by 2, 4, 1/2, 1/4

    if(status == -1) {
        return -1;
    }

    status = img.HistEqualization("../images/mountains.jpg", true); // Perform a Histogram Equalization on the image in color.

    if(status == -1) {
        return -1;
    }

    status = img.HistEqualization("../images/mountains.jpg", false); // Perform a Histogram Equalization on the image in grayscale.

    if(status == -1) {
        return -1;
    }

    status = img.BlurHomogeneous("../images/mountains.jpg", 3); // Perform a Homogeneous Blur with 3 x 3 Kernel

    if(status == -1) {
        return -1;
    }

    status = img.BlurHomogeneous("../images/mountains.jpg", 5); // Perform a Homogeneous Blur with 5 x 5 Kernel

    if(status == -1) {
        return -1;
    }

    status = img.BlurGaussian("../images/mountains.jpg", 3); // Perform a Gaussian Blur with 3 x 3 Kernel

    if(status == -1) {
        return -1;
    }

    status = img.BlurGaussian("../images/mountains.jpg", 5); // Perform a Gaussian Blur with 5 x 5 Kernel

    if(status == -1) {
        return -1;
    }
    return 0;
}

// Dedicated function for all image manipulation tasks.
int video_funcs(VideoFunctions& vid) {
    int status = 0;

    status = vid.PlayVideo("../videos/lights_vid.mov", "Displaying Lights Video");   // Show a video file.

    if(status == -1) {
        return -1;
    }

    status = vid.EditBrightness("../videos/lights_vid.mov", 50); // Adjust brightness of video by +- 50 and +-100

    if(status == -1) {
        return -1;
    }

    status = vid.EditContrast("../videos/lights_vid.mov", 2); // Adjust contrast by 2, 4, 1/2, and 1/4

    if(status == -1) {
        return -1;
    }

    status = vid.HistEqualization("../videos/lights_vid.mov", true); // Perform a Histogram Equalization on the video in color.

    if(status == -1) {
        return -1;
    }

    status = vid.HistEqualization("../videos/lights_vid.mov", false); // Perform a Histogram Equalization on the video in grayscale.

    if(status == -1) {
        return -1;
    }

    status = vid.BlurHomogeneous("../videos/lights_vid.mov", 3); // Perform a Homogeneous Blur with 3 x 3 Kernel

    if(status == -1) {
        return -1;
    }

    status = vid.BlurHomogeneous("../videos/lights_vid.mov", 5); // Perform a Homogeneous Blur with 5 x 5 Kernel

    if(status == -1) {
        return -1;
    }

    status = vid.BlurGaussian("../videos/lights_vid.mov", 3); // Perform a Gaussian Blur with 3 x 3 Kernel

    if(status == -1) {
        return -1;
    }

    status = vid.BlurGaussian("../videos/lights_vid.mov", 5); // Perform a Gaussian Blur with 5 x 5 Kernel

    if(status == -1) {
        return -1;
    }

    status = vid.ShowCamera(0, "Display Webcam");   // Display webcam capture.

    if(status == -1) {
        return -1;
    }

//    status = vid.SaveVideo(0, "../videos/savedCam.mp4");   // Display webcam capture and save it

//    if(status == -1) {
//        return -1;
//    }



    return 0;
}

int main(/*int argc, char *argv[]*/)
{

    ImageFunctions img; // Class for all Image tutorials
    VideoFunctions vid; // Class for all Video Tutorials
    int status = 0;

    status = image_funcs(img); // Do all image functions

    if(status == -1) {
        return -1;
    }

    cout << endl << "Finished Image Manipulation Functions" << endl << endl;

    status = video_funcs(vid); // do all video functions

    if(status == -1) {
        return -1;
    }

    cout << endl << "Finished Video Manipulation Functions" << endl << endl;

    return 0;



// QT WORK NOT NEEDED YET.
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
