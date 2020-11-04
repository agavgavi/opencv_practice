#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>

MainWindow::MainWindow(QWidget *parent, int argc, char *argv[])
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(argc < 2) {
        option = "lbp_front";
    }
    else {
        option = std::string(argv[1]);
    }
    processor = new VideoProcessor(nullptr,option);
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
        &VideoProcessor::outDisplay,
        ui->outImageLabel,
        &QLabel::setPixmap);

    processor->thread()->start();

    connect(processor,
            &VideoProcessor::quitProgram,
            QApplication::instance(),
            &QApplication::quit);
}

MainWindow::~MainWindow()
{
    processor->stopVideo();
    processor->thread()->quit();
    processor->thread()->wait();
    delete ui;
}

