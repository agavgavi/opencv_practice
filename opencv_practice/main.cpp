#include "mainwindow.h"
#include "ImageFuncs.h"
#include "VideoFuncs.h"

#include <QApplication>

int main(/*int argc, char *argv[]*/)
{

    ImageFunctions img; // Class for all Image tutorials
    VideoFunctions vid; // Class for all Video Tutorials
    int status = 0;

    status = img.LoadImage("../images/eagle.png", "My First OpenCV Program"); // Load image from disk and display.

    if(status == -1) {
        return -1;
    }

    status = img.CreateImage("Window with Blank Green Image", 100, 250, 30);   // Display a new fresh window with the BGR colors passed in.

    if(status == -1) {
        return -1;
    }

    status = vid.PlayVideo("../videos/smoke_vid.mov", "Displaying Smoke Video");   // Show a video file.

    if(status == -1) {
        return -1;
    }

    status = vid.ShowCamera(0, "Display Webcam");   // Display webcam capture.

    if(status == -1) {
        return -1;
    }

    return 0;



// QT WORK NOT NEEDED YET.
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
