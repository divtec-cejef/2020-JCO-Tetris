#include "tetriswidget.h"

#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>

/**
 * Constructeur de la zone de jeu
 */
TetrisWidget::TetrisWidget(QWidget *parent, Qt::WindowFlags f) : QFrame(parent, f)
{
    // Initialisation de toutes les cases de l'aire de jeu à FREE
    for(int i = 0; i < BOARD_WIDTH; i++)
        for(int j = 0; j < BOARD_HEIGHT; j++) {
            tbTetris[i][j] = FREE;
            tbTetrisFixed[i][j] = FREE;
        }

    // Force le focus sur la zone de jeu
    setFocusPolicy(Qt::StrongFocus);
}

/**
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Dessine les éléments graphique du jeuEn fonction des valeurs dans le tableau
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

    // Parcours le tableau pour peindre les pièces
    for(int i = 0; i < BOARD_WIDTH; i++)
        for(int j = 0; j < BOARD_HEIGHT; j++) {
            // Peint la pièce mobile en rouge
            if(tbTetris[i][j] == FILLED) {
                painter.fillRect(i*tilePosX, j*tilePosY, TILE_SIZE, TILE_SIZE, QBrush(Qt::red));
            }
            // Peint les pièces fixes en vert
            if(tbTetrisFixed[i][j] == FILLED) {
                painter.fillRect(i*tilePosX, j*tilePosY, TILE_SIZE, TILE_SIZE, QBrush(Qt::green));
            }
        }


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
 * Ajoute une pièce au tableau
 */
void TetrisWidget::addPiece() {

    // Choisi un nombre aléatoire entre 0 et 6
    int randomNumber = std::rand() % 7;

    // Ajoute au tableau la forme choisie
    switch (randomNumber) {
    // I
    case 0:
        tbTetris[5][0] = FILLED;
        tbTetris[5][1] = FILLED;
        tbTetris[5][2] = FILLED;
        tbTetris[5][3] = FILLED;

        shape = I;
        break;
    // L
    case 1:
        tbTetris[4][0] = FILLED;
        tbTetris[4][1] = FILLED;
        tbTetris[4][2] = FILLED;
        tbTetris[5][2] = FILLED;

        shape = L;
        break;
    // J
    case 2:
        tbTetris[5][0] = FILLED;
        tbTetris[5][1] = FILLED;
        tbTetris[5][2] = FILLED;
        tbTetris[4][2] = FILLED;

        shape = J;
        break;
    // O
    case 3:
        tbTetris[5][0] = FILLED;
        tbTetris[5][1] = FILLED;
        tbTetris[4][0] = FILLED;
        tbTetris[4][1] = FILLED;

        shape = O;
        break;
    // S
    case 4:
        tbTetris[5][0] = FILLED;
        tbTetris[6][0] = FILLED;
        tbTetris[5][1] = FILLED;
        tbTetris[4][1] = FILLED;

        shape = S;
        break;
    // Z
    case 5:
        tbTetris[5][0] = FILLED;
        tbTetris[4][0] = FILLED;
        tbTetris[5][1] = FILLED;
        tbTetris[6][1] = FILLED;

        shape = Z;
        break;
    // T
    case 6:
        tbTetris[5][0] = FILLED;
        tbTetris[5][1] = FILLED;
        tbTetris[6][1] = FILLED;
        tbTetris[4][1] = FILLED;

        shape = T;
        break;
    }

    posX = 5;
    posY = 0;
    rotation = ROTATION_0;
    needNextPiece = false;
    getBorder(currentBorder);
}

/**
 * Fait descendre la pièce de 1 case
 * jusqu'à ce qu'elle touche le fond ou qu'elle atteigne une autre pièce
 */
