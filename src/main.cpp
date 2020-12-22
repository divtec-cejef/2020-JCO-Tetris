// 2020-JCO-Tetris
// Auteur : Membrez Matteo
// Date de la dernière modification : 22.12.20

#include "mainfrm.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainFrm w;
    w.show();

    std::srand((unsigned int)std::time(0));

    return a.exec();
}
