#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <iostream>



gamewindow::gamewindow(gvr::udpair playerData_, gvr::udat allData_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewindow),
    m_playerData(playerData_), m_allData(allData_)
{
    ui->setupUi(this);
    setWindowTitle("Corre perra corre");

    //MenuView = ui->MainView;
    //MenuView->setBackgroundBrush(QBrush(QImage(":/gfx/Images/Fondo.jfif")));
    //MenuView->resize(this->width(), this->height());
    //ui->MainView->showMaximized();
    //ui->MainView->setWindowState(Qt::WindowMaximized);
    //ui->MainView->updateGeometry();
    ui->MainView->resize(1920, 1000); // Me rendí
    ui->MainView->scale(1.5,1.5);

    MenuScene = new CustomScene();
    MenuScene->setBackgroundBrush(QBrush(QImage(":/gfx/Images/Fondo.jpg")));
    MenuScene->setSceneRect(0, 0, 1920, 1000);
    ui->MainView->setScene(MenuScene);

    AddWidgets();

    LoadData();

    //proyectile *GCast = new proyectile(":gfx/Images/WoodBox.png");
    //Test1 = new explotion(":/gfx/Images/rexplotion.png", "");
    //Test1->setEnergy(100);

    ui->MainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->MainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->MainView->viewport()->setMouseTracking(true);
    //MenuView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //MenuView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->label->setText("");
    m_keys = {};
    m_Clicks = {};
    m_GameRunning = false;

}

gamewindow::~gamewindow()
{
    delete ui;
}

void gamewindow::keyPressEvent(QKeyEvent *Event){m_keys.push({Event->key(), true}); QWidget::keyPressEvent(Event);}
void gamewindow::keyReleaseEvent(QKeyEvent *Event){m_keys.push({Event->key(), false}); QWidget::keyReleaseEvent(Event);}

void gamewindow::mousePressEvent(QMouseEvent *Event){
    m_Clicks.push({{Event->button(), true},{GameScene->ClickPos.x(), GameScene->ClickPos.y()}});
    QWidget::mousePressEvent(Event);
}

void gamewindow::mouseReleaseEvent(QMouseEvent *Event){
    m_Clicks.push({{Event->button(), false},{GameScene->ClickPos.x(), GameScene->ClickPos.y()}});
    QWidget::mouseReleaseEvent(Event);
}

void gamewindow::MainMenu(){
    ui->MainView->setScene(MenuScene);

    StopCollitions();
    StopMovement();
    StopClicks();

    RemoveEntities();
    RemovePlayer();
    RemoveBlocks();

    m_Buttons[0]->show();
    m_Buttons[1]->show();
    m_Buttons[2]->show();

}

void gamewindow::LoadData(){
    m_fmanager = new fmanager("../untitled8/Files/config.dat");
    m_fmanager->newFileData({"../untitled8/Files/enckey.dat","../untitled8/Files/players.dat"});
    m_fmanager->changeFile(m_fmanager->getFileData()[1]);
}

void gamewindow::SaveData(){
    m_allData[m_playerData.first[1] + m_playerData.first[0]].second = m_playerData.second;
    std::vector<std::string> fd = {};

    for(auto data_ : m_allData){
        fd.push_back(   data_.first  + ";" +
                                data_.second.first[0] + ";" +
                                data_.second.first[1] + ";" +
                                data_.second.first[2] + ";" +
                                std::to_string(data_.second.second[0]).c_str() + ";" +
                                std::to_string(data_.second.second[1]).c_str() + ";" +
                                std::to_string(data_.second.second[2]).c_str());
    }
    m_fmanager->changeFile("../untitled8/Files/players.dat");
    m_fmanager->overrideFileData(fd);
}

//void gamewindow::mouseMoveEvent(QMouseEvent *Event){
//
//    //qDebug() << "PosX: " << QString::number(MenuScene->MousePos.x());
//    //qDebug() << "PosY: " << QString::number(MenuScene->MousePos.y());
//
//    Event->button();
//
//    // Dibujar linea de apuntar
//
//}

