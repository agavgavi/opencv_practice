#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <QObject>
#include <QPixmap>
#include <opencv4/opencv2/opencv.hpp>
#include "opencvrecognition.h"
class VideoProcessor : public QObject
{
    Q_OBJECT
public:
    explicit VideoProcessor(QObject *parent = nullptr, std::string option = "lbp_front");

signals:
    void outDisplay(QPixmap pixmap);
    void quitProgram();

public slots:
    void startVideo();
    void stopVideo();
private:
    bool stopped;
    std::string option;
    std::string url;
    std::string folder;
};

#endif // VIDEOPROCESSOR_H
