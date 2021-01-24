// 2020-JCO-Tetris
// Auteur : Membrez Matteo
// Date de la dernière modification : 24.01.21

#include "nextpiece.h"

#include <QPainter>

NextPiece::NextPiece(QWidget *parent, Qt::WindowFlags f) : QFrame (parent, f)
{

}

/**
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Dessine la prochaine pièce
 */
void NextPiece::paintEvent(QPaintEvent* pEvent) {

    QPainter painter(this);

    // Constantes
    const int WIDTH = 136;
    const int HEIGHT = 136;
    const int TILE_SIZE = 34;

    const int tilePosX = 34;
    const int tilePosY = 34;

    int x = 0;
    int y = TILE_SIZE;
    int yNextPoint = TILE_SIZE;

    // Ajout des lignes horizontales (x20)
    while(y < HEIGHT) {
        painter.drawLine(x, y, WIDTH, yNextPoint);
        y += TILE_SIZE;
        yNextPoint += TILE_SIZE;
    }

    x = TILE_SIZE;
    y = 0;
    int xNextPoint = TILE_SIZE;

    // Ajout des lignes verticales (x10)
    while(x < WIDTH) {
        painter.drawLine(x, y, xNextPoint, HEIGHT);
        x += TILE_SIZE;
        xNextPoint += TILE_SIZE;
    }

    QFrame::paintEvent(pEvent);

}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

