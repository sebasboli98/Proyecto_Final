#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include <array>
#include <string>
//#include <tuple>
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

    float getMass();
    float getFrictionQS();
    float getFrictionQD();

    void setMass(float NewMass_);
    void setFrictionQS(float NewSQF_);
    void setFrictionQD(float NewDQF_);

    void setTextures(std::array<std::string, 3> TexturesDirs_);
    void setSounds(std::array<std::string, 3> SoundsDirs_);

private:
    void setHP(float);
    void setThoughtness(float);

    void ChangeTexture(int);
    void ReproduceSound(int);

    void Damage(double Force);

private slots:
    virtual void Update();

private:
    bool m_Solid;
    bool m_Breakable;
    bool m_Movable;

    float m_Mass;
    float m_DragQ;
    float m_FrictionQS;
    float m_FrictionQD;
    float m_RestitutionQ;
    float m_TransversarlArea;
    float m_Hitpoints;
    float m_Thoughtness;

    float m_Gravity;
    float m_MediumD;

    gvr::vec2d m_Vl;
    gvr::vec2d m_Al;
    float m_Vw;
    float m_Aw;

    std::array<std::string, 3> m_Textures;
    std::array<std::string, 3> m_Sounds;

    QTimer *m_UpdateTimer;

};

#endif // BLOCK_H
