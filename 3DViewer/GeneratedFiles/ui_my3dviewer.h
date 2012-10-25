/********************************************************************************
** Form generated from reading UI file 'my3dviewer.ui'
**
** Created: Thu Apr 26 10:34:12 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MY3DVIEWER_H
#define UI_MY3DVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include "linetextwrapper.h"
#include "listwrapper.h"
#include "myglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_My3DViewerClass
{
public:
    QAction *actionLoad_Obj;
    QAction *actionPlay;
    QAction *actionStop;
    QAction *actionNew_Cube;
    QAction *actionLoad_Shader;
    QAction *actionChange_Light_Position;
    QAction *actionRemove_Vertex;
    QAction *actionSplit_Quad;
    QAction *actionAdd_Vertex;
    QAction *actionAdd_Edge;
    QAction *actionQuit;
    QAction *actionSubdivide;
    QAction *actionLoad_Obj_2;
    QAction *actionLoad_Shader_2;
    QAction *actionSave_Obj;
    QAction *actionSet_Distance;
    QAction *actionExtrude;
    QAction *actionOpen;
    QWidget *centralWidget;
    MyGLWidget *mainWindowClass;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    listWrapper *faceList;
    listWrapper *VertexList;
    QLabel *label;
    QLabel *label_2;
    listWrapper *EdgesList;
    QLabel *label_9;
    QFrame *line_2;
    QLCDNumber *lcdNumber;
    QLCDNumber *lcdNumber_2;
    QLCDNumber *lcdNumber_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_12;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QPushButton *showBox_button;
    QPushButton *hideBox_button;
    QWidget *Deform;
    QPushButton *pushButton_20;
    QPushButton *pushButton_21;
    QSpinBox *spinBox_4;
    QLabel *label_6;
    QTabWidget *tabWidget_2;
    QWidget *EditMesh;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QWidget *Camera;
    lineTextWrapper *lineEdit;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    lineTextWrapper *lineEdit_2;
    listWrapper *listWidget;
    QLabel *label_7;
    QLabel *label_8;
    QWidget *Shader;
    lineTextWrapper *lineEdit_3;
    QPushButton *pushButton_23;
    QGroupBox *groupBox;
    QLabel *label_5;
    QSlider *horizontalSlider;
    QLabel *label_4;
    QSlider *horizontalSlider_2;
    QLabel *label_3;
    QSlider *horizontalSlider_3;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAnimate;
    QMenu *menuLighting;
    QMenu *menuEdit_Mesh;
    QMenu *menuExtrude;
    QMenu *menuDocumentations;

    void setupUi(QMainWindow *My3DViewerClass)
    {
        if (My3DViewerClass->objectName().isEmpty())
            My3DViewerClass->setObjectName(QString::fromUtf8("My3DViewerClass"));
        My3DViewerClass->resize(1005, 589);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/StarterCode/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        My3DViewerClass->setWindowIcon(icon);
        My3DViewerClass->setLayoutDirection(Qt::LeftToRight);
        My3DViewerClass->setAutoFillBackground(false);
        My3DViewerClass->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.5, y1:0.165, x2:0.471909, y2:1, stop:0.329545 rgba(191, 189, 255, 255), stop:1 rgba(229, 229, 229, 255));"));
        actionLoad_Obj = new QAction(My3DViewerClass);
        actionLoad_Obj->setObjectName(QString::fromUtf8("actionLoad_Obj"));
        actionPlay = new QAction(My3DViewerClass);
        actionPlay->setObjectName(QString::fromUtf8("actionPlay"));
        actionStop = new QAction(My3DViewerClass);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        actionNew_Cube = new QAction(My3DViewerClass);
        actionNew_Cube->setObjectName(QString::fromUtf8("actionNew_Cube"));
        actionNew_Cube->setCheckable(true);
        actionLoad_Shader = new QAction(My3DViewerClass);
        actionLoad_Shader->setObjectName(QString::fromUtf8("actionLoad_Shader"));
        actionChange_Light_Position = new QAction(My3DViewerClass);
        actionChange_Light_Position->setObjectName(QString::fromUtf8("actionChange_Light_Position"));
        actionRemove_Vertex = new QAction(My3DViewerClass);
        actionRemove_Vertex->setObjectName(QString::fromUtf8("actionRemove_Vertex"));
        actionSplit_Quad = new QAction(My3DViewerClass);
        actionSplit_Quad->setObjectName(QString::fromUtf8("actionSplit_Quad"));
        actionAdd_Vertex = new QAction(My3DViewerClass);
        actionAdd_Vertex->setObjectName(QString::fromUtf8("actionAdd_Vertex"));
        actionAdd_Edge = new QAction(My3DViewerClass);
        actionAdd_Edge->setObjectName(QString::fromUtf8("actionAdd_Edge"));
        actionQuit = new QAction(My3DViewerClass);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionSubdivide = new QAction(My3DViewerClass);
        actionSubdivide->setObjectName(QString::fromUtf8("actionSubdivide"));
        actionLoad_Obj_2 = new QAction(My3DViewerClass);
        actionLoad_Obj_2->setObjectName(QString::fromUtf8("actionLoad_Obj_2"));
        actionLoad_Shader_2 = new QAction(My3DViewerClass);
        actionLoad_Shader_2->setObjectName(QString::fromUtf8("actionLoad_Shader_2"));
        actionSave_Obj = new QAction(My3DViewerClass);
        actionSave_Obj->setObjectName(QString::fromUtf8("actionSave_Obj"));
        actionSet_Distance = new QAction(My3DViewerClass);
        actionSet_Distance->setObjectName(QString::fromUtf8("actionSet_Distance"));
        actionExtrude = new QAction(My3DViewerClass);
        actionExtrude->setObjectName(QString::fromUtf8("actionExtrude"));
        actionOpen = new QAction(My3DViewerClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        centralWidget = new QWidget(My3DViewerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        mainWindowClass = new MyGLWidget(centralWidget);
        mainWindowClass->setObjectName(QString::fromUtf8("mainWindowClass"));
        mainWindowClass->setGeometry(QRect(190, 90, 621, 471));
        mainWindowClass->setStyleSheet(QString::fromUtf8("font: 75 8pt \"Leelawadee\";"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 10, 51, 51));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-image: url(:/StarterCode/rotate_unclicked.png);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"QPushButton:pressed{\n"
"image:url(:/StarterCode/rotate_clicked.png);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
""));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(100, 10, 51, 51));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton{background-image: url(:/StarterCode/stop_unclicked.png) 200 px;\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"QPushButton:pressed{\n"
"background-image:url(:/StarterCode/stop_clicked.png);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
""));
        faceList = new listWrapper(centralWidget);
        faceList->setObjectName(QString::fromUtf8("faceList"));
        faceList->setGeometry(QRect(840, 60, 151, 91));
        faceList->setStyleSheet(QString::fromUtf8("QScrollBar::vertical{\n"
"background: white;\n"
"border: 1px gray;\n"
"}\n"
"QScrollBar::handle::vertical{\n"
"background: rgb(85, 0, 255);\n"
"min-width:20px;\n"
"}\n"
"\n"
"QScrollBar::up-arrow::vertical{\n"
"border: 2px white;\n"
"background: rgb(85, 0, 255);\n"
"width: 3px;\n"
"height: 3px \n"
"}\n"
"\n"
"QScrollBar::down-arrow::vertical{\n"
"background: rgb(85, 0, 255);\n"
"width: 3px;\n"
"height: 3px;\n"
"}\n"
"\n"
"QScrollBar::add-page::vertical, QScrollBar::sub-page::vertical{\n"
"background: gray;\n"
"}\n"
"\n"
"QListView::item:selected{\n"
"    border-radius: 5px;\n"
"    border:1px solid #999999;\n"
" \n"
"	color: rgb(255,255, 255);\n"
"	\n"
"	background-color: qlineargradient(spread:pad, x1:0.5, y1:0.165, x2:0.471909, y2:1, stop:0.329545 rgba(191, 189, 255, 255), stop:1 rgba(229, 229, 229, 255));\n"
"\n"
"}\n"
"\n"
"#faceList{\n"
"background-color: rgb(0, 0, 0);\n"
"color: rgb(255,255, 255);\n"
"}\n"
"\n"
""));
        faceList->setAutoScroll(true);
        faceList->setSelectionMode(QAbstractItemView::SingleSelection);
        VertexList = new listWrapper(centralWidget);
        VertexList->setObjectName(QString::fromUtf8("VertexList"));
        VertexList->setGeometry(QRect(840, 420, 151, 141));
        VertexList->setStyleSheet(QString::fromUtf8("QScrollBar::vertical{\n"
"background: white;\n"
"border: 1px gray;\n"
"}\n"
"QScrollBar::handle::vertical{\n"
"background: rgb(85, 0, 255);\n"
"min-width:20px;\n"
"}\n"
"\n"
"QScrollBar::up-arrow::vertical{\n"
"border: 2px white;\n"
"background: rgb(85, 0, 255);\n"
"width: 3px;\n"
"height: 3px \n"
"}\n"
"\n"
"\n"
"\n"
"#VertexList{\n"
"	background-color: rgb(0, 0, 0);\n"
"color: rgb(255,255, 255);\n"
"}"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(840, 40, 46, 13));
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 89);\n"
"font: 75 10pt \"Leelawadee\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"font-weight:bold"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(840, 400, 61, 16));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 89);\n"
"font: 75 10pt \"Leelawadee\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"font-weight:bold"));
        EdgesList = new listWrapper(centralWidget);
        EdgesList->setObjectName(QString::fromUtf8("EdgesList"));
        EdgesList->setGeometry(QRect(840, 200, 151, 171));
        EdgesList->setStyleSheet(QString::fromUtf8("QScrollBar::vertical{\n"
"background: white;\n"
"border: 1px gray;\n"
"}\n"
"QScrollBar::handle::vertical{\n"
"background: rgb(85, 0, 255);\n"
"min-width:20px;\n"
"}\n"
"\n"
"QScrollBar::up-arrow::vertical{\n"
"border: 2px white;\n"
"background: rgb(85, 0, 255);\n"
"width: 3px;\n"
"height: 3px \n"
"}\n"
"\n"
"QScrollBar::down-arrow::vertical{\n"
"background: rgb(85, 0, 255);\n"
"width: 3px;\n"
"height: 3px;\n"
"}\n"
"\n"
"QScrollBar::add-page::vertical, QScrollBar::sub-page::vertical{\n"
"background: gray;\n"
"}\n"
"QListView::item:selected{\n"
"    border-radius: 5px;\n"
"    border:1px solid #999999;\n"
" \n"
"	color: rgb(255,255, 255);\n"
"	\n"
"	background-color: qlineargradient(spread:pad, x1:0.5, y1:0.165, x2:0.471909, y2:1, stop:0.329545 rgba(191, 189, 255, 255), stop:1 rgba(229, 229, 229, 255));\n"
"\n"
"}\n"
"\n"
"\n"
"\n"
"#EdgesList{\n"
"	background-color: rgb(0, 0, 0);\n"
"color: rgb(255,255, 255);\n"
"}\n"
"\n"
"QScrollBar::horizontal{\n"
"background: white;\n"
"border: 1px gray;\n"
"}\n"
"QScroll"
                        "Bar::handle::horizontal{\n"
"background: rgb(85, 0, 255);\n"
"min-width:20px;\n"
"}\n"
"\n"
"QScrollBar::left-arrow::horizontal{\n"
"border: 2px white;\n"
"background: rgb(85, 0, 255);\n"
"width: 3px;\n"
"height: 3px \n"
"}\n"
"\n"
"QScrollBar::right-arrow::horizontal{\n"
"background: rgb(85, 0, 255);\n"
"width: 3px;\n"
"height: 3px;\n"
"}\n"
"\n"
"QScrollBar::add-page::horizontal, QScrollBar::sub-page::horizontal{\n"
"background: gray;\n"
"}"));
        EdgesList->setSelectionMode(QAbstractItemView::ExtendedSelection);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(840, 180, 81, 16));
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 89);\n"
"font: 75 10pt \"Leelawadee\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"font-weight:bold"));
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(823, 33, 3, 550));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(933, 33, 51, 20));
        lcdNumber->setAutoFillBackground(false);
        lcdNumber->setStyleSheet(QString::fromUtf8("background-color: rgba(5, 5, 5, 225);\n"
"color: rgb(37, 15, 162);\n"
""));
        lcdNumber->setNumDigits(7);
        lcdNumber_2 = new QLCDNumber(centralWidget);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(930, 170, 51, 20));
        lcdNumber_2->setAutoFillBackground(false);
        lcdNumber_2->setStyleSheet(QString::fromUtf8("background-color: rgba(5, 5, 5, 225);\n"
"color: rgb(37, 15, 162);"));
        lcdNumber_2->setNumDigits(7);
        lcdNumber_3 = new QLCDNumber(centralWidget);
        lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));
        lcdNumber_3->setGeometry(QRect(930, 390, 51, 20));
        lcdNumber_3->setAutoFillBackground(false);
        lcdNumber_3->setStyleSheet(QString::fromUtf8("background-color: rgba(5, 5, 5, 225);\n"
"color: rgb(37, 15, 162);"));
        lcdNumber_3->setNumDigits(7);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(10, 280, 171, 251));
        tabWidget->setStyleSheet(QString::fromUtf8(" QTabWidget::pane { /* The tab widget frame */\n"
