#ifndef CUSTOMIMAGEHOLDER_H
#define CUSTOMIMAGEHOLDER_H

//Local
#include <customimage.h>

class CustomImageHolder {
public:
    CustomImageHolder();
    int getCount();
    void createObjects(QStringList );

    //Getters for CustomImage vector objects
    QString getImagePath(int );

    bool saveAll();
    bool saveGrayscale();
    bool saveShrinked();


private:
    //Vector of pointers to class objects of type CustomImage
    QVector<CustomImage *> holders;

    //Iterator to point at pointers to class of type CustomImage
    QVector<CustomImage *>::iterator it;

    void createShrinked(cv::Mat , int );
    void createGrayscale(int );
    void checkDir(QString );

};

#endif // CUSTOMIMAGEHOLDER_H
