#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "proyectile.h"

#include "utilities.h"

class player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    player(float px, float py, QGraphicsItem * parent = nullptr);

    void Move(float Dt);
    void Jump();
    void Slide();
    proyectile* Shoot(float x_, float y_);

    void Collition(float OtherMass_, float RestitutionQ_, gvr::vec2d OtherVl_);
    void Collition(float ExplotionForce_, gvr::vec2d Pos_);

    bool onGround();
    bool isSliding();
    bool isShootCooldownActive();

    float getMass();
    float getDragQ();
    float getFrictionQS();
    float getFrictionQD();
    float getTransversalAreaX();
    float getTransversalAreaY();
    float getHP();

    proyectile *getProyectileCast();

    float getMediumD();
    float getGravity();

    gvr::vec2d getLinealSpeed();
    gvr::vec2d getLinealAcceleration();

    void setOnGround(bool State_);
    void setSliding(bool State_);
    void setShootCooldownActive(bool State_);

    void setUsingTextures(short TextureNum);

    void setMass(float NewMass_);
    void setDragQ(float NewDrag_);
    void setFrictionQS(float NewSQF_);
    void setFrictionQD(float NewDQF_);
    void setTransversalAreaX(float NewTransversalArea_);
    void setTransversalAreaY(float NewTransversalArea_);
    void setHP(float);

    void createProyectileCast(std::string Texture_, std::string Sound_);
    void setProyectileCast(proyectile *PCast_);

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

    void UpdateStart(float ms);
    void UpdateStop();

    void SelectTextures(short TN);
    void ReproduceSound(short SN);

    void UpdateTextures(); //
    void Damage(double Force);

private slots:
    virtual void Update();

private:
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

    gvr::vec2d m_Sl;
    gvr::vec2d m_Al;

    std::array<std::vector<std::string>, 5> m_Textures;
    std::array<std::string, 5> m_Sounds;

    proyectile *m_PCast;
    QTimer *m_UpdateTimer;

};

#endif // PLAYER_H
