#include "block.h"

block::block(bool Solid_, bool Breakable_, bool Movable_, [[maybe_unused]] QGraphicsItem *parent)
    : m_Solid(Solid_), m_Breakable(Breakable_), m_Movable(Movable_)
{
    m_Mass = 40; // Kg
    m_DragQ = 0.7;
    m_FrictionQS = 0.8;
    m_FrictionQD = 0.7;
    m_RestitutionQ = 0.6; // 1 - 0
    m_TransversarlArea = 1; // m^2
    m_Hitpoints = 1000;
    m_Thoughtness = 5.8;

    m_Gravity = 9.81f; // m/s^2
    m_MediumD = 1.21f; // Kg/m^2

    m_Vl = {0, 0};
    m_Al = {0, 0};
    m_Vw = 0.0f;
    m_Aw = 0.0f;

    m_Textures = {"", "", ""};
    m_Sounds = {"", "", ""};

    setPixmap(QPixmap(m_Textures[0].c_str()));
    setTransformOriginPoint(x() + pixmap().width() * 0.5, y() - pixmap().height() * 0.5);

    m_UpdateTimer = new QTimer();
    connect(m_UpdateTimer, SIGNAL(timeout()), this, SLOT(Update()));
    m_UpdateTimer->start(16);
}

void block::Move(float Dt){
    float ma = m_Mass * m_Gravity;
    float fd = 0.5 * m_DragQ * m_MediumD * 1 * m_Vl.second * m_Vl.second;

    float ar = (ma - fd) / m_Mass;
    m_Al.second = ar * Dt;
    m_Vl.second += m_Al.second;
}

void block::Rotate([[maybe_unused]]float Dt){
    setTransformOriginPoint(0,0);
    this->rotation();
}

void block::Collition(float OtherMass_, float OtherRestitutionQ_, gvr::vec2d OtherVl_){

    gvr::vec2d P1 [[maybe_unused]] = {m_Mass * m_Vl.first, m_Mass * m_Vl.second};
    gvr::vec2d P2 [[maybe_unused]] = {OtherMass_ * OtherVl_.first, OtherMass_ * OtherVl_.second};

    gvr::vec2d Pt [[maybe_unused]] = {P1.first + P2.first, P1.second + P2.second};
    float TRQ = (OtherRestitutionQ_ + m_RestitutionQ) * 0.5f;

    gvr::vec2d Vr [[maybe_unused]] = {TRQ * (m_Vl.first - OtherVl_.first), TRQ * (m_Vl.second - OtherVl_.second)};

    gvr::vec2d U1 = {(((m_Mass - (TRQ * OtherMass_)) * m_Vl.first) - ((TRQ - 1) * OtherMass_* OtherVl_.first)) * mo::oneOver(m_Mass + OtherMass_)
                            , (((m_Mass - (TRQ * OtherMass_)) * m_Vl.second) - ((TRQ - 1) * OtherMass_* OtherVl_.second)) * mo::oneOver(m_Mass + OtherMass_)};

    m_Vl = U1;
    return;
}

void block::Collition(float ExplotionForce_, gvr::vec2d Pos_){
    m_Al.first += ExplotionForce_ / (m_Mass * mo::exp(Pos_.first, 2));
    m_Al.second += ExplotionForce_ / (m_Mass * mo::exp(Pos_.second, 2));
}


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
        Move(0.016f); // 60 updates per second
       // Rotate(0.016f);
    }

    return;
}





