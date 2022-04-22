#include "enemy.h"

enemy::enemy(float px, float py, QGraphicsItem *parent)
{
    m_OnGround = false;
    m_ShootCD = false;
    m_UpdateTextures = false;

    m_RemainingCD = 120; //  2 * 60 times per second
    m_TexturesUsing = 0;

    m_Mass = 90; // Kg
    m_DragQ = 0.8f;
    m_FrictionQS = 0.95f;
    m_FrictionQD = 0.85f;
    m_TransversalAreaX = 0.9f; // m^2
    m_TransversalAreaY = 0.175f; // m^2
    m_Hitpoints = 1000;

    m_Gravity = 9.81f; // m/s^2
    m_MediumD = 1.21f; // Kg/m^2 air

    setPos(px, py);
    m_Sl = {0, 0};
    m_Al = {0, 0};

    //setTransformOriginPoint(x() + pixmap().width() * 0.5, y() - pixmap().height() * 0.5);
    m_Textures = {}; // {{},{},{},{},{}}
    m_Sounds = {"","","","",""};

    setObjective();
    setAmmo();

    m_UpdateTimer = new QTimer();
    connect(m_UpdateTimer, SIGNAL(timeout()), this, SLOT(Update()));
    UpdateStart(16);

}

void enemy::Move(float Dt){
    {/// X

        m_FrictionQD *= onGround();
        m_FrictionQS *= onGround();

        short modifier = ((m_Sl.first <= 0) * 2) - 1;

        float ma = m_Mass * m_Al.first * onGround();
        float fd = 0.5 * m_DragQ * m_MediumD * m_TransversalAreaX * mo::exp(m_Sl.first, 3) * modifier;
        float frS = m_Mass * m_Gravity * m_FrictionQS * modifier;
        float frD = m_Mass * m_Gravity * m_FrictionQD * modifier;

        float ar = ((mo::abs(ma) > mo::abs(frS))) * ((ma - (fd + frD)) / m_Mass);
        ar = (!ar && m_Sl.first)? ((fd + frD) / m_Mass) : ar;

        if(mo::abs(m_Sl.first) < 0.05f && mo::abs(ar) < 0.01){
            m_Sl.first = 0;
            ar = 0;
        }

        m_Al.first = ar * Dt;
        m_Sl.first += m_Al.first;
        setX(x() + m_Sl.first);

        m_FrictionQS = 0.95f;
        m_FrictionQD = 0.85f;

    }
    { /// Y
        short modifier = ((m_Al.second <= 0) * 2) - 1;

        float ma = m_Mass * m_Al.second;
        float w = m_Mass * m_Gravity;
        float n = m_Mass * m_Gravity * onGround();
        float fd = 0.5 * m_DragQ * m_MediumD * m_TransversalAreaY * mo::exp(m_Sl.second, 2) * modifier;


        float ar = (ma - fd + w - n) / m_Mass;
        m_Al.second = ar * Dt;
        m_Sl.second += m_Al.second;

        if(onGround() && m_Sl.second < 0){
            setY(y() + m_Sl.second);
        }
        else if(!onGround()){
            setY(y() + m_Sl.second);
        }
    }
    setOnGround(false);
}

void enemy::PorsuitObjective(){
    if(m_Objective){
        float distanceX = m_Objective->x() - this->x();
        float distanceY = m_Objective->y() - this->y();
        short modifier = ((distanceX >= 0) * 2) - 1;

        float invMag = mo::invSqrt(mo::exp(distanceX, 2) + mo::exp(distanceY, 2));
        float distanceMag = mo::oneOver(invMag);
        float MagX = mo::abs(distanceX * invMag);
        float MagY = mo::abs(distanceY * invMag);


        if(mo::abs(distanceMag) > 800 && mo::abs(distanceMag) < 1500){
            m_Sl.first += 0.2f * modifier * MagX * onGround();
        }
        else if(mo::abs(distanceMag) < 400 * MagY){
            m_Sl.first -= 0.2f * modifier * MagX * onGround();
        }

        if(mo::abs(distanceMag) < 1200 && scene()){
            proyectile *p = Shoot();
            p? scene()->addItem(p) : void();
        }
    }
}

