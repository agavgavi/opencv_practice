#include "videoprocessorthread.h"
#include <QImage>

VideoProcessorThread::VideoProcessorThread(QObject *parent) : QThread(parent)
{

}

void VideoProcessorThread::run() {
   cv::VideoCapture camera(0); // Open a camera Capture
   cv::Mat inFrame, outFrame; // Create some Mats for what we will do to it.
   while(camera.isOpened() && !isInterruptionRequested()) { // Run while camera is open and the thread hasn't had an interrupts created
       camera >> inFrame; // Push the camera to the Mat

       if(inFrame.empty())
               continue; // If the mat is empty just continue the loop

        cv::bitwise_not(inFrame, outFrame); // We are going to bitwise not the video just for now, later on we will do other image recognition stuff.

        emit VideoProcessorThread::inDisplay(QPixmap::fromImage(QImage(inFrame.data,inFrame.cols,inFrame.rows,inFrame.step,QImage::Format_RGB888).rgbSwapped())); // emit an inDisplay signal using a QPixmap we made from the mat of the OG image

        emit VideoProcessorThread::outDisplay(QPixmap::fromImage(
                            QImage(
                                outFrame.data,
                                outFrame.cols,
                                outFrame.rows,
                                outFrame.step,
                                QImage::Format_RGB888).rgbSwapped())); // emit an outDisplay signal using a QPixmap we made from the mat of the edited video
   }
}
