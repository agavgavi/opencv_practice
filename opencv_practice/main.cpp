#include "mainwindow.h"
#include "helloworld.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    HelloWorld hw("../images/eagle.png", "My First OpenCV Program");

    return 0;



// QT WORK NOT NEEDED YET.
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
