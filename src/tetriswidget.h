#ifndef TETRISWIDGET_H
#define TETRISWIDGET_H

#include "piece.h"
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
    int tbTetris[BOARD_WIDTH][BOARD_HEIGHT];

    TetrisWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void setCurrentPiece(Piece p);
    Piece GetCurrentPiece();
    void drawPiece(Piece p);
    void clearPiece(Piece p);
    void newPiece(Piece p);
    void clear();

protected:
    void paintEvent(QPaintEvent* pEvent);

private:
    void flood(int i, int j, int px, int py, int k, int o, int value, bool visited[][SIZE]);
    void floodFill(int i, int j, int px, int py, int k, int o, int value);

    Piece currentPiece; // La pièce qui se trouve sur l'aire de jeu
    Piece ghostPiece; // La pièce qui représente la position où sera la pièce

};

#endif // TETRISWIDGET_H
