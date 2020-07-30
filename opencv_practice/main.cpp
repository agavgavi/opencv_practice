#include "mainwindow.h"
#include "tutorial1.h"

#include <QApplication>

int main(/*int argc, char *argv[]*/)
{

    Tutorial1 tut;

    tut.LoadImage("../images/eagle.png", "My First OpenCV Program"); // Load image from disk and display.

    tut.CreateImage("Window with Blank Green Image", 100, 250, 30);   // Display a new fresh window with the BGR colors passed in.

    return 0;



// QT WORK NOT NEEDED YET.
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
