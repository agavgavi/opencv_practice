#include "videoprocessor.h"
#include "chrono"


VideoProcessor::VideoProcessor(QObject *parent, std::string option_) : QObject(parent), option(option_)
{
}

void VideoProcessor::startVideo() {
    cv::CascadeClassifier face_cascade;
    std::cout << "------------------------------------------------" << std::endl << "------------------------------------------------" << std::endl;

    if(option == "lbp_front") {
        url = "../../cascades/lbp_front.xml";
        folder = "lbp_front";
    }
    else if (option == "lbp_front_improved") {
        url = "../../cascades/lbp_front_improved.xml";
        folder = "lbp_front_improved";
    }
    else if (option == "haar_front_alt") {
        url = "../../cascades/haar_front_alt.xml";
        folder = "haar_front_alt";
    }
    else if (option == "haar_front_alt2") {
        url = "../../cascades/haar_front_alt2.xml";
        folder = "haar_front_alt2";
    }
    else if (option == "haar_front_default") {
        url = "../../cascades/haar_front_default.xml";
        folder = "haar_front_default";
    }
    else if (option == "haar_front_tree") {
        url = "../../cascades/haar_front_tree.xml";
        folder = "haar_front_tree";
    } else {
        url = "../../cascades/lbp_front.xml";
        folder = "lbp_front";
    }

    std::cout << url << std::endl;
    if( !face_cascade.load(url ) )
    {
        std::cout << "--(!)Error loading face cascade\n";
        return;
    };
    cv::VideoCapture camera("../../videos/Test2.mp4");
    cv::Mat inFrame, outFrame;
    stopped = false;
    //camera.set(cv::CAP_PROP_FPS, 30);
    OpenCVRecognition openCV(folder);

    while(camera.isOpened() && !stopped) {
        bool done = camera.read(inFrame);
        if (!done) {
            break;
        }
        if(inFrame.empty())
            continue;

        cv::resize(inFrame, inFrame,cv::Size(640,480), 0, 0, cv::INTER_CUBIC);
        outFrame = openCV.DetectAndDisplay(inFrame, face_cascade);


        emit outDisplay(QPixmap::fromImage(
                           QImage(outFrame.data,
                                  outFrame.cols,
                                  outFrame.rows,
                                  outFrame.step,
                                  QImage::Format_RGB888)
                                    .rgbSwapped()));
    }
    std::cout << "------------------------------------------------" << std::endl << "------------------------------------------------" << std::endl;
    camera.release();
    stopped = true;
    emit quitProgram();
}

void VideoProcessor::stopVideo() {
    stopped = true;
}
