// 2020-JCO-Tetris
// Auteur : Membrez Matteo
// Date de la dernière modification : 22.12.20

#ifndef MAINFRM_H
#define MAINFRM_H

#include <QWidget>

namespace Ui {
class MainFrm;
}

class MainFrm : public QWidget
{
    Q_OBJECT

public:
    MainFrm(QWidget *parent = nullptr);
    ~MainFrm();

private slots:
    void on_BT_Start_clicked();
    void onEndOfGame();

    void oneRowDeleted();
    void twoRowDeleted();
    void threeRowDeleted();
    void fourRowDeleted();

private:
    Ui::MainFrm *ui;

    int score = 0;
    int level = 0;
};

#endif // MAINFRM_H
