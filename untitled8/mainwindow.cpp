#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow *MainWindow::P_game = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Login_clicked()
{
    m_rwindow = new registerwindow(true, this);
    m_rwindow->show();
    this->hide();
}


void MainWindow::on_Signin_clicked()
{
    m_rwindow = new registerwindow(false, this);
    m_rwindow->show();
    this->hide();
}