proyectile *enemy::Shoot(){
    if(!m_Objective || isShootCooldownActive())
        return nullptr;

    float modifier = (m_Objective->x() - x() <= 0)? -1 : 1;
    //float modifierY = (m_Objective->y() - y() < 0)? -1 : 1;

    float ThrowPosX = this->x() + 77 * modifier;
    float ThrowPosY = this->y() + 90;

    float ObjectivePosX = m_Objective->x() + (10 * modifier * -1);
    float ObjectivePosY = m_Objective->y() + 90;

    float ax = ObjectivePosX - ThrowPosX;
    float ay = ObjectivePosY - ThrowPosY;
    float invMag = mo::invSqrt(mo::exp(ax, 2) + mo::exp(ay, 2));

    ax = invMag * ax * mo::abs(ax);
    ay = invMag * ay * mo::abs(ay);

    setShootCooldownActive(true);
    auto Temp = new proyectile(ThrowPosX + 10 * modifier, ThrowPosY - 10, m_Ammo);
    Temp->setLinealAcceleration(ax, ay);
    Temp->setLinealSpeed(getLinealSpeed().first + ax*0.1f, getLinealSpeed().second + ay*0.1f);

    setShootCooldownActive(true);
    return Temp;
}

void enemy::Collition(float OtherMass_, float RestitutionQ_, gvr::vec2d OtherVl_){
    //gvr::vec2d P1 [[maybe_unused]] = {m_Mass * m_Sl.first, m_Mass * m_Sl.second};
    //gvr::vec2d P2 [[maybe_unused]] = {OtherMass_ * OtherVl_.first, OtherMass_ * OtherVl_.second};

    //gvr::vec2d Pt [[maybe_unused]] = {P1.first + P2.first, P1.second + P2.second};
    float TRQ = RestitutionQ_ * 0.5f;

    //gvr::vec2d Vr [[maybe_unused]] = {TRQ * (m_Sl.first - OtherVl_.first), TRQ * (m_Sl.second - OtherVl_.second)};

    gvr::vec2d U1 = {(((m_Mass - (TRQ * OtherMass_)) * m_Sl.first) - ((TRQ - 1) * OtherMass_* OtherVl_.first)) * mo::oneOver(m_Mass + OtherMass_)
                            , (((m_Mass - (TRQ * OtherMass_)) * m_Sl.second) - ((TRQ - 1) * OtherMass_* OtherVl_.second)) * mo::oneOver(m_Mass + OtherMass_)};

    m_Sl = U1;
    float U1Mag = mo::Sqrt(mo::exp(U1.first, 2) + mo::exp(U1.second, 2));
    Damage(0.5f * OtherMass_ * mo::exp(U1Mag, 2));
    return;
}

void enemy::Collition(float ExplotionForce_, gvr::vec2d Pos_){
    float dx = x() - Pos_.first;
    float dy = y() - Pos_.second;

    float invMag = mo::invSqrt(mo::exp(dx, 2) + mo::exp(dy, 2));
    float effect = ExplotionForce_ * invMag;

    m_Sl.first += (ExplotionForce_ / mo::exp(dx, 2)) * (dx > 0? 1 : -1);
    m_Sl.second += ExplotionForce_ / mo::exp(dy, 2) * (dy > 0? 1 : -1);
    Damage(effect);
}

bool enemy::onGround(){return m_OnGround;}
bool enemy::isShootCooldownActive(){return m_ShootCD;}

float enemy::getMass(){return m_Mass;}
float enemy::getDragQ(){return m_DragQ;}
float enemy::getFrictionQS(){return m_FrictionQS;}
float enemy::getFrictionQD(){return m_FrictionQD;}
float enemy::getTransversalAreaX(){return m_TransversalAreaX;}
float enemy::getTransversalAreaY(){return m_TransversalAreaY;}
float enemy::getHitpoints(){return m_Hitpoints;}

gvr::vec2d enemy::getLinealSpeed(){return m_Sl;}
gvr::vec2d enemy::getLinealAcceleration(){return m_Al;}

QGraphicsItem *enemy::getObjective(){return m_Objective;}
proyectile *enemy::getAmmo(){return m_Ammo;}

void enemy::setOnGround(bool State_){
    m_OnGround = State_;
}
void enemy::setShootCooldownActive(bool State_){
    m_RemainingCD = 120 * State_;
    m_ShootCD = State_;
}

void enemy::setUsingTextures(short TextureNum){m_TexturesUsing = TextureNum;}