void gamewindow::AddBlocks()
{
    m_fmanager->changeFile("../untitled8/Files/level" + std::to_string(m_playerData.second[0]) + "layout.dat");
    m_BlockMap = m_fmanager->getFileData();

    uint y = 0;
    uint x = 0;
    uint Count = 0;

    for(auto line_ : m_BlockMap){
        for(auto b : line_){
            switch (b) {
            case '*':
                m_Blocks.push_back(new block(1, 0, 0));
                m_Blocks[Count]->setPos(x * 80, y * 80);
                GameScene->addItem(m_Blocks[Count]);
                ++Count;
                break;
            case 'h':
                m_Blocks.push_back(new block(0, 0, 0));
                m_Blocks[Count]->setPixmap(QPixmap(":/gfx/Images/MarcoMadera.png").scaled(80, 80));
                m_Blocks[Count]->setPos(x * 80, y * 80);
                GameScene->addItem(m_Blocks[Count]);
                ++Count;
                break;
            case '#':
                m_Blocks.push_back(new block(1, 1, 1));
                m_MovableBlocks.push_back(m_Blocks[Count]);
                m_Blocks[Count]->setPixmap(QPixmap(":/gfx/Images/WoodBox.png").scaled(80, 80));
                m_Blocks[Count]->setPos(x * 80, y * 80);
                GameScene->addItem(m_Blocks[Count]);
                ++Count;
                break;
            case 'c':
                m_Checkpoints.push_back(new checkpoint(x * 80, y * 80));
                m_Checkpoints[m_Checkpoints.size() - 1]->setRespawn({x * 80, y * 80});
                GameScene->addItem(m_Checkpoints[m_Checkpoints.size() - 1]);
            default:
                break;
            }
            ++x;
        }
        ++y;
        x = 0;
    }

    //block *b = new block(1,0,1);
    //b->setPos(400, 300);
    //b->setLinealSpeed(5, -2);
    //b->setLinealAcceleration(5, -5);
    //b->setAngularSpeed(1);

    ////MenuScene->addItem(b);

    //for(int i = 5000; i > 0; i--){
    //    b = new block(1,0,0);
    //    b->setPos((80 * i), 1500);
    //    GameScene->addItem(b);
    //}

    //for(int i = 1000; i > 5; i--){
    //    b = new block(1,0,0);
    //    b->setPos((80 * i), 1100);
    //    GameScene->addItem(b);
    //}

    //b = new block(1,0,0);
    //b->setPos((160), 1400);
    //b->setRotation(30);
    //GameScene->addItem(b);

    //for(int i = 1500; i > 0; i--){
    //    b = new block(1,0,0);
    //    b->setPos((160 * i), 1420);
    //    GameScene->addItem(b);
    //}
}

void gamewindow::AddEntities(){
    m_fmanager->changeFile("../untitled8/Files/level" + std::to_string(m_playerData.second[0]) + "enemies.dat");
    std::vector<std::string> m_EnemieMap = m_fmanager->getFileData();

    uint y = 0;
    uint x = 0;
    uint Count = 0;
    explotion * Cast = new explotion(":/gfx/Images/rexplotion.png", "");
    Cast->setEnergy(10000);
    Cast->setDuration(10);
    Cast->setSizeMin(60, 60);
    Cast->setSizeMax(180, 180);

    proyectile *gCast = new proyectile(":/gfx/Images/WoodBox.png","");
    gCast->setMass(2);
    gCast->setDragQ(0.6);
    gCast->setTransversalArea(0.8);
    gCast->setExplotionCast(Cast);
    gCast->setScale(20, 5);

    for(auto line_ : m_EnemieMap){
        for(auto c : line_){
            switch (c) {
            case 'g':
                m_Enemies.push_back(new enemy(x * 80, y * 80));
                m_Enemies[Count]->setPixmap(QPixmap(":/gfx/Sprites/nigga.png").scaled(77, 180));
                m_Enemies[Count]->setAmmo(gCast);
                m_Enemies[Count]->setObjective(m_Player);
                GameScene->addItem(m_Enemies[Count]);
                ++Count;
                break;
            case 'b':
                m_Enemies.push_back(new enemy(x * 80, y * 80));
                m_Enemies[Count]->setPixmap(QPixmap(":/gfx/Sprites/nigga.png").scaled(77, 180));
                m_Enemies[Count]->setAmmo();
                m_Enemies[Count]->setObjective(m_Player);
                GameScene->addItem(m_Enemies[Count]);
                ++Count;
                break;
            default:
                break;
            }
            ++x;
        }
        ++y;
        x = 0;
    }
}

