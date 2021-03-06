#include "registerwindow.h"
#include "ui_registerwindow.h"

#include <iostream>

#define NCD {"../untitled8/Files/enckey.dat","../untitled8/Files/players.dat"}
#define NPD {"Sebas1778021;1778021;Sebas;sebasboli98@gmail.com;7;1;69069"}


registerwindow::registerwindow(bool mode_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerwindow),
    m_mode(mode_)
{
    ui->setupUi(this);
    setWindowTitle("Sign in");

    ui->WrongUser->hide();
    ui->WrongPass->hide();

    ui->UsedMail->hide();
    ui->UsedName->hide();


    if(m_mode/* Login*/){

        setWindowTitle("Log in");
        ui->Title->setText("Ingresar");
        ui->Continue->setText("Ingresar");
        ui->namelabel->setText("Nombre de usuario");

        ui->mailbox->hide();
        ui->maillabel->hide();

        ui->namelabel->setGeometry(ui->namelabel->x(), 230, ui->namelabel->width(), ui->namelabel->height());
        ui->passlabel->setGeometry(ui->passlabel->x(), 330, ui->passlabel->width(), ui->passlabel->height());
        ui->namebox->setGeometry(ui->namebox->x(), 230, ui->namebox->width(), ui->namebox->height());
        ui->passbox->setGeometry(ui->passbox->x(), 330, ui->passbox->width(), ui->passbox->height());

    }

    /// Obtener datos de los jugadores en los archivos
    m_fmanager = new fmanager("../untitled8/Files/config.dat");
    m_fmanager->newFileData(NCD);
    m_fmanager->changeFile(m_fmanager->getFileData()[1]);
    m_fmanager->newFileData(NPD);
    m_usersData = [&](){
        gvr::udat _mapData;

        for(std::string t_data : m_fmanager->getFileData()){

             if(t_data == "") continue;
            auto t_key = t_data.substr(0, t_data.find(";")); t_data.erase(0, t_data.find(";") + 1);

            auto b1temp0 = t_data.substr(0, t_data.find(";")); t_data.erase(0, t_data.find(";") + 1);
            auto b1temp1 = t_data.substr(0, t_data.find(";")); t_data.erase(0, t_data.find(";") + 1);
            auto b1temp2 = t_data.substr(0, t_data.find(";")); t_data.erase(0, t_data.find(";") + 1);

            auto b2temp0 = atoi(t_data.substr(0, t_data.find(";")).c_str());  t_data.erase(0, t_data.find(";") + 1);
            auto b2temp1 = atoi(t_data.substr(0, t_data.find(";")).c_str());  t_data.erase(0, t_data.find(";") + 1);
            auto b2temp2 = atoi(t_data.substr(0, t_data.find(";")).c_str()); t_data.erase(0, t_data.find("\0"));

            std::array<std::string, 3> t_body0 = { b1temp0, b1temp1, b1temp2 };
            std::array<uint, 3> t_body1 = { unsigned(b2temp0), unsigned(b2temp1), unsigned(b2temp2) };

            _mapData[t_key] = std::pair<std::array<std::string, 3>, std::array<uint, 3>>{ t_body0, t_body1 };
        }

        return  _mapData;
    }();

}

registerwindow::~registerwindow()
{
    delete ui;
}

bool registerwindow::loginUser(std::string UserName_, std::string UserPass_)
{
    ui->WrongUser->hide();
    ui->WrongPass->hide();
    /// Esconder textos de fallos

    if(m_usersData.count(UserName_ + UserPass_) == 0){ /// Verifica si los datos ya existen (Entra si no existen)
        for(auto _user : this->m_usersData){
            if(_user.second.first[1] == UserName_){ /// Si encuentra el usuario, la contrase??a es incorrecta
                ui->WrongPass->show();
                return false;
            }
        }
        ui->WrongUser->show();
        return false;
    }
    return true;
}

bool registerwindow::registerUser(std::string UserName_, std::string UserPass_, std::string Mail_)
{
    ui->UsedName->hide();
    ui->UsedMail->hide();
    ui->UsedMail->setText("Correo en uso");

    if(UserName_ == "" || UserPass_ == "" || Mail_ == ""){
        ui->UsedMail->setText("Datos invalidos");
        ui->UsedMail->show();
        return false;
    }

    if((m_usersData.count(UserName_ + UserPass_) != 0)){
        uint flag = 0;
        for(auto _user : this->m_usersData){
            if(_user.second.first[1] == UserName_){
                ui->UsedName->show();
                flag++;
            }
            if(_user.second.first[2] == Mail_){
                ui->UsedMail->show();
                flag++;
            }
            if(!flag)
                return false;
        }
        return false;
    }

    for(auto _user : this->m_usersData){
        if(_user.second.first[1] == UserName_){
            ui->UsedName->show();
            return false;
        }
        if(_user.second.first[2] == Mail_){
            ui->UsedMail->show();
            return false;
        }
    }
    return true;
}

void registerwindow::on_Continue_clicked()
{
    if(m_mode){ /// Verificar existencia del usuario
        if(!loginUser(ui->namebox->text().toStdString(), ui->passbox->text().toStdString())){
            ui->namebox->clear();
            ui->passbox->clear();
            return;
        }
    }
    else{ /// Verificar que no sean datos usados
        if(!registerUser(ui->namebox->text().toStdString(), ui->passbox->text().toStdString(), ui->mailbox->text().toStdString())){
            ui->mailbox->clear();
            ui->namebox->clear();
            ui->passbox->clear();
            return;
        }
        m_usersData[ui->namebox->text().toStdString() + ui->passbox->text().toStdString()]
                = gvr::udpair({ui->namebox->text().toStdString(),
                                      ui->passbox->text().toStdString(),
                                      ui->mailbox->text().toStdString()},
                                      {1,0,0});

        m_fmanager->appendFileData(
                        ui->namebox->text().toStdString() + ui->passbox->text().toStdString() + ";" +
                        ui->namebox->text().toStdString() + ";" +
                        ui->passbox->text().toStdString() + ";" +
                        ui->mailbox->text().toStdString() + ";" +
                        "1;0;0");


    }

    gw = new gamewindow(m_usersData[ui->namebox->text().toStdString() + ui->passbox->text().toStdString()], m_usersData);
    gw->show();
    gw->showMaximized();
    this->hide();

}


void registerwindow::on_Exit_clicked()
{
    exit(1);
}

