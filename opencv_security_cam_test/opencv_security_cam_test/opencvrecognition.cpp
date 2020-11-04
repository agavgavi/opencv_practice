#include "opencvrecognition.h"

OpenCVRecognition::OpenCVRecognition(std::string folder_) : folder(folder_)
{

}

cv::Mat OpenCVRecognition::DetectAndDisplay(cv::Mat frame, cv::CascadeClassifier face_cascade) {
    cv::Mat outFrame = frame.clone();
    cv::Mat frame_gray;
    cv::cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    cv::equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    std::vector<cv::Rect> faces;
    bool res;
    face_cascade.detectMultiScale( frame_gray, faces);
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        cv::Mat admin = cv::imread("../../images/Admin.png", cv::IMREAD_UNCHANGED); // Open Overlayed image
        cv::Mat mask = getAlphaLevel(admin);
        std::string outputURL = "../../output/" + folder + "/" + std::to_string(imCount++) + ".png";


        cv::resize(admin, admin, cv::Size(faces[i].width, faces[i].height));

        cv::resize(mask, mask, cv::Size(faces[i].width, faces[i].height));

        admin.copyTo(outFrame(faces[i]), mask);
        res = saveImage(outputURL, outFrame(faces[i]));
        if(res == false) {
            std::cout << "There was an error saving " + outputURL << std::endl;
        }
    }
    //-- Show what you got
    return outFrame;
}

cv::Mat OpenCVRecognition::getAlphaLevel(cv::Mat& input) {
    cv::Mat mask;
    std::vector<cv::Mat> rgbLayer;
    cv::split(input, rgbLayer);
    if(input.channels() == 4) {
        cv::split(input,rgbLayer);         // seperate channels
        cv::Mat cs[3] = { rgbLayer[0],rgbLayer[1],rgbLayer[2] };
        cv::merge(cs,3,input);  // glue together again
        mask = rgbLayer[3];       // png's alpha channel used as mask
    }
    return mask;
}

bool OpenCVRecognition::saveImage(std::string dest_url, cv::Mat output) {
    bool res = cv::imwrite(dest_url,output);
    return res;
}
