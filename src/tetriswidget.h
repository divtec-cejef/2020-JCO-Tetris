#ifndef TETRISWIDGET_H
#define TETRISWIDGET_H

#include <QFrame>

/*
 * FREE : indique que le point du tableau est vide
 * FILLED : indique que le point du tableau contient un bloc
 */
typedef enum {
    FREE,
    FILLED
} TetrisValue;

const int BOARD_HEIGHT = 20; // Hauteur de l'aire de jeu
const int BOARD_WIDTH = 10; // Largeur de l'aire de jeu

const int ORIGIN_X = 0; // L'ordonnée du point de pivot
const int ORIGIN_Y = 5; // Son abscisse

class TetrisWidget : public QFrame
{
public:
    // Déclaration du tableau représentant l'aire de jeu


    TetrisWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void addPiece();
    void downPiece();
    void startTimer();


protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent* pEvent);

private:
    int tbTetris[BOARD_WIDTH][BOARD_HEIGHT];

    bool timer = true;

    bool needNextPiece = true;

};

#endif // TETRISWIDGET_H
