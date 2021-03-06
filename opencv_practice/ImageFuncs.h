#ifndef IMAGEFUNCS_H
#define IMAGEFUNCS_H


#include <iostream>
using namespace std;
class ImageFunctions
{
private:
public:
    ImageFunctions();
    int LoadImage(string image_name, string windowName);
    int CreateImage(string windowName, int blue, int green, int red);
    int CopyImage(string src_url, string dest_url);
    int EditBrightness(string src_url, int amount);
    int EditContrast(string src_url, int amount);
    int HistEqualization(string src_url, bool color);
    int Blur(string src_url, int amount);
    int Blur3_5(string src_url);
    int Erode(string src_url, int amount);
    int Erode3_5(string src_url);
    int Dilate(string src_url, int amount);
    int Dilate3_5(string src_url);
    int InvertImage(string src_url);
    int TrackbarEdit(string src_url);
};

#endif // IMAGEFUNCS_H
