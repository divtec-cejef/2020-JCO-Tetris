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

    void onRowDeleted();
    void onOneRowDeleted();
    void onTwoRowDeleted();
    void onThreeRowDeleted();
    void onFourRowDeleted();

private:
    Ui::MainFrm *ui;

    // Palier des différents niveaux
    // En fonction du score
    const int SCORE_LEVEL1 = 500;
    const int SCORE_LEVEL2 = 1000;
    const int SCORE_LEVEL3 = 5000;
    const int SCORE_LEVEL4 = 10000;
    const int SCORE_LEVEL5 = 20000;
    const int SCORE_LEVEL6 = 40000;

    int score = 0;
    int level = 0;
};

#endif // MAINFRM_H
