#include "opencvrecognition.h"

OpenCVRecognition::OpenCVRecognition()
{

}

cv::Mat OpenCVRecognition::DetectAndDisplay(cv::Mat frame, cv::CascadeClassifier face_cascade) {
    cv::Mat outFrame = frame.clone();
    cv::Mat frame_gray;
    cv::cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    cv::equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale( frame_gray, faces );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        cv::Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        cv::Mat admin = cv::imread("../../images/eagle.png", cv::IMREAD_UNCHANGED);
        cv::Mat mask;
        std::vector<cv::Mat> rgbLayer;
        cv::split(admin, rgbLayer);
        if(admin.channels() == 4) {
            std::cout << "Hi" << admin.channels() << std::endl;
            cv::split(admin,rgbLayer);         // seperate channels
            cv::Mat cs[3] = { rgbLayer[0],rgbLayer[1],rgbLayer[2] };
            cv::merge(cs,3,admin);  // glue together again
            mask = rgbLayer[3];       // png's alpha channel used as mask
        }

        cv::resize(admin, admin, cv::Size(faces[i].width, faces[i].height));
        cv::resize(mask, mask, cv::Size(faces[i].width, faces[i].height));

        admin.copyTo(outFrame(faces[i]), mask);
        std::cout << outFrame.channels() << std::endl;
    }
    //-- Show what you got
    return outFrame;
}
