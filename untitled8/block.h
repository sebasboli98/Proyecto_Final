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
    block(bool Solid_, bool Breakable_, bool Movable_, QGraphicsItem *parent = nullptr);

    void Move(float Dt);
    void Rotate(float Dt);

    void Collition(float OtherMass_, float OtherRestitutionQ_, gvr::vec2d OtherVl_);
    void Collition(float ExplotionForce_, gvr::vec2d Pos_);

    //template<typename ... Floats, typename ... Pairs>
    //void Collition(Floats ... floats, Pairs ... pairs);

    //void Collition(float Mass_, float Vw_, gvr::vec2d Pos_, gvr::vec2d Vxy_);
    //void Collition(float Momentum_, gvr::vec2d Pos_);

    bool isSolid();
    bool isBreakable();
    bool isMovable();
    bool OnGround();

    float getMass();
    float getDragQ();
    float getFrictionQS();
    float getFrictionQD();
    float getRestitutionQ();
    float getTransversalArea();
    float getHitpoints();

    gvr::vec2d getLinealSpeed();
    gvr::vec2d getLinealAcceleration();
    float getAngularSpeed();
    float getAngularAcceleration();

    void setOnGround(bool State_);

    void setMass(float NewMass_);
    void setDragQ(float NewDrag_);
    void setFrictionQS(float NewSQF_);
    void setFrictionQD(float NewDQF_);
    void setRestitutionQ(float NewRestitutionQ_);
    void setTransversalArea(float NewTransversalArea_);
    void setThoughtness(float NewThoughtness_);
    void setHP(float);

    void setMediumD(float NewMediumD_);
    void setGravity(float NewGravity_);

    void setTextures(std::array<std::string, 3> TexturesDirs_);
    void setSounds(std::array<std::string, 3> SoundsDirs_);

    void setLinealSpeed(gvr::vec2d NewSl_);
    void setLinealSpeed(float Sx, float Sy);
    void setSpeedX(float Sx);
    void setSpeedY(float Sy);

    void setLinealAcceleration(gvr::vec2d NewAl_);
    void setLinealAcceleration(float Ax, float Ay);
    void setAccelerationX(float Ax);
    void setAccelerationY(float Ay);

    void setAngularSpeed(float NewSw_);
    void setAngularAcceleration(float NewAw_);

    void UpdateStart(float);
    void UpdateStop();

private:
    void ChangeTexture(int);
    void ReproduceSound(int);

    void Damage(double Energy);
    void Die();

private slots:
    virtual void Update();

private:
    bool m_Solid;
    bool m_Breakable;
    bool m_Movable;
    bool m_OnGround;

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
    float m_Sw; // Deg
    float m_Aw; // Deg

    std::array<std::string, 3> m_Textures;
    std::array<std::string, 3> m_Sounds;

    QTimer *m_UpdateTimer;

};

#endif // BLOCK_H
