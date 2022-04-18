#include "player.h"
#include <iostream>
#include <QDebug>

player::player(float px, float py, QGraphicsItem *parent[[maybe_unused]]){//Metodo de player

    //Inicializar banderas
    m_OnGround = false;
    m_IsSliding = false;
    m_ShootCD = false;
    m_UpdateTextures = false;

    m_RemainingCD = 120; //Guardar el valor del disparo para que se acabe
    m_TexturesUsing = 0;//Texturas en uso

//asignacion de valores a variables
    m_Mass = 90; // Kg
    m_DragQ = 0.8f;
    m_FrictionQS = 0.95f;
    m_FrictionQD = 0.85f;
    m_TransversalAreaX = 0.9f; // m^2
    m_TransversalAreaY = 0.175f; // m^2
    m_Hitpoints = 1000; // Vida

    m_Gravity = 9.81f; // m/s^2
    m_MediumD = 1.21f; // Kg/m^2 aire

    setPos(px, py);
    m_Sl = {0, 0};
    m_Al = {0, 0};

    //setTransformOriginPoint(x() + pixmap().width() * 0.5, y() - pixmap().height() * 0.5);
    m_Textures = {}; // {{},{},{},{},{}}
    m_Sounds = {"","","","",""};

    m_UpdateTimer = new QTimer(); //Crear el timer
    connect(m_UpdateTimer, SIGNAL(timeout()), this, SLOT(Update()));// conecta funcion con UPDATE(actualizar)
    UpdateStart(16);

}

void player::Move(float Dt){ //metodo para mover el personaje
    { /// mover en Y
        short modifier = ((m_Al.second <= 0) * 2) - 1; //fuerza contraria

        float ma = m_Mass * m_Al.second;//Fuerza
        float w = m_Mass * m_Gravity;//Peso
        float n = m_Mass * m_Gravity * onGround();//normal
        float fd = 0.5 * m_DragQ * m_MediumD * m_TransversalAreaY * mo::exp(m_Sl.second, 2) * modifier;//Fuerza de arrastre


        float ar = (ma - fd + w - n) / m_Mass;//sumatoria de fuerzas /se obtiene la aceleracion
        m_Al.second = ar * Dt; //Modificacion de aceleracion por tiempo
        m_Sl.second += m_Al.second; //Agrego la aceleracion a la velocidad

        if(onGround() && m_Sl.second < 0){ //Evita que el jugador traspase el suelo
            setY(y() + m_Sl.second);
        }
        else if(!onGround()){ // cuando esta en el aire se pueda mover en y
            setY(y() + m_Sl.second);
        }
    }
    {
        /// X Movement



        m_FrictionQD *= onGround(); //verifico si esta en el suelo
        m_FrictionQS *= onGround();

        short modifier = ((m_Sl.first <= 0) * 2) - 1; // fuerza contraria

        float ma = m_Mass * m_Al.first * onGround();//Fuerza
        float fd = 0.5 * m_DragQ * m_MediumD * m_TransversalAreaX * mo::exp(m_Sl.first, 3) * modifier;//Fuerza de arrastre
        float frS = m_Mass * m_Gravity * m_FrictionQS * modifier;//Friccion
        float frD = m_Mass * m_Gravity * m_FrictionQD * modifier;//Friccion
        float ar = ((mo::abs(ma) > mo::abs(frS))) * ((ma - (fd + frD)) / m_Mass); //Calcula la aceleracion resultante
        ar = (!ar && m_Sl.first)? ((fd + frD) / m_Mass) : ar;//Correccion(aceleracion)

        if(mo::abs(m_Sl.first) < 0.05f && ((isSliding() && mo::abs(ar) < 3) || (!isSliding() && mo::abs(ar) < 8.34f))){//Para detener el personaje cuando su movimiento es pequeño
            m_Sl.first = 0;
            ar = 0;
        }

        if(onGround() && m_Sl.first == 0)//Verfica si esta en el suelo y deslizando
            setSliding(false);//Detener

        qDebug() << "Sx: " << QString::number(mo::abs(m_Sl.first));//Probando
       qDebug() << "ar: " << QString::number(ar);

        m_Al.first = ar * Dt; //Acelaracion
        m_Sl.first += m_Al.first;//Velocidad
        setX(x() + m_Sl.first);//Posicion
    }

    if(!scene()->views().isEmpty())//Efecto pantalla siga al jugador
        scene()->views().first()->centerOn(this);

    setOnGround(false);//Resetear las varibles
    m_FrictionQS = (isSliding() * 0.65f) + (!isSliding() * 0.95f);
    m_FrictionQD = (isSliding() * 0.3f) + (!isSliding() * 0.85f);

}
void player::Jump(){//Metodo de salto
    //setUsingTextures(3);
    setAccelerationY(-350);//Salto
}
void player::Slide(){setSliding(true);}//Deslizarse
void player::Shoot(float x_, float y_){//Disparar

    if(isShootCooldownActive())
        return;

    float ax = x_ - this->x();
    float ay = y_ - this->y();
    float invMag = mo::invSqrt(mo::exp(ax, 2) + mo::exp(ay, 2));

    ax *= invMag * 500;
    ay *= invMag * 500;

    m_Granade = new proyectile(ax,ay,":/gfx/Images/granade.png");
    setShootCooldownActive(true); // Intentional Bug

}