"         border-top: 2px solid #C2C7CB;\n"
"     }\n"
"\n"
"     QTabWidget::tab-bar {\n"
"         left: 5px; /* move to the right by 5px */\n"
"     }\n"
"\n"
"     /* Style the tab using the tab sub-control. Note that\n"
"         it reads QTabBar _not_ QTabWidget */\n"
"     QTabBar::tab {\n"
"         background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                     stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\n"
"                                     stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\n"
"         border: 2px solid #C4C4C3;\n"
"         border-bottom-color: #C2C7CB; /* same as the pane color */\n"
"         border-top-left-radius: 4px;\n"
"         border-top-right-radius: 4px;\n"
"         min-width: 8ex;\n"
"         padding: 2px;\n"
"     }\n"
"\n"
"     QTabBar::tab:selected, QTabBar::tab:hover {\n"
"         background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                     stop: 0 #fafafa, stop"
                        ": 0.4 #f4f4f4,\n"
"                                     stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);\n"
"     }\n"
"\n"
"     QTabBar::tab:selected {\n"
"         border-color: #9B9B9B;\n"
"         border-bottom-color: #C2C7CB; /* same as pane color */\n"
"     }\n"
"\n"
"     QTabBar::tab:!selected {\n"
"         margin-top: 2px; /* make non-selected tabs look smaller */\n"
"     }\n"
"\n"
"     /* make use of negative margins for overlapping tabs */\n"
"     QTabBar::tab:selected {\n"
"         /* expand/overlap to the left and right by 4px */\n"
"         margin-left: -4px;\n"
"         margin-right: -4px;\n"
"     }\n"
"\n"
"     QTabBar::tab:first:selected {\n"
"         margin-left: 0; /* the first selected tab has nothing to overlap with on the left */\n"
"     }\n"
"\n"
"     QTabBar::tab:last:selected {\n"
"         margin-right: 0; /* the last selected tab has nothing to overlap with on the right */\n"
"     }\n"
"\n"
"     QTabBar::tab:only-one {\n"
"         margin: 0; /* if there is only one tab, we do"
                        "n't want overlapping margins */\n"
