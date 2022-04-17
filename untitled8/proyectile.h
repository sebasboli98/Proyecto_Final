#ifndef PROYECTILE_H
#define PROYECTILE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class proyectile: public QObject, QGraphicsPixmapItem
{
    Q_OBJECT
public:
    proyectile(float ax, float ay, std::string texture, QGraphicsItem *parent = nullptr);
    proyectile(float px, float py, proyectile *Cast);


};

#endif // PROYECTILE_H
