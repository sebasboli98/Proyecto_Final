#include "registerwindow.h"
#include "ui_registerwindow.h"

registerwindow::registerwindow(bool mode_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerwindow)
{
    ui->setupUi(this);

    ui->WrongUser->hide();
    ui->WrongPass->hide();

    ui->UsedMail->hide();
    ui->UsedName->hide();

    if(mode_/* Login*/){

        ui->Title->setText("Ingresar");
        ui->Continue->setText("Ingresar");
        ui->namelabel->setText("Nombre o correo");

        ui->mailbox->hide();
        ui->maillabel->hide();

        ui->namelabel->setGeometry(ui->namelabel->x(), 230, ui->namelabel->width(), ui->namelabel->height());
        ui->passlabel->setGeometry(ui->passlabel->x(), 330, ui->passlabel->width(), ui->passlabel->height());
        ui->namebox->setGeometry(ui->namebox->x(), 230, ui->namebox->width(), ui->namebox->height());
        ui->passbox->setGeometry(ui->passbox->x(), 330, ui->passbox->width(), ui->passbox->height());

    }

}

registerwindow::~registerwindow()
{
    delete ui;
}

void registerwindow::on_Continue_clicked()
{

}


void registerwindow::on_Exit_clicked()
{
    this->~registerwindow();
    exit(1);
}