"     }"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_12 = new QLabel(tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 10, 121, 16));
        label_12->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        spinBox = new QSpinBox(tab);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(50, 50, 91, 22));
        spinBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(170, 0, 127);"));
        spinBox->setMinimum(2);
        spinBox->setMaximum(5);
        spinBox_2 = new QSpinBox(tab);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(50, 150, 91, 22));
        spinBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(170, 0, 127);"));
        spinBox_2->setMinimum(2);
        spinBox_2->setMaximum(5);
        spinBox_3 = new QSpinBox(tab);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setGeometry(QRect(50, 100, 91, 22));
        spinBox_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(170, 0, 127);"));
        spinBox_3->setMinimum(2);
        spinBox_3->setMaximum(5);
        label_13 = new QLabel(tab);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(20, 50, 16, 20));
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 89);\n"
"font: 75 10pt \"Leelawadee\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"font-weight:bold"));
        label_14 = new QLabel(tab);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(20, 100, 16, 16));
        label_14->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 89);\n"
"font: 75 10pt \"Leelawadee\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"font-weight:bold"));
        label_15 = new QLabel(tab);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(20, 150, 20, 20));
        label_15->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 89);\n"
"font: 75 10pt \"Leelawadee\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"font-weight:bold"));
        showBox_button = new QPushButton(tab);
        showBox_button->setObjectName(QString::fromUtf8("showBox_button"));
        showBox_button->setGeometry(QRect(10, 190, 61, 23));
        showBox_button->setStyleSheet(QString::fromUtf8("color: white;\n"
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
        hideBox_button = new QPushButton(tab);
        hideBox_button->setObjectName(QString::fromUtf8("hideBox_button"));
        hideBox_button->setGeometry(QRect(90, 190, 61, 23));
        hideBox_button->setStyleSheet(QString::fromUtf8("color: white;\n"
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
        tabWidget->addTab(tab, QString());
        Deform = new QWidget();
        Deform->setObjectName(QString::fromUtf8("Deform"));
        pushButton_20 = new QPushButton(Deform);
        pushButton_20->setObjectName(QString::fromUtf8("pushButton_20"));
        pushButton_20->setGeometry(QRect(40, 80, 75, 23));
        pushButton_20->setStyleSheet(QString::fromUtf8("color: white;\n"
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
        pushButton_21 = new QPushButton(Deform);
        pushButton_21->setObjectName(QString::fromUtf8("pushButton_21"));
        pushButton_21->setGeometry(QRect(40, 140, 75, 23));
        pushButton_21->setStyleSheet(QString::fromUtf8("color: white;\n"
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
        spinBox_4 = new QSpinBox(Deform);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));
        spinBox_4->setGeometry(QRect(80, 30, 42, 22));
        label_6 = new QLabel(Deform);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 30, 46, 13));
        tabWidget->addTab(Deform, QString());
        tabWidget_2 = new QTabWidget(centralWidget);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(190, 0, 621, 80));
        tabWidget_2->setStyleSheet(QString::fromUtf8("\n"
"QTabWidget::pane { /* The tab widget frame */\n"
"         border-top: 2px solid #C2C7CB;\n"
"     }\n"
"\n"
"     QTabWidget::tab-bar {\n"
"         left: 5px; /* move to the right by 5px */\n"
"     }\n"
"\n"
"     /* Style the tab using the tab sub-control. Note that\n"
"         it reads QTabBar _not_ QTabWidget */\n"
"     QTabBar::tab {\n"
"         background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                     stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\n"
"                                     stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\n"
"         border: 2px solid #C4C4C3;\n"
"         border-bottom-color: #C2C7CB; /* same as the pane color */\n"
"         border-top-left-radius: 4px;\n"
"         border-top-right-radius: 4px;\n"
"         min-width: 8ex;\n"
"         padding: 2px;\n"
"     }\n"
"\n"
"     QTabBar::tab:selected, QTabBar::tab:hover {\n"
"         background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                     stop: 0 #fafafa, "
                        "stop: 0.4 #f4f4f4,\n"
"                                     stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);\n"
"     }\n"
"\n"
"     QTabBar::tab:selected {\n"
"         border-color: #9B9B9B;\n"
"         border-bottom-color: #C2C7CB; /* same as pane color */\n"
"     }\n"
"\n"
"     QTabBar::tab:!selected {\n"
"         margin-top: 2px; /* make non-selected tabs look smaller */\n"
"     }\n"
"\n"
"     /* make use of negative margins for overlapping tabs */\n"
"     QTabBar::tab:selected {\n"
"         /* expand/overlap to the left and right by 4px */\n"
"         margin-left: -4px;\n"
"         margin-right: -4px;\n"
"     }\n"
"\n"
"     QTabBar::tab:first:selected {\n"
"         margin-left: 0; /* the first selected tab has nothing to overlap with on the left */\n"
"     }\n"
"\n"
"     QTabBar::tab:last:selected {\n"
"         margin-right: 0; /* the last selected tab has nothing to overlap with on the right */\n"
"     }\n"
"\n"
"     QTabBar::tab:only-one {\n"
"         margin: 0; /* if there is only one tab, w"
                        "e don't want overlapping margins */\n"
"     }\n"
"\n"
""));
        EditMesh = new QWidget();
        EditMesh->setObjectName(QString::fromUtf8("EditMesh"));
        pushButton_6 = new QPushButton(EditMesh);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(0, 0, 61, 51));
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"image: url(:/StarterCode/delete_unclicked.png);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"image: url(:/StarterCode/delete_clicked.png);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"\n"
""));
        pushButton_5 = new QPushButton(EditMesh);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(100, 0, 61, 51));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"image: url(:/StarterCode/split_unclicked.png);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"QPushButton:pressed{\n"
"image: url(:/StarterCode/split_clicked.png);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"\n"
""));
        pushButton_4 = new QPushButton(EditMesh);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(200, 0, 61, 51));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"image: url(:/StarterCode/edge_unclicked.png);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"background-image: url(:/StarterCode/edge_clicked.png);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"\n"
