#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include <vector>

class checkpoint: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    checkpoint(float px, float py, QGraphicsItem *parent = nullptr);
    void updateTextures();

    void setTextures(std::vector<std::string> NewTextures_);

private slots:
    void Update();

private:
    std::vector<std::string> m_Textures;

    QTimer *m_UpdateTimer;

};

#endif // CHECKPOINT_H
