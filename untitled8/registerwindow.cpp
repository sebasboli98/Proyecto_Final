#include "registerwindow.h"
#include "ui_registerwindow.h"

#include <iostream>

#define NCD {"../untitled8/Files/enckey.dat","../untitled8/Files/players.dat"}
#define NPD {"Sebas1778021;1778021;Sebas;sebasboli98@gmail.com;7;1;69069"}


registerwindow::registerwindow(bool mode_, QWidget *parent) : //constructor que prepara la ventana para el modo en que se va entrar.
    QDialog(parent),
    ui(new Ui::registerwindow),
    m_mode(mode_)
{
    ui->setupUi(this);

    ui->WrongUser->hide();
    ui->WrongPass->hide();

    ui->UsedMail->hide();
    ui->UsedName->hide();

    setWindowTitle("Sign in");

    if(m_mode/* Login*/){ //en caso de  login muestra la ventana de modo usuario.

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
    //OBTENER DATOS DE LOS JUGADORES EN LOS ARCHIVOS
    m_fmanager = new fmanager("../untitled8/Files/config.dat"); //llamamos al manejador de archivos / creacion de la memoria dinamica
    //../untitled8/Files/config.dat -> Aca es donde se ubica el archivo, si no se encuentra lo crea, en caso de estar lo abre.
    m_fmanager->newFileData(NCD); //utilizacion de macro para dtos de inicializacion
    m_fmanager->changeFile(m_fmanager->getFileData()[1]); // accedo a la segunda posicion para leer los datos de los jugadores
    m_fmanager->newFileData(NPD); //utilizacion de macro por si el archivo no exisitia.
    m_usersData = [&](){ // lambda funcion que se ejecutara una sola vez
        gvr::udat _mapData;

        for(std::string t_data : m_fmanager->getFileData()){ //ciclo que lee los datos de los jugadores en el archivo para colocarlos en un formato que se va a utilizar

             if(t_data == "") continue; //verificacion si no hay mas datos que leer termina la funcion el for vuelve a correr y retorna los datos hasta el momento.
            auto t_key = t_data.substr(0, t_data.find(";")); t_data.erase(0, t_data.find(";") + 1);

            auto b1temp0 = t_data.substr(0, t_data.find(";")); t_data.erase(0, t_data.find(";") + 1);
            auto b1temp1 = t_data.substr(0, t_data.find(";")); t_data.erase(0, t_data.find(";") + 1);
            auto b1temp2 = t_data.substr(0, t_data.find(";")); t_data.erase(0, t_data.find(";") + 1);

            auto b2temp0 = atoi(t_data.substr(0, t_data.find(";")).c_str());  t_data.erase(0, t_data.find(";") + 1);
            auto b2temp1 = atoi(t_data.substr(0, t_data.find(";")).c_str());  t_data.erase(0, t_data.find(";") + 1); //convierte string en un numero para los datos que se van a utilizar lvl checkpoitn puntaje ....
            auto b2temp2 = atoi(t_data.substr(0, t_data.find(";")).c_str()); t_data.erase(0, t_data.find("\0"));

            std::array<std::string, 3> t_body0 = { b1temp0, b1temp1, b1temp2 }; //aca se alamcenan los datos de string
            std::array<uint, 3> t_body1 = { unsigned(b2temp0), unsigned(b2temp1), unsigned(b2temp2) };//aca se alamcenan los datos de numeros

            _mapData[t_key] = std::pair<std::array<std::string, 3>, std::array<uint, 3>>{ t_body0, t_body1 }; //se agregan os datos en el mapa para retornarlos.
        }

        return  _mapData;
    }();

}

registerwindow::~registerwindow()
{
    delete ui;
}

bool registerwindow::loginUser(std::string UserName_, std::string UserPass_) //verifica si los datos son croresctos para ingresar.
{
    ui->WrongUser->hide();
    ui->WrongPass->hide();

    if(m_usersData.count(UserName_ + UserPass_) == 0){ //verifica si la identifiacacion corresponde a los datos ingresados
        for(auto _user : this->m_usersData){            //recorre la estructura en  busca de que  los daos estan repetidos o existen.
            if(_user.second.first[1] == UserName_){ //comprobamos si el nombre de usuario existe, en csao de que si la contraseña esta erronea.
                ui->WrongPass->show();
                return false; //retorna falso
            }
        }
        ui->WrongUser->show(); //indica que el nombre de usuario es incorrecto en la ventana.
        return false;
    }
    return true; //en caso de que los datos sean encontrados se puede ingresar.
}

bool registerwindow::registerUser(std::string UserName_, std::string UserPass_, std::string Mail_) //verifica que si los datos existen y en caso de que si significa que ya han sido usados.
{
    ui->UsedName->hide();
    ui->UsedMail->hide();
    ui->UsedMail->setText("Correo en uso");

    if(UserName_ == "" || UserPass_ == "" || Mail_ == ""){ //se verifica que no se hayan omitido datos, en caso de que no se pongan datos.
        ui->UsedMail->setText("Datos invalidos");
        ui->UsedMail->show();
        return false;
    }

    if((m_usersData.count(UserName_ + UserPass_) != 0)){ // se verifica que los datos ya esten usados, si entra ya estan usados
        for(auto _user : this->m_usersData){ //recorre todos los datos para hacer la verificacion respectiva
            if(_user.second.first[2] == Mail_){ //si entra significa que el correo ya esta ocupado.
                ui->UsedMail->show();
                break;
            }     
        }
        ui->UsedName->show();
        return false;
    }
                            //busqueda exaustiva
    for(auto _user : this->m_usersData){ //se revisan todos los datos buscando coincidencias
        if(_user.second.first[1] == UserName_){ // verifica si el nombre esta repetido
            ui->UsedName->show(); //indica que ya esta usado y sale
            return false;
        }
        if(_user.second.first[2] == Mail_){// verifica si el correo esta repetido
            ui->UsedMail->show(); //indica que ya esta usado y sale
            return false;
        }
    }
    return true;//en caso de que pase los controles el usuaruio puede ser registrado
}

void registerwindow::on_Continue_clicked() //implementacion del boton de continuar
{ //se verifica el modo, si de ingresar o de registrar.
    if(m_mode){
        if(!loginUser(ui->namebox->text().toStdString(), ui->passbox->text().toStdString())){ //verifica los datos ingresar
            ui->namebox->clear();
            ui->passbox->clear();
            return;
        }
    }
    else{
        if(!registerUser(ui->namebox->text().toStdString(), ui->passbox->text().toStdString(), ui->mailbox->text().toStdString())){
            ui->mailbox->clear();  //Se verifican los datos para resgistrar
            ui->namebox->clear();
            ui->passbox->clear();
            return;
        }
        //en esta variable se guardan los datos para usarlos en el juego.
        m_usersData[ui->namebox->text().toStdString() + ui->passbox->text().toStdString()]  //En caso de que los datos sean validos guarda los datos del usuario que se esa registrando
                = gvr::udpair({ui->namebox->text().toStdString(),
                                      ui->passbox->text().toStdString(),
                                      ui->mailbox->text().toStdString()},
                                      {1,0,0});

        m_fmanager->appendFileData( //aca se agregan los datos al final del archivo, ya que es un nuevo usuario.
                        ui->namebox->text().toStdString() + ui->passbox->text().toStdString() + ";" +
                        ui->namebox->text().toStdString() + ";" +
                        ui->passbox->text().toStdString() + ";" +
                        ui->mailbox->text().toStdString() + ";" +
                        "1;0;0");

    }

    gw = new gamewindow(m_usersData[ui->namebox->text().toStdString() + ui->passbox->text().toStdString()]);// creacion de la ventana del juego con los datos del usuario
    gw->show(); //muestra pantalla
    gw->showMaximized(); //maximiza la pantalla
    this->hide(); // cierra la ventana de registro o ingreso.

}



void registerwindow::on_Exit_clicked() //implementacion para el cerrado del programa.
{
    exit(1);
}
