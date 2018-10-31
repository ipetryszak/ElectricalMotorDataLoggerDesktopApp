#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStringList>
#include <QComboBox>
#include <QStringList>
#include <QDebug>


class SerialPort : public QObject
{
    Q_OBJECT


signals:
    connected();
    noConnected();


public slots:

    void readData();
    void connectWithDevice();
    void display();


public:
    SerialPort();
    void connectWithDevice(QSerialPort *myDevice);
    void send(int data);



    QList <QSerialPortInfo> availablePorts;
    QStringList availableDevices;
    QComboBox *availableDevs;
    QSerialPort *myDevice;
    int m_slot;
    QString tmp;
    QStringList BufferSplit;
    QVector<int> pomiary;
    QByteArray byteArray;

private:
    static const quint16 vendorID = 1027;
    static const quint16 productID = 24577;

};

#endif // SERIALPORT_H