"\n"
""));
        pushButton_3 = new QPushButton(EditMesh);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(300, 0, 71, 51));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"image: url(:/StarterCode/vertex_unclicked.png);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"image: url(:/StarterCode/vertex_clicked.png);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
"\n"
"\n"
""));
        pushButton_9 = new QPushButton(EditMesh);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(410, 0, 75, 51));
        pushButton_9->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"image: url(:/StarterCode/subdivide_unclicked.png);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"background-image: url(:/StarterCode/subdivide_clicked.png);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
""));
        pushButton_10 = new QPushButton(EditMesh);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(510, 0, 75, 51));
        pushButton_10->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"image: url(:/StarterCode/extrude_unclicked.png);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"background-image: url(:/StarterCode/extrude_clicked.png);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"\n"
""));
        tabWidget_2->addTab(EditMesh, QString());
        Camera = new QWidget();
        Camera->setObjectName(QString::fromUtf8("Camera"));
        lineEdit = new lineTextWrapper(Camera);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(170, 30, 113, 20));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));
        pushButton_7 = new QPushButton(Camera);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(290, 30, 75, 23));
        pushButton_7->setStyleSheet(QString::fromUtf8("color: white;\n"
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
        pushButton_8 = new QPushButton(Camera);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(290, 0, 75, 23));
        pushButton_8->setStyleSheet(QString::fromUtf8("color: white;\n"
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
        lineEdit_2 = new lineTextWrapper(Camera);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(170, 0, 113, 20));
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));
        listWidget = new listWrapper(Camera);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(380, 10, 221, 41));
        listWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-radius:5px;"));
        label_7 = new QLabel(Camera);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(60, 30, 101, 20));
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 89);\n"
"font: 75 9pt \"Leelawadee\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"font-weight:bold"));
        label_8 = new QLabel(Camera);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(60, 0, 91, 16));
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 89);\n"
"font: 75 9pt \"Leelawadee\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"font-weight:bold"));
        tabWidget_2->addTab(Camera, QString());
        Shader = new QWidget();
        Shader->setObjectName(QString::fromUtf8("Shader"));
        lineEdit_3 = new lineTextWrapper(Shader);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(40, 10, 113, 20));
        lineEdit_3->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));
        pushButton_23 = new QPushButton(Shader);
        pushButton_23->setObjectName(QString::fromUtf8("pushButton_23"));
        pushButton_23->setGeometry(QRect(170, 10, 91, 23));
        pushButton_23->setStyleSheet(QString::fromUtf8("color: white;\n"
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
        tabWidget_2->addTab(Shader, QString());
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 80, 171, 181));
        groupBox->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 89);\n"
