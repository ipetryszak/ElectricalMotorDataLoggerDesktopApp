#include "myfft.h"

myFFT::myFFT()
{
    amountOfSamples = 1;

}
void myFFT::doFFT(CurrentAllData *obj)
{
    while(amountOfSamples<obj->samples1CH.size())amountOfSamples*=2;
    amountOfSamples/=2;
    qDebug()<<"choosen amount of samples: "<<amountOfSamples;

    if(obj->amountOfChannels==1)
        analyseFFT(obj->samples1CH,obj->xAxis,amountOfSamples,obj->samplingFrequency,obj->amplitudeCH1,obj->maxFFT1Amplitude);
    if(obj->amountOfChannels==2)
    {
        analyseFFT(obj->samples1CH,obj->xAxis,amountOfSamples,obj->samplingFrequency,obj->amplitudeCH1,obj->maxFFT1Amplitude);
        analyseFFT(obj->samples2CH,obj->xAxis,amountOfSamples,obj->samplingFrequency,obj->amplitudeCH2,obj->maxFFT2Amplitude);
    }

}

//goal -> amplitudeArray and xAxis ?
//arguments -> amount of samples to do fft, array of samples, frequency,
void myFFT::analyseFFT(QVector<float> samplesAr, QVector<float> &xAx, int amountOfFFTSamples,int freq, QVector<float> &amplitude, float &maxAmp)
{

    ffft::FFTReal <float> *fft_object = new ffft::FFTReal<float>(amountOfFFTSamples);
    float *complex = new float[amountOfFFTSamples]; //size of complex == amountOfSamples
    float *real = new float[amountOfFFTSamples];
    QVector<float> tmpModule; //size amounOfSamples/2 because its module of real and imag part

    for(int i=0;i<amountOfFFTSamples;i++)real[i] = samplesAr[i];
    fft_object->do_fft(complex,real);

    for(int i=0;i<amountOfFFTSamples/2;i++)
       tmpModule.push_back(sqrt(pow(complex[i],2)+pow(complex[i+amountOfFFTSamples/2],2)));

    float tmpStep = (float)freq/(float)amountOfFFTSamples;

    xAx.push_back(0);
    for(int i=1;i<amountOfFFTSamples/2;i++)xAx.push_back(xAx[i-1]+tmpStep);

    for(int i=0;i<amountOfFFTSamples/2;i++)
       amplitude.push_back(2*(tmpModule[i])/amountOfFFTSamples);


    maxAmp = amplitude[0];

    for(int i=1;i<amplitude.size();i++)
       if(amplitude[i]>maxAmp) maxAmp = amplitude[i];

    delete fft_object;
    delete [] complex;
    delete [] real;
}



myFFT::~myFFT()
{

}
