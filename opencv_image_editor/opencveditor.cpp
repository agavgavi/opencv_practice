#include "opencveditor.h"
#include <QDebug>

OpenCVEditor::OpenCVEditor()
{

}

cv::Mat OpenCVEditor::adjustImage(cv::Mat inFrame) {

    cv::Mat outFrame;
    int editBrightness = brightness - 50;
    double editContrast = contrast / 50.0;
    qDebug() << "Brightness:" << editBrightness;
    qDebug() << "Contrast:" << editContrast;
    qDebug() << "Median:" << medianBlur;
    qDebug() << "Gaussian:" << gaussianBlur;

    if(medianBlur) {
        cv::medianBlur(inFrame, outFrame, 5);
    }

    else if(gaussianBlur) {
        cv::GaussianBlur(inFrame, outFrame,
                         cv::Size(5, 5), 1.25);
    }
    outFrame.convertTo(outFrame, -1, editContrast, editBrightness);

    return outFrame;
}

cv::Mat OpenCVEditor::detectAndDisplay(cv::Mat inFrame, cv::CascadeClassifier detect_cascade){
    cv::Mat outFrame(inFrame);
    cv::Mat frame_gray;
    cv::cvtColor( inFrame, frame_gray, cv::COLOR_BGR2GRAY );
    cv::equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    std::vector<cv::Rect> faces;
    detect_cascade.detectMultiScale( frame_gray, faces );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        cv::Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        cv::ellipse( outFrame, center, cv::Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, cv::Scalar( 255, 0, 255 ), 4 );
    }
    //-- Show what you got
    return outFrame;
}


void OpenCVEditor::setMedian(bool blur) {
    gaussianBlur = !blur;
    medianBlur = blur;
}

void OpenCVEditor::setGaussian(bool blur) {
    medianBlur = !blur;
    gaussianBlur = blur;
}
