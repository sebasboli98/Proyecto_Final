#include "fmanager.h"

fmanager::fmanager(const std::string& File_)
    : m_File(File_), m_Data(), m_NFData("")
{
    readFile();
    return;
}

std::vector<std::string> fmanager::getFileData()
{
    return m_Data;
}

void fmanager::setFileData(const std::vector<std::string> &NewData_)
{
    m_Data = NewData_;
    writeFile();
    return;
}

void fmanager::changeFile(const std::string &NewFile_)
{
    m_File = NewFile_;
    readFile();
    return;
}

void fmanager::newFileData(const std::string &Data_)
{
    m_NFData = Data_;
    return;
}

void fmanager::readFile()
{
    std::ifstream _File;
    _File.open( this->m_File , std::ios::in);
    if(_File.fail()){
        qDebug() << QString("Archivo no encontrado.");
        _File.close();

        std::ofstream Temp;
        Temp.open( this->m_File , std::ios::out);
        Temp << this->m_NFData + "\n";
        Temp.close();

        /*for(int i = 0, j = 0; i < this->m_NFData.length(); i++){

            if(this->m_NFData[i] == 92 && this->m_NFData[i + 1] == 'n'){ // Ascii 92 == "\"
                j++; i++;
                continue;
            }
            m_Data[j] += this->m_NFData[i];
        }*/ /// Updates the Data array with the new info in file

        _File.open( this->m_File , std::ios::in);
        if(_File.fail());
           // exit(-404);
    }
    {
        std::string Temp;
        while(!_File.eof()){
            std::getline(_File, Temp);
            this->m_Data.push_back(Temp);
        }
    }
    return;
}

void fmanager::writeFile()
{
    std::ofstream _File;
    _File.open("../VolatileRush/Files/" + this->m_File + ".txt", std::ios::out);

    for(std::string s : this->m_Data){
        _File << s + "\n";
    }

    _File.close();
    return;
}
