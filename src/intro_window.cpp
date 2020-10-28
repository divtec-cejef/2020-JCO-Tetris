#include "intro_window.h"
#include "game_window.h"
#include "ui_intro_window.h"

intro_window::intro_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::intro_window)
{
    ui->setupUi(this);
}

intro_window::~intro_window()
{
    delete ui;
}

void intro_window::on_actionQuitter_triggered()
{
    this->close();
}

void intro_window::on_BT_Solo_clicked()
{
    GameWindow *gameWindow = new GameWindow;
    gameWindow->show();
    this->close();
}
