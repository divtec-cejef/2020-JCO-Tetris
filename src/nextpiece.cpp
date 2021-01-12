// 2020-JCO-Tetris
// Auteur : Membrez Matteo
// Date de la dernière modification : 22.12.20

#include "nextpiece.h"

#include <QPainter>

NextPiece::NextPiece(QWidget *parent, Qt::WindowFlags f) : QFrame (parent, f)
{

}

/**
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Dessine la future pièce
 */
void NextPiece::paintEvent(QPaintEvent* pEvent) {

    QPainter painter(this);

    // Constantes
    const int WIDTH = 136;
    const int HEIGHT = 136;
    const int TILE_SIZE = 34;

    const int tilePosX = 34;
    const int tilePosY = 34;

    // Création de la prochaine pièce
    painter.fillRect(tilePosX*2, tilePosY*0, TILE_SIZE, TILE_SIZE, QBrush(Qt::red));
    painter.fillRect(tilePosX*2, tilePosY*1, TILE_SIZE, TILE_SIZE, QBrush(Qt::red));
    painter.fillRect(tilePosX*2, tilePosY*2, TILE_SIZE, TILE_SIZE, QBrush(Qt::red));
    painter.fillRect(tilePosX*2, tilePosY*3, TILE_SIZE, TILE_SIZE, QBrush(Qt::red));

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