"font: 75 10pt \"Leelawadee\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"font-weight:bold"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 120, 16, 16));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 89);\n"
"font: 75 10pt \"Leelawadee\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"font-weight:bold"));
        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(20, 40, 141, 19));
        horizontalSlider->setStyleSheet(QString::fromUtf8("QSlider{\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"QSlider::groove:horizontal {\n"
"border: 1px solid #999999;\n"
"height: 8px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"}\n"
"QSlider::handle:horizontal {\n"
"background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"border: 1px solid #5c5c5c;\n"
"width: 18px;\n"
"margin: -2px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"border-radius: 3px;\n"
"}"));
        horizontalSlider->setMinimum(-30);
        horizontalSlider->setMaximum(30);
        horizontalSlider->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 70, 16, 16));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 89);\n"
"font: 75 10pt \"Leelawadee\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"font-weight:bold"));
        horizontalSlider_2 = new QSlider(groupBox);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(20, 90, 141, 20));
        horizontalSlider_2->setStyleSheet(QString::fromUtf8("QSlider{\n"
"\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"QSlider::groove:horizontal {\n"
"border: 1px solid #999999;\n"
"height: 8px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"}\n"
"QSlider::handle:horizontal {\n"
"background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"border: 1px solid #5c5c5c;\n"
"width: 18px;\n"
"margin: -2px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"border-radius: 3px;\n"
"}"));
        horizontalSlider_2->setMinimum(-30);
        horizontalSlider_2->setMaximum(30);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 20, 16, 20));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 89);\n"
