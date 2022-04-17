#include "checkpoint.h"

checkpoint::checkpoint(float px, float py, QGraphicsItem *parent)
{
    setPos(px, py);
    m_UpdateTimer = new QTimer();
    connect(m_UpdateTimer, SIGNAL(timeout()), this, SLOT(Update()));
    // Start timer
}

void checkpoint::updateTextures()
{
    setPixmap(QPixmap(m_Textures[0].c_str()));
}

void checkpoint::setTextures(std::vector<std::string> NewTextures_){m_Textures = NewTextures_; updateTextures();}

void checkpoint::Update()
{
    updateTextures();
}
