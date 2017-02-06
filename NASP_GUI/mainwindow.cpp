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
 * @
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

