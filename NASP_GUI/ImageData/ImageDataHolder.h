#ifndef IMAGEDATAHOLDER_H
#define IMAGEDATAHOLDER_H

//Local
#include <ImageData/ImageData.h>
#include <ImageProcessing/ColorBlobDetector.h>

class ImageDataHolder
{
public:
    ImageDataHolder();
    int getCountImages();


    void createObjects(QStringList );

    //Getters for ImageHolder vector objects
    QString getImagePath(int );

    void saveAll();

    bool saveGrayscale();
    bool saveShrinked();

    cv::Mat getShrinked(int );

    /**************************************************************************
     * ColorBlobDetector
     * ***********************************************************************/
    void saveAll(ColorBlobDetector *);
    int getCountColors();


    //Parsing data onMouseEvent
    struct processImageData_STRUCT {
        ImageDataHolder *holder_S;

        ColorBlobDetector blobDetector_S;
        ColorBlobDetector *blobDetector_P;

        QVector<ColorBlobDetector *> blobDetectors_S;

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

    /**************************************************************************
     * ColorBlobDetector
     * ***********************************************************************/
    QVector<ColorBlobDetector *> blobDetectors;

};

#endif // IMAGEDATAHOLDER_H
