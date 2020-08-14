#include "videoprocessor.h"


VideoProcessor::VideoProcessor(QObject *parent) : QObject(parent)
{

}

void VideoProcessor::startVideo() {
    cv::VideoCapture camera(0);
    cv::Mat inFrame, outFrame;
    stopped = false;
    camera.set(cv::CAP_PROP_FPS, 30);
    OpenCVEditor editor;

    while(camera.isOpened() && !stopped) {
        camera >> inFrame;
        if(inFrame.empty())
            continue;

        outFrame = editor.adjustImage(inFrame);

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
