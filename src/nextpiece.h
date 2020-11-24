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
