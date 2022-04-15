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
    explicit registerwindow(bool mode_, QWidget *parent = nullptr);
    ~registerwindow();

private:
    bool loginUser(std::string UserName_, std::string UserPass_);
    bool registerUser(std::string UserName_, std::string Pass_, std::string Mail_);

private slots:
    void on_Continue_clicked();
    void on_Exit_clicked();

private:
    Ui::registerwindow *ui;
    gamewindow *gw;
    fmanager *m_fmanager;

    gvr::udat m_usersData; // Username {Pass, Email}
    std::vector<std::string> m_levelData;

    bool m_mode;

};

#endif // REGISTERWINDOW_H
