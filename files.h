#ifndef FILES_H
#define FILES_H

#include<QFile>
#include<QTextStream>
#include<QDebug>
#include <QFileDialog>
#include <QObject>

/*
 * STRUCT OF FILE WITH DATA
 * first row -> amount of channels
 * second row -> sampling frequency
 * third row -> sampling period
 * fourth row -> range
 * sixth row - n row = samples
 *
 */

//right now for one channel

class Files
{
public:
    Files();

   // QVector<QVector<float>> samples2d;
    QVector<float> samples;
    QVector<float> samples2;

    float maxAmplitude;
    float maxAmplitude2;
    float minAmplitude;
    float minAmplitude2;

    float generalMaxAmplitude;
    float generalMinAmplitude;

    struct content
    {
        int amountOfChannels;
        int samplingFrequency;
        int samplingPeriod;
        int range;
    };

   void openFile();

   QVector<float> inputFloatVect;
   struct content info;

   ~Files();
};

#endif // FILES_H
