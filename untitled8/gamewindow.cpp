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

    MenuScene = new CustomScene();
    MenuScene->setSceneRect(0,0,1000000,5000);

    ui->MainView->setScene(MenuScene);
    //MenuView->setScene(MenuScene);

    std::array<std::vector<std::string>, 5> pTextures;
    pTextures[0].push_back(":/gfx/Sprites/nigga.png");
    pTextures[1].push_back(":/gfx/Sprites/niggacostao.png");

    //proyectile *GCast = new proyectile(":gfx/Images/WoodBox.png");

    p = new player(400, 300);
    p->setTextures(pTextures);
    //p->createProyectileCast(":/gfx/Images/WoodBox.png", "");
    MenuScene->addItem(p);

    Test1 = new explotion(":/gfx/Images/rexplotion.png", "");

    AddBlocks();

    ui->MainView->scale(0.5, 0.5);
    ui->MainView->centerOn(p);
    ui->MainView->ensureVisible(p);

    enableCollitions();
    StartCollitions(16);
    enableMovement();
    StartMovement(32);

    ui->MainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->MainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->MainView->viewport()->setMouseTracking(true);
    //MenuView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //MenuView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->label->setText("Una mondaa de titulo :v");
    m_keys = {};
    m_GameRunning = false;

}

gamewindow::~gamewindow()
{
    delete ui;
}

void gamewindow::keyPressEvent(QKeyEvent *Event){m_keys.push(Event->key()); QWidget::keyPressEvent(Event);}
void gamewindow::keyReleaseEvent(QKeyEvent *Event){QWidget::keyReleaseEvent(Event);}

void gamewindow::mousePressEvent(QMouseEvent *Event){
    if(Event->button() == Qt::LeftButton){
        //qDebug() << "ScX: " << QString::number(MenuScene->ClickPos.x());
        //qDebug() << "ScY: " << QString::number(MenuScene->ClickPos.y());

        //qDebug() << "PosX: " << QString::number(MenuScene->MousePos.x());
        //qDebug() << "PosY: " << QString::number(MenuScene->MousePos.y());

        float SceneClickPosX = MenuScene->ClickPos.x();
        float SceneClickPosY = MenuScene->ClickPos.y();

        if(proyectile *Temp = p->Shoot(SceneClickPosX, SceneClickPosY)){
            MenuScene->addItem(Temp);
        }



        explotion *Test2 = new explotion(SceneClickPosX, SceneClickPosY, Test1);
        ui->MainView->scene()->addItem(Test2);
        Test2->Explode();
    }

}

void gamewindow::mouseMoveEvent(QMouseEvent *Event){

    //qDebug() << "PosX: " << QString::number(MenuScene->MousePos.x());
    //qDebug() << "PosY: " << QString::number(MenuScene->MousePos.y());

    Event->button();

    // Dibujar linea de apuntar

}

void gamewindow::AddBlocks()
{

    block *b = new block(1,0,1);
    b->setPos(400, 300);
    b->setLinealSpeed(5, -2);
    b->setLinealAcceleration(5, -5);
    b->setAngularSpeed(1);

    //MenuScene->addItem(b);

    for(int i = 5000; i > 0; i--){
        b = new block(1,0,0);
        b->setPos((80 * i), 1000);
        MenuScene->addItem(b);
    }

    b = new block(1,0,0);
    b->setPos((160), 1400);
    b->setRotation(30);
    MenuScene->addItem(b);

    for(int i = 1500; i > 0; i--){
        b = new block(1,0,0);
        b->setPos((160 * i), 1420);
        MenuScene->addItem(b);
    }

    // Usar datos leidos
}

void gamewindow::enableCollitions(){
    m_Collitions = new QTimer();
    connect(m_Collitions, &QTimer::timeout, [&](){
        // Player collitions
        QList<QGraphicsItem *> CollidingItems_ = p->collidingItems();

        if(CollidingItems_.isEmpty()){}

        for(auto i : CollidingItems_){
            block *b = dynamic_cast<block *>(i);

            if(b && b->isSolid()){
                if((p->y() <= b->y()) &&
                   ((p->x() - b->x()) < (b->pixmap().width()))){
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

void gamewindow::enableMovement(){
    m_KeyTimer = new QTimer();
    connect(m_KeyTimer, &QTimer::timeout, [&](){

        qDebug() << "PosX: " << QString::number(MenuScene->MousePos.x());
        qDebug() << "PosY: " << QString::number(MenuScene->MousePos.y());
        ui->label->setText(QString::number(MenuScene->MousePos.x()) + " " + QString::number(MenuScene->MousePos.y()));

        while(true){
            if(m_keys.empty())
                break;

            switch (m_keys.front()) {
            case Qt::Key_W:{
                if(p->isSliding()){
                    p->setSliding(false); //
                    m_keys.pop();
                    return;
                }
                if(p->onGround()){
                    p->Jump();
                    m_keys.pop();
                    return;
                }
                m_keys.pop();
                break;
            }
            case Qt::Key_A:{
                if(p->getLinealSpeed().first > 0 && !p->isSliding()){
                    p->setAccelerationX(p->getLinealAcceleration().first - 4);
                }
                m_keys.pop();
                break;
            }
            case Qt::Key_S:{
                if(p->onGround()){
                    p->Slide();
                }
                m_keys.pop();
                break;
            }
            case Qt::Key_D:{
                if(!p->isSliding()){
                    p->setAccelerationX(p->getLinealAcceleration().first + 10);
                }
                m_keys.pop();
                break;
            }
            case Qt::Key_Space:{
                if(p->isSliding()){
                    p->setSliding(false);
                    p->Jump();
                }
                if(p->onGround()){
                    p->Jump();
                }
                m_keys.pop();
                break;
            }
            case Qt::Key_E:{

                m_keys.pop();
                break;
            }
            default:{
                m_keys.pop();
                break;
            }
            }
        }
        if(p->getLinealSpeed().first < 10 && !p->isSliding()){
            p->setAccelerationX(p->getLinealAcceleration().first + 17);
        }
    });
}

void gamewindow::StartMovement(uint ms){m_KeyTimer->start(ms);}
void gamewindow::StopMovement(){m_KeyTimer->stop();}
