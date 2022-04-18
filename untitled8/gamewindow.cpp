#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <iostream>



gamewindow::gamewindow(gvr::udpair playerData_, QWidget *parent) ://Constructor
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
    MenuScene->setSceneRect(0,0,1000000,5000);

    ui->MainView->setScene(MenuScene);
    //MenuView->setScene(MenuScene);

    std::array<std::vector<std::string>, 5> pTextures;
    pTextures[0].push_back(":/gfx/Sprites/nigga.png");
    pTextures[1].push_back(":/gfx/Sprites/niggacostao.png");

    p = new player(400, 300);
    p->setTextures(pTextures);
    MenuScene->addItem(p);

    AddBlocks();

    ui->MainView->centerOn(p);
    ui->MainView->ensureVisible(p);

    enableCollitions();
    StartCollitions(16);
    enableMovement();
    StartMovement(32);

    ui->MainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->MainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //MenuView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //MenuView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->label->setText("Corre Perra Corre!");
    m_GameRunning = false;

}

gamewindow::~gamewindow()
{
    delete ui;
}

void gamewindow::keyPressEvent(QKeyEvent *Event){m_keys[Event->key()] = true; QWidget::keyPressEvent(Event);}
void gamewindow::keyReleaseEvent(QKeyEvent *Event){m_keys[Event->key()] = false; QWidget::keyReleaseEvent(Event);}

void gamewindow::mousePressEvent(QMouseEvent *Event){
    if(Event->button() == Qt::LeftButton)
        p->Shoot(Event->pos().x(), Event->pos().y());
}

void gamewindow::mouseMoveEvent(QMouseEvent *Event){
    if(p->isShootCooldownActive())
        return;

    // Dibujar linea de apuntar

}

void gamewindow::AddBlocks()//
{

    block *b = new block(1,0,1);
    b->setPos(400, 300);
    b->setLinealSpeed(5, -2);
    b->setLinealAcceleration(5, -5);
    //b->setAngularSpeed(45);

    MenuScene->addItem(b);

    for(int i = 5000; i > 0; i--){
        b = new block(1,0,0);
        b->setPos((80 * i), 500);
        MenuScene->addItem(b);
    }

    for(int i = 1500; i > 0; i--){
        b = new block(1,0,0);
        b->setPos((480 * i), 420);
        MenuScene->addItem(b);
    }

    // Usar datos leidos
}

void gamewindow::enableCollitions(){//Jugador colisione con otros objetos
    m_Collitions = new QTimer();
    connect(m_Collitions, &QTimer::timeout, [&](){
        // Player collitions
        QList<QGraphicsItem *> CollidingItems_ = p->collidingItems();

        if(CollidingItems_.isEmpty()){}

        for(auto i : CollidingItems_){
            block *b = dynamic_cast<block *>(i);

            if(b && b->isSolid()){
                if((p->y() <= b->y()) &&
                   ((p->x() - b->x()) < (b->pixmap().width() * 0.5))){
                    p->setSpeedY(0);
                    p->setOnGround(true);
                }
                else if(false){

                }

            }
            else if(proyectile *p = dynamic_cast<proyectile *>(i)){


            }
            else if(enemy *e = dynamic_cast<enemy *>(i)){

            }
            else if(checkpoint *e = dynamic_cast<checkpoint *>(i)){

            }
        }
    });
}

void gamewindow::StartCollitions(uint t){m_Collitions->start(t);}
void gamewindow::StopCollitions(){m_Collitions->stop();}

void gamewindow::enableMovement(){ //Lista de las teclas
    m_KeyTimer = new QTimer();//Moviemintos
    connect(m_KeyTimer, &QTimer::timeout, [&](){
        ;
        for(auto i : m_keys){
            if(i.second)
            switch (i.first) {
            case Qt::Key_W:{
                if(p->isSliding()){
                    p->setSliding(false);
                    return;
                }
                if(p->onGround()){
                    p->Jump();
                    return;
                }
                break;
            }
            case Qt::Key_A:{
                if(p->getLinealSpeed().first > 0 && !p->isSliding())
                    p->setAccelerationX(p->getLinealAcceleration().first - 50);
                break;
            }
            case Qt::Key_S:{
                if(p->onGround())
                    p->Slide();
                break;
            }
            case Qt::Key_D:{
                if(!p->isSliding())
                    p->setAccelerationX(p->getLinealAcceleration().first + 20);
                break;
            }
            case Qt::Key_Space:{
                if(p->isSliding()){
                    p->setSliding(false);
                    p->Jump();
                }
                if(p->onGround())
                    p->Jump();
                break;
            }
            default:
                break;
            }
        }
    });
}

void gamewindow::StartMovement(uint ms){m_KeyTimer->start(ms);}
void gamewindow::StopMovement(){m_KeyTimer->stop();}
