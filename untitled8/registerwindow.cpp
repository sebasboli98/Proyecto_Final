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

    ui->WrongUser->hide();
    ui->WrongPass->hide();

    ui->UsedMail->hide();
    ui->UsedName->hide();

    if(m_mode/* Login*/){

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
    if(m_usersData.count(UserName_ + UserPass_) == 0){
        for(auto _user : this->m_usersData){
            if(_user.second.first[1] == UserName_){
                ui->WrongPass->show();
                return false;
            }
        }
        ui->WrongUser->show();
        return false;
    }
    return true;
}

bool registerwindow::registerUser(std::string UserName_, std::string Pass_, std::string Mail_)
{
    return 0;
    // .find() -> Map on key pos | ->second -> Data of the key | .first -> first array of the std::pair | [2] -> second element from the std::string array

}

void registerwindow::on_Continue_clicked()
{

    ui->WrongUser->hide();
    ui->WrongPass->hide();

    if(m_mode){
        while(!loginUser(ui->namebox->text().toStdString(), ui->passbox->text().toStdString())){
            ui->namebox->clear();
            ui->passbox->clear();
            return;
        }
        gw = new gamewindow(m_usersData[ui->namebox->text().toStdString() + ui->passbox->text().toStdString()], this);
        gw->show();
        this->hide();

    }

    while(!registerUser(ui->namebox->text().toStdString(), ui->passbox->text().toStdString(), ui->mailbox->text().toStdString())){

    }

    //m_gameWindow = new gamewindow();

}


void registerwindow::on_Exit_clicked()
{
    exit(1);
}