void player::Collition(float OtherMass_, float RestitutionQ_, gvr::vec2d OtherVl_){//Colision en movimiento
    //gvr::vec2d P1 [[maybe_unused]] = {m_Mass * m_Sl.first, m_Mass * m_Sl.second};//momento obejto 1
    //gvr::vec2d P2 [[maybe_unused]] = {OtherMass_ * OtherVl_.first, OtherMass_ * OtherVl_.second};// momento objeto 2

    //gvr::vec2d Pt [[maybe_unused]] = {P1.first + P2.first, P1.second + P2.second};//momento total
    float TRQ = RestitutionQ_ * 0.5f;

    //gvr::vec2d Vr [[maybe_unused]] = {TRQ * (m_Sl.first - OtherVl_.first), TRQ * (m_Sl.second - OtherVl_.second)};

    //Momento final de este objeto
    gvr::vec2d U1 = {(((m_Mass - (TRQ * OtherMass_)) * m_Sl.first) - ((TRQ - 1) * OtherMass_* OtherVl_.first)) * mo::oneOver(m_Mass + OtherMass_)
                            , (((m_Mass - (TRQ * OtherMass_)) * m_Sl.second) - ((TRQ - 1) * OtherMass_* OtherVl_.second)) * mo::oneOver(m_Mass + OtherMass_)};

    m_Sl = U1;//Velocidad 1 despues de la colision
    return;
}
void player::Collition(float ExplotionForce_, gvr::vec2d Pos_){//Colision para explosiones

    float dx = x() - Pos_.first;//Distancia hasta la explosion
    float dy = y() - Pos_.second;//En Y

    float invMag = mo::invSqrt(mo::exp(dx, 2) + mo::exp(dy, 2));//Inversa de la magnitud del vector distancia
    float effect = ExplotionForce_ * invMag;//Efecto(Explosion)

    m_Al.first += ExplotionForce_ / (m_Mass * mo::exp(Pos_.first, 2));//Acelaracion resultante
    m_Al.second += ExplotionForce_ / (m_Mass * mo::exp(Pos_.second, 2));//en Y
    Damage(effect);
}
//Getters y Setters
bool player::onGround(){return m_OnGround;}
bool player::isSliding(){return m_IsSliding;}
bool player::isShootCooldownActive(){return m_ShootCD;}

float player::getMass(){return m_Mass;}
float player::getDragQ(){return m_DragQ;}
float player::getFrictionQS(){return m_FrictionQS;}
float player::getFrictionQD(){return m_FrictionQD;}
float player::getTransversalAreaX(){return m_TransversalAreaX;}
float player::getTransversalAreaY(){return m_TransversalAreaY;}

gvr::vec2d player::getLinealSpeed(){return m_Sl;}
gvr::vec2d player::getLinealAcceleration(){return m_Al;}

