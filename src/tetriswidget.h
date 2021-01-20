// 2020-JCO-Tetris
// Auteur : Membrez Matteo
// Date de la dernière modification : 11.01.21

#ifndef TETRISWIDGET_H
#define TETRISWIDGET_H

#include <QFrame>
#include <QTimer>
#include <QMediaPlaylist>
#include <QMediaPlayer>

/*
 * FREE : indique que le point du tableau est vide
 * FILLED : indique que le point du tableau contient un bloc
 */
typedef enum {
    FREE,
    FILLED
} TetrisValue;

/*
 * O : La forme O
 * I : La forme I
 * J : La forme J
 * L : La forme L
 * T : La forme T
 * S : La forme S
 * Z : La forme Z
 * NO_SHAPE : Pas de forme
 */
typedef enum {
    O,
    I,
    J,
    L,
    T,
    S,
    Z,
    NO_SHAPE
} TetrisShape;

/*
 * ROTATION_0 : la rotation de 0° de la pièce
 * ROTATION_90 : la rotation de 90° de la pièce
 * ROTATION_180 : la rotation de 180° de la pièce
 * ROTATION_270 : la rotation de 270° de la pièce
 */
typedef enum {
    ROTATION_0,
    ROTATION_90,
    ROTATION_180,
    ROTATION_270
} TetrisRotation;

/**
 * Structure qui représente les limites de la pièce
 */
struct Border {
    int dbound; // Bordure inférieure de la pièce
    int lbound; // Bordure gauche de la pièce
    int rbound; // Bordure droite de la pièce
};

const int BOARD_HEIGHT = 20; // Hauteur de l'aire de jeu
const int BOARD_WIDTH = 10; // Largeur de l'aire de jeu

class TetrisWidget : public QFrame
{
    Q_OBJECT
public:

    TetrisWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void addPiece();
    void downPiece();
    void getBorder(Border &border);
    void startTimer(int milliSeconds);
    void setTimer(int milliSeconds);
    void stopTimer();
    void changeTable();
    void blockRotate();
    int clearRow();
    bool isGameOver();
    void resetGame();
    void startMusic();
    void stopMusic();

signals:
    void endOfGame();
    void rowDeleted();
    void oneRowDeleted();
    void twoRowDeleted();
    void threeRowDeleted();
    void fourRowDeleted();

protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *pEvent);

public slots:
    void initTimer();

private:
    // Déclaration du tableau contenant la pièce en mouvement
    int tbTetris[BOARD_WIDTH][BOARD_HEIGHT];

    // Déclaration du tableau contenant les pièces déjà placées
    int tbTetrisFixed[BOARD_WIDTH][BOARD_HEIGHT];

    // Forme de la pièce en mouvement
    TetrisShape shape = NO_SHAPE;

    // L'angle de rotation de la pièce en mouvement
    TetrisRotation rotation = ROTATION_0;

    int posX = 5;
    int posY = 0;
    bool isRunning;
    bool needNextPiece = true;
    bool isCollide;
    int deletedRowCount = 0;
    Border currentBorder;
    QTimer *timer;
    QMediaPlaylist *playlist = new QMediaPlaylist();
    QMediaPlayer *music = new QMediaPlayer();

};

#endif // TETRISWIDGET_H