void TetrisWidget::downPiece() {

    // Vérifie si un des carreaux ne peut pas aller plus bas
    // car un autre carreau se trouve en dessous de lui
    for(int i = BOARD_WIDTH-1; i >= 0; i--)
        for(int j = BOARD_HEIGHT-1; j >= 0; j--)
            if(tbTetris[i][j] == FILLED && tbTetrisFixed[i][j+1] == FILLED) {
                isCollide = true;
            }

    // Parcours le tableau
    for(int i = BOARD_WIDTH-1; i >= 0; i--)
        for(int j = BOARD_HEIGHT-1; j >= 0; j--) {

            // Stop la pièce si elle arrive tout en bas du tableau
            if(currentBorder.dbound == BOARD_HEIGHT-1) {
                changeTable();
                return;

            } else if(tbTetris[i][j] == FILLED) {

                // Stop la pièce si une pièce se trouve sous elle
                if(tbTetrisFixed[i][j+1] == FILLED) {
                    changeTable();
                    isCollide = false;
                    return;

                // Descend la pièce si aucune pièce ne se trouve sous elle
                } else if(!isCollide) {
                    tbTetris[i][j] = FREE;
                    tbTetris[i][j+1] = FILLED;
                    posY++;
                }
            }
        }
    currentBorder.dbound++;
}

/**
 * Transfère tous les carreaux remplis du tableau de la pièce mobile
 * Dans le tableau des pièces fixes
 */
void TetrisWidget::changeTable() {
    for(int i = BOARD_WIDTH-1; i >= 0; i--)
        for(int j = BOARD_HEIGHT-1; j >= 0; j--)
            if(tbTetris[i][j] == FILLED) {
                tbTetrisFixed[i][j] = FILLED;
                tbTetris[i][j] = FREE;
            }
    needNextPiece = true;
}

/**
 * Définit les bordures des pièces
 * @param border strucutre des bordures
 */
void TetrisWidget::getBorder(Border &border) {

    // Permet de définir le carreau le plus bas et le plus à droite de la pièce
    int oldPosY = 0;
    for(int i = 0; i < BOARD_WIDTH; i++)
        for(int j = 0; j < BOARD_HEIGHT; j++)
            if(tbTetris[i][j] == FILLED) {

                // Carreau le plus à droite de la pièce
                border.rbound = i;

                // Carreau le plus bas de la pièce
                if(oldPosY <= j) {
                    border.dbound = j;
                }
                oldPosY = j;
            }

    // Permet de définir le carreau le plus à gauche de la pièce
    for (int i = BOARD_WIDTH-1; i >= 0; i--)
        for(int j = 0; j < BOARD_HEIGHT; j++)
            if(tbTetris[i][j] == FILLED) {
                border.lbound = i;
            }

}

/**
 * Provoque la rotation de la pièce de 90°
 */
