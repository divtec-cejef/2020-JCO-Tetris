#include "mainfrm.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainFrm w;
    w.show();

    return a.exec();
}
