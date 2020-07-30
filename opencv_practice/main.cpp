#include "mainwindow.h"
#include "tutorial1.h"

#include <QApplication>

int main(/*int argc, char *argv[]*/)
{

    Tutorial1 tut;

    tut.LoadImage("../images/eagle.png", "My First OpenCV Program"); // Load image from disk and display.
    tut.CreateImage("Window with Blank Image");

    return 0;



// QT WORK NOT NEEDED YET.
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
