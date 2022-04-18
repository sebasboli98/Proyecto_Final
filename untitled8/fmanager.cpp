#include "fmanager.h"

fmanager::fmanager(const std::string& File_)
    : m_File(File_), m_Data(), m_NFData()  //atributos de la clase, inicializacion de los atributos.
{
    return;
}

std::vector<std::string> fmanager::getFileData() //Funcion que lee los datos y los retorna.
{
    readFile(); // invocacion de funcion que lee los datos para retornar los datos leidos.
    return m_Data;
}

void fmanager::setFileData(const std::vector<std::string> &NewData_) //funcion que actualiza los datos.
{
    m_Data = NewData_; // Guarda los nuevos datos en la variable de datos.
    writeFile(); // Se hace la escritura de los datos en el archivo.
    return;
}

void fmanager::changeFile(const std::string &NewFile_) //Funcion que modifica el archivo que se trabajará.
{
    m_File = NewFile_; // Guarda la direccion del nuevo archivo.
    m_Data = {}; // Limpieza de datos, ya que puede tener datos de archivos anterires {}-> Construccion implicita para crear vector vacio.
    return;
}

void fmanager::newFileData(const std::vector<std::string> &Data_) //Funcion que recibe los datos en caso de que el archivo no exista.
{
    m_NFData = Data_; // Se asignan los datos en la variable para uttilizarlos en la lectura.
    return;
}

void fmanager::overrideFileData(std::vector<std::string> NewData_) // Funcion que sobreescribe el archivo, para actualizar el archivo.
{
    std::ofstream _File;
    _File.open(m_File, std::ios::out); //métedo de apertura para escribir o borrar los datos del archivo.
    for(auto _data : NewData_) // For en rango que recibe un vector para que todas las posiciones seran cargadas
        _File << _data + "\n"; // escritura de linea por linea de los datos.
    _File.close();
    return;
}

void fmanager::overrideFileData(std::string NewData_) //Funcion muy similar a la anterior para utilizar solo un dato.
{
    std::ofstream _File;
    _File.open(m_File, std::ios::out); // Apertura del archivo.
    _File << NewData_ + "\n"; // Escritura de  NewData_ en el archivo.
    _File.close();
    return;
}

void fmanager::appendFileData(std::vector<std::string> NewData_) //Funcion que se encarga de agregar los datos al final del archivo
{
    std::ofstream _File;
    _File.open(m_File, std::ios::app); // método de apertura para agregar al final del archivo.
    for(auto _data : NewData_) // For en rango que recibe un vector para que todas las posiciones seran cargadas
        _File << _data + "\n"; //// escritura de linea por linea de los datos.
    _File.close();
    return;
}

void fmanager::appendFileData(std::string NewData_) // Implementacion de funcion similar a la anterior pero para un solo dato.
{
    std::ofstream _File;
    _File.open(m_File, std::ios::app); // Apertura del archivo para agregar dato al final
    _File << NewData_ + "\n"; //escritura  NewData_ at al archivo.
}

void fmanager::deleteFileData() // Funcion que borra los datos del archivo en caso de que los datos esten dañados.
{
    std::ofstream _File;
    _File.open(m_File, std::ios::out); // Metodo para sobreescritura del archivo
    _File << "\0"; // caracter nulo para borrar los datos.
    return;
}

void fmanager::readFile()  //Lógica para implementacion de a lectura de archivos y manejo de excepciones.
{
    std::ifstream _File;
    _File.open(this->m_File, std::ios::in); // Método de apertura del archivo en modo lectura (in)
    if(_File.fail()){ // Se verifica que el archivo exista. en caso de que no exista entra en el condicional.
        qDebug() << QString("Archivo no encontrado.");
        _File.close(); //cierra el archivo para abrir el archivo en modo de ecritura o creacion.

        std::ofstream Temp;
        Temp.open(this->m_File, std::ios::out); //creacion del archivo. (out)
        for(auto _data : this->m_NFData){ // For en rango para guardar los datos en caso de que no exista.
            Temp << _data + "\n"; // Escritura de los datos si hay datos.
        }
        Temp.close(); // se cierra el archivo.
        _File.open(this->m_File, std::ios::in);//Se vuelve a abrir el archivo en modo lectura
        if(_File.fail()) [[unlikely]]{ // Verificacion del archivo en caso de que haya sido creado correctamente.   [[unlikely]] Es poco probable que ocurra
            exit(-404); // Erorr que determina cierre del programa
        }
    } // End if(Fail)
    {
        std::string Temp; //creacion de variable temporal para guardar los datos temporalmente
        while(!_File.eof()){ //ciclo para recorrer el archivo linea por linea.
            std::getline(_File, Temp); // Lectura de la linea en la posicion respectiva.
            this->m_Data.push_back(Temp); // Guardado de datos temporales en estructura de datos.
        }
    }
    _File.close(); //cierra el archivo y se sale.
    return;
}

void fmanager::writeFile() // Funcion que va a escribir los datos en el archivo.
{
    std::ofstream _File;
    _File.open(this->m_File, std::ios::out); // Apertura del archivo en modo de escritura o creacion (out)

    for(std::string s : this->m_Data){ // for en rango que escribe los datos al archivo.
        _File << s + "\n";
    }

    _File.close();
    return;
}