void player::setOnGround(bool State_){
    m_OnGround = State_;
}
void player::setSliding(bool State_){//Delizarse //State Booleano
    if(m_IsSliding != State_){//Confirmar que el estado es diferente
        SelectTextures(State_);//Cambio de textura
    }

    m_FrictionQS = (State_ * 0.65f) + (!State_ * 0.95f);//Friccion estatica
    m_FrictionQD = (State_ * 0.3f) + (!State_ * 0.85f);//Friccion dinamica
    m_IsSliding = State_;//Cambio el estado
}
void player::setShootCooldownActive(bool State_){//Metodo para verficiar el estado de disparo
    m_RemainingCD = 120 * State_;//Para saber si puede o no disparar
    m_ShootCD = State_;//Cambia el estado
}

//Setters y Getters
void player::setUsingTextures(short TextureNum){m_TexturesUsing = TextureNum;}

void player::setMass(float NewMass_){m_Mass = NewMass_;}
void player::setDragQ(float NewDrag_){m_DragQ = NewDrag_;}
void player::setFrictionQS(float NewSQF_){m_FrictionQS = NewSQF_;}
void player::setFrictionQD(float NewDQF_){m_FrictionQD = NewDQF_;}
void player::setTransversalAreaX(float NewTransversalArea_){m_TransversalAreaX = NewTransversalArea_;}
void player::setTransversalAreaY(float NewTransversalArea_){m_TransversalAreaY = NewTransversalArea_;}
void player::setHP(float NewHitpoints_){m_Hitpoints = NewHitpoints_;}

void player::setMediumD(float NewMediumD_){m_MediumD = NewMediumD_;}
void player::setGravity(float NewGravity_){m_Gravity = NewGravity_;}

void player::setTextures(std::array<std::vector<std::string>, 5> TexturesDirs_){m_Textures = TexturesDirs_; m_UpdateTextures = true;}
void player::setSounds(std::array<std::string, 5> SoundsDirs_){m_Sounds = SoundsDirs_;}

void player::setLinealSpeed(gvr::vec2d NewSl_){m_Sl = NewSl_;}
void player::setLinealSpeed(float Sx, float Sy){m_Sl = {Sx, Sy};}
void player::setSpeedX(float Sx){m_Sl.first = Sx;}
void player::setSpeedY(float Sy){m_Sl.second = Sy;}

void player::setLinealAcceleration(gvr::vec2d NewAl_){m_Al = NewAl_;}
void player::setLinealAcceleration(float Ax, float Ay){m_Al = {Ax, Ay};}
void player::setAccelerationX(float Ax){m_Al.first = Ax;}
void player::setAccelerationY(float Ay){m_Al.second = Ay;}

void player::UpdateStart(float ms){m_UpdateTimer->start(ms);}
void player::UpdateStop(){m_UpdateTimer->stop();}

void player::SelectTextures(short TextureNum){//Seleccionar texturas
    if(m_TexturesUsing != TextureNum){
        m_TexturesUsing = TextureNum;
        m_UpdateTextures = true;
    }
    // Transition textures code
}
void player::ReproduceSound(short SoundNumber[[maybe_unused]]){//Repoducir sonido
    // Play sound code
}

void player::UpdateTextures(){//Actualizar las texturas
    const short limit = m_Textures[m_TexturesUsing].size();
    const std::vector<std::pair<uint, uint>> rs ={{77, 180}, {180, 77}};
    static short pos = 0;

    setPixmap(QPixmap(m_Textures[m_TexturesUsing][0].c_str()).scaled(rs[m_TexturesUsing].first, rs[m_TexturesUsing].second));//Dibuja
    switch (m_TexturesUsing) {
    case 0:
        setY(y() - (rs[m_TexturesUsing].second/2) - 20);//Controlo la posicion de las texturas
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
void player::Damage(double Force[[gnu::unused]]){//Recibir daño

}

void player::Update(){//Actualizar el estado del objeto
    //setTransformOriginPoint(x() + pixmap().width() * 0.5, y() - pixmap().height() * 0.5);
    Move(0.016f);
    if(isShootCooldownActive() && !(--m_RemainingCD)){ // Argument Evaluation Order
        setShootCooldownActive(false);
        m_RemainingCD = 120;
    }
    if(m_UpdateTextures)
        UpdateTextures();
}

