#include "mytabwidget.h"

MyTabWidget::MyTabWidget()
{

    myTab = new QTabWidget;

    firstPageWidget = new QWidget;
    secondPageWidget = new QWidget;

    myTab->addTab(firstPageWidget,"Rejestracja");
    myTab->addTab(secondPageWidget,"Analiza FFT");

    mainFirstTab = new QGridLayout;


    //temporary
    ConnectButton = new QPushButton;
    ConnectButton->setText("Połącz");
    loadButton = new QPushButton;
    loadButton->setText("Wczytaj");
    saveButton = new QPushButton;
    saveButton->setText("Zapisz");

    MainVerticalBoxLayout = new QVBoxLayout;
    VerticalBoxLayout = new QVBoxLayout;
    StartVerticalBoxLayout = new QVBoxLayout;

    VerticalBoxLayout->setContentsMargins(0,0,0,0);
    StartVerticalBoxLayout->setContentsMargins(0,5,0,0);
    StartVerticalBoxLayout->addWidget(ConnectButton);
    StartVerticalBoxLayout->addWidget(loadButton);
    StartVerticalBoxLayout->addWidget(saveButton);
    VerticalBoxLayout->addSpacing(10);



    QGroupBox *startBox = new QGroupBox("Start");
    startBox->setContentsMargins(20,20,20,20);

        startBox->setLayout(StartVerticalBoxLayout);

        MainVerticalBoxLayout->addWidget(startBox);



    channelsLabel = new QLabel;
    channelsLabel->setText("Kanał");
    VerticalBoxLayout->addWidget(channelsLabel);
    channelsComboBox = new QComboBox;
    channelsStringList = new QStringList;


    channelsStringList->append("CH1");
    channelsStringList->append("CH2");
    channelsStringList->append("CH1 i CH2");

    channelsComboBox->addItems(*channelsStringList);

    VerticalBoxLayout->addWidget(channelsComboBox);


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
    VerticalBoxLayout->addWidget(samplingLabel);
    VerticalBoxLayout->addWidget(samplingComboBox);

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
    VerticalBoxLayout->addWidget(timeLabel);
    VerticalBoxLayout->addWidget(timeComboBox);

    rangeLabel = new QLabel;
    rangeComboBox = new QComboBox;
    rangeStringList = new QStringList;

    rangeLabel->setText("Zakres ");
    rangeStringList->append("1 mV/A");
    rangeStringList->append("10 mV/A");
    rangeStringList->append("100 mV/A");

    rangeComboBox->addItems(*rangeStringList);
    VerticalBoxLayout->addWidget(rangeLabel);
    VerticalBoxLayout->addWidget(rangeComboBox);


    howStartLabel = new QLabel;
    howStartComboBox = new QComboBox;
    howStartStringList = new QStringList;

    howStartLabel->setText("Tryb pomiaru ");
    howStartStringList->append("");
    howStartStringList->append("START");
    howStartStringList->append("Zbocze narastające");


    howStartComboBox->addItems(*howStartStringList);
    VerticalBoxLayout->addWidget(howStartLabel);
    VerticalBoxLayout->addWidget(howStartComboBox);



QGroupBox *samplingConf = new QGroupBox("Pomiar");
samplingConf->setContentsMargins(20,20,20,20);

    samplingConf->setLayout(VerticalBoxLayout);

    mainFirstTab->setColumnMinimumWidth(0,140);

    MainVerticalBoxLayout->addWidget(samplingConf);



    ResultsVerticalBoxLayout = new QVBoxLayout;

    currentRMSDescribeLabel = new QLabel;
    currentRMSLabel = new QLabel;

    currentRMSDescribeLabel ->setText("Irms");
    currentRMSLabel->setText(" ");
    currentRMSLabel->setAutoFillBackground(1);

    currentImaxDescribeLabel = new QLabel;
    currentImaxLabel = new QLabel;
    currentIminDescribeLabel = new QLabel;
    currentIminLabel = new QLabel;

    currentImaxDescribeLabel->setText("Imax");
    currentImaxLabel->setText(" ");
    currentImaxLabel->setAutoFillBackground(1);

    currentIminDescribeLabel->setText("Imin");
    currentIminLabel->setText(" ");
    currentIminLabel->setAutoFillBackground(1);

    ResultsVerticalBoxLayout->addWidget(currentRMSDescribeLabel);
    ResultsVerticalBoxLayout->addWidget(currentRMSLabel);

    ResultsVerticalBoxLayout->addWidget(currentImaxDescribeLabel);
    ResultsVerticalBoxLayout->addWidget(currentImaxLabel);

    ResultsVerticalBoxLayout->addWidget(currentIminDescribeLabel);
    ResultsVerticalBoxLayout->addWidget(currentIminLabel);



    QGroupBox *results = new QGroupBox("Wyniki");
    results->setContentsMargins(20,20,20,20);
    results->setLayout(ResultsVerticalBoxLayout);


    MainVerticalBoxLayout->addWidget(results);




    mainFirstTab->addLayout(MainVerticalBoxLayout,0,0,1,1,Qt::AlignTop);






    chart = new Chart();
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < 500; i++) {
        QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
        p.ry() += QRandomGenerator::global()->bounded(20);
        *series << p;

    }

    chart->addSeries(series);
    chart->setTitle("PRZEBIEG PRĄDOWY i=f(t) ZAREJESTROWANEGO SYGNAŁU");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->createDefaultAxes();



    ChartView *chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

mainFirstTab->addWidget(chartView,0,1);

   firstPageWidget->setLayout(mainFirstTab);


}