void gamewindow::AddPlayer(){
    std::array<std::vector<std::string>, 5> pTextures;
    pTextures[0].push_back(":/gfx/Sprites/nigga.png");
    pTextures[1].push_back(":/gfx/Sprites/niggacostao.png");

    explotion * PEC = new explotion(":/gfx/Images/rexplotion.png", "");
    PEC->setEnergy(10000);
    PEC->setDuration(10);
    PEC->setSizeMin(60, 60);
    PEC->setSizeMax(180, 180);

    auto Pos_ = m_Checkpoints[m_playerData.second[1]]->getRespawn();

    m_Player = new player(Pos_.first, Pos_.second);
    m_Player->setTextures(pTextures);
    m_Player->createProyectileCast(":/gfx/Images/WoodBox.png", "", PEC);
    GameScene->addItem(m_Player);

    ui->MainView->centerOn(m_Player);
    ui->MainView->ensureVisible(m_Player);
}

void gamewindow::AddWidgets(){

    m_Buttons.push_back(new QPushButton("Campaña", this));
    m_Buttons.push_back(new QPushButton("Supervivencia (WIP)", this));
    m_Buttons.push_back(new QPushButton("Salir", this));

    m_Buttons[0]->setGeometry((MenuScene->width() * 0.5f) - 250, MenuScene->height() * 0.4f, 500, 100);
    m_Buttons[1]->setGeometry((MenuScene->width() * 0.5f) - 250, MenuScene->height() * 0.6f, 500, 100);
    m_Buttons[2]->setGeometry((MenuScene->width() * 0.5f) - 250, MenuScene->height() * 0.8f, 500, 100);

    //m_Buttons[0]->setIcon(QIcon(":/gfx/Images/wtabla.png"));// ":/gfx/Images/wtabla.png"
    //m_Buttons[1]->setIcon(QIcon(":/gfx/Images/wtabla.png"));
    //m_Buttons[2]->setIcon(QIcon(":/gfx/Images/wtabla.png"));

    //m_Buttons[0]->setStyleSheet(":/gfx/Images/wtabla.png");
    //m_Buttons[1]->setStyleSheet(":/gfx/Images/wtabla.png");
    //m_Buttons[2]->setStyleSheet(":/gfx/Images/wtabla.png");

    connect(m_Buttons[0], SIGNAL(clicked()), this, SLOT(CampaignButton()));
    connect(m_Buttons[1], SIGNAL(clicked()), this, SLOT(SurvivalButton()));
    connect(m_Buttons[2], SIGNAL(clicked()), this, SLOT(ExitButton()));

    MenuScene->addWidget(m_Buttons[0]);
    MenuScene->addWidget(m_Buttons[1]);
    MenuScene->addWidget(m_Buttons[2]);
}

void gamewindow::RemoveBlocks(){

}

void gamewindow::RemoveEntities(){
    for(auto i : m_Enemies){
        i->setObjective(nullptr);
        i->UpdateStop();
        delete i;
    }
}

void gamewindow::RemovePlayer(){
    m_Player->UpdateStop();
    delete m_Player;
    m_Player = nullptr;
}

