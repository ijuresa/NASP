#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//QT
#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>

//OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//Local
#include <customimage.h>
#include <customimageholder.h>
#include <colorblobdetector.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

//Public variables/functions
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//Private slots
private slots:
    void on_findImageButton_clicked();

//Private variables/functions
    void on_processImageButton_clicked();

private:
    Ui::MainWindow *ui;
    cv::Mat inputImage;
    CustomImageHolder imageHolder;


};

#endif // MAINWINDOW_H
