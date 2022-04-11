#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow *MainWindow::P_game = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_fmanager = new fmanager("Config");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Login_clicked()
{

}


void MainWindow::on_Signin_clicked()
{

}

