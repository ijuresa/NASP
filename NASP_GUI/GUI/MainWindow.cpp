#include "GUI/MainWindow.h"
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

        qDebug() << "Count = " << imageHolder.getCountImages();

        QString currString = imageHolder.getImagePath(0);
        qDebug() << "CurrString " << currString;

        imageHolder.saveAll();
    }
}

void onMouseClick(int event, int x, int y, int flags, void *param) {

    ImageDataHolder::processImageData_STRUCT *localHolder =
            (ImageDataHolder::processImageData_STRUCT *)param;

    int it = localHolder->it;
    cv::Mat &img = localHolder->holder_S->getShrinked(it);

    switch(event) {
        case cv::EVENT_LBUTTONDOWN:
            //TODO: Put in processImageData
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
            //TODO: put in processImageData
            cv::Mat touchedRegionRgba = (img)(touchedRect);
            cv::Mat touchedRegionHsv;

            //Convert from RGB to HSV
            cv::cvtColor(touchedRegionRgba, touchedRegionHsv,
                         cv::COLOR_RGB2HSV_FULL);

            //Total value for each HSV element
            //TODO:Put in processImageData
            cv::Scalar colorHSV = cv::sum(touchedRegionHsv);

            //Get number of points from calculated rectangle
            //TODO: Put in processImageData
            int lPointCount = touchedRect.width * touchedRect.height;

            //Calculate average values by element
            for(int i = 0; i < colorHSV.rows; i ++) {
                colorHSV.val[i] /= lPointCount;
                qDebug() << "On: " << i << "=" << colorHSV.val[i];
            }

            ColorBlobDetector *lBlobDetector = new
                    ColorBlobDetector(&localHolder->blobDetector_S);

            lBlobDetector->setHsvColor(colorHSV, it);
            lBlobDetector->processImage(img, it);
            localHolder->blobDetectors_S.push_back(lBlobDetector);

            //Release matrices
            touchedRegionHsv.release();
            touchedRegionRgba.release();
            //TODO: Set new Boolean so we know it's touched
            break;
    }
}


void MainWindow::on_processImageButton_clicked() {
    //If none of the images were selected
    if(imageHolder.getCountImages() == 0) {
        QMessageBox::warning(this, tr("Images not found"),
                             tr("There aren't any images to process.\n"
                                "Please first select Find Image Button"));

    } else {
        //Show and process each image, one by one
        for(int i = 0; i < imageHolder.getCountImages(); i ++) {
            //Assign data to structure
            currHolder_S.holder_S = &imageHolder;
            currHolder_S.it = i;

            cv::namedWindow("Windows", 1);
            cv::setMouseCallback("Windows", onMouseClick,
                                (void*)&currHolder_S);

            //Interaction with nameWindow
            for(;;) {
                cv::imshow("Windows", imageHolder.getShrinked(i));

                //Assign KEY for waitKey
                char k = (char)cv::waitKey(0);

                //Is Esc is pressed this for(;;) loop is broken
                if(k == 27) {
                    qDebug() << "Entered " << k;
                    break;
                }
            }
        }

        //Destroys all windows after last picture calibration
        cv::destroyAllWindows();
        qDebug() << imageHolder.getCountImages();
        qDebug() << currHolder_S.blobDetectors_S.count();

        //Save all data from QVector in structure to QVector outside it
        //It is done this way so structure isn't needed anymore
        for(int i = 0; i < currHolder_S.blobDetectors_S.count(); i ++) {
            imageHolder.saveAll(currHolder_S.blobDetectors_S[i]);
        }

        qDebug() << imageHolder.getCountColors();
    }

}
