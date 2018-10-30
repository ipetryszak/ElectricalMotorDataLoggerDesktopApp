#include "layout.h"

layout::layout()
{

        firstPageWidget = new QWidget;
        secondPageWidget = new QWidget;
        thirdPageWidget = new QWidget;



      QPushButton *button = new QPushButton;
      button->setText("elo");

      QGridLayout *laj = new QGridLayout;
      laj->addWidget(button,0,0,1,1);


      secondPageWidget->setLayout(laj);


      QStackedLayout *stackedLayout = new QStackedLayout;
      stackedLayout->addWidget(firstPageWidget);
      stackedLayout->addWidget(secondPageWidget);
      stackedLayout->addWidget(thirdPageWidget);

      mainLayout = new QVBoxLayout;
      mainLayout->addLayout(stackedLayout);


      QComboBox *pageComboBox = new QComboBox;
       pageComboBox->addItem(("Page 1"));

       pageComboBox->addItem(("Page 2"));
       pageComboBox->addItem(("Page 3"));

       mainLayout->addWidget(pageComboBox);


       connect(pageComboBox, SIGNAL(activated(int)),
               stackedLayout, SLOT(setCurrentIndex(int)));
   }
