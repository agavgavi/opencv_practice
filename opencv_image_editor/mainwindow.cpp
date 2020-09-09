#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv4/opencv2/opencv.hpp>

#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSettings>
#include <QThread>

// Once the UI have been set up, load the predefined settings
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();

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

//    connect(processor,
//            &VideoProcessor::inDisplay,
//            ui->inImageLabel,
//            &QLabel::setPixmap);

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





// When hitting browse in the input image section, prompt user to select a file they want to open, and then populate the text field with it.
void MainWindow::on_inputPushButton_pressed()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Input Image",
                                                    QDir::currentPath(), "Images (*.jpg *.png *.bmp)");
    if(QFile::exists(fileName)) {
        ui->inputLineEdit->setText(fileName);
    }
}

// When hitting browse in the output image section, prompt user to select or create a file they want the image to be saved to, and then populate the text field with it.
void MainWindow::on_outputPushButton_pressed()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Select Output Image",
                                                    QDir::currentPath(), "Images (*.jpg *.png *.bmp)");
    if(!fileName.isEmpty()) {
        ui->outputLineEdit->setText(fileName);

    }
}


// When the save button is pressed, get the values for what is needed to be edited and edit the image.
// This opens the input image, applies a median or gaussian blur, and adjusts the brightness/contrast based
// on the sliders provided. It then will save the image to the output location.
// If the checkbox is checked, display the image after saving
void MainWindow::on_savePushButton_pressed()
{
    QString inputName = ui->inputLineEdit->text();
    QString outputName = ui->outputLineEdit->text();

    int SliderVal1 = ui->brightnessHorizontalSlider->value();
    int SliderVal2 = ui->contrastHorizontalSlider->value();

    int Brightness = SliderVal1 - 50;
    double Contrast = SliderVal2 / 50.0;

    cv::Mat inpImage, outImage;


    inpImage = cv::imread(inputName.toStdString());

    if(ui->medianBlurRadioButton->isChecked()) {
        cv::medianBlur(inpImage, outImage, 5);
    }

    else if(ui->gaussianBlurRadioButton->isChecked()) {
        cv::GaussianBlur(inpImage, outImage,
                         cv::Size(5, 5), 1.25);
    }

    outImage.convertTo(outImage, -1, Contrast, Brightness);

    cv::imwrite(outputName.toStdString(), outImage);

    if(ui->displayImageCheckBox->isChecked()) {
        cv::imshow("Output Image", outImage);
    }
}

// When closing the program, override the virtual function, prompt the user to see if they truly want to exit.
// If yes, save current state and exit.
// If no, ignore and continue on with the program
void MainWindow::closeEvent(QCloseEvent *event) {
    int result = QMessageBox::warning(this, "Exit",
                                      "Are you sure you want to close this program?",
                                      QMessageBox::Yes, QMessageBox::No);

    if(result == QMessageBox::Yes) {
        saveSettings();
        event->accept();
    }

    else {
        event->ignore();
    }
}

// Load previous settings or default values for all of the boxes in the editor.
void MainWindow::loadSettings()
{
    QSettings settings("agavgavi", "opencv_image_editor", this);

    ui->inputLineEdit->setText(settings.value("inputLineEdit", "").toString());
    ui->outputLineEdit->setText(settings.value("outputLineEdit", "").toString());

    ui->medianBlurRadioButton->setChecked(settings.value("medianBlurRadioButton", true).toBool());
    ui->gaussianBlurRadioButton->setChecked(settings.value("gaussianBlurRadioButton", false).toBool());

    ui->displayImageCheckBox->setChecked(settings.value("displayImageCheckBox", false).toBool());

    ui->brightnessHorizontalSlider->setValue(settings.value("brightnessHorizontalSlider", 50).toInt());
    ui->contrastHorizontalSlider->setValue(settings.value("contrastHorizontalSlider", 50).toInt());

    ui->brightnessLabel->setText(settings.value("brightnessLabel", "Brightness (50) : ").toString());
    ui->contrastLabel->setText(settings.value("contrastLabel", "Contrast (50) : ").toString());
}

// On exit, save all boxed in the editor for ease of access next time you load the program.
void MainWindow::saveSettings()
{
    QSettings settings("agavgavi", "opencv_image_editor", this);

    settings.setValue("inputLineEdit", ui->inputLineEdit->text());
    settings.setValue("outputLineEdit", ui->outputLineEdit->text());

    settings.setValue("medianBlurRadioButton", ui->medianBlurRadioButton->isChecked());
    settings.setValue("gaussianBlurRadioButton", ui->gaussianBlurRadioButton->isChecked());

    settings.setValue("displayImageCheckBox", ui->displayImageCheckBox->isChecked());

    settings.setValue("brightnessHorizontalSlider", ui->brightnessHorizontalSlider->value());
    settings.setValue("contrastHorizontalSlider", ui->contrastHorizontalSlider->value());

    settings.setValue("brightnessLabel", ui->brightnessLabel->text());
    settings.setValue("contrastLabel", ui->contrastLabel->text());
}


// Make the text for the brightness slider responsive to the value it is being changed to
void MainWindow::on_brightnessHorizontalSlider_sliderMoved(int position)
{
    QString brightnessVal = QString("Brightness (%1) : ").arg(position);
    editor.setMedian(ui->medianBlurRadioButton->isChecked());
    editor.setGaussian(ui->gaussianBlurRadioButton->isChecked());
    ui->brightnessLabel->setText(brightnessVal);
    editor.setBrightness(position);

}

// Make the text for the contrast slider responsive to the value it is being changed to
void MainWindow::on_contrastHorizontalSlider_sliderMoved(int position)
{
    QString contrastVal = QString("Contrast (%1) : ").arg(position);
    editor.setMedian(ui->medianBlurRadioButton->isChecked());
    editor.setGaussian(ui->gaussianBlurRadioButton->isChecked());
    ui->contrastLabel->setText(contrastVal);
    editor.setContrast(position);
}
