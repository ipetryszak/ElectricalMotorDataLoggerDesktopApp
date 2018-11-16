#include "myfft.h"

myFFT::myFFT()
{
    amountOfSamples = 1;
    complex = nullptr;
    complex2 = nullptr;
    module = nullptr;
    module2 = nullptr;
    xStep = nullptr;
    amplitude = nullptr;
    amplitude2 = nullptr;
}


void myFFT::doFFT(Files *obj)
{

    while(amountOfSamples<obj->samples.size())amountOfSamples*=2;
    amountOfSamples/=2;

    qDebug()<<"choosen amount of samples: "<<amountOfSamples;

    switch(obj->info.amountOfChannels)
    {
   case 1:
    {
        ffft::FFTReal <float> *fft_object = new ffft::FFTReal<float>(amountOfSamples);
        complex = new float[amountOfSamples];
        float *real = new float[amountOfSamples];
        module = new float[amountOfSamples/2];
        xStep = new float[amountOfSamples/2];
        amplitude = new float[amountOfSamples/2];

        for(int i=0;i<amountOfSamples;i++)real[i] = obj->samples[i];

        fft_object->do_fft(complex,real);

        for(int i=0;i<amountOfSamples/2;i++)
        {
          module[i] = sqrt(pow(complex[i],2)+pow(complex[i+amountOfSamples/2],2));
        }

        float tmpStep = (float)obj->info.samplingFrequency/(float)amountOfSamples;


        xStep[0] = 0;
        for(int i=1;i<amountOfSamples/2;i++)xStep[i] = xStep[i-1]+tmpStep;

        for(int i=0;i<amountOfSamples/2;i++)
        {
           amplitude[i] = 2*(module[i])/amountOfSamples;
        }

        maxAmplitude = amplitude[0];
        for(int i=1;i<amountOfSamples/2;i++)if(amplitude[i]>maxAmplitude) maxAmplitude = amplitude[i];

        delete [] real;
        real = nullptr;
        delete fft_object;
        fft_object = nullptr;


        break;
    }
    case 2:
    {

        ffft::FFTReal <float> *fft_object = new ffft::FFTReal<float>(amountOfSamples);
        ffft::FFTReal <float> *fft_object2 = new ffft::FFTReal<float>(amountOfSamples);
        complex = new float[amountOfSamples];
        complex2 = new float[amountOfSamples];
        float *real = new float[amountOfSamples];
        float *real2 = new float[amountOfSamples];
        module = new float[amountOfSamples/2];
        module2 = new float[amountOfSamples/2];
        xStep = new float[amountOfSamples/2];
        amplitude = new float[amountOfSamples/2];
        amplitude2 = new float[amountOfSamples/2];

        for(int i=0;i<amountOfSamples;i++) real[i] = obj->samples[i];
        for(int i=0;i<amountOfSamples;i++) real2[i] = obj->samples2[i];

        qDebug()<<real2[0];
         fft_object->do_fft(complex,real);
         fft_object2->do_fft(complex2,real2);

         int halfAmountOfSamples = amountOfSamples/2;
         qDebug()<<halfAmountOfSamples;


         for(int i=0;i<halfAmountOfSamples;i++)
         {
            qDebug()<<i<< " ";
            module[i] = sqrt(pow(complex[i],2)+pow(complex[i+halfAmountOfSamples],2));
            module2[i] = sqrt(pow(complex2[i],2)+pow(complex2[i+halfAmountOfSamples],2));
         }

         float tmpStep;
         if(amountOfSamples!=0)tmpStep = (float)obj->info.samplingFrequency/(float)amountOfSamples;

         xStep[0] = 0;
         for(int i=1;i<amountOfSamples/2;i++)xStep[i] = xStep[i-1]+tmpStep;


         for(int i=0;i<amountOfSamples/2;i++)
         {
            amplitude[i] = 2*(module[i])/amountOfSamples;
            amplitude2[i] = 2*(module2[i])/amountOfSamples;
         }

         maxAmplitude = amplitude[0];
         maxAmplitude2 = amplitude2[0];
         for(int i=1;i<amountOfSamples/2;i++)
         {
          if(amplitude[i]>maxAmplitude) maxAmplitude = amplitude[i];
          if(amplitude2[i]>maxAmplitude2) maxAmplitude2 = amplitude2[i];
         }




         delete [] real;
         real = nullptr;
         delete [] real2;
         real2 = nullptr;
        delete fft_object;
         fft_object = nullptr;
         delete fft_object2;
         fft_object2 = nullptr;
        break;
    }

    }
qDebug()<<"at the end ok";

}

myFFT::~myFFT()
{

    if(complex!=nullptr)delete [] complex;
    complex = nullptr;
    if(complex2!=nullptr)delete [] complex2;
    complex2 = nullptr;
    if(module!=nullptr) delete [] module;
    module = nullptr;
   if(module2!=nullptr) delete [] module2;
   module2 = nullptr;
   if(xStep!=nullptr) delete [] xStep;
   xStep = nullptr;
    if(amplitude!=nullptr) delete [] amplitude;
    amplitude = nullptr;
    if(amplitude2!=nullptr) delete [] amplitude2;
    amplitude2 = nullptr;

}
