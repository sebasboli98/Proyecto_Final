#ifndef PROYECTILE_H
#define PROYECTILE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include "explotion.h"
#include "utilities.h"

class proyectile: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    proyectile(std::string Texture_, std::string Sound_, QGraphicsItem *parent = nullptr);
    proyectile(float px, float py, proyectile *Cast);

    void Move(float Dt);
    QGraphicsItem * Collition();

    float getMass();
    float getDragQ();
    float getTransversalArea();
    float getMediumD();
    float getGravity();

    gvr::vec2d getScale();

    explotion *getExplotionCast();

    std::string getTexture();
    std::string getSound();

    gvr::vec2d getLinealSpeed();
    gvr::vec2d getLinealAcceleration();

    void setMass(float NewMass_);
    void setDragQ(float NewDrag_);
    void setTransversalArea(float NewTransversalArea_);
    void setMediumD(float NewMediumD_);
    void setGravity(float NewGravity_);

    void setScale(gvr::vec2d NewScale_);
    void setScale(float sx, float sy);

    void setExplotionCast(explotion *Cast_);

    void setTexture(std::string TextureDir_);
    void setSound(std::string SoundDir_);

    void setLinealSpeed(gvr::vec2d NewSl_);
    void setLinealSpeed(float Sx, float Sy);
    void setSpeedX(float Sx);
    void setSpeedY(float Sy);

    void setLinealAcceleration(gvr::vec2d NewAl_);
    void setLinealAcceleration(float Ax, float Ay);
    void setAccelerationX(float Ax);
    void setAccelerationY(float Ay);

    void UpdateStart(uint ms);
    void UpdateStop();

private slots:
    void Update();

private:
    float m_Mass;
    float m_DragQ;
    float m_TransversalArea;

    float m_Gravity;
    float m_MediumD;

    gvr::vec2d m_Al;
    gvr::vec2d m_Sl;

    gvr::vec2d m_Scale;
    std::string m_Texture;
    std::string m_Sound;

    explotion *m_ECast;
    QTimer *m_UpdateTimer;

};

#endif // PROYECTILE_H
