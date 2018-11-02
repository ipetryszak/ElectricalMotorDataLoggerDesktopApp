#include "serialport.h"

SerialPort::SerialPort()
{

    //create QSerialPort object
    myDevice = new QSerialPort;
    connect(myDevice,SIGNAL(readyRead()),this,SLOT(readData()));


    /*  testing code to discover vendor and product id
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
