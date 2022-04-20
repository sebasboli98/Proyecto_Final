#ifndef EXPLOTION_H
#define EXPLOTION_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>

#include <map>

#include "utilities.h"

class explotion: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explotion(std::string Texture_, std::string Sound_, QGraphicsItem *parent = nullptr);
    explotion(float px, float py, explotion *Cast);

    void Explode();

    void setEnergy(float Energy_);
    void setDuration(short ms);

    void setSize(float sx, float sy);
    void setSizeMin(float sx, float sy);
    void setSizeMax(float sx, float sy);
    void setGrowRate(float gx, float gy);

    void setSize(gvr::vec2d Size);
    void setSizeMin(gvr::vec2d Size);
    void setSizeMax(gvr::vec2d Size);
    void setGrowRate(gvr::vec2d GrowRate);

    void setTexture(std::string NewTexture_);
    void setSound(std::string NewSound_);

    void setObjectAffected(QGraphicsItem *Object_);

    float getEnergy();
    short getDuration();

    gvr::vec2d getSize();
    gvr::vec2d getSizeMin();
    gvr::vec2d getSizeMax();
    gvr::vec2d getSizeDifference();
    gvr::vec2d getGrowRate();

    std::string getTexture();
    std::string getSound();

    bool wasAffect(QGraphicsItem *Object_);

private slots:
    void UpdateExplotion();

private:
    float m_Energy;
    short m_Duration;

    gvr::vec2d m_Size;
    gvr::vec2d m_SizeMin;
    gvr::vec2d m_SizeMax;
    gvr::vec2d m_GrowRate;

    std::string m_Texture;
    std::string m_Sound;

    std::map<QGraphicsItem *, bool> m_Affected;

    QTimer *m_Update;

};

#endif // EXPLOTION_H