void TetrisWidget::blockRotate() {

    // Effectue la rotation en fonction de
    // la forme actuellement en mouvement
    switch (shape) {
    case O:
        break;

    case I:
        // Gère les 4 orrientation de la pièce I
        switch(rotation) {
        case ROTATION_0:
            tbTetris[posX-1][posY+2] = FREE;
            tbTetris[posX+1][posY+2] = FREE;
            tbTetris[posX+2][posY+2] = FREE;

            tbTetris[posX][posY] = FILLED;
            tbTetris[posX][posY+1] = FILLED;
            tbTetris[posX][posY+2] = FILLED;
            tbTetris[posX][posY+3] = FILLED;

            rotation = ROTATION_90;
            break;

        case ROTATION_90:
            tbTetris[posX][posY] = FREE;
            tbTetris[posX][posY+1] = FREE;
            tbTetris[posX][posY+3] = FREE;

            tbTetris[posX-1][posY+2] = FILLED;
            tbTetris[posX][posY+2] = FILLED;
            tbTetris[posX+1][posY+2] = FILLED;
            tbTetris[posX+2][posY+2] = FILLED;

            rotation = ROTATION_180;
            break;

        case ROTATION_180:
            tbTetris[posX-1][posY+2] = FREE;
            tbTetris[posX+1][posY+2] = FREE;
            tbTetris[posX+2][posY+2] = FREE;

            tbTetris[posX][posY] = FILLED;
            tbTetris[posX][posY+1] = FILLED;
            tbTetris[posX][posY+2] = FILLED;
            tbTetris[posX][posY+3] = FILLED;

            rotation = ROTATION_270;
            break;

        case ROTATION_270:
            tbTetris[posX][posY] = FREE;
            tbTetris[posX][posY+1] = FREE;
            tbTetris[posX][posY+3] = FREE;

            tbTetris[posX-1][posY+2] = FILLED;
            tbTetris[posX][posY+2] = FILLED;
            tbTetris[posX+1][posY+2] = FILLED;
            tbTetris[posX+2][posY+2] = FILLED;

            rotation = ROTATION_0;
            break;
        }

        break;

    case J:
        // Gère les 4 orrientation de la pièce J
        switch(rotation) {
        case ROTATION_0:

            break;

        case ROTATION_90:

            break;

        case ROTATION_180:

            break;

        case ROTATION_270:

            break;
        }

        break;

    case L:
        // Gère les 4 orrientation de la pièce L
        switch(rotation) {
        case ROTATION_0:

            break;

        case ROTATION_90:

            break;

        case ROTATION_180:

            break;

        case ROTATION_270:

            break;
        }

        break;

    case T:
        // Gère les 4 orrientation de la pièce T
        switch(rotation) {
        case ROTATION_0:

            break;

        case ROTATION_90:

            break;

        case ROTATION_180:

            break;

        case ROTATION_270:

            break;
        }

        break;

    case S:
        // Gère les 4 orrientation de la pièce S
        switch(rotation) {
        case ROTATION_0:

            break;

        case ROTATION_90:

            break;

        case ROTATION_180:

            break;

        case ROTATION_270:

            break;
        }

        break;

    case Z:
        // Gère les 4 orrientation de la pièce Z
        switch(rotation) {
        case ROTATION_0:

            break;

        case ROTATION_90:

            break;

        case ROTATION_180:

            break;

        case ROTATION_270:

            break;
        }

        break;

    case NO_SHAPE:
        break;
    }
}

/**
 * Lance le timer
 */
void TetrisWidget::startTimer() {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(initTimer()));
    timer->start(1000);
}

/**
 * Gère le code à exécuter dans le timer
 */
void TetrisWidget::initTimer() {
    update();
    downPiece();

    // Vérifie s'il faut ajouter une nouvelle pièce
    if(needNextPiece) {
        addPiece();
    }
}

/**
 * Gère les événements effectués lors de l'appui sur les touches du clavier
 * @param event l'événement réalisé
 */
void TetrisWidget::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {
    // Flèche de gauche
    // Aller à gauche si n'est pas à la limite gauche
    case Qt::Key_Left:
        if(currentBorder.lbound != 0) {
            for(int i = 0; i < BOARD_WIDTH; i++)
                for(int j = BOARD_HEIGHT-1; j >= 0; j--)
                    if(tbTetris[i][j] == FILLED) {
                        tbTetris[i][j] = FREE;
                        tbTetris[i-1][j] = FILLED;
                        posX--;
                    }
            update();
            currentBorder.lbound--;
            currentBorder.rbound--;
        }
        break;

    // Flèche de droite
    // Aller à droite si n'est pas à la limite droite
    case Qt::Key_Right:
        if(currentBorder.rbound < BOARD_WIDTH-1) {
            for(int i = BOARD_WIDTH-1; i >= 0; i--)
                for(int j = BOARD_HEIGHT-1; j >= 0; j--)
                    if(tbTetris[i][j] == FILLED) {
                        tbTetris[i][j] = FREE;
                        tbTetris[i+1][j] = FILLED;
                        posX++;
                    }
            update();
            currentBorder.lbound++;
            currentBorder.rbound++;
        }

        break;

    // Flèche du bas
    // Faire descendre la pièce
    case Qt::Key_Down:
        downPiece();
        update();
        break;

    // Flèche du haut
    // Rotation
    case Qt::Key_Up:
        blockRotate();
        update();
        break;

    // Barre espace
    // Faire tomber la pièce
    case Qt::Key_Space:

        update();
        break;
    }
}
