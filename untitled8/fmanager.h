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
    std::vector<std::string> getFileData();
    void setFileData(const std::vector<std::string>&);
    // Change file to read / write
    void changeFile(const std::string&);
    // Data to write when a file is created
    void newFileData(const std::vector<std::string>&);
    // Direct changes to data in file
    void overrideFileData(std::vector<std::string> NewData);
    void overrideFileData(std::string NewData);
    void appendFileData(std::vector<std::string> NewData);
    void appendFileData(std::string NewData);
    void deleteFileData();

private:
    // Implementation of reading / writting of files
    void readFile();
    void writeFile();

public:

private:
    std::string m_File; // Current file using
    std::vector<std::string> m_Data; // Data from file
    std::vector<std::string> m_NFData; // Data to write when file does not exists

};


#endif // FMANAGER_H
