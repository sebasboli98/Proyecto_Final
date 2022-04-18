#ifndef FMANAGER_H
#define FMANAGER_H

#include <fstream>
#include <string>
#include <vector>

#include <QDebug>

class fmanager
{
public:
    fmanager(const std::string&);

    // File Data getter / setter
    std::vector<std::string> getFileData(); //Obtenemos los datos
    void setFileData(const std::vector<std::string>&); //Guardamos los datos
    // Change file to read / write
    void changeFile(const std::string&); //Cambiar archivo o editar
    // Data to write when a file is created
    void newFileData(const std::vector<std::string>&); //Datos a guardar si el archivo no existe
    // Direct changes to data in file

    //Cambios directos al archivo
    void overrideFileData(std::vector<std::string> NewData); // sobreesscrivir el archivo
    void overrideFileData(std::string NewData); // sobreesscrivir el archivo
    void appendFileData(std::vector<std::string> NewData); //Al final del archivo agregamos los datos deseados dejando el archivo como se encuentra
    void appendFileData(std::string NewData);
    void deleteFileData(); //Se borran los datos del archivo

private:
    // Implementation of reading / writting of files
    void readFile();
    void writeFile();

public:

private:
    std::string m_File; // Current file using -  Direccion del archivo
    std::vector<std::string> m_Data; // Data from file - Datos pertenecientes a la direccion del archivo
    std::vector<std::string> m_NFData; // Data to write when file does not exists - contiene los datos a colocar si no existe

};


#endif // FMANAGER_H
