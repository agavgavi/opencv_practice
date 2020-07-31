#ifndef VIDEOFUNCTIONS_H
#define VIDEOFUNCTIONS_H


#include <iostream>
using namespace std;
class VideoFunctions
{
public:
    VideoFunctions();
    int PlayVideo(string video_url, string windowName);
    int ShowCamera(int camera_device, string windowName);
};

#endif // VIDEOFUNCTIONS_H
