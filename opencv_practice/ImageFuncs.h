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
};

#endif // IMAGEFUNCS_H
