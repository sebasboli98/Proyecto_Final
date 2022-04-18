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

void fmanager::appendFileData(std::string NewData_)
{
    std::ofstream _File;
    _File.open(m_File, std::ios::app); // Opens the file
    _File << NewData_ + "\n"; // Writes NewData_ at the end of file
    return;
}

void fmanager::deleteFileData()
{
    std::ofstream _File;
    _File.open(m_File, std::ios::out); // Opens the file
    _File << "\0"; // Overrides data with null char
    return;
}

void fmanager::readFile()
{
    std::ifstream _File;
    _File.open(this->m_File, std::ios::in); // Opens file
    if(_File.fail()){ // Checks if the file exists
        qDebug() << QString("Archivo no encontrado.");
        _File.close();

        std::ofstream Temp;
        Temp.open(this->m_File, std::ios::out); // Creates the file
        for(auto _data : this->m_NFData){
            Temp << _data + "\n"; // Writes the creation data (if any)
        }
        Temp.close(); //

        /*for(int i = 0, j = 0; i < this->m_NFData.length(); i++){

            if(this->m_NFData[i] == 92 && this->m_NFData[i + 1] == 'n'){ // Ascii 92 == "\"
                j++; i++;
                continue;
            }
            m_Data[j] += this->m_NFData[i];
        }*/ /// Updates the Data array with the new info in file

        _File.open(this->m_File, std::ios::in);
        if(_File.fail()) [[unlikely]]{ // Checks if the file was created successfully
            exit(-404); // Exits with error if not
        }
    } // End if(Fail)
    {
        std::string Temp;
        while(!_File.eof()){
            std::getline(_File, Temp); // Reads data from file
            this->m_Data.push_back(Temp); // Stores data in variable
        }
    }
    _File.close();
    return;
}

void fmanager::writeFile()
{
    std::ofstream _File;
    _File.open(this->m_File, std::ios::out); // Opens / Create file

    for(std::string s : this->m_Data){ // Writes the data from variable to file
        _File << s + "\n";
    }

    _File.close();
    return;
}