void enemy::setMass(float NewMass_){m_Mass = NewMass_;}
void enemy::setDragQ(float NewDrag_){m_DragQ = NewDrag_;}
void enemy::setFrictionQS(float NewSQF_){m_FrictionQS = NewSQF_;}
void enemy::setFrictionQD(float NewDQF_){m_FrictionQD = NewDQF_;}
void enemy::setTransversalAreaX(float NewTransversalArea_){m_TransversalAreaX = NewTransversalArea_;}
void enemy::setTransversalAreaY(float NewTransversalArea_){m_TransversalAreaY = NewTransversalArea_;}
void enemy::setHP(float NewHitpoints_){m_Hitpoints = NewHitpoints_;}

void enemy::setMediumD(float NewMediumD_){m_MediumD = NewMediumD_;}
void enemy::setGravity(float NewGravity_){m_Gravity = NewGravity_;}

void enemy::setTextures(std::array<std::vector<std::string>, 5> TexturesDirs_){m_Textures = TexturesDirs_; m_UpdateTextures = true;}
void enemy::setSounds(std::array<std::string, 5> SoundsDirs_){m_Sounds = SoundsDirs_;}

void enemy::setLinealSpeed(gvr::vec2d NewSl_){m_Sl = NewSl_;}
void enemy::setLinealSpeed(float Sx, float Sy){m_Sl = {Sx, Sy};}
void enemy::setSpeedX(float Sx){m_Sl.first = Sx;}
void enemy::setSpeedY(float Sy){m_Sl.second = Sy;}

void enemy::setLinealAcceleration(gvr::vec2d NewAl_){m_Al = NewAl_;}
void enemy::setLinealAcceleration(float Ax, float Ay){m_Al = {Ax, Ay};}
void enemy::setAccelerationX(float Ax){m_Al.first = Ax;}
void enemy::setAccelerationY(float Ay){m_Al.second = Ay;}

void enemy::setObjective(QGraphicsItem *Obj_){m_Objective = Obj_;}
void enemy::setAmmo(proyectile *Ammo_){
    if(Ammo_){
        m_Ammo = Ammo_;
        return;
    }

    m_Ammo = new proyectile(":/gfx/Images/WoodBox.png", "Elba Lazo");
    m_Ammo->setMass(5);
    m_Ammo->setDragQ(0.02f);
    m_Ammo->setTransversalArea(0.1f);
    m_Ammo->setGravity(m_Gravity);
    m_Ammo->setMediumD(m_MediumD);
    m_Ammo->setScale(25, 15);
    m_Ammo->setExplotionCast(nullptr);
    return;
}

void enemy::UpdateStart(float ms){m_UpdateTimer->start(ms);}
void enemy::UpdateStop(){m_UpdateTimer->stop();}

void enemy::SelectTextures(short TextureNum){
    if(m_TexturesUsing != TextureNum){
        m_TexturesUsing = TextureNum;
        m_UpdateTextures = true;
    }
    // Transition textures code
}
void enemy::ReproduceSound(short SoundNumber[[maybe_unused]]){
    // Play sound code
}

void enemy::UpdateTextures(){
    const short limit = m_Textures[m_TexturesUsing].size();
    const std::vector<std::pair<uint, uint>> rs ={{77, 180}, {180, 77}};
    static short pos = 0;

    setPixmap(QPixmap(m_Textures[m_TexturesUsing][0].c_str()).scaled(rs[m_TexturesUsing].first, rs[m_TexturesUsing].second));
    switch (m_TexturesUsing) {
    case 0:
        setY(y() - (rs[m_TexturesUsing].second/2) - 20);
        break;
    case 1:
        setY(y() + (rs[m_TexturesUsing].second/2) + 20);
        break;
    default:
        break;
    }

    m_UpdateTextures = false;
    //setPixmap(QPixmap(m_Textures[m_TexturesUsing][pos].c_str()));
    pos++;
    (pos == limit) && (pos = limit); // Argument Evaluation Order

}
void enemy::Damage(double Force){
    m_Hitpoints -= Force;
    // if(!m_Hitpoints) Die();
}

void enemy::Update(){
    //setTransformOriginPoint(x() + pixmap().width() * 0.5, y() - pixmap().height() * 0.5);
    PorsuitObjective();
    Move(0.016f);
    if(isShootCooldownActive() && !(--m_RemainingCD)){ // Argument Evaluation Order
        setShootCooldownActive(false);
        m_RemainingCD = 120;
    }
    //if(m_UpdateTextures)
    //    UpdateTextures();
}
