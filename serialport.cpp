#include "serialport.h"
QSerialPortInfo *info;
SerialPort::SerialPort()
{

    tmp = "";

    //create QSerialPort object
    myDevice = new QSerialPort;
    connect(myDevice,SIGNAL(readyRead()),this,SLOT(display()));


    /*  testing code
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


void SerialPort::readData()
{
/*
        byteArray.append(port->readAll());
  // QByteArray array;
  //  array = port->readAll();

    if(byteArray.endsWith("!"))
    {
        QString a(byteArray);
        tmp+=a;
        BufferSplit = tmp.split(',');

        for(int i=0;i<BufferSplit.size()-1;i++)
        {
            QString tmpString;
            int tmpInt;
            tmpString = BufferSplit[i];
            tmpInt = tmpString.toInt();
            pomiary.push_back(tmpInt);
         }
       // for(int i=0;i<pomiary.size();i++)qDebug()<<pomiary[i];
    //    qDebug()<<pomiary;
     //   emit containChanged();

    }
   // emit containChanged();
   */
}


void SerialPort::connectWithDevice()
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
        qDebug()<<"found device";
        myDevice->setPortName(devicePortName);
        myDevice->open(QIODevice::ReadWrite);
        myDevice->setBaudRate(QSerialPort::Baud9600);
        myDevice->setDataBits(QSerialPort::Data8);
        myDevice->setFlowControl(QSerialPort::NoFlowControl);
        myDevice->setParity(QSerialPort::NoParity);
        myDevice->setStopBits(QSerialPort::OneStop);
        emit connected();
    }
    else
    {
        qDebug()<<"couldnt find device";
        emit noConnected();
    }

}


void SerialPort::send(QString msg)
{
   if(myDevice->isOpen()) {
        myDevice->write(msg.toStdString().c_str());
        myDevice->waitForBytesWritten(-1);
    }

}

void SerialPort::display()
{
    QByteArray array;
    array = myDevice->readAll();
    QString got(array);


    tmp+=got;

        qDebug()<<tmp;
        tmp = "";

}








