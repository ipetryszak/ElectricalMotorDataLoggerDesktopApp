#include "recorderwindow.h"

RecorderWindow::RecorderWindow()
{
    device = new SerialPort;
    statusBar = new QStatusBar;
    statusBar->setAutoFillBackground(1);

    connect(device,SIGNAL(gotSample()),this,SLOT(paintSamples()));

    //widgets with individual pages, MainWindowTabWidget consists of that
    recordPageWidget = new QWidget;
    fftPageWidget = new QWidget;

    //widget that cover all window space, divides it on record and fft area
    mainWindowTabWidget = new QTabWidget;
    mainWindowTabWidget->addTab(recordPageWidget,"Rejestracja");
    mainWindowTabWidget->addTab(fftPageWidget,"Analiza FFT");

    //Main Grid Layout, parent->recordPageWidget, contains left menu and right chart
    mainRecordLayout = new QGridLayout;
    mainRecordLayout->setColumnMinimumWidth(0,140);

//-------------------------------------------------------------------------------------
//------------------------------ BEGIN OF LEFT MENU -----------------------------------
//-------------------------------------------------------------------------------------

    //QVBoxLayout that holds start, pomiary, wyniki QVBoxLayouts
    mainMenuBoxLayout = new QVBoxLayout;


//---------------- start of start position -----------------------------------

    //first GroupBox in left menu, contains QVBoxLayot and widgets - buttons
    startGroupBox = new QGroupBox("Start");
    startGroupBox->setContentsMargins(20,20,20,20);
    //contains all widgets, parent = startGroupBox, because i cant add directly widgets to QGroupBox
    startMenuBoxLayout = new QVBoxLayout;
    startMenuBoxLayout->setContentsMargins(0,5,0,0);

            //objects

            connectButton = new QPushButton;
            connectButton->setText("Połącz");
            connect(connectButton,SIGNAL(clicked(bool)),device,SLOT(connectWithDevice()));
            connect(device,SIGNAL(connected()),this,SLOT(connectedChanged()));
            connect(device,SIGNAL(noConnected()),this,SLOT(noConnectedChanged()));
            connect(device,SIGNAL(disconnectedCorrectly()),this,SLOT(disconnectedCorrectlyChanged()));

            loadButton = new QPushButton;
            loadButton->setText("Wczytaj");
            saveButton = new QPushButton;
            saveButton->setText("Zapisz");

    //add objects to startMenuBoxLayout //QVBoxLayout
    startMenuBoxLayout->addWidget(connectButton);
    startMenuBoxLayout->addWidget(loadButton);
    startMenuBoxLayout->addWidget(saveButton);

    //add made up layout to startGroupBox widget
     startGroupBox->setLayout(startMenuBoxLayout);

     //add startgroupBox to left menu start layout
     mainMenuBoxLayout->addWidget(startGroupBox);

//------------------ end of start position ----------------------------
//---------------------------------------------------------------------
//------------------ start of pomiary position ------------------------

     pomiarGroupBox = new QGroupBox("Pomiar");
     pomiarGroupBox->setContentsMargins(20,20,20,20);

     pomiarMenuBoxLayout = new QVBoxLayout;
     pomiarMenuBoxLayout->setContentsMargins(0,0,0,0);
     pomiarMenuBoxLayout->addSpacing(10);

     //----- start of channels position ------------------

           channelsLabel = new QLabel;
           channelsComboBox = new QComboBox;
           channelsStringList = new QStringList;

           channelsLabel->setText("Kanał");
           channelsStringList->append("CH1");
           channelsStringList->append("CH2");
           channelsStringList->append("CH1 i CH2");

           channelsComboBox->addItems(*channelsStringList);
           connect(channelsComboBox,SIGNAL(activated(int)),this,SLOT(channelChanged()));

    //----- end of channels position ----------------------

    //----- start of częstotliwość próbkowania position----

           samplingLabel = new QLabel;
           samplingComboBox = new QComboBox;
           samplingStringList = new QStringList;

           samplingLabel->setText("Częstotliwość próbkowania");
           samplingStringList->append("1 kHz");
           samplingStringList->append("2 kHz");
           samplingStringList->append("3 kHz");
           samplingStringList->append("4 kHz");
           samplingStringList->append("5 kHz");
           samplingStringList->append("6 kHz");
           samplingStringList->append("7 kHz");
           samplingStringList->append("8 kHz");
           samplingStringList->append("9 kHz");
           samplingStringList->append("10 kHz");

           samplingComboBox->addItems(*samplingStringList);
           connect(samplingComboBox,SIGNAL(activated(int)),this,SLOT(samplingChanged()));

    //----- end of częstotliwość próbkowania position -----

    //----- start of czas próbkowania position ------------

           timeLabel = new QLabel;
           timeComboBox = new QComboBox;
           timeStringList = new QStringList;

           timeLabel->setText("Czas próbkowania");
           timeStringList->append("1 s");
           timeStringList->append("2 s");
           timeStringList->append("3 s");
           timeStringList->append("4 s");
           timeStringList->append("5 s");
           timeStringList->append("6 s");
           timeStringList->append("7 s");
           timeStringList->append("8 s");
           timeStringList->append("9 s");
           timeStringList->append("10 s");

           timeComboBox->addItems(*timeStringList);
           connect(timeComboBox,SIGNAL(activated(int)),this,SLOT(timeChanged()));

     //---- end of czas próbkowania position --------------

     //---- start of zakres position ----------------------

           rangeLabel = new QLabel;
           rangeComboBox = new QComboBox;
           rangeStringList = new QStringList;

           rangeLabel->setText("Zakres ");
           rangeStringList->append("1 mV/A");
           rangeStringList->append("10 mV/A");
           rangeStringList->append("100 mV/A");

           connect(rangeComboBox,SIGNAL(activated(int)),this,SLOT(rangeChanged()));
           rangeComboBox->addItems(*rangeStringList);

     //---- end of zakres position -----------------------

    //---- start of tryb pomiaru -------------------------

           howStartLabel = new QLabel;
           howStartComboBox = new QComboBox;
           howStartStringList = new QStringList;

           howStartLabel->setText("Tryb pomiaru ");
           howStartStringList->append("");
           howStartStringList->append("START");
           howStartStringList->append("Zbocze narastające");


           howStartComboBox->addItems(*howStartStringList);

           connect(howStartComboBox,SIGNAL(activated(int)),this,SLOT(howStartChanged()));

     //------ end of tryb pomiaru --------------------------


    pomiarMenuBoxLayout->addWidget(channelsLabel);
    pomiarMenuBoxLayout->addWidget(channelsComboBox);
    pomiarMenuBoxLayout->addWidget(samplingLabel);
    pomiarMenuBoxLayout->addWidget(samplingComboBox);
    pomiarMenuBoxLayout->addWidget(timeLabel);
    pomiarMenuBoxLayout->addWidget(timeComboBox);
    pomiarMenuBoxLayout->addWidget(rangeLabel);
    pomiarMenuBoxLayout->addWidget(rangeComboBox);
    pomiarMenuBoxLayout->addWidget(howStartLabel);
    pomiarMenuBoxLayout->addWidget(howStartComboBox);

    pomiarGroupBox->setLayout(pomiarMenuBoxLayout);

    mainMenuBoxLayout->addWidget(pomiarGroupBox);

//----- end of pomiary position in main menu --------------
//---------------------------------------------------------
//----- start of wyniki position in main menu -------------

    resultsGroupBox = new QGroupBox("Wyniki");
    resultsGroupBox ->setContentsMargins(20,20,20,20);

    resultsMenuBoxLayout = new QVBoxLayout;
    resultsMenuBoxLayout->setContentsMargins(0,0,0,0);
    resultsMenuBoxLayout->addSpacing(10);

    //--start of SamplingFrequency--------------------------

        samplingFrequencyDescribeLabel = new QLabel;
        samplingFrequencyLabel = new QLabel;

        samplingFrequencyDescribeLabel ->setText("Częstotliwość próbkowania");

        samplingFrequencyLabel->setText(" ");
        samplingFrequencyLabel->setAutoFillBackground(1);

    //--start of Irms --------------------------

        currentRMSDescribeLabel = new QLabel;
        currentRMSLabel = new QLabel;

        currentRMSDescribeLabel ->setText("Irms");

        currentRMSLabel->setText(" ");
        currentRMSLabel->setAutoFillBackground(1);

     //-- end of Irms --------------------------

     //-- start of Imax ------------------------

        currentImaxDescribeLabel = new QLabel;
        currentImaxLabel = new QLabel;

        currentImaxDescribeLabel->setText("Imax");
        currentImaxLabel->setText(" ");
        currentImaxLabel->setAutoFillBackground(1);

     //-- end of Imax --------------------------

     //-- start of Imin ------------------------

        currentIminDescribeLabel = new QLabel;
        currentIminLabel = new QLabel;

        currentIminDescribeLabel->setText("Imin");
        currentIminLabel->setText(" ");
        currentIminLabel->setAutoFillBackground(1);

     //-- end of Imin --------------------------


    resultsMenuBoxLayout->addWidget(samplingFrequencyDescribeLabel);
    resultsMenuBoxLayout->addWidget(samplingFrequencyLabel);
    resultsMenuBoxLayout->addWidget(currentRMSDescribeLabel);
    resultsMenuBoxLayout->addWidget(currentRMSLabel);
    resultsMenuBoxLayout->addWidget(currentImaxDescribeLabel);
    resultsMenuBoxLayout->addWidget(currentImaxLabel);
    resultsMenuBoxLayout->addWidget(currentIminDescribeLabel);
    resultsMenuBoxLayout->addWidget(currentIminLabel);

    resultsGroupBox->setLayout(resultsMenuBoxLayout);

    mainMenuBoxLayout->addWidget(resultsGroupBox);

//---------------------------------------------------------------------------
//--------------------------- END OF LEFT MENU ------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//--------------------------- START OF CHART AREA ---------------------------
//---------------------------------------------------------------------------

    chart = new Chart();
    series = new QLineSeries();
    series2 = new QLineSeries;
    chart->addSeries(series);
    chart->addSeries(series2);
    chart->setTitle("PRZEBIEG PRĄDOWY i=f(t) ZAREJESTROWANEGO SYGNAŁU");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->axisY()->setRange(-500,500);
    chart->axisX()->setRange(0,0.2);
    chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

//---------------------------------------------------------------------------
//-------------------------- END OF CHART AREA ------------------------------
//---------------------------------------------------------------------------

// added left menu and chart to grid layout and nextly to tab widget
    mainRecordLayout->addLayout(mainMenuBoxLayout,0,0,1,1,Qt::AlignTop);
    mainRecordLayout->addWidget(chartView,0,1,1,1);
    mainRecordLayout->addWidget(statusBar,2,0,1,2);

    statusBar->showMessage("Ready");
    recordPageWidget->setLayout(mainRecordLayout);
}


