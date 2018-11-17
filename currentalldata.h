#ifndef CURRENTALLDATA_H
#define CURRENTALLDATA_H

#include <QVector>
/*
 * Class treated as a container to store
 * all data proccesed in one proccesing cycle
 */


class CurrentAllData
{
public:
    CurrentAllData();

    //samples
    QVector<float> samples1CH;
    QVector<float> samples2CH;

    //infos 'bout samples
    int amountOfChannels;
    int samplingFrequency;
    int samplingPeriod;
    int samplingRange;

    float maxAmplitude;
    float minAmplitude;

    //fft
    QVector<float> xAxis;
    QVector<float> amplitudeCH1;
    QVector<float> amplitudeCH2;

    float maxFFT1Amplitude;
    float maxFFT2Amplitude;
};

#endif // CURRENTALLDATA_H
