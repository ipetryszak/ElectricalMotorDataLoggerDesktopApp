#ifndef LAYOUT_H
#define LAYOUT_H

#include <QStackedLayout>
#include<QComboBox>
#include<QObject>
#include<QLayout>
#include<QWidget>
#include<QPushButton>
#include<QGridLayout>

class layout :QObject
{
    Q_OBJECT
public:
    layout();

    QVBoxLayout *mainLayout;
    QStackedLayout *stackedLayout;
    QWidget *firstPageWidget;
    QWidget *secondPageWidget;
    QWidget *thirdPageWidget;
};

#endif // LAYOUT_H
