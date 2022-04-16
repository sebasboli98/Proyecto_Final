#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <iostream>



gamewindow::gamewindow(gvr::udpair playerData_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewindow),
    m_playerData(playerData_)
{
    ui->setupUi(this);
    setWindowTitle("Volatile Rush dev 0.1.0");

    //MenuView = ui->MainView;
    //MenuView->setBackgroundBrush(QBrush(QImage(":/gfx/Images/Fondo.jfif")));
    //MenuView->resize(this->width(), this->height());
    //ui->MainView->showMaximized();
    //ui->MainView->setWindowState(Qt::WindowMaximized);
    //ui->MainView->updateGeometry();
    ui->MainView->resize(1920, 1000);

    MenuScene = new QGraphicsScene();
    MenuScene->setSceneRect(0,0,10000,5000);

    ui->MainView->setScene(MenuScene);
    //MenuView->setScene(MenuScene);


    block *b = new block(1,0,1);
    b->setPos(400, 400);
    b->setLinealSpeed(5, -2);
    b->setLinealAcceleration(5, -5);
    //b->setAngularSpeed(45);

    MenuScene->addItem(b);

    b = new block(1,0,0);
    b->setPos(480, 500);
    MenuScene->addItem(b);
    b = new block(1,0,0);
    b->setPos(560, 500);
    MenuScene->addItem(b);
    b = new block(1,0,0);
    b->setPos(640, 500);
    MenuScene->addItem(b);
    b = new block(1,0,0);
    b->setPos(720, 500);
    MenuScene->addItem(b);

    ui->MainView->centerOn(b);
    ui->MainView->ensureVisible(b);

    ui->MainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->MainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //MenuView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //MenuView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

gamewindow::~gamewindow()
{
    delete ui;
}

void gamewindow::keyPressEvent(QKeyEvent *Event)
{

}

void gamewindow::AddBlocks()
{

}

void gamewindow::enableCollitions(){
    m_Collitions = new QTimer();
    connect(m_Collitions, &QTimer::timeout, [](){
        //QList<QGraphicsItem *> CollidingItems_ = ;
    });
}

void gamewindow::StartCollitions(uint t){m_Collitions->start(t);}
void gamewindow::StopCollitions(){m_Collitions->stop();}
