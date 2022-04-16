#include "block.h"

block::block(bool Solid_, bool Breakable_, bool Movable_, [[maybe_unused]] QGraphicsItem *parent)
    : m_Solid(Solid_), m_Breakable(Breakable_), m_Movable(Movable_)
{
    m_Mass = 40; // Kg
    m_DragQ = 0.7f;
    m_FrictionQS = 0.8f;
    m_FrictionQD = 0.62f;
    m_RestitutionQ = 0.6f; // 1 - 0
    m_TransversalArea = 1; // m^2
    m_Hitpoints = 1000;
    m_Thoughtness = 5.8f;

    m_Gravity = 9.81f; // m/s^2
    m_MediumD = 1.21f; // Kg/m^2

    setPos(0, 0);
    m_Sl = {0, 0};
    m_Al = {0, 0};
    m_Sw = 0.0f;
    m_Aw = 0.0f;

    m_Textures = {":/gfx/Images/Wood-SteelBox.png", "", ""};
    m_Sounds = {"", "", ""};

    setPixmap(QPixmap(m_Textures[0].c_str()).scaled(80, 80));
    setTransformOriginPoint(x() + pixmap().width() * 0.5, y() - pixmap().height() * 0.5);

    if(m_Movable){
        m_UpdateTimer = new QTimer();
        connect(m_UpdateTimer, SIGNAL(timeout()), this, SLOT(Update()));
        UpdateStart(16);
    }
}

void block::Move(float Dt){
    { /// Y Movement
        short modifier = ((m_Sl.second >= 0) * 2) - 1;

        float ma = m_Mass * m_Al.second;
        float w = m_Mass * m_Gravity;
        float fd = 0.5 * m_DragQ * m_MediumD * m_TransversalArea * mo::exp(m_Sl.second, 2) * modifier;


        float ar = (ma - fd + w) / m_Mass;
        m_Al.second = ar * Dt;
        m_Sl.second += m_Al.second;
        setY(y() + m_Sl.second);
        //m_Sl.second > 0? setY(y() + (m_OnGround * m_Sl.second * Dt)) : setY(y() + m_Sl.second * Dt);

    }
    { /// X Movement
        if(collidingItems().isEmpty()){
            m_FrictionQD = 0.0f;
            m_FrictionQS = 0.0f;
        }

        short modifier = ((m_Sl.first >= 0) * 2) - 1; // m_Sl.first > 0? 1 : -1;

        float ma = m_Mass * m_Al.first;
        float fd = 0.5 * m_DragQ * m_MediumD * m_TransversalArea * mo::exp(m_Sl.first, 2) * modifier;
        float frS = m_Mass * m_Gravity * m_FrictionQS * modifier;
        float frD = m_Mass * m_Gravity * m_FrictionQD * modifier;

        float ar = (!(mo::abs(ma) < mo::abs(fd+frS))) * ((ma - (fd + frD)) / m_Mass); // mo::abs(ma) < mo::abs(fd+frS)? 0 : ((ma - (fd + frD)) / m_Mass);
        m_Al.first = ar * Dt;
        m_Sl.first += m_Al.first;
        setX(x() + m_Sl.first);
    }
    if(!scene()->views().isEmpty())
        scene()->views().first()->centerOn(this);
}

void block::Rotate([[maybe_unused]]float Dt){

    setTransformOriginPoint(x() + pixmap().width() * 0.5, y() - pixmap().height() * 0.5);
    setRotation(m_Sw * Dt);

}

void block::Collition(float OtherMass_, float OtherRestitutionQ_, gvr::vec2d OtherVl_){

    gvr::vec2d P1 [[maybe_unused]] = {m_Mass * m_Sl.first, m_Mass * m_Sl.second};
    gvr::vec2d P2 [[maybe_unused]] = {OtherMass_ * OtherVl_.first, OtherMass_ * OtherVl_.second};

    gvr::vec2d Pt [[maybe_unused]] = {P1.first + P2.first, P1.second + P2.second};
    float TRQ = (OtherRestitutionQ_ + m_RestitutionQ) * 0.5f;

    gvr::vec2d Vr [[maybe_unused]] = {TRQ * (m_Sl.first - OtherVl_.first), TRQ * (m_Sl.second - OtherVl_.second)};

    gvr::vec2d U1 = {(((m_Mass - (TRQ * OtherMass_)) * m_Sl.first) - ((TRQ - 1) * OtherMass_* OtherVl_.first)) * mo::oneOver(m_Mass + OtherMass_)
                            , (((m_Mass - (TRQ * OtherMass_)) * m_Sl.second) - ((TRQ - 1) * OtherMass_* OtherVl_.second)) * mo::oneOver(m_Mass + OtherMass_)};

    m_Sl = U1;
    return;
}

