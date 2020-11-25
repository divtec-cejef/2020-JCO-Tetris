#include "mainfrm.h"
#include "piecefactory.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainFrm w;
    w.show();

    std::srand((unsigned int)std::time(0));

    return a.exec();
}
