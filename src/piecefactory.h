#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H

#include "piece.h"
#include <QList>

class PieceFactory
{
public:
    PieceFactory();
    Piece CreatePiece();

private:

    static const int NB_SHAPES = 7;
    static const int SIZE = 4;

    int shapeTable[NB_SHAPES][SIZE][SIZE] =
    {
        // Carré
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 2, 0},
            {0, 0, 0, 0}
        },
        // I
        {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 2, 0, 0},
            {0, 1, 0, 0}
        },
        // T
        {
            {0, 1, 0, 0},
            {0, 2, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },
        // Z Gauche
        {
            {0, 0, 1, 0},
            {0, 1, 2, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },
        // Z Droite
        {
            {0, 1, 0, 0},
            {0, 2, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 0}
        },
        // L Droite
        {
            {0, 0, 1, 0},
            {0, 0, 2, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        // L Gauche
        {
            {0, 1, 0, 0},
            {0, 2, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        }
    };
};

#endif // PIECEFACTORY_H
