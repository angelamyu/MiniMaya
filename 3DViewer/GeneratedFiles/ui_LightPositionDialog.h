/********************************************************************************
** Form generated from reading UI file 'LightPositionDialog.ui'
**
** Created: Fri Apr 20 01:55:51 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIGHTPOSITIONDIALOG_H
#define UI_LIGHTPOSITIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *LightPosition;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(231, 139);
        Dialog->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.5, y1:0.165, x2:0.471909, y2:1, stop:0.329545 rgba(191, 189, 255, 255), stop:1 rgba(229, 229, 229, 255));"));
        LightPosition = new QDialogButtonBox(Dialog);
        LightPosition->setObjectName(QString::fromUtf8("LightPosition"));
        LightPosition->setGeometry(QRect(-20, 90, 221, 41));
        LightPosition->setStyleSheet(QString::fromUtf8("color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #600000, stop: 0.1 #c00000, stop: 0.49 #ff0000, stop: 0.5 #700000, stop: 1 #600000);\n"
""));
        LightPosition->setOrientation(Qt::Horizontal);
        LightPosition->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 141, 16));
        label->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"font: 75 10pt \"Leelawadee\";\n"
"font-weight:bold;\n"
"color: rgb(25, 13, 45);"));
        lineEdit = new QLineEdit(Dialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 60, 191, 21));
        lineEdit->setStyleSheet(QString::fromUtf8("border-width: 1px; \n"
"border-style: inset; \n"
"border-color: #535353; \n"
"border-radius: 9px; \n"
"background-color: rgb(0, 0, 0);\n"
"color:rgb(255, 255, 255)"));

        retranslateUi(Dialog);
        QObject::connect(LightPosition, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(LightPosition, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "Change Light Position", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIGHTPOSITIONDIALOG_H
