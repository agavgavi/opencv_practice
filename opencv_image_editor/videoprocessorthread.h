#ifndef VIDEOPROCESSORTHREAD_H
#define VIDEOPROCESSORTHREAD_H
#include <QThread>
#include <QPixmap>
#include "opencv4/opencv2/opencv.hpp"

class VideoProcessorThread : public QThread
{
public:
    explicit VideoProcessorThread(QObject *parent = nullptr);

signals:
    void inDisplay(QPixmap pixmap);
    void outDisplay(QPixmap pixmap);
private:
    void run() override;
};

#endif // VIDEOPROCESSORTHREAD_H
