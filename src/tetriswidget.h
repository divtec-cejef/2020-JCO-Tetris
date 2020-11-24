#ifndef TETRISWIDGET_H
#define TETRISWIDGET_H

#include <QFrame>

class TetrisWidget : public QFrame
{
public:
    TetrisWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

protected:
    void paintEvent(QPaintEvent* pEvent);

private:

};

#endif // TETRISWIDGET_H
