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
 *
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

            QVector<float> tmpV;
            tmpV.push_back(tmp1.toFloat());
            tmpV.push_back(tmp2.toFloat());
            samples2d.push_back(tmpV);

        }
qDebug()<<"ok";



    }
    else {}
}
