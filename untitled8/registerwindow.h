#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QDialog>

namespace Ui {
class registerwindow;
}

class registerwindow : public QDialog
{
    Q_OBJECT

public:
    explicit registerwindow(bool mode_, QWidget *parent = nullptr);
    ~registerwindow();

private slots:
    void on_Continue_clicked();

    void on_Exit_clicked();

private:
    Ui::registerwindow *ui;
};

#endif // REGISTERWINDOW_H
