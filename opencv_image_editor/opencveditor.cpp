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

void OpenCVEditor::setMedian(bool blur) {
    gaussianBlur = !blur;
    medianBlur = blur;
}

void OpenCVEditor::setGaussian(bool blur) {
    medianBlur = !blur;
    gaussianBlur = blur;
}
