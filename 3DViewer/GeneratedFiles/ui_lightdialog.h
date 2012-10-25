/********************************************************************************
** Form generated from reading UI file 'lightdialog.ui'
**
** Created: Thu Apr 26 10:34:12 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIGHTDIALOG_H
#define UI_LIGHTDIALOG_H

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

class Ui_Dialog
{
public:
    lineTextWrapper *lineEdit_3;
    QPushButton *pushButton_9;
    QLabel *label;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(275, 180);
        lineEdit_3 = new lineTextWrapper(Dialog);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(30, 70, 221, 31));
        lineEdit_3->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));
        pushButton_9 = new QPushButton(Dialog);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(170, 110, 81, 31));
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
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 151, 21));
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 89);\n"
"font: 75 10pt \"Leelawadee\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"font-weight:bold"));

        retranslateUi(Dialog);
        QObject::connect(pushButton_9, SIGNAL(clicked()), Dialog, SLOT(accept()));
        QObject::connect(pushButton_9, SIGNAL(clicked()), lineEdit_3, SLOT(gotClickedLightPos()));
        QObject::connect(lineEdit_3, SIGNAL(signalLightPos(QString)), Dialog, SLOT(getPos(QString)));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QApplication::translate("Dialog", "Ok", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "Change Light Position", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIGHTDIALOG_H
