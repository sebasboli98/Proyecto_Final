#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

#include "registerwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Login_clicked();

    void on_Signin_clicked();

public:
    Ui::MainWindow *ui;

    registerwindow *m_rwindow;

private:
    static MainWindow *P_game;

};
#endif // MAINWINDOW_H
