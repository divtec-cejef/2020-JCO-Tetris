#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"
#include "ui_gamewindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuitter_triggered()
{
    this->close();
}



void MainWindow::on_BT_Solo_clicked()
{
    gameWindow->show();
    this->close();
}
