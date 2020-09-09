#include "cascadetest.h"
#include "opencv4/opencv2/objdetect.hpp"
#include "opencv4/opencv2/highgui.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/videoio.hpp"
#include <iostream>

using namespace std;

void detectAndDisplay( cv::Mat frame);

cv::CascadeClassifier face_cascade;
CascadeTest::CascadeTest(int argc, char *argv[])
{
    cv::CommandLineParser parser(argc, argv,
                                 "{help h||}"
                                 "{face_cascade|../cascades/haarcascade_frontalface_alt.xml|Path to face cascade.}"
                                 "{camera|0|Camera device number.}");
    parser.about( "\nThis program demonstrates using the cv::CascadeClassifier class to detect objects (Face + eyes) in a video stream.\n"
                  "You can use Haar or LBP features.\n\n" );
    parser.printMessage();

    cv::String face_cascade_name =  parser.get<cv::String>("face_cascade");
    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) )
    {
        cout << "--(!)Error loading face cascade\n";
        return;
    };
    int camera_device = parser.get<int>("camera");
    cv::VideoCapture capture;
    //-- 2. Read the video stream
    capture.open( camera_device );
    capture.set(cv::CAP_PROP_FPS, 30);
    if ( ! capture.isOpened() )
    {
        cout << "--(!)Error opening video capture\n";
        return ;
    }
    cv::Mat frame;
    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            cout << "--(!) No captured frame -- Break!\n";
            break;
        }
        //-- 3. Apply the classifier to the frame
        detectAndDisplay( frame );
        if( cv::waitKey(10) == 'q' )
        {
            break; // escape
        }
    }
}
void detectAndDisplay( cv::Mat frame )
{
    cv::Mat frame_gray;
    cv::cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    cv::equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale( frame_gray, faces );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        cv::Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        cv::ellipse( frame, center, cv::Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, cv::Scalar( 255, 0, 255 ), 4 );
    }
    //-- Show what you got
    cv::imshow( "Capture - Face detection", frame );
}
