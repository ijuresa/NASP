#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 *        Input for app
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
}
/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow() {
    delete ui;
}

/**
 * @brief MainWindow::on_findImageButton_clicked
 */
void MainWindow::on_findImageButton_clicked() {
    //Get image path
    QStringList imgNames = QFileDialog::getOpenFileNames(this,
        tr("Open Image"));

    //Check if anything was picked
    if(!imgNames.isEmpty()) {
        imageHolder.createObjects(imgNames);

        qDebug() << "Count = " << imageHolder.getCount();

        QString currString = imageHolder.getImagePath(0);
        qDebug() << "CurrString " << currString;

        bool drek = imageHolder.saveAll();

    }
}



void onMouseClick(int event, int x, int y, int flags, void* userdata) {
    switch(event) {
        case cv::EVENT_LBUTTONDOWN:
            qDebug() << "Clicked at: " << x << y;
            break;
    }
}

void MainWindow::on_processImageButton_clicked() {
    if(imageHolder.getCount() == 0) {
        QMessageBox::warning(this, tr("Images not found"),
                             tr("There aren't any images to process.\n"
                                "Please first select Find Image Button"));
    } else {

        for(int i = 0; i < imageHolder.getCount(); i ++) {
            cv::namedWindow("Windows", 1);
            cv::setMouseCallback("Windows", onMouseClick, NULL);
            for(;;) {
                cv::imshow("Windows", imageHolder.getShrinked(i));

                char k = (char)cv::waitKey(0);

                if(k == 27) {
                    qDebug() << "Entered " << k;
                    break;
                }
                else if(k = 'c') {
                    qDebug() << "Entered " << k;
                    break;
                }
            }
        }
    }
}
