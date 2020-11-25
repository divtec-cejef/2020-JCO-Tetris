#include "piecefactory.h"
#include <QApplication>

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

    int RandomNumber = std::rand() % 7;

    // Création d'une nouvelle pièce
    Piece *newPiece = new Piece(shapeTable[RandomNumber]);

    return *newPiece;
}
