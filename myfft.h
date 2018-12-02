#ifndef MYFFT_H
#define MYFFT_H

#include <QDebug>
#include <QVector>

#include "fft/FFTReal.h"
#include "files.h"
#include "currentalldata.h"

class myFFT
{
public:
    myFFT();

    void doFFT(CurrentAllData *obj);
   // void doFFT(Files *obj);
    void analyseFFT(QVector<float>, QVector<float> &, int amountOfFFTSamples,int freq, QVector<float> &,float &);

    long amountOfSamples;

    ~myFFT();

};

#endif // MYFFT_H
