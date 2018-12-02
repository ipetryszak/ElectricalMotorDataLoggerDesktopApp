#include "serialport.h"

SerialPort::SerialPort()
{

    //create QSerialPort object
    myDevice = new QSerialPort;
    //default sampling frequency
    samplingFrequency = 1000;
    connect(myDevice,SIGNAL(readyRead()),this,SLOT(readData()));


  /*  //  testing code to discover vendor and product id
     qDebug()<<"Number of ports "<<QSerialPortInfo::availablePorts().length()<<"\n";
     for(const QSerialPortInfo &SerialPortInfo : QSerialPortInfo::availablePorts())
     {
         qDebug()<<"Description "<<SerialPortInfo.description()<<"\n";
         qDebug()<<"Has vendor id? "<<SerialPortInfo.hasVendorIdentifier()<<"\n";
         qDebug()<<"Vendor ID " << SerialPortInfo.vendorIdentifier()<<"\n";
         qDebug()<<"Has product ID ? "<<SerialPortInfo.hasProductIdentifier()<<"\n";
         qDebug()<<"Product ID "<<SerialPortInfo.productIdentifier()<<"\n";
     }
*/

}


void SerialPort::connectWithDevice()
{
    if(myDevice->isOpen())
    {
        //disconnect device;
        myDevice->close();
        qDebug()<<"Device disconnected";
        emit disconnectedCorrectly();
    }
    else
    {
            bool deviceIsAvailable = false;
            QString devicePortName;
            for(const QSerialPortInfo &SerialPortInfo : QSerialPortInfo::availablePorts())
                {
                    if(SerialPortInfo.hasProductIdentifier() && SerialPortInfo.hasVendorIdentifier())
                        {
                            if(SerialPortInfo.productIdentifier()==productID && SerialPortInfo.vendorIdentifier()==vendorID)
                                {
                                    deviceIsAvailable = true;
                                    devicePortName = SerialPortInfo.portName();
                                }
                        }
                }

    if(deviceIsAvailable)
    {
        qDebug()<<"Device found";
        myDevice->setPortName(devicePortName);
        myDevice->open(QIODevice::ReadWrite);
        myDevice->setBaudRate(QSerialPort::Baud38400);
        myDevice->setDataBits(QSerialPort::Data8);
        myDevice->setFlowControl(QSerialPort::NoFlowControl);
        myDevice->setParity(QSerialPort::NoParity);
        myDevice->setStopBits(QSerialPort::OneStop);
        emit connected();
    }
    else
    {
        qDebug()<<"Device didn't find";
        emit noConnected();
    }
    }

}


void SerialPort::send(QString msg)
{
   if(myDevice->isOpen()) {
        myDevice->write(msg.toStdString().c_str());
        myDevice->waitForBytesWritten(-1);
    }

}


void SerialPort::readData()
{
    samplesIntVector.clear();
    BufferSplit.clear();
    //appends all data do qbytearray
    byteArrayToReadData.append(myDevice->readAll());

    //data receiving process ends with char "!" so then data can be converted to int type
    if(byteArrayToReadData.endsWith("!"))
    {
        //converting received data from qbyte to qstring
        QString tmp(byteArrayToReadData);
        //adding coverted data to qstringlist, data are spilted using coma
        BufferSplit = tmp.split(',');
        qDebug()<<BufferSplit;
        //converting data from qstring list to vector<int> array
        for(int i=0;i<BufferSplit.size()-1;i++)
        {
            QString tmpString;
            int tmpInt;
            tmpString = BufferSplit[i];
            tmpInt = tmpString.toInt();
            samplesIntVector.push_back(tmpInt);
         }
        byteArrayToReadData.clear();
        emit gotSample();
     }
}


void SerialPort::copyData(CurrentAllData *obj)
{
    if(obj->amountOfChannels==1)
    {
        for(int i=0;i<samplesIntVector.size();i++) obj->samples1CH.push_back((float)((samplesIntVector[i]-1845)/(float)obj->samplingRange));
    }
    else if(obj->amountOfChannels==2)
    {
        for(int i=0;i<samplesIntVector.size()-1;i++)
        {
            obj->samples1CH.push_back((float)((samplesIntVector[i++]-1972)/(float)obj->samplingRange));
            obj->samples2CH.push_back((float)((samplesIntVector[i]-1972)/(float)obj->samplingRange));
        }
    }
    else{}

//---------------find max min amplitude--------------------------------------------------
   float tmpMaxAmplitude = obj->samples1CH[0];
   float tmpMaxAmplitude2 = obj->samples2CH[0];
    for(int i=1;i<obj->samples1CH.size()-2;i++)
    {
        if(tmpMaxAmplitude<obj->samples1CH[i])tmpMaxAmplitude = obj->samples1CH[i];
        if(tmpMaxAmplitude2<obj->samples2CH[i])tmpMaxAmplitude2 = obj->samples2CH[i];
    }

    float tmpMinAmplitude = obj->samples1CH[0];
    float tmpMinAmplitude2 = obj->samples2CH[0];
    for(int i=1;i<obj->samples1CH.size()-2;i++)
    {
        if(tmpMinAmplitude>obj->samples1CH[i])tmpMinAmplitude = obj->samples1CH[i];
       if(tmpMinAmplitude2>obj->samples2CH[i])tmpMinAmplitude2 = obj->samples2CH[i];
    }

    if(obj->amountOfChannels==1)
    {
        obj->maxAmplitude = tmpMaxAmplitude;
        obj->minAmplitude = tmpMinAmplitude;
    }
    else if(obj->amountOfChannels==2)
    {

        obj->maxAmplitude = (tmpMaxAmplitude>tmpMaxAmplitude2) ? tmpMaxAmplitude : tmpMaxAmplitude2;
        obj->minAmplitude = (tmpMinAmplitude<tmpMinAmplitude2) ? tmpMinAmplitude : tmpMinAmplitude2;

        qDebug()<<"================================================="<<obj->samples1CH<<"------------------------"<<obj->samples2CH<<"------------";
        qDebug()<<"max amp "<<obj->maxAmplitude<<" min amp "<<obj->minAmplitude;
    }
    else {}



}
