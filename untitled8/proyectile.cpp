#include "proyectile.h"

proyectile::proyectile(std::string Texture_, std::string Sound_, QGraphicsItem *parent){
    m_Mass = 0.002f; // Kg
    m_DragQ = 0.05f;
    m_TransversalArea = 0.002; // m^2

    m_Gravity = 9.81f; // m/s^2
    m_MediumD = 1.21f; // Kg/m^2

    setPos(0, 0);
    m_Sl = {0, 0};
    m_Al = {0, 0};

    m_Scale = {5, 2};
    m_Texture = Texture_;
    m_Sound = Sound_;

    setExplotionCast(nullptr);
    //psetTransformOriginPoint(x() + pixmap().width() * 0.5, y() - pixmap().height() * 0.5);
}
proyectile::proyectile(float px, float py, proyectile *Cast){
    m_Mass = Cast->getMass(); // Kg
    m_DragQ = Cast->getDragQ();
    m_TransversalArea = Cast->getTransversalArea(); // m^2

    m_Gravity = Cast->getGravity(); // m/s^2
    m_MediumD = Cast->getMediumD(); // Kg/m^2

    setPos(px, py);
    m_Sl = Cast->getLinealSpeed();
    m_Al = Cast->getLinealAcceleration();

    m_Texture = Cast->getTexture();
    m_Sound = Cast->getSound();

    m_ECast = Cast->getExplotionCast();

    setPixmap(QPixmap(m_Texture.c_str()).scaled(Cast->getScale().first, Cast->getScale().second));
    setTransformOriginPoint(x() + pixmap().width() * 0.5, y() - pixmap().height() * 0.5);

    m_UpdateTimer = new QTimer();
    connect(m_UpdateTimer, SIGNAL(timeout()), this, SLOT(Update()));
    UpdateStart(16);
}

void proyectile::Move(float Dt){
    { /// Y Movement
        short modifier = ((m_Sl.second >= 0) * 2) - 1;

        float ma = m_Mass * m_Al.second;
        float w = m_Mass * m_Gravity;
        float fd = 0.5 * m_DragQ * m_MediumD * m_TransversalArea * mo::exp(m_Sl.second, 2) * modifier;

        float ar = (ma - fd + w) / m_Mass;
        m_Al.second = ar * Dt;
        m_Sl.second += m_Al.second;
        setY(y() + m_Sl.second);

        if(y() > 2500)
            delete this;
    }
    { /// X Movement
        short modifier = ((m_Sl.first >= 0) * 2) - 1; // m_Sl.first > 0? 1 : -1;

        float ma = m_Mass * m_Al.first;
        float fd = 0.1 * m_DragQ * m_MediumD * m_TransversalArea * mo::exp(m_Sl.first, 2) * modifier;

        float ar = (ma - fd) / m_Mass; // mo::abs(ma) < mo::abs(fd+frS)? 0 : ((ma - (fd + frD)) / m_Mass);
        m_Al.first = ar * Dt;
        m_Sl.first += m_Al.first;
        setX(x() + m_Sl.first);
    }
}
QGraphicsItem * proyectile::Collition(){
    if(!getExplotionCast())
        return nullptr;

    auto exp = new explotion(x(), y(), m_ECast);
    float V = mo::Sqrt(mo::exp(m_Sl.first, 2) + mo::exp(m_Sl.second, 2));

    exp->setEnergy(0.5f * m_Mass * mo::exp(V, 2));
    //exp.set

    return exp;
}

float proyectile::getMass(){return m_Mass;}
float proyectile::getDragQ(){return m_DragQ;}
float proyectile::getTransversalArea(){return m_TransversalArea;}
float proyectile::getMediumD(){return m_MediumD;}
float proyectile::getGravity(){return m_Gravity;}

gvr::vec2d proyectile::getScale(){return m_Scale;}

explotion *proyectile::getExplotionCast(){return m_ECast;}

std::string proyectile::getTexture(){return m_Texture;}
std::string proyectile::getSound(){return m_Sound;}

gvr::vec2d proyectile::getLinealSpeed(){return m_Sl;}
gvr::vec2d proyectile::getLinealAcceleration(){return m_Al;}

void proyectile::setMass(float NewMass_){m_Mass = NewMass_;}
void proyectile::setDragQ(float NewDrag_){m_DragQ = NewDrag_;}
void proyectile::setTransversalArea(float NewTransversalArea_){m_TransversalArea = NewTransversalArea_;}
void proyectile::setMediumD(float NewMediumD_){m_MediumD = NewMediumD_;}
void proyectile::setGravity(float NewGravity_){m_Gravity = NewGravity_;}

void proyectile::setScale(gvr::vec2d NewScale_){m_Scale = NewScale_;}
void proyectile::setScale(float sx, float sy){m_Scale = {sx, sy};}

void proyectile::setExplotionCast(explotion *Cast_){m_ECast = Cast_;}

void proyectile::setTexture(std::string TextureDir_){m_Texture = TextureDir_;}
void proyectile::setSound(std::string SoundDir_){m_Sound = SoundDir_;}

void proyectile::setLinealSpeed(gvr::vec2d NewSl_){m_Sl = NewSl_;}
void proyectile::setLinealSpeed(float Sx, float Sy){m_Sl = {Sx, Sy};}
void proyectile::setSpeedX(float Sx){m_Sl.first = Sx;}
void proyectile::setSpeedY(float Sy){m_Sl.second = Sy;}

void proyectile::setLinealAcceleration(gvr::vec2d NewAl_){m_Al = NewAl_;}
void proyectile::setLinealAcceleration(float Ax, float Ay){m_Al = {Ax, Ay};}
void proyectile::setAccelerationX(float Ax){m_Al.first = Ax;}
void proyectile::setAccelerationY(float Ay){m_Al.second = Ay;}

void proyectile::UpdateStart(uint ms){m_UpdateTimer->start(ms);}
void proyectile::UpdateStop(){m_UpdateTimer->stop();}

void proyectile::Update(){
    Move(0.016);
}
