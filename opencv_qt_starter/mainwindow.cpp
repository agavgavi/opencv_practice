#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    processor = new VideoProcessor();
    processor->moveToThread(new QThread(this));

    connect(processor->thread(),
        &QThread::started,
        processor,
        &VideoProcessor::startVideo);

    connect(processor->thread(),
        &QThread::finished,
        processor,
        &QThread::deleteLater);

    connect(processor,
            &VideoProcessor::inDisplay,
            ui->inImageLabel,
            &QLabel::setPixmap);

    connect(processor,
        &VideoProcessor::outDisplay,
        ui->outImageLabel,
        &QLabel::setPixmap);

    processor->thread()->start();
}

MainWindow::~MainWindow()
{
    processor->stopVideo();
    processor->thread()->quit();
    processor->thread()->wait();
    delete ui;
}

