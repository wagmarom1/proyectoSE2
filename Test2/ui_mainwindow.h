/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Nov 14 21:59:44 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *lbOriginal;
    QLabel *lbMap;
    QPushButton *pushButton;
    QGroupBox *groupBox;
    QRadioButton *rbSquare;
    QRadioButton *rbTriangle;
    QLabel *lbpoint;
    QLabel *lbLost;
    QLabel *lbCached;
    QLabel *label;
    QLabel *label2;
    QScrollBar *horizontalScrollBar;
    QLabel *label2_2;
    QLabel *lbLevel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(909, 579);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lbOriginal = new QLabel(centralWidget);
        lbOriginal->setObjectName(QString::fromUtf8("lbOriginal"));
        lbOriginal->setGeometry(QRect(20, 110, 291, 231));
        lbOriginal->setAutoFillBackground(true);
        lbOriginal->setScaledContents(true);
        lbMap = new QLabel(centralWidget);
        lbMap->setObjectName(QString::fromUtf8("lbMap"));
        lbMap->setGeometry(QRect(340, 20, 531, 441));
        lbMap->setAutoFillBackground(false);
        lbMap->setStyleSheet(QString::fromUtf8("QLabel{\n"
"		background-color:rgb(242, 230, 255);\n"
"}"));
        lbMap->setScaledContents(false);
        lbMap->setWordWrap(false);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 360, 101, 41));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: lightGreen;\n"
"    border-style: outset;\n"
"    border-width: 1px;\n"
"    border-radius: 10px;\n"
"    border-color: beige;\n"
"    font: bold 14px;\n"
"    min-width: 5em;\n"
"    padding: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(224, 0, 0);\n"
"    border-style: inset;\n"
"}"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(130, 354, 120, 91));
        rbSquare = new QRadioButton(groupBox);
        rbSquare->setObjectName(QString::fromUtf8("rbSquare"));
        rbSquare->setGeometry(QRect(0, 60, 116, 22));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        rbSquare->setFont(font);
        rbSquare->setChecked(true);
        rbTriangle = new QRadioButton(groupBox);
        rbTriangle->setObjectName(QString::fromUtf8("rbTriangle"));
        rbTriangle->setEnabled(true);
        rbTriangle->setGeometry(QRect(0, 30, 116, 22));
        rbTriangle->setFont(font);
        rbTriangle->setChecked(false);
        lbpoint = new QLabel(centralWidget);
        lbpoint->setObjectName(QString::fromUtf8("lbpoint"));
        lbpoint->setGeometry(QRect(10, 470, 111, 21));
        lbLost = new QLabel(centralWidget);
        lbLost->setObjectName(QString::fromUtf8("lbLost"));
        lbLost->setGeometry(QRect(120, 0, 101, 71));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        lbLost->setFont(font1);
        lbCached = new QLabel(centralWidget);
        lbCached->setObjectName(QString::fromUtf8("lbCached"));
        lbCached->setGeometry(QRect(140, 50, 101, 71));
        lbCached->setFont(font1);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 0, 101, 71));
        label->setFont(font1);
        label2 = new QLabel(centralWidget);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(10, 50, 121, 71));
        label2->setFont(font1);
        horizontalScrollBar = new QScrollBar(centralWidget);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(130, 450, 181, 21));
        horizontalScrollBar->setStyleSheet(QString::fromUtf8("QScrollBar:horizontal {\n"
"     border: 2px solid grey;\n"
"     background: #32CC99;\n"
"     height: 15px;\n"
"     margin: 0px 20px 0 20px;\n"
" }\n"
" QScrollBar::handle:horizontal {\n"
"     background: white;\n"
"     min-width: 20px;\n"
" }\n"
" QScrollBar::add-line:horizontal {\n"
"     border: 2px solid grey;\n"
"     background: #32CC99;\n"
"     width: 20px;\n"
"     subcontrol-position: right;\n"
"     subcontrol-origin: margin;\n"
" }\n"
"\n"
" QScrollBar::sub-line:horizontal {\n"
"     border: 2px solid grey;\n"
"     background: #32CC99;\n"
"     width: 20px;\n"
"     subcontrol-position: left;\n"
"     subcontrol-origin: margin;\n"
" }"));
        horizontalScrollBar->setMinimum(10);
        horizontalScrollBar->setMaximum(100);
        horizontalScrollBar->setSingleStep(10);
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        label2_2 = new QLabel(centralWidget);
        label2_2->setObjectName(QString::fromUtf8("label2_2"));
        label2_2->setGeometry(QRect(130, 480, 61, 31));
        label2_2->setFont(font1);
        lbLevel = new QLabel(centralWidget);
        lbLevel->setObjectName(QString::fromUtf8("lbLevel"));
        lbLevel->setGeometry(QRect(190, 480, 61, 31));
        lbLevel->setFont(font1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 909, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        lbOriginal->setText(QString());
        lbMap->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "Reset", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Figure", 0, QApplication::UnicodeUTF8));
        rbSquare->setText(QApplication::translate("MainWindow", "Square", 0, QApplication::UnicodeUTF8));
        rbTriangle->setText(QApplication::translate("MainWindow", "Triangle", 0, QApplication::UnicodeUTF8));
        lbpoint->setText(QString());
        lbLost->setText(QString());
        lbCached->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Lost Packets:", 0, QApplication::UnicodeUTF8));
        label2->setText(QApplication::translate("MainWindow", "Cached Packets:", 0, QApplication::UnicodeUTF8));
        label2_2->setText(QApplication::translate("MainWindow", "Level:", 0, QApplication::UnicodeUTF8));
        lbLevel->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
