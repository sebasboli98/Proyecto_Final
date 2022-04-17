#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include <proyectile.h>

#include "utilities.h"

class enemy: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enemy(float px, float py, QGraphicsItem *parent = nullptr);

    void Move(float Dt);
    void PorsuitObjective();
    void Shoot();

    void Collition(float OtherMass_, float RestitutionQ_, gvr::vec2d OtherVl_);
    void Collition(float ExplotionForce_, gvr::vec2d Pos_);

    bool onGround();
    bool isShootCooldownActive();

    float getMass();
    float getDragQ();
    float getFrictionQS();
    float getFrictionQD();
    float getTransversalAreaX();
    float getTransversalAreaY();

    gvr::vec2d getLinealSpeed();
    gvr::vec2d getLinealAcceleration();

    void setOnGround(bool State_);
    void setShootCooldownActive(bool State_);

    void setUsingTextures(short TextureNum);

    void setMass(float NewMass_);
    void setDragQ(float NewDrag_);
    void setFrictionQS(float NewSQF_);
    void setFrictionQD(float NewDQF_);
    void setRestitutionQ(float NewRestitutionQ_);
    void setTransversalAreaX(float NewTransversalArea_);
    void setTransversalAreaY(float NewTransversalArea_);
    void setHP(float);

    void setMediumD(float NewMediumD_);
    void setGravity(float NewGravity_);

    void setTextures(std::array<std::vector<std::string>, 5> TexturesDirs_);
    void setSounds(std::array<std::string, 5> SoundsDirs_);

    void setLinealSpeed(gvr::vec2d NewSl_);
    void setLinealSpeed(float Sx, float Sy);
    void setSpeedX(float Sx);
    void setSpeedY(float Sy);

    void setLinealAcceleration(gvr::vec2d NewAl_);
    void setLinealAcceleration(float Ax, float Ay);
    void setAccelerationX(float Ax);
    void setAccelerationY(float Ay);

    void setObjective(QGraphicsItem *Obj_ = nullptr);
    void setAmmo(proyectile *Ammo_ = nullptr);

    void UpdateStart(float ms);
    void UpdateStop();

    void SelectTextures(short TN);
    void ReproduceSound(short SN);

    void UpdateTextures();
    void Damage(double Force);

private slots:
    virtual void Update();

private:
    bool m_OnGround;
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

    gvr::vec2d m_Sl;
    gvr::vec2d m_Al;

    std::array<std::vector<std::string>, 5> m_Textures;
    std::array<std::string, 5> m_Sounds;

    QGraphicsItem *m_Objective;
    proyectile *m_Ammo;
    std::vector<std::string> m_AmmoProperties;
    QTimer *m_UpdateTimer;

};

#endif // ENEMY_H
