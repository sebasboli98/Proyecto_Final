#include "gamewindow.h"
#include "ui_gamewindow.h"

gamewindow::gamewindow(gvr::udpair playerData_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewindow),
    m_playerData(playerData_)
{
    ui->setupUi(this);
}

gamewindow::~gamewindow()
{
    delete ui;
}
