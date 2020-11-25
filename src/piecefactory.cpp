#include "piecefactory.h"
#include <list>
#include <vector>
#include <iostream>

/**
 * Constructeur de la PieceFactory
 */
PieceFactory::PieceFactory()
{

}

/**
 * Créé une nouvelle pièce de façon aléatoire
 * @return La pièce créée
 */
Piece PieceFactory::CreatePiece() {

    std::srand((unsigned int)std::time(0));

    int RandomNumber = std::rand() % 7;

    // Création d'une nouvelle pièce
    Piece *newPiece = new Piece(shapeTable[RandomNumber]);

    return *newPiece;
}
