/********************************************************************************
** Form generated from reading UI file 'sonMain.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SONMAIN_H
#define UI_SONMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sonMain
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer;
    QLineEdit *aFilename;
    QLineEdit *aMD5;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *bFilename;
    QLineEdit *bMD5;

    void setupUi(QWidget *sonMain)
    {
        if (sonMain->objectName().isEmpty())
            sonMain->setObjectName(QString::fromUtf8("sonMain"));
        sonMain->resize(400, 300);
        gridLayout_2 = new QGridLayout(sonMain);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(sonMain);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 0, 1, 1);

        aFilename = new QLineEdit(groupBox);
        aFilename->setObjectName(QString::fromUtf8("aFilename"));

        gridLayout_3->addWidget(aFilename, 0, 0, 1, 1);

        aMD5 = new QLineEdit(groupBox);
        aMD5->setObjectName(QString::fromUtf8("aMD5"));

        gridLayout_3->addWidget(aMD5, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(sonMain);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_2, 2, 0, 1, 1);

        bFilename = new QLineEdit(groupBox_2);
        bFilename->setObjectName(QString::fromUtf8("bFilename"));

        gridLayout_4->addWidget(bFilename, 0, 0, 1, 1);

        bMD5 = new QLineEdit(groupBox_2);
        bMD5->setObjectName(QString::fromUtf8("bMD5"));

        gridLayout_4->addWidget(bMD5, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(sonMain);

        QMetaObject::connectSlotsByName(sonMain);
    } // setupUi

    void retranslateUi(QWidget *sonMain)
    {
        sonMain->setWindowTitle(QApplication::translate("sonMain", "sonMain", nullptr));
        groupBox->setTitle(QApplication::translate("sonMain", "\346\226\207\344\273\266A", nullptr));
        groupBox_2->setTitle(QApplication::translate("sonMain", "\346\226\207\344\273\266B", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sonMain: public Ui_sonMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SONMAIN_H