"font: 75 10pt \"Leelawadee\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"font-weight:bold"));
        horizontalSlider_3 = new QSlider(groupBox);
        horizontalSlider_3->setObjectName(QString::fromUtf8("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(20, 140, 141, 20));
        horizontalSlider_3->setStyleSheet(QString::fromUtf8("QSlider{\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"QSlider::groove:horizontal {\n"
"border: 1px solid #999999;\n"
"height: 8px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"}\n"
"QSlider::handle:horizontal {\n"
"background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"border: 1px solid #5c5c5c;\n"
"width: 18px;\n"
"margin: -2px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"border-radius: 3px;\n"
"}"));
        horizontalSlider_3->setMinimum(-30);
        horizontalSlider_3->setMaximum(30);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        My3DViewerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(My3DViewerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1005, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuAnimate = new QMenu(menuBar);
        menuAnimate->setObjectName(QString::fromUtf8("menuAnimate"));
        menuLighting = new QMenu(menuBar);
        menuLighting->setObjectName(QString::fromUtf8("menuLighting"));
        menuEdit_Mesh = new QMenu(menuBar);
        menuEdit_Mesh->setObjectName(QString::fromUtf8("menuEdit_Mesh"));
        menuExtrude = new QMenu(menuEdit_Mesh);
        menuExtrude->setObjectName(QString::fromUtf8("menuExtrude"));
        menuDocumentations = new QMenu(menuBar);
        menuDocumentations->setObjectName(QString::fromUtf8("menuDocumentations"));
        My3DViewerClass->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAnimate->menuAction());
        menuBar->addAction(menuLighting->menuAction());
        menuBar->addAction(menuEdit_Mesh->menuAction());
        menuBar->addAction(menuDocumentations->menuAction());
        menuFile->addAction(actionLoad_Obj_2);
        menuFile->addAction(actionSave_Obj);
        menuFile->addSeparator();
        menuFile->addAction(actionNew_Cube);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuAnimate->addAction(actionPlay);
        menuAnimate->addAction(actionStop);
        menuLighting->addAction(actionChange_Light_Position);
        menuEdit_Mesh->addAction(actionAdd_Vertex);
        menuEdit_Mesh->addAction(actionRemove_Vertex);
        menuEdit_Mesh->addAction(actionSplit_Quad);
        menuEdit_Mesh->addAction(actionAdd_Edge);
        menuEdit_Mesh->addSeparator();
        menuEdit_Mesh->addAction(actionSubdivide);
        menuEdit_Mesh->addAction(menuExtrude->menuAction());
        menuExtrude->addAction(actionSet_Distance);
        menuExtrude->addAction(actionExtrude);
        menuDocumentations->addAction(actionOpen);

        retranslateUi(My3DViewerClass);
        QObject::connect(pushButton_3, SIGNAL(clicked()), EdgesList, SLOT(addVertexIntoEdge()));
        QObject::connect(pushButton_5, SIGNAL(clicked()), faceList, SLOT(addSplitQuad()));
        QObject::connect(pushButton_6, SIGNAL(clicked()), EdgesList, SLOT(addDeleteVertex()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), EdgesList, SLOT(addEdgeTwoFacesUsingHalfEdges()));
        QObject::connect(pushButton, SIGNAL(clicked()), mainWindowClass, SLOT(startCubeRotation()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), mainWindowClass, SLOT(stopCubeRotation()));
        QObject::connect(mainWindowClass, SIGNAL(sendFaces(FACES)), faceList, SLOT(addFaces(FACES)));
        QObject::connect(faceList, SIGNAL(updateGLWindow()), mainWindowClass, SLOT(doUpdateGL()));
        QObject::connect(mainWindowClass, SIGNAL(sendHalfEdges(EDGES)), EdgesList, SLOT(addEdges(EDGES)));
        QObject::connect(EdgesList, SIGNAL(callAddVertexToEdge(HalfEdge*,Vertex*)), mainWindowClass, SLOT(gotAddVertexToEdge(HalfEdge*,Vertex*)));
        QObject::connect(faceList, SIGNAL(callAddEdgeBetweenTwoFacesShareAVertex(FaceHE*,FaceHE*,HalfEdge*,HalfEdge*)), mainWindowClass, SLOT(doAddEdgeBetweenTwoFacesShareAVertex(FaceHE*,FaceHE*,HalfEdge*,HalfEdge*)));
        QObject::connect(faceList, SIGNAL(callSplitFace(FaceHE*)), mainWindowClass, SLOT(doSplitQuadIntoTwoTriangles(FaceHE*)));
        QObject::connect(EdgesList, SIGNAL(callDeleteVertex(HalfEdge*)), mainWindowClass, SLOT(doDeleteVertex(HalfEdge*)));
        QObject::connect(EdgesList, SIGNAL(callAddEdgeBetweenTwoFacesShareAVertex(FaceHE*,FaceHE*,HalfEdge*,HalfEdge*)), mainWindowClass, SLOT(doAddEdgeBetweenTwoFacesShareAVertex(FaceHE*,FaceHE*,HalfEdge*,HalfEdge*)));
        QObject::connect(horizontalSlider_2, SIGNAL(sliderReleased()), mainWindowClass, SLOT(checkFacePlanarity()));
        QObject::connect(horizontalSlider_3, SIGNAL(sliderReleased()), mainWindowClass, SLOT(checkFacePlanarity()));
        QObject::connect(mainWindowClass, SIGNAL(setFaceRow(int)), faceList, SLOT(setTheRow(int)));
        QObject::connect(horizontalSlider_2, SIGNAL(sliderMoved(int)), mainWindowClass, SLOT(redrawOutlines()));
        QObject::connect(horizontalSlider_3, SIGNAL(sliderMoved(int)), mainWindowClass, SLOT(redrawOutlines()));
        QObject::connect(horizontalSlider, SIGNAL(sliderReleased()), mainWindowClass, SLOT(checkFacePlanarity()));
        QObject::connect(horizontalSlider, SIGNAL(sliderMoved(int)), mainWindowClass, SLOT(redrawOutlines()));
        QObject::connect(mainWindowClass, SIGNAL(sendVertices(VERTICES)), VertexList, SLOT(addVertices(VERTICES)));
        QObject::connect(mainWindowClass, SIGNAL(setVertexRow(int)), VertexList, SLOT(setTheRow(int)));
        QObject::connect(faceList, SIGNAL(sendNum(int)), lcdNumber, SLOT(display(int)));
        QObject::connect(EdgesList, SIGNAL(sendNum(int)), lcdNumber_2, SLOT(display(int)));
        QObject::connect(VertexList, SIGNAL(sendNum(int)), lcdNumber_3, SLOT(display(int)));
        QObject::connect(mainWindowClass, SIGNAL(setHERow(int)), EdgesList, SLOT(setTheRow(int)));
        QObject::connect(EdgesList, SIGNAL(sendEdge(HalfEdge*)), mainWindowClass, SLOT(printEdge(HalfEdge*)));
        QObject::connect(actionQuit, SIGNAL(triggered()), My3DViewerClass, SLOT(exitWindow()));
        QObject::connect(actionNew_Cube, SIGNAL(triggered()), mainWindowClass, SLOT(newCube()));
        QObject::connect(actionPlay, SIGNAL(triggered()), mainWindowClass, SLOT(startCubeRotation()));
        QObject::connect(actionStop, SIGNAL(triggered()), mainWindowClass, SLOT(stopCubeRotation()));
        QObject::connect(actionAdd_Edge, SIGNAL(triggered()), EdgesList, SLOT(addEdgeTwoFacesUsingHalfEdges()));
        QObject::connect(actionAdd_Vertex, SIGNAL(triggered()), EdgesList, SLOT(addVertexIntoEdge()));
        QObject::connect(actionRemove_Vertex, SIGNAL(triggered()), EdgesList, SLOT(addDeleteVertex()));
        QObject::connect(actionSplit_Quad, SIGNAL(triggered()), faceList, SLOT(addSplitQuad()));
        QObject::connect(actionSubdivide, SIGNAL(triggered()), mainWindowClass, SLOT(subdivide()));
        QObject::connect(actionLoad_Obj_2, SIGNAL(triggered()), mainWindowClass, SLOT(loadMesh()));
        QObject::connect(actionLoad_Shader_2, SIGNAL(triggered()), mainWindowClass, SLOT(showLoad()));
        QObject::connect(actionSave_Obj, SIGNAL(triggered()), mainWindowClass, SLOT(saveMesh()));
        QObject::connect(actionChange_Light_Position, SIGNAL(triggered()), mainWindowClass, SLOT(changeLight()));
        QObject::connect(showBox_button, SIGNAL(clicked()), mainWindowClass, SLOT(showBox()));
        QObject::connect(hideBox_button, SIGNAL(clicked()), mainWindowClass, SLOT(disableBox()));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), mainWindowClass, SLOT(getLValue(int)));
        QObject::connect(spinBox_2, SIGNAL(valueChanged(int)), mainWindowClass, SLOT(getMValue(int)));
        QObject::connect(spinBox_3, SIGNAL(valueChanged(int)), mainWindowClass, SLOT(getNValue(int)));
        QObject::connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), listWidget, SLOT(gotClickedCam()));
        QObject::connect(mainWindowClass, SIGNAL(resetSavedViews()), listWidget, SLOT(clear()));
        QObject::connect(mainWindowClass, SIGNAL(addUserCam(CAMERAS,QString)), listWidget, SLOT(addCam(CAMERAS,QString)));
        QObject::connect(pushButton_7, SIGNAL(clicked()), lineEdit, SLOT(gotClickedCam()));
        QObject::connect(pushButton_8, SIGNAL(clicked()), lineEdit_2, SLOT(gotClickedRefPoint()));
        QObject::connect(lineEdit, SIGNAL(signalSaveCam(QString)), mainWindowClass, SLOT(saveUserView(QString)));
        QObject::connect(listWidget, SIGNAL(sendCam(CAMERAS)), mainWindowClass, SLOT(userView(CAMERAS)));
        QObject::connect(lineEdit_2, SIGNAL(signalRefPoint(QString)), mainWindowClass, SLOT(setRefPoint(QString)));
        QObject::connect(pushButton_4, SIGNAL(clicked()), mainWindowClass, SLOT(addEdge()));
        QObject::connect(horizontalSlider, SIGNAL(sliderMoved(int)), mainWindowClass, SLOT(setXBox(int)));
        QObject::connect(horizontalSlider_2, SIGNAL(sliderMoved(int)), mainWindowClass, SLOT(setYBox(int)));
        QObject::connect(horizontalSlider_3, SIGNAL(sliderMoved(int)), mainWindowClass, SLOT(setZBox(int)));
        QObject::connect(mainWindowClass, SIGNAL(sendSetX(int)), VertexList, SLOT(setX(int)));
        QObject::connect(mainWindowClass, SIGNAL(sendSetY(int)), VertexList, SLOT(setY(int)));
        QObject::connect(mainWindowClass, SIGNAL(sendSetZ(int)), VertexList, SLOT(setZ(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), mainWindowClass, SLOT(setXBox(int)));
        QObject::connect(spinBox_2, SIGNAL(valueChanged(int)), mainWindowClass, SLOT(setYBox(int)));
        QObject::connect(spinBox_3, SIGNAL(valueChanged(int)), mainWindowClass, SLOT(setZBox(int)));
        QObject::connect(pushButton_20, SIGNAL(clicked()), mainWindowClass, SLOT(twist()));
        QObject::connect(pushButton_21, SIGNAL(clicked()), mainWindowClass, SLOT(taper()));
        QObject::connect(actionSet_Distance, SIGNAL(triggered()), mainWindowClass, SLOT(showEBox()));
        QObject::connect(actionExtrude, SIGNAL(triggered()), mainWindowClass, SLOT(callExtrude()));
        QObject::connect(pushButton_10, SIGNAL(clicked()), mainWindowClass, SLOT(callExtrude()));
        QObject::connect(pushButton_9, SIGNAL(clicked()), mainWindowClass, SLOT(subdivide()));
        QObject::connect(actionOpen, SIGNAL(triggered()), mainWindowClass, SLOT(showDoc()));
        QObject::connect(pushButton_23, SIGNAL(clicked()), lineEdit_3, SLOT(gotClickedShaderName()));
        QObject::connect(lineEdit_3, SIGNAL(signalShaderN(QString)), mainWindowClass, SLOT(loadShader(QString)));
        QObject::connect(spinBox_4, SIGNAL(valueChanged(int)), mainWindowClass, SLOT(twistIndex(int)));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), mainWindowClass, SLOT(checkFacePlanarity()));
        QObject::connect(horizontalSlider_2, SIGNAL(valueChanged(int)), mainWindowClass, SLOT(checkFacePlanarity()));
        QObject::connect(horizontalSlider_3, SIGNAL(valueChanged(int)), mainWindowClass, SLOT(checkFacePlanarity()));

        tabWidget->setCurrentIndex(1);
        tabWidget_2->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(My3DViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *My3DViewerClass)
    {
        My3DViewerClass->setWindowTitle(QApplication::translate("My3DViewerClass", "Mini Maya", 0, QApplication::UnicodeUTF8));
        actionLoad_Obj->setText(QApplication::translate("My3DViewerClass", "Load Obj", 0, QApplication::UnicodeUTF8));
        actionPlay->setText(QApplication::translate("My3DViewerClass", "Play", 0, QApplication::UnicodeUTF8));
        actionStop->setText(QApplication::translate("My3DViewerClass", "Stop", 0, QApplication::UnicodeUTF8));
        actionNew_Cube->setText(QApplication::translate("My3DViewerClass", "New Cube", 0, QApplication::UnicodeUTF8));
        actionLoad_Shader->setText(QApplication::translate("My3DViewerClass", "Load Shader", 0, QApplication::UnicodeUTF8));
        actionChange_Light_Position->setText(QApplication::translate("My3DViewerClass", "Change Light Position", 0, QApplication::UnicodeUTF8));
        actionRemove_Vertex->setText(QApplication::translate("My3DViewerClass", "Remove Vertex", 0, QApplication::UnicodeUTF8));
        actionSplit_Quad->setText(QApplication::translate("My3DViewerClass", "Split Quad", 0, QApplication::UnicodeUTF8));
        actionAdd_Vertex->setText(QApplication::translate("My3DViewerClass", "Add Vertex", 0, QApplication::UnicodeUTF8));
        actionAdd_Edge->setText(QApplication::translate("My3DViewerClass", "Add Edge", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("My3DViewerClass", "Quit", 0, QApplication::UnicodeUTF8));
        actionSubdivide->setText(QApplication::translate("My3DViewerClass", "Subdivide", 0, QApplication::UnicodeUTF8));
        actionLoad_Obj_2->setText(QApplication::translate("My3DViewerClass", "Load Obj", 0, QApplication::UnicodeUTF8));
        actionLoad_Shader_2->setText(QApplication::translate("My3DViewerClass", "Load Shader", 0, QApplication::UnicodeUTF8));
        actionSave_Obj->setText(QApplication::translate("My3DViewerClass", "Save Obj", 0, QApplication::UnicodeUTF8));
        actionSet_Distance->setText(QApplication::translate("My3DViewerClass", "Set Distance", 0, QApplication::UnicodeUTF8));
        actionExtrude->setText(QApplication::translate("My3DViewerClass", "Extrude", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("My3DViewerClass", "Open", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        label->setText(QApplication::translate("My3DViewerClass", "Faces", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("My3DViewerClass", "Vertices", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("My3DViewerClass", "Half Edges", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("My3DViewerClass", "Dimensions:", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("My3DViewerClass", "X", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("My3DViewerClass", "Y", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("My3DViewerClass", "Z", 0, QApplication::UnicodeUTF8));
        showBox_button->setText(QApplication::translate("My3DViewerClass", "Show Box", 0, QApplication::UnicodeUTF8));
        hideBox_button->setText(QApplication::translate("My3DViewerClass", "Hide Box", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("My3DViewerClass", "Bounding Box", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabToolTip(tabWidget->indexOf(tab), QApplication::translate("My3DViewerClass", "Bounding Box", 0, QApplication::UnicodeUTF8));
        pushButton_20->setText(QApplication::translate("My3DViewerClass", "Twist", 0, QApplication::UnicodeUTF8));
        pushButton_21->setText(QApplication::translate("My3DViewerClass", "Taper", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("My3DViewerClass", "Twist", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(Deform), QApplication::translate("My3DViewerClass", "Deform", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabToolTip(tabWidget->indexOf(Deform), QApplication::translate("My3DViewerClass", "Deform", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QString());
        pushButton_5->setText(QString());
        pushButton_4->setText(QString());
        pushButton_3->setText(QString());
        pushButton_9->setText(QString());
        pushButton_10->setText(QString());
        tabWidget_2->setTabText(tabWidget_2->indexOf(EditMesh), QApplication::translate("My3DViewerClass", "Edit Mesh", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("My3DViewerClass", "Save Camera", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("My3DViewerClass", "Set Ref Point", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("My3DViewerClass", "Camera Name", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("My3DViewerClass", "New Reference Pt", 0, QApplication::UnicodeUTF8));
        tabWidget_2->setTabText(tabWidget_2->indexOf(Camera), QApplication::translate("My3DViewerClass", "Camera", 0, QApplication::UnicodeUTF8));
        pushButton_23->setText(QApplication::translate("My3DViewerClass", "Load Shader", 0, QApplication::UnicodeUTF8));
        tabWidget_2->setTabText(tabWidget_2->indexOf(Shader), QApplication::translate("My3DViewerClass", "Shader", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("My3DViewerClass", "Translation", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("My3DViewerClass", "Z", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("My3DViewerClass", "Y", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("My3DViewerClass", "X", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("My3DViewerClass", "File", 0, QApplication::UnicodeUTF8));
        menuAnimate->setTitle(QApplication::translate("My3DViewerClass", "Animate", 0, QApplication::UnicodeUTF8));
        menuLighting->setTitle(QApplication::translate("My3DViewerClass", "Lighting", 0, QApplication::UnicodeUTF8));
        menuEdit_Mesh->setTitle(QApplication::translate("My3DViewerClass", "Edit Mesh", 0, QApplication::UnicodeUTF8));
        menuExtrude->setTitle(QApplication::translate("My3DViewerClass", "Extrude", 0, QApplication::UnicodeUTF8));
        menuDocumentations->setTitle(QApplication::translate("My3DViewerClass", "Documentations", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class My3DViewerClass: public Ui_My3DViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MY3DVIEWER_H
