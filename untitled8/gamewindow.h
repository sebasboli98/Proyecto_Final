#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QPushButton>

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
    explicit gamewindow(gvr::udpair playerData_, gvr::udat allData_, QWidget *parent = nullptr);
    ~gamewindow();

private:
    void keyPressEvent(QKeyEvent *Event);
    void keyReleaseEvent(QKeyEvent * Event);
    void mousePressEvent(QMouseEvent *Event);
    void mouseReleaseEvent(QMouseEvent *Event);
    //void mouseMoveEvent(QMouseEvent *Event);

    void MainMenu();
    void LoadData();
    void SaveData();

    void LoadTextures();
    void LoadSounds();

    void AddBlocks();
    void AddEntities();
    void AddPlayer();
    void AddWidgets();

    void RemoveBlocks();
    void RemoveEntities();
    void RemovePlayer();

    void enableCollitions();
    void StartCollitions(uint ms);
    void StopCollitions();

    void enableMovement();
    void StartMovement(uint ms);
    void StopMovement();

    void enableClicks();
    void StartClicks(uint ms);
    void StopClicks();

private slots:
    void CampaignButton();
    void SurvivalButton();
    void ExitButton();

private:
    Ui::gamewindow *ui;
    fmanager *m_fmanager;

    QGraphicsView *MenuView;
    QGraphicsView *GameView;
    QGraphicsView *TexturesView;

    CustomScene *MenuScene;
    CustomScene *GameScene;
    CustomScene *TexturesScene;
    //QGraphicsView *View;

    std::vector<QPushButton *>m_Buttons;
    std::vector<std::string> m_BlockMap;
    std::vector<std::string> m_EnemyMap;

    gvr::udpair m_playerData;
    gvr::udat m_allData;
    std::vector<std::pair<std::string, uint>> m_platforms;
    std::vector<std::pair<uint, std::pair<gvr::llint, int>>> m_decorations;

    player *m_Player;
    std::vector<enemy *> m_Enemies;
    std::vector<block *> m_MovableBlocks;
    std::vector<block *> m_Blocks;
    std::vector<checkpoint *> m_Checkpoints;

    std::queue<std::pair<int, bool>> m_keys;
    std::queue<std::pair<std::pair<int, bool>, gvr::vec2d>> m_Clicks;

    bool m_GameRunning;
    QTimer *m_KeyTimer;
    QTimer *m_CollitionsTimer;
    QTimer *m_MouseTimer;


};

#endif // GAMEWINDOW_H
