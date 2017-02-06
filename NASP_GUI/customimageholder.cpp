#include "customimageholder.h"

/**
 * @brief CustomImageHolder::CustomImageHolder
 */
CustomImageHolder::CustomImageHolder() { }

/**
 * @brief CustomImageHolder::getCount
 * @return Number of objects(images) in CustomImageHolder
 */
int CustomImageHolder::getCount() {
    return holders.count();
}

/**
 * @brief CustomImageHolder::setNames
 *          Create _input.count() pointers to CustomImage which will be stored
 *          to [holders] vector
 *          Additionaly call createShrinked and createGrayscale
 *
 * @param _input QStringList containing path to images
 */
void CustomImageHolder::createObjects(QStringList _input) {
    for(int i = 0; i < _input.count(); i ++) {
        CustomImage* cus = new CustomImage((QString)_input[i]);
        cv::Mat inputImage = cv::imread(_input[i].toStdString());

        holders.push_back(cus);

        createShrinked(inputImage, i);
        createGrayscale(i);


    }
}

QString CustomImageHolder::getImagePath(int newIt) {
    return holders[newIt]->getOriginalPath();
}

/**
 * @brief CustomImageHolder::createShrinked
 *          Create and save shrinked image
 *
 * @param _input Original, non shrinked, image
 * @param i Vector position
 */
void CustomImageHolder::createShrinked(cv::Mat _input, int i) {
    cv::Mat _local;
    cv::resize(_input, _local, holders[i]->getSize(), CV_INTER_AREA);
    holders[i]->setInputImgShrinked(_local);
}

/**
 * @brief CustomImageHolder::createGrayscale
 *          Create and save shrinked image as grayscale
 *
 * @param i Vector position
 */
void CustomImageHolder::createGrayscale(int i) {
    cv::Mat _local;
    cv::cvtColor(holders[i]->getInputImgShrinked(), _local, CV_RGB2GRAY);
    holders[i]->setInputImgGrayscale(_local);
}

void CustomImageHolder::checkDir(QString _nameOfDir) {
    QDir _local(_nameOfDir);
    _local.setNameFilters(QStringList() << "*.*");
    _local.setFilter(QDir::Files);

    if(!_local.exists()) QDir().mkdir(_nameOfDir);
    else {
        foreach (QString _fileName, _local.entryList()) {
            qDebug() << "Found file: " << _fileName;
            _local.remove(_fileName);
        }
    }
}

bool CustomImageHolder::saveAll() {
    int i = 0;
    QString _nameGrayscale = "Grayscale";
    QString _nameShrinked = "Shrinked";
    QString _type = ".jpg";

    checkDir(_nameGrayscale);
    checkDir(_nameShrinked);

    it = holders.begin();
    while(it != holders.end()) {
        (*it)->CustomImage::printOriginalPath();

        QString _writer = _nameGrayscale + QString::number(i) + _type;
        cv::imwrite("Grayscale/" + _writer.toStdString(),
                    (*it)->CustomImage::getInputImgGrayscale());

        _writer = _nameShrinked + QString::number(i) + _type;
        cv::imwrite("Shrinked/" + _writer.toStdString(),
                    (*it)->CustomImage::getInputImgShrinked());

        ++it;
        ++i;
    }

    return true;
}


