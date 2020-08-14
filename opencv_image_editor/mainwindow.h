#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videoprocessor.h"
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_inputPushButton_pressed();

    void on_outputPushButton_pressed();

    void on_savePushButton_pressed();

    void on_brightnessHorizontalSlider_sliderMoved(int position);

    void on_contrastHorizontalSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    void loadSettings();
    void saveSettings();
    VideoProcessor *processor;

protected:
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