void RecorderWindow::connectedChanged()
{
    connectButton->setText("Rozłącz");
    statusBar->showMessage("Znaleziono urządzenie i połączono");
}
void RecorderWindow::noConnectedChanged()
{
    connectButton->setText("Połącz");
    statusBar->showMessage("Nie znaleziono urządzenia - podłącz urządzenie i spróbuj ponownie");
}

void RecorderWindow::disconnectedCorrectlyChanged()
{
    connectButton->setText("Połącz");
    statusBar->showMessage("Rozłączono urządzenie - kliknij połącz aby połączyć ponownie");
}

void RecorderWindow::channelChanged()
{

    QStringList channels = {"C1!","C2!","C3!"};
    device->send(channels.at(channelsComboBox->currentIndex()));
}

void RecorderWindow::rangeChanged()
{
    currentRange = rangeComboBox->currentIndex();
}

void RecorderWindow::samplingChanged()
{
    QStringList sampling = {"F0!","F1!","F2!","F3!","F4!","F5!","F6!","F7!","F8!","F9!"};
    device->send(sampling.at(samplingComboBox->currentIndex()));
    device->samplingFrequency = (samplingComboBox->currentIndex()+1)*1000;
    QString tmp;
    tmp.append(QString::number(device->samplingFrequency,10));
    tmp.append(" Hz");
    samplingFrequencyLabel->setText(tmp);

}

void RecorderWindow::timeChanged()
{
    QStringList time = {"T0!","T1!","T2!","T3!","T4!","T5!","T6!","T7!","T8!","T9!"};
    device->send(time.at(timeComboBox->currentIndex()));
}

void RecorderWindow::howStartChanged()
{
    QStringList start = {"","S1!","S2!"};
    device->send(start.at(howStartComboBox->currentIndex()));
}

void RecorderWindow::paintSamples()
{

    series->clear();
    series2->clear();
    chart->removeSeries(series);
    chart->removeSeries(series2);

    qreal step = 0;
    qreal x=0;
    if(channelsComboBox->currentIndex() == 0 | channelsComboBox->currentIndex() == 1)
    {
        int divideFactor=1;
        if(currentRange==0)divideFactor=1;
        if(currentRange==1)divideFactor=10;
        if(currentRange==2)divideFactor=100;
        if(device->samplingFrequency!=0)step = (1/(qreal)(device->samplingFrequency));

        for (int i = 0; i < device->samplesIntVector.size(); i++)
        {
            QPointF p(x+=step, ((qreal)(device->samplesIntVector[i]-1080))/(divideFactor));
            series->append(p);
        }
    }
    else if(channelsComboBox->currentIndex()==2)
    {
        if(device->samplingFrequency!=0)step = (1/(qreal)((device->samplingFrequency)));
        for (int i = 0; i < device->samplesIntVector.size()-1; i+=2)
        {
            QPointF p(x+=step, device->samplesIntVector[i]/10);
            QPointF r(x,device->samplesIntVector[i+1]/10);
            series->append(p);
            series2->append(r);
        }
    }



    chart->addSeries(series);
    chart->addSeries(series2);

    chart->createDefaultAxes();

    if(currentRange==1)
    {
        chart->axisY()->setRange(-80,80);
        chart->axisX()->setRange(0,0.2);
    }
    if(currentRange==2)
    {
        chart->axisY()->setRange(-20,20);
        chart->axisX()->setRange(0,0.2);
    }

}
