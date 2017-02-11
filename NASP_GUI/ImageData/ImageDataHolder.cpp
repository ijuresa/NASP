#include "ImageDataHolder.h"

ImageDataHolder::ImageDataHolder() { }

/**
 * @brief ImageDataHolder::getCount
 * @return Number of objects(images) in CustomImageHolder
 */
int ImageDataHolder::getCountImages() {
    return holders.count();
}

/**
 * @brief ImageDataHolder::CreateObjects
 *          Create _input.count() pointers to CustomImage which will be stored
 *          to [holders] vector
 *          Additionaly call createShrinked and createGrayscale
 *
 * @param _input QStringList containing path to images
 */
void ImageDataHolder::createObjects(QStringList _input) {
    for(int i = 0; i < _input.count(); i ++) {
        ImageData* cus = new ImageData((QString)_input[i]);
        cv::Mat inputImage = cv::imread(_input[i].toStdString());

        //Save instance of ImageData to QVector
        holders.push_back(cus);

        //Resize image to default size
        createShrinked(inputImage, i);
        //Resized image convert to grayscale
        createGrayscale(i);
    }
}

/**
 * @brief ImageDataHolder::getImagePath
 * @param newIt Index of wanted image
 * @return Absolute path to image(QString)
 */
QString ImageDataHolder::getImagePath(int newIt) {
    return holders[newIt]->getOriginalPath();
}

/**
 * @brief ImageDataHolder::getShrinked
 * @param newIt Index of wanted image
 * @return Absolute path to image(QString)
 */
cv::Mat ImageDataHolder::getShrinked(int newIt) {
    return holders[newIt]->getInputImgShrinked();
}

/**
 * @brief ImageDataHolder::createShrinked
 *          Create and save shrinked image
 *
 * @param _input Original, non shrinked, image
 * @param i Vector position
 */
void ImageDataHolder::createShrinked(cv::Mat _input, int i) {
    cv::Mat _local;
    cv::resize(_input, _local, holders[i]->getSize(), CV_INTER_AREA);
    holders[i]->setInputImgShrinked(_local);
}

/**
 * @brief ImageDataHolder::createGrayscale
 *          Create and save shrinked image as grayscale
 *
 * @param i Vector position
 */
void ImageDataHolder::createGrayscale(int i) {
    cv::Mat _local;
    cv::cvtColor(holders[i]->getInputImgShrinked(), _local, CV_RGB2GRAY);
    holders[i]->setInputImgGrayscale(_local);
}

/**
 * @brief ImageDataHolder::checkDir
 *          Checks if dir of _nameOfDir exists
 *          True: Remove all files inside and create new ones
 *          False: Create new dir and create new files
 *
 * @param _nameOfDir Name of dir to be created or modified
 */
void ImageDataHolder::checkDir(QString _nameOfDir) {
    QDir _local(_nameOfDir);

    //Filter for files(All)
    _local.setNameFilters(QStringList() << "*.*");
    _local.setFilter(QDir::Files);

    if(!_local.exists()) QDir().mkdir(_nameOfDir);
    //TODO: Only work on first button event - find out why
    else {
        foreach (QString _fileName, _local.entryList()) {
            qDebug() << "Found file: " << _fileName;
            _local.remove(_fileName);
        }
    }
}

//TODO: Create more error messages
void ImageDataHolder::saveAll() {
    int i = 0;
    //Names of directories
    QString _nameGrayscale = "Grayscale";
    QString _nameShrinked = "Shrinked";

    //Images will be saved as this type
    QString _type = ".jpg";

    //Check directories
    checkDir(_nameGrayscale);
    checkDir(_nameShrinked);

    //Set iterator to begining of vector
    it = holders.begin();
    while(it != holders.end()) {
        //TODO: Remove this
        (*it)->ImageData::printOriginalPath();

        //String for images (As they will be saved) -- Grayscale
        QString _writer = _nameGrayscale + QString::number(i) + _type;
        cv::imwrite("Grayscale/" + _writer.toStdString(),
                    (*it)->ImageData::getInputImgGrayscale());

        //String for images (As they will be saved) -- Shrinked
        _writer = _nameShrinked + QString::number(i) + _type;
        cv::imwrite("Shrinked/" + _writer.toStdString(),
                    (*it)->ImageData::getInputImgShrinked());

        ++it;
        ++i;
    }
}

/******************************************************************************
 * ColorBlobDetector
 * ***************************************************************************/
/**
 * @brief ImageDataHolder::saveAll
 *          Save all colors to vector instead structure
 *
 * @param _input Pointer to object of ColorBlobDetector from structure
 */
void ImageDataHolder::saveAll(ColorBlobDetector *_input) {
    blobDetectors.push_back(_input);
}

/**
 * @brief ImageDataHolder::getCountColors
 * @return Number of clicks
 *          TODO: Fix
 */
int ImageDataHolder::getCountColors() {
    return blobDetectors.count();
}
