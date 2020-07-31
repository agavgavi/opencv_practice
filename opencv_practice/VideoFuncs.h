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
    int SaveVideo(int camera_device, string dest_url);
    int EditBrightness(string video_url, int amount);
    int EditContrast(string src_url, int amount);
};

#endif // VIDEOFUNCTIONS_H
