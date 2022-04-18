#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <array>
#include <string>

#include "utilities.h"

class block: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    block(bool Solid_, bool Breakable_, bool Movable_, QGraphicsItem *parent = nullptr);//Constructor

    void Move(float Dt);  //Movimientos(fisicas)
    void Rotate(float Dt); //Rotar

    void Collition(float OtherMass_, float OtherRestitutionQ_, gvr::vec2d OtherVl_);   // interacciones con otros obejtos
    void Collition(float ExplotionForce_, gvr::vec2d Pos_); //Explosiones


    bool isSolid(); // Bloque solido
    bool isBreakable(); // si se puede o no romper
    bool isMovable(); //si se puede mover
    bool OnGround(); //Si esta sobre el suelo

    float getMass();        //Obtener masa
    float getDragQ();       //Coeficiente de arrastre
    float getFrictionQS();  //Friccion estatica
    float getFrictionQD();   //Friccion dinamica
    float getRestitutionQ();      //Coeficiente de restitucion
    float getTransversalArea();   //Area con que choca con el aire

    gvr::vec2d getLinealSpeed();        //Velocidad normal x y y
    gvr::vec2d getLinealAcceleration();    //acelaracion en x y y
    float getAngularSpeed();               //Velocidad angular
    float getAngularAcceleration();         //Aceleracion angular

    void setOnGround(bool State_);  // si esta en el suelo o no

    void setMass(float NewMass_);   //Masa
    void setDragQ(float NewDrag_);      //Arrastre
    void setFrictionQS(float NewSQF_);      //Friccion estatica
    void setFrictionQD(float NewDQF_);      //Dinamica
    void setRestitutionQ(float NewRestitutionQ_);       //Coeficiente de restitucion
    void setTransversalArea(float NewTransversalArea_);
    void setThoughtness(float NewThoughtness_);     //Dureza
    void setHP(float);      //Vida de la caja

    void setMediumD(float NewMediumD_);     //Densidad del aire
    void setGravity(float NewGravity_);     //Gravedad

    void setTextures(std::array<std::string, 3> TexturesDirs_); //Texturas para la caja
    void setSounds(std::array<std::string, 3> SoundsDirs_); //Sonidos

    void setLinealSpeed(gvr::vec2d NewSl_); //Velocidad x y
    void setLinealSpeed(float Sx, float Sy);
    void setSpeedX(float Sx); //velocidad x
    void setSpeedY(float Sy); //velocidad y

    void setLinealAcceleration(gvr::vec2d NewAl_);  //Aceleracion x y
    void setLinealAcceleration(float Ax, float Ay);
    void setAccelerationX(float Ax);
    void setAccelerationY(float Ay);

    void setAngularSpeed(float NewSw_);     //Velocidad angular
    void setAngularAcceleration(float NewAw_);      //Acelearacion angular

    void UpdateStart(float);    //Temporizador empezar
    void UpdateStop();      //Temporizador terminar

private:
    void ChangeTexture(int);        //Cambiar texturas
    void ReproduceSound(int);       //Reproducir sonido

    void Damage(double Force);      //Recibir daño por ipacto

private slots://Funciones conectables a un temporizador
    virtual void Update();          //actualiza el estado del objeto

private: //Variables de atributos
    bool m_Solid;
    bool m_Breakable;
    bool m_Movable;
    bool m_OnGround;

    //Magnitudes fisicas
    float m_Mass;
    float m_DragQ;
    float m_FrictionQS;
    float m_FrictionQD;
    float m_RestitutionQ;
    float m_TransversalArea;
    float m_Hitpoints;
    float m_Thoughtness;

    float m_Gravity;
    float m_MediumD;

    gvr::vec2d m_Sl;
    gvr::vec2d m_Al;
    float m_Sw; // Grados
    float m_Aw;

    std::array<std::string, 3> m_Textures;
    std::array<std::string, 3> m_Sounds;

    QTimer *m_UpdateTimer;

};

#endif // BLOCK_H
