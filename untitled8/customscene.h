#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsSceneMouseEvent>

class CustomScene: public QGraphicsScene
{
    Q_OBJECT
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *Event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *Event);

public:
    QPointF ClickPos;
    QPointF MousePos;

};

#endif // CUSTOMSCENE_H
