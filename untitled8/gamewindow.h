#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>

#include "block.h"
#include "fmanager.h"
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
    void AddBlocks();

    void enableCollitions();
    void StartCollitions(uint t);
    void StopCollitions();

private:
    Ui::gamewindow *ui;
    QTimer *m_Collitions;

    QGraphicsView *MenuView;
    QGraphicsView *GameView;
    QGraphicsView *TexturesView;

    QGraphicsScene *MenuScene;
    QGraphicsScene *GameScene;
    QGraphicsScene *TexturesScene;
    //QGraphicsView *View;

    gvr::udpair m_playerData;
    std::vector<std::pair<std::string, uint>> m_platforms;
    std::vector<std::pair<uint, std::pair<gvr::llint, int>>> m_decorations;
};

#endif // GAMEWINDOW_H
