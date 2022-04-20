#include "customscene.h"

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *Event){
    ClickPos = Event->scenePos();
}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *Event){
    MousePos = Event->scenePos();
}