void gamewindow::enableCollitions(){
    m_CollitionsTimer = new QTimer();
    connect(m_CollitionsTimer, &QTimer::timeout, [&](){
        // Player collitions

        if(m_Player->getHP() <= 0){
            m_Player->setPos(400, 1400);
            if(m_playerData.second[1] > 0){
                auto pos_ = m_Checkpoints[m_playerData.second[1]]->getRespawn(); m_Player->setPos(pos_.first, pos_.second);
            }

            m_Player->setHP(1000);
            m_Player->setLinealAcceleration(0, 0);
            m_Player->setLinealSpeed(0, 0);
            m_Player->UpdateStart(16);
        }

        QList<QGraphicsItem *> CollidingItems_ = m_Player->collidingItems();
        uint Count = 0;

        if(!CollidingItems_.isEmpty()){
            for(auto i : CollidingItems_){
                block *b = dynamic_cast<block *>(i);
                proyectile *p = dynamic_cast<proyectile *>(i);
                explotion *e = dynamic_cast<explotion *>(i);
                checkpoint *cp = dynamic_cast<checkpoint *>(i);

                if(b && b->isSolid()){
                    if(b->isMovable()){
                        m_Player->Collition(b->getMass(), b->getRestitutionQ(), b->getLinealSpeed());
                        b->Collition(m_Player->getMass(), 0.3f, m_Player->getLinealSpeed());
                    }

                    if((m_Player->y() <= b->y()) &&
                       ((m_Player->x() - b->x()) < (b->pixmap().width()))){
                        m_Player->setSpeedY(0);
                        m_Player->setOnGround(true);
                    }
                    else if(false){

                    }

                }
                else if(p){
                    explotion *e = dynamic_cast<explotion *>(p->Collition());
                    if(e){
                        delete p;
                        ui->MainView->scene()->addItem(e);
                        e->Explode();
                        continue;
                    }
                    m_Player->Collition(p->getMass(), 0, p->getLinealSpeed());
                    delete p;
                    continue;
                }
                else if(e && !e->wasAffect(m_Player)){
                    e->setObjectAffected(m_Player);
                    m_Player->Collition(e->getEnergy(), {e->x(), e->y()});
                    continue;
                }
                else if(cp && m_playerData.second[1] < 1){
                    m_playerData.second[1] += 1;
                    m_allData[m_playerData.first[1] + m_playerData.first[0]].second[1] += 1;
                    SaveData();
                }
                // else if(letalobject *lo = dynamic_cast<letalobject *>(i)){}
            }
        }
        Count = 0;
        for(auto enemy_ : m_Enemies){
            if(enemy_->getHitpoints() <= 0){
                delete enemy_;
                m_MovableBlocks.erase(m_MovableBlocks.begin() + Count);
                continue;
            }

            CollidingItems_ = enemy_->collidingItems();

            if(!CollidingItems_.isEmpty()){
                for(auto i : CollidingItems_){
                    block *b = dynamic_cast<block *>(i);
                    proyectile *p = dynamic_cast<proyectile *>(i);
                    explotion *e = dynamic_cast<explotion *>(i);

                    if(b && b->isSolid()){
                        if(b->isMovable()){
                            enemy_->Collition(b->getMass(), b->getRestitutionQ(), b->getLinealSpeed());
                            b->Collition(enemy_->getMass(), 0.3f, enemy_->getLinealSpeed());
                        }

                        if((enemy_->y() <= b->y()) &&
                           ((enemy_->x() - b->x()) < (b->pixmap().width()))){
                            enemy_->setSpeedY(0);
                            enemy_->setOnGround(true);
                        }
                        else if(false){

                        }

                    }
                    else if(p){
                        explotion *e = dynamic_cast<explotion *>(p->Collition());
                        if(e){
                            delete p;
                            ui->MainView->scene()->addItem(e);
                            e->Explode();
                            continue;
                        }
                        enemy_->Collition(p->getMass(), 0, p->getLinealSpeed());
                        delete p;
                        continue;
                    }
                    else if(e && !e->wasAffect(enemy_)){
                        e->setObjectAffected(enemy_);
                        enemy_->Collition(e->getEnergy(), {e->x(), e->y()});
                        continue;
                    }
                    // else if(letalobject *lo = dynamic_cast<letalobject *>(i)){}
                }
            }
            Count++;
        }
        Count = 0;
        for(auto block_ : m_MovableBlocks){

            if(block_->getHitpoints() <= 0){
                delete block_;
                m_MovableBlocks.erase(m_MovableBlocks.begin() + Count);
                continue;
            }

            CollidingItems_ = block_->collidingItems();

            if(!CollidingItems_.isEmpty()){
                for(auto i : CollidingItems_){
                    block *b = dynamic_cast<block *>(i);
                    proyectile *p = dynamic_cast<proyectile *>(i);
                    explotion *e = dynamic_cast<explotion *>(i);

                    if(b && b->isSolid()){
                        if(b->isMovable()){
                            block_->Collition(b->getMass(), b->getRestitutionQ(), b->getLinealSpeed());
                            b->Collition(block_->getMass(), block_->getRestitutionQ(), block_->getLinealSpeed());
                        }

                        if((block_->y() <= b->y()) && ((block_->x() - b->x()) < (b->pixmap().width()))){
                            block_->setSpeedY(0);
                            block_->setOnGround(true);
                        }
                        else if(false){

                        }

                    }
                    else if(p){
                        explotion *e = dynamic_cast<explotion *>(p->Collition());
                        if(e){
                            delete p;
                            ui->MainView->scene()->addItem(e);
                            e->Explode();
                            continue;
                        }
                        block_->Collition(p->getMass(), block_->getRestitutionQ(), p->getLinealSpeed());
                        delete p;
                        continue;
                    }
                    else if(e && !e->wasAffect(block_)){
                        e->setObjectAffected(block_);
                        block_->Collition(e->getEnergy(), {e->x(), e->y()});
                        continue;
                    }
                    // else if(letalobject *lo = dynamic_cast<letalobject *>(i)){}
                }
            }
            Count++;
        }
        Count = 0;
    });
}
void gamewindow::StartCollitions(uint t){m_CollitionsTimer->start(t);}
void gamewindow::StopCollitions(){m_CollitionsTimer->stop();}

