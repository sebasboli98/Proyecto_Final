#include "checkpoint.h"

checkpoint::checkpoint(float px, float py, QGraphicsItem *parent)
{
    setPos(px, py);
    setPixmap(QPixmap(":/gfx/Images/WoodBox.png").scaled(80, 80));
    m_UpdateTimer = new QTimer();
    connect(m_UpdateTimer, SIGNAL(timeout()), this, SLOT(Update()));
    // Start timer
}

void checkpoint::updateTextures()
{
    setPixmap(QPixmap(m_Textures[0].c_str()));
}

gvr::vec2d checkpoint::getRespawn(){return m_RespawnPoint;}
void checkpoint::setRespawn(gvr::vec2d RespawnPos){m_RespawnPoint = RespawnPos;}

void checkpoint::setTextures(std::vector<std::string> NewTextures_){m_Textures = NewTextures_; updateTextures();}

void checkpoint::Update()
{
    updateTextures();
}
