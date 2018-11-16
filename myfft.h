#ifndef MYFFT_H
#define MYFFT_H

#include <QDebug>

#include "fft/FFTReal.h"
#include "files.h"

class myFFT
{
public:
    myFFT();

    void doFFT(Files obj);

    long amountOfSamples;
    float *complex;
    float *complex2; //second array is allocated when amount of channels is 2

    QVector<float> module;
    QVector<float> module2;
    QVector<float> amplitude;
    QVector<float> amplitude2;
    QVector<float> xStep;

    float maxAmplitude;
    float maxAmplitude2;


};

#endif // MYFFT_H
