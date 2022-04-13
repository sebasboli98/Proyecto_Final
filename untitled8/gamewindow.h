#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

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
    Ui::gamewindow *ui;

    gvr::udpair m_playerData;
};

#endif // GAMEWINDOW_H
