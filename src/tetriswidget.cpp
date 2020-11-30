#include "tetriswidget.h"

#include <QPainter>

TetrisWidget::TetrisWidget(QWidget *parent, Qt::WindowFlags f) : QFrame(parent, f)
{
    // Initialisation de toutes les cases de l'aire de jeu à FREE
    for(int i = 0; i < BOARD_WIDTH; i++)
        for(int j = 0; j < BOARD_HEIGHT; j++)
            tbTetris[i][j] = FREE;
}

/**
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * créé les éléments graphique du jeu
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
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/**
 * Modifie la pièce actuellement en jeu
 * @param p la pièce actuellement en jeu
*/
void TetrisWidget::setCurrentPiece(Piece p) {
    currentPiece = p;
}

/**
 * Récupère la pièce actuellement en jeu
 * @return la pièce actuellement en jeu
 */
Piece TetrisWidget::GetCurrentPiece() {
    return currentPiece;
}

/**
 * @param i         Coordonnée à partir de laquelle floodfiller dans l'aire de jeu
 * @param j         Coordonnée à partir de laquelle floodfiller dans l'aire de jeu
 * @param px        Coordonnée de la case à partir de laquelle floodfiller dans la matrice de la pièce
 * @param py        Coordonnée de la case à partir de laquelle floodfiller dans la matrice de la pièce
 * @param k         (kind) type de la pièce
 * @param o         (orientation) orientation de la pièce
 * @param value     valeur avec laquelle remplir l'aire de jeu
 * @param visited   Marque les cases du tableau déjà visitées
 */
void TetrisWidget::flood(int i, int j, int px, int py, int k, int o, int value, bool visited[][SIZE])
{
    if(px < 0 || px >= SIZE || py < 0 || py >= SIZE || visited[px][py] || PIECES[k][o][px][py] == FREE)
        return;

    visited[px][py] = true;
    tbTetris[j][i] = value; // On remplit la case de la valeur dans l'aire

    flood(i, j - 1, px, py - 1, k, o, value, visited); // On cherche vers le haut
    flood(i + 1, j, px + 1, py, k, o, value, visited); // On cherche à droite
    flood(i, j + 1, px, py + 1, k, o, value, visited); // On cherche vers le bas
    flood(i - 1, j, px - 1, py, k, o, value, visited); // On cherche à gauche
}

/**
 * Appelle le flood
 */
void TetrisWidget::floodFill(int i, int j, int px, int py, int k, int o, int value)
{
    bool visited[SIZE][SIZE];

    for(int l = 0; l < SIZE; ++l)
        for(int m = 0; m < SIZE; ++m)
            visited[l][m] = false;

    flood(i, j, px, py, k, o, value, visited);
}

/**
 * Dessine une pièce sur l'aire de jeu
 * @param p la pièce à dessiner
 */
void TetrisWidget::drawPiece(Piece p) {

    // On récupère les coordonnées de la pièce
    int i = p.getPosX();
    int j = p.getPosY();

    // On récupère le type et l'orientation de la pièce
    int k = p.getKind();
    int o = p.getOrientation();

    switch (k) {
    case 0:
        p.setColor(CYAN);
        break;
    case 1:
        p.setColor(BLUE);
        break;
    case 2:
        p.setColor(ORANGE);
        break;
    case 3:
        p.setColor(YELLOW);
        break;
    case 4:
        p.setColor(GREEN);
        break;
    case 5:
        p.setColor(PURPLE);
        break;
    case 6:
        p.setColor(RED);
        break;
    default:
        break;
    }

    /* On fait un flood fill à partir du point de pivot de la pièce
     * et on remplit l'aire de jeu en fonction de la couleur de la pièce
     */
    floodFill(i, j, PIVOT_X, PIVOT_Y, k, o, p.getColor());
}

/**
 * Efface une pièce de l'aire de jeu
 * @param p la pièce à effacer
 */
void TetrisWidget::clearPiece(Piece p) {
    int i = p.getPosX();
    int j = p.getPosY();

    int k = p.getKind();
    int o = p.getOrientation();

    floodFill(i, j, PIVOT_X, PIVOT_Y, k, o, FREE);
}

/**
 * Fait apparaître une nouvelle pièce
 * @param p la pièce à faire apparaître
 */
void TetrisWidget::newPiece(Piece p) {

    // On donne à la pièce les coordonnées de l'origine
    p.setPosX(ORIGIN_X);
    p.setPosY(ORIGIN_Y);

    // On dessine la pièce
    drawPiece(p);

    // On déclare cette pièce comme pièce actuelle de l'aire
    setCurrentPiece(p);
}

/**
 * Retire toutes les pièces de l'aire de jeu
 */
void TetrisWidget::clear() {
    for(int i = 0; i < BOARD_WIDTH; i++) {
        for(int j = 0; j < BOARD_HEIGHT; j++)
            tbTetris[i][j] = FREE;
    }
}
