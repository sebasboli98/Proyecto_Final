#include "fmanager.h"

fmanager::fmanager(const std::string& File_)
    : m_File(File_), m_Data(), m_NFData()
{
    return;
}

std::vector<std::string> fmanager::getFileData()
{
    readFile(); // Read file and updates data in variable
    return m_Data;
}

void fmanager::setFileData(const std::vector<std::string> &NewData_)
{
    m_Data = NewData_; // Sets the data variable to the desired data
    writeFile(); // Writes new data to file
    return;
}

void fmanager::changeFile(const std::string &NewFile_)
{
    m_File = NewFile_; // Change file dir to access
    m_Data = {}; // Resets the data in variable
    return;
}

void fmanager::newFileData(const std::vector<std::string> &Data_)
{
    m_NFData = Data_; // Stores the data to write if a file is created
    return;
}

void fmanager::overrideFileData(std::vector<std::string> NewData_)
{
    std::ofstream _File;
    _File.open(m_File, std::ios::out); // Opens or create the file
    for(auto _data : NewData_)
        _File << _data + "\n"; // Writes NewData_ into file
    return;
}

void fmanager::overrideFileData(std::string NewData_)
{
    std::ofstream _File;
    _File.open(m_File, std::ios::out); // Opens or create the file
    _File << NewData_ + "\n"; // Writes NewData_ into file
    return;
}

void fmanager::appendFileData(std::vector<std::string> NewData_)
{
    std::ofstream _File;
    _File.open(m_File, std::ios::app); // Opens the file
    for(auto _data : NewData_)
        _File << _data + "\n"; // Writes NewData_ at the end of file
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
