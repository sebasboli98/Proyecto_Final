/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QPushButton *Login;
    QLabel *Title;
    QPushButton *Signin;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1366, 768);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 1366, 768));
        QFont font;
        font.setFamily(QString::fromUtf8("Bradley Hand ITC"));
        font.setPointSize(22);
        graphicsView->setFont(font);
        graphicsView->setAutoFillBackground(true);
        graphicsView->setStyleSheet(QString::fromUtf8("background-image: url(:/gfx/Images/Fondo.jpg);"));
        Login = new QPushButton(centralwidget);
        Login->setObjectName(QString::fromUtf8("Login"));
        Login->setGeometry(QRect(396, 450, 221, 111));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bradley Hand ITC"));
        font1.setPointSize(28);
        font1.setBold(true);
        font1.setItalic(false);
        Login->setFont(font1);
        Login->setAutoFillBackground(false);
        Login->setStyleSheet(QString::fromUtf8("background-image: url(:/gfx/Images/wtabla.png);\n"
"color: rgb(0, 0, 0);"));
        Title = new QLabel(centralwidget);
        Title->setObjectName(QString::fromUtf8("Title"));
        Title->setGeometry(QRect(452, 90, 391, 70));
        QFont font2;
        font2.setPointSize(40);
        font2.setBold(true);
        font2.setItalic(true);
        font2.setStrikeOut(false);
        font2.setKerning(true);
        Title->setFont(font2);
        Title->setLayoutDirection(Qt::LeftToRight);
        Title->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        Title->setScaledContents(false);
        Signin = new QPushButton(centralwidget);
        Signin->setObjectName(QString::fromUtf8("Signin"));
        Signin->setGeometry(QRect(720, 450, 221, 111));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Bradley Hand ITC"));
        font3.setPointSize(22);
        font3.setBold(true);
        Signin->setFont(font3);
        Signin->setAutoFillBackground(false);
        Signin->setStyleSheet(QString::fromUtf8("background-image: url(:/gfx/Images/wtabla.png);\n"
"color: rgb(0, 0, 0);"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1366, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Login->setText(QCoreApplication::translate("MainWindow", "Ingresar", nullptr));
#if QT_CONFIG(shortcut)
        Login->setShortcut(QCoreApplication::translate("MainWindow", "Return, Space", nullptr));
#endif // QT_CONFIG(shortcut)
        Title->setText(QCoreApplication::translate("MainWindow", "Run Bitch Run", nullptr));
        Signin->setText(QCoreApplication::translate("MainWindow", "Registrarse", nullptr));
#if QT_CONFIG(shortcut)
        Signin->setShortcut(QCoreApplication::translate("MainWindow", "Return, Space", nullptr));
#endif // QT_CONFIG(shortcut)
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
