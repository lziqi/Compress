/********************************************************************************
** Form generated from reading UI file 'imgCompress.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMGCOMPRESS_H
#define UI_IMGCOMPRESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_imgCompressClass
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QProgressBar *progressBar;
    QSpacerItem *verticalSpacer;
    QPushButton *md5Button;

    void setupUi(QWidget *imgCompressClass)
    {
        if (imgCompressClass->objectName().isEmpty())
            imgCompressClass->setObjectName(QString::fromUtf8("imgCompressClass"));
        imgCompressClass->resize(388, 337);
        gridLayout = new QGridLayout(imgCompressClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(imgCompressClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        progressBar = new QProgressBar(groupBox);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        gridLayout_2->addWidget(progressBar, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 258, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 1, 1, 1);

        md5Button = new QPushButton(groupBox);
        md5Button->setObjectName(QString::fromUtf8("md5Button"));

        gridLayout_2->addWidget(md5Button, 2, 1, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(imgCompressClass);

        QMetaObject::connectSlotsByName(imgCompressClass);
    } // setupUi

    void retranslateUi(QWidget *imgCompressClass)
    {
        imgCompressClass->setWindowTitle(QApplication::translate("imgCompressClass", "imgCompress", nullptr));
        groupBox->setTitle(QString());
        md5Button->setText(QApplication::translate("imgCompressClass", "\346\240\241\351\252\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class imgCompressClass: public Ui_imgCompressClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMGCOMPRESS_H
