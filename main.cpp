#include <QApplication>

#include <QStackedLayout>
#include<QComboBox>
#include<QObject>
#include<QLayout>
#include<QWidget>
#include<QPushButton>

#include "recorderwindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

//    layout lay;
    RecorderWindow *tabW = new RecorderWindow;

   //    QWidget *w = new QWidget();

        // Set the grid layout as a main layout

        tabW->mainWindowTabWidget->setMinimumSize(1100,700);

        // Window title
       tabW->mainWindowTabWidget->setWindowTitle("Rejestrator v.beta");

        // Display
        tabW->mainWindowTabWidget->show();


    return a.exec();
}
