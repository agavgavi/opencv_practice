#ifndef OPENCVEDITOR_H
#define OPENCVEDITOR_H

#include <opencv4/opencv2/opencv.hpp>
class OpenCVEditor
{
private:
    int brightness;
    int contrast;
    bool gaussianBlur = false;
    bool medianBlur = true;
public:
    OpenCVEditor();
    cv::Mat adjustImage(cv::Mat inFrame);
    void setBrightness(int bright) { brightness = bright; }
    void setContrast(int cont) { contrast = cont; }
    void setGaussian(bool blur);
    void setMedian(bool blur);
};

#endif // OPENCVEDITOR_H
