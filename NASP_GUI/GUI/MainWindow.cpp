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

    ColorBlobDetector &_localBlob = localHolder->blobDetector_S;
    _localBlob.setPoint(cv::Point(x, y));

    switch(flags) {
        case cv::EVENT_LBUTTONDOWN: {
            ProcessImageData _temp(cv::Point(x, y));

            //ColorBlobDetector *lBlobDetector = new
            //   ColorBlobDetector(&localHolder->blobDetector_S, cv::Point(x, y));

            _localBlob.setHsvColor(_temp.calculateHsv(img), it);
            _localBlob.processImage(img, it);

            break;
        }

        case (cv::EVENT_FLAG_SHIFTKEY + cv::EVENT_FLAG_LBUTTON): {
            ProcessImageData _temp(cv::Point(x, y));

        //ColorBlobDetector *lBlobDetector = new
        //   ColorBlobDetector(&localHolder->blobDetector_S, cv::Point(x, y));

            _localBlob.setHsvColor(_temp.calculateHsv(img), it);
            _localBlob.processImage(img, it);
            localHolder->blobDetectors_S.push_back(&_localBlob);

            break;
        }
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
            ColorBlobDetector _localBlob;
            //Assign data to structure
            currHolder_S.holder_S = &imageHolder;
            currHolder_S.it = i;
            currHolder_S.blobDetector_S = _localBlob;

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
