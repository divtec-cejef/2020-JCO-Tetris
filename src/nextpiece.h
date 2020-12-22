// 2020-JCO-Tetris
// Auteur : Membrez Matteo
// Date de la dernière modification : 22.12.20

#ifndef NEXTPIECE_H
#define NEXTPIECE_H

#include <QFrame>

class NextPiece : public QFrame
{

public:
    NextPiece(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

protected:
    void paintEvent(QPaintEvent* pEvent);
};

#endif // NEXTPIECE_H
