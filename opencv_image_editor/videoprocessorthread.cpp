#include "videoprocessorthread.h"
#include <QPixmap>
#include <QImage>

VideoProcessorThread::VideoProcessorThread(QObject *parent) : QThread(parent)
{

}

void VideoProcessorThread::run() {
   cv::VideoCapture camera(0);
   cv::Mat inFrame, outFrame;
   while(camera.isOpened() && !isInterruptionRequested()) {
       camera >> inFrame;

       if(inFrame.empty())
               continue;
        cv::bitwise_not(inFrame, outFrame);
        emit inDisplay(QPixmap::fromImage(
                           QImage(
                               inFrame.data,
                               inFrame.cols,
                               inFrame.rows,
                               inFrame.step,
                               QImage::Format_RGB888).rgbSwapped()));

        emit outDisplay(QPixmap::fromImage(
                            QImage(
                                outFrame.data,
                                outFrame.cols,
                                outFrame.rows,
                                outFrame.step,
                                QImage::Format_RGB888).rgbSwapped()));
   }
}
