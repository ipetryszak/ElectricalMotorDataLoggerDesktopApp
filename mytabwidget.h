#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QTabWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineSeries>
#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>
#include <QRect>
#include <QLabel>
#include <QComboBox>
#include<QGroupBox>

#include "chart.h"
#include "chartview.h"

class MyTabWidget
{
public:
    MyTabWidget();




    QTabWidget *myTab;
    QGridLayout *mainFirstTab;
    QWidget *firstPageWidget;
    QWidget *secondPageWidget;



    QPushButton *ConnectButton;
    QPushButton *loadButton;
    QPushButton *saveButton;
    Chart *chart;

    //tempry
    QVBoxLayout *MainVerticalBoxLayout;
    QVBoxLayout *StartVerticalBoxLayout;
    QVBoxLayout *VerticalBoxLayout;
    QVBoxLayout *ResultsVerticalBoxLayout;


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

#endif // MYTABWIDGET_H
