/********************************************************************************
** Form generated from reading UI file 'loadshader.ui'
**
** Created: Thu Apr 26 10:34:12 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADSHADER_H
#define UI_LOADSHADER_H

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

class Ui_ShaderLoader
{
public:
    lineTextWrapper *lineEdit_4;
    QLabel *label;
    QPushButton *pushButton_10;
    QPushButton *pushButton_9;

    void setupUi(QDialog *ShaderLoader)
    {
        if (ShaderLoader->objectName().isEmpty())
            ShaderLoader->setObjectName(QString::fromUtf8("ShaderLoader"));
        ShaderLoader->setWindowModality(Qt::WindowModal);
        ShaderLoader->resize(313, 202);
        lineEdit_4 = new lineTextWrapper(ShaderLoader);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(40, 70, 241, 31));
        lineEdit_4->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));
        label = new QLabel(ShaderLoader);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 151, 21));
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 89);\n"
"font: 75 10pt \"Leelawadee\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"font-weight:bold"));
        pushButton_10 = new QPushButton(ShaderLoader);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(190, 130, 81, 31));
        pushButton_10->setStyleSheet(QString::fromUtf8("color: white;\n"
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
        pushButton_9 = new QPushButton(ShaderLoader);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(100, 130, 81, 31));
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

        retranslateUi(ShaderLoader);
        QObject::connect(pushButton_9, SIGNAL(clicked()), ShaderLoader, SLOT(accept()));
        QObject::connect(pushButton_10, SIGNAL(clicked()), ShaderLoader, SLOT(reject()));
        QObject::connect(pushButton_9, SIGNAL(clicked()), lineEdit_4, SLOT(gotClickedShaderName()));
        QObject::connect(lineEdit_4, SIGNAL(signalShaderN(QString)), ShaderLoader, SLOT(signalname(QString)));

        QMetaObject::connectSlotsByName(ShaderLoader);
    } // setupUi

    void retranslateUi(QDialog *ShaderLoader)
    {
        ShaderLoader->setWindowTitle(QApplication::translate("ShaderLoader", "LoadShader", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ShaderLoader", "Load Shader", 0, QApplication::UnicodeUTF8));
        pushButton_10->setText(QApplication::translate("ShaderLoader", "Cancel", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QApplication::translate("ShaderLoader", "Load", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ShaderLoader: public Ui_ShaderLoader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADSHADER_H
