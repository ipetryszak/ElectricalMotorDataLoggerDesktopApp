#include "recorderwindow.h"

RecorderWindow::RecorderWindow()
{

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

     //---- end of czas próbkowania position --------------

     //---- start of zakres position ----------------------

           rangeLabel = new QLabel;
           rangeComboBox = new QComboBox;
           rangeStringList = new QStringList;

           rangeLabel->setText("Zakres ");
           rangeStringList->append("1 mV/A");
           rangeStringList->append("10 mV/A");
           rangeStringList->append("100 mV/A");

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

    currentWaveChart = new Chart();
    QLineSeries *series = new QLineSeries();

    for (int i = 0; i < 500; i++) {
        QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
        p.ry() += QRandomGenerator::global()->bounded(20);
        *series << p;
    }

    currentWaveChart->addSeries(series);
    currentWaveChart->setTitle("PRZEBIEG PRĄDOWY i=f(t) ZAREJESTROWANEGO SYGNAŁU");
    currentWaveChart->setAnimationOptions(QChart::SeriesAnimations);
    currentWaveChart->legend()->hide();
    currentWaveChart->createDefaultAxes();

    ChartView *chartView = new ChartView(currentWaveChart);
    chartView->setRenderHint(QPainter::Antialiasing);

//---------------------------------------------------------------------------
//-------------------------- END OF CHART AREA ------------------------------
//---------------------------------------------------------------------------

// added left menu and chart to grid layout and nextly to tab widget
    mainRecordLayout->addLayout(mainMenuBoxLayout,0,0,1,1,Qt::AlignTop);
    mainRecordLayout->addWidget(chartView,0,1);
    recordPageWidget->setLayout(mainRecordLayout);
}
