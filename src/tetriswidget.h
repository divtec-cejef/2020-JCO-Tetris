#ifndef TETRISWIDGET_H
#define TETRISWIDGET_H

#include <QFrame>
#include <QTimer>

/*
 * FREE : indique que le point du tableau est vide
 * FILLED : indique que le point du tableau contient un bloc
 */
typedef enum {
    FREE,
    FILLED
} TetrisValue;

/**
 * Structure qui représente les limites de la pièce
 */
struct Border {
    int ubound;
    int dbound;
    int lbound;
    int rbound;
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
    void startTimer();


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

    bool isRunning;
    bool needNextPiece = true;
    bool isCollide;
    Border currentBorder;
    QTimer *timer;

};

#endif // TETRISWIDGET_H