void block::Collition(float ExplotionForce_, gvr::vec2d Pos_){
    m_Al.first += ExplotionForce_ / (m_Mass * mo::exp(Pos_.first, 2));
    m_Al.second += ExplotionForce_ / (m_Mass * mo::exp(Pos_.second, 2));
}

bool block::isSolid(){return m_Solid;}
bool block::isBreakable(){return m_Breakable;}
bool block::isMovable(){return m_Movable;}
bool block::OnGround(){return m_OnGround;}

float block::getMass(){return m_Mass;}
float block::getDragQ(){return m_DragQ;}
float block::getFrictionQS(){return m_FrictionQS;}
float block::getFrictionQD(){return m_FrictionQD;}
float block::getRestitutionQ(){return m_RestitutionQ;}
float block::getTransversalArea(){return m_TransversalArea;}

gvr::vec2d block::getLinealSpeed(){return m_Sl;}
gvr::vec2d block::getLinealAcceleration(){return m_Al;}
float block::getAngularSpeed(){return m_Sw;}
float block::getAngularAcceleration(){return m_Aw;}

void block::setOnGround(bool State_){m_OnGround = State_;}

void block::setMass(float NewMass_){m_Mass = NewMass_;}
void block::setDragQ(float NewDrag_){m_DragQ = NewDrag_;}
void block::setFrictionQS(float NewSQF_){m_FrictionQS = NewSQF_;}
void block::setFrictionQD(float NewDQF_){m_FrictionQD = NewDQF_;}
void block::setRestitutionQ(float NewRestitutionQ_){m_RestitutionQ = NewRestitutionQ_;}
void block::setTransversalArea(float NewTransversalArea_){m_TransversalArea = NewTransversalArea_;}
void block::setThoughtness(float NewThoughtness_){m_Thoughtness = NewThoughtness_;}
void block::setHP(float NewHitpoints_){m_Hitpoints = NewHitpoints_;}

void block::setMediumD(float NewMediumD_){m_MediumD = NewMediumD_;}
void block::setGravity(float NewGravity_){m_Gravity = NewGravity_;}

void block::setTextures(std::array<std::string, 3> TexturesDirs_){m_Textures = TexturesDirs_;}
void block::setSounds(std::array<std::string, 3> SoundsDirs_){m_Sounds = SoundsDirs_;}

void block::setLinealSpeed(gvr::vec2d NewSl_){m_Sl = NewSl_;}
void block::setLinealSpeed(float Sx, float Sy){m_Sl = {Sx, Sy};}
void block::setSpeedX(float Sx){m_Sl.first = Sx;}
void block::setSpeedY(float Sy){m_Sl.second = Sy;}

void block::setLinealAcceleration(gvr::vec2d NewAl_){m_Al = NewAl_;}
void block::setLinealAcceleration(float Ax, float Ay){m_Al = {Ax, Ay};}
void block::setAccelerationX(float Ax){m_Al.first = Ax;}
void block::setAccelerationY(float Ay){m_Al.second = Ay;}

void block::setAngularSpeed(float NewSw_){m_Sw = NewSw_;}
void block::setAngularAcceleration(float NewAw_){m_Aw = NewAw_;}

void block::UpdateStart(float t){m_UpdateTimer->start(t);}
void block::UpdateStop(){m_UpdateTimer->stop();}



//gvr::vec2d Vxy_, gvr::vec2d Vw_ = {0,0}
//template<typename ... Floats, typename ... Pairs>
//[[deprecated("Use specialization")]]
//void block::Collition(Floats ... floats, Pairs ... pairs){
//    Collition(floats ..., pairs ...);
//    return;
//}
//
//
//void block::Collition(float Mass_, float Vw_, gvr::vec2d Vl_, gvr::vec2d Pos_){
//    float pl = Mass_ * mo::Sqrt(mo::exp(Vl_.first,2) + mo::exp(Vl_.second,2));
//    float pw = Mass_ * Vw_;
//
//    float a = 0;
//    //float vt = (this->pixmap().width() * 0.5f) * Vw_;
//    Collition(pl + pw, Pos_);
//    return;
//}
//
//template<>
//void block::Collition(float Momentum_, gvr::vec2d Pos_){
//
//
//    return;
//}

void block::Update(){

    if(m_Movable){
        Move(0.016f); // 60 updates per second 0.016f
        Rotate(0.016f);
    }
    return;
}




