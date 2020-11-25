#include "tetriswidget.h"

#include <QPainter>

TetrisWidget::TetrisWidget(QWidget *parent, Qt::WindowFlags f) : QFrame(parent, f)
{

}

/**
 * @brief TetrisWidget::paintEvent créé les éléments graphique du jeu
 */
void TetrisWidget::paintEvent(QPaintEvent* pEvent) {
    QPainter painter(this);

    // Constantes
    const int WIDTH = 340;
    const int HEIGHT = 680;
    const int TILE_SIZE = 34;

    // Variables
    int tilePosX = 34;
    int tilePosY = 34;

    // Création de la pièce Z Gauche
    painter.fillRect(tilePosX*0, tilePosY*0, TILE_SIZE, TILE_SIZE, QBrush(Qt::red));
    painter.fillRect(tilePosX, tilePosY*0, TILE_SIZE, TILE_SIZE, QBrush(Qt::red));
    painter.fillRect(tilePosX, tilePosY, TILE_SIZE, TILE_SIZE, QBrush(Qt::red));
    painter.fillRect(tilePosX*2, tilePosY, TILE_SIZE, TILE_SIZE, QBrush(Qt::red));

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
}
