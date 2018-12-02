#ifndef RECORDERWINDOW_H
#define RECORDERWINDOW_H

//layout
#include <QTabWidget>
#include <QGridLayout>
#include <QVBoxLayout>
//elements
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QObject>
#include <QStatusBar>
#include <QAbstractAxis>

#include <QLineSeries>
#include <QScatterSeries>

#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>

#include "chart.h"
#include "chartview.h"
#include "serialport.h"
#include "myfft.h"
#include "files.h"
#include "currentalldata.h"



class RecorderWindow : public QObject
{
    Q_OBJECT

public slots:
    void connectedChanged();
    void noConnectedChanged();
    void channelChanged();
    void samplingChanged();
    void timeChanged();
    void startChanged();
    void disconnectedCorrectlyChanged();
    void rangeChanged();
    void loadData();
    void saveData();
    void loadReceivedSample();
    void currentMaxMinRMSChanged();

signals:
    newSample();

public:
    RecorderWindow();
    void drawSinChart(CurrentAllData *);
    void drawFFTChart(CurrentAllData *);
    void createLayout();

    CurrentAllData *currentData;

    myFFT *fftObj;
    Files *myFile;
    QLineSeries *series;
    QLineSeries *series2;

    QLineSeries *seriesFFT;
    QLineSeries *seriesFFT2;
    SerialPort *device;
    QStatusBar *statusBar;
    Chart *chart;
    ChartView *chartView;
    Chart *chartFFT;
    Chart *chartFFT2;
    ChartView *chartViewFFT;
    ChartView *chartViewFFT2;
    int currentRange=0;

    //widgets that are included by mainWindowTabWidget, contains all layout and objects
    QWidget *recordPageWidget;
    QWidget *fftPageWidget;
    //widget that cover all window space, divides it on record and fft area
    QTabWidget *mainWindowTabWidget;
    //Main Grid Layout, parent->recordPageWidget, contains left menu and right chart
    QGridLayout *mainRecordLayout;
     QGridLayout *mainFFTLayout;
    //first GroupBox in left menu, contains QVBoxLayot and widgets - buttons
    QGroupBox *startGroupBox;
    QGroupBox *pomiarGroupBox;
    QGroupBox *resultsGroupBox;

    //main MenuBoxLayout and boxes added to it = start box, pomiary box, wyniki box
    QVBoxLayout *mainMenuBoxLayout;
    QVBoxLayout *startMenuBoxLayout;
    QVBoxLayout *pomiarMenuBoxLayout;
    QVBoxLayout *resultsMenuBoxLayout;




    //OBJECTS

    QPushButton *connectButton;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *startButton;

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

    QLabel *startLabel;

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