void gamewindow::enableMovement(){
    m_KeyTimer = new QTimer();
    connect(m_KeyTimer, &QTimer::timeout, [&](){

        //qDebug() << "PosX: " << QString::number(MenuScene->MousePos.x());
        //qDebug() << "PosY: " << QString::number(MenuScene->MousePos.y());
        //ui->label->setText(QString::number(GameScene->MousePos.x()) + " " + QString::number(GameScene->MousePos.y()));

        while(!m_keys.empty()){
            switch (m_keys.front().first) {
            case Qt::Key_W:{
                if(m_Player->isSliding()){
                    m_Player->setSliding(false); //
                    m_keys.pop();
                    return;
                }
                if(m_Player->onGround()){
                    m_Player->Jump();
                    m_keys.pop();
                    return;
                }
                m_keys.pop();
                break;
            }
            case Qt::Key_A:{
                if(m_Player->getLinealSpeed().first > 0 && !m_Player->isSliding()){
                    m_Player->setAccelerationX(m_Player->getLinealAcceleration().first - 4);
                }
                m_keys.pop();
                break;
            }
            case Qt::Key_S:{
                if(m_Player->onGround()){
                    m_Player->Slide();
                }
                m_keys.pop();
                break;
            }
            case Qt::Key_D:{
                if(!m_Player->isSliding()){
                    m_Player->setAccelerationX(m_Player->getLinealAcceleration().first + 10);
                }
                m_keys.pop();
                break;
            }
            case Qt::Key_Space:{
                if(m_Player->isSliding()){
                    m_Player->setSliding(false);
                    m_Player->Jump();
                }
                if(m_Player->onGround()){
                    m_Player->Jump();
                }
                m_keys.pop();
                break;
            }
            case Qt::Key_Escape:{
                if(m_GameRunning){
                    MainMenu();
                    SaveData();
                    m_GameRunning = false;
                    m_keys.pop();
                }
            }
            default:{
                m_keys.pop();
                break;
            }
            }
        }
        if(m_Player->getLinealSpeed().first < 10 && !m_Player->isSliding()){
            m_Player->setAccelerationX(m_Player->getLinealAcceleration().first + 17);
        }
    });
}
void gamewindow::StartMovement(uint ms){m_KeyTimer->start(ms);}
void gamewindow::StopMovement(){m_KeyTimer->stop();}

void gamewindow::enableClicks(){
    m_MouseTimer = new QTimer();
    connect(m_MouseTimer, &QTimer::timeout, [&](){

        while(!m_Clicks.empty()){
            if(m_Clicks.front().first.first == Qt::LeftButton && m_Clicks.front().first.second){
                //qDebug() << "ScX: " << QString::number(MenuScene->ClickPos.x());
                //qDebug() << "ScY: " << QString::number(MenuScene->ClickPos.y());

                //qDebug() << "PosX: " << QString::number(MenuScene->MousePos.x());
                //qDebug() << "PosY: " << QString::number(MenuScene->MousePos.y());

                float SceneClickPosX = GameScene->ClickPos.x();
                float SceneClickPosY = GameScene->ClickPos.y();

                if(proyectile *Temp = m_Player->Shoot(SceneClickPosX, SceneClickPosY)){
                    GameScene->addItem(Temp);
                }

            }
            m_Clicks.pop();
        }
    });
}
void gamewindow::StartClicks(uint ms){m_MouseTimer->start(ms);}
void gamewindow::StopClicks(){m_MouseTimer->stop();}

void gamewindow::CampaignButton(){

    m_Buttons[0]->hide();
    m_Buttons[1]->hide();
    m_Buttons[2]->hide();

    GameScene = new CustomScene();
    GameScene->setSceneRect(0,0,1000000,5000);
    GameScene->setBackgroundBrush(QBrush(QImage(":/gfx/Images/Fondo.jpg").scaled(1920, 1000)));

    enableCollitions();
    StartCollitions(16);
    enableMovement();
    StartMovement(32);
    enableClicks();
    StartClicks(16);

    AddBlocks();
    AddPlayer();
    AddEntities();

    ui->MainView->setScene(GameScene);
    ui->MainView->scale(0.1, 0.1);
    m_GameRunning = true;
}

void gamewindow::SurvivalButton(){
    qDebug() << "No disponible";
}

void gamewindow::ExitButton(){
    // Save Data
    close();
}
