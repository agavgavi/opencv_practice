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
    int CopyImage(string image_name);
};

#endif // IMAGEFUNCS_H
