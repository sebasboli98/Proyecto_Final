#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QDialog>
#include <map>
#include <array>

#include "fmanager.h"
#include "utilities.h"
#include "gamewindow.h"

namespace Ui {
class registerwindow;
}

class registerwindow : public QDialog
{
    Q_OBJECT

public:
    explicit registerwindow(bool mode_, QWidget *parent = nullptr); //Constructor que recibe si esta registrando o ingresando.
    ~registerwindow(); //mode_ boolenao que determina el modo

private:
    bool loginUser(std::string UserName_, std::string UserPass_); //funcion utilizada para verificar si el usuario existe y los datos son validos.
    bool registerUser(std::string UserName_, std::string Pass_, std::string Mail_);//verifica si los datos estan disponibles para crear una nueva cuenta

private slots:
    void on_Continue_clicked(); //funcion que recibe el boton de continuar
    void on_Exit_clicked();  //funcion que recibe el boton de salir
private:
    Ui::registerwindow *ui; //variable de la clase
    gamewindow *gw;         //variable de la ventana del juego
    fmanager *m_fmanager;   //manejador de archivos

    gvr::udat m_usersData; //  datos de los usuarios - {Sebas1778021;1778021;Sebas;sebasboli98@gmail.com;7;1;69069}
    std::vector<std::string> m_levelData;

    bool m_mode; //modo si entra como registro o ingreso.

};

#endif // REGISTERWINDOW_H
