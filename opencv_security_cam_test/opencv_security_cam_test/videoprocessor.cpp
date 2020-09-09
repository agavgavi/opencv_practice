#include "videoprocessor.h"


VideoProcessor::VideoProcessor(QObject *parent) : QObject(parent)
{

}

void VideoProcessor::startVideo() {
    cv::CascadeClassifier face_cascade;
    if( !face_cascade.load( "../../cascades/haarcascade_frontalface_alt.xml" ) )
    {
        std::cout << "--(!)Error loading face cascade\n";
        return;
    };
    cv::VideoCapture camera(0);
    cv::Mat inFrame, outFrame;
    stopped = false;
    camera.set(cv::CAP_PROP_FPS, 30);


    while(camera.isOpened() && !stopped) {
        camera >> inFrame;
        if(inFrame.empty())
            continue;

        //outFrame = editor.detectAndDisplay(inFrame, face_cascade);
        //outFrame = editor.adjustImage(inFrame);
        outFrame = inFrame;

        emit inDisplay(QPixmap::fromImage(
                           QImage(inFrame.data,
                                  inFrame.cols,
                                  inFrame.rows,
                                  inFrame.step,
                                  QImage::Format_RGB888)
                                    .rgbSwapped()));

        emit outDisplay(QPixmap::fromImage(
                           QImage(outFrame.data,
                                  outFrame.cols,
                                  outFrame.rows,
                                  outFrame.step,
                                  QImage::Format_RGB888)
                                    .rgbSwapped()));
    }
}

void VideoProcessor::stopVideo() {
    stopped = true;
}
