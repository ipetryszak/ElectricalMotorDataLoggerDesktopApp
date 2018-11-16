#include "myfft.h"

myFFT:: myFFT()
{
    amountOfSamples = 1;
}


void myFFT::doFFT(Files obj)
{
    if(obj.info.amountOfChannels==1) while(amountOfSamples<obj.samples.size())amountOfSamples*=2;
    if(obj.info.amountOfChannels==2) while(amountOfSamples<obj.samples2d.size())amountOfSamples*=2;
    amountOfSamples/=2;
    qDebug()<<"choosen amount of samples: "<<amountOfSamples;

    switch(obj.info.amountOfChannels)
    {
    case 1:
    {
        ffft::FFTReal <float> *fft_object = new ffft::FFTReal<float>(amountOfSamples);
        complex = new float[amountOfSamples];
        float *real = new float[amountOfSamples];
        for(int i=0;i<amountOfSamples;i++)real[i] = obj.samples[i];

        fft_object->do_fft(complex,real);

        for(int i=0;i<amountOfSamples/2;i++)
        {
            float tmp = sqrt(complex[i]*complex[i]+complex[i+amountOfSamples/2]*complex[i+amountOfSamples/2]);
            module.push_back(tmp);
        }

        float tmpStep = (float)obj.info.samplingFrequency/(float)amountOfSamples;
        xStep.push_back(0);
        for(int i=1;i<amountOfSamples/2;i++)xStep.push_back(xStep[i-1]+tmpStep);
        for(int i=0;i<amountOfSamples/2;i++)
        {
            float tmp = 2*module[i]/amountOfSamples;
            amplitude.push_back(tmp);
        }

        maxAmplitude = amplitude[0];
        for(int i=1;i<amplitude.size();i++) if(amplitude[i]>maxAmplitude) maxAmplitude = amplitude[i];

        break;
    }
    case 2:
    {
        qDebug()<<"jestem";
        ffft::FFTReal <float> *fft_object = new ffft::FFTReal<float>(amountOfSamples);
        ffft::FFTReal <float> *fft_object2 = new ffft::FFTReal<float>(amountOfSamples);
        complex = new float[amountOfSamples];
        complex2 = new float[amountOfSamples];
        float *real = new float[amountOfSamples];
        float *real2 = new float[amountOfSamples];

        for(int i=0;i<obj.samples2d.size();i++) real[i] = obj.samples2d[i].at(0);
        for(int i=0;i<obj.samples2d.size();i++) real2[i] = obj.samples2d[i].at(1);

        qDebug()<<real2[0];
         fft_object->do_fft(complex,real);
         fft_object2->do_fft(complex2,real2);

         for(int i=0;i<amountOfSamples/2;i++)
         {
             float tmp = sqrt(complex[i]*complex[i]+complex[i+amountOfSamples/2]*complex[i+amountOfSamples/2]);
             module.push_back(tmp);
             float tmp2 = sqrt(complex2[i]*complex2[i]+complex2[i+amountOfSamples/2]*complex2[i+amountOfSamples/2]);
             module2.push_back(tmp2);
         }

         float tmpStep = (float)obj.info.samplingFrequency/(float)amountOfSamples;
         xStep.push_back(0);
         for(int i=1;i<amountOfSamples/2;i++)xStep.push_back(xStep[i-1]+tmpStep);

         for(int i=0;i<amountOfSamples/2;i++)
         {
             float tmp = 2*module[i]/amountOfSamples;
             amplitude.push_back(tmp);

             tmp = 2*module2[i]/amountOfSamples;
             amplitude2.push_back(tmp);
         }

         maxAmplitude = amplitude[0];
         maxAmplitude2 = amplitude2[0];
         for(int i=1;i<amplitude.size();i++)
         {
          if(amplitude[i]>maxAmplitude) maxAmplitude = amplitude[i];
          if(amplitude2[i]>maxAmplitude2) maxAmplitude2 = amplitude2[i];
         }
        break;
    }

    }


}

