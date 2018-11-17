#include "files.h"

Files::Files()
{

}

/*
 * STRUCT OF FILE WITH DATA
 * first row -> amount of channels
 * second row -> sampling frequency
 * third row -> sampling period
 * fourth row -> range
 * sixth row - n row = samples
 */

/* Inputs float numbers should be in form ex. 2,33 row by row
 * Function swaps ',' on '.'
 * Informations about signal are saved in struct content; variable info
 * If signal origin is from one channel then data are saved in QVector samples
 * If signal origin is from two channels then data are saved in QVector samples2d
 */
void Files::openFile()
{

   QString fileName = QFileDialog::getOpenFileName(0,QObject::tr("Otwórz dane"), "../output_files", QObject::tr("Text files (*.txt)"));

   qDebug()<<fileName;

    QFile file(fileName);
    if (!file.exists()) {
        qDebug()<<"doesnt exist!";
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"couldnt open";
        return;
    }

//--info about signal are saved to struct content variable info--/
    QTextStream in(&file);
    QString line = in.readLine();
    info.amountOfChannels = line.toFloat(); //first line amount of channels
    qDebug()<<"amount of channels "<<info.amountOfChannels;
    line = in.readLine();
    info.samplingFrequency = line.toFloat(); //second line sampling frequency
    qDebug()<<"frequency "<<info.samplingFrequency;
    line = in.readLine();
    info.samplingPeriod = line.toFloat(); //third line sampling period (time)
    line = in.readLine();
    info.range = line.toFloat(); //fourth line range (dipens on used device to measurement)
    line = in.readLine(); //read empty line
//-----------------------------------------------------------------
    if(info.amountOfChannels==1)
    {
        while (!in.atEnd())
        {
            QString line = in.readLine();
            line.replace(',','.');
            samples.push_back(line.toFloat());
        }
        qDebug()<<samples;


        maxAmplitude = samples[0];
        for(int i=1;i<samples.size();i++) if(maxAmplitude<samples[i])maxAmplitude = samples[i];
        minAmplitude = samples[0];
        for(int i=1;i<samples.size();i++)if(minAmplitude>samples[i])minAmplitude = samples[i];
        generalMaxAmplitude = maxAmplitude;
        generalMinAmplitude = minAmplitude;


    }
    else if(info.amountOfChannels==2)
    {
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList pieces = line.split( '\t' );

            QString tmp1 = pieces[0];
            QString tmp2 = pieces[1];
            tmp1.replace(',','.');
            tmp2.replace(',','.');


            samples.push_back(tmp1.toFloat());
            samples2.push_back(tmp2.toFloat());

            // samples2d.push_back(tmpV);

        }

        //find max amplitude
        maxAmplitude = samples[0];
        maxAmplitude2 = samples2[0];
        for(int i=1;i<samples.size();i++)
        {
            if(maxAmplitude<samples[i])maxAmplitude = samples[i];
            if(maxAmplitude2<samples2[i])maxAmplitude2 = samples2[i];
        }

        minAmplitude = samples[0];
        minAmplitude2 = samples2[0];
        for(int i=1;i<samples.size();i++)
        {
            if(minAmplitude>samples[i])minAmplitude = samples[i];
            if(minAmplitude2<samples2[i])minAmplitude2 = samples2[i];
        }

        generalMaxAmplitude = (maxAmplitude>maxAmplitude2) ? maxAmplitude : maxAmplitude2;
        generalMinAmplitude = (minAmplitude<minAmplitude2) ? minAmplitude : minAmplitude2;




    }
    else {}

    file.close();


    qDebug()<<"samples size "<<samples.size();
    qDebug()<<"samples2 size "<<samples2.size();
}

void Files::copyData(CurrentAllData *obj)
{

    obj->amountOfChannels = info.amountOfChannels;
    obj->samplingFrequency = info.samplingFrequency;
    obj->samplingPeriod = info.samplingPeriod;
    obj->samplingRange = info.range;

    obj->samples1CH = samples;
    obj->samples2CH = samples2;

    obj->maxAmplitude = generalMaxAmplitude;
    obj->minAmplitude = generalMinAmplitude;
}

void Files::saveFile(CurrentAllData *obj)
{
    QString fileName = QFileDialog::getSaveFileName(0,QObject::tr("Zapisz"), "", QObject::tr("Text files (*.txt)"));

    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    if (fileName.isEmpty()) return;
    else {

         }


    QTextStream out(&file);
    out << obj->amountOfChannels<<endl
        << obj->samplingFrequency<<endl
        << obj->samplingPeriod<<endl
        << obj->samplingRange<<endl<<endl;

    if(obj->amountOfChannels==1)
    {
        for(int i=0;i<obj->samples1CH.size();i++)
        {
            out<<obj->samples1CH[i]<<endl;
        }
    }
    else if(obj->amountOfChannels==2)
    {
        for(int i=0;i<obj->samples1CH.size();i++)
        {
            out<<obj->samples1CH[i]<<"\t"<<obj->samples2CH[i]<<endl;
        }
    }

    file.flush();
    file.close();

}



Files::~Files()
{

}
