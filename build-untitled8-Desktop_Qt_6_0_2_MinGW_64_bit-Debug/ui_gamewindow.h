/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gamewindow
{
public:
    QGraphicsView *MainView;
    QLabel *label;

    void setupUi(QWidget *gamewindow)
    {
        if (gamewindow->objectName().isEmpty())
            gamewindow->setObjectName(QString::fromUtf8("gamewindow"));
        gamewindow->resize(1080, 720);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gamewindow->sizePolicy().hasHeightForWidth());
        gamewindow->setSizePolicy(sizePolicy);
        MainView = new QGraphicsView(gamewindow);
        MainView->setObjectName(QString::fromUtf8("MainView"));
        MainView->setEnabled(true);
        MainView->setGeometry(QRect(0, 0, 1080, 720));
        MainView->setStyleSheet(QString::fromUtf8("background-image: url(:/gfx/Images/Fondo.jpg);"));
        label = new QLabel(gamewindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(340, 120, 371, 141));
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        retranslateUi(gamewindow);

        QMetaObject::connectSlotsByName(gamewindow);
    } // setupUi

    void retranslateUi(QWidget *gamewindow)
    {
        gamewindow->setWindowTitle(QCoreApplication::translate("gamewindow", "Form", nullptr));
        label->setText(QCoreApplication::translate("gamewindow", "Mondaa de prueba", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gamewindow: public Ui_gamewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
