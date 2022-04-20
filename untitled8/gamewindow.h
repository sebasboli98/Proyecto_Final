#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>

#include <queue>

#include "fmanager.h"
#include "block.h"
#include "player.h"
#include "enemy.h"
#include "proyectile.h"
#include "explotion.h"
#include "checkpoint.h"
#include "customscene.h"

#include "utilities.h"

namespace Ui {
class gamewindow;
}

class gamewindow : public QWidget
{
    Q_OBJECT

public:
    explicit gamewindow(gvr::udpair playerData_, QWidget *parent = nullptr);
    ~gamewindow();

private:
    void keyPressEvent(QKeyEvent *Event);
    void keyReleaseEvent(QKeyEvent * Event);
    void mousePressEvent(QMouseEvent *Event);
    void mouseMoveEvent(QMouseEvent *Event);

    void LoadTextures();
    void LoadSounds();

    void AddBlocks();
    void AddEntities();
    void AddPlayer();

    void enableCollitions();
    void StartCollitions(uint ms);
    void StopCollitions();

    void enableMovement();
    void StartMovement(uint ms);
    void StopMovement();

private:
    Ui::gamewindow *ui;
    QTimer *m_Collitions;

    QGraphicsView *MenuView;
    QGraphicsView *GameView;
    QGraphicsView *TexturesView;

    CustomScene *MenuScene;
    CustomScene *GameScene;
    CustomScene *TexturesScene;
    //QGraphicsView *View;

    bool m_GameRunning;

    gvr::udpair m_playerData;
    player *p;
    std::vector<std::pair<std::string, uint>> m_platforms;
    std::vector<std::pair<uint, std::pair<gvr::llint, int>>> m_decorations;

    explotion *Test1;

    std::queue<int> m_keys;
    QTimer *m_KeyTimer;

};

#endif // GAMEWINDOW_H
