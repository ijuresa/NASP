#ifndef IMAGEDATAHOLDER_H
#define IMAGEDATAHOLDER_H

//Local
#include <ImageData/ImageData.h>

class ImageDataHolder
{
public:
    ImageDataHolder();
    int getCount();
    void createObjects(QStringList );

    //Getters for ImageHolder vector objects
    QString getImagePath(int );

    bool saveAll();
    bool saveGrayscale();
    bool saveShrinked();

    cv::Mat getShrinked(int );

    struct processImage_STRUCT {
        ImageDataHolder *holder_S;
        int it;
    };

private:
    //Vector of pointers to class objects of type ImageHolder
    QVector<ImageData *> holders;

    //Iterator to point at pointers to class of type ImageHolder
    QVector<ImageData *>::iterator it;

    void createShrinked(cv::Mat , int );
    void createGrayscale(int );
    void checkDir(QString );

};

#endif // IMAGEDATAHOLDER_H
