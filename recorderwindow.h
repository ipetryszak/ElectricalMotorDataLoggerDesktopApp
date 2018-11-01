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
#include <QAbstractAxis>

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
    void paintSamples();
public:
    RecorderWindow();

    QLineSeries *series;
    SerialPort *device;
    QStatusBar *statusBar;



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

    QLabel *samplingFrequencyDescribeLabel;
    QLabel *samplingFrequencyLabel;

    QLabel *currentRMSDescribeLabel;
    QLabel *currentRMSLabel;

    QLabel *currentImaxDescribeLabel;
    QLabel *currentImaxLabel;

    QLabel *currentIminDescribeLabel;
    QLabel *currentIminLabel;

};

#endif // RECORDERWINDOW_H
