#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videoprocessor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, int argc = 0, char *argv[] = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    VideoProcessor *processor;
    std::string option;
};
#endif // MAINWINDOW_H
