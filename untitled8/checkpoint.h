#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include <vector>

#include "utilities.h"

class checkpoint: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    checkpoint(float px, float py, QGraphicsItem *parent = nullptr);
    void updateTextures();

    gvr::vec2d getRespawn();
    void setRespawn(gvr::vec2d RespawnPos);

    void setNumber(uint Number_);
    void setTextures(std::vector<std::string> NewTextures_);

private slots:
    void Update();

private:
    gvr::vec2d m_RespawnPoint;

    std::vector<std::string> m_Textures;

    QTimer *m_UpdateTimer;

};

#endif // CHECKPOINT_H
