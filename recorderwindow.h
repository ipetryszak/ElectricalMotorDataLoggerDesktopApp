#ifndef RECORDERWINDOW_H
#define RECORDERWINDOW_H


#include <QTabWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineSeries>
#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QObject>
#include <QStatusBar>

#include "chart.h"
#include "chartview.h"
#include "serialport.h"


class RecorderWindow : public QObject
{
    Q_OBJECT

public slots:
    void connectedChanged();
    void noConnectedChanged();
    void channelChanged();
    void samplingChanged();
    void timeChanged();
    void howStartChanged();
public:
    RecorderWindow();

    SerialPort *device;
    QStatusBar *statusBar;

    enum deviceCommands {CH1 = 1, CH2 = 2, CH12 = 3, S1kHz = 11, S2kHz = 12, S3kHz = 13, S4kHz = 14, S5kHz = 15, S6kHz = 16, S7kHz = 17,
                        S8kHz = 18, S9kHz = 19, S10kHz = 20, T1s = 101,T2s = 102, T3s = 103, T4s = 104, T5s = 105, T6s = 106, T7s = 107,
                        T8s = 108, T9s = 109, T10s = 110, START = 120, RISING_EDGE = 121};

    deviceCommands commands;

    //widgets that are included by mainWindowTabWidget, contains all layout and objects
    QWidget *recordPageWidget;
    QWidget *fftPageWidget;
    //widget that cover all window space, divides it on record and fft area
    QTabWidget *mainWindowTabWidget;
    //Main Grid Layout, parent->recordPageWidget, contains left menu and right chart
    QGridLayout *mainRecordLayout;
    //first GroupBox in left menu, contains QVBoxLayot and widgets - buttons
    QGroupBox *startGroupBox;
    QGroupBox *pomiarGroupBox;
    QGroupBox *resultsGroupBox;

    //main MenuBoxLayout and boxes added to it = start box, pomiary box, wyniki box
    QVBoxLayout *mainMenuBoxLayout;
    QVBoxLayout *startMenuBoxLayout;
    QVBoxLayout *pomiarMenuBoxLayout;
    QVBoxLayout *resultsMenuBoxLayout;


    Chart *currentWaveChart;

    //OBJECTS

    QPushButton *connectButton;
    QPushButton *loadButton;
    QPushButton *saveButton;

    QLabel *channelsLabel;
    QComboBox *channelsComboBox;
    QStringList *channelsStringList;

    QLabel *samplingLabel;
    QComboBox *samplingComboBox;
    QStringList *samplingStringList;

    QLabel *timeLabel;
    QComboBox *timeComboBox;
    QStringList *timeStringList;

    QLabel *rangeLabel;
    QComboBox *rangeComboBox;
    QStringList *rangeStringList;

    QLabel *howStartLabel;
    QComboBox *howStartComboBox;
    QStringList *howStartStringList;

    QLabel *currentRMSDescribeLabel;
    QLabel *currentRMSLabel;

    QLabel *currentImaxDescribeLabel;
    QLabel *currentImaxLabel;

    QLabel *currentIminDescribeLabel;
    QLabel *currentIminLabel;

};

#endif // RECORDERWINDOW_H
