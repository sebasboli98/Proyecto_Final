#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <proyectile.h>

#include "utilities.h"

class player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    player(float px, float py, QGraphicsItem * parent = nullptr);

    void Move(float Dt); //movimiento(Fisicas)
    void Jump();    //salto
    void Slide();   //desliza
    void Shoot(float x_, float y_); // Disparar

    void Collition(float OtherMass_, float RestitutionQ_, gvr::vec2d OtherVl_); //Metodo de colision
    void Collition(float ExplotionForce_, gvr::vec2d Pos_);

    bool onGround();    //esta encima de un objeto
    bool isSliding(); //comprueba si esta deslizando
    bool isShootCooldownActive();   //comprueba si esta activado el disparo

    //Getters,recibir los datos
    float getMass();
    float getDragQ();
    float getFrictionQS();
    float getFrictionQD();
    float getTransversalAreaX();
    float getTransversalAreaY();

    gvr::vec2d getLinealSpeed();    //Velocidad x y
    gvr::vec2d getLinealAcceleration(); //Aceleracion x y

    //Setters, para modificar los valores
    void setOnGround(bool State_);
    void setSliding(bool State_);
    void setShootCooldownActive(bool State_);

    void setUsingTextures(short TextureNum);
//para las fisicas
    void setMass(float NewMass_);
    void setDragQ(float NewDrag_);
    void setFrictionQS(float NewSQF_);
    void setFrictionQD(float NewDQF_);
    void setRestitutionQ(float NewRestitutionQ_);
    void setTransversalAreaX(float NewTransversalArea_);
    void setTransversalAreaY(float NewTransversalArea_);
    void setHP(float);//vida del jugador

    void setMediumD(float NewMediumD_);
    void setGravity(float NewGravity_);

    void setTextures(std::array<std::vector<std::string>, 5> TexturesDirs_);//texturas
    void setSounds(std::array<std::string, 5> SoundsDirs_);//Sonidos
//setters de velocidades
    void setLinealSpeed(gvr::vec2d NewSl_);
    void setLinealSpeed(float Sx, float Sy);
    void setSpeedX(float Sx);
    void setSpeedY(float Sy);

    void setLinealAcceleration(gvr::vec2d NewAl_);
    void setLinealAcceleration(float Ax, float Ay);
    void setAccelerationX(float Ax);
    void setAccelerationY(float Ay);

    void UpdateStart(float ms); //Actualizacion de inicio
    void UpdateStop();          //detiene la actualizaciones

    void SelectTextures(short TN);//Seleccion de texturas
    void ReproduceSound(short SN);

    void UpdateTextures();      //Actulizacion de texturas
    void Damage(double Force);  //

private slots:
    virtual void Update();      //Ciclo para atualizar

private:
    //Varibales
    bool m_OnGround;
    bool m_IsSliding;
    bool m_ShootCD;
    bool m_UpdateTextures;

    short m_RemainingCD;
    short m_TexturesUsing;

    float m_Mass;
    float m_DragQ;
    float m_FrictionQS;
    float m_FrictionQD;
    float m_TransversalAreaX;
    float m_TransversalAreaY;
    float m_Hitpoints;

    float m_Gravity;
    float m_MediumD;

    gvr::vec2d m_Sl;//Velocidad lienal
    gvr::vec2d m_Al;//Acelearacion lineal

    std::array<std::vector<std::string>, 5> m_Textures;
    std::array<std::string, 5> m_Sounds;

    proyectile *m_Granade;
    QTimer *m_UpdateTimer;

};

#endif // PLAYER_H
