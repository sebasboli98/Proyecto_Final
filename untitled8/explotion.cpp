#include "explotion.h"

explotion::explotion(std::string Texture_, std::string Sound_, QGraphicsItem *parent){

    setEnergy(0);
    setDuration(100);

    setSizeMin(60, 60);
    setSizeMax(180, 180);
    setSize(m_SizeMin);
    setGrowRate(getSizeDifference().first * OneThird, getSizeDifference().second * OneThird);

    setTexture(Texture_);
    setSound(Sound_);
    setPos(0, 0);

    m_Affected = {};

}
explotion::explotion(float px, float py, explotion *Cast){
    setPos(px, py);

    setEnergy(Cast->getEnergy());
    setDuration(Cast->getDuration());

    setSize(Cast->getSize());
    setSizeMin(Cast->getSizeMin());
    setSizeMax(Cast->getSizeMax());
    setGrowRate(Cast->getGrowRate());

    setTexture(Cast->getTexture());
    setSound(Cast->getSound());

    m_Affected = {};

}

void explotion::Explode(){
    m_Update = new QTimer();
    connect(m_Update, SIGNAL(timeout()), this, SLOT(UpdateExplotion()));

    m_Size = m_SizeMin;
    m_GrowRate = {getSizeDifference().first * OneThird, getSizeDifference().second * OneThird};
    // Old Formula: getSizeDifference() * mo::oneOver((60*getDuration())/1000)

    m_Update->start(16);
}

void explotion::setEnergy(float Energy_){m_Energy = Energy_;}
void explotion::setDuration(short ms){m_Duration = ms;}

void explotion::setSize(float sx, float sy){m_Size = {sx, sy};}
void explotion::setSizeMin(float sx, float sy){m_SizeMin = {sx, sy};}
void explotion::setSizeMax(float sx, float sy){m_SizeMax = {sx, sy};}
void explotion::setGrowRate(float gx, float gy){m_GrowRate = {gx, gy};}

void explotion::setSize(gvr::vec2d Size){m_Size = Size;}
void explotion::setSizeMin(gvr::vec2d Size){m_SizeMin = Size;}
void explotion::setSizeMax(gvr::vec2d Size){m_SizeMax = Size;}
void explotion::setGrowRate(gvr::vec2d GrowRate){m_GrowRate = GrowRate;}

void explotion::setTexture(std::string NewTexture_){m_Texture = NewTexture_; setPixmap(QPixmap(m_Texture.c_str()).scaled(m_SizeMin.first, m_SizeMin.second));}
void explotion::setSound(std::string NewSound_){m_Sound = NewSound_;}

void explotion::setObjectAffected(QGraphicsItem *Object_){m_Affected.insert({Object_, true});}

float explotion::getEnergy(){return m_Energy;}
short explotion::getDuration(){return m_Duration;}

gvr::vec2d explotion::getSize(){return m_Size;}
gvr::vec2d explotion::getSizeMin(){return m_SizeMin;}
gvr::vec2d explotion::getSizeMax(){return m_SizeMax;}
gvr::vec2d explotion::getSizeDifference(){return {m_SizeMax.first - m_SizeMin.first, m_SizeMax.second - m_SizeMin.second};}
gvr::vec2d explotion::getGrowRate(){return m_GrowRate;}

std::string explotion::getTexture(){return m_Texture;}
std::string explotion::getSound(){return m_Sound;}

bool explotion::wasAffect(QGraphicsItem *Object_){
    if(m_Affected.find(Object_) != m_Affected.end() && m_Affected.find(Object_)->second){
          return true;
    }
    return false;
}

void explotion::UpdateExplotion(){
    if(m_Size <= m_SizeMax){
        setPixmap(QPixmap(m_Texture.c_str()).scaled(m_Size.first, m_Size.second));
        m_Size.first += m_GrowRate.first;
        m_Size.second += m_GrowRate.second;
        return;
    }
    delete this;
}
