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



void onMouseClick(int event, int x, int y, int flags, void *param) {

    CustomImageHolder::processImage_STRUCT *localHolder =
            (CustomImageHolder::processImage_STRUCT *)param;

    int it = localHolder->it;
    cv::Mat &img = localHolder->holder_S->getShrinked(it);

    switch(event) {
        case cv::EVENT_LBUTTONDOWN:
            //TODO: Put in ProcessImage
            cv::Rect touchedRect;
            qDebug() << "Clicked at: " << x << y;

            //Calculate starting points for RECT(x, y)
            touchedRect.x = (x > 4) ?  (x - 4) : 0;
            touchedRect.y = (y > 4) ? (y -4) : 0;
            qDebug() << "RectX =" << touchedRect.x << "RectY" << touchedRect.y;

            //Calculate RectWidth
            touchedRect.width = (x + 4 < (img).cols) ? x + 4 - touchedRect.x :
                                                      (img).cols -touchedRect.x;
            qDebug() << "Rect width:" << touchedRect.width;

            //Calculate RectHeight
            touchedRect.height = (y + 4 < (img).rows) ? y + 4 -touchedRect.y :
                                                     (img).rows - touchedRect.y;
            qDebug() << "Rech height:" << touchedRect.height;

            //Get submatrix from touchedRect (8x8)
            //TODO: put in ProcessImage
            cv::Mat touchedRegionRgba = (img)(touchedRect);
            cv::Mat touchedRegionHsv;

            //Convert from RGB to HSV
            cv::cvtColor(touchedRegionRgba, touchedRegionHsv,
                         cv::COLOR_RGB2HSV_FULL);

            //Total value for each HSV element
            //TODO:Put in ProcessImage
            cv::Scalar colocHSV = cv::sum(touchedRegionHsv);

            //Get number of points from calculated rectangle
            //TODO: Put in ProcessImage
            int lPointCount = touchedRect.width * touchedRect.height;

            //Calculate average values by element
            for(int i = 0; i < colocHSV.rows; i ++) {
                colocHSV.val[i] /= lPointCount;
                qDebug() << "On: " << i << "=" << colocHSV.val[i];
            }

            touchedRegionHsv.release();
            touchedRegionRgba.release();
            //TODO: Set new Boolean so we know it's touched
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

            CustomImageHolder::processImage_STRUCT currHolder_S;
            currHolder_S.holder_S = &imageHolder;
            currHolder_S.it = i;

            cv::namedWindow("Windows", 1);
            cv::setMouseCallback("Windows", onMouseClick,
                                (void*)&currHolder_S);

            //Interaction with nameWindow
            for(;;) {
                cv::imshow("Windows", imageHolder.getShrinked(i));
                qDebug() << imageHolder.getShrinked(i).cols;
                qDebug() << imageHolder.getShrinked(i).rows;
                char k = (char)cv::waitKey(0);

                if(k == 27) {
                    qDebug() << "Entered " << k;
                    break;
                }
            }
        }
        cv::destroyAllWindows();
    }
}
