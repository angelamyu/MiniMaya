/********************************************************************************
** Form generated from reading UI file 'extrudedialog.ui'
**
** Created: Thu Apr 26 10:34:12 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTRUDEDIALOG_H
#define UI_EXTRUDEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include "linetextwrapper.h"

QT_BEGIN_NAMESPACE

class Ui_SetDistance
{
public:
    lineTextWrapper *lineEdit_3;
    QLabel *label;
    QPushButton *pushButton_9;
    QPushButton *pushButton_11;

    void setupUi(QDialog *SetDistance)
    {
        if (SetDistance->objectName().isEmpty())
            SetDistance->setObjectName(QString::fromUtf8("SetDistance"));
        SetDistance->resize(244, 197);
        lineEdit_3 = new lineTextWrapper(SetDistance);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(30, 40, 151, 21));
        lineEdit_3->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));
        label = new QLabel(SetDistance);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 111, 16));
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 89);\n"
"font: 75 10pt \"Leelawadee\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"font-weight:bold"));
        pushButton_9 = new QPushButton(SetDistance);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(20, 80, 81, 31));
        pushButton_9->setStyleSheet(QString::fromUtf8("color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #600000, stop: 0.1 #c00000, stop: 0.49 #ff0000, stop: 0.5 #700000, stop: 1 #600000);\n"
"border-width: 1px;\n"
"border-color: #fff;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 10px;\n"
"font-weight:bold;\n"
"padding-left: 5px;\n"
"padding-right: 5px;"));
        pushButton_11 = new QPushButton(SetDistance);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(110, 80, 81, 31));
        pushButton_11->setStyleSheet(QString::fromUtf8("color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #600000, stop: 0.1 #c00000, stop: 0.49 #ff0000, stop: 0.5 #700000, stop: 1 #600000);\n"
"border-width: 1px;\n"
"border-color: #fff;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 10px;\n"
"font-weight:bold;\n"
"padding-left: 5px;\n"
"padding-right: 5px;"));

        retranslateUi(SetDistance);
        QObject::connect(pushButton_9, SIGNAL(clicked()), SetDistance, SLOT(accept()));
        QObject::connect(pushButton_11, SIGNAL(clicked()), SetDistance, SLOT(reject()));
        QObject::connect(pushButton_9, SIGNAL(clicked()), lineEdit_3, SLOT(gotDistance()));
        QObject::connect(lineEdit_3, SIGNAL(signalDistance(float)), SetDistance, SLOT(signalDist(float)));

        QMetaObject::connectSlotsByName(SetDistance);
    } // setupUi

    void retranslateUi(QDialog *SetDistance)
    {
        SetDistance->setWindowTitle(QApplication::translate("SetDistance", "Set Distance", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SetDistance", "Set Distance", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QApplication::translate("SetDistance", "Ok", 0, QApplication::UnicodeUTF8));
        pushButton_11->setText(QApplication::translate("SetDistance", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SetDistance: public Ui_SetDistance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTRUDEDIALOG_H
