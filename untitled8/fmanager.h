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

    std::vector<std::string> getFileData();
    void setFileData(const std::vector<std::string>&);

    void changeFile(const std::string&);

    void newFileData(const std::vector<std::string>&);

private:
    void readFile();
    void writeFile();

public:

private:
    std::string m_File;
    std::vector<std::string> m_Data;
    std::vector<std::string> m_NFData;

};


#endif // FMANAGER_H
