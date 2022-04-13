/********************************************************************************
** Form generated from reading UI file 'registerwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWINDOW_H
#define UI_REGISTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_registerwindow
{
public:
    QPushButton *Continue;
    QPushButton *Exit;
    QLabel *Title;
    QLineEdit *mailbox;
    QLineEdit *namebox;
    QLabel *maillabel;
    QLineEdit *passbox;
    QLabel *namelabel;
    QLabel *passlabel;
    QLabel *WrongUser;
    QLabel *WrongPass;
    QLabel *UsedMail;
    QLabel *UsedName;

    void setupUi(QDialog *registerwindow)
    {
        if (registerwindow->objectName().isEmpty())
            registerwindow->setObjectName(QString::fromUtf8("registerwindow"));
        registerwindow->resize(1080, 720);
        Continue = new QPushButton(registerwindow);
        Continue->setObjectName(QString::fromUtf8("Continue"));
        Continue->setGeometry(QRect(300, 520, 200, 50));
        QFont font;
        font.setPointSize(22);
        Continue->setFont(font);
        Exit = new QPushButton(registerwindow);
        Exit->setObjectName(QString::fromUtf8("Exit"));
        Exit->setGeometry(QRect(580, 520, 200, 50));
        Exit->setFont(font);
        Title = new QLabel(registerwindow);
        Title->setObjectName(QString::fromUtf8("Title"));
        Title->setGeometry(QRect(430, 60, 231, 61));
        QFont font1;
        font1.setPointSize(28);
        Title->setFont(font1);
        Title->setScaledContents(false);
        Title->setAlignment(Qt::AlignCenter);
        mailbox = new QLineEdit(registerwindow);
        mailbox->setObjectName(QString::fromUtf8("mailbox"));
        mailbox->setEnabled(true);
        mailbox->setGeometry(QRect(560, 180, 371, 61));
        QFont font2;
        font2.setPointSize(16);
        mailbox->setFont(font2);
        mailbox->setMaxLength(32767);
        namebox = new QLineEdit(registerwindow);
        namebox->setObjectName(QString::fromUtf8("namebox"));
        namebox->setGeometry(QRect(560, 270, 371, 61));
        namebox->setFont(font2);
        namebox->setMaxLength(32);
        maillabel = new QLabel(registerwindow);
        maillabel->setObjectName(QString::fromUtf8("maillabel"));
        maillabel->setGeometry(QRect(190, 180, 331, 61));
        maillabel->setFont(font);
        maillabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        passbox = new QLineEdit(registerwindow);
        passbox->setObjectName(QString::fromUtf8("passbox"));
        passbox->setGeometry(QRect(560, 360, 371, 61));
        passbox->setFont(font2);
        passbox->setMaxLength(32);
        namelabel = new QLabel(registerwindow);
        namelabel->setObjectName(QString::fromUtf8("namelabel"));
        namelabel->setGeometry(QRect(190, 270, 331, 61));
        namelabel->setFont(font);
        namelabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        passlabel = new QLabel(registerwindow);
        passlabel->setObjectName(QString::fromUtf8("passlabel"));
        passlabel->setGeometry(QRect(190, 360, 331, 61));
        passlabel->setFont(font);
        passlabel->setLayoutDirection(Qt::LeftToRight);
        passlabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        WrongUser = new QLabel(registerwindow);
        WrongUser->setObjectName(QString::fromUtf8("WrongUser"));
        WrongUser->setEnabled(true);
        WrongUser->setGeometry(QRect(560, 210, 371, 20));
        WrongUser->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        WrongUser->setAlignment(Qt::AlignCenter);
        WrongPass = new QLabel(registerwindow);
        WrongPass->setObjectName(QString::fromUtf8("WrongPass"));
        WrongPass->setGeometry(QRect(560, 310, 371, 20));
        WrongPass->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        WrongPass->setAlignment(Qt::AlignCenter);
        UsedMail = new QLabel(registerwindow);
        UsedMail->setObjectName(QString::fromUtf8("UsedMail"));
        UsedMail->setEnabled(true);
        UsedMail->setGeometry(QRect(560, 160, 371, 20));
        UsedMail->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        UsedMail->setAlignment(Qt::AlignCenter);
        UsedName = new QLabel(registerwindow);
        UsedName->setObjectName(QString::fromUtf8("UsedName"));
        UsedName->setEnabled(true);
        UsedName->setGeometry(QRect(560, 250, 371, 20));
        UsedName->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        UsedName->setAlignment(Qt::AlignCenter);

        retranslateUi(registerwindow);

        QMetaObject::connectSlotsByName(registerwindow);
    } // setupUi

    void retranslateUi(QDialog *registerwindow)
    {
        registerwindow->setWindowTitle(QCoreApplication::translate("registerwindow", "Dialog", nullptr));
        Continue->setText(QCoreApplication::translate("registerwindow", "Continuar", nullptr));
        Exit->setText(QCoreApplication::translate("registerwindow", "Salir", nullptr));
        Title->setText(QCoreApplication::translate("registerwindow", "Registrarse", nullptr));
        mailbox->setText(QString());
        maillabel->setText(QCoreApplication::translate("registerwindow", "Correo electronico:", nullptr));
        namelabel->setText(QCoreApplication::translate("registerwindow", "Nombre de usuario:", nullptr));
        passlabel->setText(QCoreApplication::translate("registerwindow", "Contrase\303\261a:", nullptr));
        WrongUser->setText(QCoreApplication::translate("registerwindow", "Nombre o correo incorrecto", nullptr));
        WrongPass->setText(QCoreApplication::translate("registerwindow", "Contrase\303\261a incorrecta", nullptr));
        UsedMail->setText(QCoreApplication::translate("registerwindow", "Correo en uso", nullptr));
        UsedName->setText(QCoreApplication::translate("registerwindow", "Nombre en uso", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registerwindow: public Ui_registerwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWINDOW_H
