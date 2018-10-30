#include <QApplication>

#include <QStackedLayout>
#include<QComboBox>
#include<QObject>
#include<QLayout>
#include<QWidget>
#include<QPushButton>

#include "layout.h"
#include "mytabwidget.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

//    layout lay;
    MyTabWidget *tabW = new MyTabWidget;

   //    QWidget *w = new QWidget();

        // Set the grid layout as a main layout

        tabW->myTab->setMinimumSize(1100,700);

        // Window title
       tabW->myTab->setWindowTitle("Rejestrator v.beta");

        // Display
        tabW->myTab->show();


    return a.exec();
}
